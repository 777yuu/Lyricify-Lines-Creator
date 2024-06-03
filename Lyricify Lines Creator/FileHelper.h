/************************************************************************
 * Filename:    FileHelper.h
 * Description: �ļ������ඨ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <ShlObj.h>

class FileHelper
{
public:
	/// <summary>
	/// ѡ���ļ�
	/// </summary>
	/// <param name="title">�Ի������</param>
	/// <param name="fileFilter">�ļ�����ɸѡ��</param>
	/// <returns>�ļ�����δѡ��Ϊ���ַ���</returns>
	static std::wstring SelectFile(LPCWSTR title, LPCWSTR fileFilter);

	/// <summary>
	/// ѡ���ļ���
	/// </summary>
	/// <param name="title">�Ի������</param>
	/// <returns>·����δѡ��Ϊ���ַ���</returns>
	static std::wstring SelectFolder(LPCWSTR title);

	/// <summary>
	/// ȷ��·�����ڣ�������ʱ���Դ���Ŀ¼
	/// </summary>
	/// <param name="path">Ҫȷ�����ڵ�·��</param>
	/// <returns>·���Ƿ����</returns>
	static bool EnsureDirectoryExists(const std::wstring& path);

	/// <summary>
	/// ��ȡ�ļ����ݲ������ַ���
	/// </summary>
	/// <param name="filePath">�ļ�·��</param>
	/// <returns>�ļ������ַ���</returns>
	static std::string ReadAllText(const std::wstring& filePath);
};
