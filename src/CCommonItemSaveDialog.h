#pragma once
//Local
#include "CCommonItemOpenDialog.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CCommonItemSaveDialog
	{
	private:
		//Variables
		IFileSaveDialog *pFD;
		const CWindow *pParentWindow;
	public:
		//Constructor
		CCommonItemSaveDialog();
		//Destructor
		~CCommonItemSaveDialog();
		//Functions
		bool Create(const CWindow *pParentWindow);
		SJCLib::CWString GetResult() const;
		bool Run();
		void SetFileTypes(uint16 nFilterspecs, const COMDLG_FILTERSPEC *pFilterspecs);
	};
}

/*
namespace SJCLibWindows
{
	class SJCLIB_API CCommonItemSaveDialog
	{
	public:
		FILEOPENDIALOGOPTIONS GetOptions();
		void SetFileName(SJCLibString::CString name);
		void SetOptions(FILEOPENDIALOGOPTIONS flags);
	};
}*/