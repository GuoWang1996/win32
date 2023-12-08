#include "XmlDemo.h"

void XmlDemo::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == _T("btnHello"))
		{
			::MessageBox(NULL, _T("���ǰ�ť"), _T("����˰�ť"), NULL);
		}
	}
	__super::Notify(msg);
}

LRESULT XmlDemo::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	if (uMsg == WM_DESTROY)
	{
		::PostQuitMessage(0);
		return 0;
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}
