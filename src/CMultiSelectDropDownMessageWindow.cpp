//Class Header
#include "CMultiSelectDropDownMessageWindow.h"
//Local
#include "CMultiSelectDropDown.h"
#include "CTheme.h"
//Namespaces
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Message-callbacks
void CMultiSelectDropDownMessageWindow::OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y)
{
	POINT pt;
	CRect rcDropDown;
	
	GetCursorPos(&pt);
	this->pCtrl->dropDownWindow.GetRect(rcDropDown);
	
	if(rcDropDown.PointInRect(pt))
	{
		rcDropDown.left = pt.x;
		rcDropDown.top = pt.y;
		this->pCtrl->dropDownWindow.ScreenToClient(rcDropDown);
		this->pCtrl->dropDownWindow.list.SendMessageA(WM_LBUTTONDOWN, 0, MAKELONG(rcDropDown.left, rcDropDown.top));
	}
	else
	{
		this->pCtrl->state = CBXS_NORMAL;
		this->pCtrl->dropDownWindow.Show(SW_HIDE);
		ReleaseCapture();
		this->pCtrl->Invalidate();
	}
}

//Public Functions
void CMultiSelectDropDownMessageWindow::Create(CMultiSelectDropDown &refCtrl)
{
	this->pCtrl = &refCtrl;
	ASSERT(false);
	//return CWindow::CreateMessageWindow(refCtrl.GetModule());
}