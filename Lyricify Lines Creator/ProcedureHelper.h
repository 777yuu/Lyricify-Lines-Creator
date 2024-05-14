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

