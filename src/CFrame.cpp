//Class Header
#include "CFrame.h"
//Local
#include "__CWindows.h"
//Namespaces
using namespace SJCWinLib;

//Callbacks
void CFrame::OnAcceleratorCommand(uint16 acceleratorCmdId)
{
	CFrame::RespondDefault();
}

void CFrame::OnDestroy()
{
	PostQuitMessage(EXIT_SUCCESS);
}

bool CFrame::OnEraseBackground(CDeviceContext &refDC)
{
	CRect rcClient;

	this->GetClientRect(rcClient);
	refDC.FillSolidRect(rcClient, CColor().GetSystemColor(COLOR_WINDOW));
	
	return true;
}

bool CFrame::OnRequestCursor(const CWindow *pContainingWindow, uint16 hitTest, uint16 msgId)
{
	if(hitTest == HTCLIENT)
	{
		CCursor cursor;
		
		cursor.LoadSystemCursor(IDC_ARROW);
		cursor.SetAsActive();
		
		return true;
	}

	CWindow::RespondDefault();
	return false;
}

//Public Functions
void CFrame::Create(SJCLib::CString title, uint16 x, uint16 y, uint16 width, uint16 height)
{
	//WndProc does attach
	CreateWindowEx(0, SJCWINLIB_WNDCLASS_DEFAULT, title.GetC_Str(), WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, GetModuleHandle(NULL), this);
}