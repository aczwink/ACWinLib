#pragma once
//Local
#include "CEdit.h"
#include "CAutoCompleteEditDropDown.h"
#include "CAutoCompleteEditMessageWindow.h"

//Forward Declarations
namespace SJCLibIntern
{
	LRESULT CALLBACK EditSubclassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

namespace SJCWinLib
{
	class SJCWINLIB_API CAutoCompleteEdit : public CEdit
	{
		friend LRESULT CALLBACK SJCLibIntern::EditSubclassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		friend class SJCLibIntern::CAutoCompleteEditMessageWindow;
	private:
		//Variables
		WNDPROC origWndProc;
		SJCLibIntern::CAutoCompleteEditDropDown dropDownWindow;
		SJCLibIntern::CAutoCompleteEditMessageWindow messageWindow;
		SJCLib::CString seperator;
		SJCLib::CArray<SJCLib::CString> choices;
		//Message-callbacks
		void OnChange();
		//Functions
		void Filter();
		int32 GetNextSeperator();
		int32 GetPreviousSeperator();
	public:
		//Functions
		void AddChoice(SJCLib::CString text);
		void Complete();
		void Create(uint32 styleFlags, uint32 exStyleFlags, uint16 x, uint16 y, uint16 width, uint16 height, const CWindow &refParentWindow);

		inline void Create(uint32 styleFlags, uint32 exStyleFlags, const CRect &refRect, const CWindow &refParentWindow)
		{
			this->Create(styleFlags, exStyleFlags, (uint16)refRect.left, (uint16)refRect.top, refRect.GetWidth(), refRect.GetHeight(), refParentWindow);
		}

		void SetFont(const CFont &refFont);
		void SetSeperator(SJCLib::CString text);
	};
	/*class SJCWINLIB_API CAutoCompleteEdit : public CControl
	{
	private:
		//Variables
		uint32 caretCharPos;
		uint32 drawFrom;
		CFont font;
		TEXTMETRIC fontMetrics;
		SJCLibString::CString text;
		//Message-callbacks
		void OnChar(uint16 characterCode, uint16 repeatCount, byte scanCode, bool isExtendedKey, bool isAltKeyPressed, bool previousKeyState, bool transitionTable);
		void OnFocus(CWindow *pPreviousFocusedWindow);
		void OnKeyDown(uint16 characterCode, uint16 repeatCount, byte scanCode, bool isExtendedKey, bool previousKeyState);
		void OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y);
		void OnLooseFocus(CWindow *pUpcomingFocusedWindow);
		uint32 OnGetDialogCode(uint16 virtualKeyCode);
		void OnPaint();
		void OnSetFont(const CFont &refFont);
		//Functions
		void AddChar(char c);
		uint16 GetNumberOfCharsToFit();
		void Scroll(bool left);
		void UpdateCaretPos();
		void UpdateCaretPos(uint16 x);
	public:
		//Constructor
		CAutoCompleteEdit();
		//Functions
	};*/
};