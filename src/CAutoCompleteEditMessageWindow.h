#pragma once
//Local
#include "CCursor.h"
#include "CWindow.h"

//Forward Declarations
namespace SJCWinLib
{
	class CAutoCompleteEdit;
}

namespace SJCLibIntern
{
	class CAutoCompleteEditMessageWindow : public SJCWinLib::CWindow
	{
	private:
		//Variables
		SJCWinLib::CAutoCompleteEdit *pCtrl;
		SJCWinLib::CCursor cursorArrow;
		SJCWinLib::CCursor cursorIBeam;
		//Message-callbacks
		void OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y);
		void OnMouseMove(uint16 keys);
	public:
		//Functions
		void Create(SJCWinLib::CAutoCompleteEdit *pCtrl);
	};
}