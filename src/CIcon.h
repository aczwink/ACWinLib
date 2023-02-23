#pragma once
//Local
#include "CGDIObject.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CIcon
	{
		friend class CModule;
	private:
		//Variables
		HICON hIcon;
	public:
		//Constructor
		CIcon();
		//Destructor
		~CIcon();
		//Functions
		void Destroy();
		void LoadSystemIcon(LPCTSTR iconName);
	};
}