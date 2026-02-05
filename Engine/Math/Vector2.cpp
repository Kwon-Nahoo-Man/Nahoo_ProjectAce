#include <cstdio>
#include "Vector2.h"

Nahoo::C_VECTOR2 Nahoo::C_VECTOR2::Zero(0, 0);
Nahoo::C_VECTOR2 Nahoo::C_VECTOR2::One(1, 1);
Nahoo::C_VECTOR2 Nahoo::C_VECTOR2::Up(0, 1);
Nahoo::C_VECTOR2 Nahoo::C_VECTOR2::Right(1, 0);

Nahoo::C_VECTOR2::C_VECTOR2()
	:m_x(0), m_y(0)
{

}

Nahoo::C_VECTOR2::C_VECTOR2(int x, int y)
	:m_x(x), m_y(y)
{

}

Nahoo::C_VECTOR2::~C_VECTOR2()
{
	if (string != nullptr)
	{
		delete[] string;
		string = nullptr;
	}
}

Nahoo::C_VECTOR2 Nahoo::C_VECTOR2::operator+(const C_VECTOR2& other) const
{
	return C_VECTOR2(m_x + other.m_x, m_y + other.m_y);
}

Nahoo::C_VECTOR2 Nahoo::C_VECTOR2::operator-(const C_VECTOR2& other) const
{
	return C_VECTOR2(m_x - other.m_x, m_y - other.m_y);
}

bool Nahoo::C_VECTOR2::operator==(const C_VECTOR2& other) const
{
	return (m_x == other.m_x) && (m_y == other.m_y);
}

bool Nahoo::C_VECTOR2::operator!=(const C_VECTOR2& other) const
{
	return (m_x != other.m_x) || (m_y != other.m_y);
}

Nahoo::C_VECTOR2::operator COORD() const
{
	COORD coord{};
	coord.X = static_cast<short>(m_x);
	coord.Y = static_cast<short>(m_y);

	return coord;
}

const char* Nahoo::C_VECTOR2::Tostring()
{
	if (string != nullptr)
	{
		delete[] string;
		string = nullptr;
	}

	string = new char[128] {};
	sprintf_s(string, 128, "(%d, %d)", m_x, m_y);

	return string;
}
