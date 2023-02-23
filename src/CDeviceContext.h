#pragma once
//Global
#include <Windows.h>
//SJCLib
#include <SJCLib.h>
//Local
#include "CBitmap.h"
#include "CBrush.h"
#include "CColor.h"
#include "CFont.h"
#include "CPen.h"
#include "CRect.h"
#include "CRegion.h"
#include "CWindow.h"
#include "Definitions.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CDeviceContext
	{
		//Procedures
		friend bool SJCLibIntern::ForwardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		//Classes
		friend class CTheme;
		friend class CWindow;
	private:
		//Variables
		enum
		{
			RA_NONE,
			RA_DELETE,
			RA_RELEASE
		} releaseAction;
	protected:
		//Variables
		HDC hDC;
	public:
		//Constructor
		CDeviceContext();
		//Destructor
		~CDeviceContext();
		//Functions
		void BitBlt(int32 x, int32 y, int32 width, int32 height, const CDeviceContext &refDCSource, int32 sourceX, int32 sourceY, uint32 rasterOperation) const;
		void BitBlt(int32 x, int32 y, int32 width, int32 height, const SJCLib::CPointer<CDeviceContext> &refpDCSource, int32 sourceX, int32 sourceY, uint32 rasterOperation) const;
		SJCLib::CPointer<CBitmap> CreateCompatibleBitmap(uint32 width, uint32 height) const;
		SJCLib::CPointer<CDeviceContext> CreateCompatibleDC();
		SJCLib::CPointer<CBitmap> CreateDIBSection(const BITMAPINFO *pBmi, uint32 usage, void **ppvBits) const;
		void DrawFrameControl(CRect &refRect, uint32 type, uint32 state) const;
		void FillRect(const CRect &refRect, const CBrush &refBrush) const;
		void FillSolidRect(const CRect &refRect, const CColor &refColor) const;
		
		inline int32 GetDeviceCaps(int32 index) const
		{
			return ::GetDeviceCaps(this->hDC, index);
		}
		
		void GetTextMetrics(TEXTMETRIC *pTM) const;
		CWindow *GetWindow() const;
		void Release();
		
		inline int32 SelectClipRegion(const CRegion &refRegion)
		{
			return SelectClipRgn(this->hDC, refRegion.hRgn);
		}
		
		SJCLib::CPointer<CBitmap> SelectObject(const SJCLib::CPointer<CBitmap> &refBitmap) const;
		SJCLib::CPointer<CFont> SelectObject(const CFont &refFont) const;
		SJCLib::CPointer<CPen> SelectPen(const CPen &refPen) const;
		CColor SetBackgroundColor(const CColor &refColor) const;
		void SetBackgroundMode(bool opaque = true) const;

		inline uint32 SetDIBits(const SJCLib::CPointer<CBitmap> &refBitmap, uint32 startLineIndex, uint32 nLines, const void *pBits, const BITMAPINFO *pBmi, uint32 colorUse)
		{
			return ::SetDIBits(this->hDC, (HBITMAP)refBitmap->hGDIObj, startLineIndex, nLines, pBits, pBmi, colorUse);
		}

		inline int32 SetStretchBltMode(int32 stretchMode)
		{
			return ::SetStretchBltMode(this->hDC, stretchMode);
		}

		CColor SetTextColor(const CColor &refColor) const;
		//Inline
		inline void Arc(const CRect &refBounds, POINT startPt, POINT endPt)
		{
			::Arc(this->hDC, refBounds.left, refBounds.top, refBounds.right, refBounds.bottom, startPt.x, startPt.y, endPt.x, endPt.y);
		}

		inline int32 DrawTextA(const SJCLib::CString &refText, const CRect &refRect, uint32 formatFlags)
		{
			return ::DrawTextA(this->hDC, refText.GetC_Str(), refText.GetLength(), (RECT *)&refRect, formatFlags);
		}

		inline int32 DrawTextW(const SJCLib::CWString &refText, const CRect &refRect, uint32 formatFlags)
		{
			return ::DrawTextW(this->hDC, refText.GetC_Str(), refText.GetLength(), (RECT *)&refRect, formatFlags);
		}
		
		inline int32 ExcludeClipRect(const CRect &refRect)
		{
			return ::ExcludeClipRect(this->hDC, refRect.left, refRect.top, refRect.right, refRect.bottom);
		}

		inline int32 GetDIBits(const CBitmap &refBitmap, uint32 startLine, uint32 nLinesToCopy, void *pBuffer, BITMAPINFO &refBitmapInfo, bool useRGB)
		{
			return ::GetDIBits(this->hDC, (HBITMAP)refBitmap.hGDIObj, startLine, nLinesToCopy, pBuffer, &refBitmapInfo, useRGB ? DIB_RGB_COLORS : DIB_PAL_COLORS);
		}

		inline uint32 GetGlyphOutline(char c, GLYPHMETRICS &refGM, const MAT2 &refMat2) const
		{
			return ::GetGlyphOutline(this->hDC, c, GGO_METRICS, &refGM, 0, NULL, &refMat2);
		}

		inline SIZE GetTextExtentPoint(const SJCLib::CString &refText) const
		{
			SIZE size;

			::GetTextExtentPoint32A(this->hDC, refText.GetC_Str(), refText.GetLength(), &size);

			return size;
		}
		inline SIZE GetTextExtentPoint(const SJCLib::CWString &refText) const
		{
			SIZE size;

			::GetTextExtentPoint32W(this->hDC, refText.GetC_Str(), refText.GetLength(), &size);
			
			return size;
		}
		inline void GradientFill(uint32 nVertices, TRIVERTEX *pVertices, uint32 nRectangles, GRADIENT_RECT *pGradientRects, bool fillHorizontal)
		{
			::GradientFill(this->hDC, pVertices, nVertices, pGradientRects, nRectangles, (fillHorizontal ? GRADIENT_FILL_RECT_H : GRADIENT_FILL_RECT_V));
		}

		inline void MoveTo(int32 x, int32 y)
		{
			MoveToEx(this->hDC, x, y, NULL);
		}

		inline void LineTo(int32 x, int32 y)
		{
			::LineTo(this->hDC, x, y);
		}

		inline void StretchBlt(int32 x, int32 y, int32 width, int32 height, const SJCLib::CPointer<CDeviceContext> &refpDCSource, int32 sourceX, int32 sourceY, int32 sourceWidth, int32 sourceHeight, uint32 rasterOperation)
		{
			::StretchBlt(this->hDC, x, y, width, height, refpDCSource->hDC, sourceX, sourceY, sourceWidth, sourceHeight, rasterOperation);
		}

		inline uint32 TabbedTextOut(int32 x, int32 y, const SJCLib::CString &refString, uint32 nTabStops, const uint32 *pTabStops, int32 tabOrigin)
		{
			return ::TabbedTextOut(this->hDC, x, y, refString.GetC_Str(), refString.GetLength(), nTabStops, (const int32 *)pTabStops, tabOrigin);
		}

		inline void TextOut(int32 x, int32 y, const SJCLib::CString &refString)
		{
			::TextOut(this->hDC, x, y, refString.GetC_Str(), refString.GetLength());
		}

		inline void TextOut(int32 x, int32 y, uint32 flags, const CRect &refRect, const SJCLib::CString &refText)
		{
			ExtTextOut(this->hDC, x, y, flags, &refRect, refText.GetC_Str(), refText.GetLength(), NULL);
		}
	};

	typedef CDeviceContext CDC;
}

/*#pragma once
//Definitions
#define WIN32_LEAN_AND_MEAN
//Global
#include <iostream>
#include <Windows.h>
//Local
#include "SJCLib.h"
#include "CWindow.h"
#include "CColor.h"
#include "CBitmap.h"
#include "CBrush.h"

namespace SJCWinLib
{
	class SJCLIB_API CDeviceContext
	{
		friend class CTheme;
	public:
		//constructors
		CDeviceContext(HDC hDC);//check usage
		//operators
		CDeviceContext &operator=(const HDC &hDC);//check usage
		bool operator==(const HDC &hDC);//check usage
		bool operator!=(const HDC &hDC);//check usage
		//Functions
		void DrawFocusRect(const RECT *pRc);
		void FillSolidRect(uint32 x, uint32 y, uint32 width, uint32 height, CColor color);
		void GetWindowOrg(POINT *pPt);
		void LogicalToDevicePoint(POINT *pt);//check usage
		SJCLib::CSmartPointer<CBitmap> SelectObject(CBitmap *pBitmap);
		void SetWindowOrg(int32 x, int32 y);
		void TextOutEx(int32 x, int32 y, uint32 options, const RECT *pRc, SJCLibString::CString text);
	};
}*/