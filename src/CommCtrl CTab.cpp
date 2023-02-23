//Class Header
#include "CommCtrl CTab.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLibCommCtrl;

//Message-callbacks
void CTab::OnSelectionChanged()
{
}

bool CTab::OnSelectionChanging()
{
	return true;
}

//Public methods
int32 CTab::InsertItem(uint32 index, CString text)
{
	TCITEM item;
	
	MemZero(&item, sizeof(item));
	item.mask = TCIF_TEXT;
	item.pszText = (LPSTR)text.GetC_Str();
	item.cchTextMax = text.GetLength();
	
	return (int32)this->SendMessageA(TCM_INSERTITEM, index, (LPARAM)&item);
}

void CTab::Select(uint32 index, bool inform)
{
	if(inform)
	{
		if(!this->OnSelectionChanging())
		{
			return;
		}
	}
	this->SendMessageA(TCM_SETCURSEL, index, 0);
	if(inform)
	{
		this->OnSelectionChanged();
	}
}

/*
using namespace SJCWinLib;

LRESULT CTab::OnNotify(NMHDR *pNmh)
{
	switch(pNmh->code)
	{
	case TCN_SELCHANGE:
		this->OnSelectionChanged();
		return 0;
	case TCN_SELCHANGING:
		return !this->OnSelectionChanging();
	}

	return CWindow::RespondDefault();
}

void CTab::SetText(uint32 index, CString text)
{
	TCITEM item;
	
	MemZero(&item, sizeof(item));
	item.mask = TCIF_TEXT;
	item.pszText = (LPSTR)text.GetC_Str();
	
	this->SendMessageA(TCM_SETITEM, index, (LPARAM)&item);
}

/*
//Namespaces
using namespace SJCLib;
using namespace SJCLibString;
using namespace SJCLibWindows;

//Callbacks
LRESULT CTab::OnNotify(NMHDR *pNmh)
{
	switch(pNmh->code)
	{
	case NM_RCLICK:
		return !this->OnRightClick();
	case TCN_SELCHANGE:
		this->OnSelectionChanged();
		return 0;
	case TCN_SELCHANGING:
		return !this->OnSelectionChanging();
	}

	return CWindow::RespondDefault();
}

bool CTab::OnRightClick()
{
	return true;
}

//Public Functions
void CTab::DeleteItem(uint32 index)
{
	this->SendMessageA(TCM_DELETEITEM, index, 0);
}

int32 CTab::GetItemFromPos(int32 x, int32 y, uint32 flags)
{
	TCHITTESTINFO tchti;

	tchti.flags = flags;
	tchti.pt.x = x;
	tchti.pt.y = y;

	return (int32)this->SendMessageA(TCM_HITTEST, 0, (LPARAM)&tchti);
}
*/