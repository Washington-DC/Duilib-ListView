#include "stdafx.h"
#include "EditExUI.h"

#include "EditExWnd.h"


CEditExUI::CEditExUI()
	: m_pWindow(NULL)
	, m_uMaxChar(255)
	, m_bReadOnly(false)
	, m_bPasswordMode(false)
	, m_cPasswordChar(_T('*'))
	, m_bAutoSelAll(false)
	, m_uButtonState(0)
	, m_dwEditbkColor(0xFFFFFFFF)
	, m_iWindowStyls(0)
{
	SetTextPadding(CDuiRect(4, 3, 4, 3));
	SetBkColor(0xFFFFFFFF);
}

LPCTSTR CEditExUI::GetClass() const
{
	return _T("EditEx");
}

LPVOID CEditExUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, DUI_CTR_EDIT) == 0) return static_cast<CEditExUI*>(this);
	return CLabelUI::GetInterface(pstrName);
}

UINT CEditExUI::GetControlFlags() const
{
	if (!IsEnabled()) return CControlUI::GetControlFlags();

	return UIFLAG_SETCURSOR | UIFLAG_TABSTOP;
}

HWND CEditExUI::GetNativeWindow() const
{
	if (m_pWindow) return m_pWindow->GetHWND();
	return NULL;
}

void CEditExUI::DoEvent(TEventUI& event)
{
	if (!IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND) {
		if (m_pParent != NULL) m_pParent->DoEvent(event);
		else CLabelUI::DoEvent(event);
		return;
	}

	if (event.Type == UIEVENT_SETCURSOR && IsEnabled())
	{
		::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_IBEAM)));
		return;
	}
	if (event.Type == UIEVENT_WINDOWSIZE)
	{
		if (m_pWindow != NULL) m_pManager->SetFocusNeeded(this);
	}
	if (event.Type == UIEVENT_SCROLLWHEEL)
	{
		if (m_pWindow != NULL) return;
	}
	if (event.Type == UIEVENT_SETFOCUS && IsEnabled())
	{
		if (m_pWindow) return;
		m_pWindow = new CEditExWnd();
		ASSERT(m_pWindow);
		m_pWindow->Init(this);
		Invalidate();
	}
	if (event.Type == UIEVENT_KILLFOCUS && IsEnabled())
	{
		Invalidate();
	}
	if (event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK || event.Type == UIEVENT_RBUTTONDOWN)
	{
		if (IsEnabled()) {
			GetManager()->ReleaseCapture();
			if (IsFocused() && m_pWindow == NULL)
			{
				m_pWindow = new CEditExWnd();
				ASSERT(m_pWindow);
				m_pWindow->Init(this);
			}
			else if (m_pWindow != NULL)
			{
				if (!m_bAutoSelAll) {
					POINT pt = event.ptMouse;
					pt.x -= m_rcItem.left + m_rcTextPadding.left;
					pt.y -= m_rcItem.top + m_rcTextPadding.top;
					Edit_SetSel(*m_pWindow, 0, 0);
					::SendMessage(*m_pWindow, WM_LBUTTONDOWN, event.wParam, MAKELPARAM(pt.x, pt.y));
				}
			}
		}
		return;
	}
	if (event.Type == UIEVENT_MOUSEMOVE)
	{
		return;
	}
	if (event.Type == UIEVENT_BUTTONUP)
	{
		return;
	}
	if (event.Type == UIEVENT_CONTEXTMENU)
	{
		return;
	}
	if (event.Type == UIEVENT_MOUSEENTER)
	{
		if (::PtInRect(&m_rcItem, event.ptMouse)) {
			if (IsEnabled()) {
				if ((m_uButtonState & UISTATE_HOT) == 0) {
					m_uButtonState |= UISTATE_HOT;
					Invalidate();
				}
			}
		}
	}
	if (event.Type == UIEVENT_MOUSELEAVE)
	{
		if (!::PtInRect(&m_rcItem, event.ptMouse)) {
			if (IsEnabled()) {
				if ((m_uButtonState & UISTATE_HOT) != 0) {
					m_uButtonState &= ~UISTATE_HOT;
					Invalidate();
				}
			}
			if (m_pManager) m_pManager->RemoveMouseLeaveNeeded(this);
		}
		else {
			if (m_pManager) m_pManager->AddMouseLeaveNeeded(this);
			return;
		}
	}
	CLabelUI::DoEvent(event);
}

void CEditExUI::SetEnabled(bool bEnable)
{
	CControlUI::SetEnabled(bEnable);
	if (!IsEnabled()) {
		m_uButtonState = 0;
	}
}

void CEditExUI::SetText(LPCTSTR pstrText)
{
	m_sText = pstrText;
	if (m_pWindow != NULL) Edit_SetText(*m_pWindow, m_sText);
	Invalidate();
}

void CEditExUI::SetMaxChar(UINT uMax)
{
	m_uMaxChar = uMax;
	if (m_pWindow != NULL) Edit_LimitText(*m_pWindow, m_uMaxChar);
}

UINT CEditExUI::GetMaxChar()
{
	return m_uMaxChar;
}

void CEditExUI::SetReadOnly(bool bReadOnly)
{
	if (m_bReadOnly == bReadOnly) return;

	m_bReadOnly = bReadOnly;
	if (m_pWindow != NULL) Edit_SetReadOnly(*m_pWindow, m_bReadOnly);
	Invalidate();
}

bool CEditExUI::IsReadOnly() const
{
	return m_bReadOnly;
}

void CEditExUI::SetNumberOnly(bool bNumberOnly)
{
	if (bNumberOnly)
	{
		m_iWindowStyls |= ES_NUMBER;
	}
	else
	{
		m_iWindowStyls &= ~ES_NUMBER;
	}
}

bool CEditExUI::IsNumberOnly() const
{
	return m_iWindowStyls&ES_NUMBER ? true : false;
}

int CEditExUI::GetWindowStyls() const
{
	return m_iWindowStyls;
}

HWND CEditExUI::GetNativeEditHWND() const
{
	if (m_pWindow == NULL) return NULL;
	return m_pWindow->GetHWND();
}

void CEditExUI::SetPasswordMode(bool bPasswordMode)
{
	if (m_bPasswordMode == bPasswordMode) return;
	m_bPasswordMode = bPasswordMode;
	Invalidate();
}

bool CEditExUI::IsPasswordMode() const
{
	return m_bPasswordMode;
}

void CEditExUI::SetPasswordChar(TCHAR cPasswordChar)
{
	if (m_cPasswordChar == cPasswordChar) return;
	m_cPasswordChar = cPasswordChar;
	if (m_pWindow != NULL) Edit_SetPasswordChar(*m_pWindow, m_cPasswordChar);
	Invalidate();
}

TCHAR CEditExUI::GetPasswordChar() const
{
	return m_cPasswordChar;
}

bool CEditExUI::IsAutoSelAll()
{
	return m_bAutoSelAll;
}

void CEditExUI::SetAutoSelAll(bool bAutoSelAll)
{
	m_bAutoSelAll = bAutoSelAll;
}

LPCTSTR CEditExUI::GetNormalImage()
{
	return m_diNormal.sDrawString;
}

void CEditExUI::SetNormalImage(LPCTSTR pStrImage)
{
	if (m_diNormal.sDrawString == pStrImage && m_diNormal.pImageInfo != NULL) return;
	m_diNormal.Clear();
	m_diNormal.sDrawString = pStrImage;
	Invalidate();
}

LPCTSTR CEditExUI::GetHotImage()
{
	return m_diHot.sDrawString;
}

void CEditExUI::SetHotImage(LPCTSTR pStrImage)
{
	if (m_diHot.sDrawString == pStrImage && m_diHot.pImageInfo != NULL) return;
	m_diHot.Clear();
	m_diHot.sDrawString = pStrImage;
	Invalidate();
}

LPCTSTR CEditExUI::GetFocusedImage()
{
	return m_diFocused.sDrawString;
}

void CEditExUI::SetFocusedImage(LPCTSTR pStrImage)
{
	if (m_diFocused.sDrawString == pStrImage && m_diFocused.pImageInfo != NULL) return;
	m_diFocused.Clear();
	m_diFocused.sDrawString = pStrImage;
	Invalidate();
}

LPCTSTR CEditExUI::GetDisabledImage()
{
	return m_diDisabled.sDrawString;
}

void CEditExUI::SetDisabledImage(LPCTSTR pStrImage)
{
	if (m_diDisabled.sDrawString == pStrImage && m_diDisabled.pImageInfo != NULL) return;
	m_diDisabled.Clear();
	m_diDisabled.sDrawString = pStrImage;
	Invalidate();
}

void CEditExUI::SetNativeEditBkColor(DWORD dwBkColor)
{
	m_dwEditbkColor = dwBkColor;
}

DWORD CEditExUI::GetNativeEditBkColor() const
{
	return m_dwEditbkColor;
}

void CEditExUI::SetSel(long nStartChar, long nEndChar)
{
	if (m_pWindow != NULL) Edit_SetSel(*m_pWindow, nStartChar, nEndChar);
}

void CEditExUI::SetSelAll()
{
	SetSel(0, -1);
}

void CEditExUI::SetReplaceSel(LPCTSTR lpszReplace)
{
	if (m_pWindow != NULL) Edit_ReplaceSel(*m_pWindow, lpszReplace);
}

void CEditExUI::SetPos(RECT rc, bool bNeedInvalidate)
{
	CControlUI::SetPos(rc, bNeedInvalidate);
	if (m_pWindow != NULL) {
		RECT rcPos = m_pWindow->CalPos();
		if (::IsRectEmpty(&rcPos)) ::ShowWindow(m_pWindow->GetHWND(), SW_HIDE);
		else {
			::SetWindowPos(m_pWindow->GetHWND(), NULL, rcPos.left, rcPos.top, rcPos.right - rcPos.left,
				rcPos.bottom - rcPos.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
		}
	}
}

void CEditExUI::Move(SIZE szOffset, bool bNeedInvalidate)
{
	CControlUI::Move(szOffset, bNeedInvalidate);
	if (m_pWindow != NULL) {
		RECT rcPos = m_pWindow->CalPos();
		if (::IsRectEmpty(&rcPos)) ::ShowWindow(m_pWindow->GetHWND(), SW_HIDE);
		else {
			::SetWindowPos(m_pWindow->GetHWND(), NULL, rcPos.left, rcPos.top, rcPos.right - rcPos.left,
				rcPos.bottom - rcPos.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
		}
	}
}

void CEditExUI::SetVisible(bool bVisible)
{
	CControlUI::SetVisible(bVisible);
	if (!IsVisible() && m_pWindow != NULL) m_pManager->SetFocus(NULL);
}

void CEditExUI::SetInternVisible(bool bVisible)
{
	if (!IsVisible() && m_pWindow != NULL) m_pManager->SetFocus(NULL);
}

SIZE CEditExUI::EstimateSize(SIZE szAvailable)
{
	if (m_cxyFixed.cy == 0) return CDuiSize(m_cxyFixed.cx, m_pManager->GetFontInfo(GetFont())->tm.tmHeight + 8);
	return CControlUI::EstimateSize(szAvailable);
}

void CEditExUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName, _T("readonly")) == 0) SetReadOnly(_tcscmp(pstrValue, _T("true")) == 0);
	else if (_tcscmp(pstrName, _T("numberonly")) == 0) SetNumberOnly(_tcscmp(pstrValue, _T("true")) == 0);
	else if (_tcscmp(pstrName, _T("password")) == 0) SetPasswordMode(_tcscmp(pstrValue, _T("true")) == 0);
	else if (_tcscmp(pstrName, _T("autoselall")) == 0) SetAutoSelAll(_tcscmp(pstrValue, _T("true")) == 0);
	else if (_tcscmp(pstrName, _T("maxchar")) == 0) SetMaxChar(_ttoi(pstrValue));
	else if (_tcscmp(pstrName, _T("normalimage")) == 0) SetNormalImage(pstrValue);
	else if (_tcscmp(pstrName, _T("hotimage")) == 0) SetHotImage(pstrValue);
	else if (_tcscmp(pstrName, _T("focusedimage")) == 0) SetFocusedImage(pstrValue);
	else if (_tcscmp(pstrName, _T("disabledimage")) == 0) SetDisabledImage(pstrValue);
	else if (_tcscmp(pstrName, _T("nativebkcolor")) == 0) {
		if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		SetNativeEditBkColor(clrColor);
	}
	else CLabelUI::SetAttribute(pstrName, pstrValue);
}

void CEditExUI::PaintStatusImage(HDC hDC)
{
	if (IsFocused()) m_uButtonState |= UISTATE_FOCUSED;
	else m_uButtonState &= ~UISTATE_FOCUSED;
	if (!IsEnabled()) m_uButtonState |= UISTATE_DISABLED;
	else m_uButtonState &= ~UISTATE_DISABLED;

	if ((m_uButtonState & UISTATE_DISABLED) != 0) {
		if (DrawImage(hDC, m_diDisabled)) return;
	}
	else if ((m_uButtonState & UISTATE_FOCUSED) != 0) {
		if (DrawImage(hDC, m_diFocused)) return;
	}
	else if ((m_uButtonState & UISTATE_HOT) != 0) {
		if (DrawImage(hDC, m_diHot)) return;
	}

	if (DrawImage(hDC, m_diNormal)) return;
}

void CEditExUI::PaintText(HDC hDC)
{
	if (m_dwTextColor == 0) m_dwTextColor = m_pManager->GetDefaultFontColor();
	if (m_dwDisabledTextColor == 0) m_dwDisabledTextColor = m_pManager->GetDefaultDisabledColor();

	if (m_sText.IsEmpty()) return;

	CDuiString sText = m_sText;
	if (m_bPasswordMode) {
		sText.Empty();
		LPCTSTR p = m_sText.GetData();
		while (*p != _T('\0')) {
			sText += m_cPasswordChar;
			p = ::CharNext(p);
		}
	}

	RECT rc = m_rcItem;
	rc.left += m_rcTextPadding.left;
	rc.right -= m_rcTextPadding.right;
	rc.top += m_rcTextPadding.top;
	rc.bottom -= m_rcTextPadding.bottom;
	if (IsEnabled()) {
		CRenderEngine::DrawText(hDC, m_pManager, rc, sText, m_dwTextColor, \
			m_iFont, DT_SINGLELINE | m_uTextStyle);
	}
	else {
		CRenderEngine::DrawText(hDC, m_pManager, rc, sText, m_dwDisabledTextColor, \
			m_iFont, DT_SINGLELINE | m_uTextStyle);

	}
}
