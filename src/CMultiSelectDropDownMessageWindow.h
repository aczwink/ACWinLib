#pragma once
//Local
#include "CWindow.h"

//Forward Declarations
namespace SJCWinLib
{
	class CMultiSelectDropDown;
}

namespace SJCLibIntern
{
	class CMultiSelectDropDownMessageWindow : public SJCWinLib::CWindow
	{
	private:
		//Variables
		SJCWinLib::CMultiSelectDropDown *pCtrl;
		//Message-callbacks
		void OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y);
	public:
		//Functions
		void Create(SJCWinLib::CMultiSelectDropDown &refCtrl);
	};
}