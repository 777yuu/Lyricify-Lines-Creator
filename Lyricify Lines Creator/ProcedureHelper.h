/************************************************************************
 * Filename:    ProcedureHelper.h
 * Description: �ص������ඨ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <map>
#include <Windows.h>

class ProcedureHelper
{
private:
	static std::map<HWND, WNDPROC> originalProcs;
	static std::map<HWND, WNDPROC> parentProcs;

	static LRESULT CALLBACK ControlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	/// <summary>
	/// ���ؼ��ļ��̰����ص��������ؼ�
	/// </summary>
	/// <param name="hControl">�ؼ����</param>
	/// <param name="wParent">���ؼ����</param>
	static void TransKeyMsgToParent(HWND hControl, WNDPROC wParent);
};

