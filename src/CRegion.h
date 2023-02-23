#pragma once
//Global
#include <Windows.h>
//Local
#include "Definitions.h"
#include "CRect.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CRegion
	{
		friend class CDeviceContext;
		friend class CWindow;
	private:
		//Variables
		HRGN hRgn;
	public:
		//Constructor
		inline CRegion()
		{
			this->hRgn = NULL;
		}

		//Destructor
		inline ~CRegion()
		{
			this->Delete();
		}

		//Functions
		inline int32 Combine(const CRegion &refOther, int32 combineMode)
		{
			return CombineRgn(this->hRgn, this->hRgn, refOther.hRgn, combineMode);
		}

		inline void CreateRectangular(uint32 left, uint32 top, uint32 right, uint32 bottom)
		{
			this->hRgn = CreateRectRgn(left, top, right, bottom);
		}

		inline void CreateRectangular(const CRect &refRect)
		{
			this->hRgn = CreateRectRgnIndirect(&refRect);
		}

		void Delete();

		inline int32 GetBox(CRect &refRect) const
		{
			return GetRgnBox(this->hRgn, &refRect);
		}

		inline bool IsNullRegion() const
		{
			return !this->hRgn;
		}
	};
}