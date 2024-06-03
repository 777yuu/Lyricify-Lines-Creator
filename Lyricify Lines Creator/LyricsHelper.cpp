/************************************************************************
 * Filename:    LyricsHelper.cpp
 * Description: ��ʰ�����ʵ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "LyricsHelper.h"

namespace Lyricify
{
	std::vector<std::wstring> LyricsHelper::ReadTextToLines(std::wstring filePath)
	{
        std::ifstream inputFile(filePath);

        if (!inputFile) // �ļ�������ʧ��
        {
            return std::vector<std::wstring>(); // ���ؿ��б�
        }

        std::vector<std::wstring> lines;

        std::string line;
        while (std::getline(inputFile, line))
        {
            auto ws = StringHelper::StringToWstring(line);
            if (StringHelper::IsEmptyOrWhiteSpace(ws)) continue; // ��������
            lines.push_back(StringHelper::Trim(ws));
        }

        inputFile.close();

        return lines;
	}

	std::vector<Lyricify::Lyrics> LyricsHelper::GetLyricsFromLines(std::vector<std::wstring> lines)
	{
        std::vector<Lyricify::Lyrics> list;

        for (uint32_t i = 0; i < lines.size(); i++)
        {
            Lyricify::Lyrics line(lines[i]);
            list.push_back(line);
        }

		return list;
	}

	std::vector<Lyricify::Lyrics> LyricsHelper::ParseLyricsFromLyricifyLinesString(std::wstring raw)
	{
		std::vector<Lyricify::Lyrics> list;

		// �ָ�����Ϊÿһ��
		std::wistringstream iss(raw);
		std::wstring line;
		while (std::getline(iss, line))
		{
			// ����Ƿ��Ǹ����
			if (line.find(L"[") != std::wstring::npos && line.find(L"]") != std::wstring::npos)
			{
				// ��ȡ��ʼʱ��ͽ���ʱ��
				size_t startPos = line.find(L"[");
				size_t endPos = line.find(L"]");
				std::wstring timeStr = line.substr(startPos + 1, endPos - startPos - 1);
				if (timeStr[0] < '0' || timeStr[1] > '9') continue;// ������ͷ����Ϣ�У�����

				// ��ȡ��βʱ��
				size_t commaPos = timeStr.find(L",");
				int startTime = -1, endTime = -1;
				try
				{
					startTime = std::stoi(timeStr.substr(0, commaPos));
					endTime = std::stoi(timeStr.substr(commaPos + 1));
				}
				catch (...)
				{
					continue; // �����ˣ���������
				}

				// ��ȡ����ı�
				std::wstring text = line.substr(endPos + 1);

				// ���� Lyrics ������ӵ��б���
				list.push_back(Lyricify::Lyrics(StringHelper::Trim(text), startTime, endTime));
			}
		}

		return list;
	}

	std::wstring LyricsHelper::GenerateLyricifyLinesFromLyricsList(const std::vector<Lyricify::Lyrics>& lyrics)
	{
		if (lyrics.size() < 1) return L"";

		std::wstring result = L"[type:LyricifyLines]\n";
		for (size_t i = 0; i < lyrics.size(); i++)
		{
			if (lyrics[i].StartTime == -1)
				break; // ����û����ʼʱ��ĸ�ʣ�ֱ�ӽ����ַ�������

			int startTime = lyrics[i].StartTime;
			int endTime = (lyrics[i].EndTime != -1) ? lyrics[i].EndTime : ((i + 1 < lyrics.size() && lyrics[i + 1].StartTime != -1) ? lyrics[i + 1].StartTime : 0);

			result += L"[" + std::to_wstring(startTime) + L"," + std::to_wstring(endTime) + L"]" + lyrics[i].Text + L"\n";
		}

		return result == L"[type:LyricifyLines]\n" ? L"" : StringHelper::TrimEnd(result);
	}

	/// <summary>
	/// ��ʽ��ʱ��Ϊ�ַ��������� LRC ���
	/// </summary>
	/// <param name="timeMs">ʱ�������</param>
	/// <returns>ʱ���ַ���</returns>
	static std::wstring FormatTime(int timeMs)
	{
		int minutes = timeMs / 60000;
		int seconds = (timeMs % 60000) / 1000;
		int hundredths = (timeMs % 1000) / 10;

		std::wostringstream oss;
		oss << L"[" << std::setfill(L'0') << std::setw(2) << minutes << L":"
			<< std::setfill(L'0') << std::setw(2) << seconds << L"."
			<< std::setfill(L'0') << std::setw(2) << hundredths << L"]";
		return oss.str();
	}

	std::wstring LyricsHelper::GenerateLrcFromLyricsList(const std::vector<Lyricify::Lyrics>& lyrics)
	{
		if (lyrics.empty()) return L"";

		std::wstring result;
		for (const auto& lyric : lyrics)
		{
			if (lyric.StartTime == -1)
				break; // ����û����ʼʱ��ĸ�ʣ�ֱ�ӽ����ַ�������

			result += FormatTime(lyric.StartTime) + lyric.Text + L"\n";
		}

		return result.empty() ? L"" : StringHelper::TrimEnd(result);
	}
}
