#pragma once
#include "day1.h"

class duiLibdemo : public CWindowWnd, public INotifyUI
{

public:

	virtual LPCTSTR GetWindowClassName() const;//返回自定义类名
	virtual void    Notify(TNotifyUI& msg);//duiLib消息机制
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);//w32消息
public:
	CPaintManagerUI m_PaintManager;//渲染器对象


};


