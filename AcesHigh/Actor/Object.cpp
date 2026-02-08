#include "Core/Input.h"
#include "Actor/Object.h"
#include "Component/HitComponent.h"

C_OBJECT::C_OBJECT(const char* fileName, const C_VECTOR2& position)
	:C_ACTOR(fileName, position, true)
{
	m_xPosition = static_cast<float>(m_position.m_x);
	m_yPosition = static_cast<float>(m_position.m_y);
}

C_OBJECT::~C_OBJECT()
{
	OnDestroy();
}

void C_OBJECT::BeginPlay()
{
	m_moveVerticalSpeed = 0;
	m_moveHorizontalSpeed = 0;
	m_hitComponent->SetCollitionType(E_COLLISIONTYPE::None);
}

void C_OBJECT::Tick(float deltaTime)
{
	C_ACTOR::Tick(deltaTime);

	m_xPosition += m_moveVerticalSpeed * deltaTime;
	m_yPosition += m_moveHorizontalSpeed * deltaTime;

	m_position.m_x = static_cast<int>(m_xPosition);
	m_position.m_y = static_cast<int>(m_yPosition);

	
	if (m_position.m_y + m_height < 0)
	{
		Destroy();
	}
}

void C_OBJECT::OnHit(const C_ACTOR* otherActor)
{
	
}

void C_OBJECT::OnDestroy()
{
	C_ACTOR::OnDestroy();

}


