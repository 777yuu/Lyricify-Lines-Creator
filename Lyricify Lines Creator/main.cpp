#include <fstream>
#include <vector>
#include <string>

#include "DpiHelper.h" // 须优先引用，其中定义了系统要求常量
#include "CommonDefine.h"
#include "WindowMain.h"

double DPI_Scale = 1;

int main()
{
	if (ENABLE_HIGHDPI)
	{
		// 高 DPI 支持
		DPI_Scale = GetDpiScale(); // 必须先获取，在设置 DPI Aware 后这个值将变为 1
		EnableDpiAwareness();

		hiex::SysControlBase::DPI_Scale = DPI_Scale;
	}

	hiex::SetCustomIcon(MAKEINTRESOURCE(IDI_ICON1), MAKEINTRESOURCE(IDI_ICON1));
	WindowMain::Show(DPI_Scale);

	closegraph();
	return 0;
}
