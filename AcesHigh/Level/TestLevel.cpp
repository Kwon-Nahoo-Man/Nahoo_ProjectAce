#include "Level/TestLevel.h"
#include "Actor/TestActor.h"

C_TESTLEVEL::C_TESTLEVEL()
{
	AddNewActor(new C_TESTACTOR());
}

C_TESTLEVEL::~C_TESTLEVEL()
{

}