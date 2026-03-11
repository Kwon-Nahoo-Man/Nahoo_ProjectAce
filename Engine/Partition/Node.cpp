#include "Node.h"
#include "Enumeration/NodeIndex.h"
#include "Component/HitComponent.h"
#include "Renderer/Renderer.h"

Nahoo::C_NODE::C_NODE(int x, int y, int width, int height, int depth, int maxDepth)
    :m_x(x),m_y(y),m_width(width), m_height(height),m_depth(depth), m_maxDepth(maxDepth)
{
       

}

Nahoo::C_NODE::~C_NODE()
{
    Clear(true);
}

bool Nahoo::C_NODE::IsDivided()
{
    return m_topLeft != nullptr;
}

bool Nahoo::C_NODE::Subdivide()
{
    if (IsDivided() == true)
    {
        return true;
    }
    else if(m_depth < m_maxDepth)
    {
        int halfWidth = m_width / 2;
        int halfHeight = m_height / 2;

        m_topLeft = new C_NODE(m_x, m_y, halfWidth, halfHeight, m_depth + 1, m_maxDepth);
        m_topRight = new C_NODE(m_x + halfWidth, m_y, m_width - halfWidth, halfHeight, m_depth + 1, m_maxDepth);
        m_bottomLeft = new C_NODE(m_x, m_y + halfHeight, halfWidth, m_height - halfHeight, m_depth + 1, m_maxDepth);
        m_bottomRight = new C_NODE(m_x + halfWidth, m_y + halfHeight, m_width - halfWidth, m_height - halfHeight, m_depth + 1, m_maxDepth);

        return true;
    }
    
    return false;
}

Nahoo::E_NODEINDEX Nahoo::C_NODE::GetNodeIndex(int x, int y, int width, int height)
{
    E_NODEINDEX nodeIndex{};

    int halfWidth = m_width / 2;
    int halfHeight = m_height / 2;
    int centerX = m_x + halfWidth;
    int centerY = m_y + halfHeight;

    bool left = x + width >= m_x && x < centerX;
    bool right = x + width >= centerX && x < m_x + m_width;
    bool top = y + height >= m_y && y < centerY;
    bool bottom = y + height >= centerY && y < m_y + m_height;
    
    if (top && left)
    {
        nodeIndex = nodeIndex | E_NODEINDEX::TopLeft;
    }
    if (top && right)
    {
        nodeIndex = nodeIndex | E_NODEINDEX::TopRight;
    }
    if (bottom && left)
    {
        nodeIndex = nodeIndex | E_NODEINDEX::BottomLeft;
    }
    if (bottom && right)
    {
        nodeIndex = nodeIndex | E_NODEINDEX::BottomRight;
    }


    return nodeIndex;
}

Nahoo::E_NODEINDEX Nahoo::C_NODE::TestRegion(int x, int y, int width, int height)
{
    unsigned char quads = static_cast<unsigned char>(GetNodeIndex(x, y, width, height));

    if (quads == 0)
    {
        return E_NODEINDEX::None;
    }

    if ((quads & (quads - 1)) == 0)
    {
        return static_cast<E_NODEINDEX>(quads);
    }

    return static_cast<E_NODEINDEX>(quads) | E_NODEINDEX::Straddling;

}

bool Nahoo::C_NODE::Insert(COMP_HITCOMPONENT* hitComp)
{
    if (hitComp == nullptr)
    {
        return false;
    }

    C_VECTOR2 position = hitComp->GetActorPosition();
    C_VECTOR2 widthHeight = hitComp->GetActorWidthHeight();
    E_NODEINDEX result = TestRegion(position.m_x, position.m_y, widthHeight.m_x, widthHeight.m_y);

    // 어디에도 해당안되거나 판단 안서는 경우
    if (result == E_NODEINDEX::None)
    {
        return false;
    }
    // 겹치는 경우
    if ((result & E_NODEINDEX::Straddling) != E_NODEINDEX::None)
    {
        m_hitComps.emplace_back(hitComp);
        return true;
    }

    // 한 사분면에만 들어가는 경우
    else
    {
        if (Subdivide() == true)
        {
            if ((result & E_NODEINDEX::TopLeft) != E_NODEINDEX::None)
            {
                m_topLeft->Insert(hitComp);
            }
            else if ((result & E_NODEINDEX::TopRight) != E_NODEINDEX::None)
            {
                m_topRight->Insert(hitComp);
            }
            else if ((result & E_NODEINDEX::BottomLeft) != E_NODEINDEX::None)
            {
                m_bottomLeft->Insert(hitComp);
            }
            else if ((result & E_NODEINDEX::BottomRight) != E_NODEINDEX::None)
            {
                m_bottomRight->Insert(hitComp);
            }
            return true;

        }
        // 한 사분면에 해당하지만 나눌 수 없는 경우
        else
        {
            m_hitComps.emplace_back(hitComp);
            return true;
        }
    }

    return false;
}

void Nahoo::C_NODE::Query(const COMP_HITCOMPONENT* hitComp, std::vector<C_NODE*>& possibleNodes)
{
    possibleNodes.emplace_back(this);

    if (IsDivided() == true)
    {
        int x = hitComp->GetActorPosition().m_x;
        int y = hitComp->GetActorPosition().m_y;

        int width = hitComp->GetActorWidthHeight().m_x;
        int height = hitComp->GetActorWidthHeight().m_y;

        E_NODEINDEX result = GetNodeIndex(x, y, width, height);

        if ((result & E_NODEINDEX::TopLeft) != E_NODEINDEX::None)
        {
            m_topLeft->Query(hitComp, possibleNodes);
        }
        if ((result & E_NODEINDEX::TopRight) != E_NODEINDEX::None)
        {
            m_topRight->Query(hitComp, possibleNodes);
        }
        if ((result & E_NODEINDEX::BottomLeft) != E_NODEINDEX::None)
        {
            m_bottomLeft->Query(hitComp, possibleNodes);
        }
        if ((result & E_NODEINDEX::BottomRight) != E_NODEINDEX::None)
        {
            m_bottomRight->Query(hitComp, possibleNodes);
        }

    }

}

void Nahoo::C_NODE::Clear(bool memoryReleaseFlag)
{
    m_hitComps.clear();

    if (IsDivided() == true)
    {
        m_topLeft->Clear(memoryReleaseFlag);
        m_topRight->Clear(memoryReleaseFlag);
        m_bottomLeft->Clear(memoryReleaseFlag);
        m_bottomRight->Clear(memoryReleaseFlag);

        if (memoryReleaseFlag == true)
        {
            ClearChildren();
        }
    }
}

void Nahoo::C_NODE::DebugDraw()
{
    if (m_hitComps.empty())
    {
        Nahoo::C_RENDERER::GetInstance().DebugSubmit(m_width, m_height, C_VECTOR2(m_x, m_y), E_COLOR::BackgroundBlue | E_COLOR::BackgroundRed, 50);
    }
    else
    {
        Nahoo::C_RENDERER::GetInstance().DebugSubmit(m_width, m_height, C_VECTOR2(m_x, m_y), E_COLOR::BackgroundGreen, 51);
    }

    if (IsDivided() == true)
    {
        m_topLeft->DebugDraw();
        m_topRight->DebugDraw();
        m_bottomLeft->DebugDraw();
        m_bottomRight->DebugDraw();
    }

}


void Nahoo::C_NODE::ClearChildren()
{
    delete m_topLeft;
    delete m_topRight;
    delete m_bottomLeft;
    delete m_bottomRight;

    m_topLeft = nullptr;
    m_topRight = nullptr;
    m_bottomLeft = nullptr;
    m_bottomRight = nullptr;
}
