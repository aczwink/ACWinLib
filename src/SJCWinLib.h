#define WIN32_LEAN_AND_MEAN
//Local
#include "Definitions.h"
//Includes belonging to this namespace
#include "AThread.h"
#include "CApplication.h"
#include "CConsole.h"
#include "CControl.h"
#include "CCriticalSection.h"
#include "CCursor.h"
#include "CDeviceContext.h"
#include "CDialog.h"
#include "CEvent.h"
#include "CFrame.h"
#include "CHTTPGet.h"
#include "CMenu.h"
#include "CModule.h"
#include "CPaintDC.h"
#include "CRect.h"
#include "CRegion.h"
#include "CSocket.h"
#include "CWindow.h"
#include "Messageformers.h"
//Controls
#include "CAutoCompleteEdit.h"
#include "CButton.h"
#include "CCheckBox.h"
#include "CComboBox.h"
#include "CEdit.h"
#include "CListBox.h"
#include "CMultiSelectDropDown.h"
#include "CStatic.h"
#include "CStatusBar.h"
#include "CTab.h"
#include "CToolBar.h"
#include "CToolTip.h"
#include "CTreeView.h"
//Dialogs
#include "CCommonItemOpenDialog.h"
#include "CCommonItemSaveDialog.h"
#include "CFolderDialog.h"
#include "CProgressDialog.h"
#include "CPromptDialog.h"
#include "CSelectDialog.h"
//GDI
#include "CBrush.h"
#include "CFont.h"
#include "CPen.h"
//File
#include "CDirectory.h"
#include "CFile.h"
#include "CReadFile.h"
//Window Classes
#include "CPopupWindow.h"




//Common Controls
#include "CCommonButtonClose.h"

namespace SJCWinLib
{
	void SJCWINLIB_API AllocateConsole();
	bool SJCWINLIB_API Initialize(bool winsock);
	SJCLib::CArray<SJCLib::CWString> SJCWINLIB_API ListFiles(SJCLib::CWString path, const SJCLib::CWString &refFilter, bool includeSubDirectories);
	SJCLib::CString SJCWINLIB_API URLEncode(SJCLib::CString url);
}

/*#pragma once

#include "CColor.h"
#include "CIcon.h"
#include "CImageList.h"
#include "CPaintDC.h"
#include "CProcess.h"
#include "CTheme.h"
#include "CTrayIcon.h"
//Controls
#include "CTab.h"
//Extended Controls
#include "CListBoxEx.h"
#include "CMultiSelectList.h"
#include "CMSTextView.h"
//Dialogs
#include "CCommonItemOpenDialog.h"
#include "CCommonItemSaveDialog.h"

namespace SJCLibWindows
{
	//Functions
	bool SJCLIB_API InitWinsock();
}*/