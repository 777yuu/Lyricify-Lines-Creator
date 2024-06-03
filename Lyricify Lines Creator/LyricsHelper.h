/************************************************************************
 * Filename:    LyricsHelper.h
 * Description: ��ʰ����ඨ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <fstream>
#include <vector>
#include <string>
#include "Lyrics.h"
#include "StringHelper.h"

namespace Lyricify
{
	class LyricsHelper
	{
	public:
		/// <summary>
		/// ���ļ���ȡ�ı��д��� vector �б�
		/// </summary>
		/// <param name="filePath">�ļ�·��</param>
		/// <returns>����� vector �б���ʧ���򷵻ؿ��б�</returns>
		static std::vector<std::wstring> ReadTextToLines(std::wstring filePath);

		/// <summary>
		/// ���ı����б�����µ� Lyricify.Lyrics �� vector �б�
		/// </summary>
		/// <param name="lines">�ı��� vector �б�</param>
		/// <returns>����� vector �б�</returns>
		static std::vector<Lyricify::Lyrics> GetLyricsFromLines(std::vector<std::wstring> lines);

		/// <summary>
		/// ������ʵ��б�
		/// </summary>
		/// <param name="raw">ԭʼ Lyricify Lines ����ַ���</param>
		/// <returns>����б�</returns>
		static std::vector<Lyricify::Lyrics> ParseLyricsFromLyricifyLinesString(std::wstring raw);

		/// <summary>
		/// ���� Lyricify Lines ����ַ���
		/// </summary>
		/// <param name="lyrics">����б�</param>
		/// <returns>���ɵ��ַ���</returns>
		static std::wstring GenerateLyricifyLinesFromLyricsList(const std::vector<Lyricify::Lyrics>& lyrics);

		/// <summary>
		/// ���� LRC ����ַ���
		/// </summary>
		/// <param name="lyrics">����б�</param>
		/// <returns>���ɵ��ַ���</returns>
		static std::wstring GenerateLrcFromLyricsList(const std::vector<Lyricify::Lyrics>& lyrics);
	};
}
