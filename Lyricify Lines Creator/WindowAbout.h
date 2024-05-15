#pragma once

#include <thread>
#include <Windows.h>
#include "CommonDefine.h"
#include "FontHelper.h"
#include "StringHelper.h"
#include "TaskHelper.h"
#include "WindowHelper.h"

namespace WindowAbout
{
	/// <summary>
	/// ��ʾ���ڴ���
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
