//Class Header
#include "CFolderDialog.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Intern
namespace SJCLibIntern
{
	int CALLBACK BrowseCallbackProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		CFolderDialog *pDialog = (CFolderDialog *)lParam;
		
		switch(msg)
		{
		case BFFM_INITIALIZED:
			((CFolderDialog *)pDialog->pBrowseDialog)->hWnd = hWnd;
			break;
		case BFFM_SELCHANGED:
			pDialog->OnChangeSelection((LPITEMIDLIST)wParam);
			break;
		}
		return 0;
	}
}

//Constructor
CFolderDialog::CFolderDialog()
{
	this->flags = 0;
	this->pParentWindow = NULL;
	this->pBrowseDialog = NULL;
}

//Message-callbacks
void CFolderDialog::OnChangeSelection(LPITEMIDLIST id)
{
}

//Protected Functions
void CFolderDialog::EnableOKButton(bool enable)
{
	this->pBrowseDialog->SendMessageA(BFFM_ENABLEOK, 0, enable ? TRUE : FALSE);
}

//Public Functions
void CFolderDialog::Create(CString title, uint32 flags, const CWindow *pParentWindow)
{
	this->title = title;
	this->flags = flags;
	this->pParentWindow = pParentWindow;
}

CString CFolderDialog::GetString(LPITEMIDLIST id)
{
	char buffer[MAX_PATH];
	SHGetPathFromIDList(id, buffer);

	return buffer;
}

LPITEMIDLIST CFolderDialog::Run()
{
	LPITEMIDLIST folderId;
	BROWSEINFO bi;
	char buffer[MAX_PATH];

	bi.hwndOwner = ((CFolderDialog *)this->pParentWindow)->hWnd;
	bi.iImage = 0;
	bi.lParam = (LPARAM)this;
	bi.lpfn = (BFFCALLBACK)SJCLibIntern::BrowseCallbackProcedure;
	bi.lpszTitle = this->title.GetC_Str();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = buffer;
	bi.ulFlags = this->flags;

	this->pBrowseDialog = new CWindow;
	folderId = SHBrowseForFolder(&bi);
	HeapDelete(this->pBrowseDialog);
	
	return folderId;
}