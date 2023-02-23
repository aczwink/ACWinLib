//Class Header
#include "CCommonItemOpenDialog.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Constructor
CCommonItemOpenDialog::CCommonItemOpenDialog()
{
	this->pFD = NULL;
	this->pParentWindow = NULL;
}

//Destructor
CCommonItemOpenDialog::~CCommonItemOpenDialog()
{
	SAFERELEASE(this->pFD);
}

//Public Functions
bool CCommonItemOpenDialog::Create(const CWindow *pParentWindow)
{
	HRESULT hr;
	
	this->pParentWindow = pParentWindow;

	hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&this->pFD));

	return SUCCEEDED(hr);
}

CWString CCommonItemOpenDialog::GetResult() const
{
	CWString str;
	IShellItem *pSI;
	PWSTR filePath = NULL;

	this->pFD->GetResult(&pSI);
	pSI->GetDisplayName(SIGDN_FILESYSPATH, &filePath);
	str = filePath;

	CoTaskMemFree(filePath);
	SAFERELEASE(pSI);

	return str;
}

bool CCommonItemOpenDialog::Run()
{
	return SUCCEEDED(this->pFD->Show(this->pParentWindow->hWnd));
}

void CCommonItemOpenDialog::SetFileTypes(uint16 nFilterspecs, const COMDLG_FILTERSPEC *pFilterspecs)
{
	this->pFD->SetFileTypes(nFilterspecs, pFilterspecs);
}

/*
//Namespaces
using namespace SJCLibString;
using namespace SJCLibWindows;



FILEOPENDIALOGOPTIONS CCommonItemOpenDialog::GetOptions()
{
	FILEOPENDIALOGOPTIONS flags;
	
	this->pFD->GetOptions(&flags);
	return flags;
}

void CCommonItemOpenDialog::SetFileTypeIndex(uint16 index)
{
	this->pFD->SetFileTypeIndex(index);
}

void CCommonItemOpenDialog::SetOptions(FILEOPENDIALOGOPTIONS flags)
{
	this->pFD->SetOptions(flags);
}*/