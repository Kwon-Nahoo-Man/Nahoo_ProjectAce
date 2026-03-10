#pragma once

#include "Level/Level.h"
#include "Enumeration/Color.h"


using namespace Nahoo;


class C_MAINLEVEL : public C_LEVEL
{
public:

	C_MAINLEVEL();
	~C_MAINLEVEL();

	C_MAINLEVEL(const C_MAINLEVEL&) = delete;
	const C_MAINLEVEL& operator=(const C_MAINLEVEL&) = delete;

	virtual void Tick(float deltaTIme) override;

private:
	void SetMenuColor(int selectedIndex);
	void SelectMenu();

private:

	int m_currentMenuIndex{};

	E_COLOR m_selectedColor = E_COLOR::BackgroundGreen | E_COLOR::BackgroundIntensity;
	E_COLOR m_unselectedColor = E_COLOR::BackgroundWhite | E_COLOR::BackgroundIntensity;

	std::vector<C_UICLASS*> m_menus{};








};