#pragma once

#include <vector>

#include "Node.h"

namespace Nahoo
{
	class COMP_HITCOMPONENT;

	class C_QUADTREE
	{
		
	public:
		C_QUADTREE(int x, int y, int width, int height, int maxDepth);
		~C_QUADTREE();

		bool Insert(COMP_HITCOMPONENT* hitComp);
		
		void QueryCollision(COMP_HITCOMPONENT* hitComp);
		void ClearCompList();

		void DebugShow();

	private:

		C_NODE* m_root{};

	};

}