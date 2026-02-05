#include <iostream>
#include "Engine/Engine.h"
#include "Level/TestLevel.h"


int main()
{
	Nahoo::C_ENGINE engine{};
	engine.SetNewLevel(new C_TESTLEVEL());
	engine.Run();
	
}