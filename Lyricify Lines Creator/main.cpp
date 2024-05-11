#include "HiEasyX.h"
#include "resource.h"

#pragma region Const Definations

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
// 让 Button 的位置与其他控件保持居中所需要的位移值
constexpr auto BUTTON_HEIGHT_OFFSET = (CONTROL_HEIGHT - BUTTON_HEIGHT) / 2.0;

// 控件默认间距 (不含控件本身高度)
constexpr auto CONTROL_PADDING_HORIZONTAL = 10;
// 控件默认行距 (竖直方向间距) (含控件本身高度)
constexpr auto CONTROL_PADDING_VERTICAL = 28;

// 顶部区域左侧 Label 的宽度，后期本地化时在这里更改尺寸
int TOP_LEFT_LABEL_MAX_WIDTH = 60;

#pragma endregion

#pragma region Function Definations

void AddWindowControls(HWND);
void DrawLabelControls();
void DrawPlaybackArea();
void DrawAtWndProcPaint();

#pragma endregion

#pragma region Controls

#pragma region Control Definations

// 顶部区域

hiex::Canvas CanvasMain;

hiex::SysEdit TextBoxChooseAudio;
hiex::SysEdit TextBoxChooseRawLyrics;
hiex::SysEdit TextBoxOutputPath;

hiex::SysButton ButtonChooseAudio;
hiex::SysButton ButtonChooseRawLyrics;
hiex::SysButton ButtonOutputPath;

// 播放区域

hiex::SysButton ButtonPlayPause;

// 底部区域

hiex::SysButton ButtonAbout;
hiex::SysButton ButtonViewOutput;
hiex::SysButton ButtonPreview;
hiex::SysButton ButtonRestart;
hiex::SysButton ButtonStart;

#pragma endregion

/// <summary>
/// 添加主窗体的控件
/// </summary>
/// <param name="hwnd">传入主窗体的句柄</param>
void AddWindowControls(HWND hwnd)
{
	int left, top;
	int w = CanvasMain.GetWidth(), h = CanvasMain.GetHeight();

#pragma region 顶部区域

	DrawLabelControls();

	left = MARGIN_HORIZONTAL + TOP_LEFT_LABEL_MAX_WIDTH + CONTROL_PADDING_HORIZONTAL;
	auto width = w - (MARGIN_HORIZONTAL * 2 + TOP_LEFT_LABEL_MAX_WIDTH + BUTTON_WIDTH + CONTROL_PADDING_HORIZONTAL * 2);
	TextBoxChooseAudio.Create(hwnd, left, MARGIN_VERTICAL, width, CONTROL_HEIGHT);
	TextBoxChooseRawLyrics.Create(hwnd, left, MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, width, CONTROL_HEIGHT);
	TextBoxOutputPath.Create(hwnd, left, MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, width, CONTROL_HEIGHT);


	left = w - MARGIN_HORIZONTAL - BUTTON_WIDTH;
	ButtonChooseAudio.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL, BUTTON_WIDTH, BUTTON_HEIGHT, L"导入音频");
	ButtonChooseRawLyrics.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, BUTTON_WIDTH, BUTTON_HEIGHT, L"导入歌词");
	ButtonOutputPath.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, BUTTON_WIDTH, BUTTON_HEIGHT, L"选择路径");

#pragma endregion

#pragma region 播放区域

	top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;
	ButtonPlayPause.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + top, BUTTON_WIDTH, BUTTON_HEIGHT, L"暂停");

#pragma endregion

#pragma region 底部区域

	top = h - MARGIN_VERTICAL - BUTTON_HEIGHT;
	ButtonAbout.Create(hwnd, MARGIN_HORIZONTAL, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"关于");
	ButtonViewOutput.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 4 - CONTROL_PADDING_HORIZONTAL * 5, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"查看输出");
	ButtonPreview.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 3 - CONTROL_PADDING_HORIZONTAL * 4, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"预览效果");
	ButtonRestart.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"重新制作");
	ButtonStart.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"开始制作");

#pragma endregion

	// 设置字体
	TextBoxChooseAudio.SetFont(18, 0, DEFAULT_FONT);
	TextBoxChooseRawLyrics.SetFont(18, 0, DEFAULT_FONT);
	TextBoxOutputPath.SetFont(18, 0, DEFAULT_FONT);
	ButtonChooseAudio.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
	ButtonChooseRawLyrics.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
	ButtonOutputPath.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
	ButtonPlayPause.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
	ButtonAbout.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
	ButtonViewOutput.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
	ButtonPreview.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
	ButtonRestart.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
	ButtonStart.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
}

/// <summary>
/// 窗口大小改变时调用的方法，用于控件位置和尺寸自适应
/// </summary>
static void ResizeMoveControls()
{
	int left, top;
	int w = CanvasMain.GetWidth();
	int h = CanvasMain.GetHeight();

#pragma region 顶部区域

	// 因 HiEasyX 的一些问题，Resize 后边框将变粗
	auto width = w - (MARGIN_HORIZONTAL * 2 + TOP_LEFT_LABEL_MAX_WIDTH + BUTTON_WIDTH + CONTROL_PADDING_HORIZONTAL * 2);
	TextBoxChooseAudio.Resize(width, CONTROL_HEIGHT);
	TextBoxChooseRawLyrics.Resize(width, CONTROL_HEIGHT);
	TextBoxOutputPath.Resize(width, CONTROL_HEIGHT);

	left = w - MARGIN_HORIZONTAL - BUTTON_WIDTH;
	ButtonChooseAudio.Move(left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL);
	ButtonChooseRawLyrics.Move(left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL);
	ButtonOutputPath.Move(left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2);

#pragma endregion

#pragma region 播放区域

	top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;
	ButtonPlayPause.Move(left, BUTTON_HEIGHT_OFFSET + top);

#pragma endregion

#pragma region 底部区域

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
/// 在 Canvas 中绘制文本 (实现 Label 控件效果)
/// </summary>
void DrawLabelControls()
{
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL, MARGIN_VERTICAL, L"选择音频：");
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL, MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, L"选择歌词：");
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL, MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, L"输出路径：");
}

/// <summary>
/// 绘制播放区域
/// </summary>
void DrawPlaybackArea()
{
	auto top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;

#pragma region 音频区域

	// 当前时间
	setfont(20, 0, L"Consolas");
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top, L"0:00.000");

	// 进度条
	auto right = CanvasMain.GetWidth() - MARGIN_HORIZONTAL - BUTTON_WIDTH - CONTROL_PADDING_HORIZONTAL;
	auto progress = 0.333; // 暂设进度为 33.3%
	auto width = right - (MARGIN_HORIZONTAL + 80);
	CanvasMain.GP_SetLineWidth(3);
	CanvasMain.GP_Line(MARGIN_HORIZONTAL + 80, top + 11, right, top + 11, true, RGB(0xBF, 0xBF, 0xBF));
	CanvasMain.GP_Line(MARGIN_HORIZONTAL + 80, top + 11, right - width * (1 - progress), top + 11, true, RGB(0x7F, 0x7F, 0x7F));
	CanvasMain.GP_SetLineWidth(1); // 还原

#pragma endregion

#pragma region 歌词区域

	setfont(20, 0, DEFAULT_FONT, 0, 0, FW_BOLD, false, false, false);
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + CONTROL_PADDING_VERTICAL, L"当前行：");
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + CONTROL_PADDING_VERTICAL * 2, L"下一行：");

	// 还原字体设置
	setfont(20, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);

	// 绘制歌词文本
	// 可通过剩余高度 判断绘制多行歌词

#pragma endregion

#pragma region 提示区域

	top = CanvasMain.GetHeight() - BUTTON_HEIGHT - MARGIN_VERTICAL - 12 - 35;
	setfont(20, 0, DEFAULT_FONT, 0, 0, FW_BOLD, false, false, false);
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top, L"按键提示：");
	setfont(20, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	CanvasMain.OutTextXY(MARGIN_HORIZONTAL + 100, top, L"行起始：↑     行结束：→     回到上一行：↓     回退 5s：B     播放/暂停：Space");

#pragma endregion

}

/// <summary>
/// 回调时调用的重绘方法
/// </summary>
static void DrawAtWndProcPaint()
{
	const auto LINE_COLOR = RGB(0xAF, 0xAF, 0xAF);
	const auto SUBLINE_COLOR = RGB(0xCF, 0xCF, 0xCF);
	int top;
	int w = CanvasMain.GetWidth(), h = CanvasMain.GetHeight();

	CanvasMain.SetBkColor(BACKGROUND_COLOR);
	DrawLabelControls();
	DrawPlaybackArea();

	// 顶部区域分割线
	top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 10;
	CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);

	// 提示区域分割线
	top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12 - 50;
	CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);

	// 底部区域分割线
	top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12;
	CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);
	CanvasMain.Line(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL * 2.5, top + 10, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL * 2.5, top + 40, true, SUBLINE_COLOR);
}

#pragma endregion

#pragma region Main & Window

/// <summary>
/// 主窗口回调函数
/// </summary>
/// <param name="hWnd">窗口句柄</param>
/// <param name="msg">消息ID</param>
/// <param name="wParam">消息参数 wParam</param>
/// <param name="lParam">消息参数 lParam</param>
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
	// 初始化窗口
	hiex::SetCustomIcon(MAKEINTRESOURCE(IDI_ICON1), MAKEINTRESOURCE(IDI_ICON1));
	hiex::Window wnd(WINDOW_WIDTH, WINDOW_HEIGHT, EW_NORMAL, L"Lyricify Lyrics Creator");
	wnd.BindCanvas(&CanvasMain);
	// 设置 Canvas 字体
	// 参考文档: https://docs.easyx.cn/zh-cn/LOGFONT
	setfont(20, 0, DEFAULT_FONT, 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	CanvasMain.SetTextColor(BLACK);
	wnd.SetProcFunc(WndProc);
	hiex::AutoExit();

	// 绘制窗体控件
	AddWindowControls(wnd.GetHandle());
	wnd.Redraw(); // 立即重绘窗口 才能使得绘制的文本显示出来

	// 关闭窗口，结束程序
	hiex::init_end(wnd.GetHandle());

	closegraph();
	return 0;
}

#pragma endregion
