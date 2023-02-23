//Class Header
#include "CPaintDC.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Constructor
CPaintDC::CPaintDC(const CWindow *pWnd)
{
	this->pWnd = pWnd;
	
	MemZero(&this->ps, sizeof(this->ps));
	this->hDC = BeginPaint(pWnd->hWnd, &ps);
}

//Destructor
CPaintDC::~CPaintDC()
{
	EndPaint(this->pWnd->hWnd, &this->ps);
	this->hDC = NULL;
}

//Public Functions
void CPaintDC::GetPaintRect(CRect &refRect) const
{
	refRect.bottom = this->ps.rcPaint.bottom;
	refRect.left = this->ps.rcPaint.left;
	refRect.right = this->ps.rcPaint.right;
	refRect.top = this->ps.rcPaint.top;
}