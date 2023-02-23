//Class Header
#include "CSystemWindow.h"
//Local
#include "__CWindows.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Callbacks
void CSystemWindow::OnCommand(WPARAM wParam)
{
	CSystemWindow::RespondDefault();
}

LRESULT CSystemWindow::OnNotify(NMHDR *pNMI)
{
	CSystemWindow::RespondDefault();
	return 0;
}

//Public Functions
void CSystemWindow::Create(CString className, uint32 styleFlags, uint32 exStyleFlags, const CWindow &refParentWindow)
{
	HWND hWnd;
	
	hWnd = CreateWindowEx(exStyleFlags, className.GetC_Str(), NULL, WS_CHILD | WS_VISIBLE | styleFlags, 0, 0, 0, 0, refParentWindow.hWnd, (HMENU)CWindows::GetUniqueId(), (HINSTANCE)GetWindowLongPtr(refParentWindow.hWnd, GWLP_HINSTANCE), NULL);
	CWindows::AttachWindow(this, hWnd);
}

CString CSystemWindow::GetText() const
{
	CString result;
	char *pBuffer;
	uint32 length;

	length = (uint32)((CWindow *)this)->SendMessageA(WM_GETTEXTLENGTH, 0, 0);
	if(length)
	{
		pBuffer = (char *)malloc(length+1);
		((CWindow *)this)->SendMessageA(WM_GETTEXT, length+1, (LPARAM)pBuffer);
		result.Assign(pBuffer, length);
		free(pBuffer);

		return result;
	}
	return CString();
}