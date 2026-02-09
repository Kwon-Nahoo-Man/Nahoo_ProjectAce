#include "Core/Input.h"
#include "Level/Level.h"
#include "Player.h"
#include "Component/HitComponent.h"
#include "Actor/Object.h"
#include "Util/Timer.h"


C_PLAYER::C_PLAYER(const char* fileName, C_VECTOR2& position, bool collision, E_COLOR color,
					int sortingOrder, int moveSpeed, int health, E_COLLISIONTYPE collisionType, float fireRate)
	: C_PLANE(fileName, position,collision,color,moveSpeed,health,collisionType)
{
	m_fireRate = fireRate;
	m_hitComponent->SetCollisionType(E_COLLISIONTYPE::Player);
	m_sortingOrder = 11;
}

void C_PLAYER::BeginPlay()
{
	C_PLANE::BeginPlay();

	// 사격위치 값 초기설정
	m_firePosition.m_x = m_position.m_x + m_width / 2 - 1;
	m_firePosition.m_y = m_position.m_y - 5;

}

void C_PLAYER::Tick(float deltaTime)
{
	C_ACTOR::Tick(deltaTime);
	

	// PlayerMovement
	{
		if (Nahoo::C_INPUT::GetInstance().GetKeyDown(VK_SPACE))
		{
			Fire();
		}

		if (Nahoo::C_INPUT::GetInstance().GetKey(VK_LEFT))
		{
			m_xPosition -= m_moveHorizontalSpeed * deltaTime;
		}
		if (Nahoo::C_INPUT::GetInstance().GetKey(VK_RIGHT))
		{
			m_xPosition += m_moveHorizontalSpeed * deltaTime;
		}
		if (Nahoo::C_INPUT::GetInstance().GetKey(VK_UP))
		{
			m_yPosition -= m_moveVerticalSpeed * deltaTime;

		}
		if (Nahoo::C_INPUT::GetInstance().GetKey(VK_DOWN))
		{
			m_yPosition += m_moveVerticalSpeed * deltaTime;
		}

		m_position.m_x = static_cast<int>(m_xPosition);
		m_position.m_y = static_cast<int>(m_yPosition);
	}


	if (Nahoo::C_INPUT::GetInstance().GetKeyDown('Q'))
	{
		Destroy();
	}

}

void C_PLAYER::OnHit(const C_ACTOR* otherActor)
{
	//총알 히트
	//C_PLAIN과 같게
	C_PLANE::OnHit(otherActor);

	//아이템 획득
	E_COLLISIONTYPE otherActorCollisionType{};
	otherActorCollisionType = otherActor->GetHitComponent()->GetCollisionType();

	if ((otherActorCollisionType & E_COLLISIONTYPE::Item) == E_COLLISIONTYPE::Item)
	{
		// Todo: item 효과

	}

}

void C_PLAYER::Fire()
{
	Nahoo::C_VECTOR2 firePosition{};
	

	//m_owner->AddNewActor(new C_OBJECT("bullet.txt", firePosition));
}

void C_PLAYER::OnDamaged(int damage)
{
	C_PLANE::OnDamaged(damage);

	PowerDown();
}

void C_PLAYER::PowerUp()
{
	if (m_currentPower < 2)
	{
		m_currentPower++;
	}

	// Todo: 총알 변경, m_firePosition도 바꿔야해

	//char buffer[30]{};
	//sprintf_s(buffer, 30, "PlayerBullet%d", m_currentPower);
	//m_bulletFileName = buffer;
}

void C_PLAYER::PowerDown()
{
	if (m_currentPower > 0)
	{
		m_currentPower--;
	}

	// Todo: 총알 변경
}
