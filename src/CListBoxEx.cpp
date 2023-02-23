/*//Class Header
#include "CListBoxEx.h"
//Local
#include "CBrush.h"
#include "CPaintDC.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCLibString;
using namespace SJCLibWindows;
//Definitions
#define INNERCOLUMNPADDING_DEFAULT 5
#define INNERCELLPADDING_DEFAULT 5

//Constructor
CListBoxEx::CListBoxEx()
{
	this->columnRowHeight = 0;
	this->fontHeight = 0;
	this->selection = SELECTION_NONE;
	this->style.innerCellPadding = INNERCELLPADDING_DEFAULT;
	this->style.innerColumnPadding = INNERCOLUMNPADDING_DEFAULT;

	this->UpdateFontHeight();

	this->AddColumn("");
}

//Callbacks
void CListBoxEx::OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y)
{
	this->selection = this->FindElementFromHeight(this->GetBasePos(this->GetScrollPos()) + y - this->columnRowHeight);
	this->Invalidate();
}

void CListBoxEx::OnMouseWheel(int16 zDelta, uint16 keys)
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

void CListBoxEx::OnPaint()
{
	CPaintDC dc(this);
	CSmartPointer<CDeviceContext> pMemDC;
	CSmartPointer<CBitmap> pBackbufferBmp;
	CRect rcClient, rcColumnRow, rcColumn, rcRow, rcCell;
	RECT rcContent;
	uint16 columnWidth, rowHeight;
	CFont columnFont;
	LOGFONT columnFontAttrib;
	TEXTMETRIC tm;

	this->GetClientRect(&rcClient);
	pMemDC = dc.CreateCompatibleDC();
	pBackbufferBmp = dc.CreateCompatibleBitmap(rcClient.GetWidth(), rcClient.GetHeight());
	pMemDC->SelectObject(pBackbufferBmp);

	pMemDC->FillSolidRect(&rcClient, CColor::GetSystemColor(COLOR_WINDOW));

	//Draw Columns
	this->font.GetFontAttributes(&columnFontAttrib);
	columnFontAttrib.lfWeight = FW_BOLD;
	columnFont.Create(&columnFontAttrib);
	pMemDC->SelectObject(&columnFont);
	pMemDC->GetTextMetrics(&tm);

	rcColumnRow.left = rcClient.left;
	rcColumnRow.top = rcClient.top;
	rcColumnRow.right = rcClient.right;
	rcColumnRow.bottom = tm.tmHeight + this->style.innerColumnPadding + 1;

	this->columnRowHeight = (uint16)rcColumnRow.GetHeight();

	rcContent.left = rcClient.left;
	rcContent.top = rcColumnRow.top + rcColumnRow.bottom;
	rcContent.right = rcClient.right;
	rcContent.bottom = rcClient.bottom;

	pMemDC->FillSolidRect(&rcColumnRow, CColor::GetSystemColor(COLOR_3DFACE));
	pMemDC->SetBackgroundColor(GetSysColor(COLOR_3DFACE));
	pMemDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));

	pMemDC->MoveTo(rcColumnRow.left, rcColumnRow.bottom);
	pMemDC->LineTo(rcColumnRow.right, rcColumnRow.bottom);

	rcColumn.left = rcColumnRow.left + this->style.innerColumnPadding;
	rcColumn.top = rcColumnRow.top;
	rcColumn.right = 0;
	rcColumn.bottom = rcColumnRow.bottom;

	repeat(this->columns.GetLength(), i)
	{
		if(this->columns[i].width == COLUMN_AUTOSIZE)
		{
			columnWidth = this->CalculateAutoColumnSize(i);
		}
		else
		{
			columnWidth = this->columns[i].width;
		}

		rcColumn.right += columnWidth;

		pMemDC->DrawText(this->columns[i].caption, &rcColumn, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS);

		pMemDC->MoveTo(rcColumn.right, rcClient.top);
		pMemDC->LineTo(rcColumn.right, rcClient.bottom);

		rcColumn.left += columnWidth;
	}

	//Draw Cells
	rcRow.left = rcClient.left;
	rcRow.top = 0; //Will be set in loop
	rcRow.right = rcClient.right;
	rcRow.bottom = rcColumnRow.top + rcColumnRow.bottom; //Will also be set in loop

	pMemDC->SelectObject(&this->font);
	
	for(uint32 i = this->FindElementFromHeight(this->GetScrollPos()); i < this->cells.GetLength(); i++)
	{
		rowHeight = this->GetRowHeight(i);

		rcRow.top = rcRow.bottom+1;
		rcRow.bottom += rowHeight;

		rcCell.left = rcRow.left + this->style.innerCellPadding;
		rcCell.top = rcRow.top + this->style.innerCellPadding;
		rcCell.right = 0;
		rcCell.bottom = rcRow.bottom - this->style.innerCellPadding;

		if(i == this->selection)
		{
			pMemDC->FillSolidRect(&rcRow, CColor::GetSystemColor(COLOR_HIGHLIGHT));			
			pMemDC->SetBackgroundColor(GetSysColor(COLOR_HIGHLIGHT));
			pMemDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
		}
		else
		{
			pMemDC->SetBackgroundColor(GetSysColor(COLOR_WINDOW));
			pMemDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		}

		repeat(this->columns.GetLength(), j)
		{
			if(this->columns[j].width == COLUMN_AUTOSIZE)
			{
				columnWidth = this->CalculateAutoColumnSize(j);
			}
			else
			{
				columnWidth = this->columns[j].width;
			}

			rcCell.right += columnWidth;

			pMemDC->DrawText(this->cells[i][j], &rcCell, DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS);

			if(i == selection)
			{
				//Redraw overdrawn lines
				pMemDC->MoveTo(rcCell.right, rcRow.top);
				pMemDC->LineTo(rcCell.right, rcRow.bottom);
			}
			
			rcCell.left += columnWidth;
		}

		pMemDC->MoveTo(rcRow.left, rcRow.bottom);
		pMemDC->LineTo(rcRow.right, rcRow.bottom);
	}

	//Copy Backbuffer into Foreground
	dc.BitBlt(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom, pMemDC, 0, 0, SRCCOPY);
	pBackbufferBmp->Release();
	pMemDC->Release();

	//Update Scrollbars
	this->SetScrollRange(this->GetOverallHeight());
	this->SetScrollPageSize(rcContent.bottom - rcContent.top);
}

void CListBoxEx::OnSetFont(CFont *pFont)
{
	this->font = *pFont;

	this->UpdateFontHeight();
}

void CListBoxEx::OnVerticalScroll(uint16 scrollCode)
{
	uint16 element, elementHeight;
	uint32 scrollRange, oldScrollPos, newScrollPos;

	scrollRange = this->GetScrollRange();
	oldScrollPos = this->GetScrollPos();
	element = this->FindElementFromHeight(oldScrollPos);
	elementHeight = this->GetRowHeight(element);

	switch(scrollCode)
	{
	case SB_PAGEUP:
	case SB_LINEUP:
		if(element > 0)
		{
			newScrollPos = oldScrollPos - elementHeight;
		}
		else
		{
			newScrollPos = 0;
		}
		break;
	case SB_PAGEDOWN:
	case SB_LINEDOWN:
		if(element >= this->cells.GetLength())
		{
			newScrollPos = scrollRange;
		}
		else
		{
			newScrollPos = oldScrollPos + elementHeight;
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
	this->Invalidate(false);
}

//Private Functions
uint16 CListBoxEx::CalculateAutoColumnSize(uint16 columnIndex)
{
	CDeviceContext dc;
	CSmartPointer<CDeviceContext> pMemDC;
	CFont columnFont;
	LOGFONT columnFontAttrib;
	CRect rc;
	uint16 columnSize, maxSize = 0;
	
	dc.GetDC(this);
	pMemDC = dc.CreateCompatibleDC();

	this->font.GetFontAttributes(&columnFontAttrib);
	columnFontAttrib.lfWeight = FW_BOLD;
	columnFont.Create(&columnFontAttrib);
	
	pMemDC->SelectObject(&columnFont);

	pMemDC->DrawText(this->columns[columnIndex].caption, &rc, DT_CALCRECT);
	columnSize = (uint16)rc.right;
	maxSize = columnSize;

	pMemDC->SelectObject(&this->font);

	repeat(this->cells.GetLength(), i)
	{
		pMemDC->DrawText(this->cells[i][columnIndex], &rc, DT_CALCRECT);

		if(rc.right > maxSize)
		{
			maxSize = (uint16)rc.right;
		}
	}

	pMemDC->Release();
	if(maxSize == columnSize)
	{
		maxSize += 2 * this->style.innerColumnPadding;
	}
	else
	{
		maxSize += 2 * this->style.innerCellPadding;
	}

	this->columns[columnIndex].width = maxSize;

	return maxSize;
}

uint16 CListBoxEx::FindElementFromHeight(uint32 pos)
{
	uint32 size = 0;
	uint32 i = 0;

	for(; i < this->cells.GetLength(); i++)
	{
		size += this->GetRowHeight(i);

		if(size > pos)
		{
			return i;
		}
	}

	return SELECTION_NONE;
}

uint32 CListBoxEx::GetBasePos(uint32 pos)
{
	uint32 basePos = 0;
	uint16 height = 0;

	repeat(this->cells.GetLength(), i)
	{
		if(basePos >= pos)
		{
			return basePos - height;
		}

		height = this->GetRowHeight(i);

		basePos += height;
	}

	return basePos;
}

uint32 CListBoxEx::GetOverallHeight()
{
	uint32 height = 0;
	repeat(this->cells.GetLength(), i)
	{
		height += this->GetRowHeight(i);
	}

	return height;
}

uint16 CListBoxEx::GetRowHeight(uint16 rowIndex)
{
	uint16 nMaxLines = 1;
	uint16 nLines;
	
	repeat(this->columns.GetLength(), i)
	{
		CString &tmp = this->cells[rowIndex][i];
		nLines = 1;

		repeat(tmp.GetLength(), i)
		{
			if(tmp[i] == '\n')
			{
				nLines++;
			}
		}

		if(nLines > nMaxLines)
		{
			nMaxLines = nLines;
		}
	}

	return nMaxLines * this->fontHeight + 2 * this->style.innerCellPadding + 1 + 1;
}

void CListBoxEx::UpdateFontHeight()
{
	CDeviceContext dc;
	CSmartPointer<CDeviceContext> pMemDC;
	TEXTMETRIC tm;

	dc.GetDC(this);
	pMemDC = dc.CreateCompatibleDC();

	pMemDC->SelectObject(&this->font);
	pMemDC->GetTextMetrics(&tm);

	this->fontHeight = (uint16)tm.tmHeight;

	pMemDC->Release();
}

//Public Functions
void CListBoxEx::AddColumn(CString caption, uint16 width)
{
	ListBoxExColumn column;

	column.caption = caption;
	column.width = width;

	this->columns.Push(column);

	repeat(this->cells.GetLength(), i)
	{
		this->cells[i].Push("");
	}
}

void CListBoxEx::AddRow(CString text)
{
	CArray<CString> arr;

	arr.Push(text);

	for(uint32 i = 1; i < this->columns.GetLength(); i++)
	{
		arr.Push("");
	}

	this->cells.Push(arr);

	this->Invalidate();
}

SJCLibResult CListBoxEx::Create(DWORD style, int x, int y, int width, int height, CWindow *pParentWindow)
{
	CBrush backgroundBrush;

	backgroundBrush.CreateSystemColorBrush(COLOR_WINDOW);
	pParentWindow->GetModule().RegisterWindowClass(&backgroundBrush, LoadCursor(NULL, IDC_ARROW), NULL, NULL, CLISTBOXEX_CLASSNAME);

	return CWindow::Create(CLISTBOXEX_CLASSNAME, "", WS_VISIBLE | WS_CHILD | WS_VSCROLL | style, 0, x, y, width, height, pParentWindow);
}

uint16 CListBoxEx::GetColumnWidth(uint16 columnIndex)
{
	return this->columns[columnIndex].width;
}

uint16 CListBoxEx::GetRowCount()
{
	return this->cells.GetLength();
}

void CListBoxEx::SetCellText(uint16 rowIndex, uint16 columnIndex, CString text)
{
	this->cells[rowIndex][columnIndex] = text;
}

void CListBoxEx::SetColumnText(uint16 index, CString caption)
{
	this->columns[index].caption = caption;
}

void CListBoxEx::SetColumnWidth(uint16 index, uint16 width)
{
	this->columns[index].width = width;
}

void CListBoxEx::SetControlStyle(CListBoxExStyle style, int32 value)
{
	switch(style)
	{
	case CLISTBOXEXSTYLE_INNERCELLPADDING:
		this->style.innerCellPadding = value;
		break;
	}
}*/