//Class Header
#include "CommCtrl CListView.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
using namespace SJCWinLibCommCtrl;

//Intern
namespace SJCLibIntern
{
	int32 CALLBACK CompareProc(LPARAM index1, LPARAM index2, LPARAM lParam)
	{
		CListView *pList;

		pList = (CListView *)lParam;

		return pList->OnSort((uint32)index1, (uint32)index2);
	}
}

//Constructor
CListView::CListView()
{
	this->nColumns = 0;
	this->nGroups = 0;
}

//Message-callbacks
void CListView::OnClick(int32 index)
{
	CWindow::RespondDefault();
}

void CListView::OnColumnClick(uint16 subItem)
{
	CWindow::RespondDefault();
}

uint16 CListView::OnCustomDraw(uint32 itemIndex, LPARAM lParam, uint32 drawStage, CColor &textColor, CColor &textBackgroundColor)
{
	return CDRF_DODEFAULT;
}

void CListView::OnDoubleClick(int32 index)
{
	CWindow::RespondDefault();
}

void CListView::OnKeyDown(uint16 virtualKeyCode, uint32 flags)
{
	CWindow::RespondDefault();
}

LRESULT CListView::OnNotify(NMHDR *pNMI)
{
	switch(pNMI->code)
	{
	case NM_CLICK:
		this->OnClick(((NMITEMACTIVATE *)pNMI)->iItem);
		return 0;
	case NM_DBLCLK:
		this->OnDoubleClick(((NMITEMACTIVATE *)pNMI)->iItem);
		return 0;
	case NM_RCLICK:
		{
			NMITEMACTIVATE *pNMIA = (NMITEMACTIVATE *)pNMI;
			return this->OnRightClick(pNMIA->iItem, pNMIA->iSubItem, pNMIA->ptAction);
		}
	case NM_CUSTOMDRAW:
		{
			LRESULT result;
			NMLVCUSTOMDRAW *pCD = (NMLVCUSTOMDRAW *)pNMI;
			CColor textColor, backgroundColor;
			
			textColor.FromCOLORREF(pCD->clrText);
			backgroundColor.FromCOLORREF(pCD->clrTextBk);
			result = this->OnCustomDraw((uint32)pCD->nmcd.dwItemSpec, pCD->nmcd.lItemlParam, pCD->nmcd.dwDrawStage, textColor, backgroundColor);
			pCD->clrText = textColor.ToCOLORREF();
			pCD->clrTextBk = backgroundColor.ToCOLORREF();
			
			return result;
		}
		/*case LVN_ITEMCHANGED:
		this->OnItemChanged(((NMLISTVIEW *)pNMI)->iItem);
		return 0;*/
	case LVN_COLUMNCLICK:
		this->OnColumnClick(((NMLISTVIEW *)pNMI)->iSubItem);
		return 0;
	case LVN_KEYDOWN:
		this->OnKeyDown(((NMLVKEYDOWN *)pNMI)->wVKey, ((NMLVKEYDOWN *)pNMI)->flags);
		return 0;
	}
	
	CWindow::RespondDefault();
	return 0;
}

bool CListView::OnRightClick(uint16 item, uint16 subItem, POINT pt)
{
	CWindow::RespondDefault();
	return false;
}

EListViewCompareValues CListView::OnSort(uint32 index1, uint32 index2)
{
	return CMP_EQUAL;
}

//Public Functions
int32 CListView::AddColumn(const CWString &refText)
{
	LVCOLUMNW lvc;
	
	MemZero(&lvc, sizeof(lvc));
	lvc.mask = LVCF_TEXT;
	lvc.pszText = (LPWSTR)refText.GetC_Str();
	
	return (int32)this->SendMessageA(LVM_INSERTCOLUMNW, this->nColumns++, (LPARAM)&lvc);
}

void CListView::Clear()
{
	this->SendMessageA(LVM_DELETEALLITEMS, 0, 0);
}

void CListView::Create(uint32 styleFlags, const CWindow &refParentWindow)
{
	CSystemWindow::Create(WC_LISTVIEW, styleFlags, 0, refParentWindow);
}

void CListView::EnableGroupView(bool enable)
{
	this->SendMessageA(LVM_ENABLEGROUPVIEW, enable, 0);
}

void CListView::EnsureVisible(uint32 index, bool entirelyVisible)
{
	this->SendMessageA(LVM_ENSUREVISIBLE, index, entirelyVisible ? FALSE : TRUE);
}

int32 CListView::GetCurrentSelection() const
{
	//MAKELPARAM((LVNI_FOCUSED | LVNI_SELECTED), 0)
	return this->GetNextItem(-1, LVNI_FOCUSED | LVNI_SELECTED);
}

uint32 CListView::GetItemCount() const
{
	return (uint32)((CListView *)this)->SendMessageA(LVM_GETITEMCOUNT, 0, 0);
}

LPARAM CListView::GetItemData(uint32 index) const
{
	LVITEM item;

	MemZero(&item, sizeof(item));
	item.iItem = index;
	item.mask = LVIF_PARAM;
	
	((CListView *)this)->SendMessageA(LVM_GETITEM, 0, (LPARAM)&item);

	return item.lParam;
}

int32 CListView::GetItemGroup(uint32 index) const
{
	LVITEM item;

	MemZero(&item, sizeof(item));
	item.iItem = index;
	item.mask = LVIF_PARAM;
	
	((CListView *)this)->SendMessageA(LVM_GETITEM, 0, (LPARAM)&item);
	
	return item.iGroupId;
}

CString CListView::GetItemText(uint32 index, uint32 subItemIndex) const
{
	CString result;
	LVITEM item = {0};
	char buffer[512] = {0};

	item.iItem = index;
	item.iSubItem = subItemIndex;
	item.pszText = buffer;
	item.cchTextMax = sizeof(buffer);
	item.mask = LVIF_TEXT;

	((CListView *)this)->SendMessageA(LVM_GETITEM, NULL, (LPARAM)&item);

	result = item.pszText;

	return result;
}

int32 CListView::GetNextItem(int32 beginIndex, uint32 flags) const
{
	return (int32)((CListView *)this)->SendMessageA(LVM_GETNEXTITEM, beginIndex, flags);
}

int32 CListView::InsertGroup(CWString title, uint32 index)
{
	LVGROUP group = {0};

	group.cbSize = sizeof(group);
	group.mask = LVGF_HEADER | LVGF_GROUPID;
	group.pszHeader = (LPWSTR)title.GetC_Str();
	group.iGroupId = this->nGroups++;

	return (int32)this->SendMessageA(LVM_INSERTGROUP, index, (LPARAM)&group);
}

int32 CListView::InsertItem(int32 groupId)
{
	LVITEM item;

	MemZero(&item, sizeof(item));
	//item.mask = LVIF_TEXT;
	if(groupId != I_GROUPIDNONE)
	{
		item.mask |= LVIF_GROUPID;
	}
	
	item.iItem = this->GetItemCount();
	//item.pszText = (LPSTR)text.GetC_Str();
	item.iGroupId = groupId;
	
	return (uint32)this->SendMessageA(LVM_INSERTITEMW, 0, (LPARAM)&item);
}

void CListView::Select(uint32 index, bool select)
{
	LVITEM item;
	LRESULT result;

	MemZero(&item, sizeof(item));
	item.stateMask = LVIF_STATE;
	if(select)
	{
		item.state = LVIS_FOCUSED | LVIS_SELECTED;
	}

	result = this->SendMessageA(LVM_SETITEMSTATE, index, (LPARAM)&item);
	this->SendMessageA(LVM_ENSUREVISIBLE, index, FALSE);
}

void CListView::SetColumnWidth(uint32 columnIndex, uint16 width)
{
	this->SendMessageA(LVM_SETCOLUMNWIDTH, columnIndex, MAKELPARAM(width, 0));
}

void CListView::SetExtendedStyle(uint32 exStyle)
{
	this->SendMessageA(LVM_SETEXTENDEDLISTVIEWSTYLE, exStyle, exStyle);
}

void CListView::SetItemData(uint32 index, LPARAM value)
{
	LVITEM item;

	MemZero(&item, sizeof(item));

	item.iItem = index;
	item.mask = LVIF_PARAM;
	item.lParam = value;

	this->SendMessage(LVM_SETITEM, 0, (LPARAM)&item);
}

void CListView::SetItemText(const CWString &refText, uint32 index, uint32 subItem)
{
	LVITEMW item;

	MemZero(&item, sizeof(item));

	item.iSubItem = subItem;
	item.pszText = (LPWSTR)refText.GetC_Str();

	this->SendMessageA(LVM_SETITEMTEXTW, index, (LPARAM)&item);
}

void CListView::Sort()
{
	ListView_SortItemsEx(this->hWnd, SJCLibIntern::CompareProc, this);
}

/*
//Global
#include <iostream>
#include <string>
#include <CommCtrl.h>
//Namespaces
using namespace SJCLib;
using namespace SJCLibString;
using namespace SJCLibWindows;

//Messagehandlers
void CListView::OnItemChanged(uint32 itemIndex)
{
}

void CListView::SetItemCount(uint32 count)
{
	this->SendMessageA(LVM_SETITEMCOUNT, count, 0);
}

void CListView::SetItemText(CWString text, uint32 index, int subItem)
{
	LVITEM item;

	memzero(&item, sizeof(item));
	item.iSubItem = subItem;
	item.pszText = (LPSTR)text.c_str();

	this->SendMessageA(LVM_SETITEMTEXTW, index, (LPARAM)&item);
}
*/