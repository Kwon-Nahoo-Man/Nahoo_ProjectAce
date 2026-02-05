#pragma once

#include <vector>

#include "Math/Vector2.h"
#include "Math/Color.h"

namespace Nahoo
{
	class C_SCREENBUFFER;

	class NAHOO_API C_RENDERER
	{
		struct S_FRAME
		{
			S_FRAME(int bufferCount);
			~S_FRAME();

			void Clear(const C_VECTOR2& screenSize);

			CHAR_INFO* m_charInfoArray{};

			int* m_sortingOrderArray{};
		};

		struct S_RENDERCOMMAND
		{
			const char* m_text = nullptr;

			C_VECTOR2 m_position{};
			E_COLOR m_color = E_COLOR::White;
			int m_sortingOrder{};

		};
	
	public:
		C_RENDERER(const C_VECTOR2& screenSize);
		~C_RENDERER();

		void Draw();
		void Submit(const char* text, const C_VECTOR2& position, E_COLOR color = E_COLOR::White, int sortingOrder = 1);
		static C_RENDERER& GetInstance();

	private:
		void Clear();
		void Present();
		C_SCREENBUFFER* GetCurrentBuffer();

	private:
		C_VECTOR2 m_screenSize;
		
		S_FRAME* m_frame = nullptr;
		
		C_SCREENBUFFER* m_screenBuffers[2]{};
		int m_currentBufferIndex{};

		std::vector<S_RENDERCOMMAND>m_renderQueue{};

		static C_RENDERER* m_instance;
	};


}
