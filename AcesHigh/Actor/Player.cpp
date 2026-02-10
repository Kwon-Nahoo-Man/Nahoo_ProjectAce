#include "Core/Input.h"
#include "Level/Level.h"
#include "Player.h"
#include "Component/HitComponent.h"
#include "Actor/Bullet.h"
#include "Util/Timer.h"
#include "Engine/Engine.h"
#include "Actor/Item.h"
#include "Level/TestLevel.h"


C_PLAYER::C_PLAYER(const char* fileName, C_VECTOR2& position, bool collision, E_COLOR color,
					int sortingOrder, int moveSpeed, int health, float fireRate)
	: C_PLANE(fileName, position,collision,color,moveSpeed,health,E_COLLISIONTYPE::Ally)
{
	m_fireRate = fireRate;
	m_hitComponent->SetCollisionType(E_COLLISIONTYPE::Player);
	m_sortingOrder = 11;
}

C_PLAYER::~C_PLAYER()
{
	C_PLANE::OnDestroy();
}


void C_PLAYER::BeginPlay()
{
	C_PLANE::BeginPlay();

	// 사격위치 값 초기설정
	m_firePosition.m_x = m_position.m_x + m_width / 2 - 1;
	m_firePosition.m_y = m_position.m_y - 6;
	m_damage = 1;
	m_bulletFileName = "bullet.txt";
	m_specialAttack = 3;
	m_timer.SetTargetTime(m_fireRate);
}

void C_PLAYER::Tick(float deltaTime)
{
	C_ACTOR::Tick(deltaTime);
	m_timer.Tick(deltaTime);

	// PlayerMovement
	{
		if (Nahoo::C_INPUT::GetInstance().GetKey(VK_SPACE))
		{
			Fire();
		}

		if (Nahoo::C_INPUT::GetInstance().GetKey(VK_LEFT) && m_position.m_x > 0)
		{
			m_xPosition -= m_moveHorizontalSpeed * deltaTime;
			
		}
		if (Nahoo::C_INPUT::GetInstance().GetKey(VK_RIGHT)&& m_position.m_x + m_width +2 < Nahoo::C_ENGINE::GetInstance().GetWidth())
		{
			m_xPosition += m_moveHorizontalSpeed * deltaTime;
			

		}
		if (Nahoo::C_INPUT::GetInstance().GetKey(VK_UP) && m_position.m_y > 0)
		{
			m_yPosition -= m_moveVerticalSpeed * deltaTime;
			

		}
		if (Nahoo::C_INPUT::GetInstance().GetKey(VK_DOWN) && m_position.m_y + m_height +1 < Nahoo::C_ENGINE::GetInstance().GetHeight())
		{
			m_yPosition += m_moveVerticalSpeed * deltaTime;
			
		}

		m_position.m_x = static_cast<int>(m_xPosition);
		m_position.m_y = static_cast<int>(m_yPosition);

		if (Nahoo::C_INPUT::GetInstance().GetKeyDown('E'))
		{
			SpecialAttack();
		}
		if (Nahoo::C_INPUT::GetInstance().GetKeyDown('Q'))
		{
			PowerUp();
		}



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
		const C_ITEM* item = static_cast<const C_ITEM*>(otherActor);
		if (item->GetItemType() == E_ITEMTYPE::PowerUp)
		{
			PowerUp();
		}
		else if (item->GetItemType() == E_ITEMTYPE::SpecialAttack)
		{
			EarnSpecialAttack();
		}

	}

}

void C_PLAYER::OnDestroy()
{
	C_PLANE::OnDestroy();
}

void C_PLAYER::Fire()
{
	if (m_timer.IsTimeOut())
	{
		if (m_currentPower == 0)
		{
			m_firePosition.m_x = m_position.m_x + m_width / 2 - 1;
		}
		else if (m_currentPower == 1)
		{
			m_firePosition.m_x = m_position.m_x + m_width / 2 - 5;
		}
		else if (m_currentPower == 2)
		{
			m_firePosition.m_x = m_position.m_x + m_width / 2 - 9;
		}

		m_firePosition.m_y = m_position.m_y - 6;

		C_BULLET* bullet{};
		bullet = new C_BULLET(m_bulletFileName, m_firePosition, 
			E_COLOR::Green | E_COLOR::ForegroundIntensity | E_COLOR::BackgroundGreen | E_COLOR::BackgroundIntensity
			, 0, 200, E_COLLISIONTYPE::Ally, m_damage, false);
		GetOwner()->AddNewActor(bullet);
		bullet->GiveMoveOrder(E_MOVEDIRECTION::Up);

		m_timer.Reset();
	}

	//m_owner->AddNewActor(new C_OBJECT("bullet.txt", firePosition));
}

void C_PLAYER::OnDamaged(int damage)
{
	C_PLANE::OnDamaged(damage);

	// Check DownCasting --> testLevel 아니면 위험
	static_cast<C_TESTLEVEL*>(m_owner)->UpdatePlayerHealthUI(m_health);

	PowerDown();
}

void C_PLAYER::PowerUp()
{
	if (m_currentPower < 2)
	{
		m_currentPower++;
	}
	EarnSpecialAttack();

	if (m_currentPower == 2)
	{
		m_bulletFileName = "bullet3.txt";
		m_damage = 3;
	}
	else if (m_currentPower == 1)
	{
		m_bulletFileName = "bullet2.txt";
		m_damage = 2;
	}

}

void C_PLAYER::PowerDown()
{
	if (m_currentPower > 0)
	{
		m_currentPower--;
	}

	if (m_currentPower == 0)
	{
		m_bulletFileName = "bullet.txt";
		m_damage = 1;
	}
	else if (m_currentPower == 1)
	{
		m_bulletFileName = "bullet2.txt";
		m_damage = 2;
	}

}

void C_PLAYER::EarnSpecialAttack()
{
	if (m_specialAttack < 3)
	{
		m_specialAttack++;
	}
	static_cast<C_TESTLEVEL*>(m_owner)->UpdatePlayerSpecialAttackUI(m_specialAttack);
}

void C_PLAYER::SpecialAttack()
{
	if (m_specialAttack <= 0)
	{
		return;
	}
	m_specialAttack--;

	C_VECTOR2 spawnPosition{};
	spawnPosition.m_y = Nahoo::C_ENGINE::GetInstance().GetHeight() - 20;
	
	C_PLANE* ally{};
	for (int i = 1; i <= 3; i++)
	{
		spawnPosition.m_x = (Nahoo::C_ENGINE::GetInstance().GetWidth() - 10) / 4 * i;
		ally = new C_PLANE("ally_plane1.txt", spawnPosition, true, E_COLOR::Blue, 40, 10, E_COLLISIONTYPE::Ally, 0.5f);
		ally->SetBulletSpec("enemyPistol.txt", E_COLOR::Blue | E_COLOR::ForegroundIntensity | E_COLOR::BackgroundBlue, 0, 80, 2, false, E_MOVEDIRECTION::Up);
		ally->GiveMoveOrder(E_MOVEDIRECTION::Up);
		m_owner->AddNewActor(ally);

	}
	static_cast<C_TESTLEVEL*>(m_owner)->UpdatePlayerSpecialAttackUI(m_specialAttack);
	
}
