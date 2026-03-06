#pragma once

#include "Enumeration/BitMaskHelperFunc.h"

namespace Nahoo
{
	enum class E_DEBUGSHOW
	{
		None = 0,
		QuadTree = 1 << 0,
		HitComponent = 1 << 1,
	};

	inline E_DEBUGSHOW operator|(const E_DEBUGSHOW& left, const E_DEBUGSHOW& right)
	{
		return static_cast<E_DEBUGSHOW>(static_cast<unsigned char>(left) | static_cast<unsigned char>(right));
	}

	inline E_DEBUGSHOW operator&(const E_DEBUGSHOW& left, const E_DEBUGSHOW& right)
	{
		return static_cast<E_DEBUGSHOW>(static_cast<unsigned char>(left) & static_cast<unsigned char>(right));
	}
	
	// 없으면 추가, 있으면 제거
	inline E_DEBUGSHOW operator^(const E_DEBUGSHOW& left, const E_DEBUGSHOW& right)
	{
		return static_cast<E_DEBUGSHOW>(static_cast<unsigned char>(left) ^ static_cast<unsigned char>(right));
	}

	inline E_DEBUGSHOW operator~(const E_DEBUGSHOW& target)
	{
		return static_cast<E_DEBUGSHOW>(~static_cast<unsigned char>(target));
	}

}

