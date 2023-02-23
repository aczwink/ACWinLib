/*//Class Header
#include "CommCtrl CSysLink.h"
//Global
#include <CommCtrl.h>
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
using namespace SJCWinLibCommCtrl;

//Message-callbacks
void CSysLink::OnClick(CWString id, CWString url)
{
}

LRESULT CSysLink::OnNotify(NMHDR *pNmh)
{
	switch(pNmh->code)
	{
	case NM_RETURN:
		this->OnReturn(((NMLINK *)pNmh)->item.szID, ((NMLINK *)pNmh)->item.szUrl);
		return 0;
	case NM_CLICK:
		this->OnClick(((NMLINK *)pNmh)->item.szID, ((NMLINK *)pNmh)->item.szUrl);
		return 0;
	}

	return CWindow::RespondDefault();
}

void CSysLink::OnReturn(CWString id, CWString url)
{
}

//Public Functions
void CSysLink::Create(CString text, uint32 styleFlags, uint32 x, uint32 y, uint32 width, uint32 height, const CWindow &refParentWindow)
{
	CWindow::Create(WC_LINK, text, WS_CHILD | WS_VISIBLE | styleFlags, 0, x, y, width, height, refParentWindow);
}*/