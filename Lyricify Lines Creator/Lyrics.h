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
		std::string Text;

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
		{
			Text = "";
			StartTime = -1;
			EndTime = -1;
		}

		Lyrics(std::string text)
		{
			Text = text;
			StartTime = -1;
			EndTime = -1;
		}

		Lyrics(std::string text, int start)
		{
			Text = text;
			StartTime = start;
			EndTime = -1;
		}

		Lyrics(std::string text, int start, int end)
		{
			Text = text;
			StartTime = start;
			EndTime = end;
		}
	};
}
