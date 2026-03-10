#include "Level/TestLevel.h"
#include "Actor/Player.h"
#include "Actor/Spawner.h"
#include "Engine/Engine.h"
#include "Actor/Status.h"

C_TESTLEVEL::C_TESTLEVEL()
	:C_LEVEL(true)
{
	AddNewActor(new C_SPAWNER());
	C_VECTOR2 position1{};
	position1.m_x = 10;
	position1.m_y = Nahoo::C_ENGINE::GetInstance().GetHeight() - 30;
	

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

	menu = new C_UICLASS(("quitGame.txt"), position);
	AddNewUI(menu);
	position.m_x = (Nahoo::C_ENGINE::GetInstance().GetWidth() / 2) - (menu->GetActorWidth() / 2);
	position.m_y = (Nahoo::C_ENGINE::GetInstance().GetHeight() / 2) - (menu->GetActorHeight() / 2) + 80;
	menu->SetPosition(position);

	for (int i = 0; i < 10; i += 2)
	{
		heartUI[i] = new C_STATUS("leftHeart.txt", position1,E_COLOR::BackgroundRed | E_COLOR::Red);
		AddNewUI(heartUI[i]);
		position1.m_x += 11;
		heartUI[i+1] = new C_STATUS("rightHeart.txt", position1, E_COLOR::BackgroundRed | E_COLOR::Red);
		AddNewUI(heartUI[i+1]);
		position1.m_x += 11;
	}
	
	position1.m_x = Nahoo::C_ENGINE::GetInstance().GetWidth() - 30;

	for (int i = 0; i < 3; i++)
	{
		specialAttackUI[i] = new C_STATUS("specialAttackUI.txt", position1, E_COLOR::BackgroundWhite | E_COLOR::White);
		AddNewUI(specialAttackUI[i]);
		position1.m_x -= 15;
	}

	position1.m_x = Nahoo::C_ENGINE::GetInstance().GetWidth() / 2 - 22;
	position1.m_y = Nahoo::C_ENGINE::GetInstance().GetHeight() - 50;

	C_PLAYER* test2{};
	test2 = new C_PLAYER("player_plane1.txt", position1, true, E_COLOR::Green | E_COLOR::ForegroundIntensity | E_COLOR::BackgroundGreen, 11, 100, 10, 0.3f);
	AddNewActor(test2);

}

C_TESTLEVEL::~C_TESTLEVEL()
{

}

void C_TESTLEVEL::UpdatePlayerHealthUI(int currentHealth)
{
	for (int i = 0; i < 10; i++)
	{
		heartUI[i]->SetActive(false);
	}
	
	for (int i = 0; i < currentHealth; i++)
	{
		heartUI[i]->SetActive(true);
	}
}

void C_TESTLEVEL::UpdatePlayerSpecialAttackUI(int currentSpecialAttack)
{
	for (int i = 0; i < 3; i++)
	{
		specialAttackUI[i]->SetActive(false);
	}

	for (int i = 0; i < currentSpecialAttack; i++)
	{
		specialAttackUI[i]->SetActive(true);
	}
}


