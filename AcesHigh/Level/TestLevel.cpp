#include "Level/TestLevel.h"
#include "Actor/Object.h"
#include "Actor/Player.h"
#include "Actor/Bullet.h"

C_TESTLEVEL::C_TESTLEVEL()
{
	C_VECTOR2 position1{};

	position1.m_x = 0;
	position1.m_y = 50;

	C_PLAYER* test{};
	test = new C_PLAYER("player_plane1.txt", position1, true, E_COLOR::Green, 11, 100, 10, 0.5f);
	AddNewActor(test);


}

C_TESTLEVEL::~C_TESTLEVEL()
{

}