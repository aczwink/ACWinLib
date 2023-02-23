//Class Header
#include "CMultiSelectDropDownDropDown.h"
//Local
#include "CMultiSelectDropDown.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCWinLib;
//Definitions
#define CMULTISELECTDROPDOWN_CLASSNAME "CMultiSelectDropDown"

//CMultiSelectList Class
//Callbacks
void SJCLibIntern::CMultiSelectList::OnSelectionChange()
{
	((CMultiSelectDropDownDropDown *)this->GetParent())->pCtrl->Invalidate();
}

//Message-callbacks
void CMultiSelectDropDownDropDown::OnSize(WPARAM resizingType, uint32 newWidth, uint32 newHeight)
{
	CRect rcCtrl, rcClient;

	this->pCtrl->GetRect(rcCtrl);
	this->SetPos(CRect(rcCtrl.left, rcCtrl.bottom, rcCtrl.right, rcCtrl.bottom + this->CalculateHeight()), SWP_NOACTIVATE);
	this->GetClientRect(rcClient);
	this->list.SetPos(rcClient, SWP_NOZORDER);
}

//Private Functions
uint32 CMultiSelectDropDownDropDown::CalculateHeight()
{
	uint32 height = 0;
	CRect rc;
	SJCWinLib::CFont font;

	CPointer<CDeviceContext> pDC(this->GetDC());
	
	this->pCtrl->GetFont(font);
	pDC->SelectObject(font);
	
	repeat(this->list.GetItemCount(), i)
	{
		height += pDC->DrawTextA(this->list.GetItemText(i), rc, DT_CALCRECT) + this->list.style.padding;
	}

	height += 2*this->list.style.spacing;

	return height;
}

//Public Functions
void CMultiSelectDropDownDropDown::Create(CMultiSelectDropDown &refParentCtrl)
{
	this->pCtrl = &refParentCtrl;
	//CWindow::Create(CMULTISELECTDROPDOWN_CLASSNAME, "", WS_POPUPWINDOW, WS_EX_NOACTIVATE, 0, 0, 0, 0, refParentCtrl);
	ASSERT(false);
	this->list.Create(0, 0, 0, 0, 0, 0, *this);
}