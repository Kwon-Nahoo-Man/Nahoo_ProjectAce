#include "Effect.h"
#include "Core/ResourceManager.h"
#include "Renderer/Renderer.h"

void Nahoo::C_EFFECT::InitializeEffect(std::vector<std::string>& fileNames, const C_VECTOR2& position, float frameDuration, E_COLOR color, int sortingOrder)
{
	if (m_isActive == true)
	{
		return;
	}
	
	m_timer.Reset();

	m_fileNames = fileNames;
	
	m_maxIndex = static_cast<int>(m_fileNames.size() - 1);
	if (m_maxIndex < 0)
	{
		__debugbreak();
	}
	m_currentIndex = 0;

	m_timer.SetTargetTime(frameDuration / (m_maxIndex + 1));


	bool result = Nahoo::C_RESOURCEMANAGER::GetInstance().GetData(m_fileNames[m_currentIndex], m_sprite, m_width, m_height);
	if (result == false)
	{
		__debugbreak();
	}
	
	m_positionOrigin = position;
	m_position.m_x = m_positionOrigin.m_x - (m_width / 2);
	m_position.m_y = m_positionOrigin.m_y + 2;


	m_color = color;
	m_sortingOrder = sortingOrder;

	m_isActive = true;
}

void Nahoo::C_EFFECT::Tick(float deltaTime)
{
	if (m_isActive == false)
	{
		return;
	}
	
	
	m_timer.Tick(deltaTime);
	if (m_timer.IsTimeOut() == true && m_currentIndex < m_maxIndex)
	{
		++m_currentIndex;
		UpdateSprite();
		m_timer.Reset();
	}
	else if (m_timer.IsTimeOut() == true && m_currentIndex >= m_maxIndex)
	{
		Disappear();
	}
}

void Nahoo::C_EFFECT::Draw()
{
	if (m_isActive == false)
	{
		return;
	}

	Nahoo::C_RENDERER::GetInstance().Submit(m_sprite, m_width, m_height, m_position, m_color, m_sortingOrder);

}

void Nahoo::C_EFFECT::Disappear()
{
	m_isActive = false;
}

bool Nahoo::C_EFFECT::UpdateSprite()
{
	bool result = Nahoo::C_RESOURCEMANAGER::GetInstance().GetData(m_fileNames[m_currentIndex], m_sprite, m_width, m_height);
	if (result == false)
	{
		__debugbreak();
	}
	m_position.m_x = m_positionOrigin.m_x - (m_width / 2);
	m_position.m_y = m_positionOrigin.m_y - (m_height / 2);

	return result;
}
