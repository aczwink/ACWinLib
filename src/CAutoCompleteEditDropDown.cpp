//Class Header
#include "CAutoCompleteEditDropDown.h"
//Local
#include "CAutoCompleteEdit.h"
//Namespaces
using namespace SJCLibIntern;
using namespace SJCWinLib;
//Definitions
#define CAUTOCOMPLETEEDITDROPDOWN_CLASSNAME "CAutoCompleteEditDropDown"
#define STYLE_HEIGHT 150

//Message-callbacks
void CAutoCompleteEditDropDown::OnSize(WPARAM resizingType, uint32 newWidth, uint32 newHeight)
{
	CRect rcCtrl, rcClient;
	
	this->pParentCtrl->GetRect(rcCtrl);
	this->SetPos(CRect(rcCtrl.left, rcCtrl.bottom, rcCtrl.right, rcCtrl.bottom + STYLE_HEIGHT), SWP_NOACTIVATE);
	this->GetClientRect(rcClient);
	this->list.SetPos(rcClient, SWP_NOZORDER);
}

//Public Functions
void CAutoCompleteEditDropDown::Create(CAutoCompleteEdit *pParentCtrl)
{
	CBrush backgroundBrush;
	CCursor cursor;

	this->pParentCtrl = pParentCtrl;
	backgroundBrush.CreateSystemColorBrush(COLOR_WINDOW);
	cursor.LoadSystemCursor(IDC_IBEAM);
	//pParentCtrl->GetModule().RegisterWindowClass(&backgroundBrush, &cursor, NULL, NULL, CAUTOCOMPLETEEDITDROPDOWN_CLASSNAME);
	ASSERT(false);
	//CWindow::Create(CAUTOCOMPLETEEDITDROPDOWN_CLASSNAME, "", WS_POPUPWINDOW, 0, 0, 0, 0, 0, *pParentCtrl);
	this->list.Create(WS_VSCROLL | LBS_NOTIFY, 0, *this);
}