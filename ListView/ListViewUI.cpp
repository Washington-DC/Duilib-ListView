#include "stdafx.h"
#include "ListViewUI.h"


CListViewUI::CListViewUI()
{
	m_nActiveItem = -1;
	DUI__Trace(L"\t------CListViewUI");
}


CListViewUI::~CListViewUI()
{
}


LPCTSTR CListViewUI::GetClass() const
{
	return _T("CustomListViewUI");
}

LPVOID CListViewUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcsicmp(pstrName, _T("ListView")) == 0)
		return this;
	return CListUI::GetInterface(pstrName);
}

CControlUI* CListViewUI::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, L"ListItem") == 0)
		return new CListItemUI();
	return NULL;
}

void CListViewUI::DoInit()
{
	/*for (int i = 0; i < 20; i++)
	{
	CDialogBuilder builder;
	CListItemUI* pItem = static_cast<CListItemUI*>(builder.Create(L"ListItemLayout.xml", (UINT)0, this, m_pManager));

	CDuiString text;
	text.Format(L"test-%02d", i);
	pItem->SetItemName(text);
	Add(pItem);
	}*/
}


bool CListViewUI::SetActiveItem(int iIndex, bool bTakeFocus)
{
	if (!__super::SelectItem(iIndex,bTakeFocus))
	{
		return false;
	}
	//取消原有的选中状态
	if (m_nActiveItem != -1)
	{
		CListItemUI* pItem = static_cast<CListItemUI*>(this->GetItemAt(m_nActiveItem));
		pItem->SetActive(false);
	}
	m_nActiveItem = iIndex;
	//将新的item选中状态
	if (m_nActiveItem != -1)
	{
		CListItemUI* pItem = static_cast<CListItemUI*>(this->GetItemAt(m_nActiveItem));
		pItem->SetActive(true);
	}
	return true;
}



