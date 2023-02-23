//Class Header
#include "CStatic.h"
//Local
#include "CPaintDC.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
//Definitions
#define CSTATIC_WNDCLASS "CStatic"

//Message-callbacks
void CStatic::OnPaint()
{
	CPaintDC dc(this);
	CRect rcClient/*, rcText*/;
	uint32 flags/*, currentPos, nextPos*/;
	//TEXTMETRIC tm;

	flags = 0;
	//currentPos = 0;
	this->GetClientRect(rcClient);
	//rcText = rcClient;

	switch(this->alignment)
	{
	case ALIGN_CENTER:
		flags |= DT_CENTER;
		break;
	case ALIGN_RIGHT:
		flags |= DT_RIGHT;
		break;
	}

	dc.SelectObject(this->font);
	//dc.GetTextMetricsA(&tm);
	dc.SetBackgroundMode(false);
	//dc.SetBackgroundColor(CColor::GetSystemColor(COLOR_WINDOW));
	dc.SetTextColor(this->textColor);
	//dc.FillSolidRect(rcClient, CColor::GetSystemColor(COLOR_WINDOW));

	dc.DrawTextA(this->text, rcClient, flags | DT_END_ELLIPSIS);

	/*while(true)
	{
		nextPos = this->text.Find("\n", currentPos);

		dc.DrawTextA(this->text.SubString(currentPos, nextPos - currentPos), &rcText, flags | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);

		currentPos = nextPos;
		rcText.left = 0;
		rcText.top += tm.tmHeight;
	}*/
}

void CStatic::OnSetFont(const SJCWinLib::CFont &refFont)
{
	this->font = refFont;
}

//Public Functions
void CStatic::Create(CString text, uint32 styleFlags, const CWindow &refParentWindow)
{
	CFont font;

	this->alignment = ALIGN_LEFT;
	this->text = text;

	this->textColor = CColor::GetSystemColor(COLOR_WINDOWTEXT);
	font.LoadSystemFont(DEFAULT_GUI_FONT);

	CWindow::Create(styleFlags, 0, refParentWindow);
	
	this->OnSetFont(font);
}

void CStatic::SetText(CString text)
{
	this->text = text;
	this->Invalidate();
}