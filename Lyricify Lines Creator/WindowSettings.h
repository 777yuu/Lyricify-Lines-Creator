/************************************************************************
 * Filename:    WindowSettings.h
 * Description: ���ô��巽������
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <fstream>
#include <string>
#include <Windows.h>
#include "CommonDefine.h"
#include "FontHelper.h"
#include "StringHelper.h"
#include "WindowHelper.h"

namespace WindowSettings
{
	/// <summary>
	/// ��ʾ���ô���
	/// </summary>
	/// <param name="DPI_Scale">DPI ���ű�</param>
	/// <param name="rect">���������򣬲����������λ��</param>
	/// <param name="hParent">�����ھ��</param>
	void Show(double DPI_Scale = 1, RECT rect = { -1, -1, -1, -1 }, HWND hParent = (HWND)nullptr);

	/// <summary>
	/// ���ڴ����Ƿ�������ʾ
	/// </summary>
	bool IsOpened();
}
