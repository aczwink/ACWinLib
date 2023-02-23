//Class Header
#include "CToolBar.h"
//Global
#include <CommCtrl.h>
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
//Definitions
#define IMGLIST_ID 0

//Message-callbacks
bool CToolBar::OnClick(uint16 commandId)
{
	return false;
}

LRESULT CToolBar::OnNotify(NMHDR *pNmh)
{
	switch(pNmh->code)
	{
	case NM_CLICK:
		return this->OnClick((uint16)((NMMOUSE *)pNmh)->dwItemSpec);
	}
	
	CWindow::RespondDefault();
	return 0;
}

//Public Functions
void CToolBar::AddButton(const CString &refText, uint32 commandId, uint32 bitmapIndex)
{
	TBBUTTON tbb;

	MemZero(&tbb, sizeof(tbb));

	tbb.iBitmap = bitmapIndex;
	tbb.idCommand = commandId;
	tbb.fsState = TBSTATE_ENABLED;
	tbb.fsStyle = BTNS_AUTOSIZE | BTNS_BUTTON;
	tbb.iString = (INT_PTR)refText.GetC_Str();

	this->SendMessageA(TB_ADDBUTTONS, 1, (LPARAM)&tbb);
}

void CToolBar::AddSeperator()
{
	TBBUTTON tbb;

	MemZero(&tbb, sizeof(tbb));

	tbb.fsState = TBSTATE_ENABLED;
	tbb.fsStyle = BTNS_SEP;

	this->SendMessageA(TB_ADDBUTTONS, 1, (LPARAM)&tbb);
}

void CToolBar::LoadSystemImages(uint32 bitmapDb)
{
	this->SendMessageA(TB_LOADIMAGES, bitmapDb, (LPARAM)HINST_COMMCTRL);
}

void CToolBar::SetImageList(const CImageList &refImgList)
{
	this->SendMessageA(TB_SETIMAGELIST, IMGLIST_ID, (LPARAM)refImgList.hImgList);
}

/*
//Global
#include <Windows.h>
#include <CommCtrl.h>
//Local
#include "__CWindows.h"
//Namespaces
using namespace SJCLib;
using namespace SJCLibIntern;
using namespace SJCLibString;
using namespace SJCLibWindows;

//Public Functions
void CToolBar::EnableButton(uint16 commandId, bool enable)
{
	this->SendMessageA(TB_ENABLEBUTTON, commandId, MAKELONG(enable, 0));
}
*/