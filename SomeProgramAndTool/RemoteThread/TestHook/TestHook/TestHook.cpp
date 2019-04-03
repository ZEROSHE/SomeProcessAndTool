// TestHook.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	HMODULE H = LoadLibrary(L"Kernel32.dll");
	GetProcAddress(H, "Sleep");
	return 0;
}

