//Class Header
#include "CCommonItemSaveDialog.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Constructor
CCommonItemSaveDialog::CCommonItemSaveDialog()
{
	this->pFD = NULL;
	this->pParentWindow = NULL;
}

//Destructor
CCommonItemSaveDialog::~CCommonItemSaveDialog()
{
	SAFERELEASE(this->pFD);
}

//Public Functions
bool CCommonItemSaveDialog::Create(const CWindow *pParentWindow)
{
	HRESULT hr;
	
	this->pParentWindow = pParentWindow;
	hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&this->pFD));
	
	return SUCCEEDED(hr);
}

CWString CCommonItemSaveDialog::GetResult() const
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

bool CCommonItemSaveDialog::Run()
{
	return SUCCEEDED(this->pFD->Show(this->pParentWindow->hWnd));
}

void CCommonItemSaveDialog::SetFileTypes(uint16 nFilterspecs, const COMDLG_FILTERSPEC *pFilterspecs)
{
	this->pFD->SetFileTypes(nFilterspecs, pFilterspecs);
}

/*
//Namespaces
using namespace SJCLibString;
using namespace SJCLibWindows;



FILEOPENDIALOGOPTIONS CCommonItemSaveDialog::GetOptions()
{
	FILEOPENDIALOGOPTIONS flags;
	
	this->pFD->GetOptions(&flags);
	return flags;
}

void CCommonItemSaveDialog::SetFileName(CString name)
{
	this->pFD->SetFileName(CWString(name).c_str());
}

void CCommonItemSaveDialog::SetOptions(FILEOPENDIALOGOPTIONS flags)
{
	this->pFD->SetOptions(flags);
}*/