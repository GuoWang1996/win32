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
			::MessageBox(NULL, _T("我是按钮"), _T("点击了按钮"), NULL);
		}
	}

}

LRESULT duiLibdemo::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
		//CControlUI *pWnd = new CButtonUI();
		//pWnd->SetName(_T("btnHello"));      // 设置控件的名称，这个名称用于标识每一个控件，必须唯一，相当于MFC里面的控件ID
		//pWnd->SetText("Hello World");   // 设置文字
		//pWnd->SetBkColor(0xFF00FF00);       // 设置背景色

		//m_PaintManager.Init(m_hWnd);
		//m_PaintManager.AttachDialog(pWnd);
		//m_PaintManager.AddNotifier(this);
		//return lRes;
		m_PaintManager.Init(m_hWnd);

		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(_T("duilib.xml"), (UINT)0, NULL, &m_PaintManager);   // duilib.xml需要放到exe目录下
		ASSERT(pRoot && "Failed to parse XML");

		m_PaintManager.AttachDialog(pRoot);
		m_PaintManager.AddNotifier(this);   // 添加控件等消息响应，这样消息就会传达到duilib的消息循环，我们可以在Notify函数里做消息处理
		return lRes;

	}
	else if (uMsg == WM_CLOSE)
	{
		DestroyWindow(m_hWnd);
	}        // 以下3个消息WM_NCACTIVATE、WM_NCCALCSIZE、WM_NCPAINT用于屏蔽系统标题栏
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
//	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());   // 设置资源的默认路径（此处设置为和exe在同一目录）
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
	p = L"尼玛死了";
	wchar_t  pwText1 = L'1';

	pwText = L"尼玛死了";
	
	return 0;
}