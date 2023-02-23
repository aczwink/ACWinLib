#pragma once
//Local
#include "CSystemWindow.h"
//Global
#include <CommCtrl.h>

namespace SJCWinLibCommCtrl
{
	class SJCWINLIB_API CProgressBar : public SJCWinLib::CSystemWindow
	{
	public:
		//Inline
		inline void Advance(int32 delta)
		{
			this->SendMessageA(PBM_DELTAPOS, delta, 0);
		}

		inline void Create(uint32 styleFlags, const CWindow &refParentWindow)
		{
			SJCWinLib::CSystemWindow::Create(PROGRESS_CLASS, styleFlags, 0, refParentWindow);
		}

		inline uint32 GetRangeMax() const
		{
			return (uint32)((CProgressBar *)this)->SendMessageA(PBM_GETRANGE, FALSE, NULL);
		}
		
		inline uint32 GetRangeMin() const
		{
			return (uint32)((CProgressBar *)this)->SendMessageA(PBM_GETRANGE, TRUE, NULL);
		}
		
		inline uint32 GetPos() const
		{
			return (uint32)((CProgressBar *)this)->SendMessageA(PBM_GETPOS, 0, 0);
		}
		
		inline void PostAdvance(int32 delta)
		{
			this->PostMessageA(PBM_DELTAPOS, delta, 0);
		}
		
		inline void SetRange(uint32 min, uint32 max)
		{
			this->SendMessageA(PBM_SETRANGE32, min, max);
		}
	};
}