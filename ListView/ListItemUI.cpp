#include "stdafx.h"
#include "ListItemUI.h"


CListItemUI::CListItemUI()
{
	DUI__Trace(L"\t------CListItemUI");

	m_strItemName = L"test";
	m_strItemContent = L"abc12345lalalala";
	m_strItemInfo = L"Hello World,Hello Duilib";

	m_bActive = false;
}


CListItemUI::~CListItemUI()
{
}

LPCTSTR CListItemUI::GetClass() const
{
	return L"CustomListItemUI";
}

void CListItemUI::DoEvent(TEventUI& event)
{
	CTabLayoutUI* pTabUI = static_cast<CTabLayoutUI*>(this->FindSubControl(L"tab"));
	if (!m_bActive)
	{
		if (event.Type == UIEVENT_MOUSEENTER)//enter
		{
			pTabUI->SelectItem(1);
		}
		else if (event.Type == UIEVENT_MOUSELEAVE)//leave
		{
			pTabUI->SelectItem(0);
		}
		else if (event.Type == UIEVENT_MOUSEHOVER)//hover
		{
		}
	}
	CListContainerElementUI::DoEvent(event);
}


void CListItemUI::SetItemName(LPCTSTR strName)
{
	m_strItemName = strName;
	CTabLayoutUI* pTabUI = static_cast<CTabLayoutUI*>(this->FindSubControl(L"tab"));
	int count = 3/*pTabUI->GetCount()*/;
	for (int i = 0; i < count; i++)
	{
		CContainerUI* pContainerUI = static_cast<CContainerUI*>(pTabUI->GetItemAt(i));
		CTextUI* pTextUI = static_cast<CTextUI*>(pContainerUI->FindSubControl(L"name"));
		pTextUI->SetText(strName);
	}
}

void CListItemUI::SetItemContent(LPCTSTR strContent)
{
	m_strItemContent = strContent;
	CTabLayoutUI* pTabUI = static_cast<CTabLayoutUI*>(this->FindSubControl(L"tab"));
	int count = 3 /*pTabUI->GetCount()*/;
	for (int i = 0; i < count; i++)
	{
		CContainerUI* pContainerUI = static_cast<CContainerUI*>(pTabUI->GetItemAt(i));
		CTextUI* pTextUI = static_cast<CTextUI*>(pContainerUI->FindSubControl(L"content"));
		pTextUI->SetText(strContent);
	}
}

void CListItemUI::SetItemInfo(LPCTSTR strInfo)
{
	m_strItemInfo = strInfo;
	CTabLayoutUI* pTabUI = static_cast<CTabLayoutUI*>(this->FindSubControl(L"tab"));

	CContainerUI* pContainerUI = static_cast<CContainerUI*>(pTabUI->GetItemAt(2));
	CTextUI* pTextUI = static_cast<CTextUI*>(pContainerUI->FindSubControl(L"info"));
	pTextUI->SetText(strInfo);
}

void CListItemUI::SetActive(bool bActive /*= true*/)
{
	m_bActive = bActive;
	CTabLayoutUI* pTabUI = static_cast<CTabLayoutUI*>(this->FindSubControl(L"tab"));
	if (m_bActive)
	{
		this->SetFixedHeight(80);
		pTabUI->SelectItem(2);
	}
	else
	{
		this->SetFixedHeight(50);
		pTabUI->SelectItem(0);
	}
}




