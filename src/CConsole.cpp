//Class Header
#include "CConsole.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Public Functions
uint32 CConsole::FillOutputCharacter(char c, uint16 x, uint16 y, uint32 length)
{
	COORD coord;
	uint32 numberOfCharsWritten;

	coord.X = x;
	coord.Y = y;
	FillConsoleOutputCharacter(this->hConsole, c, length, coord, (DWORD *)&numberOfCharsWritten);

	return numberOfCharsWritten;
}

void CConsole::GetCursorPosition(COORD *pCoord) const
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	this->GetScreenBufferInfo(&csbi);

	memcpy(pCoord, &csbi.dwCursorPosition, sizeof(csbi.dwCursorPosition));
}

void CConsole::GetScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFO *pCSBI) const
{
	GetConsoleScreenBufferInfo(this->hConsole, pCSBI);
}

uint32 CConsole::GetMode() const
{
	uint32 mode;

	GetConsoleMode(this->hConsole, (DWORD *)&mode);

	return mode;
}

void CConsole::GetStdIn()
{
	this->hConsole = GetStdHandle(STD_INPUT_HANDLE);
}

void CConsole::GetStdOut()
{
	this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

uint32 CConsole::ReadInput(INPUT_RECORD *pRecords, uint32 nBufElements)
{
	uint32 nEventsRead;

	ReadConsoleInput(this->hConsole, pRecords, nBufElements, (DWORD *)&nEventsRead);

	return nEventsRead;
}

void CConsole::SetCursorPosition(COORD pCoord)
{
	SetConsoleCursorPosition(this->hConsole, pCoord);
}

void CConsole::SetMode(uint32 mode)
{
	SetConsoleMode(this->hConsole, mode);
}

uint32 CConsole::Write(CString text)
{
	uint32 numberOfCharsWritten;

	WriteConsole(this->hConsole, text.GetC_Str(), text.GetLength(), (DWORD *)&numberOfCharsWritten, NULL);

	return numberOfCharsWritten;
}