#include "stdafx.h"
#include "DuiMainWnd.h"

#include "ListViewUI.h"


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
	return L"list";
}

void CDuiMainWnd::InitWindow()
{
	m_PaintManager.AddFont(0, L"ËÎÌו", 18, true, false, false, true);
	m_PaintManager.AddFont(1, L"ËÎÌו", 18, false, false, false, true);

	CListViewUI* pListView = static_cast<CListViewUI*>(m_PaintManager.FindControl(L"mylist"));

	for (int i = 0; i < 20; i++)
	{
		CDialogBuilder builder;
		CListItemUI* pItem = static_cast<CListItemUI*>(builder.Create(L"ListItemLayout.xml", (UINT)0, this, &m_PaintManager));

		CDuiString text;
		text.Format(L"test-%02d", i);
		pItem->SetItemName(text);
		pListView->Add(pItem);
	}
}

CControlUI * CDuiMainWnd::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, L"ListView") == 0)
		return	new CListViewUI();
	if (_tcsicmp(pstrClass, L"ListItem") == 0)
		return new CListItemUI();
	return NULL;
}

void CDuiMainWnd::Notify(TNotifyUI& msg)
{
	CListViewUI* pListView = static_cast<CListViewUI*>(m_PaintManager.FindControl(L"mylist"));

	if (msg.sType == DUI_MSGTYPE_ITEMSELECT)
	{
		int index = pListView->GetCurSel();
		pListView->SetActiveItem(index, true);
	}

	__super::Notify(msg);
}


