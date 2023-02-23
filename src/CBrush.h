#pragma once
//SJCLib
#include <SJCLib.h>
//Local
#include "CColor.h"
#include "CGDIObject.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CBrush : public CGDIObject
	{
	public:
		//Functions
		void CreateSolidBrush(const CColor &refColor);
		void CreateSystemColorBrush(int64 index);
	};
}

/*#pragma once
//global
#include <Windows.h>
//local
#include "SJCLib.h"
#include "CColor.h"
#include "CGDIObject.h"

namespace SJCWinLib
{
	class SJCLIB_API CBrush : public CGDIObject
	{
		friend class CDeviceContext;
		friend class CModule;
	public:
		//constructor
		CBrush();
		CBrush(HBRUSH hBrush);
		//functions
	};
};*/