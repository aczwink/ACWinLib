#pragma once
//Local
#include "CWindow.h"
#include "CTheme.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CTab : public CWindow
	{
		struct STab
		{
			SJCLib::CWString title;
			//SJCLib::CPointer<CWindow> pTabChild; //ASSERTMSG(0, "must be reimplemented, because of CPOINTER");
			CRect itemRect;
			int32 stateId;
		};
	private:
		//Variables
		uint32 activeTabIndex;
		SJCLib::CArray<STab> tabs;
		CTheme theme;
		CFont font;
		uint16 tabHeight;
		//Callbacks
		void OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y);
		void OnMouseMove(uint16 keys);
		void OnPaint();
		void OnSize(WPARAM resizingType, uint32 newWidth, uint32 newHeight);
		//Functions
		void DrawItem(uint32 index, SJCLib::CPointer<CDeviceContext> &refpMemDC);
		CRect GetChildWindowArea() const;
		CRect GetInnerWindowArea() const;
		void RecalcItemRect(uint32 index);
		void Refresh();
	public:
		//Constructor
		CTab();
		//Destructor
		~CTab();
		//Functions
		uint32 AddTab(const SJCLib::CWString &refTitle, const SJCLib::CPointer<CWindow> &refpTabChild);
		void Create(const CWindow &refParentWindow);
		void Release();
		void Select(uint32 index);
		//Inline
		inline int32 GetActiveTab() const
		{
			if(this->tabs.IsEmpty())
				return -1;
			return this->activeTabIndex;
		}
		
		inline CWindow *GetChildWindow(uint32 tabIndex)
		{
			ASSERT(tabIndex < this->tabs.GetNoOfElements());
			
			ASSERTMSG(0, "must be reimplemented, because of pTabChild");
			return NULL;
			//return this->tabs[tabIndex].pTabChild.GetPointer();
		}
	};
}