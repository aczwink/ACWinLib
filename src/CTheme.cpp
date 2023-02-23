//Class Header
#include "CTheme.h"
//Local
#include <vssym32.h>
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Constructor
CTheme::CTheme()
{
	this->hTheme = NULL;
}

//Destructor
CTheme::~CTheme()
{
	this->CloseData();
}

//Public Functions
void CTheme::CloseData()
{
	if(this->hTheme)
		CloseThemeData(this->hTheme);
}

void CTheme::DrawBackground(const CDeviceContext &refDC, int32 partId, int32 stateId, const CRect &refRect, const CRect *pClipRect) const
{
	::DrawThemeBackground(this->hTheme, refDC.hDC, partId, stateId, &refRect, pClipRect);
}

void CTheme::DrawParentBackground(const CWindow &refWnd, const CDeviceContext &refDC, const CRect &refRect) const
{
	::DrawThemeParentBackground(refWnd.hWnd, refDC.hDC, &refRect);
}

bool CTheme::GetPartSize(int32 partId, int32 stateId, THEMESIZE size, SIZE *pOutSize)
{
	return GetThemePartSize(this->hTheme, NULL, partId, stateId, NULL, size, pOutSize) == S_OK;
}

bool CTheme::IsBackgroundPartiallyTransparent(int32 partId, int32 stateId) const
{
	return ::IsThemeBackgroundPartiallyTransparent(this->hTheme, partId, stateId) == TRUE;
}

void CTheme::OpenData(const CWindow &refWnd, CWString classList)
{
	this->hTheme = OpenThemeData(refWnd.hWnd, classList.GetC_Str());
}