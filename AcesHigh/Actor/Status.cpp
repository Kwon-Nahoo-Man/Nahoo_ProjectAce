#include "Status.h"




C_STATUS::C_STATUS(const char* fileName, Nahoo::C_VECTOR2& position, Nahoo::E_COLOR color)
	:C_ACTOR(fileName,position, false)
{
	m_sortingOrder = 30;
	m_color = color;
}

C_STATUS::~C_STATUS()
{

}

void C_STATUS::Tick(float deltaTime)
{
	C_ACTOR::Tick(deltaTime);
}

void C_STATUS::Draw()
{
	if (m_isPaint == true)
	{
		C_ACTOR::Draw();
	}
}

void C_STATUS::SetPaint(bool isPaint)
{
	m_isPaint = isPaint;
}
