/************************************************************************
 * Filename:    DpiHelper.h
 * Description: DPI ������������
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

// ���֧�� Windows 7
#define WINVER 0x0601
#define _WIN32_WINNT 0x0601

#include <shellscalingapi.h>
#include "WinUser.h"
#include <Windows.h>

/// <summary>
/// ���� DPI ��֪ (�����Զ����� DPI)
/// </summary>
void EnableDpiAwareness();

/// <summary>
/// ��ȡ DPI ֵ
/// </summary>
/// <returns>DPI ֵ (Ĭ��Ϊ 96)</returns>
int GetDpi();

/// <summary>
/// ��ȡ DPI ���ű�
/// </summary>
/// <returns>DPI ���ű� (Ĭ��Ϊ 1.0)</returns>
double GetDpiScale();
