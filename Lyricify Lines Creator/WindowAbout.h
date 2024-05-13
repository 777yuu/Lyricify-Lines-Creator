#pragma once

#include <thread>
#include "CommonDefine.h"

class WindowAbout
{
private:
	/// <summary>
	/// �򿪴���
	/// </summary>
	/// <param name="isOpened">�����Ƿ��Ѿ��ر�</param>
	/// <param name="DPI_Scale">DPI ���ű�</param>
	/// <param name="rect">���������򣬲����������λ��</param>
	static void OpenWindow(bool* isOpened, double DPI_Scale, RECT rect = { -1, -1, -1, -1 });

public:
	/// <summary>
	/// ��ʾ���ڴ���
	/// </summary>
	/// <param name="DPI_Scale">DPI ���ű�</param>
	/// <param name="rect">���������򣬲����������λ��</param>
	static void Show(double DPI_Scale = 1, RECT rect = { -1, -1, -1, -1 });
};