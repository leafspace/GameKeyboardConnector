#pragma once;

#include <iostream>

#define MAIN_WND_GETHWND_MESSAGE (WM_USER + 1)

BOOL EnableKeyboardCapture(void);
BOOL DisableKeyboardCapture(void);

void SetMainWind(HWND hWnd);
void SetGetWindowHwndKey(ULONG nKeyValue);
HWND GetTargetWind(void);