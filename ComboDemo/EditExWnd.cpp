#include "stdafx.h"
#include "EditExWnd.h"

#include "EditExUI.h"

CEditExWnd::CEditExWnd() : m_pOwner(NULL), m_hBkBrush(NULL), m_bInit(false), m_bDrawCaret(false)
{
}

void CEditExWnd::Init(CEditExUI* pOwner)
{
	m_pOwner = pOwner;
	RECT rcPos = CalPos();
	UINT uStyle = WS_CHILD | ES_AUTOHSCROLL | pOwner->GetWindowStyls();
	UINT uTextStyle = m_pOwner->GetTextStyle();
	if (uTextStyle & DT_LEFT) uStyle |= ES_LEFT;
	else if (uTextStyle & DT_CENTER) uStyle |= ES_CENTER;
	else if (uTextStyle & DT_RIGHT) uStyle |= ES_RIGHT;
	if (m_pOwner->IsPasswordMode()) uStyle |= ES_PASSWORD;
	Create(m_pOwner->GetManager()->GetPaintWindow(), NULL, uStyle, 0, rcPos);

	HFONT hFont = NULL;
	int iFontIndex = m_pOwner->GetFont();
	if (iFontIndex != -1)
		hFont = m_pOwner->GetManager()->GetFont(iFontIndex);
	if (hFont == NULL)
		hFont = m_pOwner->GetManager()->GetDefaultFontInfo()->hFont;

	SetWindowFont(m_hWnd, hFont, TRUE);
	Edit_LimitText(m_hWnd, m_pOwner->GetMaxChar());
	if (m_pOwner->IsPasswordMode()) Edit_SetPasswordChar(m_hWnd, m_pOwner->GetPasswordChar());
	Edit_SetText(m_hWnd, m_pOwner->GetText());
	Edit_SetModify(m_hWnd, FALSE);
	SendMessage(EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(0, 0));
	Edit_Enable(m_hWnd, m_pOwner->IsEnabled() == true);
	Edit_SetReadOnly(m_hWnd, m_pOwner->IsReadOnly() == true);

	//Styls
	::ShowWindow(m_hWnd, SW_SHOWNOACTIVATE);
	::SetFocus(m_hWnd);
	if (m_pOwner->IsAutoSelAll()) {
		int nSize = GetWindowTextLength(m_hWnd);
		if (nSize == 0) nSize = 1;
		Edit_SetSel(m_hWnd, 0, nSize);
	}
	else {
		int nSize = GetWindowTextLength(m_hWnd);
		Edit_SetSel(m_hWnd, nSize, nSize);
	}

	m_bInit = true;
}

RECT CEditExWnd::CalPos()
{
	CDuiRect rcPos = m_pOwner->GetPos();
	RECT rcInset = m_pOwner->GetTextPadding();
	rcPos.left += rcInset.left;
	rcPos.top += rcInset.top;
	rcPos.right -= rcInset.right;
	rcPos.bottom -= rcInset.bottom;
	LONG lEditHeight = m_pOwner->GetManager()->GetFontInfo(m_pOwner->GetFont())->tm.tmHeight;
	if (lEditHeight < rcPos.GetHeight()) {
		rcPos.top += (rcPos.GetHeight() - lEditHeight) / 2;
		rcPos.bottom = rcPos.top + lEditHeight;
	}

	CControlUI* pParent = m_pOwner;
	RECT rcParent;
	while (pParent = pParent->GetParent()) {
		if (!pParent->IsVisible()) {
			rcPos.left = rcPos.top = rcPos.right = rcPos.bottom = 0;
			break;
		}
		rcParent = pParent->GetClientPos();
		if (!::IntersectRect(&rcPos, &rcPos, &rcParent)) {
			rcPos.left = rcPos.top = rcPos.right = rcPos.bottom = 0;
			break;
		}
	}

	return rcPos;
}

LPCTSTR CEditExWnd::GetWindowClassName() const
{
	return _T("EditWnd");
}

LPCTSTR CEditExWnd::GetSuperClassName() const
{
	return WC_EDIT;
}

void CEditExWnd::OnFinalMessage(HWND hWnd)
{
	m_pOwner->Invalidate();
	// Clear reference and die
	if (m_hBkBrush != NULL) ::DeleteObject(m_hBkBrush);
	m_pOwner->GetManager()->RemoveNativeWindow(hWnd);
	m_pOwner->m_pWindow = NULL;
	delete this;
}

LRESULT CEditExWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	if (uMsg == WM_CREATE) {
		m_pOwner->GetManager()->AddNativeWindow(m_pOwner, m_hWnd);
		if (m_pOwner->GetManager()->IsLayered()) {
			::SetTimer(m_hWnd, DEFAULT_TIMERID, ::GetCaretBlinkTime(), NULL);
		}
		bHandled = FALSE;
	}
	else if (uMsg == WM_KILLFOCUS) lRes = OnKillFocus(uMsg, wParam, lParam, bHandled);
	else if (uMsg == OCM_COMMAND) {
		if (GET_WM_COMMAND_CMD(wParam, lParam) == EN_CHANGE) lRes = OnEditChanged(uMsg, wParam, lParam, bHandled);
		else if (GET_WM_COMMAND_CMD(wParam, lParam) == EN_UPDATE) {
			RECT rcClient;
			::GetClientRect(m_hWnd, &rcClient);
			::InvalidateRect(m_hWnd, &rcClient, FALSE);
		}
	}
	else if (uMsg == WM_KEYDOWN && TCHAR(wParam) == VK_RETURN) {
		m_pOwner->GetManager()->SendNotify(m_pOwner, DUI_MSGTYPE_RETURN);
	}
	else if (uMsg == OCM__BASE + WM_CTLCOLOREDIT || uMsg == OCM__BASE + WM_CTLCOLORSTATIC) {
		if (m_pOwner->GetManager()->IsLayered() && !m_pOwner->GetManager()->IsPainting()) {
			m_pOwner->GetManager()->AddNativeWindow(m_pOwner, m_hWnd);
		}
		DWORD clrColor = m_pOwner->GetNativeEditBkColor();
		if (clrColor == 0xFFFFFFFF) return 0;
		::SetBkMode((HDC)wParam, TRANSPARENT);
		DWORD dwTextColor = m_pOwner->GetTextColor();
		::SetTextColor((HDC)wParam, RGB(GetBValue(dwTextColor), GetGValue(dwTextColor), GetRValue(dwTextColor)));
		if (clrColor < 0xFF000000) {
			if (m_hBkBrush != NULL) ::DeleteObject(m_hBkBrush);
			RECT rcWnd = m_pOwner->GetManager()->GetNativeWindowRect(m_hWnd);
			HBITMAP hBmpEditBk = CRenderEngine::GenerateBitmap(m_pOwner->GetManager(), rcWnd, m_pOwner, clrColor);
			m_hBkBrush = ::CreatePatternBrush(hBmpEditBk);
			::DeleteObject(hBmpEditBk);
		}
		else {
			if (m_hBkBrush == NULL) {
				m_hBkBrush = ::CreateSolidBrush(RGB(GetBValue(clrColor), GetGValue(clrColor), GetRValue(clrColor)));
			}
		}
		return (LRESULT)m_hBkBrush;
	}
	else if (uMsg == WM_PAINT) {
		if (m_pOwner->GetManager()->IsLayered()) {
			m_pOwner->GetManager()->AddNativeWindow(m_pOwner, m_hWnd);
		}
		bHandled = FALSE;
	}
	else if (uMsg == WM_PRINT) {
		if (m_pOwner->GetManager()->IsLayered()) {
			lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
			if (m_pOwner->IsEnabled() && m_bDrawCaret) { // todo:ÅÐ¶ÏÊÇ·ñenabled
				RECT rcClient;
				::GetClientRect(m_hWnd, &rcClient);
				POINT ptCaret;
				::GetCaretPos(&ptCaret);
				RECT rcCaret = { ptCaret.x, ptCaret.y, ptCaret.x, ptCaret.y + rcClient.bottom - rcClient.top };
				CRenderEngine::DrawLine((HDC)wParam, rcCaret, 1, 0xFF000000);
			}
			return lRes;
		}
		bHandled = FALSE;
	}
	else if (uMsg == WM_TIMER) {
		if (wParam == DEFAULT_TIMERID) {
			m_bDrawCaret = !m_bDrawCaret;
			RECT rcClient;
			::GetClientRect(m_hWnd, &rcClient);
			::InvalidateRect(m_hWnd, &rcClient, FALSE);
			return 0;
		}
		bHandled = FALSE;
	}
	else bHandled = FALSE;
	if (!bHandled) return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	return lRes;
}

LRESULT CEditExWnd::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT lRes = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	if ((HWND)wParam != m_pOwner->GetManager()->GetPaintWindow()) {
		::SendMessage(m_pOwner->GetManager()->GetPaintWindow(), WM_KILLFOCUS, wParam, lParam);
	}
	SendMessage(WM_CLOSE);
	return lRes;
}

LRESULT CEditExWnd::OnEditChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if (!m_bInit) return 0;
	if (m_pOwner == NULL) return 0;
	// Copy text back
	int cchLen = ::GetWindowTextLength(m_hWnd) + 1;
	LPTSTR pstr = static_cast<LPTSTR>(_alloca(cchLen * sizeof(TCHAR)));
	ASSERT(pstr);
	if (pstr == NULL) return 0;
	::GetWindowText(m_hWnd, pstr, cchLen);
	m_pOwner->m_sText = pstr;
	m_pOwner->GetManager()->SendNotify(m_pOwner, DUI_MSGTYPE_TEXTCHANGED);
	if (m_pOwner->GetManager()->IsLayered()) m_pOwner->Invalidate();
	return 0;
}
