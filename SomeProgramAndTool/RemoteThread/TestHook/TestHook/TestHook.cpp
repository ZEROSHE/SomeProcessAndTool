// TestHook.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	HMODULE H = LoadLibrary(L"Kernel32.dll");
	GetProcAddress(H, "Sleep");
	return 0;
}

