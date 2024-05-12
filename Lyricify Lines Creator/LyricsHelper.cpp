#include "LyricsHelper.h"

namespace Lyricify
{
	/// <summary>
	/// ���ļ���ȡ�ı��д��� vector �б�
	/// </summary>
	/// <param name="filePath">�ļ�·��</param>
	/// <returns>����� vector �б���ʧ���򷵻ؿ��б�</returns>
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

	/// <summary>
	/// ���ı����б�����µ� Lyricify.Lyrics �� vector �б�
	/// </summary>
	/// <param name="lines">�ı��� vector �б�</param>
	/// <returns>����� vector �б�</returns>
	std::vector<Lyricify::Lyrics> LyricsHelper::GetLyricsFromLines(std::vector<std::wstring> lines)
	{
        std::vector<Lyricify::Lyrics> list;

        for (int i = 0; i < lines.size(); i++)
        {
            Lyricify::Lyrics line(lines[i]);
            list.push_back(line);
        }

        return list;
	}
}
