//Class Header
#include "CAutoCompleteEditMessageWindow.h"
//Local
#include "CAutoCompleteEdit.h"
#include "Messageformers.h"
//Namespaces
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Message-callbacks
void CAutoCompleteEditMessageWindow::OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y)
{
	POINT pt;
	CRect rcCtrl, rcDropDown;
	
	GetCursorPos(&pt);
	this->pCtrl->GetRect(rcCtrl);
	this->pCtrl->dropDownWindow.GetRect(rcDropDown);
	
	if(rcCtrl.PointInRect(pt))
	{
		this->pCtrl->dropDownWindow.ScreenToClient(pt);
		this->pCtrl->PostMessageA(MsgLButtonDown(0, pt.x, pt.y));
		this->pCtrl->PostMessageA(MsgLButtonUp(0, pt.x, pt.y));
	}
	else if(rcDropDown.PointInRect(pt) && this->pCtrl->dropDownWindow.list.GetCurrentSelection() != LB_ERR)
	{
		this->pCtrl->Complete();
	}
	else
	{
		this->pCtrl->GetParent()->Focus();
	}
}

void CAutoCompleteEditMessageWindow::OnMouseMove(uint16 keys)
{
	POINT pt;
	CRect rcCtrl, rcDropDown;
	
	GetCursorPos(&pt);
	this->pCtrl->GetRect(rcCtrl);
	this->pCtrl->dropDownWindow.GetRect(rcDropDown);
	
	if(rcCtrl.PointInRect(pt))
	{
		this->cursorIBeam.SetAsActive();
	}
	else if(rcDropDown.PointInRect(pt))
	{
		this->cursorArrow.SetAsActive();
		this->pCtrl->dropDownWindow.ScreenToClient(pt);
		this->pCtrl->dropDownWindow.list.Select(this->pCtrl->dropDownWindow.list.GetItemFromPoint((uint16)pt.x, (uint16)pt.y));
	}
	else
	{
		this->cursorArrow.SetAsActive();
	}
}

//Public Functions
void CAutoCompleteEditMessageWindow::Create(CAutoCompleteEdit *pCtrl)
{
	this->pCtrl = pCtrl;
	ASSERT(false);
	//CWindow::CreateMessageWindow(pCtrl->GetModule());
	this->cursorArrow.LoadSystemCursor(IDC_ARROW);
	this->cursorIBeam.LoadSystemCursor(IDC_IBEAM);
}