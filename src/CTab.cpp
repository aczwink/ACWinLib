//Class Header
#include "CTab.h"
//Local
#include "__CWindows.h"
#include "CPaintDC.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
//Definitions
#define CTAB_CLASSNAME "CTab"
#define CTAB_MAXTABWIDTH 100
#define CTAB_BORDERSPACING 5

//Constructor
CTab::CTab()
{
	this->activeTabIndex = 0;
}

//Destructor
CTab::~CTab()
{
	this->Release();
}

//Callbacks
void CTab::OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y)
{
	bool refresh;
	POINT pt;
	
	refresh = false;
	GetCursorPos(&pt);
	this->ScreenToClient(pt);

	foreach(it, this->tabs)
	{
		if((*it).itemRect.PointInRect(pt))
		{
			this->Select(it.GetIndex());
			return;
		}
	}
}

void CTab::OnMouseMove(uint16 keys)
{
	bool refresh;
	POINT pt;
	
	GetCursorPos(&pt);
	this->ScreenToClient(pt);
	refresh = false;
	
	foreach(it, this->tabs)
	{
		switch((*it).stateId)
		{
		case TIS_NORMAL:
			{
				if((*it).itemRect.PointInRect(pt))
				{
					(*it).stateId = TIS_HOT;
					refresh = true;
				}
			}
			break;
		case TIS_HOT:
			{
				if(!(*it).itemRect.PointInRect(pt))
				{
					(*it).stateId = TIS_NORMAL;
					refresh = true;
				}
			}
			break;
		}
	}
	
	if(refresh)
		this->Refresh();
}

void CTab::OnPaint()
{
	CRect rcClient, rcTabWnd;
	CColor backgroundColor;
	CPaintDC dc(this);
	
	//Initiate double buffering
	this->GetClientRect(rcClient);
	
	CPointer<CDeviceContext> pMemDC(dc.CreateCompatibleDC());
	CPointer<CBitmap> pMemBmp(dc.CreateCompatibleBitmap(rcClient.GetWidth(), rcClient.GetHeight())); //Important that the bitmap comes from the PaintDC!!!

	pMemDC->SelectObject(pMemBmp);

	pMemDC->SelectObject(this->font);
	pMemDC->SetBackgroundMode(false);

	//Get the client area for the subwindow
	rcTabWnd = this->GetInnerWindowArea();

	/*
	Unimportant: WS_CLIPCHILDREN does the trick
	//If we have a child window... we need to exclude it from clipping, so we don't overdraw it
	if(!this->tabs.IsEmpty())
	{
		dc.ExcludeClipRect(this->GetChildWindowArea()); //IMPORTANT THAT WE CALL THAT ON THE PAINT DC!
	}*/
	
	//Draw the background
	backgroundColor = CColor::GetSystemColor(COLOR_MENU);
	pMemDC->FillSolidRect(rcClient, backgroundColor);

	if(!this->tabs.IsEmpty())
	{
		theme.DrawBackground(*pMemDC.GetPointer(), TABP_PANE, 0, rcTabWnd, NULL);
		
		//Draw the selected item (if there is one)
		this->DrawItem(this->activeTabIndex, pMemDC);
		
		//Draw all unselected items
		repeat(this->tabs.GetNoOfElements(), i)
		{
			if(i != this->activeTabIndex)
			{
				this->DrawItem(i, pMemDC);
			}
		}
	}
	
	dc.BitBlt(0, 0, rcClient.GetWidth(), rcClient.GetHeight(), pMemDC, 0, 0, SRCCOPY);
}

void CTab::OnSize(WPARAM resizingType, uint32 newWidth, uint32 newHeight)
{
	if(!this->tabs.IsEmpty())
	{
		repeat(this->tabs.GetNoOfElements(), i)
		{
			this->RecalcItemRect(i);
		}

		ASSERTMSG(0, "must be reimplemented, because of CPOINTER");		
		//this->tabs[this->activeTabIndex].pTabChild->SetPos(this->GetChildWindowArea());
	}

	this->Refresh();
}

//Private Functions
void CTab::DrawItem(uint32 index, CPointer<CDeviceContext> &refpMemDC)
{
	CRect drawRect;
	STab &refTab = this->tabs[index];

	drawRect = refTab.itemRect;
	if(index == this->activeTabIndex)
	{
		//take one pixel to left and right more (causes to overdraw borders)
		drawRect.left--;
		drawRect.right++;
		drawRect.bottom++;
		this->theme.DrawBackground(*refpMemDC.GetPointer(), TABP_TABITEM, TIS_SELECTED, drawRect, NULL);
	}
	else
	{
		drawRect.top += 2;
		this->theme.DrawBackground(*refpMemDC.GetPointer(), TABP_TABITEM, refTab.stateId, drawRect, NULL);
	}
	refpMemDC->DrawTextW(refTab.title, drawRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER /*| DT_END_ELLIPSIS*/);
}

CRect CTab::GetChildWindowArea() const
{
	CRect rcChild;
	
	rcChild = this->GetInnerWindowArea();
	rcChild.left += 2;
	rcChild.top += 2;
	rcChild.right -= 4;
	rcChild.bottom -= 4;

	return rcChild;
}

CRect CTab::GetInnerWindowArea() const
{
	CRect rcTabWnd;
	
	this->GetClientRect(rcTabWnd);
	
	rcTabWnd.top = this->tabHeight;
	
	return rcTabWnd;
}

void CTab::RecalcItemRect(uint32 index)
{
	uint32 leftOffset;
	CRect rc;
	
	CPointer<CDC> pDC(this->GetDC());

	STab &refTab = this->tabs[index];
	
	leftOffset = 2;
	if(index > 0)
	{
		leftOffset = this->tabs[index-1].itemRect.right;
	}
	
	pDC->SelectObject(this->font);

	pDC->DrawTextW(refTab.title, rc, DT_SINGLELINE | DT_CALCRECT);

	refTab.itemRect.left = leftOffset;
	refTab.itemRect.top = 0;
	refTab.itemRect.right = leftOffset + MIN(rc.right + 2*CTAB_BORDERSPACING, CTAB_MAXTABWIDTH);
	refTab.itemRect.bottom = this->tabHeight;
}

void CTab::Refresh()
{
	this->Invalidate();
	if(!this->tabs.IsEmpty())
	{
		ASSERTMSG(0, "must be reimplemented, because of CPOINTER");
		//this->tabs[this->activeTabIndex].pTabChild->Invalidate();
	}
}

//Public Functions
uint32 CTab::AddTab(const CWString &refTitle, const CPointer<CWindow> &refpTabChild)
{
	uint32 index;
	STab tab;

	ASSERTMSG(0, "must be reimplemented, because of CPOINTER");
	//tab.pTabChild = refpTabChild;
	tab.title = refTitle;
	tab.stateId = TIS_NORMAL;

	ASSERTMSG(0, "must be reimplemented, because of CPOINTER");
	//tab.pTabChild->Show(SW_HIDE);
	
	index = this->tabs.Push(tab);
	this->RecalcItemRect(index);
	this->Select(index);
	
	return index;
}

void CTab::Create(const CWindow &refParentWindow)
{
	SIZE size;

	CWindow::Create(WS_CLIPCHILDREN, 0, refParentWindow);
	
	this->theme.OpenData(*this, L"TAB");
	
	//Get height of tabbar
	this->theme.GetPartSize(TABP_TABITEM, TIS_SELECTED, TS_TRUE, &size);
	this->tabHeight = (uint16)size.cy;

	//Font
	this->font.LoadSystemFont(DEFAULT_GUI_FONT);
}

void CTab::Release()
{
	this->activeTabIndex = 0;
	this->tabs.Release();
}

void CTab::Select(uint32 index)
{
	ASSERT(index < this->tabs.GetNoOfElements());

	ASSERTMSG(0, "must be reimplemented, because of CPOINTER");
	/*
	this->tabs[this->activeTabIndex].pTabChild->Show(SW_HIDE);

	this->activeTabIndex = index;
	this->OnSize(0, 0, 0);
	
	this->tabs[this->activeTabIndex].pTabChild->Show(SW_SHOW);
	this->tabs[this->activeTabIndex].pTabChild->Focus();
	*/
}