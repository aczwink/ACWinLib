#pragma once
//Local
#include "CSystemWindow.h"
#include "CMultiSelectList.h"

//Forward Declarations
namespace SJCWinLib
{
	class CMultiSelectDropDown;
}

namespace SJCLibIntern
{
	class CMultiSelectList : public SJCWinLib::CMultiSelectList
	{
	private:
		//Callbacks
		void OnSelectionChange();
	};

	class CMultiSelectDropDownDropDown : public SJCWinLib::CSystemWindow
	{
		friend class CMultiSelectList;
		friend class SJCWinLib::CMultiSelectDropDown;
	private:
		//Variables
		SJCWinLib::CMultiSelectDropDown *pCtrl;
		//Message-callbacks
		void OnSize(WPARAM resizingType, uint32 newWidth, uint32 newHeight);
		//Functions
		uint32 CalculateHeight();
	public:
		//Variables
		CMultiSelectList list;
		//Functions
		void Create(SJCWinLib::CMultiSelectDropDown &refParentCtrl);
	};
}