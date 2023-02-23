/*//Local
#include "CControl.h"
#include "CDeviceContext.h"
//Definitions
#define CLISTBOXEX_CLASSNAME "CListBoxEx"
#define SELECTION_NONE -1
#define COLUMN_AUTOSIZE 0

namespace SJCLibIntern
{
	struct ListBoxExColumn
	{
		SJCLibString::CString caption;
		uint16 width;
	};
}

namespace SJCLibWindows
{
	enum CListBoxExStyle
	{
		CLISTBOXEXSTYLE_INNERCOLUMNPADDING,
		CLISTBOXEXSTYLE_INNERCELLPADDING
	};

	class SJCLIB_API CListBoxEx : public CControl
	{
	private:
		//Variables
		CFont font;
		SJCLib::CArray<SJCLibIntern::ListBoxExColumn> columns;
		SJCLib::CArray<SJCLib::CArray<SJCLibString::CString>> cells;
		uint16 columnRowHeight;
		uint16 fontHeight;
		int32 selection;
		struct
		{
			uint16 innerColumnPadding;
			uint16 innerCellPadding;
		} style;
		//Callbacks
		void OnLeftMouseButtonDown(uint16 keys, uint16 x, uint16 y);
		void OnMouseWheel(int16 zDelta, uint16 keys);
		void OnPaint();
		void OnSetFont(CFont *pFont);
		void OnVerticalScroll(uint16 scrollCode);
		//Functions
		uint16 CalculateAutoColumnSize(uint16 columnIndex);
		uint16 FindElementFromHeight(uint32 pos);
		uint32 GetBasePos(uint32 pos);
		uint32 GetOverallHeight();
		uint16 GetRowHeight(uint16 rowIndex);
		void RecalcScrollBar();
		void RegisterWindowClass(HINSTANCE hInstance);
		void UpdateFontHeight();
	public:
		//Constructor
		CListBoxEx();
		//Functions
		void AddColumn(SJCLibString::CString caption, uint16 width = COLUMN_AUTOSIZE);
		void AddRow(SJCLibString::CString text);
		SJCLib::SJCLibResult Create(DWORD style, int x, int y, int width, int height, CWindow *parentWindow);
		uint16 GetColumnWidth(uint16 columnIndex);
		int32 GetControlStyle(CListBoxExStyle style);
		uint16 GetRowCount();
		void SetCellText(uint16 rowIndex, uint16 columnIndex, SJCLibString::CString text);
		void SetColumnText(uint16 index, SJCLibString::CString caption);
		void SetColumnWidth(uint16 index, uint16 width);
		void SetControlStyle(CListBoxExStyle style, int32 value);
	};
}*/