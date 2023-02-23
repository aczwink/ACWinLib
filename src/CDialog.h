#pragma once
//Local
#include "CPopupWindow.h"
#include "CSystemWindow.h"

//Forward Declarations
namespace SJCLibIntern
{
	LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}

namespace SJCWinLib
{
	class SJCWINLIB_API CDialog : public CPopupWindow
	{
		friend LRESULT CALLBACK SJCLibIntern::DialogProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		//Variables
		DLGTEMPLATE *pTemplate;
		uint32 tplSize;
		const CWindow *pParentWindow;
		//Message-callbacks
		virtual void OnClose();
		virtual void OnInit();
		//Functions
		void AppendData(void *pData, uint16 dataSize);
		void AppendString(SJCLib::CString str);
		void EnsureSize(uint16 size);
	public:
		//Constructor
		CDialog();
		//Destructor
		~CDialog();
		//Functions
		void Create(SJCLib::CString caption, uint32 styleFlags, dialogBoxUnits x, dialogBoxUnits y, dialogBoxUnits width, dialogBoxUnits height, const CWindow *pParentWindow, const CFont &refFont);
		const CRect &DialogToScreenUnits(CRect &refRc);
		void End(int32 result = 0);
		CSystemWindow *GetNextGroupItem(const CSystemWindow *pStartingPointCtrl, bool next = true);
		int32 Run();

		//Inline
		inline void SetFocus(CWindow &refControl)
		{
			this->PostMessageA(WM_NEXTDLGCTL, (WPARAM)refControl.hWnd, TRUE);
		}
	};
}

/*
#include "CControl.h"
#include "CModule.h"

namespace SJCWinLib
{
	class SJCLIB_API CDialog : public CWindow
	{
		friend LRESULT CALLBACK SJCLibIntern::DialogProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	protected:
		//Variables
		//Functions
		//Messagehandlers
		virtual void OnSize(WPARAM resizingType, uint16 newWidth, uint16 newHeight);
	public:
		int RunModeless();
		void ScreenToDialogUnits(CRect &refRc);
	};
}*/