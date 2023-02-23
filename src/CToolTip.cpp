/*//Class Header
#include "CToolTip.h"
//Global
#include <Windows.h>
#include <CommCtrl.h>
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Public Functions
void CToolTip::AddTool(CString text, uint32 id, const CRect &refParentArea)
{
	TOOLINFO ti;
	
	MemZero(&ti, sizeof(ti));
	ti.cbSize = sizeof(ti);
	ti.hwnd = this->pParentWindow->hWnd;
	ti.hinst = this->pParentWindow->GetModule().hModule;
	ti.lpszText = (LPSTR)text.GetC_Str();
	ti.uFlags = TTF_SUBCLASS;
	ti.uId = id;
	ti.rect.left = refParentArea.left;
	ti.rect.top = refParentArea.top;
	ti.rect.right = refParentArea.right;
	ti.rect.bottom = refParentArea.bottom;
	
	this->SendMessageA(TTM_ADDTOOL, 0, (LPARAM)&ti);
}

void CToolTip::Create(const CWindow *pParentWindow)
{
	this->pParentWindow = pParentWindow;

	CWindow::Create(TOOLTIPS_CLASS, CString(), WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX, WS_EX_TOPMOST, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, *pParentWindow);
	SetWindowPos(this->hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CToolTip::UpdateTipText(uint32 id, CString text)
{
	TOOLINFO ti;

	MemZero(&ti, sizeof(ti));
	ti.cbSize = sizeof(ti);
	ti.hwnd = this->pParentWindow->hWnd;
	ti.hinst = this->pParentWindow->GetModule().hModule;
	ti.uId = id;
	ti.lpszText = (LPSTR)text.GetC_Str();
	
	this->SendMessageA(TTM_UPDATETIPTEXT, 0, (LPARAM)&ti);
}

void CToolTip::UpdateToolRect(uint32 id, const CRect &refNewArea)
{
	TOOLINFO ti;

	MemZero(&ti, sizeof(ti));
	ti.cbSize = sizeof(ti);
	ti.hwnd = this->pParentWindow->hWnd;
	ti.uId = id;
	ti.rect.left = refNewArea.left;
	ti.rect.top = refNewArea.top;
	ti.rect.right = refNewArea.right;
	ti.rect.bottom = refNewArea.bottom;

	this->SendMessageA(TTM_NEWTOOLRECT, 0, (LPARAM)&ti);
}*/