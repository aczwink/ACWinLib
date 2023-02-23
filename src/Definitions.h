#pragma once
//SJCLib
#include <SJCLib.h>

#ifdef SJCWINLIB_BUILD
#define SJCWINLIB_API __declspec(dllexport)
#else
#define SJCWINLIB_API __declspec(dllimport)
#endif

//Types
typedef int16 dialogBoxUnits;

//COM
#define SAFERELEASE(pCOMInterface) if(pCOMInterface){pCOMInterface->Release();}

namespace SJCWinLib
{
	//Enums
	enum EAlignment
	{
		ALIGN_LEFT,
		ALIGN_CENTER,
		ALIGN_RIGHT
	};
	
	enum EVAlignment
	{
		VALIGN_TOP,
		VALIGN_CENTER,
		VALIGN_BOTTOM
	};
}