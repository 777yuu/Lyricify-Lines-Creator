#pragma once

#include <thread>
#include <Windows.h>
#include "CommonDefine.h"
#include "StringHelper.h"

namespace WindowAbout
{
	/// <summary>
	/// ��ʾ���ڴ���
	/// </summary>
	/// <param name="DPI_Scale">DPI ���ű�</param>
	/// <param name="rect">���������򣬲����������λ��</param>
	void Show(double DPI_Scale = 1, RECT rect = { -1, -1, -1, -1 });
}
