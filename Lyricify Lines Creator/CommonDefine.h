#pragma once

#include "HiEasyX.h"

#pragma warning(disable: 4244) // ����ת��������ʧ�� warning

constexpr auto VERSION = L"0.1-alpha";

constexpr auto ENABLE_HIGHDPI = true; // ���ø� DPI ֧��

//constexpr auto DEFAULT_FONT = L"PingFang SC Pro";
constexpr auto DEFAULT_FONT = L"Microsoft YaHei UI";
constexpr auto DEFAULT_CANVAS_FONTSIZE = 20;
constexpr auto DEFAULT_TEXTBOX_FONTSIZE = 18;
constexpr auto DEFAULT_BUTTON_FONTSIZE = 18;

constexpr auto BACKGROUND_COLOR = CLASSICGRAY;

constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 500;

constexpr auto MARGIN_HORIZONTAL = 15;
constexpr auto MARGIN_VERTICAL = 15;

constexpr auto CONTROL_HEIGHT = 23;

// �ؼ�Ĭ�ϼ�� (�����ؼ�����߶�)
constexpr auto CONTROL_PADDING_HORIZONTAL = 10;
// �ؼ�Ĭ���о� (��ֱ������) (���ؼ�����߶�)
constexpr auto CONTROL_PADDING_VERTICAL = 28;

constexpr auto BUTTON_WIDTH = 80;
constexpr auto BUTTON_HEIGHT = 26;
// �� Button ��λ���������ؼ����־�������Ҫ��λ��ֵ
constexpr auto BUTTON_HEIGHT_OFFSET = (CONTROL_HEIGHT - BUTTON_HEIGHT) / 2.0;

constexpr auto LYRICS_PADDING_VERTICAL = 32;
