/*#pragma once
//Global
#include <Windows.h>
#include <ShellAPI.h>
//Local
#include "SJCLib.h"
#include "SJCLibString.h"
#include "CApplication.h"
#include "CIcon.h"
#include "CWindow.h"

namespace SJCLIB_NAMESPACE_INTERN
{
	class CTrayWindow : public SJCLibWindows::CWindow
	{
		friend class SJCLibWindows::CTrayIcon;
	private:
		//Variables
		SJCLibWindows::CTrayIcon *trayIcon;
		//Callbacks
		void OnUserMessage(UINT message, WPARAM wParam, LPARAM lParam);
	};
}

namespace SJCLibWindows
{
	class SJCLIB_API CTrayIcon
	{
		friend class SJCLIB_NAMESPACE_INTERN::CTrayWindow;
	private:
		//Variables
		NOTIFYICONDATA nid;
		//Callbacks
		virtual void OnClick();
		virtual void OnRightClick();
	protected:
		//Variables
		SJCLIB_NAMESPACE_INTERN::CTrayWindow trayWindow;
	public:
		//Constructor
		CTrayIcon();
		//Destructor
		~CTrayIcon();
		//Functions
		void Add();
		void Init(CApplication *pApp);
		void Remove();
		void SetIcon(CIcon *pIcon, SJCLibString::CString toolTip);
	};
}*/