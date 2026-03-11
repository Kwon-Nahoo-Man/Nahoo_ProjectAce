#include "Level/TestLevel.h"
#include "Actor/Player.h"
#include "Actor/Spawner.h"
#include "Engine/Engine.h"
#include "Actor/Status.h"
#include "Level/MainLevel.h"

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
	logo->SetColor(E_COLOR::White);
	logo->SetSortingOrder(0);


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

void C_TESTLEVEL::Tick(float deltaTime)
{
	C_LEVEL::Tick(deltaTime);

	if (m_gameEndFlag == true)
	{
		m_timer.Tick(deltaTime);
		if (m_timer.IsTimeOut())
		{
			Nahoo::C_ENGINE::GetInstance().SetNewLevel(new C_MAINLEVEL());
		}
	}

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

void C_TESTLEVEL::ReturnToMainMenu()
{
	m_gameEndFlag = true;
	m_timer.SetTargetTime(6.0f);
	C_UICLASS* finish = new C_UICLASS("dead.txt", C_VECTOR2::Zero);
	finish->SetPosition(C_VECTOR2((Nahoo::C_ENGINE::GetInstance().GetWidth() / 2) - (finish->GetActorWidth() / 2), (Nahoo::C_ENGINE::GetInstance().GetHeight() / 2) - (finish->GetActorHeight() / 2)));
	finish->SetColor(E_COLOR::BackgroundRed);
	finish->SetSortingOrder(2);
	AddNewUI(finish);

	finish = new C_UICLASS("eddie.txt", C_VECTOR2::Zero);
	finish->SetPosition(C_VECTOR2((Nahoo::C_ENGINE::GetInstance().GetWidth() / 2) - (finish->GetActorWidth() / 2), (Nahoo::C_ENGINE::GetInstance().GetHeight() / 2) - (finish->GetActorHeight() / 2) + 50));
	finish->SetColor(E_COLOR::Red | E_COLOR::ForegroundIntensity);
	finish->SetSortingOrder(2);
	AddNewUI(finish);
	
}


