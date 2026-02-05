#pragma once

#include <Windows.h>

#include "Common/Common.h"

namespace Nahoo
{
	class NAHOO_API C_VECTOR2
	{
	public:
		C_VECTOR2();
		C_VECTOR2(int x, int y);
		~C_VECTOR2();

		C_VECTOR2 operator+(const C_VECTOR2& other) const;
		C_VECTOR2 operator-(const C_VECTOR2& other) const;

		bool operator==(const C_VECTOR2& other) const;
		bool operator!=(const C_VECTOR2& other) const;
		operator COORD() const;

	public:
		const char* Tostring();

	public:
		int m_x{};
		int m_y{};

		static C_VECTOR2 Zero;
		static C_VECTOR2 One;
		static C_VECTOR2 Up;
		static C_VECTOR2 Right;

	private:
		char* string{};
	};
}
