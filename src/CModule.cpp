//Class Header
#include "CModule.h"
//Local
#include "__CWindows.h"
#include "__WndProc.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Constructors
CModule::CModule(HMODULE hModule)
{
	this->hModule = hModule;
	this->isLoaded = false;
}

CModule::CModule(const CWString &refFileName)
{
	this->hModule = ::LoadLibraryW(refFileName.GetC_Str());
	this->isLoaded = true;
}

//Destructor
CModule::~CModule()
{
	this->FreeLibrary();
}

//Public Functions
void CModule::FreeLibrary()
{
	if(this->hModule && this->isLoaded)
	{
		::FreeLibrary(this->hModule);
		this->hModule = NULL;
		this->isLoaded = false;
	}
}

CPointer<CBitmap> CModule::LoadBitmap(uint32 resourceId)
{
	CPointer<CBitmap> pBmp(new CBitmap);

	//pBmp->hGDIObj = LoadImage(this->hModule, refResourceName.GetC_Str(), IMAGE_BITMAP, 0, 0, LR_SHARED);
	//pBmp->hGDIObj = ::LoadBitmap(this->hModule, refResourceName.GetC_Str());
	pBmp->hGDIObj = ::LoadBitmap(this->hModule, MAKEINTRESOURCE(resourceId));

	return pBmp;
}

CWString CModule::LoadStringW(uint32 id) const
{
	wchar_t buffer[1024];

	MemZero(buffer, sizeof(buffer));
	::LoadStringW(this->hModule, id, buffer, sizeof(buffer));

	return buffer;
}

/*bool CModule::RegisterWindowClass(const CBrush *pBackgroundBrush, const CCursor *pCursor, const CIcon *pIcon, const CIcon *pIconSmall, CString classname) const
{
	WNDCLASSEX wcex;

	if(!GetClassInfoEx(this->hModule, classname.GetC_Str(), &wcex))
	{
		wcex.cbClsExtra = 0;
		wcex.cbSize = sizeof(wcex);
		wcex.cbWndExtra = 0;
		wcex.hbrBackground = NULL;
		if(pBackgroundBrush)
		{
			if(pBackgroundBrush->hGDIObj <= (void *)COLOR_BTNTEXT)
				wcex.hbrBackground = (HBRUSH)((uint32)pBackgroundBrush->hGDIObj + 1);
			else
				wcex.hbrBackground = (HBRUSH)pBackgroundBrush->hGDIObj;
		}
		wcex.hCursor = NULL;
		if(pCursor)
			wcex.hCursor = pCursor->hCursor;
		wcex.hIcon = NULL;
		if(pIcon)
			wcex.hIcon = pIcon->hIcon;
		wcex.hIconSm = NULL;
		if(pIconSmall)
			wcex.hIconSm = pIconSmall->hIcon;
		wcex.hInstance = this->hModule;
		wcex.lpfnWndProc = SJCLibIntern::WndProc;
		wcex.lpszClassName = classname.GetC_Str();
		wcex.lpszMenuName = NULL;
		wcex.style = 0;

		CWindows::RegisterWindowClass(this->hModule, classname);
		
		return RegisterClassEx(&wcex) != 0;
	}

	return true;
}

void CModule::UnregisterWindowClass(CString className)
{
	UnregisterClass(className.GetC_Str(), this->hModule);
	CWindows::UnregisterWindowClass(className);
}*/

/*
//Local
#include "__CWindows.h"
//Namespaces
using namespace SJCLibIntern;
using namespace SJCLibString;
using namespace SJCLibWindows;

//Operators
CModule &CModule::operator=(const HMODULE hModule)
{
	this->Attach(hModule);

	return *this;
}
*/