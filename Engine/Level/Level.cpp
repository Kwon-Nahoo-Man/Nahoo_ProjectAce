#include "Level.h"
#include "Core/Input.h"
#include "Actor/Actor.h"
#include "UI/UIClass.h"
#include "Component/HitComponent.h"
#include "Enumeration/CollisionType.h"
#include "Partition/QuadTree.h"
#include "Engine/Engine.h"

Nahoo::C_LEVEL::C_LEVEL(bool quadTreeFlag)
{
	if (quadTreeFlag == true)
	{
		m_quadTree = new C_QUADTREE(0, 0, Nahoo::C_ENGINE::GetInstance().GetWidth(), Nahoo::C_ENGINE::GetInstance().GetHeight(), 4);
	}
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

	if (m_quadTree != nullptr)
	{
		delete m_quadTree;
		m_quadTree = nullptr;
	}

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

	if (m_quadTree != nullptr)
	{
		ProcessQuadTree();
	}
	
	if (Nahoo::C_INPUT::GetInstance().GetKeyDown(VK_F1))
	{
		SetDebugDraw(E_DEBUGSHOW::HitComponent);
	}
	if (Nahoo::C_INPUT::GetInstance().GetKeyDown(VK_F2))
	{
		SetDebugDraw(E_DEBUGSHOW::QuadTree);
	}

}

void Nahoo::C_LEVEL::Draw()
{
	bool HitComponentDebugShow = BitMask::HasFlag(m_debugShow, E_DEBUGSHOW::HitComponent);
	


	for (C_ACTOR* actor : m_actors)
	{
		actor->Draw(HitComponentDebugShow);
	}

	for (C_UICLASS* UI : m_UIs)
	{
		UI->Draw();
	}

}

void Nahoo::C_LEVEL::SetDebugDraw(E_DEBUGSHOW changeValue)
{
	// Check: 현재 QuadTree의 Debug Submit은 Tick()에서, HitComponent의 Debug Submit은 Draw()에서 이루어짐
	m_debugShow = m_debugShow ^ changeValue;
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

void Nahoo::C_LEVEL::ProcessQuadTree()
{
	int length = static_cast<int>(m_actorHitComps.size());
	// 쿼드트리에 충돌할 Hit Component 삽입
	if (length != 0)
	{

		for (int i = 0; i < length; ++i)
		{
			m_quadTree->Insert(m_actorHitComps[i]);
		}
		for (int i = 0; i < length; ++i)
		{
			m_quadTree->QueryCollision(m_actorHitComps[i]);
		}
		
		// 렌더 submit 타이밍이 Draw()가 아닌 Tick()임을 숙지
		if (BitMask::HasFlag(m_debugShow, E_DEBUGSHOW::QuadTree) == true)
		{
			m_quadTree->DebugShow();
		}
		
		// 쿼드트리 노드 안 Hit Component list 삭제
		m_quadTree->ClearCompList();
	}
	
}



////Legacy Collision Check(not using QuadTree)
//for (int i = 0; i < length - 1; i++)
//{
//	for (int j = i + 1; j < length; j++)
//	{
//		if (m_actorHitComps[i]->IsActive() == true && m_actorHitComps[j]->IsActive() == true)
//		{
//			// 히트판정
//			m_actorHitComps[i]->HasCollided(m_actorHitComps[j]);
//			// Legacy 방식으로 할려면 HitComponent의 HasCollided 함수에서 otherComp->Onhit()까지 불러줘야함
//		}
//	}
//}