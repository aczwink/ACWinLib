#pragma once
//Local
#include "CGDIObject.h"

namespace SJCLibIntern
{
	bool ForwardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}

namespace SJCWinLib
{
	class SJCWINLIB_API CFont : public CGDIObject
	{
		friend bool SJCLibIntern::ForwardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	public:
		//Operators
		CFont &operator=(const CFont &refFont);
		//Functions
		void Create(int32 height, int32 width, int32 escapement, int32 orientation, int32 weight, bool italic, bool underline, bool strikeOut, uint32 charSet, uint32 outputPrecision, uint32 clipPrecision, uint32 quality, uint32 pitchAndFamily, SJCLib::CString face);
		void Create(const LOGFONT *pLF);
		void GetFontAttributes(LOGFONT *pLF) const;
		void LoadSystemFont(int32 index);
	};
}