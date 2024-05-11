#include "DpiHelper.h"

#include <fstream>
#include <vector>
#include <string>

#include "HiEasyX.h"
#include "LyricsHelper.h"
#include "resource.h"

#pragma warning(disable: 4244) // ����ת����ʧ�� warning

#pragma region Const Definations

#define ENABLE_HIGHDPI // ���ø� DPI ֧��

//constexpr auto DEFAULT_FONT = L"PingFang SC Pro";
constexpr auto DEFAULT_FONT = L"Microsoft YaHei UI";
constexpr auto DEFAULT_BUTTON_FONTSIZE = 18;

constexpr auto BACKGROUND_COLOR = CLASSICGRAY;

constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 500;

constexpr auto MARGIN_HORIZONTAL = 15;
constexpr auto MARGIN_VERTICAL = 15;

constexpr auto CONTROL_HEIGHT = 23;

constexpr auto BUTTON_WIDTH = 80;
constexpr auto BUTTON_HEIGHT = 26;
// �� Button ��λ���������ؼ����־�������Ҫ��λ��ֵ
constexpr auto BUTTON_HEIGHT_OFFSET = (CONTROL_HEIGHT - BUTTON_HEIGHT) / 2.0;

// �ؼ�Ĭ�ϼ�� (�����ؼ�����߶�)
constexpr auto CONTROL_PADDING_HORIZONTAL = 10;
// �ؼ�Ĭ���о� (��ֱ������) (���ؼ�����߶�)
constexpr auto CONTROL_PADDING_VERTICAL = 28;

constexpr auto LYRICS_PADDING_VERTICAL = 32;

// ����������� Label �Ŀ�ȣ����ڱ��ػ�ʱ��������ĳߴ�
int TOP_LEFT_LABEL_MAX_WIDTH = 65;

#pragma endregion

#pragma region Public Varibles Defination

double DPI_Scale = 1;

#pragma endregion

#pragma region Function Definations

void AddWindowControls(HWND);
void DrawLabelControls();
void DrawPlaybackArea();
void DrawAtWndProcPaint();

#pragma endregion

#pragma region Controls

#pragma region Control Definations

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
	ButtonChooseAudio.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL, BUTTON_WIDTH, BUTTON_HEIGHT,  L"������Ƶ");
	ButtonChooseRawLyrics.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, BUTTON_WIDTH, BUTTON_HEIGHT , L"������");
	ButtonOutputPath.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, BUTTON_WIDTH, BUTTON_HEIGHT , L"ѡ��·��");

#pragma endregion

#pragma region ��������

	top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;
	ButtonPlayPause.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + top, BUTTON_WIDTH, BUTTON_HEIGHT,  L"��ͣ");

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
	int fontSize = (int)(18 * DPI_Scale);
	TextBoxChooseAudio.SetFont(fontSize, 0, DEFAULT_FONT);
	TextBoxChooseRawLyrics.SetFont(fontSize, 0, DEFAULT_FONT);
	TextBoxOutputPath.SetFont(fontSize, 0, DEFAULT_FONT);
	fontSize = (int)(DEFAULT_BUTTON_FONTSIZE * DPI_Scale);
	ButtonChooseAudio.SetFont(fontSize, 0, DEFAULT_FONT);
	ButtonChooseRawLyrics.SetFont(fontSize, 0, DEFAULT_FONT);
	ButtonOutputPath.SetFont(fontSize, 0, DEFAULT_FONT);
	ButtonPlayPause.SetFont(fontSize, 0, DEFAULT_FONT);
	ButtonAbout.SetFont(fontSize, 0, DEFAULT_FONT);
	ButtonViewOutput.SetFont(fontSize, 0, DEFAULT_FONT);
	ButtonPreview.SetFont(fontSize, 0, DEFAULT_FONT);
	ButtonRestart.SetFont(fontSize, 0, DEFAULT_FONT);
	ButtonStart.SetFont(fontSize, 0, DEFAULT_FONT);
}

/// <summary>
/// ���ڴ�С�ı�ʱ���õķ��������ڿؼ�λ�úͳߴ�����Ӧ
/// </summary>
static void ResizeMoveControls()
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
	setfont(20, 0, L"Consolas");
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top, L"0:00.000");

	// ������
	auto right = w - MARGIN_HORIZONTAL - BUTTON_WIDTH - CONTROL_PADDING_HORIZONTAL;
	auto progress = 0.333; // �������Ϊ 33.3%
	auto width = right - (MARGIN_HORIZONTAL + 80);
	CanvasMain.GP_SetLineWidth(3);
	CanvasMain.GP_Line(MARGIN_HORIZONTAL + 83, top + 11, right, top + 11, true, RGB(0xBF, 0xBF, 0xBF));
	CanvasMain.GP_Line(MARGIN_HORIZONTAL + 83, top + 11, right - width * (1 - progress), top + 11, true, RGB(0x7F, 0x7F, 0x7F));
	CanvasMain.GP_SetLineWidth(1); // ��ԭ

#pragma endregion

#pragma region �������

	setfont(20, 0, DEFAULT_FONT, 0, 0, FW_BOLD, false, false, false);
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + LYRICS_PADDING_VERTICAL, L"��ǰ�У�");
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + LYRICS_PADDING_VERTICAL * 2, L"��һ�У�");

	// ��ԭ��������
	setfont(20, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);

	// ���Ƹ���ı�
	// ��ͨ��ʣ��߶� �жϻ��ƶ��и��

#pragma endregion

#pragma region ��ʾ����

	top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12 - 35;
	setfont(20, 0, DEFAULT_FONT, 0, 0, FW_BOLD, false, false, false);
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top - 1, L"������ʾ��");
	setfont(19, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL + 100, top, L"����ʼ����     �н�������     �ص���һ�У���     ���� 3s��B     ����/��ͣ��Space");

#pragma endregion

}

/// <summary>
/// �ص�ʱ���õ��ػ淽��
/// </summary>
static void DrawAtWndProcPaint()
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

#pragma region Main & Window

/// <summary>
/// �����ڻص�����
/// </summary>
/// <param name="hWnd">���ھ��</param>
/// <param name="msg">��ϢID</param>
/// <param name="wParam">��Ϣ���� wParam</param>
/// <param name="lParam">��Ϣ���� lParam</param>
/// <returns></returns>
static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
	default:
		return HIWINDOW_DEFAULT_PROC;
		break;
	}

	return 0;
}

int main()
{
#ifdef ENABLE_HIGHDPI
	// �� DPI ֧��
	DPI_Scale = GetDpiScale(); // �����Ȼ�ȡ�������� DPI Aware �����ֵ����Ϊ 1
	EnableDpiAwareness();

	hiex::SysControlBase::DPI_Scale = DPI_Scale;
#endif // ENABLE_HIGHDPI

	// ��ʼ������
	hiex::SetCustomIcon(MAKEINTRESOURCE(IDI_ICON1), MAKEINTRESOURCE(IDI_ICON1));
	hiex::Window wnd(WINDOW_WIDTH * DPI_Scale, WINDOW_HEIGHT * DPI_Scale, EW_NORMAL, L"Lyricify Lyrics Creator");
	wnd.BindCanvas(&CanvasMain);
	// ���� Canvas ����
	// �ο��ĵ�: https://docs.easyx.cn/zh-cn/LOGFONT
	setfont(20, 0, DEFAULT_FONT, 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	setaspectratio(DPI_Scale, DPI_Scale);
	CanvasMain.SetTextColor(BLACK);
	wnd.SetProcFunc(WndProc);
	hiex::AutoExit();

	// ���ƴ���ؼ�
	AddWindowControls(wnd.GetHandle());
	wnd.Redraw(); // �����ػ洰�� ����ʹ�û��Ƶ��ı���ʾ����

	// �رմ��ڣ���������
	hiex::init_end(wnd.GetHandle());

	closegraph();
	return 0;
}

#pragma endregion
