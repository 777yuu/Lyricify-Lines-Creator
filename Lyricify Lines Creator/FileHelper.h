#pragma once

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
};
