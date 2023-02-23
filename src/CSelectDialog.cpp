//Class Header
#include "CSelectDialog.h"
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

//CSelectList Message-callbacks
void CSelectList::OnChangeSelection()
{
	CSelectDialog *pDlg;

	pDlg = (CSelectDialog *)this->GetParent();
	pDlg->buttonOK.Enable();
}

//CSelectDialogButtonOK Message-callbacks
void CSelectDialogButtonOK::OnClick()
{
	CSelectDialog *pDialog = ((CSelectDialog *)this->GetParent());
	
	pDialog->selection = pDialog->selectBox.GetSelection();
	pDialog->End(IDOK);
}

//Message-callbacks
void CSelectDialog::OnInit()
{
	this->selectBox.CreateDropDownList(0, *this);
	this->selectBox.SetFont(font);
	this->selectBox.SetPos(this->DialogToScreenUnits(CRect(DIALOG_SPACING, DIALOG_SPACING, DIALOG_WIDTH - DIALOG_SPACING, DIALOG_SPACING + DIALOG_CONTROLHEIGHT)));

	foreach(it, this->selections)
	{
		this->selectBox.AddItem(*it);
	}
	this->selectBox.Select(this->selection);
	
	this->buttonOK.Create("OK", 0, *this);
	this->buttonOK.SetFont(font);
	this->buttonOK.Enable(false);
	this->buttonOK.SetPos(this->DialogToScreenUnits(CRect().Init(10, 25, DIALOG_BUTTONWIDTH, DIALOG_CONTROLHEIGHT)));
	
	this->buttonCancel.Create("Cancel", 0, *this);
	this->buttonCancel.SetFont(font);
	this->buttonCancel.SetPos(this->DialogToScreenUnits(CRect().Init(90, 25, DIALOG_BUTTONWIDTH, DIALOG_CONTROLHEIGHT)));

	this->buttonOK.SetDefault();
	this->SetFocus(this->selectBox);
}

//Public Functions
void CSelectDialog::AddSelection(CString title)
{
	this->selections.Push(title);
}

void CSelectDialog::Create(CString caption, const CWindow &refParentWindow)
{
	this->font.LoadSystemFont(DEFAULT_GUI_FONT);
	CDialog::Create(caption, WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | DS_MODALFRAME | DS_CENTER, 0, 0, DIALOG_WIDTH, DIALOG_HEIGHT, &refParentWindow, this->font);
}

int32 CSelectDialog::GetSelection()
{
	return this->selection;
}

void CSelectDialog::PreSelect(uint32 index)
{
	this->selection = index;
}