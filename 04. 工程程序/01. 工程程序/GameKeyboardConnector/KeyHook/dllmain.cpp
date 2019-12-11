// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "../Inlude/KeyHook.h"

HWND g_hMain = NULL;
HWND g_hTarget = NULL;
ULONG g_ulKeyValue = VK_SPACE;
HHOOK g_hkHook = NULL;                      //定义钩子句柄
HINSTANCE g_hInstance = NULL;                  //程序实例

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
		//MessageBox(0,"KBhook.dll被加载！","DllMain",MB_OK);
		break;
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
		//MessageBox(0,"卸载KBhook.dll！","DllMain",MB_OK);
        break;
    }

	g_hInstance = (HINSTANCE)hModule;          //得到DLL实例
    return TRUE;
}

LRESULT CALLBACK GetMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (VK_SPACE == wParam)
	{
		POINT ptPoint;
		GetCursorPos(&ptPoint);
		g_hTarget = ::WindowFromPoint(ptPoint);
		//g_hTarget = ::GetActiveWindow();
		//SendMessage(g_hMain, MAIN_WND_GETHWND_MESSAGE, wParam, lParam);
	}

	return CallNextHookEx(g_hkHook, code, wParam, lParam);
}

BOOL EnableKeyboardCapture(void)
{
	if (!(g_hkHook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)GetMsgProc, g_hInstance, 0)))
		return FALSE;
	return TRUE;

}

BOOL DisableKeyboardCapture(void)
{
	return UnhookWindowsHookEx(g_hkHook);
}

void SetMainWind(HWND hWnd)
{
	g_hMain = hWnd;
}

void SetGetWindowHwndKey(ULONG nKeyValue)
{
	g_ulKeyValue = nKeyValue;
}

HWND GetTargetWind(void)
{
	return g_hTarget;
}