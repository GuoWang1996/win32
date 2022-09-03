#include "windows.h"
#include "TCHAR.H"
#include "stdio.h"
#include <iostream>
using namespace std;
//入口函数
int WINAPI _tWinMain(
	HINSTANCE hInctance,
    HINSTANCE hPrevInctance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	if (MessageBox(NULL, "test", "test333", MB_ICONHAND) == 1)
	{
		cout << "------------------" << endl;
	}

	return 1;
}
//窗口处理函数