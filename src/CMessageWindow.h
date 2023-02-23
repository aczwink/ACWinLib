#pragma once
//Global
#include <Windows.h>
//Local
#include "Definitions.h"

namespace SJCLibIntern
{
	bool ForwardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}

namespace SJCWinLib
{
	/*
	Message-only window

	Mouse messages can be processed if window captures mouse.
	*/
	class SJCWINLIB_API CMessageWindow
	{
		//Procedures
		friend bool SJCLibIntern::ForwardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		//Callbacks
		virtual void OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y);
		virtual void OnUserMessage(UINT message, WPARAM wParam, LPARAM lParam);
	protected:
		//Variables
		HWND hWnd;
		//Functions
		static void RespondDefault();
	public:
		//Constructor
		CMessageWindow();
		//Destructor
		~CMessageWindow();
		//Operators
		inline bool operator==(const CMessageWindow &refWnd) const
		{
			return this->hWnd == refWnd.hWnd;
		}
		//Functions
		void Create();
		const CMessageWindow *SetCapture() const;

		//Inline
		inline bool WindowExists() const
		{
			return IsWindow(this->hWnd) != 0;
		}
	};
}