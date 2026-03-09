#include "Actor/Actor.h"
#include "RenderComponent.h"
#include "Core/ResourceManager.h"
#include "Renderer/Renderer.h"



void Nahoo::COMP_RENDER::BeginPlay()
{
	if (m_hasBeganPlay == true)
	{
		return;
	}
	COMP_COMPONENT::BeginPlay();
	SetRenderInfo(m_owner->GetFilePath(), m_owner->GetColor(), m_owner->GetSortingOrder());

	bool result = Nahoo::C_RESOURCEMANAGER::GetInstance().GetData(m_filePath, m_sprite, m_width, m_height);
	if (result == false)
	{
		// 액터 파일 얻어오기 실패
		__debugbreak();
	}

	m_isActive = true;

}

void Nahoo::COMP_RENDER::Destroy()
{
	m_destroyRequested = true;
}



void Nahoo::COMP_RENDER::Draw()
{
	if (IsActive() == true)
	{
		Nahoo::C_RENDERER::GetInstance().Submit(m_sprite, m_width, m_height, m_owner->GetPosition(), m_color, m_sortingOrder);
	}
}

bool Nahoo::COMP_RENDER::SetRenderInfo(const std::string& filePath, E_COLOR color, int sortingOrder)
{
	if (filePath.empty() == true)
	{
		return false;
	}
	
	if (m_filePath == filePath)
	{
		return true;
	}
	
	// 액터 beginPlay든 sprite update할 때든 이걸 호출해야함
	m_filePath = filePath;
	m_color = color;
	m_sortingOrder = sortingOrder;

	bool result = Nahoo::C_RESOURCEMANAGER::GetInstance().GetData(m_filePath, m_sprite, m_width, m_height);
	if (result == true)
	{
		m_owner->SetActorWidthHeight(m_width, m_height);
	}
	return result;

}

void Nahoo::COMP_RENDER::SetActive(bool isActive)
{
	m_isActive = isActive;
}


bool Nahoo::COMP_RENDER::IsActive() const
{
	if (m_isActive == false)
	{
		return false;
	}
	if (m_destroyRequested == true)
	{
		return false;
	}
	if (m_sprite.empty() == true)
	{
		return false;
	}

	return true;
}

