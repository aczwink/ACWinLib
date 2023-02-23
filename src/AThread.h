#pragma once
//SJCLib
#include <SJCLib.h>
//Global
#include <Windows.h>
//Local
#include "Definitions.h"

namespace SJCLibIntern
{
	uint32 __stdcall ThreadProc(void *pThreadParameter);
}

namespace SJCWinLib
{
	class SJCWINLIB_API AThread
	{
		friend uint32 __stdcall SJCLibIntern::ThreadProc(void *pThreadParameter);
	private:
		//Variables
		HANDLE hThread;
		//Callbacks
		virtual uint32 Procedure() = NULL;
	public:
		//Constructor
		inline AThread()
		{
			this->hThread = NULL;
		}

		//Destructor
		inline ~AThread()
		{
			this->Release();
		}

		//Functions
		void Create(bool createSuspended = false);

		inline uint32 GetExitCode()
		{
			uint32 exitCode;

			GetExitCodeThread(this->hThread, (DWORD *)&exitCode);

			return exitCode;
		}

		inline void Release()
		{
			if(this->hThread)
			{
				CloseHandle(this->hThread);
				this->hThread = NULL;
			}
		}

		inline uint32 Resume()
		{
			return ResumeThread(this->hThread);
		}
	};
}