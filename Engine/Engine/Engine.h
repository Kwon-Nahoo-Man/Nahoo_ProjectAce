#pragma once
#include "Common/Common.h"

namespace Nahoo
{
	class C_LEVEL;
	class C_INPUT;
	class C_RENDERER;

	class NAHOO_API C_ENGINE
	{
		struct S_ENGINESETTING
		{
			float targetFrameRate{};
			int width{};
			int height{};
		};

	public:
		C_ENGINE();
		virtual ~C_ENGINE();

	public:
		void QuitEngine();
		void Run();
		void SetNewLevel(C_LEVEL* newLevel);

		static C_ENGINE& GetInstance();

		int GetWidth();
		int GetHeight();

	protected:
		void LoadEngineSetting();
		void BeginPlay();
		void Tick(float deltatime);
		void Draw();
		void ShutDown();
		
	
	protected:
		bool m_isQuit{ false };
		S_ENGINESETTING m_engineSetting;
		C_LEVEL* m_mainLevel{};
		C_INPUT* m_input{};
		C_RENDERER* m_renderer{};

		static C_ENGINE* m_instance;

	};
}

 
