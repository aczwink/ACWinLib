#pragma once
//Global
#include <Windows.h>
#include <shellapi.h>
//Local
#include "CMessageWindow.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CDrop
	{
		//Procedures
		friend bool SJCLibIntern::ForwardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		//Variables
		HDROP hDrop;
	public:
		//Destructor
		~CDrop();
		//Functions
		SJCLib::CWString GetFileName(uint32 index) const;
		//Inline
		inline uint32 GetNumberOfFiles() const
		{
			return DragQueryFile(this->hDrop, 0xFFFFFFFF, NULL, 0);
		}
	};
}