#pragma once
//Global
#include <ShlObj.h>
//Local
#include "CDialog.h"

namespace SJCLibIntern
{
	int CALLBACK BrowseCallbackProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

namespace SJCWinLib
{
	class SJCWINLIB_API CFolderDialog : public CDialog
	{
		friend int CALLBACK SJCLibIntern::BrowseCallbackProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		//Variables
		SJCLib::CString title;
		uint32 flags;
		const CWindow *pParentWindow;
		CWindow *pBrowseDialog;
	protected:
		//Message-callbacks
		virtual void OnChangeSelection(LPITEMIDLIST id);
		//Functions
		void EnableOKButton(bool enable);
	public:
		//Constructor
		CFolderDialog();
		//Functions
		void Create(SJCLib::CString title, uint32 flags, const CWindow *pParentWindow);
		static SJCLib::CString GetString(LPITEMIDLIST id);
		LPITEMIDLIST Run();
	};
}

/*
namespace SJCLibWindows
{
	class SJCLIB_API CFolderDialog : public CDialog
	{
	private:
		//Variables
		CWindow *pBrowseDialog;
	public:
	//Destructor
		~CFolderDialog();
	};
}*/