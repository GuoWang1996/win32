#pragma once
#include "day1.h"
class XmlDemo : public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const { return _T("DUIMainFrame"); }
	virtual CDuiString GetSkinFile() { return "duilib.xml"; }
	virtual CDuiString GetSkinFolder() { return _T(""); }
	virtual void    Notify(TNotifyUI& msg);//duiLib��Ϣ����
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);//w32��Ϣ
};
