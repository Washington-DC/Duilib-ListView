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
	void DoInit();//��ʼ��
	int m_nActiveItem;//��ʶѡ�е�item
	bool SetActiveItem(int iIndex, bool bTakeFocus);
	CControlUI* CreateControl(LPCTSTR pstrClass);
};