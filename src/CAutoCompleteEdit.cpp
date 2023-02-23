//Class Header
#include "CAutoCompleteEdit.h"
//Local
#include "__CWindows.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Subclass procedure
LRESULT CALLBACK SJCLibIntern::EditSubclassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CAutoCompleteEdit *pCtrl;
	LRESULT result;
	
	pCtrl = (CAutoCompleteEdit *)CWindows::GetWindowPointer(hWnd);
	
	switch(msg)
	{
	case WM_SETFOCUS:
		result = CallWindowProc(pCtrl->origWndProc, hWnd, msg, wParam, lParam);
		pCtrl->dropDownWindow.SendMessageA(WM_SIZE, 0, 0);
		pCtrl->dropDownWindow.Show(SW_SHOWNA);
		return result;
	case WM_KILLFOCUS:
		result = CallWindowProc(pCtrl->origWndProc, hWnd, msg, wParam, lParam);
		pCtrl->dropDownWindow.Show(SW_HIDE);
		ReleaseCapture();
		return result;
	case WM_GETDLGCODE:
		return DLGC_WANTALLKEYS;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_TAB:
			pCtrl->Complete();
			return 0;
		case VK_RETURN:
			return 0;
		case VK_END:
		case VK_HOME:
		case VK_LEFT:
		case VK_RIGHT:
			result = CallWindowProc(pCtrl->origWndProc, hWnd, msg, wParam, lParam);
			pCtrl->Filter();
			return 0;
		case VK_UP:
			if(pCtrl->dropDownWindow.list.GetCurrentSelection() > 0)
				pCtrl->dropDownWindow.list.Select(pCtrl->dropDownWindow.list.GetCurrentSelection()-1);
			return 0;
		case VK_DOWN:
			if(pCtrl->dropDownWindow.list.GetCurrentSelection() < pCtrl->dropDownWindow.list.GetCount())
				pCtrl->dropDownWindow.list.Select(pCtrl->dropDownWindow.list.GetCurrentSelection()+1);
			return 0;
		}
		break;
	case WM_KEYUP:
	case WM_CHAR:
		switch(wParam)
		{
		case VK_TAB:
			return 0;
		case VK_RETURN:
			pCtrl->GetParent()->Focus();
			return 0;
		}
		break;
	case WM_LBUTTONUP:
		result = CallWindowProc(pCtrl->origWndProc, hWnd, msg, wParam, lParam);
		pCtrl->Filter();
		pCtrl->messageWindow.SetCapture();
		return 0;
	}

	return CallWindowProc(pCtrl->origWndProc, hWnd, msg, wParam, lParam);
}

//Message-callbacks
void CAutoCompleteEdit::OnChange()
{
	this->Filter();
}

//Private Functions
void CAutoCompleteEdit::Complete()
{
	CString editText, itemText;
	int32 index, prevPos, nextPos;
	
	index = this->dropDownWindow.list.GetCurrentSelection();
	prevPos = this->GetPreviousSeperator();
	nextPos = this->GetNextSeperator();
	itemText = this->dropDownWindow.list.GetItemText(index);
	editText = this->GetText();

	this->SetText(editText.SubString(0, prevPos) + itemText + editText.SubString(nextPos, editText.GetLength() - nextPos));
	CEdit::Select(prevPos + itemText.GetLength(), prevPos + itemText.GetLength());
	this->dropDownWindow.list.Clear();
	this->dropDownWindow.list.AddItem(itemText);
	this->dropDownWindow.list.Select(0);
}

void CAutoCompleteEdit::Filter()
{
	int32 prevPos, nextPos;
	CString filter;

	prevPos = this->GetPreviousSeperator();
	nextPos = this->GetNextSeperator();
	filter = this->GetText().SubString(prevPos, nextPos-prevPos).ToLowercase();
	
	this->dropDownWindow.list.Clear();
	repeat(this->choices.GetNoOfElements(), i)
	{
		if(this->choices[i].ToLowercase().Find(filter) != STRING_NOMATCH)
		{
			this->dropDownWindow.list.AddItem(this->choices[i]);
		}
	}
	this->dropDownWindow.list.Select(0);
}

int32 CAutoCompleteEdit::GetNextSeperator()
{
	CString text;
	int32 pos, nearestPos;

	text = this->GetText();
	nearestPos = text.GetLength();
	this->GetSelection((uint32 *)&pos, NULL);
	
	if((pos = text.Find(this->seperator, pos)) != STRING_NOMATCH)
	{
		if(pos < nearestPos)
		{
			nearestPos = pos;
		}
	}
	
	return nearestPos;
}

int32 CAutoCompleteEdit::GetPreviousSeperator()
{
	CString text;
	int32 pos, nearestPos = 0;
	uint32 searchPos;

	text = this->GetText();
	this->GetSelection(&searchPos, NULL);
	searchPos--;
	if((int32)searchPos < 0 || this->seperator.IsEmpty())
		return 0;
	
	if((pos = text.FindReverse(this->seperator, searchPos)) != STRING_NOMATCH)
	{
		if(pos > nearestPos)
		{
			nearestPos = pos + this->seperator.GetLength();
		}
	}
	return nearestPos;
}

//Public Functions
void CAutoCompleteEdit::AddChoice(CString text)
{
	this->choices.Push(text);
	//this->Filter();
}

void CAutoCompleteEdit::Create(uint32 styleFlags, uint32 exStyleFlags, uint16 x, uint16 y, uint16 width, uint16 height, const CWindow &refParentWindow)
{
	ASSERT(0);
	//CEdit::Create("", styleFlags, exStyleFlags, x, y, width, height, refParentWindow);
	this->dropDownWindow.Create(this);
	this->messageWindow.Create(this);
	this->origWndProc = (WNDPROC)SetWindowLongPtr(this->hWnd, GWLP_WNDPROC, (LONG_PTR)EditSubclassProc);
}

void CAutoCompleteEdit::SetFont(const SJCWinLib::CFont &refFont)
{
	CWindow::SetFont(refFont);
	this->dropDownWindow.list.SetFont(refFont);
}

void CAutoCompleteEdit::SetSeperator(CString text)
{
	this->seperator = text;
}


/*//Local
#include "CPaintDC.h"
using namespace SJCLib;
//Definitions
#define CAUTOCOMPLETEEDIT_CLASSNAME "CAutoCompleteEdit"
#define STYLE_AUTOSCROLLBY 5
#define STYLE_SPACING 2

//Constructor
CAutoCompleteEdit::CAutoCompleteEdit()
{
	this->caretCharPos = 0;
	this->drawFrom = 0;
	MemZero(&this->fontMetrics, sizeof(this->fontMetrics));
}

//Message-callbacks
void CAutoCompleteEdit::OnChar(uint16 characterCode, uint16 repeatCount, byte scanCode, bool isExtendedKey, bool isAltKeyPressed, bool previousKeyState, bool transitionTable)
{
	switch(characterCode)
	{
		//Special chars first
	case VK_BACK:
		if(this->caretCharPos > 0)
		{
			this->text = this->text.SubString(0, this->caretCharPos-1) + this->text.SubString(this->caretCharPos, this->text.GetLength() - this->caretCharPos);
			this->caretCharPos--;

			this->UpdateCaretPos();
			this->Invalidate();
			this->Filter();
		}
		break;
	case VK_TAB:
		this->Complete();
		break;
	case VK_RETURN:
		this->GetParent()->Focus();
		break;
	default: //Normal char
		this->AddChar((char)characterCode);
	}
}

void CAutoCompleteEdit::OnFocus(CWindow *pPreviousFocusedWindow)
{
	this->CreateSolidCaret(1, (uint16)this->fontMetrics.tmHeight);
	this->ShowCaret();
	this->dropDownWindow.SendMessageA(WM_SIZE, 0, 0);
	this->dropDownWindow.Show(SW_SHOWNA);
	this->messageWindow.SetCapture();
}

void CAutoCompleteEdit::OnKeyDown(uint16 characterCode, uint16 repeatCount, byte scanCode, bool isExtendedKey, bool previousKeyState)
{
	switch(characterCode)
	{
	case VK_LEFT:
		if(this->caretCharPos > 0)
		{
			this->caretCharPos--;
			this->UpdateCaretPos();
			this->Filter();
		}
		break;
	case VK_UP:
		if(this->dropDownWindow.list.GetCurrentSelection() > 0)
			this->dropDownWindow.list.Select(this->dropDownWindow.list.GetCurrentSelection()-1);
		break;
	case VK_RIGHT:
		if(this->caretCharPos < this->text.GetLength())
		{
			this->caretCharPos++;
			
			this->UpdateCaretPos();
			this->Filter();
		}
		break;
	case VK_DOWN:
		if(this->dropDownWindow.list.GetCurrentSelection() < this->dropDownWindow.list.GetCount())
			this->dropDownWindow.list.Select(this->dropDownWindow.list.GetCurrentSelection()+1);
		break;
	case VK_DELETE://DÜPPEL AB HIER
		if(this->caretCharPos < this->text.GetLength())
		{
			this->text = this->text.SubString(0, this->caretCharPos) + this->text.SubString(this->caretCharPos+1, this->text.GetLength() - this->caretCharPos -1);
			this->Invalidate();
			this->Filter();
		}
		break;
	case VK_END:
		this->caretCharPos = this->text.GetLength();
		this->UpdateCaretPos();
		this->Filter();
		break;
	case VK_HOME:
		this->caretCharPos = 0;
		this->UpdateCaretPos();
		this->Filter();
		break;
	}
}

void CAutoCompleteEdit::OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y)
{
	this->Focus();
	this->UpdateCaretPos(x);
	this->Filter();
}

void CAutoCompleteEdit::OnLooseFocus(CWindow *pUpcomingFocusedWindow)
{
	this->dropDownWindow.Show(SW_HIDE);
	DestroyCaret();
	ReleaseCapture();
}

uint32 CAutoCompleteEdit::OnGetDialogCode(uint16 virtualKeyCode)
{
	return DLGC_WANTALLKEYS;
}

void CAutoCompleteEdit::OnPaint()
{
	CPaintDC dc(this);
	CRect rcClient, rcText;
	CColor backgroundColor;
	
	this->GetClientRect(&rcClient);
	dc.SelectObject(font);
	
	rcText.left = STYLE_SPACING;
	rcText.top = STYLE_SPACING;
	rcText.bottom = rcClient.bottom - STYLE_SPACING;
	rcText.right = rcClient.right - STYLE_SPACING;
	
	backgroundColor = CColor::GetSystemColor(COLOR_WINDOW);
	
	dc.SetBackgroundColor(backgroundColor);
	dc.SetTextColor(CColor::GetSystemColor(COLOR_WINDOWTEXT));
	dc.FillSolidRect(rcClient, backgroundColor);
	
	dc.DrawTextA(this->text.SubString(this->drawFrom, this->GetNumberOfCharsToFit()), &rcText, DT_SINGLELINE);
}

void CAutoCompleteEdit::OnSetFont(const CFont &refFont)
{
	CPointer<CDeviceContext> pDC;

	this->font = refFont;
	pDC = this->GetDC();
	pDC->SelectObject(refFont);
	pDC->GetTextMetricsA(&this->fontMetrics);

	this->dropDownWindow.SetFont(refFont);
}

//Private Functions
void CAutoCompleteEdit::AddChar(char c)
{
	if(this->caretCharPos == 0) //Caret is at the beginning
		this->text = c + this->text;
	else if(this->caretCharPos == this->text.GetLength()) //Caret is at the end
		this->text += c;
	else //Caret is somewhere in between the text
		this->text = this->text.SubString(0, this->caretCharPos) + c + this->text.SubString(this->caretCharPos, this->text.GetLength() - this->caretCharPos);
	
	this->caretCharPos++;

	if(this->caretCharPos == this->text.GetLength() && this->text.GetLength() > this->GetNumberOfCharsToFit())
		this->drawFrom++;
	
	this->UpdateCaretPos();
	this->Invalidate();
	this->Filter();
}

uint16 CAutoCompleteEdit::GetNumberOfCharsToFit()
{
	CPointer<CDeviceContext> pDC;
	CRect rcCalc, rcClient;
	uint32 width, textAreaWidth;
	
	this->GetClientRect(&rcClient);
	width = 2*STYLE_SPACING;
	textAreaWidth = rcClient.right;
	pDC = this->GetDC();
	pDC->SelectObject(this->font);

	for(uint32 i = this->drawFrom; i < this->text.GetLength(); i++)
	{
		pDC->DrawTextA(this->text[i], &rcCalc, DT_CALCRECT);
		if(width >= textAreaWidth)
			return i - this->drawFrom-1;
		width += rcCalc.right;
	}

	return this->text.GetLength() - this->drawFrom;
}

void CAutoCompleteEdit::Scroll(bool left)
{
	if(left)
	{
		if((int32)this->drawFrom - STYLE_AUTOSCROLLBY < 0)
			this->drawFrom = 0;
		else
			this->drawFrom -= STYLE_AUTOSCROLLBY;
	}
	else
	{
		if(this->drawFrom + this->GetNumberOfCharsToFit() + STYLE_AUTOSCROLLBY > this->text.GetLength())
			this->drawFrom = this->text.GetLength() - this->GetNumberOfCharsToFit();
		else
			this->drawFrom += STYLE_AUTOSCROLLBY;
	}
	this->Invalidate();
}

void CAutoCompleteEdit::UpdateCaretPos()
{
	CPointer<CDeviceContext> pDC;
	CRect rcCalc;
	uint32 drawTo;
	
	pDC = this->GetDC();
	pDC->SelectObject(this->font);

	//Ensure that the caret is visible
	drawTo = this->drawFrom + this->GetNumberOfCharsToFit();
	if(this->caretCharPos > this->drawFrom && this->caretCharPos < drawTo)
	{
		if(this->caretCharPos > this->drawFrom)
			this->Scroll(true);
		else
			this->Scroll(false);
	}
	
	pDC->DrawText(this->text.SubString(this->drawFrom, this->caretCharPos - this->drawFrom), &rcCalc, DT_CALCRECT);
	SetCaretPos(STYLE_SPACING + rcCalc.right, STYLE_SPACING);
}

void CAutoCompleteEdit::UpdateCaretPos(uint16 x)
{
	CPointer<CDeviceContext> pDC;
	CRect rcCalc;
	int32 pos = STYLE_SPACING;
	uint16 i;
	
	pDC = this->GetDC();
	pDC->SelectObject(this->font);
	
	for(i = this->drawFrom; i < this->text.GetLength(); i++)
	{
		pDC->DrawText(this->text[i], &rcCalc, DT_CALCRECT);
		if(pos >= x)
			break;
		pos += rcCalc.right;
	}
	this->caretCharPos = i;
	SetCaretPos(pos, STYLE_SPACING);
}

//Public Functions
void CAutoCompleteEdit::Create(uint32 styleFlags, uint32 exStyleFlags, uint16 x, uint16 y, uint16 width, uint16 height, const CWindow &refParentWindow)
{
	CBrush backgroundBrush;
	
	backgroundBrush.CreateSystemColorBrush(COLOR_WINDOW);
	refParentWindow.GetModule().RegisterWindowClass(&backgroundBrush, LoadCursor(NULL, IDC_IBEAM), NULL, NULL, CAUTOCOMPLETEEDIT_CLASSNAME);
	CWindow::Create(CAUTOCOMPLETEEDIT_CLASSNAME, "", WS_VISIBLE | WS_CHILD | styleFlags, exStyleFlags, x, y, width, height, refParentWindow);
}
*/