#include "duiLibdemo.h"
#include "XmlDemo.h"
LPCTSTR duiLibdemo::GetWindowClassName() const
{
	return "DUIMainFrame"; 
}

void duiLibdemo::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == _T("btnHello"))
		{
			::MessageBox(NULL, _T("���ǰ�ť"), _T("����˰�ť"), NULL);
		}
	}

}

LRESULT duiLibdemo::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
		//CControlUI *pWnd = new CButtonUI();
		//pWnd->SetName(_T("btnHello"));      // ���ÿؼ������ƣ�����������ڱ�ʶÿһ���ؼ�������Ψһ���൱��MFC����Ŀؼ�ID
		//pWnd->SetText("Hello World");   // ��������
		//pWnd->SetBkColor(0xFF00FF00);       // ���ñ���ɫ

		//m_PaintManager.Init(m_hWnd);
		//m_PaintManager.AttachDialog(pWnd);
		//m_PaintManager.AddNotifier(this);
		//return lRes;
		m_PaintManager.Init(m_hWnd);

		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(_T("duilib.xml"), (UINT)0, NULL, &m_PaintManager);   // duilib.xml��Ҫ�ŵ�exeĿ¼��
		ASSERT(pRoot && "Failed to parse XML");

		m_PaintManager.AttachDialog(pRoot);
		m_PaintManager.AddNotifier(this);   // ��ӿؼ�����Ϣ��Ӧ��������Ϣ�ͻᴫ�ﵽduilib����Ϣѭ�������ǿ�����Notify����������Ϣ����
		return lRes;

	}
	else if (uMsg == WM_CLOSE)
	{
		DestroyWindow(m_hWnd);
	}        // ����3����ϢWM_NCACTIVATE��WM_NCCALCSIZE��WM_NCPAINT��������ϵͳ������
	else if (uMsg == WM_NCACTIVATE)
	{
		if (!::IsIconic(m_hWnd))
		{
			return (wParam == 0) ? TRUE : FALSE;
		}
	}
	else if (uMsg == WM_NCCALCSIZE)
	{
		return 0;
	}
	else if (uMsg == WM_NCPAINT)
	{
		return 0;
	}


	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);

}
//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
//{
//	::CoInitialize(NULL);
//	CPaintManagerUI::SetInstance(hInstance);
//	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());   // ������Դ��Ĭ��·�����˴�����Ϊ��exe��ͬһĿ¼��
//
//	duiLibdemo *duiFrame=new duiLibdemo();
//	if (duiFrame)
//	{
//		duiFrame->Create(NULL, "123", UI_WNDSTYLE_FRAME,0,0,0,500,300);
//		duiFrame->CenterWindow();
//		duiFrame->ShowModal();
//		
//	}
//	else
//	{
//		MessageBox(NULL,"11", "1",MB_OK);
//	}
//	CPaintManagerUI::Term();
//	::CoUninitialize();
//	return 1;
//}
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//CPaintManagerUI::SetInstance(hInstance);

	//XmlDemo duiFrame;
	//duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	//duiFrame.CenterWindow();
	//duiFrame.ShowModal();
	wchar_t  *pwText = L"Hello World";
	wchar_t *p = pwText;
	p = L"��������";
	wchar_t  pwText1 = L'1';

	pwText = L"��������";
	
	return 0;
}