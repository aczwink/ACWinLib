#pragma once
//Global
#include <Windows.h>
#include <CommCtrl.h>
//Local
#include "CColor.h"
#include "CSystemWindow.h"

namespace SJCLibIntern
{
	int32 CALLBACK CompareProc(LPARAM index1, LPARAM index2, LPARAM lParam);
}

namespace SJCWinLibCommCtrl
{
	enum EListViewCompareValues
	{
		CMP_LEFT = -1,
		CMP_EQUAL = 0,
		CMP_RIGHT = 1
	};

	class SJCWINLIB_API CListView : public SJCWinLib::CSystemWindow
	{
		friend int32 CALLBACK SJCLibIntern::CompareProc(LPARAM, LPARAM, LPARAM);
	private:
		//Variables
		uint32 nColumns;
		uint32 nGroups;
		//Message-callbacks
		virtual void OnClick(int32 index);
		virtual void OnColumnClick(uint16 subItem);
		virtual uint16 OnCustomDraw(uint32 itemIndex, LPARAM lParam, uint32 drawStage, SJCWinLib::CColor &textColor, SJCWinLib::CColor &textBackgroundColor);
		virtual void OnDoubleClick(int32 index);
		virtual void OnKeyDown(uint16 virtualKeyCode, uint32 flags);
		LRESULT OnNotify(NMHDR *pNMI);
		virtual bool OnRightClick(uint16 item, uint16 subItem, POINT pt);
		virtual EListViewCompareValues OnSort(uint32 index1, uint32 index2);
	public:
		//Constructor
		CListView();
		//Functions
		int32 AddColumn(const SJCLib::CWString &refText);
		void Clear();
		void Create(uint32 styleFlags, const CWindow &refParentWindow);
		void EnableGroupView(bool enable = true);
		void EnsureVisible(uint32 index, bool entirelyVisible = true);
		int32 GetCurrentSelection() const;
		uint32 GetItemCount() const;
		LPARAM GetItemData(uint32 index) const;
		int32 GetItemGroup(uint32 index) const;
		SJCLib::CString GetItemText(uint32 index, uint32 subItemIndex) const;
		int32 GetNextItem(int32 beginIndex, uint32 flags) const;
		int32 InsertGroup(SJCLib::CWString title, uint32 index = -1);
		int32 InsertItem(int32 groupId = I_GROUPIDNONE);
		void Select(uint32 index, bool select = true);
		void SetColumnWidth(uint32 columnIndex, uint16 width);
		void SetExtendedStyle(uint32 exStyle);
		void SetItemData(uint32 index, LPARAM value);
		void SetItemText(const SJCLib::CWString &refText, uint32 index, uint32 subItem);
		void Sort();

		//Inline
		inline void CreateReportView(uint32 styleFlags, const CWindow &refParentWindow)
		{
			this->Create(styleFlags | LVS_REPORT, refParentWindow);
		}

		inline int32 GetFocusedGroup() const
		{
			return (int32)((CListView *)this)->SendMessageA(LVM_GETFOCUSEDGROUP, 0, 0);
		}

		inline void GetGroupHeaderRect(uint32 index, SJCWinLib::CRect &refOut) const
		{
			refOut.top = LVGGR_HEADER;
			
			((CListView *)this)->SendMessageA(LVM_GETGROUPRECT, index, (LPARAM)&refOut);
		}

		inline uint32 GetNumberOfGroups() const
		{
			return (int32)((CListView *)this)->SendMessageA(LVM_GETGROUPCOUNT, 0, 0);
		}
	};
}

/*#pragma once
//Global
#include <vector>
//SJCLib
#include <SJCLibString.h>
//Local
#include "CControl.h"

namespace SJCLibWindows
{

	class SJCLIB_API CListView : public CControl
	{
	private:
		//Messagehandlers
		virtual void OnItemChanged(uint32 itemIndex);
	public:
		//Functions
		void SetItemCount(uint32 count);
		void SetItemText(SJCLibString::CWString text, uint32 index, int subItem);
	};
}*/