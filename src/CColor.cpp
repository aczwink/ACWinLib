//Class Header
#include "CColor.h"
//Namespace
using namespace SJCWinLib;

//Constructors
CColor::CColor()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

CColor::CColor(uint32 rrggbb)
{
	this->r = (rrggbb >> 16) & 0xFF;
	this->g = (rrggbb >> 8) & 0xFF;
	this->b = rrggbb & 0xFF;
}

//Public Functions
void CColor::FromCOLORREF(COLORREF color)
{
	this->r = GetRValue(color);
	this->g = GetGValue(color);
	this->b = GetBValue(color);
}

CColor CColor::GetSystemColor(int32 index)
{
	CColor color;

	color.FromCOLORREF(GetSysColor(index));

	return color;
}

void CColor::Set(byte r, byte g, byte b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

COLORREF CColor::ToCOLORREF() const
{
	return RGB(this->r, this->g, this->b);
}

/*
//Namespaces
using namespace SJCLibWindows;

//Constructors

CColor::CColor(byte r, byte g, byte b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

//Functions

const byte CColor::GetB() const
{
	return this->b;
}

const byte CColor::GetG() const
{
	return this->g;
}

const byte CColor::GetR() const
{
	return this->r;
}

void CColor::SetB(byte b)
{
	this->b = b;
}

void CColor::SetG(byte g)
{
	this->g = g;
}

void CColor::SetR(byte r)
{
	this->r = r;
}
*/