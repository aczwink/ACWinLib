//Class Header
#include "CEdit.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Message-callbacks
void CEdit::OnChange()
{
}

void CEdit::OnCommand(WPARAM wParam)
{
	switch(HIWORD(wParam))
	{
	case EN_CHANGE:
		this->OnChange();
	}
}