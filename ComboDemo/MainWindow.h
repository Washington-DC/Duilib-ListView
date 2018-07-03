#pragma once

#include "ListWnd.h"

class CMainWindow :public WindowImplBase
{
public:
	CMainWindow();
	~CMainWindow();

	virtual LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();

	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual void InitWindow();

	virtual void Notify(TNotifyUI& msg);

	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:

	CEditUI* pEdit = nullptr;

	CListEditWnd* m_pListWnd = nullptr;

	std::vector<std::string > itemList;
};

