/*//Class Header
#include "CTreeView.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//CTreeViewNode Public Functions
CTreeViewNode *CTreeViewNode::AddNode(CString text)
{
	TVITEM item;
	TVINSERTSTRUCT tvis;
	CTreeViewNode subNode;
	uint32 index;

	MemZero(&item, sizeof(item));
	MemZero(&tvis, sizeof(tvis));

	item.mask = TVIF_TEXT;
	item.pszText = (LPSTR)text.GetC_Str();
	item.cchTextMax = text.GetLength()+1;

	if(this->subNodes.IsEmpty())
		tvis.hInsertAfter = TVI_FIRST;
	else
		tvis.hInsertAfter = this->subNodes[this->subNodes.GetNoOfElements()-1].hItem;
	tvis.hParent = this->hItem;
	tvis.item = item;
	
	subNode.hItem = (HTREEITEM)this->pOwner->SendMessageA(TVM_INSERTITEM, 0, (LPARAM)&tvis);
	subNode.pOwner = this->pOwner;

	index = this->subNodes.Push(subNode);

	return &this->subNodes[index];
}

void CTreeViewNode::Expand()
{
	this->pOwner->SendMessageA(TVM_EXPAND, TVM_EXPAND, (LPARAM)this->hItem);
}

//Public Functions
void CTreeView::Create(uint32 styleFlags, uint32 x, uint32 y, uint32 width, uint32 height, const CWindow &refParentWindow)
{
	this->hItem = TVI_ROOT;
	this->pOwner = this;
	CWindow::Create(WC_TREEVIEW, "", WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT, 0, x, y, width, height, refParentWindow);
}

void CTreeView::Create(uint32 styleFlags, const CRect &refRc, const CWindow &refParentWindow)
{
	return this->Create(styleFlags, refRc.left, refRc.top, refRc.GetWidth(), refRc.GetHeight(), refParentWindow);
}

/*
//Namespaces
using namespace SJCLib;
using namespace SJCLibString;
using namespace SJCLibWindows;

//CTreeViewNode Public Functions
CTreeViewNode *CTreeViewNode::GetNode(uint16 index)
{
	return &this->subNodes[index];
}
*/