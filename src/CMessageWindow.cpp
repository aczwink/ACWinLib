//Class Header
#include "CMessageWindow.h"
//Local
#include "__CWindows.h"
#include "__WndProc.h"
//Namespaces
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Constructor
CMessageWindow::CMessageWindow()
{
	this->hWnd = NULL;
}

//Destructor
CMessageWindow::~CMessageWindow()
{
	CWindows::UnregisterWindow(this->hWnd);
	this->hWnd = NULL;
}

//Callbacks
void CMessageWindow::OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y)
{
	CMessageWindow::RespondDefault();
}

void CMessageWindow::OnUserMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	CWindow::RespondDefault();
}

//Protected Functions
void CMessageWindow::RespondDefault()
{
	g_respondDefaultToCurrentMessage = true;
}

//Public Functions
void CMessageWindow::Create()
{
	HWND hWnd;
	
	hWnd = CreateWindow(SJCWINLIB_WNDCLASS_DEFAULT, "", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, GetModuleHandle(NULL), NULL);
	CWindows::AttachWindow(this, hWnd);
}

const CMessageWindow *CMessageWindow::SetCapture() const
{
	return CWindows::GetWindowPointer(::SetCapture(this->hWnd));
}