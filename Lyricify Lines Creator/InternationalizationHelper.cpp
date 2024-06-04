/************************************************************************
 * Filename:    InternationalizationHelper.cpp
 * Description: ���ػ�����ʵ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "InternationalizationHelper.h"

std::map<std::string, std::map<Languages, std::wstring>> translations =
{
	{
		"String.Window.Main.SelectAudio",
		{
			{ Languages::EN, L"Select Audio:" },
			{ Languages::ZH_HANS, L"ѡ����Ƶ��" },
			{ Languages::ZH_HANT, L"�x�����l��" }
		}
	},
	{
		"String.Window.Main.SelectLyrics",
		{
			{ Languages::EN, L"Select Lyrics:" },
			{ Languages::ZH_HANS, L"ѡ���ʣ�" },
			{ Languages::ZH_HANT, L"�x����~��" }
		}
	},
	{
		"String.Window.Main.OutputPath",
		{
			{ Languages::EN, L"Output Path:" },
			{ Languages::ZH_HANS, L"���·����" },
			{ Languages::ZH_HANT, L"ݔ��·����" }
		}
	},
	{
		"String.Window.Main.ImportAudio",
		{
			{ Languages::EN, L"Import Audio" },
			{ Languages::ZH_HANS, L"������Ƶ" },
			{ Languages::ZH_HANT, L"�������l" }
		}
	},
	{
		"String.Window.Main.ImportLyrics",
		{
			{ Languages::EN, L"Import Lyrics" },
			{ Languages::ZH_HANS, L"������" },
			{ Languages::ZH_HANT, L"������~" }
		}
	},
	{
		"String.Window.Main.SelectPath",
		{
			{ Languages::EN, L"Select Path" },
			{ Languages::ZH_HANS, L"ѡ��·��" },
			{ Languages::ZH_HANT, L"�x��·��" }
		}
	},
	{
		"String.Window.Main.Play",
		{
			{ Languages::EN, L"Play" },
			{ Languages::ZH_HANS, L"����" },
			{ Languages::ZH_HANT, L"����" }
		}
	},
	{
		"String.Window.Main.Pause",
		{
			{ Languages::EN, L"Pause" },
			{ Languages::ZH_HANS, L"��ͣ" },
			{ Languages::ZH_HANT, L"��ͣ" }
		}
	},
	{
		"String.Window.Main.About",
		{
			{ Languages::EN, L"About" },
			{ Languages::ZH_HANS, L"����" },
			{ Languages::ZH_HANT, L"�P�" }
		}
	},
	{
		"String.Window.Main.Settings",
		{
			{ Languages::EN, L"Settings" },
			{ Languages::ZH_HANS, L"����" },
			{ Languages::ZH_HANT, L"�O��" }
		}
	},
	{
		"String.Window.Main.ViewOutput",
		{
			{ Languages::EN, L"View Output" },
			{ Languages::ZH_HANS, L"�鿴���" },
			{ Languages::ZH_HANT, L"�鿴ݔ��" }
		}
	},
	{
		"String.Window.Main.Preview",
		{
			{ Languages::EN, L"Preview" },
			{ Languages::ZH_HANS, L"Ԥ��Ч��" },
			{ Languages::ZH_HANT, L"�A�[Ч��" }
		}
	},
	{
		"String.Window.Main.Restart",
		{
			{ Languages::EN, L"Restart" },
			{ Languages::ZH_HANS, L"��������" },
			{ Languages::ZH_HANT, L"�����u��" }
		}
	},
	{
		"String.Window.Main.Start",
		{
			{ Languages::EN, L"Start" },
			{ Languages::ZH_HANS, L"��ʼ����" },
			{ Languages::ZH_HANT, L"�_ʼ�u��" }
		}
	},
	{
		"String.Window.Main.SaveLyrics",
		{
			{ Languages::EN, L"Save Lyrics" },
			{ Languages::ZH_HANS, L"������" },
			{ Languages::ZH_HANT, L"������~" }
		}
	},
	{
		"String.Window.Main.AudioLoadFailed",
		{
			{ Languages::EN, L"Audio load failed!" },
			{ Languages::ZH_HANS, L"��Ƶ����ʧ�ܣ�" },
			{ Languages::ZH_HANT, L"���l���dʧ����" }
		}
	},
	{
		"String.Window.Main.SelectAudioDialogTitle",
		{
			{ Languages::EN, L"Select Audio" },
			{ Languages::ZH_HANS, L"ѡ����Ƶ" },
			{ Languages::ZH_HANT, L"�x�����l" }
		}
	},
	{
		"String.Window.Main.SelectAudioDialogFilter",
		{
			{ Languages::EN, L"Audio (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg" },
			{ Languages::ZH_HANS, L"��Ƶ (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg" },
			{ Languages::ZH_HANT, L"���l (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg" }
		}
	},
	{
		"String.Window.Main.SelectLyricsDialogTitle",
		{
			{ Languages::EN, L"Select Lyrics" },
			{ Languages::ZH_HANS, L"ѡ����" },
			{ Languages::ZH_HANT, L"�x����~" }
		}
	},
	{
		"String.Window.Main.SelectLyricsDialogFilter",
		{
			{ Languages::EN, L"Text Files (*.txt)\0*.txt" },
			{ Languages::ZH_HANS, L"�ı��ĵ� (*.txt)\0*.txt" },
			{ Languages::ZH_HANT, L"�ı��ļ� (*.txt)\0*.txt" }
		}
	},
	{
		"String.Window.Main.EmptyOrErrorText",
		{
			{ Languages::EN, L"The text is empty or an error occurred while reading!" },
			{ Languages::ZH_HANS, L"�ı�Ϊ�գ�����ֶ�ȡ����" },
			{ Languages::ZH_HANT, L"�ı���գ�����F�xȡ�e�`��" }
		}
	},
	{
		"String.Window.Main.OutputPathDialogTitle",
		{
			{ Languages::EN, L"Select Export Path" },
			{ Languages::ZH_HANS, L"ѡ�񵼳�·��" },
			{ Languages::ZH_HANT, L"�x�񌧳�·��" }
		}
	},
	{
		"String.Window.Main.NoOutputToView",
		{
			{ Languages::EN, L"No output to view!" },
			{ Languages::ZH_HANS, L"û�пɲ鿴�������" },
			{ Languages::ZH_HANT, L"�]�пɲ鿴��ݔ����" }
		}
	},
	{
		"String.Window.Main.NoPreviewToView",
		{
			{ Languages::EN, L"No preview to view!" },
			{ Languages::ZH_HANS, L"û�пɲ鿴��Ԥ����" },
			{ Languages::ZH_HANT, L"�]�пɲ鿴���A�[��" }
		}
	},
	{
		"String.Window.Main.NoAudioSelected",
		{
			{ Languages::EN, L"No audio selected!" },
			{ Languages::ZH_HANS, L"δѡ����Ƶ��" },
			{ Languages::ZH_HANT, L"δ�x�����l��" }
		}
	},
	{
		"String.Window.Main.NoLyricsSelected",
		{
			{ Languages::EN, L"No lyrics file selected!" },
			{ Languages::ZH_HANS, L"δѡ�����ı���" },
			{ Languages::ZH_HANT, L"δ�x����~�ļ���" }
		}
	},
	{
		"String.Window.Main.NoLyricsToSave",
		{
			{ Languages::EN, L"Save failed, no lyrics written to file!" },
			{ Languages::ZH_HANS, L"����ʧ�ܣ�û�и�ʱ�д���ļ���" },
			{ Languages::ZH_HANT, L"����ʧ�����]�и��~�������ļ���" }
		}
	},
	{
		"String.Window.Main.SaveFailed",
		{
			{ Languages::EN, L"Save failed, unable to write to file!" },
			{ Languages::ZH_HANS, L"����ʧ�ܣ��޷�д���ļ���" },
			{ Languages::ZH_HANT, L"����ʧ�����o�������ļ���" }
		}
	},
	{
		"String.Window.Main.SaveFailedTitle",
		{
			{ Languages::EN, L"Save Failed" },
			{ Languages::ZH_HANS, L"����ʧ��" },
			{ Languages::ZH_HANT, L"����ʧ��" }
		}
	},
	{
		"String.Window.Main.OutputSaveFailed",
		{
			{ Languages::EN, L"Save failed, unable to write to file!" },
			{ Languages::ZH_HANS, L"����ʧ�ܣ��޷�д���ļ���" },
			{ Languages::ZH_HANT, L"����ʧ�����o�������ļ���" }
		}
	},
	{
		"String.Window.Main.OutputSaveSuccess",
		{
			{ Languages::EN, L"Save successful!" },
			{ Languages::ZH_HANS, L"����ɹ���" },
			{ Languages::ZH_HANT, L"����ɹ���" }
		}
	},
	{
		"String.Window.Main.OutputSaveSuccessTitle",
		{
			{ Languages::EN, L"Save Successful" },
			{ Languages::ZH_HANS, L"����ɹ�" },
			{ Languages::ZH_HANT, L"����ɹ�" }
		}
	},
	{
		"String.Window.Main.PreviousLine",
		{
			{Languages::EN, L"Previous Line:"},
			{Languages::ZH_HANS, L"��һ�У�"},
			{Languages::ZH_HANT, L"��һ�У�"}
		}
	},
	{
		"String.Window.Main.CurrentLine",
		{
			{Languages::EN, L"Current Line:"},
			{Languages::ZH_HANS, L"��ǰ�У�"},
			{Languages::ZH_HANT, L"��ǰ�У�"}
		}
	},
	{
		"String.Window.Main.NextLine",
		{
			{Languages::EN, L"Next Line:"},
			{Languages::ZH_HANS, L"��һ�У�"},
			{Languages::ZH_HANT, L"��һ�У�"}
		}
	},
	{
		"String.Window.Main.NoticeLineStart",
		{
			{Languages::EN, L"Line Start: ��"},
			{Languages::ZH_HANS, L"����ʼ: ��"},
			{Languages::ZH_HANT, L"����ʼ: ��"}
		}
	},
	{
		"String.Window.Main.NoticeCurrentLineEnd",
		{
			{Languages::EN, L"Current Line End: ��"},
			{Languages::ZH_HANS, L"��ǰ�н���: ��"},
			{Languages::ZH_HANT, L"��ǰ�нY��: ��"}
		}
	},
	{
		"String.Window.Main.NoticePreviousLineEnd",
		{
			{Languages::EN, L"Previous Line End: ��"},
			{Languages::ZH_HANS, L"��һ�н���: ��"},
			{Languages::ZH_HANT, L"��һ�нY��: ��"}
		}
	},
	{
		"String.Window.Main.NoticeReturnToPreviousLine",
		{
			{Languages::EN, L"Return to Previous Line: ��"},
			{Languages::ZH_HANS, L"�ص���һ��: ��"},
			{Languages::ZH_HANT, L"�ص���һ��: ��"}
		}
	},
	{
		"String.Window.Main.NoticePlayPause",
		{
			{Languages::EN, L"Play/Pause: Space"},
			{Languages::ZH_HANS, L"����/��ͣ: Space"},
			{Languages::ZH_HANT, L"����/��ͣ: Space"}
		}
	},
	{
		"String.Window.Main.NoticeSeekBack3s",
		{
			{Languages::EN, L"Seek Back 3s: B"},
			{Languages::ZH_HANS, L"���� 3s: B"},
			{Languages::ZH_HANT, L"���� 3s: B"}
		}
	},
	{
		"String.Window.Main.NoticeSeekForward3s",
		{
			{Languages::EN, L"Seek Forward 3s: N"},
			{Languages::ZH_HANS, L"ǰ�� 3s: N"},
			{Languages::ZH_HANT, L"ǰ�M 3s: N"}
		}
	},
	{
		"String.Window.Main.NoticeSeekForward10s",
		{
			{Languages::EN, L"Seek Forward 10s: M"},
			{Languages::ZH_HANS, L"ǰ�� 10s: M"},
			{Languages::ZH_HANT, L"ǰ�M 10s: M"}
		}
	},
	{
		"String.Window.Main.NoticeSeekForward30s",
		{
			{Languages::EN, L"Seek Forward 30s: C"},
			{Languages::ZH_HANS, L"ǰ�� 30s: C"},
			{Languages::ZH_HANT, L"ǰ�M 30s: C"}
		}
	},
	{
		"String.Window.Main.NoticeSeekTo0s",
		{
			{Languages::EN, L"Seek to 0s: R"},
			{Languages::ZH_HANS, L"�ص� 0s: R"},
			{Languages::ZH_HANT, L"�ص� 0s: R"}
		}
	},
	{
		"String.Window.Main.KeyTips",
		{
			{Languages::EN, L"Key Tips:"},
			{Languages::ZH_HANS, L"������ʾ��"},
			{Languages::ZH_HANT, L"���I��ʾ��"}
		}
	},
	{
		"String.Window.PreviewLyrics",
		{
			{ Languages::EN, L"Preview Lyrics" },
			{ Languages::ZH_HANS, L"���Ԥ��" },
			{ Languages::ZH_HANT, L"���~�A�[" }
		}
	},
	{
		"String.Window.PreviewOutput",
		{
			{ Languages::EN, L"Output Preview" },
			{ Languages::ZH_HANS, L"���Ԥ��" },
			{ Languages::ZH_HANT, L"ݔ���A�[" }
		}
	},
	{
		"String.Window.PreviewOutput.Save",
		{
			{ Languages::EN, L"Save" },
			{ Languages::ZH_HANS, L"����" },
			{ Languages::ZH_HANT, L"����" }
		}
	},
	{
		"String.Window.PreviewOutput.SaveSuccess",
		{
			{ Languages::EN, L"Saved successfully!" },
			{ Languages::ZH_HANS, L"����ɹ���" },
			{ Languages::ZH_HANT, L"����ɹ���" }
		}
	},
	{
		"String.Window.PreviewOutput.SaveFailed",
		{
			{ Languages::EN, L"Save failed, unable to write to file!" },
			{ Languages::ZH_HANS, L"����ʧ�ܣ��޷�д���ļ���" },
			{ Languages::ZH_HANT, L"����ʧ�����o�������ļ���" }
		}
	},
	{
		"String.Window.PreviewOutput.SaveFailedTitle",
		{
			{ Languages::EN, L"Save failed" },
			{ Languages::ZH_HANS, L"����ʧ��" },
			{ Languages::ZH_HANT, L"����ʧ��" }
		}
	},
	{
		"String.Window.PreviewOutput.SaveSuccessTitle",
		{
			{ Languages::EN, L"Save successful" },
			{ Languages::ZH_HANS, L"����ɹ�" },
			{ Languages::ZH_HANT, L"����ɹ�" }
		}
	},
	{
		"String.Window.About",
		{
			{ Languages::EN, L"About" },
			{ Languages::ZH_HANS, L"����" },
			{ Languages::ZH_HANT, L"�P�" }
		}
	},
	{
		"String.Window.About.FullName",
		{
			{ Languages::EN, L"Lyricify Lines Line-Synced Lyrics Creator" },
			{ Languages::ZH_HANS, L"Lyricify Lines ���и�ʴ��Ṥ��" },
			{ Languages::ZH_HANT, L"Lyricify Lines ���и��~���S����" }
		}
	},
	{
		"String.Window.About.Developer",
		{
			{ Languages::EN, L"Developer" },
			{ Languages::ZH_HANS, L"������" },
			{ Languages::ZH_HANT, L"�_�l��" }
		}
	},
	{
		"String.Window.About.ThirdParty",
		{
			{ Languages::EN, L"Third Party Notices" },
			{ Languages::ZH_HANS, L"������֪ͨ" },
			{ Languages::ZH_HANT, L"������֪ͨ" }
		}
	},
	{
		"String.Window.About.License.MIT",
		{
			{ Languages::EN, L"MIT License" },
			{ Languages::ZH_HANS, L"MIT Э��" },
			{ Languages::ZH_HANT, L"MIT �f�h" }
		}
	},
	{
		"String.Window.About.License.LGPL21",
		{
			{ Languages::EN, L"LGPL-2.1 License" },
			{ Languages::ZH_HANS, L"LGPL-2.1 Э��" },
			{ Languages::ZH_HANT, L"LGPL-2.1 �f�h" }
		}
	},
	{
		"String.Window.Settings",
		{
			{ Languages::EN, L"Settings" },
			{ Languages::ZH_HANS, L"����" },
			{ Languages::ZH_HANT, L"�O��" }
		}
	},
	{
		"String.Window.Settings.Language",
		{
			{ Languages::EN, L"Language" },
			{ Languages::ZH_HANS, L"����" },
			{ Languages::ZH_HANT, L"�Z��" }
		}
	},
	{
		"String.Window.Settings.LyricsOutputFormat",
		{
			{ Languages::EN, L"Lyrics Output Format" },
			{ Languages::ZH_HANS, L"��������ʽ" },
			{ Languages::ZH_HANT, L"���~ݔ����ʽ" }
		}
	},
	{
		"String.Window.Settings.DeviceLatency",
		{
			{ Languages::EN, L"Device Latency" },
			{ Languages::ZH_HANS, L"�豸�ӳ�" },
			{ Languages::ZH_HANT, L"�O�����t" }
		}
	},
	{
		"String.Window.Settings.KeyboardLatency",
		{
			{ Languages::EN, L"Keyboard Latency" },
			{ Languages::ZH_HANS, L"�����ӳ�" },
			{ Languages::ZH_HANT, L"���I���t" }
		}
	},
	{
		"String.Window.Settings.PreviewLyricsMaximize",
		{
			{ Languages::EN, L"Preview Lyrics Maximize" },
			{ Languages::ZH_HANS, L"���Ԥ�����" },
			{ Languages::ZH_HANT, L"���~�A�[���" }
		}
	},
	{
		"String.Window.Settings.Save",
		{
			{ Languages::EN, L"Save" },
			{ Languages::ZH_HANS, L"ȷ��" },
			{ Languages::ZH_HANT, L"�_��" }
		}
	},
	{
		"String.Window.Settings.Cancel",
		{
			{ Languages::EN, L"Cancel" },
			{ Languages::ZH_HANS, L"ȡ��" },
			{ Languages::ZH_HANT, L"ȡ��" }
		}
	},
	{
		"String.Window.Settings.InvalidLatencyValue",
		{
			{ Languages::EN, L"The latency value should be an integer, usually a natural number." },
			{ Languages::ZH_HANS, L"�ӳ�ֵӦΪ������һ��Ϊ��Ȼ����" },
			{ Languages::ZH_HANT, L"���tֵ����������һ�����Ȼ����" }
		}
	},
	{
		"String.Window.Settings.ErrorInput",
		{
			{ Languages::EN, L"Error Input" },
			{ Languages::ZH_HANS, L"��������" },
			{ Languages::ZH_HANT, L"�e�`ݔ��" }
		}
	},
};

std::wstring GetStringFromKey(const std::string& key)
{
	Languages lang = Languages::ZH_HANS;
	try
	{
		lang = static_cast<Languages>(SettingsHelper::Settings.Language);
	}
	catch (...) {}
	return translations[key][lang];
}

std::wstring GetStringFromKey(const std::string& key, Languages lang)
{
	return translations[key][lang];
}
