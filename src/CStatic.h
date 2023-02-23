#pragma once
//Local
#include "CSystemWindow.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CStatic : public CSystemWindow
	{
	private:
		//Variables
		EAlignment alignment;
		CFont font;
		CColor textColor;
		SJCLib::CString text;
		//Message-callbacks
		void OnPaint();
		void OnSetFont(const CFont &refFont);
	public:
		//Functions
		void Create(SJCLib::CString text, uint32 styleFlags, const CWindow &refParentWindow);
		void SetText(SJCLib::CString text);
		//Inline Functions
		inline void SetTextAlignment(EAlignment alignment)
		{
			this->alignment = alignment;
		}

		inline void SetTextColor(const CColor &refColor)
		{
			this->textColor = refColor;
		}
	};
}