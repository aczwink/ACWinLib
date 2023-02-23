//Class Header
#include "CCommonButtonClose.h"
//Local
#include "CDialog.h"
//Namespaces
using namespace SJCWinLib;

void CCommonButtonClose::OnClick()
{
	((CDialog *)this->GetParent())->End(IDCANCEL);
}