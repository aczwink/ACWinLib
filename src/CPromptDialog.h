#pragma once
//Local
#include "CButton.h"
#include "CCommonButtonClose.h"
#include "CDialog.h"
#include "CEdit.h"

namespace SJCLibIntern
{
	class CPromptDialogButtonOK : public SJCWinLib::CButton
	{
	private:
		//Message-callbacks
		void OnClick();
	};
};

namespace SJCWinLib
{
	class SJCWINLIB_API CPromptDialog : public CDialog
	{
		friend class SJCLibIntern::CPromptDialogButtonOK;
	private:
		//Variables
		bool hasTextLimit;
		uint32 textLimit;
		CFont font;
		SJCLib::CString text;
		CEdit editText;
		SJCLibIntern::CPromptDialogButtonOK buttonOK;
		CCommonButtonClose buttonCancel;
		//Message-callbacks
		void OnInit();
	public:
		//Functions
		void Create(SJCLib::CString caption, SJCLib::CString value, const CWindow *pParentWindow);
		SJCLib::CString GetValue();

		//Inline
		inline void SetTextLimit(uint32 nChars)
		{
			this->hasTextLimit = true;
			this->textLimit = nChars;
		}
	};
}