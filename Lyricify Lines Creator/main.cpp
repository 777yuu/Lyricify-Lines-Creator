#include <fstream>
#include <vector>
#include <string>

#include "DpiHelper.h" // ���������ã����ж�����ϵͳҪ����
#include "CommonDefine.h"
#include "WindowMain.h"

#pragma warning(disable: 4244) // ����ת��������ʧ�� warning

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

	WindowMain::Show(DPI_Scale);

	closegraph();
	return 0;
}
