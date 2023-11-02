// Copyright (C) 2023 Theo Niessink <theo@taletn.com>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.

#include <windows.h>
#include <string.h>

#pragma comment(lib, "user32.lib")

int APIENTRY WinMain(HINSTANCE const hInst, HINSTANCE const hPrevInst, LPSTR const lpCmdLine, const int nCmdShow)
{
	const char* pin = lpCmdLine;
	while (pin[0] == ' ') pin++;

	int len = (int)strlen(pin);
	while (len && pin[len - 1] == ' ') len--;
	if (!len) return 1;

	HANDLE const hMutex = CreateMutexA(NULL, FALSE, "2b93b074-0703-42ee-9916-bb0d0e3fbc98");
	if (!hMutex || GetLastError() == ERROR_ALREADY_EXISTS) return 1;

	HWND hWnd = NULL;
	DWORD delay = 1000, timer = 0;
	static const DWORD timeout = 30*1000;

	for (int idx = 0; timer < timeout;)
	{
		Sleep(delay);
		timer += delay;

		if (!hWnd)
		{
			hWnd = FindWindowA("Credential Dialog Xaml Host", NULL);
		}
		else if (idx < len)
		{
			const int c = pin[idx];
			PostMessageA(hWnd, WM_CHAR, c, (c << 16) | 1);
			if (!idx++) delay = 250;
		}
		else
		{
			const UINT enter = MapVirtualKeyA(VK_RETURN, MAPVK_VK_TO_VSC);
			PostMessageA(hWnd, WM_KEYDOWN, VK_RETURN, (enter << 16) | 1);
			PostMessageA(hWnd, WM_KEYUP, VK_RETURN, ((KF_UP | KF_REPEAT | enter) << 16) | 1);
			break;
		}
	}

	ReleaseMutex(hMutex);
	return timer >= timeout;
}
