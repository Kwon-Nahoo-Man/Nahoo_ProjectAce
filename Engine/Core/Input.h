#pragma once
#include "Common/Common.h"

namespace Nahoo
{
	class NAHOO_API C_INPUT
	{
		friend class C_ENGINE;

		struct S_KEYSTATE
		{
			bool isKeyDown{ false };
			bool wasKeyDown{ false };
		};

	public:
		C_INPUT();
		~C_INPUT();

	public:
		bool GetKeyDown(int keycode);
		bool GeyKeyUp(int keycode);
		bool GetKey(int keycode);

		static C_INPUT& GetInstance();

	private:
		void ProcessInput();
		void SavePreviousInputState();


	private:
		static C_INPUT* m_instance;
		S_KEYSTATE m_keyStates[256]{};

		
	};
}
