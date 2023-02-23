#pragma once
//Local
#include "CSystemWindow.h"
//Global
#include <CommCtrl.h>

namespace SJCWinLib
{
	class SJCWINLIB_API CEdit : public CSystemWindow
	{
	private:
		//Message-callbacks
		virtual void OnChange();
		void OnCommand(WPARAM wParam);
	public:
		//Inline
		inline void Create(uint32 styleFlags, const CWindow &refParentWindow)
		{
			CSystemWindow::Create(WC_EDIT, styleFlags, WS_EX_CLIENTEDGE, refParentWindow);
		}

		inline void GetSelection(uint32 *pStart, uint32 *pEnd) const
		{
			((CEdit *)this)->SendMessageA(EM_GETSEL, (WPARAM)pStart, (LPARAM)pEnd);
		}

		inline void Select(uint32 start, uint32 end)
		{
			this->SendMessageA(EM_SETSEL, start, end);
		}

		inline void SetCueBanner(SJCLib::CWString text, bool showOnFocus = false)
		{
			this->SendMessageA(EM_SETCUEBANNER, showOnFocus, (LPARAM)text.GetC_Str());
		}
		
		inline void SetTextLimit(uint32 nChars)
		{
			this->SendMessageA(EM_LIMITTEXT, nChars, 0);
		}
	};
}