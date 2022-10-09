#include <windows.h> 
#include "TCHAR.H"
#include "stdio.h"
#include "resource.h"
HANDLE  handle = 0;


LRESULT CALLBACK WindProc(HWND hwnd, UINT msgID, WPARAM wPARAM, LPARAM lparam);
void onTimer() {
	char str[280] = { 0 };
	sprintf(str, "时间:%d\n", 1);
	WriteConsole(handle, str, strlen(str), NULL, NULL);
}
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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);//设置窗口背景
	wc.hCursor = NULL;//默认光标
	wc.hIcon = NULL;//默认图标
	wc.hInstance = hInctance;//当前程序实例句柄
	wc.lpfnWndProc = WindProc;
	wc.lpszClassName = "窗口名称";
	wc.lpszMenuName = (LPCSTR)IDR_MENU1;//默认菜单
	wc.style = CS_HREDRAW | CS_VREDRAW;//检测窗口位置变化刷新绘制
	RegisterClass(&wc);//将窗口类写入操作系统
	//2.在内存中申请创建内存
	HWND hwnd = CreateWindow("窗口名称", "俄罗斯方块", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInctance, (LPVOID)NULL);
	//3.显示窗口
	ShowWindow(hwnd, SW_SHOW);//原样刷新显示
	UpdateWindow(hwnd);//刷新窗口 防止漏加载资源
	//消息循环
	MSG nMSG = { 0 };
	while (1) //如果函数检索到WM_QUIT以外的消息，则返回值非零。
			 //如果函数检索到WM_QUIT消息，则返回值为零。WM_QUIT表示终止应用程序的请求
	{

		if (PeekMessage(&nMSG, NULL, 0, 0, PM_NOREMOVE)) {//侦察消息，无消息返回false
			if (GetMessage(&nMSG, NULL, 0, 0))
			{
				TranslateMessage(&nMSG);//翻译消息
				DispatchMessage(&nMSG);//派发消息  交给窗口处理函数处理
			}
			else
			{
				return 0;
			}
		}
		else {
			//WriteConsole(handle, "无消息！", strlen("无消息！"), NULL, NULL);
			Sleep(100);//while循环太快了 睡一下打印输出，观察窗口变化输出是否正常
		}

	}
	return 0;
}
//窗口处理函数(自定义，处理消息)
LRESULT CALLBACK WindProc(HWND hwnd, UINT msgID, WPARAM wPARAM, LPARAM lparam) {
	switch (msgID)
	{
	case WM_TIMER:
		onTimer();
		break;
	case WM_CREATE:
		SetTimer(hwnd, 1, 1000, 0);
		break;
	}

	return DefWindowProc(hwnd, msgID, wPARAM, lparam);
}