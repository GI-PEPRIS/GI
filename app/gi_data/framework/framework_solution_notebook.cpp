// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#include "framework_solution_notebook.h"
#include "framework_data_macroes.h"

#include "gis/gis_solution_maplayer_explorer_treectrl.h"

// icons
#include "xpm/solution/gis explorer/huihua.xpm" 
#include "xpm/solution/gis explorer/dongtai.xpm" 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
giDataSolutionNotebook::giDataSolutionNotebook(wxWindow* parent, \
	const wxString &solution_name, \
	wxWindowID id, const wxPoint& pos, const wxSize& size, long style) \
	: giDataAuiNotebook(parent, solution_name, id, pos, size, style)
{
}

giDataSolutionNotebook::~giDataSolutionNotebook()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
long giDataSolutionNotebook::CreateDBUserManagementExplorer(long explorer_window_id)
{
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
long giDataSolutionNotebook::CreateMapCatelogueExplorer(long explorer_window_id)
{
	// background sizers' layout
	wxBoxSizer* explorer_sizer = new wxBoxSizer(wxVERTICAL);
	explorer_sizer->AddSpacer(PX_BASESIZER_TO_UPPER_BORDER);

	wxPanel *explorer_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	explorer_panel->SetSizer(explorer_sizer);

	wxBoxSizer* top_order_commands_sizer = new wxBoxSizer(wxHORIZONTAL);
	explorer_sizer->Add(top_order_commands_sizer, 0, wxLEFT | wxRIGHT | wxTOP, PX_SIZER_TO_SIZER_VECTICAL);

	wxBoxSizer* top_search_sizer = new wxBoxSizer(wxHORIZONTAL);
	explorer_sizer->Add(top_search_sizer, 0, wxLEFT | wxRIGHT | wxTOP, PX_SIZER_TO_SIZER_VECTICAL);

	wxBoxSizer* layer_tree_sizer = new wxBoxSizer(wxHORIZONTAL);
	explorer_sizer->Add(layer_tree_sizer, 1, wxALL | wxEXPAND, PX_SIZER_TO_SIZER_VECTICAL);

	//
	// top commands
	{
		// rendering order btn
		{
			wxBitmap btn_bitmap;
			btn_bitmap.CopyFromIcon(wxIcon(huihua_xpm));
			wxBitmapButton *render_order_btn = new wxBitmapButton(explorer_panel, explorer_window_id++/*wxID_ANY*/, btn_bitmap, wxDefaultPosition, wxSize(PX_SMALL_BTN_WIDTH, PX_SMALL_BTN_HEIGHT), wxBU_AUTODRAW);
			render_order_btn->SetToolTip(_(wxT("List in layer rendering order")));
			top_order_commands_sizer->Add(render_order_btn, 0, wxRIGHT, PX_CTRL_TO_CTRL_HORIZONTAL);
		}

		// source order btn
		{
			wxBitmap btn_bitmap;
			btn_bitmap.CopyFromIcon(wxIcon(dongtai_xpm));
			wxBitmapButton *source_order_btn = new wxBitmapButton(explorer_panel, explorer_window_id++/*wxID_ANY*/, btn_bitmap, wxDefaultPosition, wxSize(PX_SMALL_BTN_WIDTH, PX_SMALL_BTN_HEIGHT), wxBU_AUTODRAW);
			source_order_btn->SetToolTip(_(wxT("List in data source or path order")));
			top_order_commands_sizer->Add(source_order_btn, 0, wxRIGHT, PX_CTRL_TO_CTRL_HORIZONTAL);
		}

		//
	}

	// top search text
	{
		// search text ctrl
		{
			wxTextCtrl *search_textctrl = new wxTextCtrl(explorer_panel, explorer_window_id++/*wxID_ANY*/, wxT(""), wxDefaultPosition, wxSize(this->GetSize().GetX()-2* PX_SMALL_BTN_WIDTH, PX_SMALL_BTN_HEIGHT));
			top_search_sizer->Add(search_textctrl, 0, wxRIGHT, PX_CTRL_TO_CTRL_HORIZONTAL);
		}

		// btns
		{
			wxButton *prev_btn = new wxButton(explorer_panel, explorer_window_id++/*wxID_ANY*/, _(wxT("¡ü")), wxDefaultPosition, wxSize(PX_SMALL_BTN_WIDTH, PX_SMALL_BTN_HEIGHT));
			top_search_sizer->Add(prev_btn, 0, wxRIGHT, PX_CTRL_TO_CTRL_HORIZONTAL);
		}
		{
			wxButton *next_btn = new wxButton(explorer_panel, explorer_window_id++/*wxID_ANY*/, _(wxT("¡ý")), wxDefaultPosition, wxSize(PX_SMALL_BTN_WIDTH, PX_SMALL_BTN_HEIGHT));
			top_search_sizer->Add(next_btn, 0, wxRIGHT, PX_CTRL_TO_CTRL_HORIZONTAL);
		}
	}

	// map layers or explorer
	giGISMapLayerExplorerTreeCtrl *layertree;
	{
		int style = wxTR_DEFAULT_STYLE | wxTR_EDIT_LABELS | wxEXPAND | wxTR_HAS_VARIABLE_ROW_HEIGHT;
		layertree = new giGISMapLayerExplorerTreeCtrl(explorer_panel, explorer_window_id,
			wxDefaultPosition, wxDefaultSize, wxString("map layer tree"), style | wxTR_MULTIPLE);
		
		//layertree->LoadNodeImageIcons();
		//layertree->LoadNodeStateIcons();

		//
		layer_tree_sizer->Add(layertree, 1, wxALL | wxEXPAND, 0);
	}

	//
	explorer_sizer->AddSpacer(PX_BASESIZER_TO_BOTTOM_BORDER);	
	explorer_panel->SetSizer(explorer_sizer);
	explorer_panel->Layout();
	explorer_sizer->Fit(explorer_panel);

	//
	wxBitmap tab_bitmap;
	tab_bitmap.CopyFromIcon(wxIcon(huihua_xpm));
	this->AddPage(explorer_panel, _(wxT("Map Catalogue")), true, tab_bitmap);

	// reserve 10000 even ids for running time consuming
	return layertree->LoadTreeItems()+10000;
}

long giDataSolutionNotebook::CreateVectorMapAnalysisExplorer(long explorer_window_id)
{
	return explorer_window_id;
}
long giDataSolutionNotebook::CreateRasterMapAnalysisExplorer(long explorer_window_id)
{
	return explorer_window_id;
}
long giDataSolutionNotebook::CreateContourMapAnalysisExplorer(long explorer_window_id)
{
	return explorer_window_id;
}