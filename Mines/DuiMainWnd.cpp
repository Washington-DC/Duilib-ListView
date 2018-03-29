#include "stdafx.h"
#include "DuiMainWnd.h"

CDuiMainWnd::CDuiMainWnd()
{
}


CDuiMainWnd::~CDuiMainWnd()
{
}



LPCTSTR CDuiMainWnd::GetWindowClassName() const
{
	return L"DuiMainWnd";
}

DuiLib::CDuiString CDuiMainWnd::GetSkinFile()
{
	return L"MainFrame.xml";
}

DuiLib::CDuiString CDuiMainWnd::GetSkinFolder()
{
	return L"Mines";
}

void CDuiMainWnd::InitWindow()
{
	
}

CControlUI * CDuiMainWnd::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

void CDuiMainWnd::Notify(TNotifyUI& msg)
{
	
	__super::Notify(msg);
}


