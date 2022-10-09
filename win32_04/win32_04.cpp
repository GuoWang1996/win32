#include <windows.h> 
#include "TCHAR.H"

int WINAPI _tWinMain(
	HINSTANCE hInctance,
	HINSTANCE hPrevInctance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	//2.在内存中申请创建内存
	HWND hwnd = CreateWindow("button", "标题", WS_VISIBLE| WS_CHILD|BS_PUSHBUTTON, 100, 50, 100, 50, hwnd, (HMENU)1000, hInctance, (LPVOID)NULL);
	//3.显示窗口
	ShowWindow(hwnd, SW_SHOW);//原样刷新显示
	UpdateWindow(hwnd);//刷新窗口 防止漏加载资源
	//消息循环
	MSG nMSG = { 0 };
	while (GetMessage(&nMSG, NULL, 0, 0))
	{
		TranslateMessage(&nMSG);//翻译消息
		DispatchMessage(&nMSG);//派发消息  交给窗口处理函数处理
	}
	return 0;
}