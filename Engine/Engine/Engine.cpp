#include <Windows.h>
#include <iostream>

#include "Engine.h"
#include "Core/Input.h"
#include "Level/Level.h"
#include "Util/Util.h"
#include "Renderer/Renderer.h"

//using namespace Nahoo;

Nahoo::C_ENGINE* Nahoo::C_ENGINE::m_instance = nullptr;

Nahoo::C_ENGINE::C_ENGINE()
{
	m_instance = this;
	m_input = new C_INPUT();
	LoadEngineSetting();

	m_renderer = new C_RENDERER(C_VECTOR2(m_engineSetting.width, m_engineSetting.height));

	UTIL::SetCursorAppear(false);

	UTIL::SetRandomSeed();
}

Nahoo::C_ENGINE::~C_ENGINE()
{
	if (m_mainLevel != nullptr)
	{
		delete m_mainLevel;
		m_mainLevel = nullptr;
	}

	if (m_input != nullptr)
	{
		delete m_input;
		m_input = nullptr;
	}

	if (m_renderer != nullptr)
	{
		delete m_renderer;
		m_renderer = nullptr;
	}
}

void Nahoo::C_ENGINE::Run()
{

	LARGE_INTEGER frequency{};
	QueryPerformanceFrequency(&frequency);

	LONGLONG previousTime{};
	LONGLONG currentTime{};

	LARGE_INTEGER time{};
	QueryPerformanceCounter(&time);

	currentTime = time.QuadPart;
	previousTime = currentTime;

	//float targetFrameRate{120.0f};

	if (m_engineSetting.targetFrameRate == 0)
	{
		m_engineSetting.targetFrameRate = 60.0f;
	}
	float oneFrameTime = 1.0f / m_engineSetting.targetFrameRate;


	while (m_isQuit == false)
	{
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		float deltaTime{};
		deltaTime = static_cast<float>(currentTime - previousTime);
		deltaTime = deltaTime / static_cast<float>(frequency.QuadPart);

		if (deltaTime >= oneFrameTime)
		{
			m_input->ProcessInput();

			BeginPlay();
			Tick(deltaTime);
			Draw();

			previousTime = currentTime;

			m_input->SavePreviousInputState();

			if (m_mainLevel != nullptr)
			{
				m_mainLevel->ProcessActors();
			}
		}

	}
	ShutDown();
}

void Nahoo::C_ENGINE::SetNewLevel(C_LEVEL* newLevel)
{

	// Todo: 레벨 바뀔 때 바로 바꾸면 안됨.
	if (m_mainLevel != nullptr)
	{
		delete m_mainLevel;
		m_mainLevel = nullptr;
	}

	m_mainLevel = newLevel;
}

Nahoo::C_ENGINE& Nahoo::C_ENGINE::GetInstance()
{
	if (m_instance == nullptr)
	{
		std::cout << "Error: C_ENGINE::GetInstance(). No Engine Instance.\n";
		__debugbreak();
	}

	return *m_instance;
}

void Nahoo::C_ENGINE::LoadEngineSetting()
{
	FILE* file = nullptr;
	fopen_s(&file, "../Config/Config.txt", "rt");

	if (file == nullptr)
	{
		std::cout << "Failed To Load File(Engine Load Settings).\n";
		__debugbreak();
		return;
	}

	char buffer[2048]{};

	size_t readSize = fread(buffer, sizeof(char), 2048, file);

	char* context{};
	char* token{};

	token = strtok_s(buffer, "\n", &context);

	while (token)
	{
		char header[20]{};

		sscanf_s(token, "%s", header, 20);

		if (strcmp(header, "targetFrameRate") == 0)
		{
			sscanf_s(token, "targetFrameRate = %f", &m_engineSetting.targetFrameRate);
		}
		else if (strcmp(header, "width") == 0)
		{
			sscanf_s(token, "width = %d", &m_engineSetting.width);
		}
		else if (strcmp(header, "height") == 0)
		{
			sscanf_s(token, "height = %d", &m_engineSetting.height);
		}

		token = strtok_s(nullptr, "\n", &context);
	}

	fclose(file);
}

void Nahoo::C_ENGINE::BeginPlay()
{
	if (m_mainLevel == nullptr)
	{
		std::cout << "Main level is empty. (Engine::BeginPlay())\n";
		return;
	}
	m_mainLevel->BeginPlay();
}

void Nahoo::C_ENGINE::Tick(float deltatime)
{
	if (m_mainLevel == nullptr)
	{
		std::cout << "Error: Engine::Tick(). Main Level is empty.\n";
		return;
	}
	m_mainLevel->Tick(deltatime);
}

void Nahoo::C_ENGINE::Draw()
{
	if (m_mainLevel == nullptr)
	{
		std::cout << "Error: Engine::Draw(). Main Level is empty.\n";
		return;
	}
	// 엔진 draw -> 레벨 draw -> 액터 draw(정보 submit)
	m_mainLevel->Draw();

	m_renderer->Draw();
}

void Nahoo::C_ENGINE::ShutDown()
{
	std::cout << "C_ENGINE::Run() Out\n";

	UTIL::SetCursorAppear(true);

}

void Nahoo::C_ENGINE::QuitEngine()
{
	m_isQuit = true;
}
