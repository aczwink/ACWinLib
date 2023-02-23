//SJCLib
#include <SJCLib.h>
//Local
#include "CMessageWindow.h"
#include "CWindow.h"
//Definitions
#define SJCWINLIB_WNDCLASS_DEFAULT "SJCWinLibDefaultWndClass"

namespace SJCLibIntern
{
	class CAccessibleWindow : public SJCWinLib::CMessageWindow
	{
		friend class CWindows;
	};

	struct SWindowListElement
	{
		SJCWinLib::CMessageWindow *pWnd;
		bool isSystemWnd;
	};

	class CWindows
	{
	private:
		//Variables
		static SJCLib::CMap<HANDLE, uint32> m_GDIReferenceCount;
		static HWND m_hCurrentDlg;
		static uint16 m_IdCounter;
		static bool m_IsWinSockInitiated;
		static SJCLib::CMap<HWND, SWindowListElement> m_WindowList;
		static SJCLib::CMap<SJCLib::CString, HINSTANCE> m_WindowClassesList;
	public:
		//Functions
		static void AttachWindow(SJCWinLib::CMessageWindow *pWnd, HWND hWnd, bool isSystemWindow = false);
		static void GDIAddReferenceCount(HANDLE h);
		static uint32 GDIReleaseReferenceCount(HANDLE h);
		static HWND GetCurrentDialog();
		static uint16 GetUniqueId();
		static SJCWinLib::CMessageWindow *GetWindowPointer(HWND hWnd);
		static bool InitWinSock();
		static SJCWinLib::CMessageWindow *IsAttached(HWND hWnd);
		static void RegisterWindow(HWND hWnd, SJCWinLib::CMessageWindow *pWnd, bool isSystemWindow = false);
		static void RegisterWindowClass(HINSTANCE hInstance, SJCLib::CString className);
		static void Release();
		static inline void SetCurrentDialog(HWND hDialog)
		{
			m_hCurrentDlg = hDialog;
		}
		static void UnregisterWindow(HWND hWnd);
		static void UnregisterWindowClass(SJCLib::CString className);
	};
}

/*#pragma once
//Global
#include <Windows.h>
//Local
#include "CControl.h"
#include "CWindow.h"

//Forward Declarations
namespace SJCWinLib
{
	class CWindow;
	class CControl;
}

namespace SJCLibIntern
{
	class CWindows
	{
	private:
		//Variables
		static SJCLib::CMap<uint16, SJCWinLib::CControl *> m_ControlList;
	public:
		//Functions
		static SJCWinLib::CControl *GetControlPointer(uint16 controlId);
		static void RegisterControl(uint16 ctrlId, SJCWinLib::CControl *pCtrl);
	};
}*/