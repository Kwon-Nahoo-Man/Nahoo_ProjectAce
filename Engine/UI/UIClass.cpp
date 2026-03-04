#include <iostream>

#include "UIClass.h"
#include "Renderer/Renderer.h"

namespace Nahoo
{

    C_UICLASS::C_UICLASS(const char* fileName, const C_VECTOR2& position)
		:m_position(position)
    {
		char path[2048]{};
		sprintf_s(path, 2048, "../Assets/%s", fileName);

		FILE* file = nullptr;
		fopen_s(&file, path, "rt");

		if (!file)
		{
			// 표준 오류 콘솔 활용.
			std::cerr << "Failed to Actor asset file.\n";

			// 디버그 모드에서 중단점으로 중단해주는 기능.
			__debugbreak();
		}

		fseek(file, 0, SEEK_END);
		size_t fileSize = ftell(file);
		rewind(file);

		char* data = new char[fileSize + 1] {};

		fread(data, sizeof(char), fileSize, file);

		char* context{};
		char* token{};

		m_sprite.reserve(fileSize);

		token = strtok_s(data, "\n", &context);
		m_width = static_cast<int>(strlen(token));

		while (token)
		{
			m_height++;
			for (int i = 0; i < m_width; i++)
			{
				m_sprite.push_back(token[i]);
			}
			token = strtok_s(nullptr, "\n", &context);
		}
		delete[] data;
		data = nullptr; // 필요없음

		fclose(file);
    }

    C_UICLASS::~C_UICLASS()
    {

    }

	void C_UICLASS::BeginPlay()
	{
		m_hasBegunPlay = true;
	}

	void C_UICLASS::Tick(float deltaTime)
	{
		
	}
	
	void C_UICLASS::Draw()
	{
		if (IsActive() == false)
		{
			return;
		}
		
		Nahoo::C_RENDERER::GetInstance().Submit(m_sprite, m_width, m_height, m_position, m_color, m_sortingOrder);
		
	}

	void C_UICLASS::Destroy()
	{
		m_destroyRequested = true;
	}

	void C_UICLASS::OnDestroy()
	{
		
	}

	void C_UICLASS::SetPosition(const C_VECTOR2& newPosition)
	{
		if (newPosition != m_position)
		{
			m_position = newPosition;
		}
	}
	
}