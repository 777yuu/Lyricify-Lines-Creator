/************************************************************************
 * Filename:    SettingsHelper.cpp
 * Description: ���ð�����ʵ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "SettingsHelper.h"

void SettingsHelper::LoadSettings()
{
    std::wstring fullPath = GetSettingsFilePath();
    std::ifstream file(fullPath);
    if (file.is_open())
    {
        nlohmann::json j;
        file >> j;
        Settings = j.get<MainSettings>();
    }
    else
    {
        // ����ļ���ʧ�ܣ�ʹ��Ĭ������
        Settings = MainSettings();
    }
}

void SettingsHelper::SaveSettings()
{
    std::wstring fullPath = GetSettingsFilePath();
    nlohmann::json j = Settings;
    std::ofstream file(fullPath);
    file << j.dump(4);
}

std::wstring SettingsHelper::GetSettingsFilePath()
{
    TCHAR exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, MAX_PATH);
    std::wstring outputPath = exePath;
    size_t pos = outputPath.find_last_of(L"\\/");
    if (std::wstring::npos != pos)
    {
        outputPath = outputPath.substr(0, pos);
    }
    return outputPath + L"\\" + _fileName;
}
