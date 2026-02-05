#include <iostream>
#include <Windows.h>

#include "Input.h"

Nahoo::C_INPUT* Nahoo::C_INPUT::m_instance = nullptr;

Nahoo::C_INPUT::C_INPUT()
{
	m_instance = this;
}

Nahoo::C_INPUT::~C_INPUT()
{

}

bool Nahoo::C_INPUT::GetKeyDown(int keycode)
{
	return m_keyStates[keycode].isKeyDown && !m_keyStates[keycode].wasKeyDown;
}

bool Nahoo::C_INPUT::GeyKeyUp(int keycode)
{
	return !m_keyStates[keycode].isKeyDown && m_keyStates[keycode].wasKeyDown;
}

bool Nahoo::C_INPUT::GetKey(int keycode)
{
	return m_keyStates[keycode].isKeyDown;
}

Nahoo::C_INPUT& Nahoo::C_INPUT::GetInstance()
{
	if (m_instance == nullptr)
	{
		std::cout << "Error: C_INPUT::GetInstance() No Input Instance.\n";
		__debugbreak();
	}

	return *m_instance;

}

void Nahoo::C_INPUT::ProcessInput()
{
	for (int i = 0; i < 256; i++)
	{
		if ((GetAsyncKeyState(i) & 0x8000) > 0)
		{
			m_keyStates[i].isKeyDown = true;
		}
		else
		{
			m_keyStates[i].isKeyDown = false;
		}
	}
}

void Nahoo::C_INPUT::SavePreviousInputState()
{
	for (int i = 0; i < 256; i++)
	{
		m_keyStates[i].wasKeyDown = m_keyStates[i].isKeyDown;
	}
}
