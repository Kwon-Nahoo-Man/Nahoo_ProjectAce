#include <iostream>

#include "ScreenBuffer.h"
#include "Renderer.h"

Nahoo::C_SCREENBUFFER::C_SCREENBUFFER(const C_VECTOR2& screenSize)
	: m_screenSize(screenSize)
{
	m_buffer = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		nullptr,
		CONSOLE_TEXTMODE_BUFFER,
		nullptr
	);

	if (m_buffer == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(nullptr, "ScreenBuffer - Failed to create buffer", "Buffer create error.", MB_OK);
		__debugbreak();
	}

	SMALL_RECT rect;
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = static_cast<SHORT>(screenSize.m_x - 1);
	rect.Bottom = static_cast<SHORT>(screenSize.m_y - 1);

	if (SetConsoleWindowInfo(m_buffer, true, &rect) == false)
	{
		std::cerr << "Failed to set console Window info.\n";
		__debugbreak();
	}

	if (SetConsoleScreenBufferSize(m_buffer, screenSize) == false)
	{
		std::cerr << "Failed to set console Buffer size.\n";
		__debugbreak();
	}

	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(m_buffer, &info);

	info.bVisible = false;
	SetConsoleCursorInfo(m_buffer, &info);

}

Nahoo::C_SCREENBUFFER::~C_SCREENBUFFER()
{
	if (m_buffer != nullptr)
	{
		CloseHandle(m_buffer);
	}
}

void Nahoo::C_SCREENBUFFER::Clear()
{
	DWORD writtenCount{};

	FillConsoleOutputCharacterA(
		m_buffer,
		' ',
		m_screenSize.m_x * m_screenSize.m_y,
		C_VECTOR2::Zero,
		&writtenCount
	);
}

void Nahoo::C_SCREENBUFFER::Draw(CHAR_INFO* charInfo)
{
	SMALL_RECT writeRegion{};
	writeRegion.Left = 0;
	writeRegion.Top= 0;
	writeRegion.Right = static_cast<short>(m_screenSize.m_x - 1);
	writeRegion.Bottom = static_cast<short>(m_screenSize.m_y - 1);

	WriteConsoleOutputA(m_buffer, charInfo, m_screenSize, C_VECTOR2::Zero, &writeRegion);
}
