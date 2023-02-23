#pragma once
//Global
#include <Windows.h>
#include <CommCtrl.h>
//Local
#include "CSystemWindow.h"

namespace SJCWinLibCommCtrl
{
	class SJCWINLIB_API CTrackbar : public SJCWinLib::CSystemWindow
	{
	public:
		//Inline
		inline void Create(uint32 styleFlags, const CWindow &refParentWindow)
		{
			SJCWinLib::CSystemWindow::Create(TRACKBAR_CLASS, styleFlags, 0, refParentWindow);
			this->SendMessageA(TBM_SETRANGEMIN, TRUE, 0);
		}

		inline void SetRange(uint32 max, bool redraw = true)
		{
			this->SendMessageA(TBM_SETRANGEMAX, redraw, max);
		}
	};
}