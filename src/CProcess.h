/*#pragma once
//Global
#include <Windows.h>
//SJCLib
#include <SJCLib.h>

namespace SJCLibWindows
{
	class SJCLIB_API CProcess
	{
	private:
		HANDLE hProcess;
	public:
		//Constructor
		CProcess();
		//Functions
		uint32 GetExitCode();
		void Open(uint32 accessFlags, bool inherit, uint32 processId);
	};
}*/