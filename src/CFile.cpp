//Class Header
#include "CFile.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Constructor
CFile::CFile()
{
	this->hFile = NULL;
}

//Destructor
CFile::~CFile()
{
	this->Close();
}

//Public Methods
void CFile::Close()
{
	if(this->hFile)
	{
		CloseHandle(this->hFile);
		this->hFile = NULL;
	}
}