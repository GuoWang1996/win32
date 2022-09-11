#include <windows.h> 
#include "TCHAR.H"
#include "stdio.h"
#define WM_MYMESSGAE WM_USER+1000
HANDLE  handle = 0;

void wmSize(HWND hwnd, LPARAM lparam) {
	short x = LOWORD(lparam);
	short y = HIWORD(lparam);
	char str[256] = { 0 };
	sprintf(str, "��:%d,��:%d\n", x, y);

	WriteConsole(handle, str, strlen(str), NULL, NULL);

}
void myMessage() {
	MessageBox(NULL, "�������Լ��������Ϣ", "wmCreate", MB_YESNO);
}
void myPaint() {
	WriteConsole(handle, "�������Լ�����Ĵ�����Ϣ��", strlen("�������Լ�����Ĵ�����Ϣ��"), NULL, NULL);
}
void myMouseMove(LPARAM lparam) {
	POINTS points = MAKEPOINTS(lparam);
	short x=points.x;
	short y = points.y;
	char str[256] = { 0 };
	sprintf(str, "x:%d,y:%d\n", x, y);
	WriteConsole(handle, str, strlen(str), NULL, NULL);
}
LRESULT CALLBACK WindProc(HWND hwnd, UINT msgID, WPARAM wPARAM, LPARAM lparam);

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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW );//���ô��ڱ���
	wc.hCursor = NULL;//Ĭ�Ϲ��
	wc.hIcon = NULL;//Ĭ��ͼ��
	wc.hInstance = hInctance;//��ǰ����ʵ�����
	wc.lpfnWndProc = WindProc;
	wc.lpszClassName = "��������";
	wc.lpszMenuName = NULL;//Ĭ�ϲ˵�
	wc.style = CS_HREDRAW | CS_VREDRAW;//��ⴰ��λ�ñ仯ˢ�»���
	RegisterClass(&wc);//��������д�����ϵͳ
	//2.���ڴ������봴���ڴ�
	HWND hwnd = CreateWindow("��������", "������", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInctance, (LPVOID)NULL);
	//ע���Ӵ���
	wc.cbClsExtra = 0;//���뻺����
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//���ô��ڱ���
	wc.hCursor = NULL;//Ĭ�Ϲ��
	wc.hIcon = NULL;//Ĭ��ͼ��
	wc.hInstance = hInctance;//��ǰ����ʵ�����
	wc.lpfnWndProc = DefWindowProc;//windowsĬ�ϴ��ڴ�����
	wc.lpszClassName = "�Ӵ���";
	wc.lpszMenuName = NULL;//Ĭ�ϲ˵�
	wc.style = CS_HREDRAW | CS_VREDRAW;//��ⴰ��λ�ñ仯ˢ�»���
	RegisterClass(&wc);//��������д�����ϵͳ
	//�����Ӵ���
	HWND hwnd2 = CreateWindow("�Ӵ���", "�Ӵ���", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, 100, 100, 200, 200, hwnd, NULL, hInctance, (LPVOID)NULL);
	//3.��ʾ����
	ShowWindow(hwnd, SW_SHOW);//ԭ��ˢ����ʾ
	UpdateWindow(hwnd);//ˢ�´��� ��ֹ©������Դ
	//��Ϣѭ��
	MSG nMSG = { 0 };
	while (1) //�������������WM_QUIT�������Ϣ���򷵻�ֵ���㡣
			 //�������������WM_QUIT��Ϣ���򷵻�ֵΪ�㡣WM_QUIT��ʾ��ֹӦ�ó��������
	{
		
		if (PeekMessage(&nMSG, NULL, 0, 0,PM_NOREMOVE)) {//�����Ϣ������Ϣ����false
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
	case WM_DESTROY:
		//SendMessage(hwnd, WM_QUIT, wPARAM, lparam);
		PostMessage(hwnd, WM_QUIT, wPARAM, lparam);
		break;
	case WM_SYSCOMMAND:
		if (wPARAM == SC_CLOSE)
		{
			if (MessageBox(NULL, "�Ƿ��˳�", "test333", MB_YESNO) == IDNO)
			{
				return 0;
			}
		}
		break;
	case WM_SIZE:
		PostMessage(hwnd, WM_MYMESSGAE, wPARAM, lparam);
		wmSize(hwnd, lparam);
		break;
	case WM_MYMESSGAE:
		myMessage();
		break;
	case WM_PAINT:
		myPaint();
		break;
	case WM_LBUTTONDOWN:
		InvalidateRect(hwnd,NULL,false);
		break;
	case WM_MOUSEMOVE:
		myMouseMove(lparam);
		break;
	}

	return DefWindowProc(hwnd, msgID, wPARAM, lparam);
}