#include "Bullet.h"
#include "Component/HitComponent.h"

C_BULLET::C_BULLET(const char* fileName, C_VECTOR2& position, E_COLOR color, 
	int horizontalSpeed, int verticalSpeed, E_COLLISIONTYPE collisionType, int damage, bool isBounce)
	: C_OBJECT(fileName, position, true, color, 20, 0, collisionType)
{
	m_moveHorizontalSpeed = horizontalSpeed;
	m_moveVerticalSpeed = verticalSpeed;

	if (m_hitComponent != nullptr)
	{
		m_hitComponent->SetCollision(true);
		m_hitComponent->SetCollisionType(E_COLLISIONTYPE::Bullet | collisionType);
	}

	m_damage = damage;
	m_isBounce = isBounce;

}

C_BULLET::~C_BULLET()
{
	OnDestroy();
}

void C_BULLET::BeginPlay()
{
	C_OBJECT::BeginPlay();
}

void C_BULLET::Tick(float deltaTime)
{
	C_OBJECT::Tick(deltaTime);

}

void C_BULLET::OnHit(const C_ACTOR* otherActor)
 {
 	E_COLLISIONTYPE otherActorCollisionType{};
	otherActorCollisionType = otherActor->GetHitComponent()->GetCollisionType();
	E_COLLISIONTYPE thisActorCollisionType{};
	thisActorCollisionType = m_hitComponent->GetCollisionType();

	if ((otherActorCollisionType & E_COLLISIONTYPE::Plane) == E_COLLISIONTYPE::Plane)
	{
		if ((thisActorCollisionType & otherActorCollisionType) == E_COLLISIONTYPE::None)
		{
			// Todo: √—æÀ º“∏Í ¿Ã∆Â∆Æ
			Destroy();
		}
	}

}

void C_BULLET::OnDestroy()
{
	C_OBJECT::OnDestroy();
}

const int C_BULLET::GetDamage() const
{
	return m_damage;
}
