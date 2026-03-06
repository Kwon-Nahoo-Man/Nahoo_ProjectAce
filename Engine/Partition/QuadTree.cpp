#include "QuadTree.h"
#include "Component/HitComponent.h"

Nahoo::C_QUADTREE::C_QUADTREE(int x, int y, int width, int height, int maxDepth)
{
	m_root = new C_NODE(x, y, width, height, 0, maxDepth);
}

Nahoo::C_QUADTREE::~C_QUADTREE()
{
	if (m_root != nullptr)
	{
		delete m_root;
		m_root = nullptr;
	}
}

bool Nahoo::C_QUADTREE::Insert(COMP_HITCOMPONENT* hitComp)
{
	if (hitComp == nullptr)
	{
		return false;
	}

	return m_root->Insert(hitComp);
}

void Nahoo::C_QUADTREE::QueryCollision(COMP_HITCOMPONENT* hitComp)
{
	if (hitComp == nullptr)
	{
		return;
	}

	std::vector<C_NODE*> possibleNodes{};

	// 들어온 HitComponent가 충돌할 만 한 노드 리스트 나옴
	m_root->Query(hitComp, possibleNodes);

	for (C_NODE* node : possibleNodes)
	{
		for (COMP_HITCOMPONENT* compareHitComp : node->GetHitComp())
		{
			if (compareHitComp == hitComp)
			{
				continue;
			}

			// 충돌 판정
			hitComp->HasCollided(compareHitComp);
		}
	}

}

void Nahoo::C_QUADTREE::ClearCompList()
{
	m_root->Clear(false);
}
