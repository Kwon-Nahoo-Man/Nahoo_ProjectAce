#include "Core/Input.h"
#include "Actor/TestActor.h"

C_TESTACTOR::C_TESTACTOR(const char* fileName, C_VECTOR2& position)
	:C_ACTOR(fileName, position, E_COLOR::White, true)
{

}

void C_TESTACTOR::Tick(float deltaTime)
{
	C_ACTOR::Tick(deltaTime);

	if (Nahoo::C_INPUT::GetInstance().GetKey(VK_LEFT))
	{
		m_position.m_x -= 1;
	}
	if (Nahoo::C_INPUT::GetInstance().GetKey(VK_RIGHT))
	{
		m_position.m_x += 1;
	}
	if (Nahoo::C_INPUT::GetInstance().GetKey(VK_UP))
	{
		m_position.m_y -= 1;
	}
	if (Nahoo::C_INPUT::GetInstance().GetKey(VK_DOWN))
	{
		m_position.m_y += 1;
	}
}

void C_TESTACTOR::OnHit(size_t otherActorType)
{
	m_position.m_x -= 10;
	m_position.m_y -= 10;

}


