#pragma once
//Global
#include <Windows.h>
//Local
#include "Definitions.h"

namespace SJCWinLib
{
	//Forward Declarations
	class CWindow;

	class SJCWINLIB_API CMenu
	{
		friend class CPopupWindow;
	private:
		//Variables
		HMENU hMenu;
	public:
		//Constructor
		CMenu();
		//Functions
		void AppendSeperator();
		void AppendSubMenu(SJCLib::CString title, const CMenu &refSubMenu);
		void Create();
		void CreatePopup();
		void Destroy();
		CMenu GetSubMenu(uint32 pos) const;
		void SetItemId(uint16 currentItemId, uint16 newItemId);
		void SetItemText(uint16 itemId, SJCLib::CString text);
		int32 TrackPopupMenu(EAlignment align, EVAlignment valign, int32 x, int32 y, const CWindow &refWindow);

		//Inline
		inline void AppendItem(SJCLib::CString title, uint16 itemId)
		{
			::AppendMenu(this->hMenu, MF_STRING, itemId, title.GetC_Str());
		}

		inline void CheckItem(uint16 itemId, bool check = true)
		{
			CheckMenuItem(this->hMenu, itemId, MF_BYCOMMAND | (check ? MF_CHECKED : MF_UNCHECKED));
		}

		inline void CheckItemRadio(uint16 firstItemId, uint16 lastItemId, uint16 checkId)
		{
			CheckMenuRadioItem(this->hMenu, firstItemId, lastItemId, checkId, MF_BYCOMMAND);
		}

		inline void Delete(uint16 itemId)
		{
			DeleteMenu(this->hMenu, itemId, MF_BYCOMMAND);
		}

		inline void EnableItem(uint16 menuId, bool enable = true)
		{
			::EnableMenuItem(this->hMenu, menuId, enable ? MF_ENABLED : MF_DISABLED | MF_GRAYED);
		}

		inline bool IsItemChecked(uint16 itemId) const
		{
			return (GetMenuState(this->hMenu, itemId, MF_BYCOMMAND) & MF_CHECKED) != 0;
		}

		inline void SetItemInfo(uint16 itemId, const MENUITEMINFO &refMii)
		{
			SetMenuItemInfo(this->hMenu, itemId, FALSE, &refMii);
		}
	};
}

/*#pragma once
//Global
#include <Windows.h>
//SJCLib
#include <SJCLib.h>

namespace SJCWinLib
{
	//Forward Declarations
	class CWindow;

	//Main Class
	class SJCLIB_API CMenu
	{
		friend class CWindow;
	public:
		//Functions
		SJCLib::CSmartPointer<CMenu> AddPopup();
		void Attach(HMENU hMenu);
	};
}*/