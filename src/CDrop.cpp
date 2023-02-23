//Class Header
#include "CDrop.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Destructor
CDrop::~CDrop()
{
	DragFinish(this->hDrop);
}

//Public Functions
CWString CDrop::GetFileName(uint32 index) const
{
	wchar_t *pStr;
	uint32 nChars;
	CWString result;

	nChars = DragQueryFile(this->hDrop, index, NULL, 0);
	nChars++; //must include the null byte cause otherwise DragQueryFile cuts the string
	pStr = (wchar_t *)malloc(nChars * sizeof(*pStr));
	DragQueryFileW(this->hDrop, index, pStr, nChars);
	result = pStr;
	free(pStr);

	return result;
}