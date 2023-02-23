#pragma once
//Global
#include <Windows.h>
#include <Uxtheme.h>
#include <vsstyle.h>
//Local
#include "Definitions.h"
#include "CWindow.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CTheme
	{
	private:
		//Variables
		HTHEME hTheme;
	public:
		//Constructor
		CTheme();
		//Destructor
		~CTheme();
		//Functions
		void CloseData();
		void DrawBackground(const CDeviceContext &refDC, int32 partId, int32 stateId, const CRect &refRect, const CRect *pClipRect) const;
		void DrawParentBackground(const CWindow &refWnd, const CDeviceContext &refDC, const CRect &refRect) const;
		bool GetPartSize(int32 partId, int32 stateId, THEMESIZE size, SIZE *pOutSize);
		bool IsBackgroundPartiallyTransparent(int32 partId, int32 stateId) const;
		void OpenData(const CWindow &refWnd, SJCLib::CWString classList);
	};
}