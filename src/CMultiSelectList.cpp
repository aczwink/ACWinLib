//Class Header
#include "CMultiSelectList.h"
//Local
#include "CPaintDC.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
//Definitions
#define CMULTISELECTLIST_CLASSNAME "CMultiSelectList"
#define STYLE_CHECKBOX_SIZE 18
#define STYLE_PADDING_DEFAULT 5
#define STYLE_SPACING_DEFAULT 4

//Constructor
CMultiSelectList::CMultiSelectList()
{
	//Default Style
	this->style.padding = STYLE_PADDING_DEFAULT;
	this->style.spacing = STYLE_SPACING_DEFAULT;
}

//Message-callbacks
void CMultiSelectList::OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y)
{
	if(x >= this->style.spacing && x <= this->style.spacing + STYLE_CHECKBOX_SIZE)
	{
		TEXTMETRIC tm;
		uint16 index;
		
		CPointer<CDeviceContext> pDC(this->GetDC());
		
		pDC->SelectObject(this->font);
		pDC->GetTextMetricsA(&tm);

		y -= this->style.spacing;
		index = uint16(y / (tm.tmHeight + this->style.padding));
		index += this->GetScrollPos();

		if(index > this->items.GetNoOfElements() || this->items.IsEmpty()) return;

		this->items[index].selected = !this->items[index].selected;

		this->OnSelectionChange();
		this->Invalidate();
	}
}

void CMultiSelectList::OnPaint()
{
	CPaintDC dc(this);
	CRect rcClient, rcCheckbox, rcText;
	TEXTMETRIC tm;
	uint32 state;
	
	this->GetClientRect(rcClient);
	
	CPointer<CDeviceContext> pMemDC(dc.CreateCompatibleDC());
	CPointer<CBitmap> pBackbufferBmp(dc.CreateCompatibleBitmap(rcClient.GetWidth(), rcClient.GetHeight()));
	
	pMemDC->SelectObject(pBackbufferBmp);
	pMemDC->SelectObject(font);
	pMemDC->GetTextMetricsA(&tm);

	pMemDC->FillSolidRect(rcClient, CColor::GetSystemColor(COLOR_WINDOW));

	//Fill out Rects
	rcCheckbox.left = this->style.spacing;
	rcCheckbox.right = STYLE_CHECKBOX_SIZE;

	rcText.left = this->style.spacing + STYLE_CHECKBOX_SIZE + this->style.padding;
	rcText.right = rcClient.right;
	rcText.bottom = rcClient.top + this->style.spacing;

	//Draw Items
	for(uint32 i = this->GetScrollPos(); i < this->items.GetNoOfElements(); i++)
	{
		//Calc rects
		rcText.top = rcText.bottom;
		rcText.bottom += tm.tmHeight + this->style.padding;
		rcCheckbox.top = rcText.top + (rcText.GetHeight()-STYLE_CHECKBOX_SIZE)/2;
		rcCheckbox.bottom = rcText.bottom - (rcText.GetHeight()-STYLE_CHECKBOX_SIZE)/2 + 1;

		if(this->items[i].selected)
		{
			state = DFCS_BUTTONCHECK | DFCS_CHECKED;
		}
		else
		{
			state = DFCS_BUTTONCHECK;
		}
		pMemDC->SetBackgroundColor(CColor().GetSystemColor(COLOR_WINDOW));
		pMemDC->SetTextColor(CColor().GetSystemColor(COLOR_WINDOWTEXT));

		pMemDC->DrawFrameControl(rcCheckbox, DFC_BUTTON, state);
		pMemDC->DrawTextA(this->items[i].text, rcText, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}

	//Copy Backbuffer into Foreground
	dc.BitBlt(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom, pMemDC, 0, 0, SRCCOPY);
	pBackbufferBmp->Release();
	pMemDC->Release();
}

void CMultiSelectList::OnSelectionChange()
{
}

void CMultiSelectList::OnSetFont(const SJCWinLib::CFont &refFont)
{
	this->font = refFont;
}

//Private Functions
void CMultiSelectList::UpdateScrollbar()
{
	CRect rcClient;
	TEXTMETRIC tm;
	uint32 height;
	
	CPointer<CDeviceContext> pDC(this->GetDC());
	
	this->GetClientRect(rcClient);
	
	pDC->SelectObject(font);
	pDC->GetTextMetrics(&tm);

	height = this->style.spacing; //Top spacing

	repeat(this->items.GetNoOfElements(), i)
	{
		height += tm.tmHeight + this->style.padding;
		
		if(height > (uint32)rcClient.bottom)
		{
			this->ShowScrollBar();
			this->SetScrollPageSize(i);
			this->SetScrollRange(this->items.GetNoOfElements());
			return;
		}
	}
	
	height += this->style.spacing; //Bottom spacing
	
	if(height > (uint32)rcClient.bottom)
	{
		this->ShowScrollBar();
		this->SetScrollPageSize(rcClient.bottom);
		this->SetScrollRange(height);
	}
}

//Public Functions
uint32 CMultiSelectList::AddItem(CString text)
{
	uint32 index;
	SMultiSelectItem item;
	
	item.selected = false;
	item.text = text;
	item.userData = 0;
	
	index = this->items.Push(item);
	this->UpdateScrollbar();

	return index;
}

void CMultiSelectList::Create(uint32 styleFlags, uint32 exStyleFlags, int32 x, int32 y, int32 width, int32 height, const CWindow &refParentWindow)
{
	CBrush brush;
	CCursor cursor;
	
	brush.CreateSystemColorBrush(COLOR_WINDOW+1);
	cursor.LoadSystemCursor(IDC_ARROW);
	//refParentWindow.GetModule().RegisterWindowClass(&brush, &cursor, NULL, NULL, CMULTISELECTLIST_CLASSNAME);
	ASSERT(false);
	//CWindow::Create(CMULTISELECTLIST_CLASSNAME, "", WS_VISIBLE | WS_CHILD | styleFlags, exStyleFlags, x, y, width, height, refParentWindow);
}

uint16 CMultiSelectList::GetItemCount() const
{
	return this->items.GetNoOfElements();
}

uint64 CMultiSelectList::GetItemData(uint32 index) const
{
	return this->items[index].userData;
}

CString CMultiSelectList::GetItemText(uint16 index) const
{
	return this->items[index].text;
}

CArray<uint16> CMultiSelectList::GetSelection() const
{
	CArray<uint16> selection;
	
	repeat(this->items.GetNoOfElements(), i)
		if(this->items[i].selected)
			selection.Push(i);
	
	return selection;
}

void CMultiSelectList::Select(uint32 index)
{
	this->items[index].selected = true;
	this->OnSelectionChange();
}

void CMultiSelectList::SetItemData(uint32 index, uint64 value)
{
	this->items[index].userData = value;
}


/*
//Local
#include "CPaintDC.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibString;
using namespace SJCLibWindows;


//Callbacks
void CMultiSelectList::OnMouseWheel(int16 zDelta, uint16 keys)
{
	if(zDelta < 0)
	{
		this->OnVerticalScroll(SB_LINEDOWN);
	}
	else
	{
		this->OnVerticalScroll(SB_LINEUP);
	}
}

void CMultiSelectList::OnVerticalScroll(uint16 scrollCode)
{
	CRect rcClient;
	int32 scrollRange, oldScrollPos, newScrollPos;

	this->GetClientRect(&rcClient);	
	scrollRange = this->GetScrollRange();
	oldScrollPos = this->GetScrollPos();
	
	switch(scrollCode)
	{
	case SB_PAGEUP:
	case SB_LINEUP:
		if(oldScrollPos-1 > 0)
		{
			newScrollPos = oldScrollPos - 1;
		}
		else
		{
			newScrollPos = 0;
		}
		break;
	case SB_PAGEDOWN:
	case SB_LINEDOWN:
		if(int32(this->GetScrollPageSize() + oldScrollPos+1) > scrollRange)
		{
			newScrollPos = scrollRange;
		}
		else
		{
			newScrollPos = oldScrollPos + 1;
		}
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		newScrollPos = this->GetScrollTrackPos();
		break;
	default:
		newScrollPos = oldScrollPos;
	}

	this->SetScrollPos(newScrollPos);
	this->Invalidate();
	this->Update();
}

//Public Functions
SJCLibResult CMultiSelectList::Create(uint32 styleFlags, const CRect &rc, CWindow *pParentWindow)
{
	return this->Create(styleFlags, 0, rc.left, rc.top, rc.GetWidth(), rc.GetHeight(), pParentWindow);
}

void CMultiSelectList::Select(CArray<uint16> indexList)
{
	repeat(indexList.GetLength(), i)
	{
		this->items[indexList[i]].selected = true;
	}
	this->OnSelectionChange();
}*/