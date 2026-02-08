#pragma once

#include "Actor/Actor.h"

using namespace Nahoo;

class C_OBJECT : public C_ACTOR
{
	RTTI_DECLARATIONS(C_OBJECT,C_ACTOR)

public:

	C_OBJECT(const char* fileName, const C_VECTOR2& position);
	~C_OBJECT();
	
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnHit(const C_ACTOR* otherActor) override;
	virtual void OnDestroy() override;

private:
	
	// 음수를 하면 왼쪽, 양수를 하면 오른쪽
	int m_moveVerticalSpeed{};
	// 음수를 하면 상단, 양수를 하면 하단
	int m_moveHorizontalSpeed{};
	float m_xPosition{};
	float m_yPosition{};

};

