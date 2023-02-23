#pragma once
//Local
#include "CButton.h"
#include "CComboBox.h"
#include "CCommonButtonClose.h"
#include "CDialog.h"

namespace SJCLibIntern
{
	class CSelectList : public SJCWinLib::CComboBox
	{
	private:
		//Message-callbacks
		void OnChangeSelection();
	};

	class CSelectDialogButtonOK : public SJCWinLib::CButton
	{
	private:
		//Message-callbacks
		void OnClick();
	};
};

namespace SJCWinLib
{
	class SJCWINLIB_API CSelectDialog : public CDialog
	{
		friend class SJCLibIntern::CSelectList;
		friend class SJCLibIntern::CSelectDialogButtonOK;
	private:
		//Variables
		uint32 selection;
		CFont font;
		SJCLib::CArray<SJCLib::CString> selections;
		//Children
		SJCLibIntern::CSelectList selectBox;
		SJCLibIntern::CSelectDialogButtonOK buttonOK;
		CCommonButtonClose buttonCancel;
		//Message-callbacks
		void OnInit();
	public:
		//Functions
		void AddSelection(SJCLib::CString title);
		void Create(SJCLib::CString caption, const CWindow &refParentWindow);
		int32 GetSelection();
		void PreSelect(uint32 index);
	};
}