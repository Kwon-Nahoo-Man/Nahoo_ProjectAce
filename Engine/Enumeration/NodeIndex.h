#pragma once

#include "Common/Common.h"

namespace Nahoo
{
	enum class NAHOO_API E_NODEINDEX : unsigned char
	{
		None = 0,
		TopLeft = 1 << 0,
		TopRight = 1 << 1,
		BottomLeft = 1 << 2,
		BottomRight = 1 << 3,
		Straddling = 1 << 4,
	};


	inline E_NODEINDEX operator|(const E_NODEINDEX& left, const E_NODEINDEX& right)
	{
		return static_cast<E_NODEINDEX>(static_cast<unsigned char>(left) | static_cast<unsigned char>(right));
	}

	inline E_NODEINDEX operator&(const E_NODEINDEX& left, const E_NODEINDEX& right)
	{
		return static_cast<E_NODEINDEX>(static_cast<unsigned char>(left) & static_cast<unsigned char>(right));
	}

	inline E_NODEINDEX operator~(const E_NODEINDEX& target)
	{
		return static_cast<E_NODEINDEX>(~static_cast<unsigned char>(target));
	}



}


