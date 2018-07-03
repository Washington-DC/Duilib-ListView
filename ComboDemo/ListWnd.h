#pragma once

class CListEditWnd :public WindowImplBase
{
public:
	CListEditWnd(){};
	~CListEditWnd(){};

	virtual LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();

	virtual void InitWindow();

	virtual void Notify(TNotifyUI& msg);

	bool m_bShow = FALSE;

	CPaintManagerUI* GetManager()
	{
		return &m_PaintManager;
	}

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void SetItemList(std::vector<std::string> itemlist);

	void ChangeItems(std::string keyword);

	void SetOwner(CEditUI* pOwner)
	{
		pOwner_ = pOwner;
	}

private:
	std::vector<std::string> m_itemlist_;

	CEditUI* pOwner_ = nullptr;
};