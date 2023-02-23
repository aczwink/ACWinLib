#pragma once
//Local
#include "CButton.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CCheckBox : public CSystemWindow
	{
	private:
		//Message-callbacks
		virtual void OnClick();
		void OnCommand(WPARAM wParam);
	public:
		//Functions
		void Check();
		void Create(SJCLib::CString text, uint32 styleFlags, uint32 x, uint32 y, uint32 width, uint32 height, const CWindow &refParentWindow);
		bool IsChecked();
		//Inline
		inline void CheckIndeterminate()
		{
			((CCheckBox *)this)->SendMessageA(BM_SETCHECK, BST_INDETERMINATE, 0);
		}

		inline void Create(SJCLib::CString text, uint32 styleFlags, const CRect &refRect, const CWindow &refParentWindow)
		{
			this->Create(text, styleFlags, refRect.left, refRect.top, refRect.GetWidth(), refRect.GetHeight(), refParentWindow);
		}

		inline void CreateThreeStateBox(SJCLib::CString text, uint32 styleFlags, int32 x, int32 y, int32 width, int32 height, const CWindow &refParentWindow)
		{
			this->Create(text, BS_AUTO3STATE | styleFlags, x, y, width, height, refParentWindow);
		}

		inline uint16 GetCheckState() const
		{
			return uint16(((CCheckBox *)this)->SendMessageA(BM_GETCHECK, 0, 0));
		}
	};
}

/*//Local
#include "CButton.h"

namespace SJCLibWindows
{
	class SJCLIB_API CCheckBox : public CButton
	{
	private: //Forbidden Functions
		SJCLib::SJCLibResult CreateDefPushButton(SJCLibString::CString text, DWORD style, int x, int y, int width, int height, CWindow *parentWindow);
	private:
		//Functions
		void CreateDefPushButton();
	};
}*/