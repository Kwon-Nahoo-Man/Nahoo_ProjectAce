#pragma once

#include "Level/Level.h"
#include "Util/Timer.h"
using namespace Nahoo;

class C_STATUS;

class C_TESTLEVEL : public C_LEVEL
{
	RTTI_DECLARATIONS(C_TESTLEVEL,C_LEVEL)


public:
	C_TESTLEVEL();
	~C_TESTLEVEL();

	virtual void Tick(float deltaTime) override;

	void UpdatePlayerHealthUI(int currentHealth);
	void UpdatePlayerSpecialAttackUI(int currentSpecialAttack);
	void ReturnToMainMenu();

public:
	C_STATUS* heartUI[10];
	C_STATUS* specialAttackUI[3];
	bool m_gameEndFlag{ false };
	UTIL::C_TIMER m_timer{};
};

