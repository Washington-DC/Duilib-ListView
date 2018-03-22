#pragma once
#include "stdafx.h"

class CListItemUI:public CListContainerElementUI
{
public:
	CListItemUI();
	~CListItemUI();

	LPCTSTR GetClass() const;
	void DoEvent(TEventUI& event);

	bool m_bActive;//��ʶ�Ƿ�ѡ��
	void SetActive(bool bActive = true);//�Ƿ�ѡ��

	//����Ϊitem�е����ݣ������Լ���Ҫ
	LPCTSTR m_strItemName;
	LPCTSTR m_strItemContent;
	LPCTSTR m_strItemInfo;
	void SetItemName(LPCTSTR strName);
	void SetItemContent(LPCTSTR strContent);
	void SetItemInfo(LPCTSTR strInfo);
};

