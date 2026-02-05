#pragma once

#include "Math/Vector2.h"
#include "Math/Color.h"

namespace UTIL
{
	inline void SetConsolePosition(const Nahoo::C_VECTOR2& position)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<COORD>(position));
	}

	inline void SetConsoleTextColor(const Nahoo::E_COLOR color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<unsigned short>(color));
	}

	inline void SetCursorAppear(bool isCursorTurnOn)
	{
		CONSOLE_CURSOR_INFO info{};
		GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

		info.bVisible = isCursorTurnOn;

		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	}
}


