/************************************************************************
 * Filename:    main.cpp
 * Description: ������ڵ�
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include <fstream>
#include <vector>
#include <string>

#include "DpiHelper.h" // ���������ã����ж�����ϵͳҪ����
#include "CommonDefine.h"
#include "WindowMain.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"") // ����ʾ����̨

double DPI_Scale = 1;

int main()
{
	if (ENABLE_HIGHDPI)
	{
		// �� DPI ֧��
		DPI_Scale = GetDpiScale(); // �����Ȼ�ȡ�������� DPI Aware �����ֵ����Ϊ 1
		EnableDpiAwareness();

		hiex::SysControlBase::DPI_Scale = DPI_Scale;
	}

	hiex::SetCustomIcon(MAKEINTRESOURCE(IDI_ICON1), MAKEINTRESOURCE(IDI_ICON1));
	WindowMain::Show(DPI_Scale);

	closegraph();
	return 0;
}
