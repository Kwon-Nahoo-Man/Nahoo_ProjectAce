#pragma once

#include "Actor/Actor.h"

using namespace Nahoo;

class C_TESTACTOR : public C_ACTOR
{
	RTTI_DECLARATIONS(C_TESTACTOR,C_ACTOR)

public:

	C_TESTACTOR();
	virtual void Tick(float deltaTime) override;

private:

};

