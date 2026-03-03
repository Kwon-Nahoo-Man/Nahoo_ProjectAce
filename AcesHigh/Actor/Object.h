#pragma once

#include "Actor/Actor.h"
#include "Enumeration/MoveDirection.h"
#include "Util/Timer.h"

using namespace Nahoo;

class C_OBJECT : public C_ACTOR
{
	RTTI_DECLARATIONS(C_OBJECT,C_ACTOR)

public:

	C_OBJECT(const char* fileName, C_VECTOR2& position, bool collision, E_COLOR color,
		int sortingOrder, int moveSpeed);
	~C_OBJECT();
	
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnHit(const C_ACTOR* otherActor) override;

	// moveSpeed에 -1을 넣으면 기존 사용하던 속도 사용(Default = -1)
	void GiveMoveOrder(const E_MOVEDIRECTION& moveDirection, int moveSpeed = -1);
	void SetBounce(bool decision, float minimumTime);

protected:

	void Bounce(bool isBounce);
	void ApplyMovement(float deltaTime);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void MoveStop();

protected:

	bool m_isBounce{ false };
	// 음수를 하면 왼쪽, 양수를 하면 오른쪽
	int m_moveVerticalSpeed{};
	// 음수를 하면 상단, 양수를 하면 하단
	int m_moveHorizontalSpeed{};
	float m_xPosition{};
	float m_yPosition{};
	E_MOVEDIRECTION m_currentMoveDirection = E_MOVEDIRECTION::None;
	UTIL::C_TIMER m_bounceTimer{ 7.0f };

};

