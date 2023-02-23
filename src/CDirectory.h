#pragma once
//Local
#include "CFile.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CDirectory : public CFile
	{
	public:
		//Methods
		bool Open(const SJCLib::CWString &refDirName);
	};
}