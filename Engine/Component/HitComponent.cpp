#include "Actor/Actor.h"
#include "HitComponent.h"

Nahoo::COMP_HITCOMPONENT::COMP_HITCOMPONENT(const C_VECTOR2& actorPosition, int width, int height)
    : m_actorPosition(actorPosition), m_actorMaxPosition(width, height)
{

}

Nahoo::COMP_HITCOMPONENT::~COMP_HITCOMPONENT()
{
    OnDestroy();
}

void Nahoo::COMP_HITCOMPONENT::Tick(float deltaTime)
{
    m_actorPosition = m_owner->GetPosition();
}

bool Nahoo::COMP_HITCOMPONENT::HasCollided(Nahoo::COMP_HITCOMPONENT& otherComp)
{
    int xMin = m_actorPosition.m_x;
    int xMax = m_actorPosition.m_x + m_actorMaxPosition.m_x - 1;

    int otherXMin = otherComp.m_actorPosition.m_x;
    int otherXMax = otherComp.m_actorPosition.m_x + otherComp.m_actorMaxPosition.m_x - 1;

    int yMin = m_actorPosition.m_y;
    int yMax = m_actorPosition.m_y + m_actorMaxPosition.m_y - 1;

    int otherYMin = otherComp.m_actorPosition.m_y;
    int otherYMax = otherComp.m_actorPosition.m_y + otherComp.m_actorMaxPosition.m_y - 1;

    if (xMin > otherXMax || xMax < otherXMin || yMin > otherYMax || yMax < otherYMin)
    {
        // hit가 안불려도 되나?
        //m_owner->OnHit(0);

        return false;
    }



    // 안되는 상황 다 제외했을 때
    // m_owner-> 충돌했을 때 행동 OnHit(othercomp.m_owner.isTypeof())
    m_owner->OnHit(otherComp.GetOwner()->GetType());
    otherComp.GetOwner()->OnHit(m_owner->GetType());

    return true;
}

void Nahoo::COMP_HITCOMPONENT::Destroy()
{
    m_destroyRequested = true;
}

void Nahoo::COMP_HITCOMPONENT::OnDestroy()
{
    
}

