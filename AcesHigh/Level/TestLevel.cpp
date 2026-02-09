#include "Level/TestLevel.h"
#include "Actor/Object.h"
#include "Actor/Player.h"

C_TESTLEVEL::C_TESTLEVEL()
{
	C_VECTOR2 position1{};

	position1.m_x = 0;
	position1.m_y = 10;

	//AddNewActor(new C_PLANE("player_plane1.txt", position1));
	C_PLANE* test{};
	test = new C_PLANE("player_plane1.txt", position1, true, E_COLOR::IntenceGreen, 20, 10, E_COLLISIONTYPE::Ally, 0.5f);
	AddNewActor(test);
	test->GiveMoveOrder(E_MOVEDIRECTION::None);
	position1.m_x = position1.m_x + (test->GetActorWidth() / 2);
	position1.m_y = position1.m_y - 10;
	test->SetBulletSpec("bullet.txt", position1, E_COLOR::White, -10, 1, 1, true);
	
	
	
	position1.m_x = 50;
	position1.m_y = 0;
	test = new C_PLANE("player_plane1.txt", position1, true, E_COLOR::IntenceRed, 10, 10, E_COLLISIONTYPE::Ally);
	AddNewActor(test);
	test->GiveMoveOrder(E_MOVEDIRECTION::None);
	position1.m_x = position1.m_x + (test->GetActorWidth() / 2);
	position1.m_y = position1.m_y - 2;
	test->SetBulletSpec("bullet.txt", position1, E_COLOR::Blue, -10, 1, 1, true);


	test = nullptr;

	C_OBJECT* test2{};

	position1.m_x = 25;
	position1.m_y = 50;
	test2 = new C_OBJECT("test.txt", position1, true, E_COLOR::IntenceBlue, 10, 80, E_COLLISIONTYPE::Item);
	AddNewActor(test2);
	test2->GiveMoveOrder( E_MOVEDIRECTION::Up|E_MOVEDIRECTION::Left);


	
}

C_TESTLEVEL::~C_TESTLEVEL()
{

}