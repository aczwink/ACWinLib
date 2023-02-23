#pragma once
//Global
#include <ShlObj.h>
//Local
#include "CWindow.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CCommonItemOpenDialog
	{
	private:
		//Variables
		IFileOpenDialog *pFD;
		const CWindow *pParentWindow;
	public:
		//Constructor
		CCommonItemOpenDialog();
		//Destructor
		~CCommonItemOpenDialog();
		//Functions
		bool Create(const CWindow *pParentWindow);
		SJCLib::CWString GetResult() const;
		bool Run();
		void SetFileTypes(uint16 nFilterspecs, const COMDLG_FILTERSPEC *pFilterspecs);
	};
}

/*#pragma once
//SJCLib
#include <SJCLib.h>
//Local
#include "CDialog.h"

namespace SJCLibWindows
{
	class SJCLIB_API CCommonItemOpenDialog
	{
	public:
		//Functions
		FILEOPENDIALOGOPTIONS GetOptions();
		void SetFileTypeIndex(uint16 index);
		void SetOptions(FILEOPENDIALOGOPTIONS flags);
	};
}*/