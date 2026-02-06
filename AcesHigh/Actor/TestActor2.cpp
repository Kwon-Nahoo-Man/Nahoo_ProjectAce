#include "Core/Input.h"
#include "Actor/TestActor2.h"

C_TESTACTOR2::C_TESTACTOR2(const char* fileName, C_VECTOR2& position)
	:C_ACTOR(fileName, position, E_COLOR::White, true)
{

}

void C_TESTACTOR2::Tick(float deltaTime)
{
	C_ACTOR::Tick(deltaTime);

}

void C_TESTACTOR2::OnHit(size_t otherActorType)
{
	Destroy();
}
