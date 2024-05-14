#include "LyricsHelper.h"

namespace Lyricify
{
	std::vector<std::wstring> LyricsHelper::ReadTextToLines(std::wstring filePath)
	{
        std::ifstream inputFile(filePath);

        if (!inputFile) // 文件流创建失败
        {
            return std::vector<std::wstring>(); // 返回空列表
        }

        std::vector<std::wstring> lines;

        std::string line;
        while (std::getline(inputFile, line))
        {
            auto ws = StringHelper::StringToWstring(line);
            if (StringHelper::IsEmptyOrWhiteSpace(ws)) continue; // 丢弃空行
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

		// 分割输入为每一行
		std::wistringstream iss(raw);
		std::wstring line;
		while (std::getline(iss, line))
		{
			// 检查是否是歌词行
			if (line.find(L"[") != std::wstring::npos && line.find(L"]") != std::wstring::npos)
			{
				// 获取起始时间和结束时间
				size_t startPos = line.find(L"[");
				size_t endPos = line.find(L"]");
				std::wstring timeStr = line.substr(startPos + 1, endPos - startPos - 1);
				if (timeStr[0] < '0' || timeStr[1] > '9') continue;// 可能是头部信息行，跳过

				// 获取首尾时间
				size_t commaPos = timeStr.find(L",");
				int startTime = -1, endTime = -1;
				try
				{
					startTime = std::stoi(timeStr.substr(0, commaPos));
					endTime = std::stoi(timeStr.substr(commaPos + 1));
				}
				catch (...)
				{
					continue; // 出错了，跳过该行
				}

				// 获取歌词文本
				std::wstring text = line.substr(endPos + 1);

				// 创建 Lyrics 对象并添加到列表中
				list.push_back(Lyricify::Lyrics(StringHelper::Trim(text), startTime, endTime));
			}
		}

		return list;
	}

	std::wstring LyricsHelper::GenerateLyricifyLinesFromLyricsList(std::vector<Lyricify::Lyrics> lyrics)
	{
		if (lyrics.size() < 1) return L"";

		std::wstring result = L"[type:LyricifyLines]\n";
		for (const auto& lyric : lyrics)
		{
			result += L"[" + std::to_wstring(lyric.StartTime) + L"," + (lyric.EndTime != -1 ? std::to_wstring(lyric.EndTime) : L"-1") + L"]" + lyric.Text + L"\n";
		}
		return result;
	}
}
