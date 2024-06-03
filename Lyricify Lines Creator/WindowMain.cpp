/************************************************************************
 * Filename:    WindowMain.cpp
 * Description: ������ʵ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "WindowMain.h"

namespace WindowMain
{

#pragma region Variable Definitions

	double DPI_Scale = 1;

	// ����������� Label �Ŀ�ȣ����ڱ��ػ�ʱ��������ĳߴ�
	int TOP_LEFT_LABEL_MAX_WIDTH = 65;

	bool IsInRefreshUI = false;
	bool IsInDrawAtWndProcPaint = false;
	bool IsMaking = false;
	std::vector<Lyricify::Lyrics> LyricsList;

#pragma endregion

#pragma region Control Definitions

	hiex::Window wnd;

	// ��������

	hiex::Canvas CanvasMain;

	hiex::SysEdit TextBoxChooseAudio;
	hiex::SysEdit TextBoxChooseRawLyrics;
	hiex::SysEdit TextBoxOutputPath;

	hiex::SysButton ButtonChooseAudio;
	hiex::SysButton ButtonChooseRawLyrics;
	hiex::SysButton ButtonOutputPath;

	// ��������

	hiex::SysButton ButtonPlayPause;

	// �ײ�����

	hiex::SysButton ButtonAbout;
	hiex::SysButton ButtonSettings;
	hiex::SysButton ButtonViewOutput;
	hiex::SysButton ButtonPreview;
	hiex::SysButton ButtonRestart;
	hiex::SysButton ButtonStart;

#pragma endregion

#pragma region Button Clicks & Keyboard Events

	void ButtonChooseAudio_Click()
	{
		auto path = FileHelper::SelectFile(GetStringFromKey("String.Window.Main.SelectAudioDialogTitle").c_str(), GetStringFromKey("String.Window.Main.SelectAudioDialogFilter").c_str());
		if (!path.empty())
		{
			TextBoxChooseAudio.SetText(path);

			if (!MusicPlayer::Load(path))
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), MB_OK | MB_ICONWARNING);
			}
		}
	}

	void ButtonChooseRawLyrics_Click()
	{
		auto path = FileHelper::SelectFile(GetStringFromKey("String.Window.Main.SelectLyricsDialogTitle").c_str(), GetStringFromKey("String.Window.Main.SelectLyricsDialogFilter").c_str());
		if (!path.empty())
		{
			TextBoxChooseRawLyrics.SetText(path);

			auto stringLines = Lyricify::LyricsHelper::ReadTextToLines(TextBoxChooseRawLyrics.GetText());
			if (stringLines.size() == 0)
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.EmptyOrErrorText").c_str(), GetStringFromKey("String.Window.Main.EmptyOrErrorText").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}

			// ���ظ���ı�
			LyricsList = Lyricify::LyricsHelper::GetLyricsFromLines(stringLines);

			// ���ص� UI ��
			RefreshUI();
		}
	}

	void ButtonOutputPath_Click()
	{
		auto path = FileHelper::SelectFolder(GetStringFromKey("String.Window.Main.OutputPathDialogTitle").c_str());
		if (!path.empty())
		{
			TextBoxOutputPath.SetText(path);
		}
	}

	void ButtonPlayPause_Click()
	{
		if (MusicPlayer::IsPlaying())
		{
			MusicPlayer::Pause();
			ButtonPlayPause.SetText(GetStringFromKey("String.Window.Main.Play").c_str());
		}
		else
		{
			if (MusicPlayer::CurrentAudioPath.empty() && !TextBoxChooseAudio.GetText().empty()
				|| MusicPlayer::CurrentAudioPath != TextBoxChooseAudio.GetText())
			{
				// û�м�����Ƶ������Ƶ���ʱ����Ҫ���¼���
				if (!MusicPlayer::Load(TextBoxChooseAudio.GetText()))
				{
					MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), MB_OK | MB_ICONWARNING);
				}
			}

			MusicPlayer::Play();
			ButtonPlayPause.SetText(GetStringFromKey("String.Window.Main.Pause").c_str());

			std::thread([]()
				{
					static bool IsRefreshThreadRunning = false;
					if (IsRefreshThreadRunning) return;
					IsRefreshThreadRunning = true;

					std::wstring audio = MusicPlayer::CurrentAudioPath;
					while (audio == MusicPlayer::CurrentAudioPath && MusicPlayer::IsPlaying())
					{
						// ���ڱ���ʱ������ˢ�½��ȣ���ֹ��Ⱦ����
						if (!WindowAbout::IsOpened()
							&& !WindowSettings::IsOpened()
							&& !WindowPreviewOutput::IsOpened()
							&& !WindowPreviewLyrics::IsOpened())
						{
							RefreshUI();
						}
						TaskHelper::Delay(25).wait();
					}
					if (!MusicPlayer::IsPlaying())
					{
						ButtonPlayPause.SetText(GetStringFromKey("String.Window.Main.Play").c_str());
					}

					IsRefreshThreadRunning = false;
				}).detach();
		}
	}

	void ButtonAbout_Click()
	{
		WindowAbout::Show(DPI_Scale, GetWindowRect(), wnd.GetHandle());
	}

	void ButtonSettings_Click()
	{
		WindowSettings::Show(DPI_Scale, GetWindowRect(), wnd.GetHandle());
	}

	void ButtonViewOutput_Click()
	{
		auto fileContent = SettingsHelper::Settings.IsOutputLrc
			? Lyricify::LyricsHelper::GenerateLrcFromLyricsList(LyricsList)
			: Lyricify::LyricsHelper::GenerateLyricifyLinesFromLyricsList(LyricsList);
		if (fileContent.empty())
		{
			MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.NoOutputToView").c_str(), GetStringFromKey("String.Window.Main.NoOutputToView").c_str(), MB_OK | MB_ICONINFORMATION);
			return;
		}
		auto filePath = GetOutputFullpath();
		WindowPreviewOutput::Show(filePath, fileContent, DPI_Scale, GetWindowRect(), wnd.GetHandle());
	}

	void ButtonPreview_Click()
	{
		auto fileContent = Lyricify::LyricsHelper::GenerateLyricifyLinesFromLyricsList(LyricsList);
		if (fileContent.empty())
		{
			MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.NoPreviewToView").c_str(), GetStringFromKey("String.Window.Main.NoPreviewToView").c_str(), MB_OK | MB_ICONINFORMATION);
			return;
		}
		MusicPlayer::SeekTo(0); // ���ȹ���
		WindowPreviewLyrics::Show(Lyricify::LyricsHelper::ParseLyricsFromLyricifyLinesString(fileContent), DPI_Scale, GetWindowRect());
	}

	void ButtonRestart_Click()
	{
		// ��ո�ʵ�ʱ����Ϣ��������ͷ��

		// �����Ƶ�仯����Ҫ���¼���
		if (MusicPlayer::CurrentAudioPath != TextBoxChooseAudio.GetText())
		{
			if (!MusicPlayer::Load(TextBoxChooseAudio.GetText()))
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}
		}
		else
		{
			MusicPlayer::SeekTo(0);
		}

		// ��ո����Ϣ (ֱ�����¼���)
		auto stringLines = Lyricify::LyricsHelper::ReadTextToLines(TextBoxChooseRawLyrics.GetText());
		if (stringLines.size() == 0)
		{
			MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.EmptyOrErrorText").c_str(), GetStringFromKey("String.Window.Main.EmptyOrErrorText").c_str(), MB_OK | MB_ICONWARNING);
			return;
		}
		LyricsList = Lyricify::LyricsHelper::GetLyricsFromLines(stringLines);

		if (!MusicPlayer::IsPlaying()) RefreshUI();
	}

	void ButtonStart_Click()
	{
		if (!IsMaking)
		{
			// ��ʼ����
			// �������״̬
			if (TextBoxChooseAudio.GetTextLength() == 0)
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.NoAudioSelected").c_str(), GetStringFromKey("String.Window.Main.NoAudioSelected").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}
			if (MusicPlayer::CurrentAudioPath != TextBoxChooseAudio.GetText() && !MusicPlayer::Load(TextBoxChooseAudio.GetText()))
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}
			if (TextBoxChooseRawLyrics.GetTextLength() == 0)
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.NoLyricsSelected").c_str(), GetStringFromKey("String.Window.Main.NoLyricsSelected").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}
			auto stringLines = Lyricify::LyricsHelper::ReadTextToLines(TextBoxChooseRawLyrics.GetText());
			if (stringLines.size() == 0)
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.EmptyOrErrorText").c_str(), GetStringFromKey("String.Window.Main.EmptyOrErrorText").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}

			// ���ظ���ı�
			LyricsList = Lyricify::LyricsHelper::GetLyricsFromLines(stringLines);

			// ��ʼ������Ƶ
			if (!MusicPlayer::IsPlaying())
			{
				ButtonPlayPause_Click();
			}

			// ���°�ť״̬
			ButtonRestart.Enable(true);
			ButtonStart.SetText(GetStringFromKey("String.Window.Main.SaveLyrics").c_str());
		}
		else
		{
			// ������
			// ��ͣ������Ƶ
			if (MusicPlayer::IsPlaying())
			{
				ButtonPlayPause_Click();
			}

			// �������ļ�
			auto lyricifyLinesString = SettingsHelper::Settings.IsOutputLrc
				? Lyricify::LyricsHelper::GenerateLrcFromLyricsList(LyricsList)
				: Lyricify::LyricsHelper::GenerateLyricifyLinesFromLyricsList(LyricsList);
			if (lyricifyLinesString.empty())
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.NoLyricsToSave").c_str(), GetStringFromKey("String.Window.Main.NoLyricsToSave").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}
			else
			{
				std::wofstream outFile(GetOutputFullpath());
				if (!outFile)
				{
					MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.OutputSaveFailed").c_str(), GetStringFromKey("String.Window.Main.SaveFailedTitle").c_str(), MB_OK | MB_ICONWARNING);
					return;
				}
				else
				{
					outFile << lyricifyLinesString;
					outFile.close();
				}
			}

			// ���°�ť״̬
			ButtonRestart.Enable(false);
			ButtonStart.SetText(GetStringFromKey("String.Window.Main.Start").c_str());
		}
		IsMaking = !IsMaking;
	}

	void KeyboardEvents(WPARAM wParam)
	{
		switch (wParam)
		{
		case VK_SPACE:
			ButtonPlayPause_Click();
			break;

		case 'B':
			MusicPlayer::SeekBack(3000);
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;

		case 'N':
			MusicPlayer::SeekForward(3000);
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;

		case 'M':
			MusicPlayer::SeekForward(10000);
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;

		case 'C':
			MusicPlayer::SeekForward(30000);
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;

		case 'R':
			MusicPlayer::SeekTo(0);
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;

		case VK_UP: // Ϊ��ǰ�� (��һ��) �����ʼʱ��
		{
			if (!IsMaking) break;
			auto index = GetCurrentLineIndex();
			if (index < (int)LyricsList.size() - 1)
			{
				auto line = GetCurrentLine(index + 1);
				if (line != nullptr)
				{
					line->StartTime = MusicPlayer::GetCurrentPositionMs() - SettingsHelper::Settings.TotalLatencyMs();
				}
			}
			else if (index == (int)LyricsList.size() - 1)
			{
				auto line = GetCurrentLine(index);
				if (line != nullptr && line->EndTime == -1)
				{
					line->EndTime = MusicPlayer::GetCurrentPositionMs() - SettingsHelper::Settings.TotalLatencyMs();
				}
			}
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;
		}

		case VK_RIGHT: // Ϊ��ǰ�б�ǽ���ʱ��
		{
			if (!IsMaking) break;
			auto line = GetCurrentLine();
			if (line != nullptr && line->EndTime == -1)
			{
				line->EndTime = MusicPlayer::GetCurrentPositionMs() - SettingsHelper::Settings.TotalLatencyMs();
			}
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;
		}

		case VK_LEFT: // Ϊ��һ�б�ǽ���ʱ��
		{
			if (!IsMaking) break;
			auto index = GetCurrentLineIndex();
			if (index - 1 >= 0)
			{
				auto line = GetCurrentLine(index - 1);
				if (line != nullptr && line->EndTime == -1)
				{
					line->EndTime = MusicPlayer::GetCurrentPositionMs() - SettingsHelper::Settings.TotalLatencyMs();
				}
				if (!MusicPlayer::IsPlaying()) RefreshUI();
			}
			break;
		}

		case VK_DOWN: // ɾȥ��ǰ�е���ʵʱ�䣬����н���ʱ�䣬������ɾ��
		{
			if (!IsMaking) break;
			auto index = GetCurrentLineIndex();
			auto line = GetCurrentLine(index);
			if (line != nullptr)
			{
				if (line->EndTime != -1)
				{
					MusicPlayer::SeekTo(line->EndTime);
					line->EndTime = -1;
				}
				else
				{
					MusicPlayer::SeekTo(line->StartTime);
					line->StartTime = -1;
				}
			}
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;
		}

		default:
			break;
		}
	}

#pragma endregion

#pragma region Sizes (Init & Resize)

	/// <summary>
	/// ���������Ŀؼ�
	/// </summary>
	/// <param name="hwnd">����������ľ��</param>
	void AddWindowControls(HWND hwnd)
	{
		int left, top;
		int w = CanvasMain.GetWidth() / DPI_Scale;
		int h = CanvasMain.GetHeight() / DPI_Scale;

#pragma region ��������

		DrawLabelControls();

		left = MARGIN_HORIZONTAL + TOP_LEFT_LABEL_MAX_WIDTH + CONTROL_PADDING_HORIZONTAL;
		auto width = w - (MARGIN_HORIZONTAL * 2 + TOP_LEFT_LABEL_MAX_WIDTH + BUTTON_WIDTH + CONTROL_PADDING_HORIZONTAL * 2);
		TextBoxChooseAudio.Create(hwnd, left, MARGIN_VERTICAL, width, CONTROL_HEIGHT);
		TextBoxChooseRawLyrics.Create(hwnd, left, MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, width, CONTROL_HEIGHT);
		TextBoxOutputPath.Create(hwnd, left, MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, width, CONTROL_HEIGHT);

		left = w - MARGIN_HORIZONTAL - BUTTON_WIDTH;
		ButtonChooseAudio.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.ImportAudio").c_str());
		ButtonChooseRawLyrics.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.ImportLyrics").c_str());
		ButtonOutputPath.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.SelectPath").c_str());

#pragma endregion

#pragma region ��������

		top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;
		ButtonPlayPause.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + top, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.Play").c_str());

#pragma endregion

#pragma region �ײ�����

		top = h - MARGIN_VERTICAL - BUTTON_HEIGHT;
		ButtonAbout.Create(hwnd, MARGIN_HORIZONTAL, top, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.About").c_str());
		ButtonSettings.Create(hwnd, MARGIN_HORIZONTAL + BUTTON_WIDTH + CONTROL_PADDING_HORIZONTAL, top, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.Settings").c_str());
		ButtonViewOutput.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 4 - CONTROL_PADDING_HORIZONTAL * 5, top, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.ViewOutput").c_str());
		ButtonPreview.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 3 - CONTROL_PADDING_HORIZONTAL * 4, top, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.Preview").c_str());
		ButtonRestart.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL, top, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.Restart").c_str());
		ButtonStart.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH, top, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.Start").c_str());

#pragma endregion

		// ��������
		TextBoxChooseAudio.SetFont(DEFAULT_TEXTBOX_FONTSIZE, 0, DEFAULT_FONT);
		TextBoxChooseRawLyrics.SetFont(DEFAULT_TEXTBOX_FONTSIZE, 0, DEFAULT_FONT);
		TextBoxOutputPath.SetFont(DEFAULT_TEXTBOX_FONTSIZE, 0, DEFAULT_FONT);
		ButtonChooseAudio.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonChooseRawLyrics.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonOutputPath.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonPlayPause.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonAbout.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonSettings.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonViewOutput.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonPreview.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonRestart.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonStart.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);

		// ע������Ϣ
		ButtonChooseAudio.RegisterMessage(ButtonChooseAudio_Click);
		ButtonChooseRawLyrics.RegisterMessage(ButtonChooseRawLyrics_Click);
		ButtonOutputPath.RegisterMessage(ButtonOutputPath_Click);
		ButtonPlayPause.RegisterMessage(ButtonPlayPause_Click);
		ButtonAbout.RegisterMessage(ButtonAbout_Click);
		ButtonSettings.RegisterMessage(ButtonSettings_Click);
		ButtonViewOutput.RegisterMessage(ButtonViewOutput_Click);
		ButtonPreview.RegisterMessage(ButtonPreview_Click);
		ButtonRestart.RegisterMessage(ButtonRestart_Click);
		ButtonStart.RegisterMessage(ButtonStart_Click);

		// �ؼ��ص���͸
		ProcedureHelper::TransKeyMsgToParent(ButtonChooseAudio.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonChooseRawLyrics.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonOutputPath.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonPlayPause.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonAbout.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonSettings.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonViewOutput.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonPreview.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonRestart.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonStart.GetHandle(), WndProc);

		// ���ò��ְ�ť
		ButtonRestart.Enable(false);
	}

	/// <summary>
	/// ���ڴ�С�ı�ʱ���õķ��������ڿؼ�λ�úͳߴ�����Ӧ
	/// </summary>
	void ResizeMoveControls()
	{
		int left, top;
		int w = CanvasMain.GetWidth() / DPI_Scale;
		int h = CanvasMain.GetHeight() / DPI_Scale;

#pragma region ��������

		// �� HiEasyX ��һЩ���⣬Resize ��߿򽫱��
		auto width = w - (MARGIN_HORIZONTAL * 2 + TOP_LEFT_LABEL_MAX_WIDTH + BUTTON_WIDTH + CONTROL_PADDING_HORIZONTAL * 2);
		TextBoxChooseAudio.Resize(width, CONTROL_HEIGHT);
		TextBoxChooseRawLyrics.Resize(width, CONTROL_HEIGHT);
		TextBoxOutputPath.Resize(width, CONTROL_HEIGHT);

		left = w - MARGIN_HORIZONTAL - BUTTON_WIDTH;
		ButtonChooseAudio.Move(left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL);
		ButtonChooseRawLyrics.Move(left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL);
		ButtonOutputPath.Move(left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2);

#pragma endregion

#pragma region ��������

		top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;
		ButtonPlayPause.Move(left, BUTTON_HEIGHT_OFFSET + top);

#pragma endregion

#pragma region �ײ�����

		top = h - MARGIN_VERTICAL - BUTTON_HEIGHT;
		ButtonAbout.Move(MARGIN_HORIZONTAL, top);
		ButtonSettings.Move(MARGIN_HORIZONTAL + BUTTON_WIDTH + CONTROL_PADDING_HORIZONTAL, top);
		ButtonViewOutput.Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 4 - CONTROL_PADDING_HORIZONTAL * 5, top);
		ButtonPreview.Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 3 - CONTROL_PADDING_HORIZONTAL * 4, top);
		ButtonRestart.Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL, top);
		ButtonStart.Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH, top);

#pragma endregion
	}

#pragma endregion

#pragma region Canvas Drawing

	/// <summary>
	/// ���� UI
	/// </summary>
	void RefreshUI()
	{
		if (IsInDrawAtWndProcPaint || IsInRefreshUI) return;
		IsInRefreshUI = true;

		CanvasMain.Clear(true, BACKGROUND_COLOR);
		DrawAtWndProcPaint(true);
		wnd.Redraw();

		IsInRefreshUI = false;
	}

	/// <summary>
	/// �� Canvas �л����ı� (ʵ�� Label �ؼ�Ч��)
	/// </summary>
	void DrawLabelControls()
	{
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, 1 + MARGIN_VERTICAL, GetStringFromKey("String.Window.Main.SelectAudio").c_str());
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, 1 + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, GetStringFromKey("String.Window.Main.SelectLyrics").c_str());
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, 1 + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, GetStringFromKey("String.Window.Main.OutputPath").c_str());
	}

	/// <summary>
	/// ���Ʋ�������
	/// </summary>
	void DrawPlaybackArea()
	{
		auto top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;

		int w = CanvasMain.GetWidth() / DPI_Scale;
		int h = CanvasMain.GetHeight() / DPI_Scale;

#pragma region ��Ƶ����

		// ��ǰʱ��
		auto progress = MusicPlayer::GetCurrentPositionMs();
		auto timeStr = StringHelper::TimeMsToString(progress == -1 ? 0 : progress);
		timeStr = timeStr.substr(0, timeStr.length() - 1);
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, L"Consolas");
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top, (StringHelper::StringToWstring(timeStr)).c_str());

		// ������
		auto left = MARGIN_HORIZONTAL + (timeStr.length() == 7 ? 76 : 86);
		auto right = w - MARGIN_HORIZONTAL - BUTTON_WIDTH - CONTROL_PADDING_HORIZONTAL;
		double percent = progress == -1 ? 0 : (double)progress / MusicPlayer::GetTotalDurationMs();
		auto width = right - left;
		CanvasMain.GP_SetLineWidth(3);
		CanvasMain.GP_Line(left, top + 11, right, top + 11, true, RGB(0xBF, 0xBF, 0xBF));
		CanvasMain.GP_Line(left, top + 11, right - width * (1 - percent), top + 11, true, RGB(0x7F, 0x7F, 0x7F));
		CanvasMain.GP_SetLineWidth(1); // ��ԭ

#pragma endregion

#pragma region �������

		setfont(DEFAULT_CANVAS_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_BOLD, false, false, false);
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + LYRICS_PADDING_VERTICAL, GetStringFromKey("String.Window.Main.PreviousLine").c_str());
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + LYRICS_PADDING_VERTICAL * 2, GetStringFromKey("String.Window.Main.CurrentLine").c_str());
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + LYRICS_PADDING_VERTICAL * 3, GetStringFromKey("String.Window.Main.NextLine").c_str());

		// ��ԭ��������
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);

		// ���Ƹ���ı�
		// ��ͨ��ʣ��߶� �жϻ��ƶ��и��
		left = MARGIN_HORIZONTAL + 66;
		auto currentIndex = GetCurrentLineIndex();
		auto currentLine = GetCurrentLine(currentIndex);
		auto isCurrentLineHasEndTime = false;

		// ����һ��
		if (currentIndex - 1 >= 0)
		{
			auto previousLine = GetCurrentLine(currentIndex - 1);
			if (previousLine != nullptr)
			{
				CanvasMain.SetTextColor(previousLine->EndTime == -1 ? FOREGROUND_COLOR : RGB(0x7F, 0x7F, 0x7F));
				CanvasMain.OutTextXY(left, top + LYRICS_PADDING_VERTICAL, previousLine->Text.c_str());
			}
		}

		// ����ǰ��
		if (currentLine != nullptr && currentLine->EndTime != -1)
		{
			CanvasMain.SetTextColor(RGB(0x7F, 0x7F, 0x7F));
		}
		else
		{
			CanvasMain.SetTextColor(FOREGROUND_COLOR);
		}
		CanvasMain.OutTextXY(left, top + LYRICS_PADDING_VERTICAL * 2, GetCurrentLineString(currentIndex).c_str());

		// ��������
		auto lyricsHeight = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 10 - LYRICS_PADDING_VERTICAL * 4 - top;
		auto linesAvailable = lyricsHeight / LYRICS_PADDING_VERTICAL - 1;
		linesAvailable = linesAvailable < 1 ? 1 : linesAvailable;
		auto comingLines = GetComingLinesString(currentIndex, linesAvailable);
		CanvasMain.SetTextColor(RGB(0x7F, 0x7F, 0x7F));
		for (size_t i = 0; i < comingLines.size(); i++)
		{
			CanvasMain.OutTextXY(left, top + LYRICS_PADDING_VERTICAL * (i + 3), comingLines[i].c_str());
		}

#pragma endregion

#pragma region ��ʾ����

		const std::vector<std::wstring> Notices =
		{
			GetStringFromKey("String.Window.Main.NoticeLineStart"),
			GetStringFromKey("String.Window.Main.NoticeCurrentLineEnd"),
			GetStringFromKey("String.Window.Main.NoticePreviousLineEnd"),
			GetStringFromKey("String.Window.Main.NoticeReturnToPreviousLine"),
			GetStringFromKey("String.Window.Main.NoticePlayPause"),
			GetStringFromKey("String.Window.Main.NoticeSeekBack3s"),
			GetStringFromKey("String.Window.Main.NoticeSeekForward3s"),
			GetStringFromKey("String.Window.Main.NoticeSeekForward10s"),
			GetStringFromKey("String.Window.Main.NoticeSeekForward30s"),
			GetStringFromKey("String.Window.Main.NoticeSeekTo0s"),
		};

		top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12 - 36 - 24;
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_BOLD, false, false, false);
		CanvasMain.SetTextColor(FOREGROUND_COLOR);
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top, GetStringFromKey("String.Window.Main.KeyTips").c_str());
		setfont(DEFAULT_CANVAS_FONTSIZE - 1, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
		auto fullWidth = w - MARGIN_HORIZONTAL * 2 - 90 - 10;
		fullWidth /= Notices.size() / 2;
		for (int i = 0; i < Notices.size() / 2; i++)
		{
			CanvasMain.OutTextXY(MARGIN_HORIZONTAL + 90 + fullWidth * i, top + 1, Notices[i].c_str());
		}
		for (int i = Notices.size() / 2; i < Notices.size(); i++)
		{
			CanvasMain.OutTextXY(MARGIN_HORIZONTAL + 90 + fullWidth * (i - (int)Notices.size() / 2), top + 1 + 28, Notices[i].c_str());
		}

#pragma endregion

	}

	/// <summary>
	/// �ص�ʱ���õ��ػ淽��
	/// </summary>
	void DrawAtWndProcPaint(bool ignoreInRefreshUI = false)
	{
		if (IsInDrawAtWndProcPaint || IsInRefreshUI && !ignoreInRefreshUI) return;
		IsInDrawAtWndProcPaint = true;

		const auto LINE_COLOR = RGB(0xAF, 0xAF, 0xAF);
		const auto SUBLINE_COLOR = RGB(0xCF, 0xCF, 0xCF);
		int top;
		int w = CanvasMain.GetWidth() / DPI_Scale;
		int h = CanvasMain.GetHeight() / DPI_Scale;

		CanvasMain.SetBkColor(BACKGROUND_COLOR);
		DrawLabelControls();
		DrawPlaybackArea();

		// ��������ָ���
		top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 10;
		CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);

		// ��ʾ����ָ���
		top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12 - 50 - 20;
		CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);

		// �ײ�����ָ���
		top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12;
		CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);
		CanvasMain.Line(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL * 2.5, top + 10, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL * 2.5, top + 40, true, SUBLINE_COLOR);

		IsInDrawAtWndProcPaint = false;
	}

#pragma endregion

#pragma region Lyrics

	/// <summary>
	/// ��ȡ����ļ�����·�� (���ļ���)
	/// </summary>
	/// <returns>����ļ�����·�� (���ļ���)</returns>
	std::wstring GetOutputFullpath()
	{
		auto outputPath = TextBoxOutputPath.GetText();
		if (outputPath.empty())
		{
			TCHAR exePath[MAX_PATH];
			GetModuleFileName(NULL, exePath, MAX_PATH);
			outputPath = StringHelper::GetDirectoryFromPath(exePath) + L"\\output\\";
		}
		if (outputPath.back() != L'/' && outputPath.back() != '\\') outputPath += L'\\';
		FileHelper::EnsureDirectoryExists(outputPath);
		auto filename = StringHelper::GetFileNameFromPath(TextBoxChooseAudio.GetText());
		filename = StringHelper::ReplaceFileNameExtension(filename, L"lyl");
		return outputPath + filename;
	}

	/// <summary>
	/// ��ȡ��ǰ�е���� (�� 0 Ϊ���)
	/// </summary>
	/// <returns>��ǰ�е����</returns>
	int GetCurrentLineIndex()
	{
		for (int i = 0; i < (int)LyricsList.size(); i++)
		{
			if (LyricsList[i].StartTime == -1)
			{
				return i - 1;
			}
		}
		return (int)LyricsList.size() - 1;
	}

	/// <summary>
	/// ��ȡ��ǰ�еĸ�ʶ���
	/// </summary>
	/// <param name="index">ָ����ǰ�е���ţ�����ָ�����Զ����ҵ�ǰ��</param>
	/// <returns>��ǰ�еĸ�ʶ���</returns>
	Lyricify::Lyrics* GetCurrentLine(int index)
	{
		if (index == -1)
			index = GetCurrentLineIndex();

		if (index >= 0 && index < (int)LyricsList.size())
			return &LyricsList[index];

		return nullptr;
	}

	/// <summary>
	/// ��ȡ��ǰ�еĸ���ı�
	/// </summary>
	/// <param name="index">ָ����ǰ�е���ţ�����ָ�����Զ����ҵ�ǰ��</param>
	/// <returns>��ǰ�еĸ���ı�</returns>
	std::wstring GetCurrentLineString(int index)
	{
		if (index == -2)
			index = GetCurrentLineIndex();

		if (index >= 0 && index < (int)LyricsList.size())
			return LyricsList[index].Text;

		return L"";
	}

	/// <summary>
	/// ��ȡ�����еĸ���ı��б�
	/// </summary>
	/// <param name="index">ָ����ǰ�е���ţ�����ָ�����Զ����ҵ�ǰ��</param>
	/// <param name="maxSize">����ı��б���������</param>
	/// <returns>�����еĸ���ı��б�</returns>
	std::vector<std::wstring> GetComingLinesString(int index, size_t maxSize)
	{
		if (index == -2)
			index = GetCurrentLineIndex();

		std::vector<std::wstring> strings;
		for (int i = index + 1; i < (int)LyricsList.size() && (maxSize == -1 || strings.size() < maxSize); i++)
		{
			strings.push_back(LyricsList[i].Text);
		}
		return strings;
	}

#pragma endregion

#pragma region Window

	/// <summary>
	/// ��ȡ�����������
	/// </summary>
	/// <returns>�����������</returns>
	RECT GetWindowRect()
	{
		auto pos = wnd.GetPos();
		auto size = wnd.GetWindowSize();
		return { pos.x, pos.y, pos.x + size.cx, pos.y + size.cy };
	}

	/// <summary>
	/// �����ڻص�����
	/// </summary>
	/// <param name="hWnd">���ھ��</param>
	/// <param name="msg">��ϢID</param>
	/// <param name="wParam">��Ϣ���� wParam</param>
	/// <param name="lParam">��Ϣ���� lParam</param>
	/// <returns></returns>
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_PAINT:
			DrawAtWndProcPaint();
			break;

		case WM_SIZE:
		{
			CanvasMain.Clear(true, BACKGROUND_COLOR);
			ResizeMoveControls();
			break;
		}

		case WM_GETMINMAXINFO:
		{
			MINMAXINFO* pmmi = (MINMAXINFO*)lParam;
			pmmi->ptMinTrackSize.x = MIN_WINDOW_WIDTH * DPI_Scale;
			pmmi->ptMinTrackSize.y = MIN_WINDOW_HEIGHT * DPI_Scale;
			return 0;
		}

		case WM_KEYDOWN:
		case WM_IME_KEYDOWN:
			KeyboardEvents(wParam);
			break;

		default:
			return HIWINDOW_DEFAULT_PROC;
			break;
		}

		return 0;
	}

	void Show(double scale)
	{
		DPI_Scale = scale;

		// ��ʼ������
		wnd.InitWindow(WINDOW_WIDTH * DPI_Scale, WINDOW_HEIGHT * DPI_Scale, EW_NORMAL, L"Lyricify Lines Creator");
		wnd.BindCanvas(&CanvasMain);
		wnd.SetProcFunc(WndProc);
		ImmAssociateContext(wnd.GetHandle(), NULL); // �����н��� IME
		hiex::AutoExit();

		setaspectratio(DPI_Scale, DPI_Scale);
		CanvasMain.SetTextColor(FOREGROUND_COLOR);

		// ���� Canvas ���壬�ο��ĵ�: https://docs.easyx.cn/zh-cn/LOGFONT
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, DEFAULT_FONT, 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);

		// ���ƴ���ؼ�
		AddWindowControls(wnd.GetHandle());
		wnd.Redraw(); // �����ػ洰�� ����ʹ�û��Ƶ��ı���ʾ����

		// �رմ��ڣ���������
		hiex::init_end(wnd.GetHandle());
	}

#pragma endregion
}
