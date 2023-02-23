//Class Header
#include "CControl.h"
/*//Local
#include "__CWindows.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Message-callbacks
uint32 CControl::OnGetDialogCode(uint16 virtualKeyCode)
{
	CWindow::RespondDefault();
	return 0;
}

//Public Functions
void CControl::Create(CString className, CString windowName, uint32 styleFlags, uint32 exStyleFlags, uint32 x, uint32 y, uint32 width, uint32 height, const CWindow &refParentWindow)
{
	HWND hWnd;

	hWnd = CreateWindowEx(exStyleFlags, className.GetC_Str(), windowName.GetC_Str(), styleFlags, x, y, width, height, refParentWindow.hWnd, (HMENU)CWindows::GetUniqueId(), (HINSTANCE)GetWindowLongPtr(refParentWindow.hWnd, GWLP_HINSTANCE), NULL);
	CWindows::AttachWindow(this, hWnd);
}*/