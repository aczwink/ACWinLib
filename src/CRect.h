#pragma once
//Global
#include <Windows.h>
//Local
#include "Definitions.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CRect : public RECT
	{
	public:
		//Constructors
		CRect();
		CRect(uint32 left, uint32 top, uint32 right, uint32 bottom);
		//Functions
		uint32 GetHeight() const;
		uint32 GetWidth() const;
		CRect &Init(uint32 x, uint32 y, uint32 width, uint32 height);
		bool PointInRect(POINT pt) const;
		void SetHeight(uint32 height);
		void SetWidth(uint32 width);
		//Inline
		inline void CalculateWindowRect(uint32 styleFlags, uint32 exStyleFlags, bool hasMenu)
		{
			::AdjustWindowRectEx(this, styleFlags, hasMenu, exStyleFlags);
		}

		inline void Offset(int16 dx, int16 dy)
		{
			OffsetRect(this, dx, dy);
		}

		inline void Subtract(const CRect &refrcSubtrahend)
		{
			SubtractRect(this, this, &refrcSubtrahend);
		}
	};
}

/*#pragma once
//Global
#include <Windows.h>
//Local
#include "SJCLib.h"

namespace SJCWinLib
{
	class SJCLIB_API CRect : public RECT
	{
	public:
		//Operators
		CRect &operator=(const RECT &rc);
		//Functions
		void OffsetRect(int32 dx, int32 dy);
	};
}*/