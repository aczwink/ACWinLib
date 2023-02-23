#pragma once
//Local
#include "CFrame.h"
#include "Definitions.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CApplication
	{
	public:
		//Constructor
		CApplication();
		//Destructor
		~CApplication();
		//Functions
		int32 Run();
		int32 Run(const CFrame &refFrame, HACCEL hAccelTable);
	};
}

/*#pragma once
//Global
#include <iostream>
#include <Windows.h>
//Local
#include "CModule.h"
#include "CIcon.h"
#include "WndProc.h"
//GDI
#include "CBrush.h"

namespace SJCLibWindows
{
	class SJCLIB_API CApplication
	{
	public:
	//Functions
		int Run(CWindow *pWndTranslate, HACCEL hAccel);
	};
}*/