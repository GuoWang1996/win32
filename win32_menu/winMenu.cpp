#include <windows.h> 
#include "TCHAR.H"
#include "stdio.h"
#include "resource.h"
HANDLE  handle = 0;


LRESULT CALLBACK WindProc(HWND hwnd, UINT msgID, WPARAM wPARAM, LPARAM lparam);
void onTimer() {
	char str[280] = { 0 };
	sprintf(str, "ʱ��:%d\n", 1);
	WriteConsole(handle, str, strlen(str), NULL, NULL);
}
int WINAPI _tWinMain(
	HINSTANCE hInctance,
	HINSTANCE hPrevInctance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	AllocConsole();//����DOS����
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//1.ע�ᴰ����
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;//���뻺����
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);//���ô��ڱ���
	wc.hCursor = NULL;//Ĭ�Ϲ��
	wc.hIcon = NULL;//Ĭ��ͼ��
	wc.hInstance = hInctance;//��ǰ����ʵ�����
	wc.lpfnWndProc = WindProc;
	wc.lpszClassName = "��������";
	wc.lpszMenuName = (LPCSTR)IDR_MENU1;//Ĭ�ϲ˵�
	wc.style = CS_HREDRAW | CS_VREDRAW;//��ⴰ��λ�ñ仯ˢ�»���
	RegisterClass(&wc);//��������д�����ϵͳ
	//2.���ڴ������봴���ڴ�
	HWND hwnd = CreateWindow("��������", "����˹����", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInctance, (LPVOID)NULL);
	//3.��ʾ����
	ShowWindow(hwnd, SW_SHOW);//ԭ��ˢ����ʾ
	UpdateWindow(hwnd);//ˢ�´��� ��ֹ©������Դ
	//��Ϣѭ��
	MSG nMSG = { 0 };
	while (1) //�������������WM_QUIT�������Ϣ���򷵻�ֵ���㡣
			 //�������������WM_QUIT��Ϣ���򷵻�ֵΪ�㡣WM_QUIT��ʾ��ֹӦ�ó��������
	{

		if (PeekMessage(&nMSG, NULL, 0, 0, PM_NOREMOVE)) {//�����Ϣ������Ϣ����false
			if (GetMessage(&nMSG, NULL, 0, 0))
			{
				TranslateMessage(&nMSG);//������Ϣ
				DispatchMessage(&nMSG);//�ɷ���Ϣ  �������ڴ���������
			}
			else
			{
				return 0;
			}
		}
		else {
			//WriteConsole(handle, "����Ϣ��", strlen("����Ϣ��"), NULL, NULL);
			Sleep(100);//whileѭ��̫���� ˯һ�´�ӡ������۲촰�ڱ仯����Ƿ�����
		}

	}
	return 0;
}
//���ڴ�����(�Զ��壬������Ϣ)
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