#include "Level/TestLevel.h"
#include "Actor/TestActor.h"
#include "Actor/TestActor2.h"

C_TESTLEVEL::C_TESTLEVEL()
{
	Sleep(5000);
	C_VECTOR2 position1{};

	position1.m_x = 0;
	position1.m_y = 0;

	AddNewActor(new C_TESTACTOR2("player_plane1.txt", position1));
}

C_TESTLEVEL::~C_TESTLEVEL()
{

}