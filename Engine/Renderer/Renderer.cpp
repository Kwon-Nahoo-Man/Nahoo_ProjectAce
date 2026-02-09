#include <iostream>
#include "Renderer.h"
#include "ScreenBuffer.h"

using namespace Nahoo;

Nahoo::C_RENDERER::S_FRAME::S_FRAME(int bufferCount)
{
	m_charInfoArray = new CHAR_INFO[bufferCount];
	memset(m_charInfoArray, 0, sizeof(CHAR_INFO) * bufferCount);

	m_sortingOrderArray = new int[bufferCount];
	memset(m_sortingOrderArray, 0, sizeof(int) * bufferCount);
}

Nahoo::C_RENDERER::S_FRAME::~S_FRAME()
{
	if (m_charInfoArray != nullptr)
	{
		delete[] m_charInfoArray;
		m_charInfoArray = nullptr;
	}
	if (m_sortingOrderArray != nullptr)
	{
		delete[] m_sortingOrderArray;
		m_sortingOrderArray = nullptr;
	}
}

void Nahoo::C_RENDERER::S_FRAME::Clear(const C_VECTOR2& screenSize)
{
	const int width = screenSize.m_x;
	const int height = screenSize.m_y;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			const int index = (y * width) + x;

			CHAR_INFO& info = m_charInfoArray[index];
			info.Char.AsciiChar = ' ';
			info.Attributes = 0;

			m_sortingOrderArray[index] = -1;
		}
	}
}

// ----------------------Frame----------------------//

C_RENDERER* C_RENDERER::m_instance = nullptr;

Nahoo::C_RENDERER::C_RENDERER(const C_VECTOR2& screenSize)
	: m_screenSize(screenSize)
{
	m_instance = this;

	const int bufferCount = m_screenSize.m_x * m_screenSize.m_y;
	m_frame = new S_FRAME(bufferCount);

	m_frame->Clear(m_screenSize);

	m_screenBuffers[0] = new C_SCREENBUFFER(m_screenSize);
	m_screenBuffers[0]->Clear();

	m_screenBuffers[1] = new C_SCREENBUFFER(m_screenSize);
	m_screenBuffers[1]->Clear();

	Present();
}

Nahoo::C_RENDERER::~C_RENDERER()
{
	if (m_frame != nullptr)
	{
		delete m_frame;
		m_frame = nullptr;
	}

	if (m_screenBuffers[0] != nullptr)
	{
		delete m_screenBuffers[0];
		m_screenBuffers[0] = nullptr;
	}
	if (m_screenBuffers[1] != nullptr)
	{
		delete m_screenBuffers[1];
		m_screenBuffers[1] = nullptr;
	}
}

void Nahoo::C_RENDERER::Draw()
{
	Clear();

	for (S_RENDERCOMMAND& command : m_renderQueue)
	{

		if ((command.m_sprite.size()) <= 0)
		{
			continue;
		}

		const int startX = command.m_position.m_x;
		const int endX = command.m_position.m_x + command.m_width - 1;

		const int startY = command.m_position.m_y;
		const int endY = command.m_position.m_y + command.m_height - 1;

		// Todo: 만약 게임 창이 왼쪽에 바로 붙어있지 않으면 바운더리 다시 clamp --> 그냥 액터에서 UI 못들어가게움직임을 막을까?
		if (startX > m_screenSize.m_x || endX < 0 || startY > m_screenSize.m_y || endY < 0)
		{
			continue;
		}

		const int visibleStartX = startX < 0 ? 0 : startX;
		const int visibleEndX = endX > m_screenSize.m_x ? m_screenSize.m_x - 1 : endX;

		const int visibleStartY = startY < 0 ? 0 : startY;
		const int visibleEndY = endY > m_screenSize.m_y ? m_screenSize.m_y - 1 : endY;

		for (int y = visibleStartY; y <= visibleEndY; y++)
		{
			for (int x = visibleStartX; x <= visibleEndX; x++)
			{
				const int sourceIndex = (y - startY) * command.m_width + (x - startX); // y * width + x
				const int frameIndex = y * m_screenSize.m_x + x;

				if (command.m_sprite[sourceIndex] == ' ')
				{
					continue;
				}

				if (m_frame->m_sortingOrderArray[frameIndex] > command.m_sortingOrder)
				{
					continue;
				}

				m_frame->m_charInfoArray[frameIndex].Char.AsciiChar = command.m_sprite[sourceIndex];
				m_frame->m_charInfoArray[frameIndex].Attributes = (WORD)command.m_color;
				m_frame->m_sortingOrderArray[frameIndex] = command.m_sortingOrder;
				
			}
		}
	}
	GetCurrentBuffer()->Draw(m_frame->m_charInfoArray);
	Present();

	m_renderQueue.clear();
}

void Nahoo::C_RENDERER::Submit
(
	const std::vector<char>& sprite, int width, int height, const C_VECTOR2& position, E_COLOR color, int sortingOrder
)
{
	S_RENDERCOMMAND command{};
	command.m_sprite = sprite;
	command.m_width = width;
	command.m_height = height;

	command.m_position = position;
	command.m_color = color;
	command.m_sortingOrder = sortingOrder;

	m_renderQueue.emplace_back(command);
}

C_RENDERER& C_RENDERER::GetInstance()
{
	if (m_instance == nullptr)
	{
		MessageBoxA(
			nullptr,
			"Renderer::Get() - instance is null",
			"Error",
			MB_OK
		);

		__debugbreak();
	}

	return *m_instance;
}

void Nahoo::C_RENDERER::Clear()
{
	m_frame->Clear(m_screenSize);

	GetCurrentBuffer()->Clear();
}

void Nahoo::C_RENDERER::Present()
{
	SetConsoleActiveScreenBuffer(GetCurrentBuffer()->GerBuffer());

	m_currentBufferIndex = 1 - m_currentBufferIndex;
}

C_SCREENBUFFER* Nahoo::C_RENDERER::GetCurrentBuffer()
{
	return m_screenBuffers[m_currentBufferIndex];
}
