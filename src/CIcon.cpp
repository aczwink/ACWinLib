//Class Header
#include "CIcon.h"
//Namespaces
using namespace SJCWinLib;

//Constructor
CIcon::CIcon()
{
	this->hIcon = NULL;
}

//Destructor
CIcon::~CIcon()
{
	this->Destroy();
}

//Public Functions
void CIcon::Destroy()
{
	DestroyIcon(this->hIcon);
	this->hIcon = NULL;
}

void CIcon::LoadSystemIcon(LPCTSTR iconName)
{
	this->hIcon = LoadIcon(NULL, iconName);
}

/*
void CIcon::Attach(HICON hIcon)
{
	this->hIcon = hIcon;
}
*/