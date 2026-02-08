#include "Core/Input.h"
#include "Actor/TestActor.h"
#include "Actor/TestActor2.h"
#include "Level/Level.h"

// test
#include "Engine/Engine.h"

C_TESTACTOR2::C_TESTACTOR2(const char* fileName, C_VECTOR2& position)
	:C_ACTOR(fileName, position, E_COLOR::White, true)
{
	m_moveHorizontalSpeed = 120;
	m_moveVerticalSpeed = static_cast<int>(m_moveHorizontalSpeed * 1.2);
	m_xPosition = static_cast<float>(m_position.m_x);
	m_yPosition = static_cast<float>(m_position.m_y);

}

void C_TESTACTOR2::Tick(float deltaTime)
{
	C_ACTOR::Tick(deltaTime);

	if(Nahoo::C_INPUT::GetInstance().GetKeyDown(VK_SPACE))
	{
		Fire();
	}
	if (Nahoo::C_INPUT::GetInstance().GetKey(VK_LEFT))
	{
		m_xPosition -= m_moveVerticalSpeed * deltaTime;
	}
	if (Nahoo::C_INPUT::GetInstance().GetKey(VK_RIGHT))
	{
		m_xPosition += m_moveVerticalSpeed * deltaTime;
	}
	if (Nahoo::C_INPUT::GetInstance().GetKey(VK_UP))
	{
		m_yPosition -= m_moveHorizontalSpeed * deltaTime;

	}
	if (Nahoo::C_INPUT::GetInstance().GetKey(VK_DOWN))
	{
		m_yPosition += m_moveHorizontalSpeed * deltaTime;
	}

	if (Nahoo::C_INPUT::GetInstance().GetKeyDown('Q'))
	{
		Destroy();
	}

	// Test 
	if (Nahoo::C_INPUT::GetInstance().GetKeyDown(VK_ESCAPE))
	{
		C_ENGINE::GetInstance().QuitEngine();
	}

	
	C_VECTOR2 newPosition = GetPosition();
	newPosition.m_x = static_cast<int>(m_xPosition);
	newPosition.m_y = static_cast<int>(m_yPosition);
	SetPosition(newPosition);

}

void C_TESTACTOR2::OnHit(const C_ACTOR* otherActor)
{
	Destroy();
}

void C_TESTACTOR2::Fire()
{
	Nahoo::C_VECTOR2 firePosition{};
	firePosition.m_x = m_position.m_x + m_width / 2 - 1;
	firePosition.m_y = m_position.m_y - 5;

	m_owner->AddNewActor(new C_TESTACTOR("bullet.txt",firePosition));
}
