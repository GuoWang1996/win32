#include <windows.h> 
#include "TCHAR.H"
//���ڴ�����(�Զ��壬������Ϣ)
LRESULT CALLBACK WindProc(HWND hwnd,UINT msgID,WPARAM wPARAM,LPARAM lparam) {
	
		if (msgID == WM_DESTROY) {
			PostQuitMessage(0);			//����Ϣ����GetMessage����������
		}

	
	return DefWindowProc(hwnd, msgID, wPARAM,lparam);
}
int WINAPI _tWinMain(
	HINSTANCE hInctance,
	HINSTANCE hPrevInctance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	//1.ע�ᴰ����
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;//���뻺����
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//���ô��ڱ���
	wc.hCursor = NULL;//Ĭ�Ϲ��
	wc.hIcon = NULL;//Ĭ��ͼ��
	wc.hInstance = hInctance;//��ǰ����ʵ�����
	wc.lpfnWndProc = WindProc;
	wc.lpszClassName = "��������";
	wc.lpszMenuName = NULL;//Ĭ�ϲ˵�
	wc.style = CS_HREDRAW | CS_VREDRAW;//��ⴰ��λ�ñ仯ˢ�»���
	RegisterClass(&wc);//��������д�����ϵͳ
	//2.���ڴ������봴���ڴ�
	HWND hwnd= CreateWindow("��������","����",WS_OVERLAPPEDWINDOW,100,100,500,500,NULL,NULL, hInctance, (LPVOID)NULL);
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
	HWND hwnd2 = CreateWindowEx(0,"�Ӵ���", "����",WS_CHILD|WS_VISIBLE| WS_OVERLAPPEDWINDOW, 100, 100, 200, 200, hwnd, NULL, hInctance, (LPVOID)NULL);
	//3.��ʾ����
	ShowWindow(hwnd,SW_SHOW);//ԭ��ˢ����ʾ
	UpdateWindow(hwnd);//ˢ�´��� ��ֹ©������Դ
	//��Ϣѭ��
	MSG nMSG = {0};
	while (GetMessage(&nMSG, NULL, 0, 0)) //�������������WM_QUIT�������Ϣ���򷵻�ֵ���㡣

										 //�������������WM_QUIT��Ϣ���򷵻�ֵΪ�㡣WM_QUIT��ʾ��ֹӦ�ó��������
	{
		TranslateMessage(&nMSG);//������Ϣ
		DispatchMessage(&nMSG);//�ɷ���Ϣ  �������ڴ���������
	}
	return 0;
}