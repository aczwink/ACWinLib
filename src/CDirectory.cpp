//Class Header
#include "CDirectory.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Public methods
bool CDirectory::Open(const CWString &refDirName)
{
	this->Close();
	this->hFile = CreateFileW(refDirName.GetC_Str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

	if(this->hFile == INVALID_HANDLE_VALUE)
	{
		this->hFile = NULL;
		return false;
	}

	return true;
}