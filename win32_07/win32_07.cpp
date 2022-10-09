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
			MessageBox(NULL, "ȷ����ť", "��ʾ", MB_YESNO);
		}
		break;
	}
	return FALSE;//���������ĶԻ�����Ϣ������
}
int WINAPI _tWinMain(
	HINSTANCE hInctance,
	HINSTANCE hPrevInctance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	hInctance_m = hInctance;
	AllocConsole();//����DOS����
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//1.ע�ᴰ����
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;//���뻺����
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//���ô��ڱ���
	wc.hCursor = NULL;//Ĭ�Ϲ��
	wc.hIcon = NULL;//Ĭ��ͼ��
	//wc.hIconSm = LoadIcon(hInctance, (LPCSTR)IDI_ICON2);//Ĭ��ͼ��
	wc.hInstance = hInctance;//��ǰ����ʵ�����
	wc.lpfnWndProc = WindProc;
	wc.lpszClassName = "��������";
	wc.lpszMenuName = (LPSTR)IDR_MENU1;//Ĭ�ϲ˵�
	wc.style = CS_HREDRAW | CS_VREDRAW;//��ⴰ��λ�ñ仯ˢ�»���
	RegisterClassEx(&wc);//��������д�����ϵͳ
	//2.���ڴ������봴���ڴ�
	HWND hwnd = CreateWindow("��������", "���±�", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInctance, (LPVOID)NULL);
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
	RegisterClassEx(&wc);//��������д�����ϵͳ
	//�����Ӵ���
	//HWND hwnd2 = CreateWindow("button", "����", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 100, 50, 100, 100, hwnd, NULL, hInctance, (LPVOID)NULL);
	//3.��ʾ����
	ShowWindow(hwnd, SW_SHOW);//ԭ��ˢ����ʾ
	UpdateWindow(hwnd);//ˢ�´��� ��ֹ©������Դ
	//��Ϣѭ��
	MSG nMSG = { 0 };
	while (GetMessage(&nMSG, NULL, 0, 0)) //�������������WM_QUIT�������Ϣ���򷵻�ֵ���㡣

										 //�������������WM_QUIT��Ϣ���򷵻�ֵΪ�㡣WM_QUIT��ʾ��ֹӦ�ó��������
	{
		TranslateMessage(&nMSG);//������Ϣ
		DispatchMessage(&nMSG);//�ɷ���Ϣ  �������ڴ���������
	}
	return 0;
}
//���ڴ�����(�Զ��壬������Ϣ)
LRESULT CALLBACK WindProc(HWND hwnd, UINT msgID, WPARAM wPARAM, LPARAM lparam) {
	switch (msgID)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
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
	case WM_COMMAND:
		myCommand(hwnd, wPARAM);
	}

	return DefWindowProc(hwnd, msgID, wPARAM, lparam);
}