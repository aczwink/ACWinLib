//Class Header
#include "CDialog.h"
//Global
#include <iostream>
//Local
#include "__CWindows.h"
#include "__WndProc.h"
#include "CControl.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Constructor
CDialog::CDialog()
{
	this->pTemplate = NULL;
	this->tplSize = 0;
	this->pParentWindow = NULL;
}

//Destructor
CDialog::~CDialog()
{
	if(this->pTemplate)
	{
		free(this->pTemplate);
	}
}

//Message-callbacks
void CDialog::OnClose()
{
	this->End();
}

void CDialog::OnInit()
{
}

//Private Functions
void CDialog::AppendData(void *pData, uint16 dataSize)
{
	this->EnsureSize(dataSize);

	memcpy((char *)this->pTemplate + this->tplSize, pData, dataSize);
	this->tplSize += dataSize;
}

void CDialog::AppendString(CString str)
{
	int32 length;
	wchar_t *pWideString;

	length = MultiByteToWideChar(CP_ACP, 0, str.GetC_Str(), -1, NULL, 0);
	pWideString = (wchar_t *)malloc(sizeof(*pWideString) * length);
	MultiByteToWideChar(CP_ACP, 0, str.GetC_Str(), -1, pWideString, length);
	this->AppendData(pWideString, length * (uint16)sizeof(*pWideString));
	free(pWideString);
}

void CDialog::EnsureSize(uint16 size)
{
	void *pNewBuffer = malloc(this->tplSize + size);
	memcpy(pNewBuffer, this->pTemplate, this->tplSize);
	free(this->pTemplate);
	this->pTemplate = (DLGTEMPLATE *)pNewBuffer;
}

//Public Functions
void CDialog::Create(CString caption, uint32 styleFlags, dialogBoxUnits x, dialogBoxUnits y, dialogBoxUnits width, dialogBoxUnits height, const CWindow *pParentWindow, const SJCWinLib::CFont &refFont)
{
	LOGFONT lf;
	uint16 fontSizeInPoints;
	CPointer<CDeviceContext> pDC(CWindow::GetDesktopWindow()->GetDC());

	this->pParentWindow = pParentWindow;
	
	this->tplSize = sizeof(*this->pTemplate);
	this->pTemplate = (DLGTEMPLATE *)malloc(this->tplSize);
	
	refFont.GetFontAttributes(&lf);
	fontSizeInPoints = -MulDiv(lf.lfHeight, 72, pDC->GetDeviceCaps(LOGPIXELSY));

	this->pTemplate->cdit = 0;
	this->pTemplate->cx = width;
	this->pTemplate->cy = height;
	this->pTemplate->dwExtendedStyle = 0;
	this->pTemplate->style = styleFlags | WS_VISIBLE | WS_POPUP | DS_SETFONT;
	this->pTemplate->x = x;
	this->pTemplate->y = y;

	this->AppendString("");//Menu
	this->AppendString("");//WindowClass
	this->AppendString(caption); //Title
	this->AppendData(&fontSizeInPoints, 2); //16bit size of the font in points
	this->AppendString(lf.lfFaceName); //font name
}

const CRect &CDialog::DialogToScreenUnits(CRect &refRc)
{
	MapDialogRect(this->hWnd, &refRc);

	return refRc;
}

void CDialog::End(int32 result)
{
	::EndDialog(this->hWnd, result);
}

CSystemWindow *CDialog::GetNextGroupItem(const CSystemWindow *pStartingPointCtrl, bool next)
{
	if(pStartingPointCtrl)
		return (CSystemWindow *)CWindows::GetWindowPointer(::GetNextDlgGroupItem(this->hWnd, pStartingPointCtrl->hWnd, !next));
	return (CSystemWindow *)CWindows::GetWindowPointer(::GetNextDlgGroupItem(this->hWnd, NULL, !next));
}

int32 CDialog::Run()
{
	HWND hWnd = NULL;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	//Assertions
	ASSERT(this->pTemplate); //Although this error does not cause a crash, inform the coder about this mistake...

	if(!this->pTemplate)
	{
		return -1;
	}

	if(this->pParentWindow)
	{
		hWnd = ((CDialog *)this->pParentWindow)->hWnd;
		hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
	}
	return (int32)DialogBoxIndirectParam(hInstance, this->pTemplate, hWnd, (DLGPROC)SJCLibIntern::DialogProcedure, (LPARAM)this);
}


/*
//Local
#include "SJCLib.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibString;
using namespace SJCLibWindows;

//Callbacks

void CDialog::OnSize(WPARAM resizingType, uint16 newWidth, uint16 newHeight)
{
}

//Protected Functions

int CDialog::RunModeless()
{
	HWND hWnd = NULL;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	if(!this->pTemplate)
	{
		return -1;
	}

	if(this->pParentWindow)
	{
		hWnd = ((CDialog *)this->pParentWindow)->hWnd;
		hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
	}
	return (int32)CreateDialogIndirectParam(hInstance, this->pTemplate, hWnd, (DLGPROC)SJCLibIntern::DialogProcedure, (LPARAM)this);
}

void CDialog::ScreenToDialogUnits(CRect &refRc)
{
	CRect rc(0, 0, 4, 8);
	uint32 baseUnitX, baseUnitY;

	this->DialogToScreenUnits(rc);
	baseUnitX = rc.right;
	baseUnitY = rc.bottom;

	refRc.left = MulDiv(refRc.left, 4, baseUnitX);
	refRc.top = MulDiv(refRc.top, 8, baseUnitY);
	refRc.right = MulDiv(refRc.right, 4, baseUnitX);
	refRc.bottom = MulDiv(refRc.bottom, 8, baseUnitY);
}*/