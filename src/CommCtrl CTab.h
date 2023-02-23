#pragma once
//Global
#include <Windows.h>
#include <CommCtrl.h>
//Local
#include "CSystemWindow.h"

namespace SJCWinLibCommCtrl
{
	class SJCWINLIB_API CTab : public SJCWinLib::CSystemWindow
	{
	private:
		//Message-callbacks
		virtual void OnSelectionChanged();
		virtual bool OnSelectionChanging();
	public:
		//Methods
		int32 InsertItem(uint32 index, SJCLib::CString text);
		void Select(uint32 index, bool inform = false);
		//Inline
		inline void Create(const CWindow &refParentWindow)
		{
			SJCWinLib::CSystemWindow::Create(WC_TABCONTROL,  WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, 0, refParentWindow);
		}

		inline int32 GetSelection() const
		{
			return (int32)((CTab *)this)->SendMessageA(TCM_GETCURSEL, 0, 0);
		}
	};
}

/*
namespace SJCWinLibCommCtrl
{
	class SJCWINLIB_API CTab : public SJCWinLib::CControl
	{
	private:
		LRESULT OnNotify(NMHDR *pNmh);
	public:
		//Functions
		inline void Create(const SJCWinLib::CRect &refRect, const CWindow &refParentWindow)
		{
			this->Create((uint16)refRect.left, (uint16)refRect.top, (uint16)refRect.GetWidth(), (uint16)refRect.GetHeight(), refParentWindow);
		}

		inline void GetDisplayArea(SJCWinLib::CRect *pRect) const
		{
			this->GetClientRect(*pRect);
			((CTab *)this)->SendMessageA(TCM_ADJUSTRECT, FALSE, (LPARAM)pRect);
		}

		void SetText(uint32 index, SJCLib::CString text);
	};
}

/*
namespace SJCLibWindows
{
	class SJCLIB_API CTab : public CControl
	{
	private:
		//Callbacks
		LRESULT OnNotify(NMHDR *pNmh);
		virtual bool OnRightClick();
	public:
		//Functions
		void DeleteItem(uint32 index);
		int32 GetItemFromPos(int32 x, int32 y, uint32 flags);
	};
}*/