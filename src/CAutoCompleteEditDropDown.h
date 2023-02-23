#pragma once
//Local
#include "CSystemWindow.h"
#include "CListBox.h"

//Forward Declarations
namespace SJCLibIntern
{
	LRESULT CALLBACK EditSubclassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

namespace SJCWinLib
{
	class CAutoCompleteEdit;
}

namespace SJCLibIntern
{
	class CAutoCompleteEditDropDownList : public SJCWinLib::CListBox
	{
	};
	
	class CAutoCompleteEditDropDown : public SJCWinLib::CSystemWindow
	{
		friend LRESULT CALLBACK SJCLibIntern::EditSubclassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		friend class SJCWinLib::CAutoCompleteEdit;
		friend class CAutoCompleteEditMessageWindow;
	private:
		//Variables
		SJCWinLib::CAutoCompleteEdit *pParentCtrl;
		CAutoCompleteEditDropDownList list;
		//Message-callbacks
		void OnSize(WPARAM resizingType, uint32 newWidth, uint32 newHeight);
	public:
		//Functions
		void Create(SJCWinLib::CAutoCompleteEdit *pParentCtrl);
	};
}