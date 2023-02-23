#pragma once
//Local
#include "CButton.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CCommonButtonClose : public CButton
	{
	private:
		//Message-callbacks
		void OnClick();
	};
};