#pragma once

#include <conio.h>
#include <string>
#include "irrKlang/include/irrKlang.h"

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

class MusicPlayer
{
private:
	static irrklang::ISoundEngine* engine;
	static irrklang::ISound* currentAudio;

	/// <summary>
	/// ����Ƿ�����˲�������ʼ��
	/// </summary>
	/// <param name="init">���δ��ɣ��Ƿ���г�ʼ��</param>
	/// <returns>�Ƿ�����˳�ʼ��</returns>
	static bool CheckInitiation(bool init = true);

public:
	/// <summary>
	/// ��ʼ��������
	/// </summary>
	static void InitPlayer();

	/// <summary>
	/// ����Ƶ�ļ�
	/// </summary>
	/// <param name="filePath">��Ƶ�ļ�·��</param>
	/// <param name="override">����ԭ��Ƶ (�����)</param>
	/// <returns>�Ƿ�ɹ���</returns>
	static bool Open(const std::wstring filePath, bool override = false);

	/// <summary>
	/// ��ʼ���� / �ָ�����
	/// </summary>
	static void Play();

	/// <summary>
	/// ��ͣ����
	/// </summary>
	static void Pause();

	/// <summary>
	/// �Ƿ����ڲ���
	/// </summary>
	/// <returns>�Ƿ����ڲ��ţ���ʧ�ܣ��򷵻� false</returns>
	static bool IsPlaying();

	/// <summary>
	/// ��ȡ��ǰ�Ĳ��Ž��ȣ���λΪ����
	/// </summary>
	/// <returns>��ǰ�Ĳ��Ž��ȣ���ʧ���򷵻� -1</returns>
	static int GetCurrentPositionMs();

	/// <summary>
	/// ��ȡ��Ƶ����ʱ������λΪ����
	/// </summary>
	/// <returns>��Ƶ��ʱ������ʧ���򷵻� -1</returns>
	static int GetTotalDurationMs();

	/// <summary>
	/// ��ת��Ƶ��ָ��ʱ�̣���λΪ����
	/// </summary>
	/// <param name="ms">Ҫ��ת���ĺ�����</param>
	/// <returns>�Ƿ�ɹ���ת</returns>
	static bool SeekTo(int);
};
