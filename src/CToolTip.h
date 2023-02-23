#pragma once
//Global
#include <Windows.h>
#include <CommCtrl.h>
//Local
#include "CSystemWindow.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CToolTip : public CSystemWindow
	{
	private:
		//Variables
		const CWindow *pParentWindow;
	public:
		//Functions
		void AddTool(SJCLib::CString text, uint32 id, const CRect &refParentArea);
		void Create(const CWindow *pParentWindow);
		void UpdateTipText(uint32 id, SJCLib::CString text);
		void UpdateToolRect(uint32 id, const CRect &refNewArea);
		//Inline
		inline void SetMaxTipWidth(int16 width)
		{
			this->SendMessageA(TTM_SETMAXTIPWIDTH, 0, width);
		}
	};
}