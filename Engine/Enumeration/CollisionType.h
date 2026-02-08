#pragma once

#include "Common/Common.h"

namespace Nahoo
{
	enum class NAHOO_API E_COLLISIONTYPE : unsigned char
	{
		None = 0x00,
		Ally = 0x01,
		Enemy = 0x02,
		Item = 0x04,


	};

	inline E_COLLISIONTYPE operator|(const E_COLLISIONTYPE& left, const E_COLLISIONTYPE& right)
	{
		return static_cast<E_COLLISIONTYPE>(static_cast<unsigned char>(left) | static_cast<unsigned char>(right));
	}

	inline E_COLLISIONTYPE operator&(const E_COLLISIONTYPE& left, const E_COLLISIONTYPE& right)
	{
		return static_cast<E_COLLISIONTYPE>(static_cast<unsigned char>(left) & static_cast<unsigned char>(right));
	}

	inline E_COLLISIONTYPE operator~(const E_COLLISIONTYPE& target)
	{
		return static_cast<E_COLLISIONTYPE>(~static_cast<unsigned char>(target));
	}
}
