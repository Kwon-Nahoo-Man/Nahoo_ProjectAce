#pragma once

#include "Common/Common.h"

namespace Nahoo
{
	enum class NAHOO_API E_COLLISIONTYPE : unsigned char
	{
		None = 0x00,
		Player = 0x01, // «√∑π¿ÃæÓ∞° æ∆¿Ã≈€ »πµÊ«“ ∂ß æ∏
		Ally = 0x02,
		Enemy = 0x04,
		Bullet = 0x08,
		Item = 0x0C,
		Plane = 0x10,

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
