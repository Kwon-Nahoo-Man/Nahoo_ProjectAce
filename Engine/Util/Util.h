#pragma once

#include <time.h>

#include "Math/Vector2.h"
#include "Enumeration/Color.h"

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

	inline void SetRandomSeed()
	{
		srand(static_cast<unsigned int>(time(nullptr)));
	}

	// 정수 난수 함수
	inline int RandomInteger(int min, int max)
	{
		int diff = (max - min) + 1;
		return ((diff * rand()) / (RAND_MAX + 1)) + min;
	}

	// 부동소수점 난수 함수
	inline float RandomFloat(float min, float max)
	{
		float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		float diff = (max - min);
		return (random * diff) + min;
	}

}


