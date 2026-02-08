#include "PlaneAlly.h"
#include "Component/HitComponent.h"


C_PLANEALLY::C_PLANEALLY(const char* fileName, C_VECTOR2& position)
	: C_PLANE(fileName, position)
{
	
}

void C_PLANEALLY::BeginPlay()
{
	C_PLANE::BeginPlay();

	m_moveHorizontalSpeed = 72;
	m_moveVerticalSpeed = static_cast<int>(m_moveHorizontalSpeed * 0.8);
	m_xPosition = static_cast<float>(m_position.m_x);
	m_yPosition = static_cast<float>(m_position.m_y);

	m_hitComponent->SetCollitionType(E_COLLISIONTYPE::Ally);

	m_health = 5;

	m_color = E_COLOR::IntenceBlue;
	
}

void C_PLANEALLY::Tick(float deltaTime)
{
	
	m_xPosition += m_moveVerticalSpeed * deltaTime;
	m_yPosition += m_moveHorizontalSpeed * deltaTime;

	m_position.m_x = static_cast<int>(m_xPosition);
	m_position.m_y = static_cast<int>(m_yPosition);
}

void C_PLANEALLY::OnHit(const C_ACTOR* otherActor)
{

}
