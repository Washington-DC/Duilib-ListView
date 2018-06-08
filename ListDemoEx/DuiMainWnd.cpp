#include "stdafx.h"
#include "DuiMainWnd.h"


CDuiMainWnd::CDuiMainWnd()
{
}


CDuiMainWnd::~CDuiMainWnd()
{
}

LPCTSTR CDuiMainWnd::GetWindowClassName() const
{
	return L"DuiMainWnd";
}

DuiLib::CDuiString CDuiMainWnd::GetSkinFile()
{
	return L"MainFrame.xml";
}

DuiLib::CDuiString CDuiMainWnd::GetSkinFolder()
{
	return L"list_ex";
}

void CDuiMainWnd::InitWindow()
{
	CListUI * pList = static_cast<CListUI *>(m_PaintManager.FindControl(_T("list")));

	for (int i = 0; i < 10; i++)
	{
		CDialogBuilder builder;
		CListContainerElementUI* pHBoxUI = static_cast<CListContainerElementUI*>(builder.Create(_T("ListItem.xml")));
		pList->Add(pHBoxUI);
	}
}

CControlUI * CDuiMainWnd::CreateControl(LPCTSTR pstrClass)
{

	return NULL;
}

void CDuiMainWnd::Notify(TNotifyUI& msg)
{
	__super::Notify(msg);
}

