#pragma once
//Global
#include <Windows.h>
//Local
#include "Definitions.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CGDIObject abstract
	{
		//Classes
		friend class CDeviceContext;
		friend class CModule;
		friend class CWindow;
	protected:
		//Variables
		HGDIOBJ hGDIObj;
	public:
		//Constructor
		CGDIObject();
		//Destructor
		~CGDIObject();
		//Functions
		void Release();
	};
}