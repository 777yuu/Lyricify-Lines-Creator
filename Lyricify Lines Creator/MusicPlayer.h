/************************************************************************
 * Filename:    MusicPlayer.h
 * Description: ��Ƶ�����ඨ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

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
	static std::wstring CurrentAudioPath;

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
	static bool Load(const std::wstring filePath, bool override = true);

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
	static bool SeekTo(int ms);

	/// <summary>
	/// �����ת��Ƶ����λΪ����
	/// </summary>
	/// <param name="ms">Ҫ��ת�ĺ�����</param>
	/// <returns>�Ƿ�ɹ���ת</returns>
	static bool SeekBack(int ms);

	/// <summary>
	/// ��ǰ��ת��Ƶ����λΪ����
	/// </summary>
	/// <param name="ms">Ҫ��ת�ĺ�����</param>
	/// <returns>�Ƿ�ɹ���ת</returns>
	static bool SeekForward(int ms);

	/// <summary>
	/// ���ò�������
	/// </summary>
	/// <param name="speed">�������ʣ�Ĭ��Ϊ 1.0f</param>
	/// <returns>�Ƿ�ɹ�����</returns>
	static bool SetPlaybackSpeed(float speed = 1.0f);

	/// <summary>
	/// ��ȡ��������
	/// </summary>
	/// <returns>�������ʣ�Ĭ��Ϊ 1.0f</returns>
	static float GetPlaybackSpeed();
};
