#pragma once
//Global
#include <Windows.h>
//SJCLib
#include <SJCLib.h>

namespace SJCWinLib
{
	class CEvent
	{
	private:
		//Variables
		HANDLE hEvent;
	public:
		//Constructor
		inline CEvent()
		{
			this->hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		}

		//Destructor
		inline ~CEvent()
		{
			CloseHandle(this->hEvent);
		}

		//Functions
		inline void Set()
		{
			SetEvent(this->hEvent);
		}

		inline uint32 Wait(uint32 timeOutInMilliseconds)
		{
			return WaitForSingleObject(this->hEvent, timeOutInMilliseconds);
		}
	};
}