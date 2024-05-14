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

		// TODO

		return list;
	}

	std::wstring LyricsHelper::GenerateLyricifyLinesFromLyricsList(std::vector<Lyricify::Lyrics> lyrics)
	{
		// TODO

		return L"";
	}
}
