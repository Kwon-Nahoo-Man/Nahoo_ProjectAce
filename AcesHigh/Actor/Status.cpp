#include "Status.h"

C_STATUS::C_STATUS(const char* fileName, Nahoo::C_VECTOR2& position, Nahoo::E_COLOR color)
	:C_UICLASS(fileName, position)
{
	m_sortingOrder = 30;
	m_color = color;
}

C_STATUS::~C_STATUS()
{

}
