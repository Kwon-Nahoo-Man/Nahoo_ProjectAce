#pragma once
#include <vector>

#include "Enumeration/NodeIndex.h"

namespace Nahoo
{
	class COMP_HITCOMPONENT;

	class C_NODE
	{

	public:
		C_NODE(int x, int y, int width, int height, int depth);
		~C_NODE();

		bool Insert(const COMP_HITCOMPONENT* hitComp);
		void Query(const COMP_HITCOMPONENT* hitComp, std::vector<COMP_HITCOMPONENT*>& possibleComp);
		void Clear();


	public:

		// getter
		inline int GetX() const { return m_x; }
		inline int GetY() const { return m_y; }
		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }


	private:

		bool IsDivided();
		bool Subdivide();

		E_NODEINDEX GetNodeIndex(int x, int y, int width, int height);
		E_NODEINDEX TestRegion(int x, int y, int width, int height);

		void ClearChildren();

	private:
		int m_depth{};
		int m_maxDepth{};

		int m_x{};
		int m_y{};
		int m_width{};
		int m_height{};

		C_NODE* m_topLeft{};
		C_NODE* m_topRight{};
		C_NODE* m_bottomLeft{};
		C_NODE* m_bottomRight{};

		std::vector<const COMP_HITCOMPONENT*> m_hitComps{};


	};
}
