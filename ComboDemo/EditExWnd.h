#pragma once

class CEditExUI;
class CEditExWnd : public CWindowWnd
{
public:
	CEditExWnd();

	void Init(CEditExUI* pOwner);
	RECT CalPos();

	LPCTSTR GetWindowClassName() const;
	LPCTSTR GetSuperClassName() const;
	void OnFinalMessage(HWND hWnd);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEditChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
	enum {
		DEFAULT_TIMERID = 20,
	};

	CEditExUI* m_pOwner;
	HBRUSH m_hBkBrush;
	bool m_bInit;
	bool m_bDrawCaret;
};
