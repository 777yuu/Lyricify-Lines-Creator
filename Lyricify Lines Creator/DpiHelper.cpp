/************************************************************************
 * Filename:    DpiHelper.cpp
 * Description: DPI ��������ʵ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "DpiHelper.h"
#include <Windows.h>

void EnableDpiAwareness()
{
	HMODULE hShcore = LoadLibrary(L"Shcore.dll");
	if (hShcore != NULL)
	{
		typedef HRESULT(WINAPI* LPFNSPDPIA)(PROCESS_DPI_AWARENESS);
		LPFNSPDPIA lSetProcessDpiAwareness = (LPFNSPDPIA)GetProcAddress(hShcore, "SetProcessDpiAwareness");
		if (lSetProcessDpiAwareness != NULL)
		{
			HRESULT hr = lSetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
			if (!SUCCEEDED(hr)) SetProcessDPIAware();
		}
		else SetProcessDPIAware();

		FreeLibrary(hShcore);
	}
	else SetProcessDPIAware();
}

int GetDpi()
{
	// �������� Windows 10 1607
	/*HWND hwnd = GetDesktopWindow();
	return GetDpiForWindow(hwnd);*/

    return (int)(GetDpiScale() * 96);
}

double GetDpiScale()
{
    // ��ȡ���ڵ�ǰ��ʾ�ļ�����
    // ʹ������ľ��.
    HWND hWnd = GetDesktopWindow();
    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    // ��ȡ�������߼������߶�
    MONITORINFOEX miex;
    miex.cbSize = sizeof(miex);
    GetMonitorInfo(hMonitor, &miex);
    int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
    int cyLogical = (miex.rcMonitor.bottom - miex.rcMonitor.top);

    // ��ȡ��������������߶�
    DEVMODE dm;
    dm.dmSize = sizeof(dm);
    dm.dmDriverExtra = 0;
    EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
    int cxPhysical = dm.dmPelsWidth;
    int cyPhysical = dm.dmPelsHeight;

    // ���ű�������  ʵ����ʹ���κ�һ������
    double horzScale = ((double)cxPhysical / (double)cxLogical);
    double vertScale = ((double)cyPhysical / (double)cyLogical);
    return horzScale;
}