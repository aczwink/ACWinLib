//Class Header
#include "CButton.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Message-callbacks
void CButton::OnClick()
{
}

void CButton::OnCommand(WPARAM wParam)
{
	switch(HIWORD(wParam))
	{
	case BN_CLICKED:
		this->OnClick();
	}
}