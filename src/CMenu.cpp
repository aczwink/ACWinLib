//Class Header
#include "CMenu.h"
//Local
#include "CWindow.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Constructor
CMenu::CMenu()
{
	this->hMenu = NULL;
}

//Public Functions
void CMenu::AppendSeperator()
{
	::AppendMenu(this->hMenu, MF_SEPARATOR, NULL, NULL);
}

void CMenu::AppendSubMenu(CString title, const CMenu &refSubMenu)
{
	::AppendMenu(this->hMenu, MF_STRING | MF_POPUP, (UINT_PTR)refSubMenu.hMenu, title.GetC_Str());
}

void CMenu::Create()
{
	this->hMenu = ::CreateMenu();
}

void CMenu::CreatePopup()
{
	this->hMenu = ::CreatePopupMenu();
}

void CMenu::Destroy()
{
	if(this->hMenu)
	{
		DestroyMenu(this->hMenu);
		this->hMenu = NULL;
	}
}

CMenu CMenu::GetSubMenu(uint32 pos) const
{
	CMenu tmp;

	tmp.hMenu = ::GetSubMenu(this->hMenu, pos);

	return tmp;
}

void CMenu::SetItemId(uint16 currentItemId, uint16 newItemId)
{
	MENUITEMINFO mii;

	MemZero(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_ID;
	mii.wID = newItemId;

	this->SetItemInfo(currentItemId, mii);
}

void CMenu::SetItemText(uint16 itemId, SJCLib::CString text)
{
	MENUITEMINFO mii;

	MemZero(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_STRING;
	mii.dwTypeData = (char *)text.GetC_Str();

	this->SetItemInfo(itemId, mii);
}

int32 CMenu::TrackPopupMenu(EAlignment align, EVAlignment valign, int32 x, int32 y, const CWindow &refWindow)
{
	UINT flags;
	switch(align)
	{
	case ALIGN_LEFT:
		flags = TPM_LEFTALIGN;
		break;
	case ALIGN_CENTER:
		flags = TPM_CENTERALIGN;
		break;
	case ALIGN_RIGHT:
		flags = TPM_RIGHTALIGN;
		break;
	}
	switch(valign)
	{
	case VALIGN_TOP:
		flags |= TPM_TOPALIGN;
		break;
	case VALIGN_CENTER:
		flags |= TPM_VCENTERALIGN;
		break;
	case VALIGN_BOTTOM:
		flags |= TPM_BOTTOMALIGN;
		break;
	}

	return ::TrackPopupMenu(this->hMenu, flags | TPM_NONOTIFY | TPM_RETURNCMD, x, y, 0, refWindow.hWnd, NULL);
}

/*
//Local
#include "CWindow.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibString;
using namespace SJCLibWindows;

//Public Functions
CSmartPointer<CMenu> CMenu::AddPopup()
{
	CSmartPointer<CMenu> ptr;
	ptr->Attach(CreatePopupMenu());

	return ptr;
}

void CMenu::Attach(HMENU hMenu)
{
	this->hMenu = hMenu;
}
*/