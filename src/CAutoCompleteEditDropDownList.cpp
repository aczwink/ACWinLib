/*//Class Header
#include "CAutoCompleteEditDropDownList.h"
//Local
#include "CAutoCompleteEdit.h"
//Namespaces
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Callbacks
void CAutoCompleteEditDropDownList::OnChangeSelection()
{
	CAutoCompleteEditDropDown *pControl = (CAutoCompleteEditDropDown *)this->GetParent();

	pControl->pParentCtrl->Focus();
	pControl->pParentCtrl->Complete();
}*/