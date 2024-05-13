#include "MusicPlayer.h"

/// <summary>
/// irrKlang ���������ʵ��
/// </summary>
irrklang::ISoundEngine* MusicPlayer::engine = nullptr;

/// <summary>
/// ��ǰ���ڲ�����Ƶ��ʵ��
/// </summary>
irrklang::ISound* MusicPlayer::currentAudio = nullptr;

void MusicPlayer::InitPlayer()
{
	if (engine == nullptr)
	{
		engine = irrklang::createIrrKlangDevice();
	}
}

bool MusicPlayer::CheckInitiation(bool init)
{
	if (engine == nullptr)
	{
		engine = irrklang::createIrrKlangDevice();
		return engine != nullptr;
	}
	return true;
}

bool MusicPlayer::Open(const std::wstring filePath, bool override)
{
	CheckInitiation();

	const int nBufferSize = 2048; // large enough, but best would be wcslen(yourFilename)*3.
	char strBuffer[nBufferSize];
	irrklang::makeUTF8fromUTF16string(filePath.c_str(), strBuffer, nBufferSize);

	auto audio = engine->play2D(strBuffer, false, true);
	MusicPlayer::currentAudio = audio;
	return audio != NULL;
}

void MusicPlayer::Play()
{
	if (currentAudio != NULL)
		MusicPlayer::currentAudio->setIsPaused(false);
}

void MusicPlayer::Pause()
{
	if (currentAudio != NULL)
		MusicPlayer::currentAudio->setIsPaused(true);
}

bool MusicPlayer::IsPlaying()
{
	if (currentAudio != NULL)
		return !MusicPlayer::currentAudio->getIsPaused();
	return false; // ����Ƶ������Ϊ���ڲ���
}

int MusicPlayer::GetCurrentPositionMs()
{
	if (currentAudio != NULL)
		return MusicPlayer::currentAudio->getPlayPosition();
	return -1;
}

int MusicPlayer::GetTotalDurationMs()
{
	if (currentAudio != NULL)
		return MusicPlayer::currentAudio->getPlayLength();
	return -1;
}

bool MusicPlayer::SeekTo(int ms)
{
	if (currentAudio != NULL)
		return MusicPlayer::currentAudio->setPlayPosition(ms);
	return false;
}
