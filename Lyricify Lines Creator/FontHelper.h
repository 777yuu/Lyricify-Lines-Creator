/************************************************************************
 * Filename:    FontHelper.h
 * Description: ��������ඨ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <string>
#include <Windows.h>

class FontHelper
{
public:
	/// <summary>
	/// ��ȡ�ı���ʵ����Ⱦ�ߴ�
	/// </summary>
	/// <param name="text">�ı��ַ���</param>
	/// <param name="fontName">������</param>
	/// <param name="fontSize">�ֺ�</param>
	/// <param name="dpiScale">DPI ���ű�</param>
	/// <param name="fontWeight">����</param>
	/// <param name="italic">б��</param>
	/// <param name="underline">�»���</param>
	/// <param name="strikeout">ɾ����</param>
	/// <returns>�ı���ʵ����Ⱦ�ߴ�</returns>
	static SIZE CalculateTextSize(const wchar_t* text, const wchar_t* fontName, int fontSize, int dpiScale = 1, int fontWeight = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false);
};
