#include <windows.h> 
#include "TCHAR.H"
#include "stdio.h"

HANDLE  handle = 0;
void wmCreate(HWND hwnd, LPARAM lparam) {
	CREATESTRUCT* s=(CREATESTRUCT*)lparam;
	char* str = (char*)s->lpszName;//强转成字符串
	MessageBox(NULL, str, "test333", MB_YESNO);
	//为什么EDIT就能创建成功,自定义窗口就不行
	CreateWindowEx(0,"EDIT", "标题", WS_CHILD | WS_VISIBLE |WS_BORDER, 0, 0, 200, 200, hwnd, NULL, 0,NULL);
}
void wmSize(HWND hwnd, LPARAM lparam) {
	short x = LOWORD(lparam);
	short y = HIWORD(lparam);
	char str[256] = {0};
	sprintf(str, "宽:%d,高:%d\n", x, y);

	WriteConsole(handle, str, strlen(str), NULL, NULL);

}
LRESULT CALLBACK WindProc(HWND hwnd, UINT msgID, WPARAM wPARAM, LPARAM lparam);

int WINAPI _tWinMain(
	HINSTANCE hInctance,
	HINSTANCE hPrevInctance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	AllocConsole();//增加DOS窗口
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//1.注册窗口类
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;//申请缓冲区
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//设置窗口背景
	wc.hCursor = NULL;//默认光标
	wc.hIcon = NULL;//默认图标
	wc.hInstance = hInctance;//当前程序实例句柄
	wc.lpfnWndProc = WindProc;
	wc.lpszClassName = "窗口名称";
	wc.lpszMenuName = NULL;//默认菜单
	wc.style = CS_HREDRAW | CS_VREDRAW;//检测窗口位置变化刷新绘制
	RegisterClass(&wc);//将窗口类写入操作系统
	//2.在内存中申请创建内存
	HWND hwnd= CreateWindow("窗口名称","标题",WS_OVERLAPPEDWINDOW,100,100,500,500,NULL,NULL, hInctance, (LPVOID)NULL);
	//注册子窗口
	wc.cbClsExtra = 0;//申请缓冲区
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//设置窗口背景
	wc.hCursor = NULL;//默认光标
	wc.hIcon = NULL;//默认图标
	wc.hInstance = hInctance;//当前程序实例句柄
	wc.lpfnWndProc = DefWindowProc;//windows默认窗口处理函数
	wc.lpszClassName = "子窗口";
	wc.lpszMenuName = NULL;//默认菜单
	wc.style = CS_HREDRAW | CS_VREDRAW;//检测窗口位置变化刷新绘制
	RegisterClass(&wc);//将窗口类写入操作系统
	//创建子窗口
	HWND hwnd2 = CreateWindow("子窗口", "标题",WS_CHILD|WS_VISIBLE| WS_OVERLAPPEDWINDOW, 100, 100, 200, 200, hwnd, NULL, hInctance, (LPVOID)NULL);
	//3.显示窗口
	ShowWindow(hwnd,SW_SHOW);//原样刷新显示
	UpdateWindow(hwnd);//刷新窗口 防止漏加载资源
	//消息循环
	MSG nMSG = {0};
	while (GetMessage(&nMSG, NULL, 0, 0)) //如果函数检索到WM_QUIT以外的消息，则返回值非零。

										 //如果函数检索到WM_QUIT消息，则返回值为零。WM_QUIT表示终止应用程序的请求
	{
		TranslateMessage(&nMSG);//翻译消息
		DispatchMessage(&nMSG);//派发消息  交给窗口处理函数处理
	}
	return 0;
}
//窗口处理函数(自定义，处理消息)
LRESULT CALLBACK WindProc(HWND hwnd, UINT msgID, WPARAM wPARAM, LPARAM lparam) {
	switch (msgID)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SYSCOMMAND:
		if (wPARAM == SC_CLOSE)
		{
			if (MessageBox(NULL, "是否退出", "test333", MB_YESNO) == IDNO)
			{
				return 0;
			}
		}
		break;
	case WM_CREATE:
		wmCreate(hwnd, lparam);
		break;
	case WM_SIZE:
		wmSize(hwnd, lparam);
		break;
	}
	
	return DefWindowProc(hwnd, msgID, wPARAM, lparam);
}