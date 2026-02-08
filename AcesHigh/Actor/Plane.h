#pragma once

#include "Actor/Actor.h"

using namespace Nahoo;

class C_PLANE : public C_ACTOR
{
	RTTI_DECLARATIONS(C_PLANE, C_ACTOR)

public:

	C_PLANE(const char* fileName, C_VECTOR2& position);
	~C_PLANE();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnHit(const C_ACTOR* otherActor) override;

	virtual void OnDestroy() override;

	void Fire();

protected:
	// 음수를 하면 왼쪽, 양수를 하면 오른쪽
	int m_moveVerticalSpeed{};
	// 음수를 하면 상단, 양수를 하면 하단
	int m_moveHorizontalSpeed{};
	int m_health{};
	float m_xPosition{};
	float m_yPosition{};
};

