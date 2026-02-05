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
	};

	
}
