#pragma once
//Global
#include <Windows.h>

namespace SJCWinLib
{
	class CCriticalSection
	{
	private:
		//Variables
		CRITICAL_SECTION cs;
	public:
		//Constructor
		inline CCriticalSection()
		{
			InitializeCriticalSection(&this->cs);
		}

		//Destructor
		inline ~CCriticalSection()
		{
			DeleteCriticalSection(&this->cs);
		}

		//Functions
		inline void Enter()
		{
			EnterCriticalSection(&this->cs);
		}

		inline void Leave()
		{
			LeaveCriticalSection(&this->cs);
		}

		inline bool TryEnter()
		{
			return TryEnterCriticalSection(&this->cs) != 0;
		}
	};
}