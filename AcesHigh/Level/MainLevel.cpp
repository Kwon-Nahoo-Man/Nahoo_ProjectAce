#include <Windows.h>

#include "MainLevel.h"
#include "Core/Input.h"
#include "Renderer/Renderer.h"
#include "UI/UIClass.h"
#include "Engine/Engine.h"

C_MAINLEVEL::C_MAINLEVEL()
	:C_LEVEL()
{
	C_VECTOR2 position{};

	C_UICLASS* logo = new C_UICLASS(("logo.txt"), position);
	AddNewUI(logo);
	position.m_x = (Nahoo::C_ENGINE::GetInstance().GetWidth() / 2) - (logo->GetActorWidth() / 2);
	position.m_y = (Nahoo::C_ENGINE::GetInstance().GetHeight() / 2) - (logo->GetActorHeight() / 2) - 80;
	logo->SetPosition(position);
	logo->SetColor(E_COLOR::BackgroundWhite | E_COLOR::BackgroundIntensity);



	C_UICLASS* menu = new C_UICLASS(("startGame.txt"), position);
	AddNewUI(menu);
	position.m_x = (Nahoo::C_ENGINE::GetInstance().GetWidth() / 2) - (menu->GetActorWidth() / 2);
	position.m_y = (Nahoo::C_ENGINE::GetInstance().GetHeight() / 2) - (menu->GetActorHeight() / 2) + 30;
	menu->SetPosition(position);
	m_menus.push_back(menu);

	menu = new C_UICLASS(("quitGame.txt"), position);
	AddNewUI(menu);
	position.m_x = (Nahoo::C_ENGINE::GetInstance().GetWidth() / 2) - (menu->GetActorWidth() / 2);
	position.m_y = (Nahoo::C_ENGINE::GetInstance().GetHeight() / 2) - (menu->GetActorHeight() / 2) + 80;
	menu->SetPosition(position);
	m_menus.push_back(menu);

	SetMenuColor(m_currentMenuIndex);

}

C_MAINLEVEL::~C_MAINLEVEL()
{

}

void C_MAINLEVEL::Tick(float deltaTIme)
{
	C_LEVEL::Tick(deltaTIme);

	if (C_INPUT::GetInstance().GetKeyDown(VK_DOWN))
	{
		m_currentMenuIndex++;
		if (m_currentMenuIndex >= m_menus.size())
		{
			m_currentMenuIndex = 0;
		}
		SetMenuColor(m_currentMenuIndex);
	}
	
	if (C_INPUT::GetInstance().GetKeyDown(VK_UP))
	{
		m_currentMenuIndex--;
		if (m_currentMenuIndex < 0)
		{
			m_currentMenuIndex = static_cast<int>(m_menus.size()-1);
		}
		SetMenuColor(m_currentMenuIndex);
	}

	if (C_INPUT::GetInstance().GetKeyDown(VK_RETURN))
	{
		SelectMenu();
	}



}

void C_MAINLEVEL::SetMenuColor(int selectedIndex)
{
	for (int i = 0; i < m_menus.size(); i++)
	{
		if (i == selectedIndex)
		{
			m_menus[i]->SetColor(m_selectedColor);
		}
		else
		{
			m_menus[i]->SetColor(m_unselectedColor);
		}
	}


}

void C_MAINLEVEL::SelectMenu()
{
	if (m_currentMenuIndex == 0)
	{
		// TestLevel 로 전환
	}
	else if(m_currentMenuIndex == 1)
	{
		// 엔진 종료
	}


}
