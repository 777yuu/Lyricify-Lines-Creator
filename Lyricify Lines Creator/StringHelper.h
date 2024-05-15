#pragma once

#include <chrono>
#include <codecvt>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <windows.h>

class StringHelper
{
public:
	/// <summary>
	/// �� std::string ת��Ϊ std::wstring
	/// </summary>
	/// <param name="str">std::string ���͵��ַ���</param>
	/// <returns>std::wstring ���͵��ַ���</returns>
	static std::wstring StringToWstring(const std::string& str);

	/// <summary>
	/// �� std::wstring ת��Ϊ std::string
	/// </summary>
	/// <param name="str">std::wstring ���͵��ַ���</param>
	/// <returns>std::string ���͵��ַ���</returns>
	static std::string WstringToString(const std::wstring& str);

	/// <summary>
	/// ȥ���ַ�����β�Ŀհ��ַ�
	/// </summary>
	static std::string Trim(const std::string&);

	/// <summary>
	/// ȥ���ַ�����β�Ŀհ��ַ�
	/// </summary>
	static std::wstring Trim(const std::wstring&);

	/// <summary>
	/// ȥ���ַ�����ͷ�Ŀհ��ַ�
	/// </summary>
	static std::string TrimStart(const std::string&);

	/// <summary>
	/// ȥ���ַ�����ͷ�Ŀհ��ַ�
	/// </summary>
	static std::wstring TrimStart(const std::wstring&);

	/// <summary>
	/// ȥ���ַ�����β�Ŀհ��ַ�
	/// </summary>
	static std::string TrimEnd(const std::string&);

	/// <summary>
	/// ȥ���ַ�����β�Ŀհ��ַ�
	/// </summary>
	static std::wstring TrimEnd(const std::wstring&);

	/// <summary>
	/// �滻�ַ����е����ַ���
	/// </summary>
	/// <param name="str">ԭʼ�ַ���</param>
	/// <param name="search">Ҫ�滻�����ַ���</param>
	/// <param name="replace">Ҫ�滻�ɵ��ַ���</param>
	/// <returns>�滻����ַ���</returns>
	static std::string Replace(const std::string& str, const std::string& search, const std::string& replace);

	/// <summary>
	/// �滻�ַ����е����ַ���
	/// </summary>
	/// <param name="str">ԭʼ�ַ���</param>
	/// <param name="search">Ҫ�滻�����ַ���</param>
	/// <param name="replace">Ҫ�滻�ɵ��ַ���</param>
	/// <returns>�滻����ַ���</returns>
	static std::wstring Replace(const std::wstring& str, const std::wstring& search, const std::wstring& replace);

	/// <summary>
	/// �Ƿ�Ϊ�հ��ַ�����������ո���ַ���
	/// </summary>
	static bool IsEmptyOrWhiteSpace(const std::string&);

	/// <summary>
	/// �Ƿ�Ϊ�հ��ַ�����������ո���ַ���
	/// </summary>
	static bool IsEmptyOrWhiteSpace(const std::wstring&);

	/// <summary>
	/// ��ȡʱ���ַ���
	/// </summary>
	/// <param name="ms">ʱ�䣬��λ����</param>
	/// <returns>std:string �ַ���</returns>
	static std::string TimeMsToString(long long ms);

	/// <summary>
	/// ��·���л�ȡ�ļ���
	/// </summary>
	/// <param name="path">·���ַ���</param>
	/// <returns>�ļ��������û���ҵ�·���ָ������򷵻�����·��</returns>
	static std::string GetFileNameFromPath(const std::string& path);

	/// <summary>
	/// ��·���л�ȡ�ļ���
	/// </summary>
	/// <param name="path">·���ַ���</param>
	/// <returns>�ļ��������û���ҵ�·���ָ������򷵻�����·��</returns>
	static std::wstring GetFileNameFromPath(const std::wstring& path);
	
	/// <summary>
	/// ��·���л�ȡĿ¼·�� (����ĩβ�ָ���)
	/// </summary>
	/// <param name="path">·���ַ���</param>
	/// <returns>Ŀ¼·�������û���ҵ�·���ָ������򷵻�����·��</returns>
	static std::string GetDirectoryFromPath(const std::string& path);

	/// <summary>
	/// ��·���л�ȡĿ¼·�� (����ĩβ�ָ���)
	/// </summary>
	/// <param name="path">·���ַ���</param>
	/// <returns>Ŀ¼·�������û���ҵ�·���ָ������򷵻�����·��</returns>
	static std::wstring GetDirectoryFromPath(const std::wstring& path);

	/// <summary>
	/// �滻�ļ�������չ��
	/// </summary>
	/// <param name="filename">�ļ����ַ���</param>
	/// <param name="newExtension">Ҫ�滻�ɵ���չ��</param>
	/// <returns>�滻����ļ�������ԭ�ļ���û����չ������������չ��</returns>
	static std::string ReplaceFileNameExtension(const std::string& filename, const std::string& newExtension);

	/// <summary>
	/// �滻�ļ�������չ��
	/// </summary>
	/// <param name="filename">�ļ����ַ���</param>
	/// <param name="newExtension">Ҫ�滻�ɵ���չ��</param>
	/// <returns>�滻����ļ�������ԭ�ļ���û����չ������������չ��</returns>
	static std::wstring ReplaceFileNameExtension(const std::wstring& filename, const std::wstring& newExtension);
};
