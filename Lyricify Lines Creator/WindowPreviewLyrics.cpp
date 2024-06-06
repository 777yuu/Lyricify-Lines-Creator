/************************************************************************
 * Filename:    WindowPreviewLyrics.cpp
 * Description: Ԥ����ʴ���ʵ��
 * Author:      XY Wang, TL Chen, JZ Zhang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "WindowPreviewLyrics.h"

namespace WindowPreviewLyrics
{
	const int WINDOW_WIDTH = 500;
	const int WINDOW_HEIGHT = 500;
	const int MIN_WINDOW_WIDTH = 500;
	const int MIN_WINDOW_HEIGHT = 400;

	bool IsInRefreshUI = false;
	bool IsInDrawAtWndProcPaint = false;
	bool isOpened = false;
	double DPI_Scale = 1;

	hiex::Window* Window;
	hiex::Canvas* CanvasMain;
	hiex::SysButton* ButtonPlayPause;
	std::vector<Lyricify::Lyrics> LyricsList;

	/// <summary>
	/// ���������������� Lyricify �ṩ
	/// </summary>
	static double FuncEase(double x)
	{
		x = x * 0.9793195;
		auto a = -10.55 * std::pow(x, 7) + 42.76 * std::pow(x, 6) - 73.36 * std::pow(x, 5) + 70.9 * std::pow(x, 4) - 41.89 * std::pow(x, 3) + 12.98 * std::pow(x, 2) + 0.1638 * x;
		return a / 1.0041521796874393;
	}

	/// <summary>
	/// ���ƻ���
	/// </summary>
	static void DrawAtWndProcPaint(bool ignoreInRefreshUI = false)
	{
		if (IsInDrawAtWndProcPaint || IsInRefreshUI && !ignoreInRefreshUI) return;
		IsInDrawAtWndProcPaint = true;

		int w = CanvasMain->GetWidth() / DPI_Scale;
		int h = CanvasMain->GetHeight() / DPI_Scale;

		CanvasMain->SetBkColor(BACKGROUND_COLOR);

		// TODO: ����д���壨��ʲ��֣�Ӧ����ô��

		int index = 0;
		const int SCROLL_DURATION = 600;
		const int LINE_HEIGHT = 42;
		int currentTime = MusicPlayer::GetCurrentPositionMs();

		// �ҵ���ǰ���Ÿ�ʵ�����index
		for (int i = LyricsList.size() - 1; i >= 0; i--)
		{
			if (currentTime >= LyricsList[i].StartTime - SCROLL_DURATION)
			{
				index = i;
				break;
			}
		}

		// ���㵱ǰ��ʲ��Űٷֱȣ����Դ�Ϊ��׼������Ӧ����
		// �ֱ�����Ѳ��Ÿ�ʣ����䣩�����ڲ��Ÿ�ʡ��������Ÿ��

		auto current = LyricsList[index].StartTime - currentTime;
		auto progress = (double)current / SCROLL_DURATION;
		if (progress < 0)
		{
			progress = 0;
		}
		if (progress > 1)
		{
			progress = 1;
		}

		auto realProgress = progress;
		progress = 1 - FuncEase(1 - progress);

		/* �Ѳ��Ÿ�� */
		// ��ɫ����Ϊ��ɫ
		// Ĭ�������С22
		int fontSize = 22;
		setfont(fontSize * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH), 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_DONTCARE, false, false, false);
		CanvasMain->SetTextColor(GRAY);

		// Ĭ�϶����߶�70
		int HEAD = 70;
		auto lineHeight = LINE_HEIGHT * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH);

		// ������
		int rownum = (h - HEAD) / lineHeight;
		if (rownum % 2 == 0)
		{
			rownum -= 1;
		}
		int headSpace = HEAD;

		// �и�
		lineHeight = (double)(h - HEAD) / rownum;

		for (int i = rownum / 2; i > 0; i--)
		{
			// �жϸ���Ƿ����
			if (index - i >= 0)
			{
				// ����������ɫ���䣬�ڡ�>��
				// ���������С�洰�ڴ�С�仯���仯
				if (i == 1)
				{
					// ��ǰ���Ÿ�ʲ����������ɴ�С�仯
					setfont(fontSize * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH) + 6 * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH) * progress, 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_DONTCARE, false, false, false);
					// ��ǰ���Ÿ�ʲ�������ɫ�ɺڱ�ҽ���
					CanvasMain->SetTextColor(RGB(127 * (1 - realProgress), 127 * (1 - realProgress), 127 * (1 - realProgress)));
				}
				else
				{
					setfont(fontSize * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH), 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_DONTCARE, false, false, false);
					CanvasMain->SetTextColor(GRAY);
				}
				RECT rect = { MARGIN_HORIZONTAL,
					(LONG)(headSpace + (lineHeight * progress) + lineHeight * (rownum / 2 - i)),
					w - MARGIN_HORIZONTAL,
					(LONG(headSpace + (lineHeight * progress) + lineHeight + lineHeight * (rownum / 2 - i))) };
				CanvasMain->CenterText(LyricsList[static_cast<std::vector<Lyricify::Lyrics, std::allocator<Lyricify::Lyrics>>::size_type>(index) - i].Text.c_str(), rect);
			}
		}

		/* ��ǰ���Ÿ�� */
		// ��ǰ��ʿ�ʼ������ɫ�ɻұ�ڽ���
		CanvasMain->SetTextColor(RGB(127 * realProgress, 127 * realProgress, 127 * realProgress));
		// ��ǰ��ʿ�ʼ����������С����仯
		setfont(fontSize * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH) + 6 * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH) * (1 - progress), 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_DONTCARE, false, false, false);
		RECT r = { MARGIN_HORIZONTAL,
			(LONG)(headSpace + (lineHeight * progress) + lineHeight * (rownum - 1) / 2),
			w - MARGIN_HORIZONTAL ,
			(LONG(headSpace + (lineHeight * progress) + lineHeight + lineHeight * (rownum - 1) / 2)) };
		CanvasMain->CenterText(LyricsList[index].Text.c_str(), r);

		// �������Ÿ�� ������ɫΪ��ɫ
		// ���ݴ��ڸ߶Ȼ�����Ӧ�������
		setfont(fontSize * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH), 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_DONTCARE, false, false, false);

		for (int i = 1; i <= rownum / 2; i++)
		{
			CanvasMain->SetTextColor(GRAY);

			if ((unsigned long long)index + i < LyricsList.size())
			{
				RECT rect = { MARGIN_HORIZONTAL,
					(LONG)(headSpace + (lineHeight * progress) + lineHeight * (rownum / 2 + i)),
					w - MARGIN_HORIZONTAL,
					(LONG)(headSpace + (lineHeight * progress) + lineHeight + lineHeight * (rownum / 2 + i)) };

				CanvasMain->CenterText(LyricsList[static_cast<std::vector<Lyricify::Lyrics, std::allocator<Lyricify::Lyrics>>::size_type>(index) + i].Text.c_str(), rect);
			}
		}

		/* ���ƽ����� */
		// �ڽ�����������Ѳ���ʱ�� 
		// �ڽ�����������ܲ���ʱ��

		// �����߶�45
		auto top = 45;

		// ��ǰ���Ž���
		auto progress1 = MusicPlayer::GetCurrentPositionMs();

		// ��ȡʱ��
		auto timeStr = StringHelper::TimeMsToString(progress1 == -1 ? 0 : progress1);
		// ����ʱ�������ʽ
		auto timeStr1 = timeStr.substr(0, timeStr.length() - 1);
		// �������Ҿ���
		auto left = MARGIN_HORIZONTAL + (timeStr.length() == 7 ? 76 : 86);
		auto right = w - MARGIN_HORIZONTAL - BUTTON_WIDTH - CONTROL_PADDING_HORIZONTAL;
		double percent = progress1 == -1 ? 0 : (double)progress1 / MusicPlayer::GetTotalDurationMs();
		auto width = right - left;

		// ��ʱ��
		auto progress2 = MusicPlayer::GetTotalDurationMs();
		// ��ȡʱ��
		auto timeTotalStr = StringHelper::TimeMsToString(progress2);
		// ����ʱ�������ʽ
		auto timeTotalStr1 = timeTotalStr.substr(0, timeTotalStr.length() - 1);

		setfont(DEFAULT_CANVAS_FONTSIZE, 0, L"Consolas");
		CanvasMain->OutTextXY(MARGIN_HORIZONTAL, top, (StringHelper::StringToWstring(timeStr1)).c_str());
		CanvasMain->OutTextXY(right + 20, top, (StringHelper::StringToWstring(timeTotalStr1).c_str()));

		CanvasMain->GP_SetLineWidth(3);
		CanvasMain->GP_Line(left, top + 11, right, top + 11, true, RGB(0xBF, 0xBF, 0xBF));
		CanvasMain->GP_Line(left, top + 11, right - width * (1 - percent), top + 11, true, RGB(0x7F, 0x7F, 0x7F));
		CanvasMain->GP_SetLineWidth(1);

		IsInDrawAtWndProcPaint = false;
	}

	/// <summary>
	/// ˢ�� UI (��������)
	/// </summary>
	static void RefreshUI()
	{
		if (IsInDrawAtWndProcPaint || IsInRefreshUI) return;

		IsInRefreshUI = true;

		CanvasMain->Clear(true, BACKGROUND_COLOR);
		DrawAtWndProcPaint(true);
		Window->Redraw();

		IsInRefreshUI = false;
	}

	static void ButtonPlayPause_Click()
	{
		if (MusicPlayer::IsPlaying())
		{
			MusicPlayer::Pause();
			ButtonPlayPause->SetText(L"����");
		}
		else
		{
			MusicPlayer::SetPlaybackSpeed(); // ���ò����ٶȵ� 1.0x
			MusicPlayer::Play();
			ButtonPlayPause->SetText(L"��ͣ");

			std::thread([]()
				{
					static bool IsRefreshThreadRunning = false;
					if (IsRefreshThreadRunning) return;

					IsRefreshThreadRunning = true;

					std::wstring audio = MusicPlayer::CurrentAudioPath;
					while (audio == MusicPlayer::CurrentAudioPath && MusicPlayer::IsPlaying())
					{
						if (true) //!WindowAbout::IsOpened() && !WindowPreviewOutput::IsOpened()) // ���ڱ���ʱ������ˢ�½��ȣ���ֹ��Ⱦ����
						{
							RefreshUI();
						}
						TaskHelper::Delay(10).wait();
					}
					if (!MusicPlayer::IsPlaying())
					{
						ButtonPlayPause->SetText(L"����");
					}

					IsRefreshThreadRunning = false;
				}).detach();
		}
	}

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_PAINT:
			DrawAtWndProcPaint();
			break;

		case WM_SIZE:
		{
			CanvasMain->Clear(true, BACKGROUND_COLOR);

			int w = CanvasMain->GetWidth() / DPI_Scale;
			int h = CanvasMain->GetHeight() / DPI_Scale;

			// TODO: ����д���ڴ�С�ı����жԿؼ����簴ť������λ�úͳߴ�
			ButtonPlayPause->Move(w / 2 - BUTTON_WIDTH / 2, 10);

			break;
		}

		case WM_GETMINMAXINFO:
		{
			MINMAXINFO* pmmi = (MINMAXINFO*)lParam;
			pmmi->ptMinTrackSize.x = MIN_WINDOW_WIDTH * DPI_Scale;
			pmmi->ptMinTrackSize.y = MIN_WINDOW_HEIGHT * DPI_Scale;
			return 0;
		}

		default:
			return HIWINDOW_DEFAULT_PROC;
			break;
		}

		return 0;
	}

	static void OpenWindow(double scale, std::vector<Lyricify::Lyrics> lyricsList, RECT rect, HWND hParent = (HWND)nullptr)
	{
		isOpened = true;
		DPI_Scale = scale;
		LyricsList = lyricsList;

		/* ��һ������ʱ���ݣ����ڷ��㿪�� */

		//try
		//{
		//	// ����һ�θ�� ���ڲ���
		//	TCHAR exePath[MAX_PATH];
		//	GetModuleFileName(NULL, exePath, MAX_PATH);
		//	auto filePath = StringHelper::GetDirectoryFromPath(exePath) + L"\\Lyrics.txt";
		//	auto lyricsRaw = StringHelper::StringToWstring(FileHelper::ReadAllText(filePath));
		//	auto lyrics = Lyricify::LyricsHelper::ParseLyricsFromLyricifyLinesString(lyricsRaw);
		//	LyricsList = lyrics;

		//	// ���ض�Ӧ����
		//	MusicPlayer::Load(StringHelper::GetDirectoryFromPath(exePath) + L"\\Audio.mp3");
		//}
		//catch (...)
		//{
		//	MessageBox(NULL, L"���ظ�ʻ����ʧ�ܣ�\n��ȷ�� Audio.mp3 �� Lyrics.txt �����ҿ��á�", L"����ʧ��", MB_OK);
		//}

		/* ��ʱ���ݽ��� */

		hiex::Window wnd;
		hiex::Canvas canvas;
		hiex::SysButton buttonPlayPause;
		Window = &wnd;
		CanvasMain = &canvas;
		ButtonPlayPause = &buttonPlayPause;
		if (rect.left != -1 && rect.right != -1 && rect.top != -1 && rect.bottom != -1)
		{
			int left = (rect.left + rect.right - WINDOW_WIDTH * DPI_Scale) / 2;
			int top = (rect.top + rect.bottom - WINDOW_HEIGHT * DPI_Scale) / 2;
			wnd.PreSetPos(left, top);
		}
		wnd.InitWindow(WINDOW_WIDTH * DPI_Scale, WINDOW_HEIGHT * DPI_Scale, EW_NORMAL, GetStringFromKey("String.Window.PreviewLyrics").c_str(), nullptr, hParent);
		if (hParent != (HWND)nullptr) WindowHelper::EnableMinimizeButton(wnd.GetHandle(), false);

		wnd.BindCanvas(&canvas);
		wnd.SetProcFunc(WndProc);
		setfont(20, 0, SettingsHelper::Settings.GetFont(), 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
		setaspectratio(DPI_Scale, DPI_Scale);

		// TODO: ��ť�Ĵ���

		int w = CanvasMain->GetWidth() / DPI_Scale;
		int h = CanvasMain->GetHeight() / DPI_Scale;

		ButtonPlayPause->Create(Window->GetHandle(), w / 2 - 40, 10, BUTTON_WIDTH, BUTTON_HEIGHT, L"����");
		ButtonPlayPause->RegisterMessage(ButtonPlayPause_Click);
		ButtonPlayPause->SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());

		wnd.Redraw();
		TaskHelper::Delay(10).wait();

		if (SettingsHelper::Settings.IsPreviewLyricsOpenMaximize)
		{
			// ��󻯴���
			PostMessage(wnd.GetHandle(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}

		hiex::init_end(wnd.GetHandle());
		MusicPlayer::Pause();
		if (hParent != (HWND)nullptr) BringWindowToTop(hParent); // ����������ʾ�����Ϸ�
		isOpened = false;
	}

	void Show(std::vector<Lyricify::Lyrics> lyricsList, double DPI_Scale, RECT rect, HWND hParent)
	{
		if (!isOpened)
		{
			std::thread(OpenWindow, DPI_Scale, lyricsList, rect, hParent).detach();
		}
	}

	bool IsOpened()
	{
		return isOpened;
	}
}
