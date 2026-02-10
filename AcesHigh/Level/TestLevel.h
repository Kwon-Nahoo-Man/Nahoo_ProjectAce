#pragma once

#include "Level/Level.h"

using namespace Nahoo;

class C_STATUS;

class C_TESTLEVEL : public C_LEVEL
{
	RTTI_DECLARATIONS(C_TESTLEVEL,C_LEVEL)


public:
	C_TESTLEVEL();
	~C_TESTLEVEL();

	void UpdatePlayerHealthUI(int currentHealth);
	void UpdatePlayerSpecialAttackUI(int currentSpecialAttack);

public:
	C_STATUS* heartUI[10];
	C_STATUS* specialAttackUI[3];

};

