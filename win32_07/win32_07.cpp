#include <windows.h> 
#include "TCHAR.H"
#include "stdio.h"
#include "resource.h"
HANDLE  handle = 0;
HINSTANCE hInctance_m = 0;
HWND hwndDialog = 0;
LRESULT CALLBACK WindProc(HWND hwnd, UINT msgID, WPARAM wPARAM, LPARAM lparam);
int CALLBACK dialogProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM LParam);
void myCommand(HWND hwnd, WPARAM wParam) {
	switch (LOWORD(wParam)) {
	case ID_40002:
		hwndDialog=CreateDialog(hInctance_m, (LPCTSTR)IDD_DIALOG1,hwnd, dialogProc);
		ShowWindow(hwndDialog, SW_SHOW);
		break;
	}
}
int CALLBACK dialogProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM LParam
) {
	switch (uMsg) {
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			//EndDialog(hwnd, 1000);
			DestroyWindow(hwndDialog);
		}
		break;
	case WM_COMMAND:
		if (wParam== IDSURE)
		{
			MessageBox(NULL, "确定按钮", "提示", MB_YESNO);
		}
		break;
	}
	return FALSE;//交给真正的对话框消息处理函数
}
int WINAPI _tWinMain(
	HINSTANCE hInctance,
	HINSTANCE hPrevInctance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	hInctance_m = hInctance;
	AllocConsole();//增加DOS窗口
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//1.注册窗口类
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;//申请缓冲区
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//设置窗口背景
	wc.hCursor = NULL;//默认光标
	wc.hIcon = NULL;//默认图标
	//wc.hIconSm = LoadIcon(hInctance, (LPCSTR)IDI_ICON2);//默认图标
	wc.hInstance = hInctance;//当前程序实例句柄
	wc.lpfnWndProc = WindProc;
	wc.lpszClassName = "窗口名称";
	wc.lpszMenuName = (LPSTR)IDR_MENU1;//默认菜单
	wc.style = CS_HREDRAW | CS_VREDRAW;//检测窗口位置变化刷新绘制
	RegisterClassEx(&wc);//将窗口类写入操作系统
	//2.在内存中申请创建内存
	HWND hwnd = CreateWindow("窗口名称", "记事本", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInctance, (LPVOID)NULL);
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
	RegisterClassEx(&wc);//将窗口类写入操作系统
	//创建子窗口
	//HWND hwnd2 = CreateWindow("button", "标题", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 100, 50, 100, 100, hwnd, NULL, hInctance, (LPVOID)NULL);
	//3.显示窗口
	ShowWindow(hwnd, SW_SHOW);//原样刷新显示
	UpdateWindow(hwnd);//刷新窗口 防止漏加载资源
	//消息循环
	MSG nMSG = { 0 };
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
	case WM_COMMAND:
		myCommand(hwnd, wPARAM);
	}

	return DefWindowProc(hwnd, msgID, wPARAM, lparam);
}