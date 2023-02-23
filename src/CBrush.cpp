//Class Header
#include "CBrush.h"
//Local
#include "__CWindows.h"
//Namespaces
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Public Functions
void CBrush::CreateSolidBrush(const CColor &refColor)
{
	this->hGDIObj = ::CreateSolidBrush(refColor.ToCOLORREF());
	CWindows::GDIAddReferenceCount(this->hGDIObj);
}

void CBrush::CreateSystemColorBrush(int64 index)
{
	this->hGDIObj = (HGDIOBJ)index;
}

/*
//Namespaces
using namespace SJCLibWindows;

//constructor
CBrush::CBrush()
{
	memzero(this, sizeof(*this));
}

CBrush::CBrush(HBRUSH hBrush)
{
	memzero(this, sizeof(*this));
	this->hGDIObj = hBrush;
}
*/