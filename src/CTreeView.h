#pragma once
//Global
#include <Windows.h>
#include <CommCtrl.h>
//Local
#include "CSystemWindow.h"

namespace SJCWinLib
{
	//Forward declarations
	class CTreeView;

	class SJCWINLIB_API CTreeViewNode
	{
	protected:
		//Variables
		HTREEITEM hItem;
		CTreeView *pOwner;
		SJCLib::CArray<CTreeViewNode> subNodes;
	public:
		//Functions
		CTreeViewNode *AddNode(SJCLib::CString text);
		void Expand();
	};

	class SJCWINLIB_API CTreeView : public CSystemWindow, public CTreeViewNode
	{
	public:
		//Functions
		void Create(uint32 styleFlags, uint32 x, uint32 y, uint32 width, uint32 height, const CWindow &refParentWindow);
		void Create(uint32 styleFlags, const CRect &refRc, const CWindow &refParentWindow);
	};
}

/*#pragma once
//Local
#include "CControl.h"

namespace SJCLibWindows
{
class SJCLIB_API CTreeViewNode
	{
	public:
		CTreeViewNode *GetNode(uint16 index);
	};

	class SJCLIB_API CTreeView : public CControl, public CTreeViewNode
	{
	public:
		//Functions
		SJCLib::SJCLibResult Create(uint32 styleFlags, uint32 x, uint32 y, uint32 width, uint32 height, CWindow *pParentWindow);
		SJCLib::SJCLibResult Create(uint32 styleFlags, const CRect &refRc, CWindow *pParentWindow);
	};
}*/