#include <Windows.h>
#include <iostream>

#include "Actor.h"
#include "Renderer/Renderer.h"


Nahoo::C_ACTOR::C_ACTOR()
{

}

Nahoo::C_ACTOR::C_ACTOR(const char* image, C_VECTOR2 position, E_COLOR color)
	: m_position(position.m_x, position.m_y), m_color(color)
{
	size_t length = strlen(image) + 1;
	m_image = new char[length];
	strcpy_s(m_image, length, image);
}

Nahoo::C_ACTOR::~C_ACTOR()
{
	if (m_image != nullptr)
	{
		delete[] m_image;
		m_image = nullptr;
	}
}

void Nahoo::C_ACTOR::BeginPlay()
{
	m_hasBegunPlay = true;
}

void Nahoo::C_ACTOR::Tick(float deltaTime)
{
	

}

void Nahoo::C_ACTOR::Draw()
{
	Nahoo::C_RENDERER::GetInstance().Submit(m_image, m_position, m_color, m_sortingOrder);
}

void Nahoo::C_ACTOR::SetPosition(const C_VECTOR2& newPosition)
{
	
	if (m_position != newPosition)
	{
		m_position = newPosition;
	}

}

