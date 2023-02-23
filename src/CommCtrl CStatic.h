#pragma once
//Local
#include "CSystemWindow.h"

//Forward Declarations
namespace SJCLibIntern
{
	LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}

namespace SJCWinLibCommCtrl
{
	class SJCWINLIB_API CStatic : public SJCWinLib::CSystemWindow
	{
		friend LRESULT CALLBACK SJCLibIntern::DialogProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		//Message-callbacks
		virtual SJCWinLib::CBrush OnColor(SJCWinLib::CDeviceContext &refDC);
	public:
		//Functions
		void Create(uint32 styleFlags, const CWindow &refParentWindow);
	};
}