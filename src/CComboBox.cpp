//Class Header
#include "CComboBox.h"
//Global
#include <iostream>
#include <CommCtrl.h>
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
//Definitions
#define CTHIS ((CComboBox *)this)

//Message-callbacks
void CComboBox::OnCommand(WPARAM wParam)
{
	switch(HIWORD(wParam))
	{
	case CBN_SELCHANGE:
		this->OnChangeSelection();
		break;
	}
}

void CComboBox::OnChangeSelection()
{
}

//Public Functions
uint32 CComboBox::AddItem(CString text)
{
	return (uint32)this->SendMessageA(CB_ADDSTRING, 0, (LPARAM)text.GetC_Str());
}

uint64 CComboBox::GetItemData(uint32 index) const
{
	return CTHIS->SendMessageA(CB_GETITEMDATA, index, 0);
}

int32 CComboBox::GetSelection() const
{
	return (int32)((CComboBox *)this)->SendMessageA(CB_GETCURSEL, 0, 0);
}

CString CComboBox::GetText(uint32 index) const
{
	int32 length;
	char *pBuffer;
	CString result;
	
	length = (int32)((CComboBox *)this)->SendMessageA(CB_GETLBTEXTLEN, index, 0);
	if(length)
	{
		pBuffer = (char *)malloc(length+1);
		((CComboBox *)this)->SendMessageA(CB_GETLBTEXT, index, (LPARAM)pBuffer);
		result.Assign(pBuffer, length);
		free(pBuffer);
		
		return result;
	}
	return CString();
}

void CComboBox::Select(uint32 index)
{
	this->SendMessageA(CB_SETCURSEL, index, 0);
}

void CComboBox::SetCueBanner(CWString text)
{
	this->SendMessageA(CB_SETCUEBANNER, 0, (LPARAM)text.GetC_Str());
}

void CComboBox::SetItemData(uint32 index, uint64 value) const
{
	CTHIS->SendMessageA(CB_SETITEMDATA, index, value);
}

/*
//Namespaces
using namespace SJCLib;
using namespace SJCLibString;
using namespace SJCLibWindows;

//Public Functions

//Check Usage
/*
uint comboBoxControl::GetCount()
{
	return this->SendMessageA(CB_GETCOUNT, 0, 0);
}

WNDPROC comboBoxControl::subclass(WNDPROC newProcedure)
{
	return (WNDPROC)SetWindowLong(this->hWnd, GWL_WNDPROC, (LONG)newProcedure);
}
*/