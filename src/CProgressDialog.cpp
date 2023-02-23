//Class Header
#include "CProgressDialog.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
//Definitions
#define DIALOG_WIDTH 200
#define DIALOG_HEIGHT 70
#define DIALOG_SPACING 5
#define DIALOG_CONTROLHEIGHT 20

//Callbacks
void CProgressDialog::OnInit()
{
	this->progressBar.Create(0, *this);
	this->progressBar.SetPos(this->DialogToScreenUnits(CRect(DIALOG_SPACING, DIALOG_SPACING, DIALOG_WIDTH - DIALOG_SPACING, DIALOG_CONTROLHEIGHT)));

	this->progressBar.SetText("bla");

	this->percentage.Create("", SS_CENTER, *this);
	this->percentage.SetPos(this->DialogToScreenUnits(CRect(DIALOG_SPACING, DIALOG_SPACING + DIALOG_CONTROLHEIGHT + DIALOG_SPACING, DIALOG_WIDTH - DIALOG_SPACING, DIALOG_CONTROLHEIGHT)));
	this->percentage.SetFont(this->font);
}

void CProgressDialog::OnUserMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case CPROGRESSDIALOG_WM_ADVANCE:
		{
			this->progressBar.Advance((int32)lParam);
			this->percentage.SetText(CString(this->progressBar.GetPos()) + "%");
		}
		break;
	}
}

//Public Functions
void CProgressDialog::Create(const CString &refCaption, const CPopupWindow &refParentWindow)
{
	this->font.LoadSystemFont(DEFAULT_GUI_FONT);
	CDialog::Create(refCaption, WS_CAPTION | DS_MODALFRAME | DS_CENTER, 0, 0, DIALOG_WIDTH, DIALOG_HEIGHT, &refParentWindow, this->font);
}