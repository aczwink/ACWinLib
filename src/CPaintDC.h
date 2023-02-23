#pragma once
//Local
#include "CDeviceContext.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CPaintDC : public CDeviceContext
	{
	private:
		//Variables
		const CWindow *pWnd;
		PAINTSTRUCT ps;
	public:
		//Constructor
		CPaintDC(const CWindow *pWnd);
		//Destructor
		~CPaintDC();
		//Functions
		void GetPaintRect(CRect &refRect) const;
	};
}