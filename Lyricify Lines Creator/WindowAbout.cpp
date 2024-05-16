#include "WindowAbout.h"

namespace WindowAbout
{
	enum WA_URL_INDEX
	{
		WA_URL_INDEX_NONE,
		WA_URL_INDEX_WXRIW,
		WA_URL_INDEX_EASYX,
		WA_URL_INDEX_HIEASYX,
		WA_URL_INDEX_IRRKLANG,
	};

	constexpr auto URL_COLOR = RGB(68, 147, 248);

	bool isOpened = false;
	hiex::Window* Window;
	hiex::Canvas* CanvasMain;
	std::vector<RECT> UrlAreas;
	std::vector<std::wstring> Urls;
	double DPI_Scale = 1;
	POINT lastMouseLDownPos;

	static void AddUrl(RECT rect, std::wstring url)
	{
		rect.left *= DPI_Scale;
		rect.right *= DPI_Scale;
		rect.top *= DPI_Scale;
		rect.bottom *= DPI_Scale;
		UrlAreas.push_back(rect);
		Urls.push_back(url);
	}

	static void DrawCanvas(bool init = true, WA_URL_INDEX highlight = WA_URL_INDEX_NONE)
	{
		// ��ֹ����������ͬ�������������ʧ
		static WA_URL_INDEX lastIndex = WA_URL_INDEX_NONE;
		if (!init && lastIndex == highlight) return;
		lastIndex = highlight;

		int TITLE_FONTSIZE = 24;
		int SUBTITLE_FONTSIZE = 20 - (DPI_Scale - 1) * 2;
		int ITEM_FONTSIZE = 18 - (DPI_Scale - 1) * 2;
		int URL_FONTSIZE = 14 - (DPI_Scale - 1) * 2;

		if (!init) CanvasMain->Clear();
		int w = CanvasMain->GetWidth() / DPI_Scale;
		int top = 0;
		std::wstring url;
		SIZE size;

		CanvasMain->SetTextColor(BLACK);
		setfont(TITLE_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_BOLD, false, false, false);
		CanvasMain->CenterText(L"Lyricify Lines Creator", { 0, 20, w, 45 });
		setfont(SUBTITLE_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
		CanvasMain->CenterText(L"Lyricify Lines ���и�ʴ��Ṥ��", { 0, 47, w, 67 });
		CanvasMain->SetTextColor(GRAY);
		setfont(16 + (DPI_Scale - 1) * 1, 0, L"Consolas", 0, 0, FW_DONTCARE, false, false, false);
		CanvasMain->CenterText((std::wstring(L"Version ") + std::wstring(VERSION)).c_str(), { 0, 73, w, 93 });

		top += 110;
		CanvasMain->SetTextColor(BLACK);
		setfont(SUBTITLE_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
		CanvasMain->CenterText(L"������", { 0, top, w, top + 20 }); top += 26;
		CanvasMain->SetTextColor(GRAY);

		setfont(ITEM_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
		size = FontHelper::CalculateTextSize(L"Xiaoyang Wang", DEFAULT_FONT, 16, DPI_Scale, FW_DONTCARE, false, false, false);
		if (init) AddUrl({ (w - size.cx) / 2, top, (w + size.cx) / 2, top + 20 }, L"https://github.com/WXRIW");
		if (highlight == WA_URL_INDEX_WXRIW) { CanvasMain->SetTextColor(URL_COLOR); setfont(ITEM_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, true, false); }
		CanvasMain->CenterText(L"Xiaoyang Wang", { 0, top, w, top + 20 }); top += 20;
		if (highlight == WA_URL_INDEX_WXRIW) { CanvasMain->SetTextColor(GRAY); setfont(ITEM_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false); }
		CanvasMain->CenterText(L"Tianle Chen", { 0, top, w, top + 20 }); top += 20;
		CanvasMain->CenterText(L"Junze Zhang", { 0, top, w, top + 20 }); top += 20;

		top += 20;
		CanvasMain->SetTextColor(BLACK);
		setfont(18, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
		CanvasMain->CenterText(L"������֪ͨ", { 0, top, w, top + 20 }); top += 26;
		CanvasMain->SetTextColor(GRAY);

		setfont(ITEM_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
		CanvasMain->CenterText(L"HiEasyX (MIT Э��)", { 0, top, w, top + 20 }); top += 20;
		setfont(URL_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, true, false);
		url = L"https://github.com/zouhuidong/HiEasyX/blob/main/LICENSE";
		size = FontHelper::CalculateTextSize(url.c_str(), DEFAULT_FONT, URL_FONTSIZE, DPI_Scale, FW_DONTCARE, false, false, false);
		if (init) AddUrl({ (w - size.cx) / 2, top, (w + size.cx) / 2, top + 15 }, url);
		if (highlight == WA_URL_INDEX_EASYX) CanvasMain->SetTextColor(URL_COLOR);
		CanvasMain->CenterText(url.c_str(), { 0, top, w, top + 15 }); top += 22;
		if (highlight == WA_URL_INDEX_EASYX) CanvasMain->SetTextColor(GRAY);

		setfont(ITEM_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
		CanvasMain->CenterText(L"EasyX", { 0, top, w, top + 20 }); top += 20;
		setfont(URL_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, true, false);
		url = L"https://easyx.cn/copyright";
		size = FontHelper::CalculateTextSize(url.c_str(), DEFAULT_FONT, URL_FONTSIZE, DPI_Scale, FW_DONTCARE, false, false, false);
		if (init) AddUrl({ (w - size.cx) / 2, top, (w + size.cx) / 2, top + 15 }, url);
		if (highlight == WA_URL_INDEX_HIEASYX) CanvasMain->SetTextColor(URL_COLOR);
		CanvasMain->CenterText(url.c_str(), { 0, top, w, top + 15 }); top += 22;
		if (highlight == WA_URL_INDEX_HIEASYX) CanvasMain->SetTextColor(GRAY);

		setfont(ITEM_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
		CanvasMain->CenterText(L"irrKlang", { 0, top, w, top + 20 }); top += 20;
		setfont(URL_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, true, false);
		url = L"https://www.ambiera.com/irrklang/license.html";
		size = FontHelper::CalculateTextSize(url.c_str(), DEFAULT_FONT, URL_FONTSIZE, DPI_Scale, FW_DONTCARE, false, false, false);
		if (init) AddUrl({ (w - size.cx) / 2, top, (w + size.cx) / 2, top + 15 }, url);
		if (highlight == WA_URL_INDEX_IRRKLANG) CanvasMain->SetTextColor(URL_COLOR);
		CanvasMain->CenterText(url.c_str(), { 0, top, w, top + 15 }); top += 22;
		if (highlight == WA_URL_INDEX_IRRKLANG) CanvasMain->SetTextColor(GRAY);

		Window->Redraw();
	}

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_SETCURSOR:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);

			if (PtInRect(&UrlAreas[0], pt))
			{
				SetCursor(LoadCursor(NULL, IDC_HAND));
				DrawCanvas(false, WA_URL_INDEX_WXRIW);
				return TRUE;
			}
			else if (PtInRect(&UrlAreas[1], pt))
			{
				SetCursor(LoadCursor(NULL, IDC_HAND));
				DrawCanvas(false, WA_URL_INDEX_EASYX);
				return TRUE;
			}
			else if (PtInRect(&UrlAreas[2], pt))
			{
				SetCursor(LoadCursor(NULL, IDC_HAND));
				DrawCanvas(false, WA_URL_INDEX_HIEASYX);
				return TRUE;
			}
			else if (PtInRect(&UrlAreas[3], pt))
			{
				SetCursor(LoadCursor(NULL, IDC_HAND));
				DrawCanvas(false, WA_URL_INDEX_IRRKLANG);
				return TRUE;
			}
			else
			{
				SetCursor(LoadCursor(NULL, IDC_ARROW));
				DrawCanvas(false);
				return TRUE;
			}
			break;
		}

		case WM_LBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);

			lastMouseLDownPos = { xPos, yPos };

			break;
		}

		case WM_LBUTTONUP:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);

			if (xPos == lastMouseLDownPos.x && yPos == lastMouseLDownPos.y)
			{
				POINT pt;
				GetCursorPos(&pt);
				ScreenToClient(hWnd, &pt);

				if (PtInRect(&UrlAreas[0], pt))
				{
					ShellExecute(NULL, L"open", Urls[0].c_str(), NULL, NULL, SW_SHOWNORMAL);
				}
				else if (PtInRect(&UrlAreas[1], pt))
				{
					ShellExecute(NULL, L"open", Urls[1].c_str(), NULL, NULL, SW_SHOWNORMAL);
				}
				else if (PtInRect(&UrlAreas[2], pt))
				{
					ShellExecute(NULL, L"open", Urls[2].c_str(), NULL, NULL, SW_SHOWNORMAL);
				}
				else if (PtInRect(&UrlAreas[3], pt))
				{
					ShellExecute(NULL, L"open", Urls[3].c_str(), NULL, NULL, SW_SHOWNORMAL);
				}
			}

			break;
		}

		default:
			return HIWINDOW_DEFAULT_PROC;
			break;
		}

		return 0;
	}

	static void OpenWindow(double scale, RECT rect, HWND hParent = (HWND)nullptr)
	{
		isOpened = true;
		const int WIDTH = 360;
		const int HEIGHT = 380;
		DPI_Scale = scale;

		hiex::Window wnd;
		hiex::Canvas canvas;
		Window = &wnd;
		CanvasMain = &canvas;
		if (rect.left != -1 && rect.right != -1 && rect.top != -1 && rect.bottom != -1)
		{
			int left = (rect.left + rect.right - WIDTH * DPI_Scale) / 2;
			int top = (rect.top + rect.bottom - HEIGHT * DPI_Scale) / 2;
			wnd.PreSetPos(left, top);
		}
		wnd.InitWindow(WIDTH * DPI_Scale, HEIGHT * DPI_Scale, EW_NORMAL, L"����", nullptr, hParent);
		DisableResizing(wnd.GetHandle(), true);
		WindowHelper::EnableMinimizeButton(wnd.GetHandle(), false);

		wnd.BindCanvas(&canvas);
		wnd.SetProcFunc(WndProc);
		setfont(20, 0, DEFAULT_FONT, 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
		setaspectratio(DPI_Scale, DPI_Scale);

		DrawCanvas();

		hiex::init_end(wnd.GetHandle());
		BringWindowToTop(hParent); // ����������ʾ�����Ϸ�
		isOpened = false;
	}

	void Show(double DPI_Scale, RECT rect, HWND hParent)
	{
		if (!isOpened)
		{
			std::thread(OpenWindow, DPI_Scale, rect, hParent).detach();
		}
	}

	bool IsOpened()
	{
		return isOpened;
	}
}
