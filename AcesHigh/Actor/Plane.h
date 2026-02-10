#pragma once

#include "Actor/Actor.h"
#include "Enumeration/MoveDirection.h"
#include "Util/Timer.h"

using namespace Nahoo;

class C_PLANE : public C_ACTOR
{
	RTTI_DECLARATIONS(C_PLANE, C_ACTOR)

public:
	struct S_BULLETSPEC
	{
		const char* fileName = nullptr;
		E_COLOR color = E_COLOR::White;
		C_VECTOR2 moveSpeed = C_VECTOR2::Zero;
		int damage = 1;
		bool isBounce = false;
		E_MOVEDIRECTION moveDirection = E_MOVEDIRECTION::None;
	};


	C_PLANE(const char* fileName, C_VECTOR2& position, bool collision, E_COLOR color,
		 int moveSpeed, int health, E_COLLISIONTYPE collisionType, float fireRate = 1.0f);
	~C_PLANE();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnHit(const C_ACTOR* otherActor) override;

	virtual void OnDestroy() override;

	virtual void Fire();
	virtual void OnDamaged(int damage);

	// Plane 생성 시 반드시 다음에 이동 방향 지정해야함 (지정 안할 시 멈춤)
	void GiveMoveOrder(const E_MOVEDIRECTION& moveDirection, int moveSpeed = -1);

	// Plane 생성 시 반드시 다음에 총알 스펙 지정해야함
	void SetBulletSpec(const char* fileName, E_COLOR color, int horizontalSpeed, int verticalSpeed,
		int damage, bool isBounce, E_MOVEDIRECTION moveDirection);

	// 랜덤으로 아이템을 드랍할 확률 (0 ~ 10)
	void RandomItemDrop(int percentage = 3);

	UTIL::C_TIMER m_timer{ 1.0f };


protected:
	void ApplyMovement(float deltaTime);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void MoveStop();

protected:

	// 음수를 하면 왼쪽, 양수를 하면 오른쪽
	int m_moveVerticalSpeed{};
	// 음수를 하면 상단, 양수를 하면 하단
	int m_moveHorizontalSpeed{};
	int m_health{};
	float m_xPosition{};
	float m_yPosition{};
	float m_fireRate{};

	E_MOVEDIRECTION m_currentMoveDirection = E_MOVEDIRECTION::None;
	S_BULLETSPEC m_bulletSpec;

};

