//Global
#include <Windows.h>
//SJCLib
#include <SJCLib.h>

namespace SJCLibIntern
{
	//Global Variables
	extern bool g_respondDefaultToCurrentMessage;
	extern LRESULT g_messageResult;
	//Functions
	LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool ForwardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}