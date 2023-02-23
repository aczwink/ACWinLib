#pragma once
//Local
#include "CSystemWindow.h"
//Global
#include <CommCtrl.h>

namespace SJCWinLib
{
	class SJCWINLIB_API CComboBox : public CSystemWindow
	{
	private:
		//Message-callbacks
		void OnCommand(WPARAM wParam);
		virtual void OnChangeSelection();
	public:
		//Functions
		uint32 AddItem(SJCLib::CString text);
		uint64 GetItemData(uint32 index) const;
		int32 GetSelection() const;
		SJCLib::CString GetText(uint32 index) const;
		void Select(uint32 index);
		void SetCueBanner(SJCLib::CWString text);
		void SetItemData(uint32 index, uint64 value) const;

		//Inline
		inline void Clear()
		{
			this->SendMessageA(CB_RESETCONTENT, 0, 0);
		}
		
		inline void Create(uint32 styleFlags, const CWindow &refParentWindow)
		{
			CSystemWindow::Create(WC_COMBOBOX, styleFlags, 0, refParentWindow);
		}

		inline void CreateDropDownList(uint32 styleFlags, const CWindow &refParentWindow)
		{
			this->Create(styleFlags | CBS_DROPDOWNLIST, refParentWindow);
		}
	};
}

/*#pragma once
//Global
#include <iostream>
#include <Windows.h>
#include <CommCtrl.h>
//Local
#include "CControl.h"

namespace SJCLibWindows
{
	class SJCLIB_API CComboBox : public CControl
	{
	public:
		//Check Usage
		*/
		/*
		uint GetCount();
		WNDPROC subclass(WNDPROC newProcedure);
		*/
//	};
//}