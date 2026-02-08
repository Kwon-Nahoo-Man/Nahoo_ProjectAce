#include "Core/Input.h"
#include "Actor/Object.h"
#include "Actor/Plane.h"
#include "Level/Level.h"


C_PLANE::C_PLANE(const char* fileName, C_VECTOR2& position)
	:C_ACTOR(fileName, position, true)
{
	m_moveHorizontalSpeed = 100;
	m_moveVerticalSpeed = static_cast<int>(m_moveHorizontalSpeed * 0.8);
	m_xPosition = static_cast<float>(m_position.m_x);
	m_yPosition = static_cast<float>(m_position.m_y);

}

C_PLANE::~C_PLANE()
{
	OnDestroy();
}

void C_PLANE::BeginPlay()
{
	C_ACTOR::BeginPlay();
	m_color = E_COLOR::White;

}

void C_PLANE::Tick(float deltaTime)
{
	C_ACTOR::Tick(deltaTime);

	if(Nahoo::C_INPUT::GetInstance().GetKeyDown(VK_SPACE))
	{
		Fire();
	}
	if (Nahoo::C_INPUT::GetInstance().GetKey(VK_LEFT))
	{
		m_xPosition -= m_moveHorizontalSpeed * deltaTime;
	}
	if (Nahoo::C_INPUT::GetInstance().GetKey(VK_RIGHT))
	{
		m_xPosition += m_moveHorizontalSpeed * deltaTime;
	}
	if (Nahoo::C_INPUT::GetInstance().GetKey(VK_UP))
	{
		m_yPosition -= m_moveVerticalSpeed * deltaTime;

	}
	if (Nahoo::C_INPUT::GetInstance().GetKey(VK_DOWN))
	{
		m_yPosition += m_moveVerticalSpeed * deltaTime;
	}

	if (Nahoo::C_INPUT::GetInstance().GetKeyDown('Q'))
	{
		Destroy();
	}

	
	C_VECTOR2 newPosition = GetPosition();
	newPosition.m_x = static_cast<int>(m_xPosition);
	newPosition.m_y = static_cast<int>(m_yPosition);
	SetPosition(newPosition);

}

void C_PLANE::OnHit(const C_ACTOR* otherActor)
{
	// 여기서 hitcomponent의 collisionType 가지고 hit별 행동
	Destroy();
}

void C_PLANE::OnDestroy()
{
	C_ACTOR::OnDestroy();
}

void C_PLANE::Fire()
{
	/*Nahoo::C_VECTOR2 firePosition{};
	firePosition.m_x = m_position.m_x + m_width / 2 - 1;
	firePosition.m_y = m_position.m_y - 5;

	m_owner->AddNewActor(new C_OBJECT("bullet.txt",firePosition));*/
}
