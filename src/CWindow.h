#pragma once
//Global
#include <Windows.h>
#include <shellapi.h>
#include <oleidl.h>
//Local
#include "CDeviceContext.h"
#include "CDrop.h"
#include "CFont.h"
#include "CMenu.h"
#include "CMessageWindow.h"
#include "CModule.h"
#include "CRect.h"
#include "CRegion.h"
#include "Definitions.h"

namespace SJCWinLib
{
	//Forward Declarations
	class CPopupWindow;

	class SJCWINLIB_API CWindow : public CMessageWindow
	{
		//Procedures
		friend bool SJCLibIntern::ForwardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		//Classes
		friend class CControl;
		friend class CDeviceContext;
		friend class CDialog;
		friend class CMenu;
		friend class CPaintDC;
		friend class CSystemWindow;
		friend class CTheme;
		//Controls
		//friend class CToolTip;
		//Dialogs
		friend class CCommonItemOpenDialog;
		friend class CCommonItemSaveDialog;
	private:
		//Callbacks
		virtual void OnChar(uint16 characterCode, uint16 repeatCount, byte scanCode, bool isExtendedKey, bool isAltKeyPressed, bool previousKeyState, bool transitionTable);
		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void OnDropFiles(const CDrop &refDrop);
		virtual bool OnEraseBackground(CDeviceContext &refDC);
		virtual void OnFocus(CWindow *pPreviousFocusedWindow);
		virtual void OnHelp(const CWindow &refWnd);
		virtual void OnHorizontalScroll(uint16 scrollCode);
		virtual void OnKeyDown(uint16 characterCode, uint16 repeatCount, byte scanCode, bool isExtendedKey, bool previousKeyState);
		virtual void OnLeftMouseButtonUp(uint16 keys, uint16 x, uint16 y);
		virtual void OnLooseFocus(CWindow *pUpcomingFocusedWindow);
		virtual uint8 OnMouseActivate(CPopupWindow *pActivatedWnd, uint16 hitTest, uint16 mouseMessage);
		virtual void OnMouseMove(uint16 keys, int16 x, int16 y);
		virtual void OnMouseWheel(int16 zDelta, uint16 keys);
		virtual void OnPaint();
		virtual bool OnRequestCursor(const CWindow *pContainingWindow, uint16 hitTest, uint16 msgId);
		virtual void OnRightMouseButtonUp(uint16 keys, uint16 x, uint16 y);
		virtual void OnSetFont(const CFont &refFont);
		virtual void OnSize(WPARAM resizingType, uint32 newWidth, uint32 newHeight);
		virtual void OnTimerExpires(uint32 timerId);
		virtual void OnVerticalScroll(uint16 scrollCode);
	protected:
		//Callbacks
		virtual void OnClose();
	public:
		//Functions
		void Create(uint32 styleFlags, uint32 exStyleFlags, const CWindow &refParentWindow);
		SJCLib::CPointer<CDeviceContext> GetDC();
		CWindow *GetParent();
		void GetScrollInfo(SCROLLINFO &refSI, bool verticalBar = true) const;
		uint32 GetScrollPos(bool verticalBar = true) const;
		uint32 GetScrollTrackPos(bool verticalBar = true) const;
		void ScreenToClient(CRect &refRect) const;
		void SetScrollInfo(const SCROLLINFO &refSI, bool verticalBar = true);
		void SetScrollPageSize(uint32 size, bool verticalBar = true);
		void SetScrollPos(uint32 pos, bool verticalBar = true);
		void SetScrollRange(uint32 maxRange, bool verticalBar = true);
		void ShowScrollBar(bool show = true, bool verticalBar = true);
		//Static Functions
		static CWindow *GetConsoleWindow();
		static CWindow *GetDesktopWindow();
		static CWindow *GetFocusedWindow();
		//Inline
		inline void ClientToScreen(POINT &refPoint)
		{
			::ClientToScreen(this->hWnd, &refPoint);
		}
		
		inline void CreateSolidCaret(uint16 width, uint16 height)
		{
			CreateCaret(this->hWnd, NULL, width, height);
		}

		inline void Destroy()
		{
			DestroyWindow(this->hWnd);
		}

		inline void DragAcceptFiles(bool accept)
		{
			::DragAcceptFiles(this->hWnd, accept);
		}

		inline void Focus()
		{
			SetFocus(this->hWnd);
		}
		
		inline void GetClientRect(CRect &refRect) const
		{
			::GetClientRect(this->hWnd, &refRect);
		}

		inline void GetFont(CFont &refFont) const
		{
			refFont.hGDIObj = (HFONT)((CWindow *)this)->SendMessageA(WM_GETFONT, 0, 0);
		}

		inline void GetRect(CRect &refRect) const
		{
			::GetWindowRect(this->hWnd, &refRect);
		}

		inline uint32 GetScrollRange(bool verticalBar = true) const
		{
			SCROLLINFO si = {0};
			
			si.fMask = SIF_RANGE;
			this->GetScrollInfo(si, verticalBar);
			
			return si.nMax;
		}

		inline uint32 GetStyleFlags() const
		{
			return (uint32)GetWindowLongPtr(this->hWnd, GWL_STYLE);
		}

		inline void Invalidate(bool erase = true)
		{
			::InvalidateRect(this->hWnd, NULL, erase);
		}

		inline void InvalidateRect(const CRect &refRect, bool erase = true)
		{
			::InvalidateRect(this->hWnd, &refRect, erase);
		}

		inline void KillTimer(uint32 timerId)
		{
			::KillTimer(this->hWnd, timerId);
		}
		
		inline void Move(int32 x, int32 y, int32 width, int32 height, bool repaint = true)
		{
			::MoveWindow(this->hWnd, x, y, width, height, repaint);
		}

		inline bool PostMessage(UINT message, WPARAM wParam, LPARAM lParam)
		{
			return ::PostMessage(this->hWnd, message, wParam, lParam) != FALSE;
		}

		inline void RegisterDragDrop(IDropTarget *pTarget)
		{
			::RegisterDragDrop(this->hWnd, pTarget);
		}

		inline void RevokeDragDrop()
		{
			::RevokeDragDrop(this->hWnd);
		}
		
		inline void ScreenToClient(POINT &refPoint) const
		{
			::ScreenToClient(this->hWnd, &refPoint);
		}

		inline void Scroll(int32 dx, int32 dy, const CRect *prcScroll, const CRect *prcClip, uint32 flags = SW_INVALIDATE)
		{
			ScrollWindowEx(this->hWnd, dx, dy, prcScroll, prcClip, NULL, NULL, flags);
		}
		
		inline LRESULT SendMessageA(UINT message, WPARAM wParam, LPARAM lParam)
		{
			return ::SendMessageA(this->hWnd, message, wParam, lParam);
		}

		inline LRESULT SendMessageW(UINT message, WPARAM wParam, LPARAM lParam)
		{
			return ::SendMessageW(this->hWnd, message, wParam, lParam);
		}

		inline void SetFont(const CFont &refFont, bool redraw = true)
		{
			this->SendMessageA(WM_SETFONT, (WPARAM)refFont.hGDIObj, redraw);
		}
		
		inline void SetPos(const CRect &refRect, uint32 flags = 0)
		{
			SetWindowPos(this->hWnd, HWND_TOP, refRect.left, refRect.top, refRect.GetWidth(), refRect.GetHeight(), flags);
		}

		inline void SetTimer(uint32 timerId, uint32 timeOutInMs)
		{
			::SetTimer(this->hWnd, timerId, timeOutInMs, NULL);
		}

		inline void Show(int32 nCmdShow)
		{
			ShowWindow(this->hWnd, nCmdShow);
		}

		inline void ShowCaret(bool show = true)
		{
			if(show)
				::ShowCaret(this->hWnd);
			else
				HideCaret(this->hWnd);
		}

		inline void Update()
		{
			UpdateWindow(this->hWnd);
		}
	};
}

	/*public:
		//Functions
		static CWindow *FindWindow(SJCLib::CString className, SJCLib::CString windowName);
		CWindow *GetLastActivePopup() const;
		CModule GetModule() const;

		inline int32 GetUpdateRegion(CRegion &refRegion, bool erase)
		{
			return GetUpdateRgn(this->hWnd, refRegion.hRgn, erase);
		}
		LRESULT SendMessage(UINT msg, WPARAM wParam, LPARAM lParam, UINT flags, UINT timeOut);
		*/

/*
//SJCLib
#include <SJCLib.h>
//Local
#include "CMenu.h"
#include "CModule.h"
#include "CRect.h"
#include "WndProc.h"
//GDI
#include "CFont.h"

//Forward Declarations
namespace SJCLibIntern
{
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}

namespace SJCWinLib
{
	//Forward Declarations
	class CControl;

	class SJCLIB_API CWindow
	{
		friend class CApplication;
		friend class CControl;
		friend class CDeviceContext;
		friend class CMenu;
		friend class CPaintDC;
		friend class CTheme;
	protected:
		//Vars
		HWND hWnd;
		//Functions
		static CControl *GetControlPointer(uint16 id);
		//Callbacks
		virtual bool OnEraseBackground(CDeviceContext *pDC);
		virtual void OnLeftMouseButtonUp(uint16 keys, uint16 x, uint16 y);
	public:
		//Functions
		void Create(SJCLib::CString className, SJCLib::CString windowName, uint32 styleFlags, uint32 exStyleFlags, uint32 x, uint32 y, uint32 width, uint32 height, const CWindow &refParentWindow);
		void Create(SJCLib::CWString className, SJCLib::CWString windowName, uint32 styleFlags, uint32 exStyleFlags, uint32 x, uint32 y, uint32 width, uint32 height, const CWindow &refParentWindow);

		inline void Create(SJCLib::CString className, SJCLib::CString windowName, uint32 styleFlags, uint32 exStyleFlags, const CRect &refRect, const CWindow &refParentWindow)
		{
			this->Create(className, windowName, styleFlags, exStyleFlags, refRect.left, refRect.top, refRect.GetWidth(), refRect.GetHeight(), refParentWindow);
		}
		void Attach(HWND hWnd);
		void BringToForeground();
		SJCWinLibResult Create(SJCLibString::CWString className, SJCLibString::CWString windowName, uint32 styleFlags, uint32 exStyleFlags, uint32 x, uint32 y, uint32 width, uint32 height, CWindow *pParentWindow);
		void Flash(bool invert);
		static CWindow *GetActiveWindow();
		static CWindow *GetForegroundWindow();
		CWindow *GetTopWindow();
		uint32 GetScrollPageSize(bool verticalBar = true);
		uint32 GetScrollRange(bool verticalBar = true);
		CWindow *IsAttached();
		int32 MessageBox(SJCLibString::CWString text, SJCLibString::CWString caption, uint32 type = MB_OK);
		void Move(RECT *rc, bool repaint = true);
		LRESULT SendMessageW(UINT message, WPARAM wParam, LPARAM lParam);
		void SetStyle(DWORD style);
		void SetText(SJCLibString::CWString text);
	};
}*/