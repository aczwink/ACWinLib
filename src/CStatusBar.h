#pragma once
//Local
#include "CSystemWindow.h"
//Global
#include <CommCtrl.h>

namespace SJCWinLib
{
	class SJCWINLIB_API CStatusBar : public CSystemWindow
	{
	public:
		//Inline
		inline void AutoSize()
		{
			this->SendMessageA(WM_SIZE, 0, 0);
		}

		inline void Create(uint32 styleFlags, const CWindow &refParentWindow)
		{
			CSystemWindow::Create(STATUSCLASSNAME, styleFlags | SBARS_SIZEGRIP, 0, refParentWindow);
		}

		inline void SetParts(uint8 nParts, const int32 *pPartsRightEdges)
		{
			this->SendMessageA(SB_SETPARTS, nParts, (LPARAM)pPartsRightEdges);
		}

		inline void SetText(uint8 partIndex, const SJCLib::CString &refText, byte flags = 0)
		{
			this->SendMessageA(SB_SETTEXT, MAKE16(partIndex, flags), (LPARAM)refText.GetC_Str());
		}
	};
}