#pragma once
//Global
#include <Windows.h>
#include <CommCtrl.h>
//Local
#include "Definitions.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CImageList
	{
		friend class CToolBar;
	private:
		//Variables
		HIMAGELIST hImgList;
	public:
		//Constructor
		CImageList();
		//Functions
		void Create(uint16 width, uint16 height, uint32 flags, uint16 nImages, uint16 nGrow);
	};
}