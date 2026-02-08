#include "Core/Input.h"
#include "Actor/TestActor.h"

C_TESTACTOR::C_TESTACTOR(const char* fileName, C_VECTOR2& position)
	:C_ACTOR(fileName, position, E_COLOR::White, true)
{
	m_moveSpeed = 10;
	m_xPosition = static_cast<float>(m_position.m_x);
	m_yPosition = static_cast<float>(m_position.m_y);
}

void C_TESTACTOR::Tick(float deltaTime)
{
	C_ACTOR::Tick(deltaTime);

	m_yPosition -= m_moveSpeed * deltaTime;
	m_position.m_y = static_cast<int>(m_yPosition);

	
	if (m_position.m_y + m_height < 0)
	{
		Destroy();
	}
}

void C_TESTACTOR::OnHit(const C_ACTOR* otherActor)
{
	
}


