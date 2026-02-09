#pragma once

enum class E_MOVEDIRECTION : unsigned char
{
	None = 0x00,
	Left = 0x01,
	Right = 0x02,
	Up = 0x04,
	Down = 0x08,

};

inline E_MOVEDIRECTION operator|(const E_MOVEDIRECTION& left, const E_MOVEDIRECTION& right)
{
	return static_cast<E_MOVEDIRECTION>(static_cast<unsigned char>(left) | static_cast<unsigned char>(right));
}

inline E_MOVEDIRECTION operator&(const E_MOVEDIRECTION& left, const E_MOVEDIRECTION& right)
{
	return static_cast<E_MOVEDIRECTION>(static_cast<unsigned char>(left) & static_cast<unsigned char>(right));
}

inline E_MOVEDIRECTION operator~(const E_MOVEDIRECTION& target)
{
	return static_cast<E_MOVEDIRECTION>(~static_cast<unsigned char>(target));
}
