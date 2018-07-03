#include "stdafx.h"
#include "MainWindow.h"



CMainWindow::CMainWindow()
{
	itemList.push_back(_T("23333333"));
	itemList.push_back(_T("6666666"));
	itemList.push_back(_T("22222222"));
	itemList.push_back(_T("66667777"));
	itemList.push_back(_T("678919222"));
	itemList.push_back(_T("testtest"));
	itemList.push_back(_T("testing..."));
	itemList.push_back(_T("hello world"));
	itemList.push_back(_T("hellohellohello"));
}

CMainWindow::~CMainWindow()
{
}


LPCTSTR CMainWindow::GetWindowClassName() const
{
	return _T("DuiMainWnd");
}

DuiLib::CDuiString CMainWindow::GetSkinFile()
{
	return _T("MainFrame.xml");
}

DuiLib::CDuiString CMainWindow::GetSkinFolder()
{
	return _T("combo");
}

void CMainWindow::InitWindow()
{
	m_PaintManager.AddFont( _T("ËÎÌו"), 18, true, false, false);
	m_PaintManager.AddFont( _T("ËÎÌו"), 30, true, false, false);
	
}

CControlUI * CMainWindow::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

void CMainWindow::Notify(TNotifyUI& msg)
{
	if (lstrcmp(msg.sType,DUI_MSGTYPE_WINDOWINIT) == 0)
	{
		pEdit = (CEditUI*)m_PaintManager.FindControl(_T("edt_name"));
		
	}
	else if (lstrcmp(msg.sType, DUI_MSGTYPE_TEXTCHANGED) == 0)
	{
		if (msg.pSender->GetName() == pEdit->GetName())
		{
			if (m_pListWnd && m_pListWnd->m_bShow)
			{
				m_pListWnd->ChangeItems(pEdit->GetText().GetData());
			}
		}
	}
	else if (lstrcmp(msg.sType, DUI_MSGTYPE_SETFOCUS) == 0)
	{
		if (msg.pSender->GetName() == pEdit->GetName())
		{
			if (!m_pListWnd)
			{
				m_pListWnd = new CListEditWnd();
				m_pListWnd->SetItemList(itemList);
				m_pListWnd->SetOwner(pEdit);
				m_pListWnd->Create(m_hWnd, NULL, WS_POPUP, WS_EX_TOOLWINDOW, 0, 0, 0, 0);
			}

			CDuiRect rect = pEdit->GetPos();
			DuiLib::CPoint pt;
			pt.x = rect.left + 1;
			pt.y = rect.bottom + 1;
			::ClientToScreen(m_PaintManager.GetPaintWindow(), &pt);
			if (m_pListWnd && !m_pListWnd->m_bShow)
			{
				::SetWindowPos(m_pListWnd->GetHWND(), HWND_TOPMOST, pt.x, pt.y, rect.GetWidth() - 2, rect.GetHeight() - 2 + 300, SWP_NOACTIVATE);
				m_pListWnd->ShowWindow(true, false);
				m_pListWnd->m_bShow = true;
			}
		}
	}
	else if (lstrcmp(msg.sType, _T("item_text_change_end")) == 0)
	{
		if (m_pListWnd && m_pListWnd->m_bShow)
		{
			pEdit->SetText(itemList[msg.wParam].c_str());
			m_pListWnd->ShowWindow(false, false);
			m_pListWnd->m_bShow = false;

		}
	}
	__super::Notify(msg);
}

LRESULT CMainWindow::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 1;
}

LRESULT CMainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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


