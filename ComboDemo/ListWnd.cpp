#include "stdafx.h"
#include "ListWnd.h"




LPCTSTR CListEditWnd::GetWindowClassName() const
{
	return _T("ListEditWnd");
}

DuiLib::CDuiString CListEditWnd::GetSkinFile()
{
	return _T("ListItem.xml");
}

DuiLib::CDuiString CListEditWnd::GetSkinFolder()
{
	return _T("combo");
}

void CListEditWnd::InitWindow()
{

}

void CListEditWnd::Notify(TNotifyUI& msg)
{
	//CListUI* pList = (CListUI*)m_PaintManager.FindControl("listitems");
	//if (msg.sType == DUI_MSGTYPE_ITEMSELECT)
	//{
	//	int nIndex = pList->GetCurSel();
	//	pOwner_->SetText(pList->GetItemAt(nIndex)->GetText());

	//	pOwner_->SetFocus();

	//	ShowWindow(false, false);
	//	m_bShow = false;

	//	/*this->Close();

	//	delete this;*/
	//	//this = nullptr;
	//}

	//if (msg.sType == DUI_MSGTYPE_BUTTONDOWN)
	//{
	//	CComboWnd
	//	CComboUI* pControl = m_PaintManager.FindControl()
	//}

	__super::Notify(msg);
}

void CListEditWnd::SetItemList(std::vector<std::string> itemlist)
{
	m_itemlist_.swap(std::vector<std::string>());
	m_itemlist_.assign(itemlist.begin(), itemlist.end());
	m_itemlist_.shrink_to_fit();
}


void CListEditWnd::ChangeItems(std::string keyword)
{
	CListUI* pList = (CListUI*)m_PaintManager.FindControl("listitems");
	pList->RemoveAll();

	for (size_t i = 0; i < m_itemlist_.size(); i++)
	{
		if (m_itemlist_[i].find(keyword) != std::string::npos)
		{
			CListLabelElementUI* pLable = new CListLabelElementUI();
			pLable->SetText(m_itemlist_[i].c_str());
			pLable->SetTag(i);
			pList->Add(pLable);
		}
	}
}

LRESULT CListEditWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*if (uMsg == WM_CLOSE)
	{
	pOwner_->SetManager(pOwner_->GetManager(), pOwner_->GetParent(), false);
	pOwner_->SetFocus();
	}
	else*/ 
	if (uMsg == WM_LBUTTONUP)
	{
		CListUI* pList = (CListUI*)m_PaintManager.FindControl("listitems");
		POINT pt = { 0 };
		::GetCursorPos(&pt);
		::ScreenToClient(m_PaintManager.GetPaintWindow(), &pt);
		CControlUI* pControl = m_PaintManager.FindControl(pt);
		int nIndex = pList->GetItemIndex(pControl);
		pOwner_->GetManager()->SendNotify(pOwner_, _T("item_text_change_end"), nIndex, 0);
		if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_SCROLLBAR) != 0) 
			PostMessage(WM_KILLFOCUS);
	}
	else if (uMsg == WM_KILLFOCUS)
	{
		if (m_hWnd != (HWND)wParam) {
			HWND hWnd = ::GetFocus();
			HWND hParentWnd = NULL;
			bool bIsChildFocus = false;
			while (hParentWnd = ::GetParent(hWnd)) {
				if (m_hWnd == hParentWnd) {
					bIsChildFocus = true;
					break;
				}
				hWnd = hParentWnd;
			}
			pOwner_->SetManager(pOwner_->GetManager(), pOwner_->GetParent(), false);
			//pOwner_->SetFocus();
			/*if (!bIsChildFocus) {
				PostMessage(WM_CLOSE);
				return 0;
				}*/

			
		}
	}
	LRESULT lRes = 0;
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return __super::HandleMessage(uMsg, wParam, lParam);
}


