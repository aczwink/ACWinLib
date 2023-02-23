#pragma once
//Global
#include <Windows.h>

namespace SJCWinLib
{
	class CCursor
	{
		friend class CModule;
	private:
		//Variables
		HCURSOR hCursor;
	public:
		//Functions
		inline void LoadSystemCursor(const char *pCursorName)
		{
			this->hCursor = LoadCursor(NULL, pCursorName);
		}

		inline CCursor SetAsActive()
		{
			CCursor tmp;
			
			tmp.hCursor = ::SetCursor(this->hCursor);

			return tmp;
		}
	};
}