#include <windows.h> 
#include "TCHAR.H"

int WINAPI _tWinMain(
	HINSTANCE hInctance,
	HINSTANCE hPrevInctance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	//2.���ڴ������봴���ڴ�
	HWND hwnd = NULL;
	hwnd = CreateWindow("Button", "����", WS_OVERLAPPEDWINDOW, 100, 50, 100, 50, NULL, NULL, hInctance, NULL);
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