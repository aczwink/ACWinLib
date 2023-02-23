//Class Header
#include "CImageList.h"
//Namespaces
using namespace SJCWinLib;

//Constructor
CImageList::CImageList()
{
	this->hImgList = NULL;
}

//Public Functions
void CImageList::Create(uint16 width, uint16 height, uint32 flags, uint16 nImages, uint16 nGrow)
{
	this->hImgList = ImageList_Create(width, height, flags, nImages, nGrow);
}