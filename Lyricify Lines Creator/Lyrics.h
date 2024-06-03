/************************************************************************
 * Filename:    Lyrics.h
 * Description: ����ඨ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <string>

namespace Lyricify
{
	class Lyrics
	{
	public:
		/// <summary>
		/// �����ԭ��
		/// </summary>
		std::wstring Text;

		/// <summary>
		/// �������ʼʱ��
		/// </summary>
		int StartTime;

		/// <summary>
		/// ����н���ʱ��<br/>
		/// �ر�ģ�������ʱ��Ϊ -1������Ϊû�����ý���ʱ�䣬Ӧ��������һ�е���ʼʱ��
		/// </summary>
		int EndTime;

		Lyrics()
			: Text(L""), StartTime(-1), EndTime(-1) {}

		Lyrics(std::wstring text)
			: Text(text), StartTime(-1), EndTime(-1) {}

		Lyrics(std::wstring text, int start)
			: Text(text), StartTime(start), EndTime(-1) {}

		Lyrics(std::wstring text, int start, int end)
			: Text(text), StartTime(start), EndTime(end) {}
	};
}
