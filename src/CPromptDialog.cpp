//Class Header
#include "CPromptDialog.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCWinLib;
//Definitions
#define DIALOG_WIDTH 150
#define DIALOG_HEIGHT 45
#define DIALOG_SPACING 5
#define DIALOG_CONTROLHEIGHT 14
#define DIALOG_BUTTONWIDTH 50

//CPromptDialogButtonOK Message-callbacks
void CPromptDialogButtonOK::OnClick()
{
	CPromptDialog *pDialog = ((CPromptDialog *)this->GetParent());
	
	pDialog->text = pDialog->editText.GetText();
	
	pDialog->End(IDOK);
}

//Message-callbacks
void CPromptDialog::OnInit()
{
	this->editText.Create(WS_TABSTOP | ES_AUTOHSCROLL, *this);
	this->editText.SetFont(font);
	if(this->hasTextLimit)
		this->editText.SetTextLimit(this->textLimit);
	this->editText.SetText(this->text);
	this->editText.SetPos(this->DialogToScreenUnits(CRect(DIALOG_SPACING, DIALOG_SPACING, DIALOG_WIDTH - DIALOG_SPACING, DIALOG_SPACING + DIALOG_CONTROLHEIGHT)));
	
	this->buttonOK.Create("OK", WS_TABSTOP, *this);
	this->buttonOK.SetFont(font);
	this->buttonOK.SetPos(this->DialogToScreenUnits(CRect().Init(10, 25, DIALOG_BUTTONWIDTH, DIALOG_CONTROLHEIGHT)));
	
	this->buttonCancel.Create("Cancel", WS_TABSTOP, *this);
	this->buttonCancel.SetFont(font);
	this->buttonCancel.SetPos(this->DialogToScreenUnits(CRect().Init(90, 25, DIALOG_BUTTONWIDTH, DIALOG_CONTROLHEIGHT)));

	this->buttonOK.SetDefault();
	this->SetFocus(this->editText);
}

//Public Functions
void CPromptDialog::Create(CString caption, CString value, const CWindow *pParentWindow)
{
	this->font.LoadSystemFont(DEFAULT_GUI_FONT);
	this->text = value;
	CDialog::Create(caption, WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | DS_MODALFRAME | DS_CENTER, 0, 0, DIALOG_WIDTH, DIALOG_HEIGHT, pParentWindow, this->font);
}

CString CPromptDialog::GetValue()
{
	return this->text;
}