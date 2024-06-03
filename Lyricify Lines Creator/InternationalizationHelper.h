/************************************************************************
 * Filename:    InternationalizationHelper.h
 * Description: ���ػ���������
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include "SettingsHelper.h"

/// <summary>
/// ͨ�� Key ��ȡ���ػ��ַ���
/// </summary>
std::wstring GetStringFromKey(const std::string& key);

/// <summary>
/// ͨ�� Key ��ȡ���ػ��ַ���
/// </summary>
/// <param name="lang">ָ������</param>
std::wstring GetStringFromKey(const std::string& key, Languages lang);
