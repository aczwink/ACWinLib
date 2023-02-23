#pragma once
//Local
#include "CGDIObject.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CBitmap : public CGDIObject
	{
	public:
		//Inline
		inline int32 GetInfo(BITMAP &refBmp) const
		{
			return GetObject(this->hGDIObj, sizeof(BITMAP), &refBmp);
		}
	};
}

/*#pragma once
//global
#include <Windows.h>
//local
#include "SJCLib.h"
#include "CGDIObject.h"

namespace SJCWinLib
{
	class CBitmap : public CGDIObject
	{
	public:
		//Constructors
		CBitmap();
		CBitmap(HBITMAP hBitmap);
		//Operators
		CBitmap &operator=(const HBITMAP hBmp);
	};
};*/