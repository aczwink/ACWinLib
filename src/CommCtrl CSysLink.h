#pragma once
//Local
#include "CSystemWindow.h"

namespace SJCWinLibCommCtrl
{
	class SJCWINLIB_API CSysLink : public SJCWinLib::CSystemWindow
	{
	private:
		//Message-callbacks
		virtual void OnClick(SJCLib::CWString id, SJCLib::CWString url);
		LRESULT OnNotify(NMHDR *pNmh);
		virtual void OnReturn(SJCLib::CWString id, SJCLib::CWString url);
	public:
		//Functions
		void Create(SJCLib::CString text, uint32 styleFlags, uint32 x, uint32 y, uint32 width, uint32 height, const CWindow &refParentWindow);
	};
}