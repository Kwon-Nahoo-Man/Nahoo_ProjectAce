#pragma once

#include "Actor/Actor.h"

using namespace Nahoo;

class C_TESTACTOR2 : public C_ACTOR
{
	RTTI_DECLARATIONS(C_TESTACTOR2, C_ACTOR)

public:

	C_TESTACTOR2(const char* fileName, C_VECTOR2& position);
	virtual void Tick(float deltaTime) override;
	virtual void OnHit(const C_ACTOR* otherActor) override;

	void Fire();

private:
	int m_moveVerticalSpeed{};
	int m_moveHorizontalSpeed{};
	float m_xPosition{};
	float m_yPosition{};
};

