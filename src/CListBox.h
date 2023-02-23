#pragma once
//Global
#include <Windows.h>
#include <CommCtrl.h>
//Local
#include "CSystemWindow.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CListBox : public CSystemWindow
	{
	private:
		//Message-callbacks
		virtual void OnChangeSelection();
		void OnCommand(WPARAM wParam);
	public:
		//Functions
		void Clear() const;
		int32 GetCount() const;
		int32 GetCurrentSelection() const;
		LPARAM GetItemData(uint32 index) const;
		int32 GetItemFromPoint(uint16 x, uint16 y) const;
		SJCLib::CString GetItemText(uint32 index) const;
		bool SetTopIndex(uint32 index);

		//Inline
		inline int32 AddItem(const SJCLib::CWString &refText)
		{
			return (int32)this->SendMessageW(LB_ADDSTRING, 0, (LPARAM)refText.GetC_Str());
		}

		inline void Create(uint32 styleFlags, uint32 exStyleFlags, const CWindow &refParentWindow)
		{
			CSystemWindow::Create(WC_LISTBOX, WS_VISIBLE | WS_CHILD | styleFlags, exStyleFlags, refParentWindow);
		}
		
		inline int32 GetNumberOfSelectedItems() const
		{
			return (int32)((CListBox *)this)->SendMessageA(LB_GETSELCOUNT, 0, 0);
		}
		
		inline void GetSelectedItems(uint32 *pBuffer) const
		{
			((CListBox *)this)->SendMessageA(LB_GETSELITEMS, this->GetNumberOfSelectedItems(), (LPARAM)pBuffer);
		}
		
		inline void Select(uint32 index)
		{
			this->SendMessageA(LB_SETCURSEL, index, 0);
		}

		inline void SetItemData(uint32 index, LPARAM value)
		{
			this->SendMessageA(LB_SETITEMDATA, index, value);
		}
	};
}