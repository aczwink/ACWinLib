#pragma once
//Local
#include "CWindow.h"

namespace SJCWinLib
{
	/*
	A window class that features all functionalities provided by Windows.
	*/
	class SJCWINLIB_API CSystemWindow : public CWindow
	{
		//Classes
		friend class CDialog;
		//Procedures
		friend bool SJCLibIntern::ForwardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		//Callbacks
		virtual void OnCommand(WPARAM wParam);
		virtual LRESULT OnNotify(NMHDR *pNmh);
	public:
		//Functions
		void Create(SJCLib::CString className, uint32 styleFlags, uint32 exStyleFlags, const CWindow &refParentWindow);
		SJCLib::CString GetText() const;
		//Inline
		inline void Enable(bool enable = true)
		{
			EnableWindow(this->hWnd, enable);
		}
		
		inline void SetText(SJCLib::CString text)
		{
			this->SendMessage(WM_SETTEXT, 0, (LPARAM)text.GetC_Str());
		}
	};
}