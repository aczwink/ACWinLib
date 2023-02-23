#pragma once
//Local
#include "CPopupWindow.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CFrame : public CPopupWindow
	{
		//Classes
		friend class CApplication;
		//Procedures
		friend bool SJCLibIntern::ForwardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		//Callbacks
		virtual void OnAcceleratorCommand(uint16 acceleratorCmdId);
		void OnDestroy();
		bool OnEraseBackground(CDeviceContext &refDC);
		bool OnRequestCursor(const CWindow *pContainingWindow, uint16 hitTest, uint16 msgId);
	public:
		//Functions
		void Create(SJCLib::CString title, uint16 x, uint16 y, uint16 width, uint16 height);
	};
}