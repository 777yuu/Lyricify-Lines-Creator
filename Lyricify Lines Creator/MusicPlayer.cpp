#include "MusicPlayer.h"

/// <summary>
/// ����Ƶ�ļ�
/// </summary>
/// <param name="filePath">��Ƶ�ļ�·��</param>
/// <param name="override">����ԭ��Ƶ (�����)</param>
/// <returns>�Ƿ�ɹ���</returns>
bool MusicPlayer::Open(const std::wstring filePath, bool override)
{
	const int nBufferSize = 2048; // large enough, but best would be wcslen(yourFilename)*3.
	char strBuffer[nBufferSize];
	irrklang::makeUTF8fromUTF16string(filePath.c_str(), strBuffer, nBufferSize);

	auto audio = engine->play2D(strBuffer, false, true);
	MusicPlayer::currentAudio = audio;
	return audio != NULL;
}

/// <summary>
/// ��ʼ���� / �ָ�����
/// </summary>
void MusicPlayer::Play()
{
	if (currentAudio != NULL)
		MusicPlayer::currentAudio->setIsPaused(false);
}

/// <summary>
/// ��ͣ����
/// </summary>
void MusicPlayer::Pause()
{
	if (currentAudio != NULL)
		MusicPlayer::currentAudio->setIsPaused(true);
}

/// <summary>
/// �Ƿ����ڲ���
/// </summary>
/// <returns>�Ƿ����ڲ��ţ���ʧ�ܣ��򷵻� false</returns>
bool MusicPlayer::IsPlaying()
{
	if (currentAudio != NULL)
		return !MusicPlayer::currentAudio->getIsPaused();
	return false; // ����Ƶ������Ϊ���ڲ���
}

/// <summary>
/// ��ȡ��ǰ�Ĳ��Ž��ȣ���λΪ����
/// </summary>
/// <returns>��ǰ�Ĳ��Ž��ȣ���ʧ���򷵻� -1</returns>
int MusicPlayer::GetCurrentPositionMs()
{
	if (currentAudio != NULL)
		return MusicPlayer::currentAudio->getPlayPosition();
	return -1;
}

/// <summary>
/// ��ȡ��Ƶ����ʱ������λΪ����
/// </summary>
/// <returns>��Ƶ��ʱ������ʧ���򷵻� -1</returns>
int MusicPlayer::GetTotalDurationMs()
{
	if (currentAudio != NULL)
		return MusicPlayer::currentAudio->getPlayLength();
	return -1;
}

/// <summary>
/// ��ת��Ƶ��ָ��ʱ�̣���λΪ����
/// </summary>
/// <param name="ms">Ҫ��ת���ĺ�����</param>
/// <returns></returns>
bool MusicPlayer::SeekTo(int ms)
{
	if (currentAudio != NULL)
		return MusicPlayer::currentAudio->setPlayPosition(ms);
	return false;
}