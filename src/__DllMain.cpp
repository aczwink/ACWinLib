//Global
#include <Windows.h>
//Local
#include "__CWindows.h"

BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD dwReason, LPVOID lpvReserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		SJCLibIntern::CWindows::Release();
		break;
	}
	return TRUE;
}