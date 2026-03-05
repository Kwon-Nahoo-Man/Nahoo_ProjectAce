#include "Actor/Actor.h"
#include "HitComponent.h"

Nahoo::COMP_HITCOMPONENT::COMP_HITCOMPONENT(const C_VECTOR2& actorPosition, int width, int height)
    : m_actorPosition(actorPosition), m_actorWidthHeight(width, height)
{

}

Nahoo::COMP_HITCOMPONENT::~COMP_HITCOMPONENT()
{

}

void Nahoo::COMP_HITCOMPONENT::Tick(float deltaTime)
{
    m_actorPosition = m_owner->GetPosition();
}

void Nahoo::COMP_HITCOMPONENT::SetCollision(bool onOffCollision)
{
    m_activateCollision = onOffCollision;
}

bool Nahoo::COMP_HITCOMPONENT::HasCollided(Nahoo::COMP_HITCOMPONENT* otherComp)
{
    if (otherComp == nullptr)
    {
        return false;
    }
    
	if (IsActive() == false || otherComp->IsActive() == false)
    {
        return false;
    }

    int xMin = m_actorPosition.m_x;
    int xMax = m_actorPosition.m_x + m_actorWidthHeight.m_x - 1;

    int otherXMin = otherComp->m_actorPosition.m_x;
    int otherXMax = otherComp->m_actorPosition.m_x + otherComp->m_actorWidthHeight.m_x - 1;

    int yMin = m_actorPosition.m_y;
    int yMax = m_actorPosition.m_y + m_actorWidthHeight.m_y - 1;

    int otherYMin = otherComp->m_actorPosition.m_y;
    int otherYMax = otherComp->m_actorPosition.m_y + otherComp->m_actorWidthHeight.m_y - 1;

    if (xMin > otherXMax || xMax < otherXMin || yMin > otherYMax || yMax < otherYMin)
    {
        return false;
    }

    m_owner->OnHit(otherComp->GetOwner());

    // Check: QuadTree가 중복해서 물어본다면 이 부분 빼야함(충돌 중복 일어남)
    otherComp->GetOwner()->OnHit(m_owner);

    return true;
}

void Nahoo::COMP_HITCOMPONENT::SetCollisionType(E_COLLISIONTYPE collisionType)
{
    m_collisionType = m_collisionType | collisionType;
}

void Nahoo::COMP_HITCOMPONENT::DeleteCollisionType(E_COLLISIONTYPE collisionType)
{
    m_collisionType = m_collisionType & ~collisionType;
}

bool Nahoo::COMP_HITCOMPONENT::IsActive() const
{
    if (m_activateCollision == false)
    {
        return false;
    }
    if (m_collisionType == E_COLLISIONTYPE::None)
    {
        return false;
    }
    if (m_destroyRequested == true)
    {
        return false;
    }

    return true;
}

void Nahoo::COMP_HITCOMPONENT::Destroy()
{
    m_destroyRequested = true;
    m_activateCollision = false;
    m_collisionType = E_COLLISIONTYPE::None;
}

void Nahoo::COMP_HITCOMPONENT::OnDestroy()
{
    
}

