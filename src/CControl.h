/*#pragma once
//Local
#include "CSystemWindow.h"

//Forward Declarations
namespace SJCLibIntern
{
	LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}

namespace SJCWinLib
{
	class SJCWINLIB_API CControl : public CSystemWindow
	{
		friend class CDialog;
		friend LRESULT CALLBACK SJCLibIntern::DialogProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		friend LRESULT CALLBACK SJCLibIntern::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		//Message-callbacks
		virtual uint32 OnGetDialogCode(uint16 virtualKeyCode);
	public:
		//Functions
		void Create(SJCLib::CString className, SJCLib::CString windowName, uint32 styleFlags, uint32 exStyleFlags, uint32 x, uint32 y, uint32 width, uint32 height, const CWindow &refParentWindow);
	};
}*/