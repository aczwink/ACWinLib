//Class Header
#include "CApplication.h"
//Global
#include <Windows.h>
#include <CommCtrl.h>
//Local
#include "__CWindows.h"
#include "__WndProc.h"
//Namespaces
using namespace SJCLibIntern;
using namespace SJCLib;
using namespace SJCWinLib;

//Constructor
CApplication::CApplication()
{
	HMODULE hModule;
	WNDCLASSEX wcex;
	INITCOMMONCONTROLSEX iccex;
	
	iccex.dwSize = sizeof(iccex);
	iccex.dwICC = ICC_BAR_CLASSES | ICC_LINK_CLASS | ICC_LISTVIEW_CLASSES | ICC_STANDARD_CLASSES | ICC_TAB_CLASSES | ICC_TREEVIEW_CLASSES;
	
	InitCommonControlsEx(&iccex);
	
	hModule = GetModuleHandle(NULL);

	MemZero(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(wcex);
	wcex.hInstance = hModule;
	wcex.lpfnWndProc = SJCLibIntern::WndProc;
	
	wcex.lpszClassName = SJCWINLIB_WNDCLASS_DEFAULT;
	if(!RegisterClassEx(&wcex))
	{
		ASSERT(0);
	}

	OleInitialize(NULL);
}

//Destructor
CApplication::~CApplication()
{
	HMODULE hModule;
	
	hModule = GetModuleHandle(NULL);
	
	if(!UnregisterClass(SJCWINLIB_WNDCLASS_DEFAULT, hModule))
	{
		ASSERT(0);
	}

	OleUninitialize();
}

//Public Functions
int32 CApplication::Run()
{
	MSG msg = {0};

	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		if(CWindows::GetCurrentDialog() == NULL || !IsDialogMessage(CWindows::GetCurrentDialog(), &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int32)msg.wParam;
}

int32 CApplication::Run(const CFrame &refFrame, HACCEL hAccelTable)
{
	MSG msg = {0};
	
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		if(!TranslateAccelerator(refFrame.hWnd, hAccelTable, &msg))
		{
			if(CWindows::GetCurrentDialog() == NULL || !IsDialogMessage(CWindows::GetCurrentDialog(), &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	
	return (int32)msg.wParam;
}