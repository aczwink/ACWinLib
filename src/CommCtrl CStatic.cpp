//Class Header
#include "CommCtrl CStatic.h"
//Global
#include <CommCtrl.h>
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
using namespace SJCWinLibCommCtrl;

//Message-callbacks
CBrush CStatic::OnColor(CDeviceContext &refDC)
{
	return CBrush();
}

//Public Functions
void CStatic::Create(uint32 styleFlags, const CWindow &refParentWindow)
{
	CSystemWindow::Create(WC_STATIC, styleFlags, 0, refParentWindow);
}