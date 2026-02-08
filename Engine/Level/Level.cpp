#include "Level.h"
#include "Actor/Actor.h"
#include "Component/HitComponent.h"
#include "Enumeration/CollisionType.h"

Nahoo::C_LEVEL::C_LEVEL()
{

}

Nahoo::C_LEVEL::~C_LEVEL()
{
	for (C_ACTOR* actor : m_actors)
	{
		if (actor)
		{
			delete actor;
			actor = nullptr;
		}
	}

	m_actors.clear();
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
}

void Nahoo::C_LEVEL::Tick(float deltaTime)
{
	for (C_ACTOR* actor : m_actors)
	{
		actor->Tick(deltaTime);
	}


	int length = static_cast<int>(m_actorHitComps.size());
	for (int i = 0; i < length-1; i++)
	{
		for (int j = i + 1; j < length; j++)
		{
			if (m_actorHitComps[i]->GetCollitionType() != E_COLLISIONTYPE::None)
			{
				// 히트 판정
				m_actorHitComps[i]->HasCollided(*(m_actorHitComps[j]));
			}
			
		}
	}
}

void Nahoo::C_LEVEL::Draw()
{
	for (C_ACTOR* actor : m_actors)
	{
		if (actor->IsActive())
		{
			actor->Draw();
		}
	}
}

void Nahoo::C_LEVEL::AddNewActor(C_ACTOR* newActor)
{
	// 프레임 처리 고려해서 추가작업 
	m_addRequestedActors.emplace_back(newActor);

	newActor->SetOwner(this);
}

void Nahoo::C_LEVEL::ProcessActors()
{
	// Todo: 만약 actor에 오너쉽이 생기면, actor에서 delete할 때 Level의 deleteRequestedActor 배열에 추가해서 조건식 추가
	// if(m_deleteRequestedActors.size() != 0)
	ProcessDeleteActor();


	if (m_addRequestedActors.size() != 0)
	{
		ProcessAddActor();
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

void Nahoo::C_LEVEL::ProcessDeleteActor()
{
	// Todo: 만약 actor에 오너쉽 생기면, for루프 deleteRequestedActor 배열로 변경
	// 근데 deleteRequestedActor 배열 따로 관리하면, m_actors에서 deleteRequestedActor에서 지워야 할 actor는 어떻게 고르지?
	
	// 액터 배열 지우기 전에 컴포넌트 먼저 배열에서 제거
	int cycles{};
	cycles = static_cast<int>(m_actorHitComps.size());
	for (int i = 0; i < cycles;)
	{
		if (m_actorHitComps[i]->DestroyRequested() == true)
		{
			// 컴포넌트의 해제는 액터에서 담당하고 있다. 여기서는 레벨에 있는 컴포넌트 배열만 삭제
			m_actorHitComps.erase(m_actorHitComps.begin() + i);
			cycles -= 1;
		}
		else
		{
			i++;
		}
	}

	// 액터 제거
	cycles = static_cast<int>(m_actors.size());
	for (int i = 0; i < cycles;)
	{
		if (m_actors[i]->DestroyRequested() == true)
		{
			delete m_actors[i];
			m_actors.erase(m_actors.begin() + i);
			cycles -= 1;
		}
		else
		{
			i++;
		}
	}
}


