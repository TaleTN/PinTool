// Copyright (C) 2023 Theo Niessink <theo@taletn.com>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.

#include <windows.h>

#include <stdio.h>
#include <string.h>

#pragma comment(lib, "user32.lib")

int APIENTRY WinMain(HINSTANCE const hInst, HINSTANCE const hPrevInst, LPSTR const lpCmdLine, const int nCmdShow)
{
	const char* pin = lpCmdLine;
	while (pin[0] == ' ') pin++;

	int len = (int)strlen(pin);
	while (len && pin[len - 1] == ' ') len--;
	if (!len) return 1;

	HWND hWnd = NULL;
	HANDLE hMutex = NULL;

	DWORD delay = 100, timer = 0;
	static const DWORD timeout = 30*1000;
	static const int numTries = 2;

	for (int idx = 0, tries = 0; timer < timeout;)
	{
		Sleep(delay);
		timer += delay;

		if (!hWnd)
		{
			hWnd = FindWindowA("Credential Dialog Xaml Host", NULL);
			if (hWnd)
			{
				char name[256];
				_snprintf_s(name, sizeof(name), sizeof(name), "2b93b074-0703-42ee-9916-bb0d0e3fbc98_%p", hWnd);

				hMutex = CreateMutexA(NULL, FALSE, name);
				if (!hMutex || GetLastError() == ERROR_ALREADY_EXISTS) return 1;
				delay = 1000;
			}
		}
		else if (!IsWindow(hWnd))
		{
			break;
		}
		else if (idx < 0) // Waiting before retrying...
		{
			idx++;
		}
		else if (idx < len)
		{
			const int c = pin[idx++];
			PostMessageA(hWnd, WM_CHAR, c, (c << 16) | 1);
			delay = 250;
		}
		else
		{
			const UINT enter = MapVirtualKeyA(VK_RETURN, /* MAPVK_VK_TO_VSC */ 0);
			PostMessageA(hWnd, WM_KEYDOWN, VK_RETURN, (enter << 16) | 1);
			PostMessageA(hWnd, WM_KEYUP, VK_RETURN, ((KF_UP | KF_REPEAT | enter) << 16) | 1);

			if (++tries >= numTries) break;
			timer = 0;

			// Retry if dialog is still around in 30*100 ms.
			idx = -30; delay = 100;
		}
	}

	if (hMutex) CloseHandle(hMutex);
	return 0;
}
