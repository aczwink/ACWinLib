/*//Class Header
#include "CTrayIcon.h"
//Namespaces
using namespace SJCLIB_NAMESPACE_INTERN;
using namespace SJCLibString;
using namespace SJCLibWindows;
//Definitions
#define TRAY_MESSAGE WM_USER + 1

//CTrayWindow
void CTrayWindow::OnUserMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == TRAY_MESSAGE)
	{
		switch(lParam)
		{
		case WM_LBUTTONUP:
			this->trayIcon->OnClick();
			break;
		case WM_RBUTTONUP:
			this->trayIcon->OnRightClick();
			break;
		}
	}
}

//Constructor
CTrayIcon::CTrayIcon()
{
}

//Destructor
CTrayIcon::~CTrayIcon()
{
	this->Remove();
}

//Private Callbacks
void CTrayIcon::OnClick()
{
}

void CTrayIcon::OnRightClick()
{
}

//Public Functions
void CTrayIcon::Add()
{
	Shell_NotifyIcon(NIM_ADD, &this->nid);
}

void CTrayIcon::Init(CApplication *pApp)
{
	//this->trayWindow.Create(pApp->className, "", 0, 0, 0, 0, 0, pApp->pModule);
	this->trayWindow.trayIcon = this;
}

void CTrayIcon::Remove()
{
	Shell_NotifyIcon(NIM_DELETE, &this->nid);
}

void CTrayIcon::SetIcon(CIcon *pIcon, CString toolTip)
{
	memzero(&this->nid, sizeof(this->nid));

	this->nid.cbSize = sizeof(this->nid);
	this->nid.hIcon = pIcon->hIcon;
	this->nid.hWnd = this->trayWindow.hWnd;
	this->nid.uCallbackMessage = TRAY_MESSAGE;
	this->nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	this->nid.uID = 1;
	memcpy(this->nid.szTip, toolTip.c_str(), toolTip.GetLength());
}*/