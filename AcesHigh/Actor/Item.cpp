#include "Item.h"
#include "Component/HitComponent.h"
#include "Engine/Engine.h"


C_ITEM::C_ITEM(const char* fileName, C_VECTOR2& position, E_COLOR color, int sortingOrder,
	int horizontalSpeed, int verticalSpeed, E_ITEMTYPE itemType, bool isBounce)
	: C_SKYOBJECT(fileName,position,true,color, sortingOrder,0)
{
	m_moveHorizontalSpeed = horizontalSpeed;
	m_moveVerticalSpeed = verticalSpeed;

	if (m_hitComponent != nullptr)
	{
		m_hitComponent->SetCollisionType(E_COLLISIONTYPE::Item);
	}
	m_itemType = itemType;
	SetBounce(isBounce, 10.0f);
}

C_ITEM::~C_ITEM()
{

}

void C_ITEM::BeginPlay()
{
	C_SKYOBJECT::BeginPlay();


}

void C_ITEM::Tick(float deltaTime)
{
	C_SKYOBJECT::Tick(deltaTime);

	// 화면 밖 파괴처리 (bounce 함수 때문에 좀 널널하게 파괴처리 함)
	if (m_position.m_x + m_width < -5 || m_position.m_x > Nahoo::C_ENGINE::GetInstance().GetWidth() + 5 ||
		m_position.m_y + m_height < -5 || m_position.m_y > Nahoo::C_ENGINE::GetInstance().GetHeight() + 5)
	{
		Destroy();
	}
}

void C_ITEM::OnHit(const C_ACTOR* otherActor)
{
	E_COLLISIONTYPE otherActorCollisionType{};
	otherActorCollisionType = otherActor->GetHitComponent()->GetCollisionType();
	E_COLLISIONTYPE thisActorCollisionType{};
	thisActorCollisionType = m_hitComponent->GetCollisionType();

	if ((otherActorCollisionType & E_COLLISIONTYPE::Player) == E_COLLISIONTYPE::Player)
	{
		// 아이템 획득 이펙트
		// m_owner->GetEffectManager()->SpawnEffect(2, m_position, 0.3f, E_COLOR::BackgroundRed | E_COLOR::BackgroundGreen, 40);

		Destroy();
	}

}

const E_ITEMTYPE C_ITEM::GetItemType() const
{
	return m_itemType;
}


