#include <iostream>
#include "Engine/Engine.h"
#include "Level/TestLevel.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Nahoo::C_ENGINE engine{};
	engine.SetNewLevel(new C_TESTLEVEL());
	engine.Run();

}

//HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//CONSOLE_FONT_INFOEX cfi{};
//cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
//cfi.nFont = 0;
//cfi.dwFontSize.X = 6;   // 글자 가로 크기
//cfi.dwFontSize.Y = 8;  // 글자 세로 크기
//cfi.FontFamily = FF_DONTCARE;
//cfi.FontWeight = FW_NORMAL;

//// 사용할 폰트 이름 (Consolas 추천)
//wcscpy_s(cfi.FaceName, L"Consolas");

//SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
