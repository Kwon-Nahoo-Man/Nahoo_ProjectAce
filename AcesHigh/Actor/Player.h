#pragma once

#include "Actor/Plane.h"

using namespace Nahoo;

class C_PLAYER : public C_PLANE
{
public:
	
	C_PLAYER(const char* fileName, C_VECTOR2& position, bool collision, E_COLOR color,
		int sortingOrder, int moveSpeed, int health, E_COLLISIONTYPE collisionType, float fireRate = 0.2f);

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnHit(const C_ACTOR* otherActor) override;

	virtual void Fire() override;
	virtual void OnDamaged(int damage) override;

	void PowerUp();
	void PowerDown();

protected:
	// Power Up 시 마다 총알 이미지 달라짐
	const char* m_bulletFileName{};
	int m_currentPower{};
	C_VECTOR2 m_firePosition{};

	// Todo: 특수기술(아군 호출) 용 변수
};
