#pragma once
//Global
#include <Windows.h>
//Local
#include "Definitions.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CFile
	{
	protected:
		//Members
		HANDLE hFile;
	public:
		//Constructor
		CFile();
		//Destructor
		~CFile();
		//Methods
		void Close();

		//Inline methods
		inline uint64 GetLastUpdateTime()
		{
			FILETIME time;
			
			GetFileTime(this->hFile, NULL, NULL, &time);

			return ((((uint64)time.dwHighDateTime) << 32) | time.dwLowDateTime);
		}
	};
}