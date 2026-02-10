#include "Bullet.h"
#include "Component/HitComponent.h"
#include "Engine/Engine.h"

C_BULLET::C_BULLET(const char* fileName, C_VECTOR2& position, E_COLOR color, 
	int horizontalSpeed, int verticalSpeed, E_COLLISIONTYPE collisionType, int damage, bool isBounce)
	: C_OBJECT(fileName, position, true, color, 20, 0)
{
	m_moveHorizontalSpeed = horizontalSpeed;
	m_moveVerticalSpeed = verticalSpeed;

	if (m_hitComponent != nullptr)
	{
		m_hitComponent->SetCollisionType(E_COLLISIONTYPE::Bullet | collisionType);
	}

	m_damage = damage;
	
	SetBounce(isBounce, 10.0f);

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

	// 화면 밖 파괴처리 (bounce 함수 때문에 좀 널널하게 파괴처리 함)
	if (m_position.m_x + m_width < -5 || m_position.m_x > Nahoo::C_ENGINE::GetInstance().GetWidth() + 5 ||
		m_position.m_y + m_height < -5 || m_position.m_y > Nahoo::C_ENGINE::GetInstance().GetHeight() + 5)
	{
		Destroy();
	}
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
			// Todo: 총알 소멸 이펙트
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
