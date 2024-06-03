/************************************************************************
 * Filename:    WindowPreviewOutput.h
 * Description: Ԥ��������巽������
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
#include "StringHelper.h"
#include "WindowHelper.h"

namespace WindowPreviewOutput
{
	/// <summary>
	/// ��ʾԤ���������
	/// </summary>
	/// <param name="DPI_Scale">DPI ���ű�</param>
	/// <param name="rect">���������򣬲����������λ��</param>
	/// <param name="hParent">�����ھ��</param>
	void Show(std::wstring filePath, std::wstring fileContent, double DPI_Scale = 1, RECT rect = { -1, -1, -1, -1 }, HWND hParent = (HWND)nullptr);

	/// <summary>
	/// Ԥ����������Ƿ�������ʾ
	/// </summary>
	bool IsOpened();
}
