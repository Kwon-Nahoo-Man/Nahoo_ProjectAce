#include "Core/Input.h"
#include "Actor/TestActor.h"

C_TESTACTOR::C_TESTACTOR()
	:C_ACTOR("test.txt",C_VECTOR2(0,0),E_COLOR::White)
{

}

void C_TESTACTOR::Tick(float deltaTime)
{
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
