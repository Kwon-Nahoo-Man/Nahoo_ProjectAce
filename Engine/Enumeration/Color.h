#pragma once

#include <Windows.h>

#include "Common/Common.h"

namespace Nahoo
{

	enum class NAHOO_API E_COLOR : unsigned short
	{
		Black = 0,
		Blue = FOREGROUND_BLUE,
		Green = FOREGROUND_GREEN,
		Red = FOREGROUND_RED,
		White = Blue | Green | Red,
		ForegroundIntensity = FOREGROUND_INTENSITY,
		BackgroundBlue = BACKGROUND_BLUE,
		BackgroundGreen = BACKGROUND_GREEN,
		BackgroundRed = BACKGROUND_RED,
		BackgroundWhite = BackgroundBlue | BackgroundGreen | BackgroundRed,
		BackgroundIntensity = BACKGROUND_INTENSITY,

	};
	inline E_COLOR operator|(const E_COLOR& left, const E_COLOR& right)
	{
		return static_cast<E_COLOR>(static_cast<unsigned char>(left) | static_cast<unsigned char>(right));
	}

	inline E_COLOR operator&(const E_COLOR& left, const E_COLOR& right)
	{
		return static_cast<E_COLOR>(static_cast<unsigned char>(left) & static_cast<unsigned char>(right));
	}

	inline E_COLOR operator~(const E_COLOR& target)
	{
		return static_cast<E_COLOR>(~static_cast<unsigned char>(target));
	}
	
}
