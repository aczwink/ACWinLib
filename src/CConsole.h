#pragma once
//Global
#include <Windows.h>
//Local
#include "Definitions.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CConsole
	{
	private:
		//Variables
		HANDLE hConsole;
	public:
		//Functions
		uint32 FillOutputCharacter(char c, uint16 x, uint16 y, uint32 length);
		void GetCursorPosition(COORD *pCoord) const;
		void GetScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFO *pCSBI) const;
		uint32 GetMode() const;
		void GetStdIn();
		void GetStdOut();
		uint32 ReadInput(INPUT_RECORD *pRecords, uint32 nBufElements);
		void SetCursorPosition(COORD pCoord);
		void SetMode(uint32 mode);
		uint32 Write(SJCLib::CString text);
	};
}