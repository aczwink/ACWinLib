//Class Header
#include "CommCtrl CRadioButton.h"
//Namespaces
using namespace SJCWinLibCommCtrl;

//Callbacks
void CRadioButton::OnClick()
{
}

void CRadioButton::OnCommand(WPARAM wParam)
{
	switch(HIWORD(wParam))
	{
	case BN_CLICKED:
		this->OnClick();
	}
}