#pragma once
#include "day1.h"

class duiLibdemo : public CWindowWnd, public INotifyUI
{

public:

	virtual LPCTSTR GetWindowClassName() const;//�����Զ�������
	virtual void    Notify(TNotifyUI& msg);//duiLib��Ϣ����
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);//w32��Ϣ
public:
	CPaintManagerUI m_PaintManager;//��Ⱦ������


};


