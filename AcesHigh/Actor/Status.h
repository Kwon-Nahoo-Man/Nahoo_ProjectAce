#pragma once

#include "UI/UIClass.h"
#include "Math/Vector2.h"
#include "Common/RTTI.h"
#include "Enumeration/Color.h"

class C_STATUS : public Nahoo::C_UICLASS
{
	RTTI_DECLARATIONS(C_STATUS, C_UICLASS)

public:
	C_STATUS(const char* fileName, Nahoo::C_VECTOR2& position, Nahoo::E_COLOR color);
	~C_STATUS();

private:


};
