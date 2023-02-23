//Class Header
#include "CGDIObject.h"
//Local
#include "__CWindows.h"
//Namespaces
using namespace SJCLibIntern;
using namespace SJCWinLib;

//Constructor
CGDIObject::CGDIObject()
{
	this->hGDIObj = NULL;
}

//Destructor
CGDIObject::~CGDIObject()
{
	this->Release();
}

//Public Functions
void CGDIObject::Release()
{
	if(this->hGDIObj && !CWindows::GDIReleaseReferenceCount(this->hGDIObj))
	{
		DeleteObject(this->hGDIObj);
	}
	this->hGDIObj = NULL;
}