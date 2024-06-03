/************************************************************************
 * Filename:    SettingsHelper.cpp
 * Description: �����༰���ð����ඨ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <fstream>
#include <string>
#include <windows.h>
#include <nlohmann/json.hpp>
#include "StringHelper.h"

class MainSettings
{
public:
    /// <summary>
    /// �Ƿ�Ĭ�����Ϊ LRC
    /// </summary>
    bool IsOutputLrc = false;

    /// <summary>
    /// �豸�ӳٺ�����
    /// </summary>
    int DeviceLatencyMs = 0;

    /// <summary>
    /// �����ӳٺ�����
    /// </summary>
    int KeyboardLatencyMs = 100;

    /// <summary>
    /// Ԥ����ʴ����ʱ���
    /// </summary>
    bool IsPreviewLyricsOpenMaximize = true;

    /// <summary>
    /// ���ӳٺ�����
    /// </summary>
    /// <returns>���ӳٺ�����</returns>
    int TotalLatencyMs() const
    {
        return DeviceLatencyMs + KeyboardLatencyMs;
    }

    // ���� nlohmann::json �����л��ͷ����л�
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MainSettings, IsOutputLrc, DeviceLatencyMs, KeyboardLatencyMs)
};

class SettingsHelper
{
private:
    static std::wstring _fileName;
    static std::wstring GetSettingsFilePath();

public:
    /// <summary>
    /// ʵ������������
    /// </summary>
    static MainSettings Settings;

    /// <summary>
    /// ��ʼ������
    /// </summary>
    static void LoadSettings();

    /// <summary>
    /// �����������ļ�
    /// </summary>
    static void SaveSettings();
};

inline std::wstring SettingsHelper::_fileName = L"settings.json";
inline MainSettings SettingsHelper::Settings;
