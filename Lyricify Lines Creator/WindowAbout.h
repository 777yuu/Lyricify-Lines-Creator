#pragma once

#include <thread>
#include <Windows.h>
#include "CommonDefine.h"
#include "StringHelper.h"
#include "TaskHelper.h"

namespace WindowAbout
{
	/// <summary>
	/// 显示关于窗体
	/// </summary>
	/// <param name="DPI_Scale">DPI 缩放比</param>
	/// <param name="rect">父窗口区域，不传入则随机位置</param>
	/// <param name="hParent">父窗口句柄</param>
	void Show(double DPI_Scale = 1, RECT rect = { -1, -1, -1, -1 }, HWND hParent = (HWND)nullptr);

	/// <summary>
	/// 关于窗体是否正在显示
	/// </summary>
	bool IsOpened();
}
