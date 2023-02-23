//Class Header
#include "__CWindows.h"
//Local
#include "CModule.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Member Variables
CMap<HANDLE, uint32> CWindows::m_GDIReferenceCount;
HWND CWindows::m_hCurrentDlg = NULL;
uint16 CWindows::m_IdCounter = 0;
bool CWindows::m_IsWinSockInitiated = false;
CMap<HWND, SWindowListElement> CWindows::m_WindowList;
CMap<CString, HINSTANCE> CWindows::m_WindowClassesList;

//Public Functions
void CWindows::AttachWindow(CMessageWindow *pWnd, HWND hWnd, bool isSystemWindow)
{
	CAccessibleWindow *pWndAccessible, *pCurrentWnd;

	pWndAccessible = (CAccessibleWindow *)pWnd;

	if(pWndAccessible->hWnd == hWnd)
		return;
	if(pWndAccessible->hWnd)
		UnregisterWindow(pWndAccessible->hWnd);
	
	pCurrentWnd = (CAccessibleWindow *)IsAttached(hWnd);
	
	if(pCurrentWnd)
		UnregisterWindow(pCurrentWnd->hWnd);

	pWndAccessible->hWnd = hWnd;
	RegisterWindow(hWnd, pWnd, isSystemWindow);
}

void CWindows::GDIAddReferenceCount(HANDLE h)
{
	m_GDIReferenceCount[h]++;
}

uint32 CWindows::GDIReleaseReferenceCount(HANDLE h)
{
	uint32 count;

	count = --m_GDIReferenceCount[h];
	if(!count)
		m_GDIReferenceCount.Delete(h);

	return count;
}

HWND CWindows::GetCurrentDialog()
{
	return m_hCurrentDlg;
}

uint16 CWindows::GetUniqueId()
{
	return ++m_IdCounter;
}

CMessageWindow *CWindows::GetWindowPointer(HWND hWnd)
{
	CMessageWindow *pWnd;

	if(hWnd)
	{
		pWnd = IsAttached(hWnd);
		
		if(!pWnd)
		{
			pWnd = new CWindow;
			AttachWindow(pWnd, hWnd, true);
		}
		
		return pWnd;
	}

	return NULL;
}

bool CWindows::InitWinSock()
{
	if(!m_IsWinSockInitiated)
	{
		WSADATA data;
		
		m_IsWinSockInitiated = true;

		return WSAStartup(MAKEWORD(2, 2), &data) == 0;
	}
	
	return true;
}

CMessageWindow *CWindows::IsAttached(HWND hWnd)
{
	CMap<HWND, SWindowListElement>::Iterator it;
	
	it = m_WindowList.Find(hWnd);
	if(it.IsValid())
		return it.GetValue().pWnd;
	
	return NULL;
}

void CWindows::RegisterWindow(HWND hWnd, CMessageWindow *pWnd, bool isSystemWindow)
{
	SWindowListElement element;

	element.isSystemWnd = isSystemWindow;
	element.pWnd = pWnd;

	m_WindowList[hWnd] = element;
}

void CWindows::RegisterWindowClass(HINSTANCE hInstance, CString className)
{
	m_WindowClassesList[className] = hInstance;
}

void CWindows::Release()
{
	if(m_IsWinSockInitiated)
		WSACleanup();
	
	while(m_WindowList.GetNoOfElements())
	{
		UnregisterWindow(m_WindowList.Begin().GetKey());
	}
	/*while(m_WindowClassesList.GetNoOfElements())
	{
		CMapIterator<CString, HINSTANCE> it = m_WindowClassesList.Begin();
		CModule module(it.GetValue());
		
		module.UnregisterWindowClass(it.GetKey());
	}*/
	m_WindowClassesList.Release();
	m_WindowList.Release();
}

void CWindows::UnregisterWindow(HWND hWnd)
{
	CMap<HWND, SWindowListElement>::Iterator it;

	it = m_WindowList.Find(hWnd);

	if(it.IsValid())
	{
		if(it.GetValue().isSystemWnd)
		{
			it.GetValue().isSystemWnd = false; //because ~CWindow will call UnregisterWindow again! But call delete only once
			delete it.GetValue().pWnd;
		}
		m_WindowList.Delete(hWnd);
	}
}

void CWindows::UnregisterWindowClass(CString className)
{
	m_WindowClassesList.Delete(className);
}

/*
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCLibString;
using namespace SJCWinLib;

//Member Variables
bool CWindows::m_WinSockInitiated = false;
CMap<uint16, CControl *> CWindows::m_ControlList;

//Public Functions
CControl *CWindows::GetControlPointer(uint16 controlId)
{
	CMapIterator<uint16, CControl *> it;

	it = m_ControlList.Find(controlId);

	if(!it.IsValid())
		return NULL;
	return it.GetValue();
}

void CWindows::RegisterControl(uint16 ctrlId, CControl *pCtrl)
{
	m_ControlList[ctrlId] = pCtrl;
}
*/