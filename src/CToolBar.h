#pragma once
//Local
#include "CSystemWindow.h"
#include "CImageList.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CToolBar : public CSystemWindow
	{
	private:
		//Message-callbacks
		virtual bool OnClick(uint16 commandId);
		LRESULT OnNotify(NMHDR *pNmh);
	public:
		//Functions
		void AddButton(const SJCLib::CString &refText, uint32 commandId, uint32 bitmapIndex);
		void AddSeperator();
		void LoadSystemImages(uint32 bitmapDb);
		void SetImageList(const CImageList &refImgList);

		//Inline
		inline void AddButton(const SJCLib::CString &refText, uint32 commandId)
		{
			this->AddButton(refText, commandId, I_IMAGENONE);
		}

		inline void AutoSize()
		{
			this->SendMessageA(TB_AUTOSIZE, 0, 0);
		}

		inline void Create(uint32 styleFlags, const CWindow &refParentWindow)
		{
			CSystemWindow::Create(TOOLBARCLASSNAME, styleFlags | WS_CHILD | WS_VISIBLE | TBSTYLE_LIST, 0, refParentWindow);
			this->SendMessageA(TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);
		}

		inline void EnableButton(uint32 commandId, bool enable = true)
		{
			this->SendMessageA(TB_ENABLEBUTTON, commandId, enable);
		}
	};
}

/*//Local
#include "CControl.h"
#include "CImageList.h"

namespace SJCLibWindows
{
	class SJCLIB_API CToolBar : public CControl
	{
	private:
		//Callbacks
		LRESULT OnNotify(NMHDR *pNMI);
	public:
		//Functions
		void EnableButton(uint16 commandId, bool enable = true);
	};
}*/