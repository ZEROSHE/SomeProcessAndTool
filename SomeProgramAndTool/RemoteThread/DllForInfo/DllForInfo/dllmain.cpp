// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "MinHook.h"


#if defined _M_X64
#pragma comment(lib, "libMinHook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "libMinHook.x86.lib")
#endif

typedef int (WINAPI *MESSAGEBOXW)(HWND, LPCWSTR, LPCWSTR, UINT);

typedef int (WINAPI *GETPROADDRESS)(HMODULE, LPCSTR);

// Pointer for calling original MessageBoxW.
MESSAGEBOXW fpMessageBoxW = NULL;

GETPROADDRESS fpGetProAddress = NULL;

// Detour function which overrides MessageBoxW.
int WINAPI DetourMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
	OutputDebugString(L"Hook Success");
	return fpMessageBoxW(hWnd, L"Hooked!", lpCaption, uType);
}

int WINAPI DetourGetProAddress(HMODULE hModule, LPCSTR lpProcName)
{
	OutputDebugStringA(lpProcName);
	return fpGetProAddress(hModule, lpProcName);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize MinHook.
		if (MH_Initialize() != MH_OK)
		{
			return 1;
		}

		// Create a hook for MessageBoxW, in disabled state.
		if (MH_CreateHook(&GetProcAddress, &DetourGetProAddress,
			reinterpret_cast<LPVOID*>(&fpGetProAddress)) != MH_OK)
		{
			return 1;
		}

		//// or you can use the new helper function like this.
		////if (MH_CreateHookApiEx(
		////    L"user32", "MessageBoxW", &DetourMessageBoxW, &fpMessageBoxW) != MH_OK)
		////{
		////    return 1;
		////}

		// Enable the hook for MessageBoxW.
		if (MH_EnableHook(&GetProcAddress) != MH_OK)
		{
			return 1;
		}
		break;
		// Expected to tell "Hooked!".
		//MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

	case DLL_THREAD_ATTACH:break;
	case DLL_THREAD_DETACH:break;
	case DLL_PROCESS_DETACH:
		// Disable the hook for MessageBoxW.
		if (MH_DisableHook(&GetProcAddress) != MH_OK)
		{
			return 1;
		}

		// Expected to tell "Not hooked...".
		MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

		// Uninitialize MinHook.
		if (MH_Uninitialize() != MH_OK)
		{
			return 1;
		}
		break;
	}
	return TRUE;
}


