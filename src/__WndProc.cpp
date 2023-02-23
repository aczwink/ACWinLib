//Main Header
#include "__WndProc.h"
//Global
#include <CommCtrl.h>
//Local
#include "__CWindows.h"
#include "CControl.h"
#include "CDialog.h"
#include "CDrop.h"
#include "CFrame.h"
#include "CPopupWindow.h"
#include "CWindow.h"
#include "CommCtrl CStatic.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCWinLib;
//Definitions
#define WM_APP_END 0xBFFF
//Global Variables
bool SJCLibIntern::g_respondDefaultToCurrentMessage;
LRESULT SJCLibIntern::g_messageResult;

/*
Return value: true if message was processed, false if not.
*/
bool SJCLibIntern::ForwardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CMessageWindow *pMsgWnd;
	CWindow *pWnd;
	
	pMsgWnd = CWindows::IsAttached(hWnd);
	pWnd = (CWindow *)pMsgWnd;
	
	if(!pMsgWnd)
		return false;
	
	g_respondDefaultToCurrentMessage = false;

	//CMessageWindow and CWindow Callbacks	
	switch(message)
	{
	case WM_CREATE:
		{
			g_messageResult = pWnd->OnCreate()-1;
		}
		break;
	case WM_DESTROY:
		{
			pWnd->OnDestroy();
			CWindows::UnregisterWindow(pWnd->hWnd);
			g_messageResult = 0;
		}
		break;
	case WM_SIZE:
		{
			pWnd->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
			g_messageResult = 0;
		}
		break;
	case WM_SETFOCUS:
		{
			pWnd->OnFocus((CWindow *)CWindows::GetWindowPointer((HWND)wParam));
			g_messageResult = 0;
		}
		break;
	case WM_KILLFOCUS:
		{
			pWnd->OnLooseFocus((CWindow *)CWindows::GetWindowPointer((HWND)wParam));
			g_messageResult = 0;
		}
		break;
	case WM_PAINT:
		{
			pWnd->OnPaint();
			g_messageResult = 0;
		}
		break;
	case WM_CLOSE:
		{
			pWnd->OnClose();
			g_messageResult = 0;
		}
		break;
	case WM_ERASEBKGND:
		{
			CDeviceContext dc;
			dc.hDC = ((HDC)wParam);

			g_messageResult = pWnd->OnEraseBackground(dc);
		}
		break;
	case WM_SETCURSOR:
		{
			g_messageResult = pWnd->OnRequestCursor((CWindow *)CWindows::GetWindowPointer((HWND)wParam), LOWORD(lParam), HIWORD(lParam));
		}
		break;
	case WM_MOUSEACTIVATE:
		{
			g_messageResult = pWnd->OnMouseActivate((CPopupWindow *)CWindows::GetWindowPointer((HWND)wParam), LOW16(lParam), HIGH16(lParam));
		}
		break;
	case WM_SETFONT:
		{
			SJCWinLib::CFont font;
			
			font.hGDIObj = (HGDIOBJ)wParam;
			CWindows::GDIAddReferenceCount(font.hGDIObj);
			
			pWnd->OnSetFont(font);
			g_messageResult = 0;
		}
		break;
	case WM_NOTIFY:
		{
			NMHDR *pNmh;
			
			pNmh = (NMHDR *)lParam;
			
			if(pNmh->hwndFrom)
			{
				CSystemWindow *pControl = (CSystemWindow *)CWindows::IsAttached(pNmh->hwndFrom);
				if(pControl)
				{
					g_messageResult = pControl->OnNotify(pNmh);
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		break;
	case WM_KEYDOWN:
		{
			pWnd->OnKeyDown((uint16)wParam, uint16(lParam & 0xFFFF), byte((lParam & 0xFF0000) >> 16), (lParam & 0x1000000) != 0, (lParam & 0x40000000) != 0);
			g_messageResult = 0;
		}
		break;
	case WM_COMMAND:
		{
			if(!lParam)
			{
				if(HIGH16(wParam))
				{
					//Accelerator
					((CFrame *)pWnd)->OnAcceleratorCommand(LOW16(wParam));
					g_messageResult = 0;
				}
				else
				{
					//Menu
					((CPopupWindow *)pWnd)->OnMenuCommand(LOWORD(wParam));
					g_messageResult = 0;
				}
			}
			else
			{
				//Control
				CSystemWindow *pSysWnd;

				pSysWnd = dynamic_cast<CSystemWindow *>(CWindows::IsAttached((HWND)lParam));

				pSysWnd->OnCommand(wParam);
				g_messageResult = 0;
			}
		}
		break;
	case WM_TIMER:
		{
			pWnd->OnTimerExpires((uint32)wParam);
			g_messageResult = 0;
		}
		break;
	case WM_HSCROLL:
		{
			pWnd->OnHorizontalScroll(LOWORD(wParam));
			g_messageResult = 0;
		}
		break;
	case WM_VSCROLL:
		{
			pWnd->OnVerticalScroll(LOWORD(wParam));
			g_messageResult = 0;
		}
		break;
	case WM_MOUSEMOVE:
		{
			pWnd->OnMouseMove((uint16)wParam, LOWORD(lParam), HIWORD(lParam));
			g_messageResult = 0;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			pMsgWnd->OnLeftMouseButtonDown((uint16)wParam, LOWORD(lParam), HIWORD(lParam));
			g_messageResult = 0;
		}
		break;
	case WM_LBUTTONUP:
		{
			pWnd->OnLeftMouseButtonUp((uint16)wParam, LOWORD(lParam), HIWORD(lParam));
			g_messageResult = 0;
		}
		break;
	case WM_MOUSEWHEEL:
		{
			pWnd->OnMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam), GET_KEYSTATE_WPARAM(wParam));
			g_messageResult = 0;
		}
		break;
	case WM_DROPFILES:
		{
			CDrop dropObj;

			dropObj.hDrop = (HDROP)wParam;

			pWnd->OnDropFiles(dropObj);
			g_messageResult = 0;
		}
		break;
	default:
		//Check if this is a user message
		if((message >= WM_APP) && (message <= WM_APP_END))
		{
			pMsgWnd->OnUserMessage(message, wParam, lParam);
			g_messageResult = 0;
		}
		else
		{
			goto CPopupWindowCallbacks;
		}
	}
	
	return !g_respondDefaultToCurrentMessage; //processed the message if RespondDefault wasn't called
	
	//CPopupWindow Callbacks
CPopupWindowCallbacks:;
	CPopupWindow *pPopupWindow = dynamic_cast<CPopupWindow *>(pWnd);
	if(!pPopupWindow)
		goto CSystemWindowCallbacks;
	
	switch(message)
	{
	default:
		{
			return false;
		}
		break;
	}

	return !g_respondDefaultToCurrentMessage; //processed the message if RespondDefault wasn't called
	
	//CSystemWindow Callbacks
CSystemWindowCallbacks:;
	CSystemWindow *pSysWnd = dynamic_cast<CSystemWindow *>(pWnd);
	if(!pSysWnd)
		return false;
	
	switch(message)
	{
	default:
		return false;
	}

	return !g_respondDefaultToCurrentMessage; //processed the message if RespondDefault wasn't called
}

LRESULT CALLBACK SJCLibIntern::DialogProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CDialog *pDialog;
	
	if(message == WM_INITDIALOG)
	{
		pDialog = (CDialog *)lParam;
		CWindows::AttachWindow(pDialog, hWnd);
		pDialog->OnInit();
		
		return TRUE;
	}
	else
	{
		if(ForwardMessage(hWnd, message, wParam, lParam))
		{
			return TRUE;
		}
		/*pDialog = (CDialog *)CWindows::IsAttached(hWnd);
		
		if(pDialog)
		{
			switch(message)
			{
			//case WM_SIZE:
				//pDialog->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
				//break;
			case WM_ACTIVATE:
				if(wParam == WA_INACTIVE)
					CWindows::SetCurrentDialog(NULL);
				else
					CWindows::SetCurrentDialog(hWnd);
				break;
			case WM_HELP:
				{
					HELPINFO *pHI;
					
					pHI = (HELPINFO *)lParam;
					if(pHI->iContextType == HELPINFO_MENUITEM)
					{
					}
					else
					{
						pDialog->OnHelp(*(CWindow *)CWindows::GetWindowPointer((HWND)pHI->hItemHandle));
					}
				}
				break;
			case WM_COMMAND:
				if(lParam)
				{
					CControl *pControl = (CControl *)CWindows::IsAttached((HWND)lParam);
					if(pControl)
					{
						pControl->OnCommand(wParam);
						return TRUE;
					}
				}
				pDialog->OnCommand(wParam);
				break;
			case WM_CTLCOLORSTATIC:
				{
					SJCWinLibCommCtrl::CStatic *pCtrl = (SJCWinLibCommCtrl::CStatic *)CWindows::IsAttached((HWND)lParam);
					if(pCtrl)
					{
						char buffer[100];

						GetClassName((HWND)lParam, buffer, 100);
						if(buffer == (CString)WC_STATIC)
						{
							CDeviceContext dc;
							
							dc.hDC = (HDC)wParam;
							pCtrl->OnColor(dc);
							break;
						}
						return FALSE;
					}
				}
				break;
			default:
				return FALSE;
			}
			return TRUE;
		}*/
	}
	
	return FALSE;
}

LRESULT CALLBACK SJCLibIntern::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CMessageWindow *pWnd;
	
	if(message == WM_NCCREATE)
	{
		pWnd = (CMessageWindow *)((LPCREATESTRUCT)lParam)->lpCreateParams;
		if(pWnd)
			CWindows::AttachWindow(pWnd, hWnd);
	}
	else
	{
		if(ForwardMessage(hWnd, message, wParam, lParam))
		{
			return g_messageResult;
		}
			
			/*switch(message)
			{
			case WM_ACTIVATE:
				pWnd->OnActivate((byte)wParam, (CWindow *)CWindows::GetWindowPointer((HWND)lParam));
				return 0;
			case WM_CLOSE:
				pWnd->OnClose();
				return 0;
			case WM_NOTIFY:
				NMHDR *pNMI;
				
				pNMI = (NMHDR *)lParam;
				
				if(pNMI->hwndFrom)
				{
					CControl *pCtrl = (CControl *)CWindows::IsAttached(pNMI->hwndFrom);
					if(pCtrl)
					{
						return pCtrl->OnNotify(pNMI);
					}
				}

				break;
			case WM_GETDLGCODE:
				return ((CControl *)pWnd)->OnGetDialogCode((uint16)wParam);
			case WM_CHAR:
				pWnd->OnChar((uint16)wParam, uint16(lParam & 0xFFFF), byte((lParam & 0xFF0000) >> 16), (lParam & 0x1000000) != 0, (lParam & 0x20000000) != 0, (lParam & 0x40000000) != 0, (lParam & 0x80000000) != 0);
				return 0;
			case WM_COMMAND:
				if(lParam)
				{
					CControl *pCtrl = (CControl *)CWindows::IsAttached((HWND)lParam);
					if(pCtrl)
					{
						pCtrl->OnCommand(wParam);
						return 0;
					}
				}
				else
				{
					if(HIWORD(wParam)) //Accelerator
					{
						//pWnd->OnAcceleratorCommand(LOWORD(wParam));
						//return 0;
					}
				}
				pWnd->OnCommand(wParam);
				return 0;
			case WM_RBUTTONUP:
				pWnd->OnRightMouseButtonUp((uint16)wParam, LOWORD(lParam), HIWORD(lParam));
				return 0;
			}
			*/
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}