#pragma once
//Local
#include "CFile.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CReadFile : public CFile
	{
	public:
		//Methods
		bool Open(const SJCLib::CWString &refFileName);
	};
}