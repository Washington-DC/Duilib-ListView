#pragma once

#include "stdafx.h"
#include "ListItemUI.h"

class CListViewUI:public CListUI, public IDialogBuilderCallback
{
public:
	CListViewUI();
	~CListViewUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	void DoInit();//初始化
	int m_nActiveItem;//标识选中的item
	bool SetActiveItem(int iIndex, bool bTakeFocus);
	CControlUI* CreateControl(LPCTSTR pstrClass);
};