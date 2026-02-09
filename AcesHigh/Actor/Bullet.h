#pragma once

#include "Object.h"

class C_BULLET : public C_OBJECT
{
public:
	C_BULLET(const char* fileName, C_VECTOR2& position, E_COLOR color, 
		int horizontalSpeed, int verticalSpeed, E_COLLISIONTYPE collisionType, int damage = 1, bool isBounce = false);
	~C_BULLET();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnHit(const C_ACTOR* otherActor) override;
	virtual void OnDestroy() override;

	const int GetDamage() const;

protected:
	int m_damage{};


};
