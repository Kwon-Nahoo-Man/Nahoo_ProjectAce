#include "Core/Input.h"
#include "Actor/Object.h"
#include "Component/HitComponent.h"
#include "Engine/Engine.h"

C_OBJECT::C_OBJECT(const char* fileName, C_VECTOR2& position, bool collision, E_COLOR color,
	int sortingOrder, int moveSpeed)
	:C_ACTOR(fileName, position, collision)
{
	m_color = color;
	m_sortingOrder = sortingOrder;
	m_moveHorizontalSpeed = moveSpeed;
	m_moveVerticalSpeed = static_cast<int>(m_moveHorizontalSpeed * 0.8);

	if (m_hitComponent != nullptr)
	{
		m_hitComponent->SetCollision(collision);
		// Object는 자식 개체 가서 collisionType 결정
	}

	m_xPosition = static_cast<float>(m_position.m_x);
	m_yPosition = static_cast<float>(m_position.m_y);
}

C_OBJECT::~C_OBJECT()
{

}

void C_OBJECT::BeginPlay()
{
	C_ACTOR::BeginPlay();
}

void C_OBJECT::Tick(float deltaTime)
{
	C_ACTOR::Tick(deltaTime);
	
	m_bounceTimer.Tick(deltaTime);

	ApplyMovement(deltaTime);

	Bounce(m_isBounce);
	
	// 화면 밖 파괴처리 (bounce 함수 때문에 좀 널널하게 파괴처리 함)
	if (m_position.m_y > Nahoo::C_ENGINE::GetInstance().GetHeight() + 5)
	{
		Destroy();
	}
}

void C_OBJECT::OnHit(const C_ACTOR* otherActor)
{
	
}

void C_OBJECT::GiveMoveOrder(const E_MOVEDIRECTION& moveDirection, int moveSpeed)
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

void C_OBJECT::SetBounce(bool decision, float minimumTime)
{
	m_isBounce = decision;
	m_bounceTimer.SetTargetTime(minimumTime);
}

void C_OBJECT::Bounce(bool isBounce)
{
	// 바운스를 하지 않거나, 객체 지속시간이 만료된 경우
	if (isBounce == false || m_bounceTimer.IsTimeOut())
	{
		return;
	}

	// 좌우 튕김
	if (m_position.m_x < 0)
	{
		MoveRight();
	}
	else if (m_position.m_x + m_width > Nahoo::C_ENGINE::GetInstance().GetWidth())
	{
		MoveLeft();
	}

	if (m_position.m_y  < 0)
	{
		MoveDown();
	}
	else if (m_position.m_y + m_height > Nahoo::C_ENGINE::GetInstance().GetHeight())
	{
		MoveUp();
	}

}


void C_OBJECT::ApplyMovement(float deltaTime)
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

void C_OBJECT::MoveLeft()
{
	m_currentMoveDirection = m_currentMoveDirection & ~E_MOVEDIRECTION::Right;
	m_currentMoveDirection = m_currentMoveDirection | E_MOVEDIRECTION::Left;

	if (m_moveHorizontalSpeed > 0)
	{
		m_moveHorizontalSpeed *= -1;
	}
}

void C_OBJECT::MoveRight()
{
	m_currentMoveDirection = m_currentMoveDirection & ~E_MOVEDIRECTION::Left;
	m_currentMoveDirection = m_currentMoveDirection | E_MOVEDIRECTION::Right;

	if (m_moveHorizontalSpeed < 0)
	{
		m_moveHorizontalSpeed *= -1;
	}
}

void C_OBJECT::MoveUp()
{
	m_currentMoveDirection = m_currentMoveDirection & ~E_MOVEDIRECTION::Down;
	m_currentMoveDirection = m_currentMoveDirection | E_MOVEDIRECTION::Up;

	if (m_moveVerticalSpeed > 0)
	{
		m_moveVerticalSpeed *= -1;
	}
}

void C_OBJECT::MoveDown()
{
	m_currentMoveDirection = m_currentMoveDirection & ~E_MOVEDIRECTION::Up;
	m_currentMoveDirection = m_currentMoveDirection | E_MOVEDIRECTION::Down;

	if (m_moveVerticalSpeed < 0)
	{
		m_moveVerticalSpeed *= -1;
	}
}

void C_OBJECT::MoveStop()
{
	m_currentMoveDirection = E_MOVEDIRECTION::None;
}
