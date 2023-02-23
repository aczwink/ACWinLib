//Class Header
#include "CWindow.h"
//Global
#include <iostream>
//Local
#include "__CWindows.h"
#include "__WndProc.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCWinLib;
//Definitions
#define CTHIS ((CWindow *)this)

//Callbacks
void CWindow::OnChar(uint16 characterCode, uint16 repeatCount, byte scanCode, bool isExtendedKey, bool isAltKeyPressed, bool previousKeyState, bool transitionTable)
{
	CWindow::RespondDefault();
}

void CWindow::OnClose()
{
	CWindow::RespondDefault();
}

bool CWindow::OnCreate()
{
	CWindow::RespondDefault();
	return false;
}

void CWindow::OnDestroy()
{
	CWindow::RespondDefault();
}

void CWindow::OnDropFiles(const CDrop &refDrop)
{
	CWindow::RespondDefault();
}

bool CWindow::OnEraseBackground(CDeviceContext &refDC)
{
	CWindow::RespondDefault();
	return false;
}

void CWindow::OnFocus(CWindow *pPreviousFocusedWindow)
{
	CWindow::RespondDefault();
}

void CWindow::OnHelp(const CWindow &refWnd)
{
	CWindow::RespondDefault();
}

void CWindow::OnHorizontalScroll(uint16 scrollCode)
{
	CWindow::RespondDefault();
}

void CWindow::OnKeyDown(uint16 characterCode, uint16 repeatCount, byte scanCode, bool isExtendedKey, bool previousKeyState)
{
	CWindow::RespondDefault();
}

void CWindow::OnLeftMouseButtonUp(uint16 keys, uint16 x, uint16 y)
{
	CWindow::RespondDefault();
}

void CWindow::OnLooseFocus(CWindow *pUpcomingFocusedWindow)
{
	CWindow::RespondDefault();
}

uint8 CWindow::OnMouseActivate(CPopupWindow *pActivatedWnd, uint16 hitTest, uint16 mouseMessage)
{
	CWindow::RespondDefault();
	return 0;
}

void CWindow::OnMouseMove(uint16 keys, int16 x, int16 y)
{
	CWindow::RespondDefault();
}

void CWindow::OnMouseWheel(int16 zDelta, uint16 keys)
{
	CWindow::RespondDefault();
}

void CWindow::OnPaint()
{
	CWindow::RespondDefault();
}

bool CWindow::OnRequestCursor(const CWindow *pContainingWindow, uint16 hitTest, uint16 msgId)
{
	CWindow::RespondDefault();
	return false;
}

void CWindow::OnRightMouseButtonUp(uint16 keys, uint16 x, uint16 y)
{
	CWindow::RespondDefault();
}

void CWindow::OnSetFont(const SJCWinLib::CFont &refFont)
{
	CWindow::RespondDefault();
}

void CWindow::OnSize(WPARAM resizingType, uint32 newWidth, uint32 newHeight)
{
	CWindow::RespondDefault();
}

void CWindow::OnTimerExpires(uint32 timerId)
{
	CWindow::RespondDefault();
}

void CWindow::OnVerticalScroll(uint16 scrollCode)
{
	CWindow::RespondDefault();
}

//Public Functions
void CWindow::Create(uint32 styleFlags, uint32 exStyleFlags, const CWindow &refParentWindow)
{
	HWND hWnd;
	
	hWnd = CreateWindowEx(exStyleFlags, SJCWINLIB_WNDCLASS_DEFAULT, NULL, WS_CHILD | WS_VISIBLE | styleFlags, 0, 0, 0, 0, refParentWindow.hWnd, NULL, (HINSTANCE)GetWindowLongPtr(refParentWindow.hWnd, GWLP_HINSTANCE), NULL);
	CWindows::AttachWindow(this, hWnd);
}

CPointer<CDeviceContext> CWindow::GetDC()
{
	CPointer<CDeviceContext> dc(new CDeviceContext);
	
	dc->hDC = ::GetDC(this->hWnd);
	dc->releaseAction = CDeviceContext::RA_RELEASE;
	
	return dc;
}

CWindow *CWindow::GetParent()
{
	return (CWindow *)CWindows::GetWindowPointer(::GetParent(this->hWnd));
}

void CWindow::GetScrollInfo(SCROLLINFO &refSI, bool verticalBar) const
{
	refSI.cbSize = sizeof(refSI);
	
	if(verticalBar)
		::GetScrollInfo(this->hWnd, SB_VERT, &refSI);
	else
		::GetScrollInfo(this->hWnd, SB_HORZ , &refSI);
}

uint32 CWindow::GetScrollPos(bool verticalBar) const
{
	SCROLLINFO si = {0};
	
	si.fMask = SIF_POS;
	this->GetScrollInfo(si, verticalBar);
	
	return si.nPos;
}

uint32 CWindow::GetScrollTrackPos(bool verticalBar) const
{
	SCROLLINFO si = {0};

	si.fMask = SIF_TRACKPOS;

	this->GetScrollInfo(si, verticalBar);

	return si.nTrackPos;
}

void CWindow::ScreenToClient(CRect &refRect) const
{
	POINT p;

	p.x = refRect.left;
	p.y = refRect.top;

	::ScreenToClient(this->hWnd, &p);

	refRect.left = p.x;
	refRect.top = p.y;

	p.x = refRect.right;
	p.y = refRect.bottom;

	::ScreenToClient(this->hWnd, &p);

	refRect.right = p.x;
	refRect.bottom = p.y;
}

void CWindow::SetScrollInfo(const SCROLLINFO &refSI, bool verticalBar)
{
	if(verticalBar)
		::SetScrollInfo(this->hWnd, SB_VERT, &refSI, TRUE);
	else
		::SetScrollInfo(this->hWnd, SB_HORZ, &refSI, TRUE);
}

void CWindow::SetScrollPageSize(uint32 size, bool verticalBar)
{
	SCROLLINFO si = {0};

	si.cbSize = sizeof(si);
	si.fMask = SIF_PAGE;
	si.nPage = size;

	this->SetScrollInfo(si, verticalBar);
}

void CWindow::SetScrollPos(uint32 pos, bool verticalBar)
{
	if(verticalBar)
		::SetScrollPos(this->hWnd, SB_VERT, pos, TRUE);
	else
		::SetScrollPos(this->hWnd, SB_HORZ, pos, TRUE);
}

void CWindow::SetScrollRange(uint32 maxRange, bool verticalBar)
{
	if(verticalBar)
		::SetScrollRange(this->hWnd, SB_VERT, 0, maxRange, TRUE);
	else
		::SetScrollRange(this->hWnd, SB_HORZ, 0, maxRange, TRUE);
}

void CWindow::ShowScrollBar(bool show, bool verticalBar)
{
	if(verticalBar)
		::ShowScrollBar(this->hWnd, SB_VERT, show);
	else
		::ShowScrollBar(this->hWnd, SB_HORZ, show);
}

//Static Public Functions
CWindow *CWindow::GetConsoleWindow()
{
	return (CWindow *)CWindows::GetWindowPointer(::GetConsoleWindow());
}

CWindow *CWindow::GetDesktopWindow()
{
	return (CWindow *)CWindows::GetWindowPointer(::GetDesktopWindow());
}

CWindow *CWindow::GetFocusedWindow()
{
	return (CWindow *)CWindows::GetWindowPointer(::GetFocus());
}

/*
//Public Functions
CWindow *CWindow::FindWindow(CString className, CString windowName)
{
	return (CWindow *)CWindows::GetWindowPointer(::FindWindow(className.GetC_Str(), windowName.GetC_Str()));
}

CWindow *CWindow::GetLastActivePopup() const
{
	return (CWindow *)CWindows::GetWindowPointer(::GetLastActivePopup(this->hWnd));
}

CModule CWindow::GetModule() const
{
	CModule module((HMODULE)GetWindowLongPtr(this->hWnd, GWLP_HINSTANCE));
	
	return module;
}

bool CWindow::IsWindow() const
{
	if(this->hWnd)
		return ::IsWindow(this->hWnd) != false;
	return false;
}

LRESULT CWindow::SendMessage(UINT msg, WPARAM wParam, LPARAM lParam, UINT flags, UINT timeOut)
{
	return ::SendMessageTimeout(this->hWnd, msg, wParam, lParam, flags, timeOut, NULL);
}

//Include Class Header
#include "CWindow.h"
//SJCLib
#include <SJCLib.h>
//Local
#include "__CWindows.h"
#include "WndProc.h"
//Namespaces
using namespace SJCLibIntern;
using namespace SJCLib;
using namespace SJCLibString;
using namespace SJCWinLib;

//Callbacks
bool CWindow::OnEraseBackground(CDeviceContext *pDC)
{
	return CWindow::RespondDefault() != 0;
}

void CWindow::OnLeftMouseButtonUp(uint16 keys, uint16 x, uint16 y)
{
	CWindow::RespondDefault();
}

//Protected Functions
CControl *CWindow::GetControlPointer(uint16 id)
{
	return CWindows::GetControlPointer(id);
}

//Public Functions
void CWindow::Create(CWString className, CWString windowName, uint32 styleFlags, uint32 exStyleFlags, uint32 x, uint32 y, uint32 width, uint32 height, const CWindow &refParentWindow)
{
	HWND hWnd;

	hWnd = CreateWindowExW(exStyleFlags, className.GetC_Str(), windowName.GetC_Str(), styleFlags, x, y, width, height, refParentWindow.hWnd, NULL, (HINSTANCE)GetWindowLongPtr(refParentWindow.hWnd, GWLP_HINSTANCE), NULL);
	CWindows::AttachWindow(this, hWnd);
}
void CWindow::BringToForeground()
{
	SetForegroundWindow(this->hWnd);
}

SJCWinLibResult CWindow::Create(CWString className, CWString windowName, uint32 styleFlags, uint32 exStyleFlags, uint32 x, uint32 y, uint32 width, uint32 height, CWindow *pParentWindow)
{
	if(!pParentWindow)
		return SJCWINLIB_NOPARENTWND;
	
	this->Attach(CreateWindowExW(exStyleFlags, className.GetC_Str(), windowName.GetC_Str(), styleFlags, x, y, width, height, pParentWindow->hWnd, NULL, (HINSTANCE)GetWindowLongPtr(pParentWindow->hWnd, GWLP_HINSTANCE), NULL));

	return SJCWINLIB_OK;
}

void CWindow::Flash(bool invert)
{
	FlashWindow(this->hWnd, invert);
}

CWindow *CWindow::GetActiveWindow()
{
	return CWindow::GetWindowPointer(::GetActiveWindow());
}

CWindow *CWindow::GetForegroundWindow()
{
	return CWindow::GetWindowPointer(::GetForegroundWindow());
}

CWindow *CWindow::GetTopWindow()
{
	return CWindow::GetWindowPointer(::GetTopWindow(this->hWnd));
}

uint32 CWindow::GetScrollPageSize(bool verticalBar)
{
	SCROLLINFO si = {0};

	si.fMask = SIF_PAGE;

	this->GetScrollInfo(&si, verticalBar);

	return si.nPage;
}

uint32 CWindow::GetScrollRange(bool verticalBar)
{
	SCROLLINFO si = {0};

	si.fMask = SIF_RANGE;

	this->GetScrollInfo(&si, verticalBar);

	return si.nMax;
}

CWindow *CWindow::IsAttached()
{
	return CWindows::GetWindowPointer(this->hWnd);
}

int32 CWindow::MessageBox(SJCLibString::CWString text, SJCLibString::CWString caption, uint32 type)
{
	return MessageBoxW(this->hWnd, text.GetC_Str(), caption.GetC_Str(), type);
}

void CWindow::Move(RECT *rc, bool repaint)
{
	::MoveWindow(this->hWnd, rc->left, rc->top, rc->right, rc->bottom, (repaint) ? TRUE : FALSE);
}

LRESULT CWindow::SendMessageW(UINT message, WPARAM wParam, LPARAM lParam)
{
	return ::SendMessageW(this->hWnd, message, wParam, lParam);
}

void CWindow::SetStyle(DWORD style)
{
	SetWindowLong(this->hWnd, GWL_STYLE, style);
}

void CWindow::SetText(CWString text)
{
	this->SendMessageW(WM_SETTEXT, 0, (LPARAM)text.GetC_Str());
}
*/