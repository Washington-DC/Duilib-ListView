#pragma once
#include "stdafx.h"

class CListItemUI:public CListContainerElementUI
{
public:
	CListItemUI();
	~CListItemUI();

	LPCTSTR GetClass() const;
	void DoEvent(TEventUI& event);

	bool m_bActive;//标识是否被选中
	void SetActive(bool bActive = true);//是否选中

	//以下为item中的内容，根据自己需要
	LPCTSTR m_strItemName;
	LPCTSTR m_strItemContent;
	LPCTSTR m_strItemInfo;
	void SetItemName(LPCTSTR strName);
	void SetItemContent(LPCTSTR strContent);
	void SetItemInfo(LPCTSTR strInfo);
};

