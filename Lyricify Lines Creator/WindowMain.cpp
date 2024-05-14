#include "WindowMain.h"

namespace WindowMain
{
	double DPI_Scale = 1;

	// ����������� Label �Ŀ�ȣ����ڱ��ػ�ʱ��������ĳߴ�
	int TOP_LEFT_LABEL_MAX_WIDTH = 65;

#pragma region Controls

#pragma region Control Definations

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
	hiex::SysButton ButtonViewOutput;
	hiex::SysButton ButtonPreview;
	hiex::SysButton ButtonRestart;
	hiex::SysButton ButtonStart;

#pragma endregion

#pragma region Button Clicks

	void ButtonChooseAudio_Click()
	{
		auto path = FileHelper::SelectFile(L"ѡ����Ƶ", L"��Ƶ (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg");
		if (!path.empty())
		{
			TextBoxChooseAudio.SetText(path);

			if (!MusicPlayer::Load(path))
			{
				MessageBox(wnd.GetHandle(), L"��Ƶ����ʧ�ܣ�", L"����ʧ��", MB_OK);
			}
		}
	}

	void ButtonChooseRawLyrics_Click()
	{
		auto path = FileHelper::SelectFile(L"ѡ����", L"�ı��ĵ� (*.txt)\0*.txt");
		if (!path.empty())
		{
			TextBoxChooseRawLyrics.SetText(path);
		}
	}

	void ButtonOutputPath_Click()
	{
		auto path = FileHelper::SelectFolder(L"ѡ�񵼳�·��");
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
			ButtonPlayPause.SetText(L"����");
		}
		else
		{
			if (MusicPlayer::CurrentAudioPath.empty() && !TextBoxChooseAudio.GetText().empty()
				|| MusicPlayer::CurrentAudioPath != TextBoxChooseAudio.GetText())
			{
				// û�м�����Ƶ������Ƶ���ʱ����Ҫ���¼���
				if (!MusicPlayer::Load(TextBoxChooseAudio.GetText()))
				{
					MessageBox(wnd.GetHandle(), L"��Ƶ����ʧ�ܣ�", L"����ʧ��", MB_OK);
				}
			}

			MusicPlayer::Play();
			ButtonPlayPause.SetText(L"��ͣ");

			std::thread([]()
				{
					std::wstring audio = MusicPlayer::CurrentAudioPath;
					while (audio == MusicPlayer::CurrentAudioPath && MusicPlayer::IsPlaying())
					{
						if (!WindowAbout::IsOpened())
						{
							// ���ڱ���ʱ������ˢ�½��ȣ���ֹ��Ⱦ����
							CanvasMain.Clear(true, BACKGROUND_COLOR);
							DrawAtWndProcPaint();
							wnd.Redraw();
						}
						TaskHelper::Delay(25).wait();
					}
					if (!MusicPlayer::IsPlaying())
					{
						ButtonPlayPause.SetText(L"����");
					}
				}).detach();
		}
	}

	void ButtonAbout_Click()
	{
		WindowAbout::Show(DPI_Scale, GetWindowRect(), wnd.GetHandle());
	}

	void ButtonViewOutput_Click()
	{

	}

	void ButtonPreview_Click()
	{

	}

	void ButtonRestart_Click()
	{

	}

	void ButtonStart_Click()
	{

	}

#pragma endregion

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
		ButtonChooseAudio.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL, BUTTON_WIDTH, BUTTON_HEIGHT, L"������Ƶ");
		ButtonChooseRawLyrics.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, BUTTON_WIDTH, BUTTON_HEIGHT, L"������");
		ButtonOutputPath.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, BUTTON_WIDTH, BUTTON_HEIGHT, L"ѡ��·��");

#pragma endregion

#pragma region ��������

		top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;
		ButtonPlayPause.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + top, BUTTON_WIDTH, BUTTON_HEIGHT, L"����");

#pragma endregion

#pragma region �ײ�����

		top = h - MARGIN_VERTICAL - BUTTON_HEIGHT;
		ButtonAbout.Create(hwnd, MARGIN_HORIZONTAL, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"����");
		ButtonViewOutput.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 4 - CONTROL_PADDING_HORIZONTAL * 5, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"�鿴���");
		ButtonPreview.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 3 - CONTROL_PADDING_HORIZONTAL * 4, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"Ԥ��Ч��");
		ButtonRestart.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"��������");
		ButtonStart.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"��ʼ����");

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
		ButtonViewOutput.RegisterMessage(ButtonViewOutput_Click);
		ButtonPreview.RegisterMessage(ButtonPreview_Click);
		ButtonRestart.RegisterMessage(ButtonRestart_Click);
		ButtonStart.RegisterMessage(ButtonStart_Click);
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
		ButtonViewOutput.Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 4 - CONTROL_PADDING_HORIZONTAL * 5, top);
		ButtonPreview.Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 3 - CONTROL_PADDING_HORIZONTAL * 4, top);
		ButtonRestart.Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL, top);
		ButtonStart.Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH, top);

#pragma endregion
	}

#pragma endregion

#pragma region Canvas Drawing

	/// <summary>
	/// �� Canvas �л����ı� (ʵ�� Label �ؼ�Ч��)
	/// </summary>
	void DrawLabelControls()
	{
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, 1 + MARGIN_VERTICAL, L"ѡ����Ƶ��");
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, 1 + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, L"ѡ���ʣ�");
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, 1 + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, L"���·����");
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
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + LYRICS_PADDING_VERTICAL, L"��ǰ�У�");
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + LYRICS_PADDING_VERTICAL * 2, L"��һ�У�");

		// ��ԭ��������
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);

		// ���Ƹ���ı�
		// ��ͨ��ʣ��߶� �жϻ��ƶ��и��

#pragma endregion

#pragma region ��ʾ����

		top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12 - 36;
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_BOLD, false, false, false);
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top, L"������ʾ��");
		setfont(DEFAULT_CANVAS_FONTSIZE - 1, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL + 80, top + 1, L"����ʼ����     �н�������     �ص���һ�У���     ���� 3s��B     ǰ�� 3s��N     ǰ�� 10s��M     ����/��ͣ��Space");

#pragma endregion

	}

	/// <summary>
	/// �ص�ʱ���õ��ػ淽��
	/// </summary>
	void DrawAtWndProcPaint()
	{
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
		top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12 - 50;
		CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);

		// �ײ�����ָ���
		top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12;
		CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);
		CanvasMain.Line(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL * 2.5, top + 10, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL * 2.5, top + 40, true, SUBLINE_COLOR);
	}

#pragma endregion

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

		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_SPACE:
				ButtonPlayPause_Click();
				break;

			case 'B':
				MusicPlayer::SeekBack(3000);
				break;

			case 'N':
				MusicPlayer::SeekForward(3000);
				break;

			case 'M':
				MusicPlayer::SeekForward(10000);
				break;

			default:
				break;
			}
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
		wnd.InitWindow(WINDOW_WIDTH * DPI_Scale, WINDOW_HEIGHT * DPI_Scale, EW_NORMAL, L"Lyricify Lyrics Creator");
		wnd.BindCanvas(&CanvasMain);
		wnd.SetProcFunc(WndProc);
		hiex::AutoExit();

		setaspectratio(DPI_Scale, DPI_Scale);
		CanvasMain.SetTextColor(BLACK);

		// ���� Canvas ���壬�ο��ĵ�: https://docs.easyx.cn/zh-cn/LOGFONT
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, DEFAULT_FONT, 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);

		// ���ƴ���ؼ�
		AddWindowControls(wnd.GetHandle());
		wnd.Redraw(); // �����ػ洰�� ����ʹ�û��Ƶ��ı���ʾ����

		// �رմ��ڣ���������
		hiex::init_end(wnd.GetHandle());
	}
}
