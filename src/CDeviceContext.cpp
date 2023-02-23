//Class Header
#include "CDeviceContext.h"
//Local
#include "__CWindows.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Constructor
CDeviceContext::CDeviceContext()
{
	this->releaseAction = RA_NONE;
	this->hDC = NULL;
}

//Destructor
CDeviceContext::~CDeviceContext()
{
	this->Release();
}

//Public Functions
void CDeviceContext::BitBlt(int32 x, int32 y, int32 width, int32 height, const CDeviceContext &refDCSource, int32 sourceX, int32 sourceY, uint32 rasterOperation) const
{
	::BitBlt(this->hDC, x, y, width, height, refDCSource.hDC, sourceX, sourceY, rasterOperation);
}

void CDeviceContext::BitBlt(int32 x, int32 y, int32 width, int32 height, const SJCLib::CPointer<CDeviceContext> &refpDCSource, int32 sourceX, int32 sourceY, uint32 rasterOperation) const
{
	::BitBlt(this->hDC, x, y, width, height, refpDCSource->hDC, sourceX, sourceY, rasterOperation);
}

CPointer<CBitmap> CDeviceContext::CreateCompatibleBitmap(uint32 width, uint32 height) const
{
	CPointer<CBitmap> pBmp(new CBitmap);

	pBmp->hGDIObj = ::CreateCompatibleBitmap(this->hDC, width, height);

	return pBmp;
}

CPointer<CDeviceContext> CDeviceContext::CreateCompatibleDC()
{
	CPointer<CDeviceContext> dc(new CDeviceContext);

	dc->hDC = ::CreateCompatibleDC(this->hDC);
	dc->releaseAction = RA_DELETE;
	
	return dc;
}

CPointer<CBitmap> CDeviceContext::CreateDIBSection(const BITMAPINFO *pBmi, uint32 usage, void **ppvBits) const
{
	CPointer<CBitmap> pBmp(new CBitmap);
	
	pBmp->hGDIObj = ::CreateDIBSection(this->hDC, pBmi, usage, ppvBits, NULL, 0);
	CWindows::GDIAddReferenceCount(pBmp->hGDIObj);
	
	return pBmp;
}

void CDeviceContext::DrawFrameControl(CRect &refRect, uint32 type, uint32 state) const
{
	::DrawFrameControl(this->hDC, &refRect, type, state);
}

void CDeviceContext::FillRect(const CRect &refRect, const CBrush &refBrush) const
{
	::FillRect(this->hDC, &refRect, (HBRUSH)refBrush.hGDIObj);
}

void CDeviceContext::FillSolidRect(const CRect &refRect, const CColor &refColor) const
{
	CBrush brush;

	brush.CreateSolidBrush(refColor);
	this->FillRect(refRect, brush);
}

void CDeviceContext::GetTextMetrics(TEXTMETRIC *pTM) const
{
	::GetTextMetrics(this->hDC, pTM);
}

CWindow *CDeviceContext::GetWindow() const
{
	return (CWindow *)CWindows::GetWindowPointer(WindowFromDC(this->hDC));
}

void CDeviceContext::Release()
{
	if(this->hDC)
	{
		if(this->releaseAction == RA_DELETE)
			DeleteDC(this->hDC);
		else if(this->releaseAction == RA_RELEASE)
			ReleaseDC(this->GetWindow()->hWnd, this->hDC);
	}
	
	this->releaseAction = RA_NONE;
	this->hDC = NULL;
}

CPointer<CBitmap> CDeviceContext::SelectObject(const CPointer<CBitmap> &refBitmap) const
{
	CPointer<CBitmap> pBmp(new CBitmap);
	
	pBmp->hGDIObj = ::SelectObject(this->hDC, ((CPointer<CBitmap> &)refBitmap)->hGDIObj);

	return pBmp;
}

CPointer<SJCWinLib::CFont> CDeviceContext::SelectObject(const SJCWinLib::CFont &refFont) const
{
	CPointer<SJCWinLib::CFont> pOldFont(new SJCWinLib::CFont);
	
	pOldFont->hGDIObj = ::SelectObject(this->hDC, refFont.hGDIObj);
	CWindows::GDIAddReferenceCount(pOldFont->hGDIObj);

	return pOldFont;
}

CPointer<CPen> CDeviceContext::SelectPen(const CPen &refPen) const
{
	CPointer<CPen> pOldPen(new CPen);
	
	pOldPen->hGDIObj = ::SelectObject(this->hDC, refPen.hGDIObj);
	CWindows::GDIAddReferenceCount(pOldPen->hGDIObj);
	
	return pOldPen;
}

CColor CDeviceContext::SetBackgroundColor(const CColor &refColor) const
{
	return SetBkColor(this->hDC, refColor.ToCOLORREF());
}

void CDeviceContext::SetBackgroundMode(bool opaque) const
{
	SetBkMode(this->hDC, opaque ? OPAQUE : TRANSPARENT);
}

CColor CDeviceContext::SetTextColor(const CColor &refColor) const
{
	return CColor(::SetTextColor(this->hDC, refColor.ToCOLORREF()));
}

/*
//Namespaces
using namespace SJCLib;
using namespace SJCLibString;
using namespace SJCLibWindows;

CDeviceContext::CDeviceContext(HDC hDC)
{
	memzero(this, sizeof(*this));
	this->hDC = hDC;
}

//operators
CDeviceContext &CDeviceContext::operator=(const HDC &hDC)
{
	this->Release();
	this->hDC = hDC;

	return *this;
}

bool CDeviceContext::operator==(const HDC &hDC)
{
	return this->hDC == hDC;
}

bool CDeviceContext::operator!=(const HDC &hDC)
{
	return this->hDC != hDC;
}

//public functions
void CDeviceContext::BitBlt(int x, int y, int width, int height, CSmartPointer<CDeviceContext> pDCSource, int sourceX, int sourceY, DWORD dwRasterOperation)
{
	::BitBlt(this->hDC, x, y, width, height, pDCSource->hDC, sourceX, sourceY, dwRasterOperation);
}

void CDeviceContext::DrawFocusRect(const RECT *pRc)
{
	::DrawFocusRect(this->hDC, pRc);
}

void CDeviceContext::FillSolidRect(uint32 x, uint32 y, uint32 width, uint32 height, CColor color)
{
	CRect rc;
	CBrush brush;

	rc.left = x;
	rc.top = y;
	rc.SetWidth(width);
	rc.SetHeight(height);

	brush.CreateSolidBrush(color);
	this->FillRect(&rc, &brush);
}

void CDeviceContext::GetWindowOrg(POINT *pPt)
{
	GetWindowOrgEx(this->hDC, pPt);
}

void CDeviceContext::LogicalToDevicePoint(POINT *pt)
{
	LPtoDP(this->hDC, pt, 1);
}

CSmartPointer<CBitmap> CDeviceContext::SelectObject(CBitmap *pBitmap)
{
	CSmartPointer<CBitmap> pBmp;
	pBmp->hGDIObj = ::SelectObject(this->hDC, pBitmap->hGDIObj);

	return pBmp;
}

void CDeviceContext::SetWindowOrg(int32 x, int32 y)
{
	SetWindowOrgEx(this->hDC, x, y, NULL);
}

void CDeviceContext::TextOutEx(int32 x, int32 y, uint32 options, const RECT *pRc, CString text)
{
	ExtTextOut(this->hDC, x, y, options, pRc, text.c_str(), text.GetLength(), NULL);
}*/