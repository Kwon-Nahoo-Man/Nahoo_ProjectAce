#include <Windows.h>
#include <iostream>

#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Component/HitComponent.h"
#include "Component/RenderComponent.h"


Nahoo::C_ACTOR::C_ACTOR()
{

}

Nahoo::C_ACTOR::C_ACTOR(const char* fileName, const C_VECTOR2& position, bool collision)
	: m_position(position.m_x, position.m_y)
{
	m_filePath = std::string("../Assets/") + fileName;

	MakeComponent(collision);
}

Nahoo::C_ACTOR::~C_ACTOR()
{
	if (m_hitComponent != nullptr)
	{
		delete m_hitComponent;
		m_hitComponent = nullptr;
	}

	if (m_renderComponent != nullptr)
	{
		delete m_renderComponent;
		m_renderComponent = nullptr;
	}
}

void Nahoo::C_ACTOR::BeginPlay()
{
	m_hasBegunPlay = true;

	if (m_hitComponent != nullptr && m_hitComponent->HasBegaunPlay() == false)
	{
		m_hitComponent->BeginPlay();
		// set collision type
		m_hitComponent->SetCollisionType(m_collisionType);
	}
	if (m_renderComponent != nullptr)
	{
		m_renderComponent->BeginPlay();
	}
}

void Nahoo::C_ACTOR::Tick(float deltaTime)
{

	if (m_hitComponent != nullptr)
	{
		m_hitComponent->Tick(deltaTime);
	}
	

}

void Nahoo::C_ACTOR::Draw(bool debugHitCompDraw)
{
	if (m_renderComponent != nullptr)
	{
		m_renderComponent->Draw();
	}

	if (debugHitCompDraw == true && m_hitComponent != nullptr)
	{
		m_hitComponent->DebugDraw();
	}
	
}

void Nahoo::C_ACTOR::OnHit(const C_ACTOR* otherActor)
{
	// 액터가 충돌판정 받았을 때 로직, otherActorType는 조건식으로 사용
	// ex) Is(otherActorType) 

		
}

void Nahoo::C_ACTOR::Destroy()
{
	m_destroyRequested = true;
	SetActive(false);

	if (m_hitComponent != nullptr)
	{
		m_hitComponent->Destroy();
	}
	if (m_renderComponent != nullptr)
	{
		m_renderComponent->Destroy();
	}
	
}

void Nahoo::C_ACTOR::OnDestroy()
{
	
}

void Nahoo::C_ACTOR::SetPosition(const C_VECTOR2& newPosition)
{
	if (m_position != newPosition)
	{
		m_position = newPosition;
	}
}

void Nahoo::C_ACTOR::SetActive(bool isActive)
{
	m_isActive = isActive;
	if (m_hitComponent != nullptr)
	{
		m_hitComponent->SetCollision(isActive);
	}
}

void Nahoo::C_ACTOR::SetCollision(bool activeCollision)
{
	if (m_hitComponent != nullptr)
	{
		m_hitComponent->SetCollision(activeCollision);
	}
}

void Nahoo::C_ACTOR::SetActorWidthHeight(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Nahoo::C_ACTOR::MakeComponent(bool collisionFlag)
{
	if (collisionFlag == true && m_hitComponent == nullptr)
	{
		m_hitComponent = new COMP_HITCOMPONENT();
		m_hitComponent->SetOwner(this);
	}

	if (m_renderComponent == nullptr)
	{
		m_renderComponent = new COMP_RENDER();
		m_renderComponent->SetOwner(this);
	}

}

