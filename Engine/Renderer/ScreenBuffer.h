#pragma once

#include <Windows.h>

#include "Math/Vector2.h"

namespace Nahoo
{
	class C_SCREENBUFFER
	{
	public:
		C_SCREENBUFFER(const C_VECTOR2& screenSize);
		~C_SCREENBUFFER();

		void Clear();

		void Draw(CHAR_INFO* charInfo);

		inline HANDLE GerBuffer() const { return m_buffer; }

	private:

		HANDLE m_buffer = nullptr;

		C_VECTOR2 m_screenSize{};

	};


}
