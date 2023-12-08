#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <fstream>
#include <ShlObj.h> // 使用 SHGetFolderPath
#include <Windows.h>
#include "TCHAR.H"
#define WM_DAY WM_USER+11 

HANDLE  handle = 0;

long CalculateRemainingLifetime(std::tm& birthDt, int expectedLifeYears);


//定义窗口处理函数
LRESULT CALLBACK WindProc(HWND hwnd, UINT msgID, WPARAM wPARAM, LPARAM lparam) {

	switch (msgID)
	{
		case WM_CREATE:
		{

			SetTimer(hwnd, 1, 1000, 0);
			break;
		}
		case WM_DESTROY:
		{
			PostMessage(NULL,WM_QUIT, 0, 0);
			break;
		}
		case WM_TIMER:
			InvalidateRect(hwnd, NULL, TRUE); // 强制刷新窗口
			break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// 从窗口获取剩余寿命
			LONG_PTR remainingDays = GetWindowLongPtr(hwnd, GWLP_USERDATA);

			// 转换显示天、时、分、秒
			long days = remainingDays / (24 * 3600);
			int hours = (remainingDays % (24 * 3600)) / 3600;
			int mins = (remainingDays % 3600) / 60;
			int secs = remainingDays % 60;

			// 格式化显示
			char buffer[256];  // 将缓冲区改为 char 类型
			sprintf_s(buffer, "你的生命还剩%d 天 %d 时 %d 分 %d 秒\n", days, hours, mins, secs);  // 使用 sprintf_s 函数
			RECT rect;
			GetClientRect(hwnd, &rect);
			DrawText(hdc, buffer, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hwnd, &ps);
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
	default:
		break;
	}
	return DefWindowProc(hwnd, msgID, wPARAM, lparam);
}

//定义入口函数
int WINAPI _tWinMain(
	HINSTANCE hInctance,
	HINSTANCE hPrevInctance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	std::tm t = {};
	t.tm_year = 1996 - 1900; // 年要减去 1900
	t.tm_mon = 11 - 1;       // 月要减去 1
	t.tm_mday = 2;
	t.tm_hour = 20;
	t.tm_min = 0;
	t.tm_sec = 0;

	std::time_t birthDate = std::mktime(&t);




	//1.注册窗口类
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;//申请缓冲区
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);//设置窗口背景
	wc.hCursor = NULL;//默认光标
	wc.hIcon = NULL;//默认图标
	wc.hInstance = hInctance;//当前程序实例句柄
	wc.lpfnWndProc = WindProc;
	wc.lpszClassName = "窗口名称";
	wc.lpszMenuName = NULL;//默认菜单
	wc.style = CS_HREDRAW | CS_VREDRAW;//检测窗口位置变化刷新绘制
	RegisterClassEx(&wc);//将窗口类写入操作系统

	//2.在内存中申请创建内存
	const char* str = "HelloWorld";
	HWND hwnd = CreateWindowEx(NULL,"窗口名称", "寿命统计器", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInctance, (LPVOID)str);

	//3.显示窗口
	ShowWindow(hwnd, SW_SHOW);//原样刷新显示
	UpdateWindow(hwnd);//刷新窗口 防止漏加载资源


	//4.消息循环
	MSG nMSG = { 0 };
	while (GetMessage(&nMSG, NULL, 0, 0)) //如果函数检索到WM_QUIT以外的消息，则返回值非零。

		//如果函数检索到WM_QUIT消息，则返回值为零。WM_QUIT表示终止应用程序的请求
	{

		

		long time=CalculateRemainingLifetime(t, 70);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, static_cast<LONG_PTR>(time));


		SendMessage(NULL, WM_PAINT, 0, 0);
		TranslateMessage(&nMSG);//翻译消息
		DispatchMessage(&nMSG);//派发消息  交给窗口处理函数处理
	}
	return 0;
}

// 参数:出生时间,预期寿命(年)  
long CalculateRemainingLifetime( std::tm& birthDt, int expectedLifeYears) {

	// 转换为chrono时间点  
	auto birthDate = std::chrono::system_clock::from_time_t(std::mktime(&birthDt));

	// 预期寿命转换为秒
	std::chrono::seconds expectedLifespan(expectedLifeYears * 365 * 24 * 60 * 60);

	// 计算寿命终止时间点
	auto lifeEnd = birthDate + expectedLifespan;

	// 当前时间
	auto now = std::chrono::system_clock::now();

	// 计算差值得到剩余秒数 
	std::chrono::seconds leftSeconds = std::chrono::duration_cast<std::chrono::seconds>(lifeEnd - now);

	// 返回剩余秒数  
	return leftSeconds.count();
}