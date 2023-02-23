#pragma once
//Local
#include "CSystemWindow.h"
//Global
#include <CommCtrl.h>

namespace SJCWinLibCommCtrl
{
	class SJCWINLIB_API CRadioButton : public SJCWinLib::CSystemWindow
	{
	private:
		//Callbacks
		virtual void OnClick();
		void OnCommand(WPARAM wParam);
	public:
		//Inline
		inline void Check(bool check = true)
		{
			this->SendMessageA(BM_SETCHECK, (check ? BST_CHECKED : BST_UNCHECKED), 0);
		}

		inline void Create(uint32 styleFlags, const CWindow &refParentWindow)
		{
			SJCWinLib::CSystemWindow::Create(WC_BUTTON, styleFlags | BS_RADIOBUTTON, 0, refParentWindow);
		}
		
		inline bool IsChecked() const
		{
			return ((CRadioButton *)this)->SendMessageA(BM_GETCHECK, 0, 0) & BST_CHECKED;
		}
	};
}