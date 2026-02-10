#include "Core/Input.h"
#include "Actor/Object.h"
#include "Actor/Plane.h"
#include "Level/Level.h"
#include "Component/HitComponent.h"
#include "Engine/Engine.h"
#include "Actor/Bullet.h"
#include "Util/Util.h"
#include "Actor/Item.h"


C_PLANE::C_PLANE(const char* fileName, C_VECTOR2& position, bool collision, E_COLOR color,
	 int moveSpeed, int health, E_COLLISIONTYPE collisionType, float fireRate)
	:C_ACTOR(fileName, position, collision)
{
	m_color = color;
	m_sortingOrder = 10;
	m_moveHorizontalSpeed = moveSpeed;
	m_moveVerticalSpeed = static_cast<int>(m_moveHorizontalSpeed * 0.8);
	m_health = health;

	if (m_hitComponent != nullptr)
	{
		m_hitComponent->SetCollision(collision);
		m_hitComponent->SetCollisionType(E_COLLISIONTYPE::Plane | collisionType);
	}

	m_fireRate = fireRate;

	m_xPosition = static_cast<float>(m_position.m_x);
	m_yPosition = static_cast<float>(m_position.m_y);

	m_timer.SetTargetTime(m_fireRate);

}

C_PLANE::~C_PLANE()
{
	OnDestroy();
}

void C_PLANE::BeginPlay()
{
	C_ACTOR::BeginPlay();

}

void C_PLANE::Tick(float deltaTime)
{
	C_ACTOR::Tick(deltaTime);
	m_timer.Tick(deltaTime);

	ApplyMovement(deltaTime);
	
	Fire();

	// Check: 화면 밖 파괴처리
	if (m_position.m_x + m_width < -10 || m_position.m_x > Nahoo::C_ENGINE::GetInstance().GetWidth() + 10 ||
		m_position.m_y + m_height < -10 || m_position.m_y > Nahoo::C_ENGINE::GetInstance().GetHeight() + 10)
	{
		Destroy();
	}

}

void C_PLANE::OnHit(const C_ACTOR* otherActor)
{
	E_COLLISIONTYPE otherActorCollisionType{};
	otherActorCollisionType = otherActor->GetHitComponent()->GetCollisionType();
	E_COLLISIONTYPE thisActorCollisionType{};
	thisActorCollisionType = m_hitComponent->GetCollisionType();

	if ((otherActorCollisionType & E_COLLISIONTYPE::Bullet) == E_COLLISIONTYPE::Bullet)
	{
		// 현재 엑터에서 Plane 뺀 것 & 다른 액터 collision -> 같은 편이면 값이 남을거고 아니면 안남음
		if (((thisActorCollisionType & ~E_COLLISIONTYPE::Plane) & otherActorCollisionType) == E_COLLISIONTYPE::None)
		{
			// Check: C_ACTOR를 코드의 조건식을 통해 증명했기때문에 문제 가능성 있을수도?
			const C_BULLET* bullet = static_cast<const C_BULLET*>(otherActor);

			OnDamaged(bullet->GetDamage());
		}
	}
	else if ((otherActorCollisionType & E_COLLISIONTYPE::Plane) == E_COLLISIONTYPE::Plane)
	{
		if ((otherActorCollisionType & m_hitComponent->GetCollisionType()) != (m_hitComponent->GetCollisionType() & ~E_COLLISIONTYPE::Player))
		{
			//Todo: 파괴 이펙트
			Destroy();
		}
	}
	
}

void C_PLANE::OnDestroy()
{
	C_ACTOR::OnDestroy();

}

void C_PLANE::Fire()
{
	if (m_timer.IsTimeOut())
	{
		
		C_VECTOR2 position;
		position.m_x = m_position.m_x + (m_width / 2) - 5;
		
		if ((m_bulletSpec.moveDirection & E_MOVEDIRECTION::Up) == E_MOVEDIRECTION::Up)
		{
			position.m_y = m_position.m_y - 6;
		}
		else if ((m_bulletSpec.moveDirection & E_MOVEDIRECTION::Down) == E_MOVEDIRECTION::Down)
		{
			position.m_y = m_position.m_y + m_height + 6;
		}
		else
		{
			position.m_y = m_position.m_y + (m_height / 2);
		}

		C_BULLET* bullet{};
		bullet = new C_BULLET(m_bulletSpec.fileName, position, m_bulletSpec.color, 
			m_bulletSpec.moveSpeed.m_x, m_bulletSpec.moveSpeed.m_y,
			(m_hitComponent->GetCollisionType() & ~E_COLLISIONTYPE::Plane), m_bulletSpec.damage, m_bulletSpec.isBounce);
		GetOwner()->AddNewActor(bullet);
		bullet->GiveMoveOrder(m_bulletSpec.moveDirection);


		m_timer.Reset();
	}
}

void C_PLANE::OnDamaged(int damage)
{
	m_health -= damage;
	if (m_health < 0)
	{
		// 아군이든 적군이든 죽으면 기본 30% 확률로 아이템 드랍
		RandomItemDrop();
		// Todo: 파괴되는 이펙트 액터 생성
		Destroy();
	}
}

void C_PLANE::GiveMoveOrder(const E_MOVEDIRECTION& moveDirection, int moveSpeed)
{
	if (moveDirection == E_MOVEDIRECTION::None)
	{
		MoveStop();
		return;
	}
	
	// moveSpeed가 -1이면 기존에 설정된 이동속도 적용
	if (moveSpeed != -1)
	{
		m_moveHorizontalSpeed = moveSpeed;
		m_moveVerticalSpeed = static_cast<int>(m_moveHorizontalSpeed * 0.8);
	}
	
	if ((moveDirection & E_MOVEDIRECTION::Left) == E_MOVEDIRECTION::Left)
	{
		MoveLeft();
	}
	else if ((moveDirection & E_MOVEDIRECTION::Right) == E_MOVEDIRECTION::Right)
	{
		MoveRight();
	}

	if ((moveDirection & E_MOVEDIRECTION::Up) == E_MOVEDIRECTION::Up)
	{
		MoveUp();
	}
	else if ((moveDirection & E_MOVEDIRECTION::Down) == E_MOVEDIRECTION::Down)
	{
		MoveDown();
	}
	
}

void C_PLANE::SetBulletSpec(const char* fileName, E_COLOR color, int horizontalSpeed, int verticalSpeed,
	int damage, bool isBounce, E_MOVEDIRECTION moveDirection)
{
	m_bulletSpec.fileName = fileName;
	m_bulletSpec.color = color;
	m_bulletSpec.moveSpeed.m_x = horizontalSpeed;
	m_bulletSpec.moveSpeed.m_y = verticalSpeed;
	m_bulletSpec.damage = damage;
	m_bulletSpec.isBounce = isBounce;
	m_bulletSpec.moveDirection = moveDirection;
}

void C_PLANE::RandomItemDrop(int percentage)
{
	int randomNum = UTIL::RandomInteger(0, 10);
	E_MOVEDIRECTION moveDirection{};
	if (randomNum < percentage)
	{
		// 아이템 드랍함
		C_ITEM* item{};
		randomNum = UTIL::RandomInteger(0, 10);
		
		if (randomNum < 2.5)
		{
			moveDirection = E_MOVEDIRECTION::Left | E_MOVEDIRECTION::Up;
		}
		else if (randomNum < 5)
		{
			moveDirection = E_MOVEDIRECTION::Right | E_MOVEDIRECTION::Up;
		}
		else if (randomNum < 7.5)
		{
			moveDirection = E_MOVEDIRECTION::Right | E_MOVEDIRECTION::Down;
		}
		else
		{
			moveDirection = E_MOVEDIRECTION::Right | E_MOVEDIRECTION::Up;
		}

		randomNum = UTIL::RandomInteger(0, 10);

		// powerUp
		if (randomNum < 5)
		{
			item = new C_ITEM("powerUp.txt", m_position, E_COLOR::Green | E_COLOR::Red | E_COLOR::BackgroundRed | E_COLOR::BackgroundGreen, 25, 50, 40, E_ITEMTYPE::PowerUp, true);
			item->GiveMoveOrder(moveDirection);
			m_owner->AddNewActor(item);
		}
		else //special attack
		{
			item = new C_ITEM("specialAttack.txt", m_position, E_COLOR::Red | E_COLOR::Blue | E_COLOR::BackgroundRed | E_COLOR::BackgroundBlue, 25, 50, 40, E_ITEMTYPE::SpecialAttack, true);
			item->GiveMoveOrder(moveDirection);
			m_owner->AddNewActor(item);
		}

	}


	
}

void C_PLANE::ApplyMovement(float deltaTime)
{
	if (
		((m_currentMoveDirection & E_MOVEDIRECTION::Left) == E_MOVEDIRECTION::Left) ||
		((m_currentMoveDirection & E_MOVEDIRECTION::Right) == E_MOVEDIRECTION::Right)
		)
	{
		m_xPosition += m_moveHorizontalSpeed * deltaTime;
	}

	if (
		((m_currentMoveDirection & E_MOVEDIRECTION::Up) == E_MOVEDIRECTION::Up) ||
		((m_currentMoveDirection & E_MOVEDIRECTION::Down) == E_MOVEDIRECTION::Down)
		)
	{
		m_yPosition += m_moveVerticalSpeed * deltaTime;
	}

	m_position.m_x = static_cast<int>(m_xPosition);
	m_position.m_y = static_cast<int>(m_yPosition);
}

void C_PLANE::MoveLeft()
{
	m_currentMoveDirection = m_currentMoveDirection & ~E_MOVEDIRECTION::Right;
	m_currentMoveDirection = m_currentMoveDirection | E_MOVEDIRECTION::Left;

	if (m_moveHorizontalSpeed > 0)
	{
		m_moveHorizontalSpeed *= -1;
	}
}

void C_PLANE::MoveRight()
{
	m_currentMoveDirection = m_currentMoveDirection & ~E_MOVEDIRECTION::Left;
	m_currentMoveDirection = m_currentMoveDirection | E_MOVEDIRECTION::Right;

	if (m_moveHorizontalSpeed < 0)
	{
		m_moveHorizontalSpeed *= -1;
	}
}

void C_PLANE::MoveUp()
{
	m_currentMoveDirection = m_currentMoveDirection & ~E_MOVEDIRECTION::Down;
	m_currentMoveDirection = m_currentMoveDirection | E_MOVEDIRECTION::Up;

	if (m_moveVerticalSpeed > 0)
	{
		m_moveVerticalSpeed *= -1;
	}
}

void C_PLANE::MoveDown()
{
	m_currentMoveDirection = m_currentMoveDirection & ~E_MOVEDIRECTION::Up;
	m_currentMoveDirection = m_currentMoveDirection | E_MOVEDIRECTION::Down;

	if (m_moveVerticalSpeed < 0)
	{
		m_moveVerticalSpeed *= -1;
	}
}

void C_PLANE::MoveStop()
{
	m_currentMoveDirection = E_MOVEDIRECTION::None;
}

