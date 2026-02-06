#include <Windows.h>
#include <iostream>

#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Component/HitComponent.h"


Nahoo::C_ACTOR::C_ACTOR()
{

}

Nahoo::C_ACTOR::C_ACTOR(const char* fileName, const C_VECTOR2& position, E_COLOR color, bool collision)
	: m_position(position.m_x, position.m_y), m_color(color), m_collision(collision)
{
	// 액터 생성자에서 width와 height 계산, 출력용 텍스트 1차원 배열(vector) 설정
	// Todo: 현재는 vector가 char자료형이라 문자만 받는데 텍스트 하나 별로 색을 받기 위해선 CHAR_INFO 자료형 이어야함

	char path[2048]{};
	sprintf_s(path, 2048, "../Assets/%s", fileName);

	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	if (!file)
	{
		// 표준 오류 콘솔 활용.
		std::cerr << "Failed to open map file.\n";

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


	// Actor 생성자가 끝나면, HitComponent는 생성됨.
	if (m_collision == true)
	{
		MakeHitComponent();
	}

}

Nahoo::C_ACTOR::~C_ACTOR()
{
	if (m_hitComponent != nullptr)
	{
		delete m_hitComponent;
		m_hitComponent = nullptr;
	}

	OnDestroy();
}

void Nahoo::C_ACTOR::BeginPlay()
{
	m_hasBegunPlay = true;
}

void Nahoo::C_ACTOR::Tick(float deltaTime)
{
	// hit comp -> tick(deltaTime)
	m_hitComponent->Tick(deltaTime);

}

void Nahoo::C_ACTOR::Draw()
{
	Nahoo::C_RENDERER::GetInstance().Submit
	(
		m_sprite, m_width, m_height, m_position, m_color, m_sortingOrder
	);
}

void Nahoo::C_ACTOR::OnHit(size_t otherActorType) 
{
	// 액터가 충돌판정 받았을 때 로직, otherActorType는 조건식으로 사용
	// ex) Is(otherActorType) 



		
}

void Nahoo::C_ACTOR::Destroy()
{
	m_destroyRequested = true;
	m_hitComponent->Destroy();

	OnDestroy();
}

void Nahoo::C_ACTOR::OnDestroy()
{

}

void Nahoo::C_ACTOR::QuitGame()
{
	
}

void Nahoo::C_ACTOR::SetPosition(const C_VECTOR2& newPosition)
{

	if (m_position != newPosition)
	{
		m_position = newPosition;
	}

}

void Nahoo::C_ACTOR::MakeHitComponent()
{
	
	if (m_hitComponent == nullptr)
	{
		m_hitComponent = new COMP_HITCOMPONENT(m_position, m_width, m_height);
		m_hitComponent->SetOwner(this);
	}

}

