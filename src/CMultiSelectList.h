#pragma once
//Local
#include "CSystemWindow.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CMultiSelectList : public CSystemWindow
	{
		struct SMultiSelectItem
		{
			bool selected;
			SJCLib::CString text;
			uint64 userData;
		};
	private:
		//Variables
		CFont font;
		SJCLib::CArray<SMultiSelectItem> items;
		//Message-callbacks
		void OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y);
		void OnPaint();
		virtual void OnSelectionChange();
		void OnSetFont(const CFont &refFont);
		//Functions
		void UpdateScrollbar();
	public:
		//Variables
		struct
		{
			uint16 padding;
			uint16 spacing;
		} style;
		//Constructor
		CMultiSelectList();
		//Functions
		uint32 AddItem(SJCLib::CString text);
		void Create(uint32 styleFlags, uint32 exStyleFlags, int32 x, int32 y, int32 width, int32 height, const CWindow &refParentWindow);
		uint16 GetItemCount() const;
		uint64 GetItemData(uint32 index) const;
		SJCLib::CString GetItemText(uint16 index) const;
		SJCLib::CArray<uint16> GetSelection() const;
		void Select(uint32 index);
		void SetItemData(uint32 index, uint64 value);
	};
}

/*#pragma once
//Local
#include "CControl.h"
#include "CDeviceContext.h"

namespace SJCLibWindows
{
class SJCLIB_API CMultiSelectList : public CControl
	{
	private:
		//Variables
		CFont font;
		//Callbacks
		void OnMouseWheel(int16 zDelta, uint16 keys);
		void OnVerticalScroll(uint16 scrollCode);
	public:
		SJCLib::SJCLibResult Create(uint32 styleFlags, const CRect &rc, CWindow *pParentWindow);
		void Select(SJCLib::CArray<uint16> indexList);
	};
}*/