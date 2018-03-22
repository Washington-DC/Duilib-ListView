#include "stdafx.h"
#include "ItemInfoWnd.h"


CItemInfoWnd::CItemInfoWnd()
{
}


CItemInfoWnd::~CItemInfoWnd()
{
}


LPCTSTR CItemInfoWnd::GetWindowClassName() const
{
	return L"DuiMainWnd";
}

CDuiString CItemInfoWnd::GetSkinFile()
{
	return L"ItemInfo.xml";
}

CDuiString CItemInfoWnd::GetSkinFolder()
{
	return L"list";
}

LRESULT CItemInfoWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg)
	{
	case WM_TIMER: 
		lRes = OnTimer(uMsg, wParam, lParam, bHandled);
		break;
	default: 
		bHandled = FALSE;
		break;
	}

	if (bHandled) return lRes;
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) 
		return lRes;
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CItemInfoWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//GetParent(m_hWnd)
	Close();

	return 0;
}
