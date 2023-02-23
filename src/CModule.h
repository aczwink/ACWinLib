#pragma once
//Global
#include <Windows.h>
//Local
#include "CBitmap.h"
#include "CBrush.h"
#include "CCursor.h"
#include "CIcon.h"
#include "Definitions.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CModule
	{
		friend class CToolTip;
		friend class CWindow;
	private:
		//Variables
		HMODULE hModule;
		bool isLoaded;
	public:
		//Constructors
		CModule(HMODULE hModule);
		CModule(const SJCLib::CWString &refFileName);
		//Destructor
		~CModule();
		//Functions
		void FreeLibrary();
		SJCLib::CPointer<CBitmap> LoadBitmap(uint32 resourceId);
		SJCLib::CWString LoadStringW(uint32 id) const;
		//Inline
		inline SJCLib::CWString GetFileName()
		{
			wchar_t buffer[MAX_PATH];
			
			GetModuleFileNameW(this->hModule, buffer, sizeof(buffer));
			
			return buffer;
		}
		//Static functions
		static inline CModule GetCallingProcessModule()
		{
			return CModule(GetModuleHandle(NULL));
		}
	};

	typedef CModule CInstance;
}

/*#pragma once
//Global
#include <Windows.h>
//Local
#include "SJCLib.h"
#include "SJCLibString.h"
#include "CBrush.h"
#include "CIcon.h"

namespace SJCWinLib
{
	class SJCLIB_API CModule
	{
		friend class CWindow;
		//Dialogs
		friend class CDialog;
	public:
		//Operators
		CModule &operator=(const HMODULE hModule);
	};
}*/