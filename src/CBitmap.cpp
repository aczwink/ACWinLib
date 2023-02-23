/*//Class Header
#include "CBitmap.h"
//Namespaces
using namespace SJCLibWindows;

//Constructors
CBitmap::CBitmap()
{
	memzero(this, sizeof(*this));
}

CBitmap::CBitmap(HBITMAP hBitmap)
{
	memzero(this, sizeof(*this));
	this->hGDIObj = hBitmap;
}

//Operators
CBitmap &CBitmap::operator=(const HBITMAP hBmp)
{
	this->hGDIObj = hBmp;

	return *this;
}*/