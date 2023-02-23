//Class Header
#include "CRect.h"
//Namespaces
using namespace SJCWinLib;

//Constructors
CRect::CRect()
{
	this->left = 0;
	this->top = 0;
	this->right = 0;
	this->bottom = 0;
}

CRect::CRect(uint32 left, uint32 top, uint32 right, uint32 bottom)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

//Public Functions
uint32 CRect::GetHeight() const
{
	return this->bottom - this->top;
}

uint32 CRect::GetWidth() const
{
	return this->right - this->left;
}

CRect &CRect::Init(uint32 x, uint32 y, uint32 width, uint32 height)
{
	this->left = x;
	this->top = y;
	this->right = x + width;
	this->bottom = y + height;

	return *this;
}

bool CRect::PointInRect(POINT pt) const
{
	return PtInRect(this, pt) != 0;
}

void CRect::SetHeight(uint32 height)
{
	this->bottom = this->top + height;
}

void CRect::SetWidth(uint32 width)
{
	this->right = this->left + width;
}

/*
//Namespaces
using namespace SJCLibWindows;

//Operators
CRect &CRect::operator=(const RECT &rc)
{
	this->left = rc.left;
	this->top = rc.top;
	this->right = rc.right;
	this->bottom = rc.bottom;

	return *this;
}

//Public Functions

void CRect::OffsetRect(int32 dx, int32 dy)
{
	::OffsetRect(this, dx, dy);
}
*/