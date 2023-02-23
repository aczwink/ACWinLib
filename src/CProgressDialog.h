#pragma once
//Local
#include "CDialog.h"
#include "CommCtrl CProgressBar.h"
#include "CStatic.h"
//Definitions
#define CPROGRESSDIALOG_WM_ADVANCE WM_APP

namespace SJCWinLib
{
	class SJCWINLIB_API CProgressDialog : public CDialog
	{
	private:
		//Variables
		CFont font;
		SJCWinLibCommCtrl::CProgressBar progressBar;
		CStatic percentage;
		//Callbacks
		void OnInit();
		void OnUserMessage(UINT message, WPARAM wParam, LPARAM lParam);
	public:
		//Functions
		void Create(const SJCLib::CString &refCaption, const CPopupWindow &refParentWindow);

		//Inline
		inline void Advance(int32 delta)
		{
			this->PostMessageA(CPROGRESSDIALOG_WM_ADVANCE, 0, delta);
		}
	};
}