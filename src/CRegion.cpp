//Class Header
#include "CRegion.h"
//Namespaces
using namespace SJCWinLib;

//Public Functions
void CRegion::Delete()
{
	if(this->hRgn)
	{
		DeleteObject(this->hRgn);
		this->hRgn = NULL;
	}
}