#pragma once
//SJCLib
#include <SJCLib.h>
//Local
#include "CColor.h"
#include "CGDIObject.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CPen : public CGDIObject
	{
	public:
		//Constructors
		inline CPen()
		{
		}

		inline CPen(uint32 penStyle, uint16 width, const CColor &refColor)
		{
			this->hGDIObj = CreatePen(penStyle, width, refColor.ToCOLORREF());
		}
	};
}