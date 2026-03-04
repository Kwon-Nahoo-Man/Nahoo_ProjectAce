#include "Level.h"
#include "Actor/Actor.h"
#include "UI/UIClass.h"
#include "Component/HitComponent.h"
#include "Enumeration/CollisionType.h"

Nahoo::C_LEVEL::C_LEVEL()
{

}

Nahoo::C_LEVEL::~C_LEVEL()
{
	for (C_ACTOR*& actor : m_addRequestedActors)
	{
		if (actor != nullptr)
		{
			delete actor;
			actor = nullptr;
		}
	}
	m_addRequestedActors.clear();

	for (C_ACTOR*& actor : m_actors)
	{
		if (actor)
		{
			delete actor;
			actor = nullptr;
		}
	}

	m_actors.clear();

	for (C_UICLASS*& UI : m_addRequestedUIs)
	{
		if (UI != nullptr)
		{
			delete UI;
			UI = nullptr;
		}
	}
	m_addRequestedUIs.clear();

	for (C_UICLASS*& UI : m_UIs)
	{
		if (UI != nullptr)
		{
			delete UI;
			UI = nullptr;
		}
	}
	m_UIs.clear();
}

void Nahoo::C_LEVEL::BeginPlay()
{
	for (C_ACTOR* actor : m_actors)
	{
		if (actor->HasBegunPlay() == false)
		{
			actor->BeginPlay();
		}
	}
	
	for (C_UICLASS* UI : m_UIs)
	{
		if (UI->HasBegunPlay() == false)
		{
			UI->BeginPlay();
		}
	}
}

void Nahoo::C_LEVEL::Tick(float deltaTime)
{
	for (C_ACTOR* actor : m_actors)
	{
		actor->Tick(deltaTime);
	}

	for (C_UICLASS* UI : m_UIs)
	{
		UI->Tick(deltaTime);
	}


	int length = static_cast<int>(m_actorHitComps.size());
	for (int i = 0; i < length-1; i++)
	{
		for (int j = i + 1; j < length; j++)
		{
			if (m_actorHitComps[i]->GetCurrentCollision() && m_actorHitComps[j]->GetCurrentCollision())
			{
				if (m_actorHitComps[i]->GetCollisionType() != E_COLLISIONTYPE::None ||
					(!(m_actorHitComps[i]->DestroyRequested()) && !(m_actorHitComps[j]->DestroyRequested())))
				{
					// 히트 판정
					m_actorHitComps[i]->HasCollided(*(m_actorHitComps[j]));
				}
			}
			
		}
	}
}

void Nahoo::C_LEVEL::Draw()
{
	for (C_ACTOR* actor : m_actors)
	{
		actor->Draw();
	}

	for (C_UICLASS* UI : m_UIs)
	{
		UI->Draw();
	}
}

void Nahoo::C_LEVEL::AddNewActor(C_ACTOR* newActor)
{
	// 프레임 처리 고려해서 추가작업 
	m_addRequestedActors.emplace_back(newActor);

	newActor->SetOwner(this);
}

void Nahoo::C_LEVEL::AddNewUI(C_UICLASS* newUI)
{
	m_addRequestedUIs.emplace_back(newUI);
	newUI->SetOwner(this);
}

void Nahoo::C_LEVEL::ProcessClasses()
{
	ProcessDeleteActor();
	ProcessDeleteUI();

	if (m_addRequestedActors.size() != 0)
	{
		ProcessAddActor();
	}

	if (m_addRequestedUIs.empty() == false)
	{
		ProcessAddUI();
	}

}

void Nahoo::C_LEVEL::ProcessAddActor()
{
	for (C_ACTOR* actor : m_addRequestedActors)
	{
		m_actors.emplace_back(actor);

		// 액터가 m_actors 배열에 들어가고 나서 component 배열에 추가
		if (actor->GetHitComponent() != nullptr)
		{
			m_actorHitComps.emplace_back(actor->GetHitComponent());
		}
		

		// 액터는 이미 m_addRequestedActors에 들어갈 때 부터 생성될 것이기 때문에 (AddNewActor(new C_ACTOR))
		// 이미 C_ACTOR 생성자 기점은 지나서 HitComponent는 존재한다.

	}
	m_addRequestedActors.clear();
}

void Nahoo::C_LEVEL::ProcessAddUI()
{
	for (C_UICLASS* UI : m_addRequestedUIs)
	{
		m_UIs.emplace_back(UI);
	}
	m_addRequestedUIs.clear();
}

void Nahoo::C_LEVEL::ProcessDeleteActor()
{
	
	int cycles{};
	cycles = static_cast<int>(m_actors.size());
	for (int i = 0; i < cycles;)
	{
		if (m_actors[i]->DestroyRequested() == true)
		{
			C_ACTOR* pTargetActor = m_actors[i];
			COMP_HITCOMPONENT* pTargetComp = pTargetActor->GetHitComponent();

			if (pTargetComp != nullptr)
			{
				auto iter = std::find(m_actorHitComps.begin(), m_actorHitComps.end(), pTargetComp);
				if (iter != m_actorHitComps.end())
				{
					m_actorHitComps.erase(iter);
				}
			}

			delete pTargetActor;
			m_actors.erase(m_actors.begin() + i);
			cycles -= 1;
		}
		else
		{
			i++;
		}
	}
}

void Nahoo::C_LEVEL::ProcessDeleteUI()
{
	int cycles{};
	cycles = static_cast<int>(m_UIs.size());

	for (int i = 0; i < cycles;)
	{
		if (m_UIs[i]->DestroyRequested() == true)
		{
			delete m_UIs[i];
			m_UIs.erase(m_UIs.begin() + i);
			cycles -= 1;
		}
		else
		{
			++i;
		}
	}
}


