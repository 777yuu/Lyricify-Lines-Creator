#pragma once

#include <Windows.h>

class WindowHelper
{
public:
    /// <summary>
    /// ���ô��ڵ���С����ť
    /// </summary>
    /// <param name="hWnd">���ھ��</param>
    /// <param name="enable">�Ƿ�����</param>
    static void EnableMinimizeButton(HWND hWnd, bool enable);
};
