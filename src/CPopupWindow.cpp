//Class Header
#include "CPopupWindow.h"
//Namespaces
using namespace SJCWinLib;

//Callbacks
void CPopupWindow::OnActivate(byte activationKind, CPopupWindow *pWnd)
{
	CPopupWindow::RespondDefault();
}

void CPopupWindow::OnMenuCommand(uint16 menuItemId)
{
	CPopupWindow::RespondDefault();
}