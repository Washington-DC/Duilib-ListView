#pragma once

class CDuiMainWnd:public WindowImplBase
{
public:
	CDuiMainWnd();
	~CDuiMainWnd();

	virtual LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();

	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual void InitWindow();

	virtual void Notify(TNotifyUI& msg);
};

