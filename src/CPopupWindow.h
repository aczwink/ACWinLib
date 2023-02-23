#pragma once
//Local
#include "CWindow.h"
//Definitions
#undef MessageBox

namespace SJCWinLib
{
	class SJCWINLIB_API CPopupWindow : public CWindow
	{
		//Procedures
		friend bool SJCLibIntern::ForwardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		//Callbacks
		virtual void OnActivate(byte activationKind, CPopupWindow *pWnd);
		virtual void OnMenuCommand(uint16 menuItemId);
	public:
		//Inline
		inline CMenu GetMenu()
		{
			CMenu menu;
			
			menu.hMenu = ::GetMenu(this->hWnd);
			
			return menu;
		}
		
		inline int32 MessageBox(const SJCLib::CWString &refText, const SJCLib::CWString &refCaption, uint32 flags = MB_OK) const
		{
			return ::MessageBoxW(this->hWnd, refText.GetC_Str(), refCaption.GetC_Str(), flags);
		}

		inline void SetMenu(const CMenu &refMenu)
		{
			::SetMenu(this->hWnd, refMenu.hMenu);
		}
	};
}