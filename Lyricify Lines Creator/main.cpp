#include "HiEasyX.h"

int main()
{
	// ��ʼ������
	hiex::Window wnd(640, 480);
	hiex::AutoExit();

	HWND hwnd = wnd.GetHandle();

	// �رմ��ڣ���������
	hiex::init_end(hwnd);

	closegraph();
	return 0;
}
