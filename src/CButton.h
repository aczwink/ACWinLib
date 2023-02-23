#pragma once
//Local
#include "CSystemWindow.h"
//Global
#include <CommCtrl.h>

namespace SJCWinLib
{
	class SJCWINLIB_API CButton : public CSystemWindow
	{
	private:
		//Message-callbacks
		virtual void OnClick();
		void OnCommand(WPARAM wParam);
	public:
		//Inline
		inline void Click()
		{
			this->SendMessageA(BM_CLICK, 0, 0);
		}

		inline void Create(SJCLib::CString text, uint32 styleFlags, const CWindow &refParentWindow)
		{
			CSystemWindow::Create(WC_BUTTON, styleFlags, 0, refParentWindow);
			this->SetText(text);
		}

		inline void SetDefault()
		{
			this->GetParent()->SendMessageA(DM_SETDEFID, GetWindowLongPtr(this->hWnd, GWLP_ID), 0);
		}
	};
}