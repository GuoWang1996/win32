#include <windows.h> 
#include "TCHAR.H"

int WINAPI _tWinMain(
	HINSTANCE hInctance,
	HINSTANCE hPrevInctance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	//2.���ڴ������봴���ڴ�
	HWND hwnd = CreateWindow("button", "����", WS_VISIBLE| WS_CHILD|BS_PUSHBUTTON, 100, 50, 100, 50, hwnd, (HMENU)1000, hInctance, (LPVOID)NULL);
	//3.��ʾ����
	ShowWindow(hwnd, SW_SHOW);//ԭ��ˢ����ʾ
	UpdateWindow(hwnd);//ˢ�´��� ��ֹ©������Դ
	//��Ϣѭ��
	MSG nMSG = { 0 };
	while (GetMessage(&nMSG, NULL, 0, 0))
	{
		TranslateMessage(&nMSG);//������Ϣ
		DispatchMessage(&nMSG);//�ɷ���Ϣ  �������ڴ���������
	}
	return 0;
}