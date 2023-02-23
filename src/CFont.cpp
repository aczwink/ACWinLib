//Class Header
#include "CFont.h"
//Local
#include "__CWindows.h"
//Namespaces
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Operators
CFont &CFont::operator=(const CFont &refFont)
{
	this->hGDIObj = refFont.hGDIObj;
	CWindows::GDIAddReferenceCount(this->hGDIObj);

	return *this;
}

//Public Functions
void CFont::Create(int32 height, int32 width, int32 escapement, int32 orientation, int32 weight, bool italic, bool underline, bool strikeOut, uint32 charSet, uint32 outputPrecision, uint32 clipPrecision, uint32 quality, uint32 pitchAndFamily, SJCLib::CString face)
{
	this->hGDIObj = CreateFont(height, width, escapement, orientation, weight, italic, underline, strikeOut, charSet, outputPrecision, clipPrecision, quality, pitchAndFamily, face.GetC_Str());
	CWindows::GDIAddReferenceCount(this->hGDIObj);
}

void CFont::Create(const LOGFONT *pLF)
{
	this->hGDIObj = CreateFontIndirect(pLF);
	CWindows::GDIAddReferenceCount(this->hGDIObj);
}

void CFont::GetFontAttributes(LOGFONT *pLF) const
{
	GetObject(this->hGDIObj, sizeof(*pLF), pLF);
}

void CFont::LoadSystemFont(int index)
{
	switch(index)
	{
	case ANSI_FIXED_FONT:
	case DEFAULT_GUI_FONT:
		this->hGDIObj = GetStockObject(index);
	default:
		return;
	}
	CWindows::GDIAddReferenceCount(this->hGDIObj);
}