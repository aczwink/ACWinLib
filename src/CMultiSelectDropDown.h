#pragma once
//Local
#include "CSystemWindow.h"
#include "CMultiSelectDropDownDropDown.h"
#include "CMultiSelectDropDownMessageWindow.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CMultiSelectDropDown : public CSystemWindow
	{
		friend class SJCLibIntern::CMultiSelectDropDownMessageWindow;
	private:
		//Variables
		CFont font;
		int32 state;
		SJCLibIntern::CMultiSelectDropDownDropDown dropDownWindow;
		SJCLibIntern::CMultiSelectDropDownMessageWindow messageWindow;
		//Message-callbacks
		void OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y);
		void OnPaint();
		void OnSetFont(const CFont &refFont);
	public:
		//Constructor
		CMultiSelectDropDown();
		//Functions
		uint32 AddItem(SJCLib::CString text);
		void Create(uint32 styleFlags, int32 x, int32 y, int32 width, int32 height, const CWindow &refParentWindow);

		inline void Create(uint32 styleFlags, const CRect &refRect, const CWindow &refParentWindow)
		{
			this->Create(styleFlags, refRect.left, refRect.top, refRect.GetWidth(), refRect.GetHeight(), refParentWindow);
		}

		uint64 GetItemData(uint32 index) const;
		SJCLib::CArray<uint16> GetSelection() const;
		void Select(uint32 index);
		void SetItemData(uint32 index, uint64 value);
	};
}

/*#pragma once
//Local
#include "CControl.h"
#include "CDeviceContext.h"
#include "CMultiSelectDropDownMessageWindow.h"

namespace SJCLibWindows
{
	class SJCLIB_API CMultiSelectDropDown : public CControl
	{
	friend class SJCLibIntern::CMultiSelectDropDownDropDown;
	public:
	//Functions
		void Select(SJCLib::CArray<uint16> indexList);
	};
}*/