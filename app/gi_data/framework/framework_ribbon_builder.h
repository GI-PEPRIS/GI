// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_DATA_RIBBON_BUILDER_H_
#define _GI_GUI_FRAMEWORK_DATA_RIBBON_BUILDER_H_

#include "wx/wx.h"

#include "wx/textctrl.h"
#include "wx/ribbon/bar.h"
#include "wx/ribbon/buttonbar.h"
#include "wx/ribbon/gallery.h"
#include "wx/ribbon/toolbar.h"
#include "wx/sizer.h"
#include "wx/menu.h"
#include "wx/msgdlg.h"
#include "wx/dcbuffer.h"
#include "wx/colordlg.h"
#include "wx/artprov.h"
#include "wx/combobox.h"
#include "wx/tglbtn.h"
#include "wx/wrapsizer.h"
#include "wx/spinctrl.h"

//  builder design model
class giDataRibbonBuilder
{
	//enum
	//{
	//	ID_BUTTON_XX,
	//	ID_BUTTON_XY,
	//	ID_Commbox1,
	//	ID_checkboxsearchlinkage,
	//	ID_checkboxsearchlinkage2,

	//	ID_CIRCLE = wxID_HIGHEST + 1,
	//	ID_CROSS,
	//	ID_TRIANGLE,
	//	ID_SQUARE,
	//	ID_POLYGON,
	//	ID_SELECTION_EXPAND_H,
	//	ID_SELECTION_EXPAND_V,
	//	ID_SELECTION_CONTRACT,
	//	ID_PRIMARY_COLOUR,
	//	ID_SECONDARY_COLOUR,
	//	ID_DEFAULT_PROVIDER,
	//	ID_AUI_PROVIDER,
	//	ID_MSW_PROVIDER,
	//	ID_MAIN_TOOLBAR,
	//	ID_POSITION_TOP,
	//	ID_POSITION_TOP_ICONS,
	//	ID_POSITION_TOP_BOTH,
	//	ID_POSITION_LEFT,
	//	ID_POSITION_LEFT_LABELS,
	//	ID_POSITION_LEFT_BOTH,
	//	ID_TOGGLE_PANELS,
	//	ID_ENABLE,
	//	ID_DISABLE,
	//	ID_DISABLED,
	//	ID_UI_ENABLE_UPDATED,
	//	ID_CHECK,
	//	ID_UI_CHECK_UPDATED,
	//	ID_CHANGE_TEXT1,
	//	ID_CHANGE_TEXT2,
	//	ID_UI_CHANGE_TEXT_UPDATED,
	//	ID_REMOVE_PAGE,
	//	ID_HIDE_PAGES,
	//	ID_SHOW_PAGES
	//};

	//class ColourClientData : public wxClientData
	//{
	//public:
	//	ColourClientData(const wxString& name, const wxColour& colour)
	//		: m_name(name), m_colour(colour) {}

	//	const wxString& GetName()   const { return m_name; }
	//	const wxColour& GetColour() const { return m_colour; }

	//private:
	//	wxString m_name;
	//	wxColour m_colour;
	//};

	//
	const int RIBBON_DROPDOWN_MAXIMUM = 100;

	// widget type of command
	enum RibbonCommandType
	{
		RCT_BTN = 0,
		RCT_BTN_SMALL,
		RCT_BTN_DROPDOWN,
		RCT_TOOL,
		RCT_TOOL_CHECK,
		RCT_TOOL_DROPDOWN,
		RCT_TOOL_SEPERATOR,
		RCT_COMBOX,
		RCT_CHECKBOX,
		RCT_TEXT_CTRL,
		RCT_TEXT_LABEL,
		RCT_SPINCTRL,

	};
	// the style of commands layout in panel
	enum RibbonPanelLayoutType
	{
		LAYOUT_AS_TOOLBAR = 0,
		LAYOUT_AS_BTNBAR,
		LAYOUT_AS_BOXSIZER,
	};

protected:
	//
	friend class giDataFrame;

	//
	// command -> panel -> page -> ribbon bar
	//
	struct giRibbonCommand : public wxObject
	{
		long m_id;
		int m_group_id;

		wxString m_name;
		char **m_xpm;
		int m_type;// 0:普通btn 1:小btn 2:dropdownbtn 3:普通tool 4：checktool 5：dropdowntool。。。。

		std::vector<wxString> m_dropdown_contents;//dropdown名字 或者 combox内容
		std::vector<long> m_dropdown_ids;//dropdown 菜单id
		std::vector<bool> m_dropdown_ids_checked;//dropdown 菜单id

		// for combox etc
		std::vector<double> m_candidate_values;//初始名称取值

		int m_row;//sizer类型panel 先按col排列 每一个col再分行，每row再按pos排序
		int m_col;
		int m_pos;

		wxString m_default_value;//初始取值
		bool m_is_checked;
		int m_width;
		int	m_height;

		bool m_is_enable;			//可用

		//
		giRibbonCommand()
		{
			SetDefault();
		}
		void SetDefault()
		{
			m_id = -1;
			m_group_id = 0;
			m_name = "";
			m_xpm = 0;
			m_type = 0;
			m_row = 0;
			m_col = 0;
			m_pos = 0;

			m_default_value = "";
			m_is_checked = false;
			m_width = 120;
			m_height = -1;

			m_is_enable = 1;

			m_dropdown_contents.clear();
			m_dropdown_ids.clear();
			m_candidate_values.clear();
		}

		giRibbonCommand(const giRibbonCommand &other)
		{
			*this=other;
		}
		const giRibbonCommand &operator=(const giRibbonCommand &other)
		{
			if (this == &other)
			{
				return *this;
			}

			m_id = other.m_id;
			m_group_id = other.m_group_id;
			m_name = other.m_name;
			m_xpm = other.m_xpm;
			m_type = other.m_type;
			m_row = other.m_row;
			m_col = other.m_col;
			m_pos = other.m_pos;

			m_default_value = other.m_default_value;
			m_is_checked = other.m_is_checked;
			m_width = other.m_width;
			m_height = other.m_height;

			m_is_enable = other.m_is_enable;

			m_dropdown_contents = other.m_dropdown_contents;
			m_dropdown_ids = other.m_dropdown_ids;
			m_candidate_values = other.m_candidate_values;

			return *this;
		}
	};

	struct giRibbonCommandPanel : public wxObject
	{
		long m_id;
		int m_toolbar_id;

		wxString m_name;
		char **m_xpm;
		int m_type;//0 toolbar 1 btn 2 Sizer（尽量使用sizer类型）

		//Sizer类型
		int m_rows;
		int m_cols;
		int m_pos;

		bool m_is_extendable_btn;

		std::vector<giRibbonCommand> m_commands;

		giRibbonCommandPanel()
		{
			m_id = -1;
			m_name = "";
			m_xpm = 0;
			m_rows = 0;
			m_cols = 0;
			m_pos = 0;
			m_toolbar_id = 0;
			m_type = 0;

			m_commands.clear();
			m_is_extendable_btn = false;
		}

		giRibbonCommandPanel(const giRibbonCommandPanel &other)
		{
			*this = other;
		}
		const giRibbonCommandPanel &operator=(const giRibbonCommandPanel &other)
		{
			if (this == &other)
			{
				return *this;
			}

			m_id = other.m_id;
			m_name = other.m_name;
			m_xpm = other.m_xpm;
			m_rows = other.m_rows;
			m_cols = other.m_cols;
			m_pos = other.m_pos;
			m_toolbar_id = other.m_toolbar_id;
			m_type = other.m_type;

			m_commands = other.m_commands;
			m_is_extendable_btn = false;
			return *this;
		}
	};

	struct giRibbonCommandPage
	{
		long m_id;
		wxString m_name;
		char **m_xpm;

		std::vector<giRibbonCommandPanel> m_panels;

		giRibbonCommandPage()
		{
			m_id = -1;
			m_name = "";
			m_xpm = 0;
			m_panels.clear();
		}

		const giRibbonCommandPage &operator=(const giRibbonCommandPage &other)
		{
			if (this == &other)
			{
				return *this;
			}

			m_id = other.m_id;
			m_name = other.m_name;
			m_xpm = other.m_xpm;
			m_panels.clear();

			return *this;
		}
	};

public:
	//
	giDataRibbonBuilder();
	~giDataRibbonBuilder();

public:
	//
	void SetProperty(wxRibbonBar *ribbon_bar);

	void CreateBasicPage();
	void CreateMapPage();
	void CreateRasterPage();
	void CreateContourPage();
	void CreateLogPage();
	void CreateSeismicPage();
	void Create3DPage();
	void CreateAnalysisPage();
	void CreateHelpPage();

	void Realize();

protected:
	//
	wxMenu *GetDropdownMenu(const giRibbonCommand &ribbon_cmd);

	//wxRibbonGallery* PopulateColoursPanel(wxWindow* panel, wxColour def,
	//	int gallery_id);
	//void AddText(wxString msg);
	//wxRibbonGalleryItem* AddColourToGallery(wxRibbonGallery *gallery,
	//	wxString name, wxMemoryDC& dc, wxColour* value = NULL);
	//wxColour GetGalleryColour(wxRibbonGallery *gallery,
	//	wxRibbonGalleryItem* item, wxString* name);
	//void ResetGalleryArtProviders();
	//void SetArtProvider(wxRibbonArtProvider* prov);
	//void SetBarStyle(long style);

private:
    //
	void DoLayoutToolBarPanel(wxRibbonPanel *panel, const giRibbonCommandPanel &panel_info);
	void DoLayoutBtnBarPanel(wxRibbonPanel *panel, const giRibbonCommandPanel &panel_info);
	void DoLayoutBoxSizerPanel(wxRibbonPanel *panel, const giRibbonCommandPanel &panel_info);

public:
	//
	wxRibbonBar *m_ribbon;
	wxMenu *m_dropdown_menu;
	long m_ribbon_event_id;
	std::vector<giRibbonCommandPage> m_pages;

	////
	//wxRibbonGallery* m_primary_gallery;
	//wxRibbonGallery* m_secondary_gallery;

	////
	//wxColourData m_colour_data;
	//wxColour m_default_primary;
	//wxColour m_default_secondary;
	//wxColour m_default_tertiary;
	//wxMemoryDC m_bitmap_creation_dc;
	//bool m_bEnabled;
	//bool m_bChecked;
	//wxString m_new_text;
};

#endif
