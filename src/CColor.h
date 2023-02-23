#pragma once
//Global
#include <Windows.h>
//Local
#include "Definitions.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CColor
	{
	private:
		//Variables
		byte r;
		byte g;
		byte b;
	public:
		//Constructors
		CColor();
		CColor(uint32 rrggbb);
		//Functions
		void FromCOLORREF(COLORREF color);
		static CColor GetSystemColor(int32 index);
		void Set(byte r, byte g, byte b);
		COLORREF ToCOLORREF() const;
	};
}

/*#pragma once
//Global
#include <Windows.h>
//Local
#include "SJCLib.h"
//Definitions

namespace SJCWinLib
{
	class SJCLIB_API CColor
	{
	private:
	public:
		//Constructors
		CColor(byte r, byte g, byte b);
		//Functions
		const byte GetB() const;
		const byte GetG() const;
		const byte GetR() const;
		void SetB(byte b);
		void SetG(byte g);
		void SetR(byte r);
	};
}*/