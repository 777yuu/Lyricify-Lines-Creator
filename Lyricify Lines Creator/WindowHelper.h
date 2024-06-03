/************************************************************************
 * Filename:    WindowHelper.h
 * Description: ���ڰ����ඨ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

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
