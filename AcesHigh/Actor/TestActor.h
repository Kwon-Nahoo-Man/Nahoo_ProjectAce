#pragma once

#include "Actor/Actor.h"

using namespace Nahoo;

class C_TESTACTOR : public C_ACTOR
{
	RTTI_DECLARATIONS(C_TESTACTOR,C_ACTOR)

public:

	C_TESTACTOR(const char* fileName, C_VECTOR2& position);
	virtual void Tick(float deltaTime) override;

	virtual void OnHit(const C_ACTOR* otherActor) override;

private:
	int m_moveSpeed{};
	float m_xPosition{};
	float m_yPosition{};

};

