#pragma once

#include <fstream>
#include <string>
#include <Windows.h>
#include "CommonDefine.h"
#include "FontHelper.h"
#include "Lyrics.h"
#include "MusicPlayer.h"
#include "StringHelper.h"
#include "WindowHelper.h"

namespace WindowPreviewLyrics
{
	/// <summary>
	/// ��ʾ���ڴ���
	/// </summary>
	/// <param name="DPI_Scale">DPI ���ű�</param>
	/// <param name="rect">���������򣬲����������λ��</param>
	/// <param name="hParent">�����ھ��</param>
	void Show(std::vector<Lyricify::Lyrics> lyricsList, double DPI_Scale = 1, RECT rect = { -1, -1, -1, -1 }, HWND hParent = (HWND)nullptr);

	/// <summary>
	/// ���ڴ����Ƿ�������ʾ
	/// </summary>
	bool IsOpened();
}
