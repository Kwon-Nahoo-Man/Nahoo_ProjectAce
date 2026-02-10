#include "Level/TestLevel.h"
#include "Actor/Object.h"
#include "Actor/Player.h"
#include "Actor/Bullet.h"
#include "Actor/Item.h"
#include "Actor/Spawner.h"

C_TESTLEVEL::C_TESTLEVEL()
{
	AddNewActor(new C_SPAWNER());
	
	C_VECTOR2 position1{};

	position1.m_x = 0;
	position1.m_y = 50;

	C_PLAYER* test{};
	test = new C_PLAYER("enemy_small.txt", position1, true, E_COLOR::Green | E_COLOR::ForegroundIntensity, 11, 100, 10, 0.3f);
	AddNewActor(test);

}

C_TESTLEVEL::~C_TESTLEVEL()
{

}