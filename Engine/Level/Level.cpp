
#include "Actor/Actor.h"
#include "Level.h"

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
	}
	m_addRequestedActors.clear();
}

void Nahoo::C_LEVEL::ProcessDeleteActor()
{
	// Todo: 만약 actor에 오너쉽 생기면, for루프 deleteRequestedActor 배열로 변경
	// 근데 deleteRequestedActor 배열 따로 관리하면, m_actors에서 deleteRequestedActor에서 지워야 할 actor는 어떻게 고르지?
	int cycles{};
	cycles = static_cast<int>(m_actors.size());
	for (int i = 0; i < cycles;)
	{
		if (m_actors[i]->DestroyRequested())
		{
			delete m_actors[i];
			m_actors.erase(m_actors.begin() + i);
		}
		else
		{
			i++;
		}
	}
}


