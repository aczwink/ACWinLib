//Class Header
#include "CMultiSelectDropDown.h"
//Local
#include "CPaintDC.h"
#include "CTheme.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
//Definitions
#define CMULTISELECTDROPDOWN_CLASSNAME "CMultiSelectDropDown"
#define STYLE_ARROWWIDTH 20
#define STYLE_INNERPADDING 2

//Constructor
CMultiSelectDropDown::CMultiSelectDropDown()
{
	this->state = CBXS_NORMAL;
}

//Message-callbacks
void CMultiSelectDropDown::OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y)
{
	this->state = CBXS_PRESSED;
	this->Invalidate();
	this->dropDownWindow.OnSize(0, 0, 0);
	this->dropDownWindow.Show(SW_SHOWNA);
	this->messageWindow.SetCapture();
}

void CMultiSelectDropDown::OnPaint()
{
	CPaintDC dc(this);
	CTheme theme;
	CRect rcClient, rcText, rcArrow;
	CString displayText;
	CArray<uint16> selection;

	//Set the draw areas
	this->GetClientRect(rcClient);

	rcText.left = rcClient.left + STYLE_INNERPADDING;
	rcText.top = rcClient.top + STYLE_INNERPADDING;
	rcText.right = rcClient.right - STYLE_INNERPADDING - STYLE_ARROWWIDTH;
	rcText.bottom = rcClient.bottom - STYLE_INNERPADDING;

	rcArrow = rcClient;
	rcArrow.left = rcArrow.right - 20;

	//Draw the Control
	theme.OpenData(*this, L"COMBOBOX");
	if(theme.IsBackgroundPartiallyTransparent(CP_BACKGROUND, this->state))
	{
		theme.DrawParentBackground(*this, dc, rcClient);
	}
	theme.DrawBackground(dc, CP_BACKGROUND, this->state, rcClient, NULL);
	theme.DrawBackground(dc, CP_DROPDOWNBUTTONRIGHT, this->state, rcArrow, NULL);
	
	//Set the current font
	dc.SelectObject(font);

	//Fetch the text
	selection = this->dropDownWindow.list.GetSelection();
	repeat(selection.GetNoOfElements(), i)
	{
		displayText += this->dropDownWindow.list.GetItemText(selection[i]) + ", ";
	}
	if(displayText.GetLength())
		displayText = displayText.SubString(0, displayText.GetLength()-2);
	
	//Draw the box with the text
	dc.SetBackgroundMode(false);
	dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
	dc.DrawTextA(displayText, rcText, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
}

void CMultiSelectDropDown::OnSetFont(const SJCWinLib::CFont &refFont)
{
	this->font = refFont;
	this->dropDownWindow.list.SetFont(this->font);
}

//Public Functions
uint32 CMultiSelectDropDown::AddItem(CString text)
{
	return this->dropDownWindow.list.AddItem(text);
}

void CMultiSelectDropDown::Create(uint32 styleFlags, int32 x, int32 y, int32 width, int32 height, const CWindow &refParentWindow)
{
	CBrush brush;
	CCursor cursor;
	
	brush.CreateSystemColorBrush(COLOR_WINDOW+1);
	cursor.LoadSystemCursor(IDC_ARROW);
	//refParentWindow.GetModule().RegisterWindowClass(&brush, &cursor, NULL, NULL, CMULTISELECTDROPDOWN_CLASSNAME);
	ASSERT(false);
	//CWindow::Create(CMULTISELECTDROPDOWN_CLASSNAME, "", WS_VISIBLE | WS_CHILD | styleFlags, 0, x, y, width, height, refParentWindow);
	this->dropDownWindow.Create(*this);
	this->messageWindow.Create(*this);
}

uint64 CMultiSelectDropDown::GetItemData(uint32 index) const
{
	return this->dropDownWindow.list.GetItemData(index);
}

CArray<uint16> CMultiSelectDropDown::GetSelection() const
{
	return this->dropDownWindow.list.GetSelection();
}

void CMultiSelectDropDown::Select(uint32 index)
{
	this->dropDownWindow.list.Select(index);
}

void CMultiSelectDropDown::SetItemData(uint32 index, uint64 value)
{
	this->dropDownWindow.list.SetItemData(index, value);
}

/*
//Global
#include <CommCtrl.h>
//Local
#include "__CWindows.h"
#include "CPaintDC.h"
#include "CTheme.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCLibString;
using namespace SJCLibWindows;

//Public Functions
void CMultiSelectDropDown::Select(CArray<uint16> indexList)
{
	this->dropDownWindow.list.Select(indexList);
}*/