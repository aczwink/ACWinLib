//Class Header
#include "CCheckBox.h"
//Global
#include <CommCtrl.h>
//Local
#include "CWindow.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Message-callbacks
void CCheckBox::OnClick()
{
}

void CCheckBox::OnCommand(WPARAM wParam)
{
	switch(HIWORD(wParam))
	{
	case BN_CLICKED:
		this->OnClick();
	}
}

//Public Functions
void CCheckBox::Check()
{
	this->SendMessageA(BM_SETCHECK, BST_CHECKED, 0);
}

void CCheckBox::Create(CString text, uint32 styleFlags, uint32 x, uint32 y, uint32 width, uint32 height, const CWindow &refParentWindow)
{
	if(!(styleFlags & BS_AUTO3STATE))
		styleFlags |= BS_AUTOCHECKBOX;

	//return CWindow::Create(WC_BUTTON, text, WS_VISIBLE | WS_CHILD | styleFlags, 0, x, y, width, height, refParentWindow);
	ASSERT(false);
}

bool CCheckBox::IsChecked()
{
	return (this->SendMessageA(BM_GETCHECK, 0, 0) & BST_CHECKED) != 0;
}