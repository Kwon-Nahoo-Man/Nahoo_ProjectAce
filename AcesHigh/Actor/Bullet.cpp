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

	//if (m_moveHorizontalSpeed < 0)
	//{
	//	GiveMoveOrder(E_MOVEDIRECTION::Left);
	//}
	//else if (m_moveHorizontalSpeed > 0)
	//{
	//	GiveMoveOrder(E_MOVEDIRECTION::Right);
	//}

	//if (m_moveVerticalSpeed < 0)
	//{
	//	GiveMoveOrder(E_MOVEDIRECTION::Left);
	//}


}

C_BULLET::~C_BULLET()
{
	OnDestroy();
}

void C_BULLET::OnHit(const C_ACTOR* otherActor)
{
	E_COLLISIONTYPE otherActorCollisionType{};
	otherActorCollisionType = otherActor->GetHitComponent()->GetCollisionType();

	if ((otherActorCollisionType & E_COLLISIONTYPE::Plane) == E_COLLISIONTYPE::Plane)
	{
		if ((otherActorCollisionType & m_hitComponent->GetCollisionType()) != m_hitComponent->GetCollisionType())
		{
			// Todo: √—æÀ º“∏Í ¿Ã∆Â∆Æ
			Destroy();
		}
	}

}

const int C_BULLET::GetDamage() const
{
	return m_damage;
}
