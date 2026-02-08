#include "Level/TestLevel.h"
#include "Actor/Object.h"
#include "Actor/Plane.h"

C_TESTLEVEL::C_TESTLEVEL()
{
	C_VECTOR2 position1{};

	position1.m_x = 0;
	position1.m_y = 0;

	AddNewActor(new C_PLANE("player_plane1.txt", position1));
}

C_TESTLEVEL::~C_TESTLEVEL()
{

}