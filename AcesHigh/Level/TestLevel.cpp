#include "Level/TestLevel.h"
#include "Actor/TestActor.h"
#include "Actor/TestActor2.h"

C_TESTLEVEL::C_TESTLEVEL()
{

	C_VECTOR2 position1{};
	position1.m_x = 10;
	position1.m_y = 5;
	AddNewActor(new C_TESTACTOR("test.txt",position1));

	position1.m_x = 30;
	position1.m_y = 10;

	AddNewActor(new C_TESTACTOR2("test.txt", position1));
}

C_TESTLEVEL::~C_TESTLEVEL()
{

}