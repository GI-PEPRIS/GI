// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#include "framework_ribbon_builder.h"
#include "framework_data_frame.h"
#include "framework_data_app.h"
#include "framework_data_macroes.h"

//
#include "xpm/ribbon/base/linkdb.xpm"		//connect to db
#include "xpm/ribbon/base/newdb.xpm"		//new db
#include "xpm/ribbon/base/updatedb.xpm"		//update db
#include "xpm/ribbon/base/mergedb.xpm"		//merge db
#include "xpm/ribbon/base/authorization.xpm"


#include "xpm/ribbon/base/option.xpm"
#include "xpm/ribbon/base/cancel_32.xpm" 
#include "xpm/ribbon/base/save_32.xpm"
#include "xpm/ribbon/base/edit_32.xpm" 
#include "xpm/ribbon/base/admin_32.xpm"


#include "xpm/ribbon/base/defaultview.xpm"
#include "xpm/ribbon/base/windowsfloat.xpm"
#include "xpm/ribbon/base/windowsdock.xpm"
#include "xpm/ribbon/base/windowsclose.xpm"
#include "xpm/ribbon/base/about.xpm"
#include "xpm/ribbon/base/usermanual.xpm"

//
#include "xpm/ribbon/align_center.xpm"
#include "xpm/ribbon/align_left.xpm"
#include "xpm/ribbon/align_right.xpm"
#include "xpm/ribbon/aui_style.xpm"
#include "xpm/ribbon/auto_crop_selection.xpm"
#include "xpm/ribbon/auto_crop_selection_small.xpm"
#include "xpm/ribbon/circle.xpm"
#include "xpm/ribbon/circle_small.xpm"
#include "xpm/ribbon/colours.xpm"
#include "xpm/ribbon/cross.xpm"
#include "xpm/ribbon/empty.xpm"
#include "xpm/ribbon/expand_selection_v.xpm"
#include "xpm/ribbon/expand_selection_h.xpm"
#include "xpm/ribbon/eye.xpm"
#include "xpm/ribbon/hexagon.xpm"
#include "xpm/ribbon/msw_style.xpm"
#include "xpm/ribbon/position_left_small.xpm"
#include "xpm/ribbon/position_top_small.xpm"
#include "xpm/ribbon/ribbon.xpm"
#include "xpm/ribbon/selection_panel.xpm"
#include "xpm/ribbon/square.xpm"
#include "xpm/ribbon/triangle.xpm"

#include "xpm/ribbon/map/importgis.xpm"
#include "xpm/ribbon/map/zoomin.xpm"
#include "xpm/ribbon/map/zoomout.xpm"
#include "xpm/ribbon/map/zoomfree.xpm"
#include "xpm/ribbon/map/panview.xpm"
#include "xpm/ribbon/map/fullview.xpm"
#include "xpm/ribbon/map/backview.xpm"
#include "xpm/ribbon/map/frontview.xpm"
#include "xpm/ribbon/map/pointview.xpm"
#include "xpm/ribbon/map/editor/create.xpm"
#include "xpm/ribbon/map/editor/editordelete.xpm"
#include "xpm/ribbon/map/editor/move.xpm"
#include "xpm/ribbon/map/editor/reshape.xpm"
#include "xpm/ribbon/map/editor/startedit.xpm"
#include "xpm/ribbon/map/editor/stopedit.xpm"
#include "xpm/ribbon/map/editor/undo.xpm"
#include "xpm/ribbon/map/editor/redo.xpm"
#include "xpm/ribbon/map/editor/saveedit.xpm"
#include "xpm/ribbon/map/editor/rotate.xpm"
#include "xpm/ribbon/map/editor/mirror.xpm"
#include "xpm/ribbon/map/editor/attribute.xpm"
#include "xpm/ribbon/map/editor/Setting.xpm"
#include "xpm/ribbon/map/editor/addgeometry.xpm"
#include "xpm/ribbon/map/editor/delgeometry.xpm"
#include "xpm/ribbon/map/editor/movegeometry.xpm"
#include "xpm/ribbon/map/editor/overhead.xpm"
#include "xpm/ribbon/map/editor/shorthead.xpm"
#include "xpm/ribbon/map/editor/pan.xpm"
#include "xpm/ribbon/map/editor/newversion.xpm"
#include "xpm/ribbon/map/editor/copygeometry.xpm"
#include "xpm/ribbon/map/editor/multisel.xpm"
#include "xpm/ribbon/map/editor/spline.xpm"
#include "xpm/ribbon/map/editor/thin.xpm"
#include "xpm/ribbon/map/editor/split.xpm"
#include "xpm/ribbon/map/editor/refresh.xpm"
#include "xpm/ribbon/map/pickbypoint.xpm"
#include "xpm/ribbon/map/pickbyline.xpm"
#include "xpm/ribbon/map/pickbyrectangle.xpm"
#include "xpm/ribbon/map/pickbycircle.xpm"
#include "xpm/ribbon/map/pickbypolygon.xpm"
#include "xpm/ribbon/map/Line.xpm"
#include "xpm/ribbon/map/newline.xpm"
#include "xpm/ribbon/map/poly.xpm"

#include "xpm/ribbon/raster/importpic.xpm"
#include "xpm/ribbon/raster/georeference.xpm"
#include "xpm/ribbon/raster/imgmarch.xpm"
#include "xpm/ribbon/raster/scanline.xpm"
#include "xpm/ribbon/raster/rastr2vector.xpm"

#include "xpm/ribbon/well/importwell.xpm"
#include "xpm/ribbon/well/wellfeature.xpm"
#include "xpm/ribbon/well/connectseismic.xpm"
#include "xpm/ribbon/well/rockphysic.xpm"
#include "xpm/ribbon/well/wellseismicmark.xpm"
#include "xpm/ribbon/well/logestic.xpm"

#include "xpm/ribbon/seismic/import3dsesmic.xpm"
#include "xpm/ribbon/seismic/seismicfeature.xpm"
#include "xpm/ribbon/seismic/seismicconnectwell.xpm"
#include "xpm/ribbon/seismic/addseismicdatamod.xpm"
#include "xpm/ribbon/seismic/seismicstructure.xpm"
#include "xpm/ribbon/seismic/seiismicsection.xpm"
#include "xpm/ribbon/seismic/seismicdatamod.xpm"
#include "xpm/ribbon/seismic/seismiccubemod.xpm"
#include "xpm/ribbon/seismic/gdeoutput.xpm"

#include "xpm/ribbon/contour/importcontour.xpm"
#include "xpm/ribbon/contour/contourfeature.xpm"
#include "xpm/ribbon/contour/contouredit.xpm"
#include "xpm/ribbon/contour/contourenvidence.xpm"
#include "xpm/ribbon/contour/trendsurfaceanaly.xpm"
#include "xpm/ribbon/contour/fracture.xpm"
#include "xpm/ribbon/contour/varianceanaly.xpm"

#include "xpm/ribbon/contour/contourparaanaly.xpm"
#include "xpm/ribbon/contour/landformanaly.xpm"
#include "xpm/ribbon/contour/contour2line.xpm"
#include "xpm/ribbon/contour/contourgridout.xpm"
#include "xpm/ribbon/contour/contouroutput.xpm"

#include "xpm/ribbon/analysis/mapalgebra.xpm"
#include "xpm/ribbon/analysis/layeroverlap.xpm"
#include "xpm/ribbon/analysis/probabilitypanel.xpm"
#include "xpm/ribbon/analysis/decisiontree.xpm"
#include "xpm/ribbon/analysis/probablitytree.xpm"
#include "xpm/ribbon/analysis/bayesnetwork.xpm"
#include "xpm/ribbon/analysis/crossplot.xpm"
#include "xpm/ribbon/analysis/parallelcoor.xpm"
#include "xpm/ribbon/analysis/ternarygraph.xpm"
#include "xpm/ribbon/analysis/radarmap.xpm"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
giDataRibbonBuilder::giDataRibbonBuilder() : m_ribbon(0), m_ribbon_event_id(0), m_dropdown_menu(0)
{
}

giDataRibbonBuilder::~giDataRibbonBuilder()
{
	if (m_dropdown_menu)
	{
		delete m_dropdown_menu;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void giDataRibbonBuilder::SetProperty(wxRibbonBar *ribbon_bar) 
{
	m_ribbon = ribbon_bar;
	m_ribbon->SetTabCtrlMargins(0,0);
	m_ribbon->SetMaxSize(wxSize(-1, 60));
}

void giDataRibbonBuilder::CreateBasicPage() 
{
	//{
	//	wxgiRibbonCommandPage* home = new wxgiRibbonCommandPage(m_ribbon, wxID_ANY, wxT("Examples"), ribbon_xpm);
	//	wxgiRibbonCommandPanel *toolbar_panel = new wxgiRibbonCommandPanel(home, wxID_ANY, wxT("Toolbar"),
	//		wxNullBitmap, wxDefaultPosition, wxDefaultSize,
	//		wxRIBBON_PANEL_NO_AUTO_MINIMISE |
	//		wxRIBBON_PANEL_EXT_BUTTON);
	//	wxRibbonToolBar *toolbar = new wxRibbonToolBar(toolbar_panel, ID_MAIN_TOOLBAR);
	//	toolbar->AddToggleTool(wxID_JUSTIFY_LEFT, align_left_xpm);
	//	toolbar->AddToggleTool(wxID_JUSTIFY_CENTER, align_center_xpm);
	//	toolbar->AddToggleTool(wxID_JUSTIFY_RIGHT, align_right_xpm);
	//	toolbar->AddSeparator();
	//	toolbar->AddHybridTool(wxID_NEW, wxArtProvider::GetBitmap(wxART_NEW, wxART_OTHER, wxSize(16, 15)));
	//	toolbar->AddTool(wxID_OPEN, wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_OTHER, wxSize(16, 15)), "Open something");
	//	toolbar->AddTool(wxID_SAVE, wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_OTHER, wxSize(16, 15)), "Save something");
	//	toolbar->AddTool(wxID_SAVEAS, wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS, wxART_OTHER, wxSize(16, 15)), "Save something as ...");
	//	toolbar->EnableTool(wxID_OPEN, false);
	//	toolbar->EnableTool(wxID_SAVE, false);
	//	toolbar->EnableTool(wxID_SAVEAS, false);
	//	toolbar->AddSeparator();
	//	toolbar->AddDropdownTool(wxID_UNDO, wxArtProvider::GetBitmap(wxART_UNDO, wxART_OTHER, wxSize(16, 15)));
	//	toolbar->AddDropdownTool(wxID_REDO, wxArtProvider::GetBitmap(wxART_REDO, wxART_OTHER, wxSize(16, 15)));
	//	toolbar->AddSeparator();
	//	toolbar->AddTool(wxID_ANY, wxArtProvider::GetBitmap(wxART_REPORT_VIEW, wxART_OTHER, wxSize(16, 15)));
	//	toolbar->AddTool(wxID_ANY, wxArtProvider::GetBitmap(wxART_LIST_VIEW, wxART_OTHER, wxSize(16, 15)));
	//	toolbar->AddSeparator();
	//	toolbar->AddHybridTool(ID_POSITION_LEFT, position_left_xpm,
	//		"Align ribbonbar vertically\non the left\nfor demonstration purposes");
	//	toolbar->AddHybridTool(ID_POSITION_TOP, position_top_xpm,
	//		"Align the ribbonbar horizontally\nat the top\nfor demonstration purposes");
	//	toolbar->AddSeparator();
	//	toolbar->AddHybridTool(wxID_PRINT, wxArtProvider::GetBitmap(wxART_PRINT, wxART_OTHER, wxSize(16, 15)),
	//		"This is the Print button tooltip\ndemonstrating a tooltip");
	//	toolbar->SetRows(2, 3);

	//	wxgiRibbonCommandPanel *selection_panel = new wxgiRibbonCommandPanel(home, wxID_ANY, wxT("Selection"), wxBitmap(selection_panel_xpm));
	//	wxRibbonButtonBar *selection = new wxRibbonButtonBar(selection_panel);
	//	selection->AddButton(ID_SELECTION_EXPAND_V, wxT("Expand Vertically"), wxBitmap(expand_selection_v_xpm),
	//		"This is a tooltip for Expand Vertically\ndemonstrating a tooltip");
	//	selection->AddButton(ID_SELECTION_EXPAND_H, wxT("Expand Horizontally"), wxBitmap(expand_selection_h_xpm), wxEmptyString);
	//	selection->AddButton(ID_SELECTION_CONTRACT, wxT("Contract"), wxBitmap(auto_crop_selection_xpm), wxBitmap(auto_crop_selection_small_xpm));

	//	wxgiRibbonCommandPanel *shapes_panel = new wxgiRibbonCommandPanel(home, wxID_ANY, wxT("Shapes"), wxBitmap(circle_small_xpm));
	//	wxRibbonButtonBar *shapes = new wxRibbonButtonBar(shapes_panel);
	//	shapes->AddButton(ID_CIRCLE, wxT("Circle"), wxBitmap(circle_xpm), wxBitmap(circle_small_xpm),
	//		wxNullBitmap, wxNullBitmap, wxRIBBON_BUTTON_NORMAL,
	//		"This is a tooltip for the circle button\ndemonstrating another tooltip");
	//	shapes->AddButton(ID_CROSS, wxT("Cross"), wxBitmap(cross_xpm), wxEmptyString);
	//	shapes->AddHybridButton(ID_TRIANGLE, wxT("Triangle"), wxBitmap(triangle_xpm));
	//	shapes->AddButton(ID_SQUARE, wxT("Square"), wxBitmap(square_xpm), wxEmptyString);
	//	shapes->AddDropdownButton(ID_POLYGON, wxT("Other Polygon"), wxBitmap(hexagon_xpm), wxEmptyString);

	//	wxgiRibbonCommandPanel *sizer_panel = new wxgiRibbonCommandPanel(home, wxID_ANY, wxT("Panel with Sizer"),
	//		wxNullBitmap, wxDefaultPosition, wxDefaultSize,
	//		wxRIBBON_PANEL_DEFAULT_STYLE);

	//	wxArrayString as;
	//	as.Add("Item 1 using a box sizer now");
	//	as.Add("Item 2 using a box sizer now");
	//	wxComboBox* sizer_panelcombo = new wxComboBox(sizer_panel, wxID_ANY,
	//		wxEmptyString,
	//		wxDefaultPosition, wxDefaultSize,
	//		as, wxCB_READONLY);

	//	wxComboBox* sizer_panelcombo2 = new wxComboBox(sizer_panel, wxID_ANY,
	//		wxEmptyString,
	//		wxDefaultPosition, wxDefaultSize,
	//		as, wxCB_READONLY);

	//	sizer_panelcombo->Select(0);
	//	sizer_panelcombo2->Select(1);
	//	sizer_panelcombo->SetMinSize(wxSize(150, -1));
	//	sizer_panelcombo2->SetMinSize(wxSize(150, -1));

	//	//not using wxWrapSizer(wxHORIZONTAL) as it reports an incorrect min height
	//	wxSizer* sizer_panelsizer = new wxBoxSizer(wxVERTICAL);
	//	sizer_panelsizer->AddStretchSpacer(1);
	//	sizer_panelsizer->Add(sizer_panelcombo, 0, wxALL | wxEXPAND, 2);
	//	sizer_panelsizer->Add(sizer_panelcombo2, 0, wxALL | wxEXPAND, 2);
	//	sizer_panelsizer->AddStretchSpacer(1);
	//	sizer_panel->SetSizer(sizer_panelsizer);

	//	wxFont label_font(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT);
	//	m_bitmap_creation_dc.SetFont(label_font);

	//	wxgiRibbonCommandPage* scheme = new wxgiRibbonCommandPage(m_ribbon, wxID_ANY, wxT("Appearance"), eye_xpm);
	//	m_ribbon->GetArtProvider()->GetColourScheme(&m_default_primary,
	//		&m_default_secondary, &m_default_tertiary);
	//	wxgiRibbonCommandPanel *provider_panel = new wxgiRibbonCommandPanel(scheme, wxID_ANY,
	//		wxT("Art"), wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_NO_AUTO_MINIMISE);
	//	wxRibbonButtonBar *provider_bar = new wxRibbonButtonBar(provider_panel, wxID_ANY);
	//	provider_bar->AddButton(ID_DEFAULT_PROVIDER, wxT("Default Provider"),
	//		wxArtProvider::GetBitmap(wxART_QUESTION, wxART_OTHER, wxSize(32, 32)));
	//	provider_bar->AddButton(ID_AUI_PROVIDER, wxT("AUI Provider"), aui_style_xpm);
	//	provider_bar->AddButton(ID_MSW_PROVIDER, wxT("MSW Provider"), msw_style_xpm);
	//	wxgiRibbonCommandPanel *primary_panel = new wxgiRibbonCommandPanel(scheme, wxID_ANY,
	//		wxT("Primary Colour"), colours_xpm);
	//	m_primary_gallery = PopulateColoursPanel(primary_panel,
	//		m_default_primary, ID_PRIMARY_COLOUR);
	//	wxgiRibbonCommandPanel *secondary_panel = new wxgiRibbonCommandPanel(scheme, wxID_ANY,
	//		wxT("Secondary Colour"), colours_xpm);
	//	m_secondary_gallery = PopulateColoursPanel(secondary_panel,
	//		m_default_secondary, ID_SECONDARY_COLOUR);
	//}
	//{
	//	wxgiRibbonCommandPage* page = new wxgiRibbonCommandPage(m_ribbon, wxID_ANY, wxT("UI Updated"), ribbon_xpm);
	//	wxgiRibbonCommandPanel *panel = new wxgiRibbonCommandPanel(page, wxID_ANY, wxT("Enable/Disable"), ribbon_xpm);
	//	wxRibbonButtonBar *bar = new wxRibbonButtonBar(panel, wxID_ANY);
	//	bar->AddButton(ID_DISABLED, wxT("Disabled"), ribbon_xpm);
	//	bar->AddButton(ID_ENABLE, wxT("Enable"), ribbon_xpm);
	//	bar->AddButton(ID_DISABLE, wxT("Disable"), ribbon_xpm);
	//	bar->AddButton(ID_UI_ENABLE_UPDATED, wxT("Enable UI updated"), ribbon_xpm);
	//	bar->EnableButton(ID_DISABLED, false);
	//	m_bEnabled = true;

	//	panel = new wxgiRibbonCommandPanel(page, wxID_ANY, wxT("Toggle"), ribbon_xpm);
	//	bar = new wxRibbonButtonBar(panel, wxID_ANY);
	//	bar->AddButton(ID_CHECK, wxT("Toggle"), ribbon_xpm);
	//	bar->AddToggleButton(ID_UI_CHECK_UPDATED, wxT("Toggled UI updated"), ribbon_xpm);
	//	m_bChecked = true;

	//	panel = new wxgiRibbonCommandPanel(page, wxID_ANY, wxT("Change text"), ribbon_xpm);
	//	bar = new wxRibbonButtonBar(panel, wxID_ANY);
	//	bar->AddButton(ID_CHANGE_TEXT1, wxT("One"), ribbon_xpm);
	//	bar->AddButton(ID_CHANGE_TEXT2, wxT("Two"), ribbon_xpm);
	//	bar->AddButton(ID_UI_CHANGE_TEXT_UPDATED, wxT("Zero"), ribbon_xpm);

	//	//Also set the general disabled text colour:
	//	wxRibbonArtProvider* artProvider = m_ribbon->GetArtProvider();
	//	wxColour tColour = artProvider->GetColor(wxRIBBON_ART_BUTTON_BAR_LABEL_COLOUR);
	//	artProvider->SetColor(wxRIBBON_ART_BUTTON_BAR_LABEL_DISABLED_COLOUR, tColour.MakeDisabled());
	//}
	//new wxgiRibbonCommandPage(m_ribbon, wxID_ANY, wxT("Empty Page"), empty_xpm);
	//{
	//	wxgiRibbonCommandPage* page = new wxgiRibbonCommandPage(m_ribbon, wxID_ANY, wxT("Another Page"), empty_xpm);
	//	wxgiRibbonCommandPanel *panel = new wxgiRibbonCommandPanel(page, wxID_ANY, wxT("Page manipulation"), ribbon_xpm);
	//	wxRibbonButtonBar *bar = new wxRibbonButtonBar(panel, wxID_ANY);
	//	bar->AddButton(ID_REMOVE_PAGE, wxT("Remove"), wxArtProvider::GetBitmap(wxART_DELETE, wxART_OTHER, wxSize(24, 24)));
	//	bar->AddButton(ID_HIDE_PAGES, wxT("Hide Pages"), ribbon_xpm);
	//	bar->AddButton(ID_SHOW_PAGES, wxT("Show Pages"), ribbon_xpm);
	//}

	//new wxgiRibbonCommandPage(m_ribbon, wxID_ANY, wxT("Highlight Page"), empty_xpm);
	//m_ribbon->AddPageHighlight(m_ribbon->GetPageCount() - 1);

	giRibbonCommandPage basic_page;
	basic_page.m_id = m_ribbon_event_id++; 
	basic_page.m_name = "File";
	
	// database Panel
	{
		giRibbonCommandPanel panel;
		panel.m_id = m_ribbon_event_id++;
		panel.m_name = "Database"; 
		panel.m_type = LAYOUT_AS_BTNBAR;
		panel.m_toolbar_id = m_ribbon_event_id++;

		// database commands
		{
			giRibbonCommand btn;
			//btn.m_id = m_ribbon_event_id++; btn.m_name = "Connect";        btn.m_type = RCT_BTN; btn.m_xpm = open_32_xpm;   panel.m_commands.push_back(btn);			
			btn.m_id = m_ribbon_event_id++;	
			btn.m_name = "Connect"; 
			btn.m_type = RCT_BTN_DROPDOWN;	
			btn.m_xpm = linkdb_xpm;
			panel.m_commands.push_back(btn);
			m_ribbon_event_id += RIBBON_DROPDOWN_MAXIMUM; // maximum dropdown items

			btn.m_id = m_ribbon_event_id++; 
			btn.m_name = "New";	      
			btn.m_type = RCT_BTN; btn.m_xpm = newdb_xpm;   
			panel.m_commands.push_back(btn);
					
			btn.m_id = m_ribbon_event_id++; 
			btn.m_name = "Update";         
			btn.m_type = RCT_BTN; btn.m_xpm = updatedb_xpm;   
			panel.m_commands.push_back(btn);

			btn.m_id = m_ribbon_event_id++; 
			btn.m_name = "Merge";          
			btn.m_type = RCT_BTN; 
			btn.m_xpm = mergedb_xpm;    
			panel.m_commands.push_back(btn);
			
			//btn.m_id = m_ribbon_event_id++; 
			//btn.m_name = "Authorization";  
			//btn.m_type = RCT_BTN; 
			//btn.m_xpm = authorization_xpm;  
			//panel.m_commands.push_back(btn);
		}
		basic_page.m_panels.push_back(panel);
	}

	// view Panel
	{
		giRibbonCommandPanel panel;
		panel.m_id = m_ribbon_event_id++;	
		panel.m_name = "View"; 
		panel.m_type = LAYOUT_AS_BOXSIZER; 
		panel.m_id = m_ribbon_event_id++; 
		panel.m_cols = 2; 
		panel.m_rows = 2; 
		panel.m_pos = 1;

		// commands
		{
			giRibbonCommand ctrl;
			ctrl.m_id = m_ribbon_event_id++; ctrl.m_name = "GIS Solution"; ctrl.m_type = RCT_CHECKBOX; ctrl.m_col = 0; ctrl.m_row = 0; ctrl.m_is_checked = true;  panel.m_commands.push_back(ctrl);
			ctrl.m_id = m_ribbon_event_id++; ctrl.m_name = "DB Solution"; ctrl.m_type = RCT_CHECKBOX; ctrl.m_col = 0; ctrl.m_row = 1; ctrl.m_is_checked = false; panel.m_commands.push_back(ctrl);
			ctrl.m_id = m_ribbon_event_id++; ctrl.m_name = "Work Space"; ctrl.m_type = RCT_CHECKBOX; ctrl.m_col = 0; ctrl.m_row = 1; ctrl.m_is_checked = true; panel.m_commands.push_back(ctrl);

			giRibbonCommand btn;
			btn.m_id = m_ribbon_event_id++; btn.m_name = "Default"; btn.m_type = RCT_BTN; btn.m_xpm = defaultview_xpm; btn.m_col = 1; btn.m_row = 0;	panel.m_commands.push_back(btn);
		}
		basic_page.m_panels.push_back(panel);
	}

	// window panel
	{
		giRibbonCommandPanel panel;
		panel.m_id = m_ribbon_event_id++;
		panel.m_name = "Window";
		panel.m_type = LAYOUT_AS_BTNBAR;
		panel.m_id = m_ribbon_event_id++;
		{
			giRibbonCommand btn;
			btn.m_id = m_ribbon_event_id++; btn.m_name = "Windows"; btn.m_type = RCT_BTN_DROPDOWN; btn.m_xpm = windowsfloat_xpm; panel.m_commands.push_back(btn);
			btn.m_id = m_ribbon_event_id++; btn.m_name = "Float"; btn.m_type = RCT_BTN; btn.m_xpm = windowsfloat_xpm; panel.m_commands.push_back(btn);
			btn.m_id = m_ribbon_event_id++; btn.m_name = "Dock";  btn.m_type = RCT_BTN; btn.m_xpm = windowsdock_xpm;  panel.m_commands.push_back(btn);
		
			btn.m_id = m_ribbon_event_id++;	btn.m_name = "Close"; btn.m_type = RCT_BTN_DROPDOWN;	btn.m_xpm = windowsclose_xpm;
			btn.m_dropdown_ids.push_back(m_ribbon_event_id++);     
			btn.m_dropdown_contents.push_back("Current");
			
			btn.m_dropdown_ids.push_back(m_ribbon_event_id++);     
			btn.m_dropdown_contents.push_back("Others");
			
			btn.m_dropdown_ids.push_back(m_ribbon_event_id++);     
			btn.m_dropdown_contents.push_back("All");
			panel.m_commands.push_back(btn);
		}
		basic_page.m_panels.push_back(panel);
	}

	// option panel
	{
		giRibbonCommandPanel panel;
		panel.m_id = m_ribbon_event_id++;
		panel.m_name = "Tools";
		panel.m_type = LAYOUT_AS_BTNBAR;
		panel.m_id = m_ribbon_event_id++;
		{
			giRibbonCommand btn;
			btn.m_id = m_ribbon_event_id++; btn.m_name = "Setting"; btn.m_type = RCT_BTN; btn.m_xpm = option_xpm; panel.m_commands.push_back(btn);
		}
		basic_page.m_panels.push_back(panel);
	}

	// help panel
	//{
	//	giRibbonCommandPanel panel;
	//	panel.m_id = m_ribbon_event_id++;
	//	panel.m_name = "Help";
	//	panel.m_type = LAYOUT_AS_BTNBAR;
	//	panel.m_id = m_ribbon_event_id++;
	//	{
	//		giRibbonCommand btn;
	//		btn.m_id = m_ribbon_event_id++; btn.m_name = "Manual"; btn.m_type = RCT_BTN; btn.m_xpm = usermanual_xpm;	panel.m_commands.push_back(btn);
	//		btn.m_id = m_ribbon_event_id++; btn.m_name = "About";  btn.m_type = RCT_BTN; btn.m_xpm = about_xpm;	panel.m_commands.push_back(btn);
	//	}
	//	basic_page.m_panels.push_back(panel);
	//}

	m_pages.push_back(basic_page);
}

void giDataRibbonBuilder::CreateMapPage() 
{
	
	giRibbonCommandPage map_page;
	map_page.m_id = m_ribbon_event_id++; 
	map_page.m_name = "Map";

	// map data panel
	{
		giRibbonCommandPanel panel;
		panel.m_id = m_ribbon_event_id++;
		panel.m_name = "Import"; 
		panel.m_type = LAYOUT_AS_BTNBAR; 
		panel.m_toolbar_id = m_ribbon_event_id++;
		{
			giRibbonCommand btn;
			btn.m_id = m_ribbon_event_id++;	btn.m_name = "Vector";   btn.m_type = RCT_BTN; btn.m_xpm = importgis_xpm;     panel.m_commands.push_back(btn);
			btn.m_id = m_ribbon_event_id++;	btn.m_name = "Raster";   btn.m_type = RCT_BTN; btn.m_xpm = importpic_xpm;     panel.m_commands.push_back(btn); 
			btn.m_id=  m_ribbon_event_id++;	btn.m_name ="Field";      btn.m_type=RCT_BTN;   btn.m_xpm=importcontour_xpm;   panel.m_commands.push_back(btn);
			btn.m_id=  m_ribbon_event_id++;	btn.m_name ="Well";       btn.m_type=RCT_BTN;   btn.m_xpm=importwell_xpm;      panel.m_commands.push_back(btn);
			btn.m_id=  m_ribbon_event_id++;	btn.m_name ="2D Seismic"; btn.m_type=RCT_BTN;   btn.m_xpm= import3dsesmic_xpm; panel.m_commands.push_back(btn);
			btn.m_id=  m_ribbon_event_id++;	btn.m_name ="3D Seismic"; btn.m_type=RCT_BTN;   btn.m_xpm=import3dsesmic_xpm;  panel.m_commands.push_back(btn);

		}
		map_page.m_panels.push_back(panel);
	}

	// map operation panel
	{
		giRibbonCommandPanel panel;
		panel.m_id = m_ribbon_event_id++;
		panel.m_name = "Map Operation";
		panel.m_type = LAYOUT_AS_BOXSIZER;
		panel.m_toolbar_id = m_ribbon_event_id++;
		panel.m_rows = 2;
		panel.m_cols = 9;
		panel.m_is_extendable_btn = false;
		{
			giRibbonCommand tool;
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Zoom In";   tool.m_type = RCT_BTN; tool.m_xpm = zoomin_xpm;    tool.m_col = 0; tool.m_row = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Zoom Out";  tool.m_type = RCT_BTN; tool.m_xpm = zoomout_xpm;   tool.m_col = 1; tool.m_row = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Zoom Rect"; tool.m_type = RCT_BTN; tool.m_xpm = zoomfree_xpm;  tool.m_col = 2; tool.m_row = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Pan";   tool.m_type = RCT_BTN; tool.m_xpm = panview_xpm;   tool.m_col = 3; tool.m_row = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Full";  tool.m_type = RCT_BTN; tool.m_xpm = fullview_xpm;  tool.m_col = 4; tool.m_row = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Previous"; tool.m_type = RCT_BTN; tool.m_xpm = backview_xpm;  tool.m_col = 5; tool.m_row = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Next"; tool.m_type = RCT_BTN; tool.m_xpm = frontview_xpm; tool.m_col = 6; tool.m_row = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Position";  tool.m_type = RCT_BTN; tool.m_xpm = pointview_xpm; tool.m_col = 7; tool.m_row = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Map Scale"; tool.m_type = RCT_COMBOX; tool.m_col = 8; tool.m_row = 1;	tool.m_width = 130;
			tool.m_dropdown_contents.push_back("1:1000");   tool.m_dropdown_contents.push_back("1:10000");   tool.m_dropdown_contents.push_back("1:24000");
			tool.m_dropdown_contents.push_back("1:100000"); tool.m_dropdown_contents.push_back("1:250000");  tool.m_dropdown_contents.push_back("1:500000");
			tool.m_dropdown_contents.push_back("1:750000"); tool.m_dropdown_contents.push_back("1:1000000"); tool.m_dropdown_contents.push_back("1:10000000");
			tool.m_dropdown_contents.push_back("<custom...>");
			panel.m_commands.push_back(tool); tool.m_dropdown_contents.clear();
		}
		map_page.m_panels.push_back(panel);
	}

	// map edit Panel
	{
		giRibbonCommandPanel panel;
		panel.m_id = m_ribbon_event_id++;
		panel.m_name = "Map Edit";
		panel.m_type = LAYOUT_AS_BOXSIZER;
		panel.m_toolbar_id = m_ribbon_event_id++;
		panel.m_rows = 2; 
		panel.m_cols = 1;
		panel.m_is_extendable_btn = true;
		{
			giRibbonCommand tool;
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "SDE Layers";	tool.m_type = RCT_COMBOX; tool.m_col = 0; tool.m_row = 0; tool.m_width = 200;
			tool.m_dropdown_contents.push_back("Layer1");
			tool.m_dropdown_contents.push_back("Layer2");
			tool.m_dropdown_contents.push_back("Layer3");
			panel.m_commands.push_back(tool); 
			tool.m_dropdown_contents.clear();

			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Start";  tool.m_type = RCT_TOOL; tool.m_xpm = startedit_xpm;	 tool.m_col = 0; tool.m_row = 0;                       panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "End";    tool.m_type = RCT_TOOL; tool.m_xpm=stopedit_xpm ;    tool.m_col = 0; tool.m_row=0;   tool.m_is_enable=0;   panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Commit"; tool.m_type = RCT_TOOL; tool.m_xpm = saveedit_xpm;	 tool.m_col = 0; tool.m_row = 0; tool.m_is_enable = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	                        tool.m_type = RCT_TOOL_SEPERATOR;                    tool.m_col = 0; tool.m_row = 0;                       panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	                        tool.m_type = RCT_TOOL_SEPERATOR;                    tool.m_col = 0; tool.m_row = 0;                       panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	                        tool.m_type = RCT_TOOL_SEPERATOR;                    tool.m_col = 0; tool.m_row = 0;                       panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	                        tool.m_type = RCT_TOOL_SEPERATOR;                    tool.m_col = 0; tool.m_row = 0;                       panel.m_commands.push_back(tool);

			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Undo";        tool.m_type = RCT_TOOL;		tool.m_xpm = undo_xpm;	 tool.m_col = 0; tool.m_row = 0; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Redo";        tool.m_type = RCT_TOOL;		tool.m_xpm = redo_xpm;	 tool.m_col = 0; tool.m_row = 0; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;                              tool.m_type = RCT_TOOL_SEPERATOR;	tool.m_col = 0; tool.m_row = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;                              tool.m_type = RCT_TOOL_SEPERATOR;	tool.m_col = 0; tool.m_row = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;                              tool.m_type = RCT_TOOL_SEPERATOR;	tool.m_col = 0; tool.m_row = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "New Version"; tool.m_type = RCT_TOOL;		tool.m_xpm = newversion_xpm;	 tool.m_col = 0; tool.m_row = 0; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Sync";		 tool.m_type = RCT_TOOL;		tool.m_xpm = refresh_xpm;	 tool.m_col = 0; tool.m_row = 0; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Setting";     tool.m_type = RCT_TOOL;		tool.m_xpm = Setting_xpm;	 tool.m_col = 0; tool.m_row = 0; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);

			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Copy Geometry";		tool.m_type = RCT_TOOL;			tool.m_xpm = pan_xpm;	 tool.m_col = 0; tool.m_row = 1;	tool.m_is_enable = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Pick Geometry";		tool.m_type = RCT_TOOL;		tool.m_xpm = multisel_xpm; tool.m_col = 0; tool.m_row = 1;	tool.m_is_enable = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Move Geometry";		tool.m_type = RCT_TOOL;		tool.m_xpm = move_xpm;	 tool.m_col = 0; tool.m_row = 1;	tool.m_is_enable = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Add Geometry";		tool.m_type = RCT_TOOL;		tool.m_xpm = create_xpm;	 tool.m_col = 0; tool.m_row = 1;	tool.m_is_enable = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Delete Geomerty";		tool.m_type = RCT_TOOL;		tool.m_xpm = editordelete_xpm;	 tool.m_col = 0; tool.m_row = 1;	tool.m_is_enable = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_type = RCT_TOOL_SEPERATOR;	tool.m_col = 0; tool.m_row = 1;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Query";			tool.m_type = RCT_TOOL;		tool.m_xpm = attribute_xpm;	 tool.m_col = 0; tool.m_row = 1;	tool.m_is_enable = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_type = RCT_TOOL_SEPERATOR;	tool.m_col = 0; tool.m_row = 1;	panel.m_commands.push_back(tool);
		
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Start Vertex";		tool.m_type = RCT_TOOL;		tool.m_xpm = reshape_xpm;	 tool.m_col = 0; tool.m_row = 1; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Add Vertex";		tool.m_type = RCT_TOOL;		tool.m_xpm = addgeometry_xpm; tool.m_col = 0; tool.m_row = 1; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Delete Vertex";		tool.m_type = RCT_TOOL;		tool.m_xpm = delgeometry_xpm; tool.m_col = 0; tool.m_row = 1; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Shift Vertex";		tool.m_type = RCT_TOOL;		tool.m_xpm = movegeometry_xpm; tool.m_col = 0; tool.m_row = 1; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "To Right";	tool.m_type = RCT_TOOL;		tool.m_xpm = overhead_xpm;	 tool.m_col = 0; tool.m_row = 1; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "To Left";	tool.m_type = RCT_TOOL;		tool.m_xpm = shorthead_xpm;	 tool.m_col = 0; tool.m_row = 1; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Spline";		tool.m_type = RCT_TOOL;		tool.m_xpm = spline_xpm;		 tool.m_col = 0; tool.m_row = 1; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "End Vertex";		tool.m_type = RCT_TOOL;		tool.m_xpm = reshape_xpm;	 tool.m_col = 0; tool.m_row = 1; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_type = RCT_TOOL_SEPERATOR;	tool.m_col = 0; tool.m_row = 1;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Over";		tool.m_type = RCT_TOOL;		tool.m_xpm = overhead_xpm;	 tool.m_col = 0; tool.m_row = 1; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Under";		tool.m_type = RCT_TOOL;		tool.m_xpm = shorthead_xpm;	 tool.m_col = 0; tool.m_row = 1; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Split";		tool.m_type = RCT_TOOL;		tool.m_xpm = split_xpm;		 tool.m_col = 0; tool.m_row = 1; tool.m_is_enable = 0;	panel.m_commands.push_back(tool);
		}
		map_page.m_panels.push_back(panel);
	}

	// map analysis panel
	{
		giRibbonCommandPanel panel;
		panel.m_id = m_ribbon_event_id++;
		panel.m_name = "Map Analysis";
		panel.m_type = LAYOUT_AS_BOXSIZER;
		panel.m_toolbar_id = m_ribbon_event_id++;
		panel.m_rows = 2;
		panel.m_cols = 1;
		{
			giRibbonCommand tool;
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Pick by Point";	 tool.m_type = RCT_TOOL; tool.m_xpm = pickbypoint_xpm;	   tool.m_col = 0; tool.m_row = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Pick by Rect";	 tool.m_type = RCT_TOOL; tool.m_xpm = pickbyrectangle_xpm; tool.m_col = 0; tool.m_row = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Pick by Circle";	 tool.m_type = RCT_TOOL; tool.m_xpm = pickbycircle_xpm;	   tool.m_col = 0; tool.m_row = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Pick by Polygon"; tool.m_type = RCT_TOOL; tool.m_xpm = pickbypolygon_xpm;   tool.m_col = 0; tool.m_row = 0; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Pick by Line";	 tool.m_type = RCT_TOOL; tool.m_xpm = pickbyline_xpm;      tool.m_col = 0; tool.m_row = 0; panel.m_commands.push_back(tool);
																								 																   
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Length";		     tool.m_type = RCT_TOOL; tool.m_xpm = Line_xpm;            tool.m_col = 0; tool.m_row = 1; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Perimeter";		 tool.m_type = RCT_TOOL; tool.m_xpm = newline_xpm;         tool.m_col = 0; tool.m_row = 1; panel.m_commands.push_back(tool);
			tool.m_id = m_ribbon_event_id++;	tool.m_name = "Area";		     tool.m_type = RCT_TOOL; tool.m_xpm = poly_xpm;            tool.m_col = 0; tool.m_row = 1; panel.m_commands.push_back(tool);
		}
		map_page.m_panels.push_back(panel);
	}
	m_pages.push_back(map_page);
}

void giDataRibbonBuilder::Realize() 
{	
	// loop ribbon layour schema
	for(int i = 0; i < m_pages.size(); i++) 
	{	
		// each ribbon page
		wxRibbonPage *page = new wxRibbonPage(m_ribbon, m_pages[i].m_id, m_pages[i].m_name.c_str());
		for (int j = 0; j< m_pages[i].m_panels.size(); j++) 
		{
			// panel itself style
			giRibbonCommandPanel &panel_info = m_pages[i].m_panels[j];
			int panelflag = 0;
			if (panel_info.m_is_extendable_btn)
			{
				panelflag = wxRIBBON_PANEL_DEFAULT_STYLE | wxRIBBON_PANEL_EXT_BUTTON;
			}
			wxRibbonPanel *panel = new wxRibbonPanel(page, panel_info.m_id, panel_info.m_name.c_str(), wxNullBitmap, wxDefaultPosition, wxDefaultSize, panelflag);//, wxBitmap(ribbonpanel.m_panelxpm),wxDefaultPosition,wxDefaultSize,ribbonpanel.m_panelflag);
			panel->Connect(panel_info.m_id, wxEVT_RIBBONPANEL_EXTBUTTON_ACTIVATED, wxRibbonPanelEventHandler(giDataFrame::OnRibbonPanelExtended), new giRibbonCommandPanel(panel_info));
			RIBBON_REGISTER_EVENT_ENTRY(panel_info.m_id, wxEVT_RIBBONPANEL_EXTBUTTON_ACTIVATED, panel_info.m_name);

			if(panel_info.m_type == LAYOUT_AS_TOOLBAR) 
			{
				//commands in rows & cols
				DoLayoutToolBarPanel(panel, panel_info);
			}			
			else if (panel_info.m_type == LAYOUT_AS_BTNBAR) 
			{
				// commands in large icon
				DoLayoutBtnBarPanel(panel, panel_info);
			}
			else if (panel_info.m_type == LAYOUT_AS_BOXSIZER) 
			{
				// flexible layout
				DoLayoutBoxSizerPanel(panel, panel_info);
			}
		}
	}
	//
	m_ribbon->Realize();
}

//
void giDataRibbonBuilder::DoLayoutToolBarPanel(wxRibbonPanel *panel, const giRibbonCommandPanel &panel_info) 
{	
	wxRibbonToolBar *toolbar = new wxRibbonToolBar(panel, panel_info.m_toolbar_id);
	std::vector<int> groupids;
	for (int k = 0; k < panel_info.m_commands.size(); k++) 
	{
		bool is_exist = false;
		for (int m = 0; m<groupids.size(); m++) 
		{
			if (groupids[m] == panel_info.m_commands[k].m_group_id) 
			{
				is_exist = true;
				break;
			}
		}
		if (!is_exist) 
		{
			groupids.push_back(panel_info.m_commands[k].m_group_id);
		}
	}

	for (int m = 0; m < groupids.size(); m++) 
	{
		for (int k = 0; k<panel_info.m_commands.size(); k++) 
		{
			const giRibbonCommand &cmd_info = panel_info.m_commands[k];
			if (cmd_info.m_group_id == groupids[m]) 
			{
				if (cmd_info.m_type == RCT_TOOL) 
				{
					toolbar->AddTool(cmd_info.m_id, wxBitmap(cmd_info.m_xpm), cmd_info.m_name.c_str());
					toolbar->Connect(cmd_info.m_id, wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler(giDataFrame::OnRibbonBarClicked), new giRibbonCommand(cmd_info));
					RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_RIBBONTOOLBAR_CLICKED, cmd_info.m_name);

					if (cmd_info.m_is_enable == 0)toolbar->EnableTool(cmd_info.m_id, false);
				}
				else if (cmd_info.m_type == RCT_TOOL_CHECK) 
				{
					toolbar->AddToggleTool(cmd_info.m_id, wxBitmap(cmd_info.m_xpm));
					toolbar->Connect(cmd_info.m_id, wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler(giDataFrame::OnRibbonBarClicked), new giRibbonCommand(cmd_info));
					RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_RIBBONTOOLBAR_CLICKED, cmd_info.m_name);

					if (cmd_info.m_is_enable == 0)toolbar->EnableTool(cmd_info.m_id, false);
				}
				else if (cmd_info.m_type == RCT_TOOL_DROPDOWN) 
				{
					toolbar->AddDropdownTool(cmd_info.m_id, wxBitmap(cmd_info.m_xpm));
					toolbar->Connect(cmd_info.m_id, wxEVT_RIBBONTOOLBAR_DROPDOWN_CLICKED, wxRibbonToolBarEventHandler(giDataFrame::OnRibbonBarClicked), new giRibbonCommand(cmd_info));
					RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_RIBBONTOOLBAR_DROPDOWN_CLICKED, cmd_info.m_name);

					if (cmd_info.m_is_enable == 0)toolbar->EnableTool(cmd_info.m_id, false);
				}
			}
		}
		toolbar->AddSeparator();
	}
	toolbar->SetRows(panel_info.m_rows, panel_info.m_cols);
}

//
void giDataRibbonBuilder::DoLayoutBtnBarPanel(wxRibbonPanel *panel, const giRibbonCommandPanel &panel_info) 
{
	wxRibbonButtonBar *btnbar = new wxRibbonButtonBar(panel, panel_info.m_toolbar_id);
	for (int k = 0; k < panel_info.m_commands.size(); k++) 
	{
		const giRibbonCommand &cmd_info = panel_info.m_commands[k];
		if (cmd_info.m_type == RCT_BTN) 
		{
			btnbar->AddButton(cmd_info.m_id, cmd_info.m_name.c_str(), wxBitmap(cmd_info.m_xpm), cmd_info.m_name.c_str());
			btnbar->Connect(cmd_info.m_id, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(giDataFrame::OnRibbonBarClicked), new giRibbonCommand(cmd_info));
			RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_RIBBONBUTTONBAR_CLICKED, cmd_info.m_name);

			if (cmd_info.m_is_enable == 0) btnbar->EnableButton(cmd_info.m_id, false);
		}
		else if (cmd_info.m_type == RCT_BTN_DROPDOWN) 
		{
			btnbar->AddDropdownButton(cmd_info.m_id, cmd_info.m_name.c_str(), wxBitmap(cmd_info.m_xpm), cmd_info.m_name.c_str());
			btnbar->Connect(cmd_info.m_id, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(giDataFrame::OnRibbonBarClicked), new giRibbonCommand(cmd_info));
			RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, cmd_info.m_name);

			if (cmd_info.m_is_enable == 0) btnbar->EnableButton(cmd_info.m_id, false);
		}
	}
}

//
void giDataRibbonBuilder::DoLayoutBoxSizerPanel(wxRibbonPanel *panel, const giRibbonCommandPanel &panel_info) 
{
	// col-order
	std::vector<std::vector<giRibbonCommand>> RTS;
	for (int x = 0; x < panel_info.m_commands.size(); x++)
	{
		const giRibbonCommand &cmd_info = panel_info.m_commands[x];
		bool isexist = false;
		if (RTS.size() <= 0)
		{
			isexist = false;
			std::vector<giRibbonCommand> oneRT;
			oneRT.push_back(cmd_info);
			RTS.push_back(oneRT);
			continue;
		}
		for (int p = 0; p<RTS.size(); p++)
		{
			if (cmd_info.m_col == RTS[p][0].m_col)
			{
				RTS[p].push_back(cmd_info);
				isexist = true;
				break;
			}
		}
		if (isexist)
		{
			continue;
		}
		else
		{
			std::vector<giRibbonCommand> oneRT;
			oneRT.push_back(cmd_info);
			RTS.push_back(oneRT);
			continue;
		}
	}

	std::vector<std::vector<std::vector<giRibbonCommand>>> RTSS;
	for (int k = 0; k<RTS.size(); k++)
	{
		std::vector<std::vector<giRibbonCommand>> RTS1;
		for (int p = 0; p<RTS[k].size(); p++)
		{
			giRibbonCommand &cmd_info = RTS[k][p];
			bool isexist = false;
			if (RTS1.size() <= 0)
			{
				isexist = false;
				std::vector<giRibbonCommand> oneRT;
				oneRT.push_back(cmd_info);
				RTS1.push_back(oneRT);
				continue;
			}
			for (int q = 0; q<RTS1.size(); q++)
			{
				if (cmd_info.m_row == RTS1[q][0].m_row)
				{
					RTS1[q].push_back(cmd_info);
					isexist = true;
					break;
				}
			}
			if (isexist)
			{
				continue;
			}
			else
			{
				std::vector<giRibbonCommand> oneRT;
				oneRT.push_back(cmd_info);
				RTS1.push_back(oneRT);
				continue;
			}
		}
		if (RTS1.size())
		{
			RTSS.push_back(RTS1);
		}
	}

	// add sizer
	wxSizer *sizer_panelsizer_h = new wxBoxSizer(wxHORIZONTAL);
	for (int k = 0; k<RTSS.size(); k++)
	{
		int unbtntoolsnum = 0;
		wxSizer* sizer_panelsizer_v = new wxBoxSizer(wxVERTICAL);
		for (int p = 0; p<RTSS[k].size(); p++)
		{
			wxSizer* sizer_panelsizer_Pos_h = new wxBoxSizer(wxHORIZONTAL);
			for (int q = 0; q<RTSS[k][p].size(); q++)
			{
				giRibbonCommand &cmd_info = RTSS[k][p][q];
				if (cmd_info.m_type == RCT_BTN)
				{
					wxRibbonButtonBar *btnbar = new wxRibbonButtonBar(panel, cmd_info.m_id /*+ AllRibbontoolnum*/);
					btnbar->AddButton(cmd_info.m_id, cmd_info.m_name.c_str(), wxBitmap(cmd_info.m_xpm), cmd_info.m_name.c_str());
					//btnbar->SetButtonMinSizeClass(ID_BUTTON_XX, wxRIBBON_BUTTONBAR_BUTTON_LARGE);
					btnbar->Connect(cmd_info.m_id, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(giDataFrame::OnRibbonBarClicked), new giRibbonCommand(cmd_info));
					RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_RIBBONBUTTONBAR_CLICKED, cmd_info.m_name);

					sizer_panelsizer_h->Add(btnbar, 0, wxEXPAND);
					if (cmd_info.m_is_enable == 0) btnbar->EnableButton(cmd_info.m_id, false);
				}
				else if (cmd_info.m_type == RCT_BTN_DROPDOWN)
				{
					wxRibbonButtonBar *btnbar = new wxRibbonButtonBar(panel, cmd_info.m_id /*+ AllRibbontoolnum*/);
					btnbar->AddDropdownButton(cmd_info.m_id, cmd_info.m_name.c_str(), wxBitmap(cmd_info.m_xpm), cmd_info.m_name.c_str());
					//btnbar->SetButtonMinSizeClass(ID_BUTTON_XX, wxRIBBON_BUTTONBAR_BUTTON_LARGE);
					btnbar->Connect(cmd_info.m_id, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(giDataFrame::OnRibbonBarClicked), new giRibbonCommand(cmd_info));
					RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, cmd_info.m_name);

					sizer_panelsizer_h->Add(btnbar, 0, wxEXPAND);
					if (cmd_info.m_is_enable == 0) btnbar->EnableButton(cmd_info.m_id, false);
				}
				else if (cmd_info.m_type == RCT_BTN_SMALL)
				{
					wxRibbonButtonBar *btnbar = new wxRibbonButtonBar(panel, cmd_info.m_id /*+ AllRibbontoolnum*/);
					btnbar->AddButton(cmd_info.m_id, "", wxBitmap(cmd_info.m_xpm), cmd_info.m_name.c_str());
					//btnbar->SetButtonMinSizeClass(cmd_info.m_id, wxRIBBON_BUTTONBAR_BUTTON_MEDIUM);
					btnbar->Connect(cmd_info.m_id, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(giDataFrame::OnRibbonBarClicked), new giRibbonCommand(cmd_info));
					RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_RIBBONBUTTONBAR_CLICKED, cmd_info.m_name);

					sizer_panelsizer_Pos_h->Add(btnbar, 0, wxALL | wxEXPAND, 2);
					unbtntoolsnum++;
					if (cmd_info.m_is_enable == 0) btnbar->EnableButton(cmd_info.m_id, false);
				}
				else if (cmd_info.m_type == RCT_TOOL)
				{
					wxRibbonToolBar *toolbar = new wxRibbonToolBar(panel, cmd_info.m_id /*+ AllRibbontoolnum*/);
					toolbar->AddTool(cmd_info.m_id, wxBitmap(cmd_info.m_xpm), cmd_info.m_name.c_str());
					toolbar->Connect(cmd_info.m_id, wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler(giDataFrame::OnRibbonBarClicked), new giRibbonCommand(cmd_info));
					RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_RIBBONTOOLBAR_CLICKED, cmd_info.m_name);

					sizer_panelsizer_Pos_h->Add(toolbar, 0, wxALL | wxEXPAND, 0);
					unbtntoolsnum++;
					if (cmd_info.m_is_enable == 0)toolbar->EnableTool(cmd_info.m_id, false);
				}
				else if (cmd_info.m_type == RCT_TOOL_SEPERATOR)
				{
					wxRibbonToolBar *toolbar = new wxRibbonToolBar(panel, cmd_info.m_id /*+ AllRibbontoolnum*/);
					toolbar->AddSeparator();
					toolbar->AddSeparator();
					sizer_panelsizer_Pos_h->Add(toolbar, 0, wxALL | wxEXPAND, 2);
					unbtntoolsnum++;
				}
				else if (cmd_info.m_type == RCT_COMBOX)
				{
					wxArrayString as;
					for (int s = 0; s<cmd_info.m_dropdown_contents.size(); s++)
					{
						wxString str = cmd_info.m_dropdown_contents[s].c_str();
						as.Add(str);
					}
					wxComboBox* combox = new wxComboBox(panel, cmd_info.m_id, wxEmptyString, wxDefaultPosition, wxDefaultSize, as);
					combox->Select(0);
					combox->SetMinSize(wxSize(cmd_info.m_width, cmd_info.m_height));
					combox->Connect(cmd_info.m_id, wxEVT_COMBOBOX, wxCommandEventHandler(giDataFrame::OnRibbonControlClicked), new giRibbonCommand(cmd_info));
					RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_COMBOBOX, cmd_info.m_name);

					sizer_panelsizer_Pos_h->Add(combox, 0, wxALL | wxEXPAND, 2);
					unbtntoolsnum++;
					if (cmd_info.m_is_enable == 0)combox->Enable(false);
				}
				else if (cmd_info.m_type == RCT_CHECKBOX)
				{
					wxCheckBox *checkbox = new wxCheckBox(panel, cmd_info.m_id, cmd_info.m_name);
					checkbox->SetBackgroundColour(wxColour(199, 218, 239));
					checkbox->SetValue(cmd_info.m_is_checked);
					checkbox->Connect(cmd_info.m_id, wxEVT_CHECKBOX, wxCommandEventHandler(giDataFrame::OnRibbonControlClicked), new giRibbonCommand(cmd_info));
					RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_CHECKBOX, cmd_info.m_name);

					sizer_panelsizer_Pos_h->Add(checkbox, 0, wxALL | wxEXPAND, 2);
					unbtntoolsnum++;
					if (cmd_info.m_is_enable == 0)checkbox->Enable(false);
				}
				else if (cmd_info.m_type == RCT_TEXT_CTRL)
				{
					wxTextCtrl *textctrl = new wxTextCtrl(panel, cmd_info.m_id, _T(""), wxDefaultPosition, wxSize(cmd_info.m_width, cmd_info.m_height));
					textctrl->SetMinSize(wxSize(cmd_info.m_width, cmd_info.m_height));
					textctrl->SetValue(cmd_info.m_default_value);
					textctrl-> Connect(cmd_info.m_id, wxEVT_TEXT,wxCommandEventHandler(giDataFrame::OnRibbonControlClicked));
					RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_TEXT, cmd_info.m_name);

					sizer_panelsizer_Pos_h->Add(textctrl, 0, wxALL | wxEXPAND, 2);
					unbtntoolsnum++;
					if (cmd_info.m_is_enable == 0)textctrl->Enable(false);
				}
				else if (cmd_info.m_type == RCT_TEXT_LABEL)
				{
					wxStaticText *textlabel = new wxStaticText(panel, cmd_info.m_id, cmd_info.m_name);
					textlabel->SetBackgroundColour(wxColour(199, 218, 239));
					textlabel-> Connect(cmd_info.m_id,wxEVT_CHECKBOX, wxCommandEventHandler(giDataFrame::OnRibbonControlClicked), new giRibbonCommand(cmd_info));
					RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_CHECKBOX, cmd_info.m_name);

					sizer_panelsizer_Pos_h->Add(textlabel, 0, wxALIGN_BOTTOM, 2);
					unbtntoolsnum++;
					if (cmd_info.m_is_enable == 0)textlabel->Enable(false);
				}
				else if (cmd_info.m_type == RCT_SPINCTRL)
				{
					long min = 0, max = 1000000000, intal = 0;
					if (cmd_info.m_candidate_values.size()>3)
					{
						min = cmd_info.m_candidate_values[0];
						max = cmd_info.m_candidate_values[1];
						intal = cmd_info.m_candidate_values[2];
					}

					wxSpinCtrl* spinctrl = new wxSpinCtrl(panel, cmd_info.m_id, wxEmptyString, wxDefaultPosition, wxSize(cmd_info.m_width, cmd_info.m_height), wxSP_ARROW_KEYS | wxTE_CENTER, min, max, intal);
					spinctrl->SetBackgroundColour(wxColour(199, 218, 239));
					spinctrl->Connect(cmd_info.m_id, wxEVT_SPINCTRL, wxSpinEventHandler(giDataFrame::OnRibbonControlClicked), new giRibbonCommand(cmd_info));
					RIBBON_REGISTER_EVENT_ENTRY(cmd_info.m_id, wxEVT_SPINCTRL, cmd_info.m_name);

					sizer_panelsizer_Pos_h->Add((wxWindow*)spinctrl, 0, wxALL | wxEXPAND, 2);
					unbtntoolsnum++;
					if (cmd_info.m_is_enable == 0)spinctrl->Enable(false);
				}
			}
			sizer_panelsizer_v->Add(sizer_panelsizer_Pos_h, 0, wxALL, 2);
		}
		if (unbtntoolsnum>0)
		{
			sizer_panelsizer_h->Add(sizer_panelsizer_v);
		}
		else
		{
			delete sizer_panelsizer_v;
		}
	}
	panel->SetSizer(sizer_panelsizer_h);
}

//
wxMenu *giDataRibbonBuilder::GetDropdownMenu(const giRibbonCommand &ribbon_cmd)
{
	if (m_dropdown_menu)
		delete m_dropdown_menu;
	
	m_dropdown_menu = new wxMenu;
	for (int i = 0; i < ribbon_cmd.m_dropdown_ids.size(); i++)
	{
		m_dropdown_menu->AppendCheckItem(ribbon_cmd.m_dropdown_ids[i], ribbon_cmd.m_dropdown_contents[i]);
		if (ribbon_cmd.m_dropdown_ids_checked.size())
		{
			m_dropdown_menu->Check(ribbon_cmd.m_dropdown_ids[i], ribbon_cmd.m_dropdown_ids_checked[i]);
		}
		m_dropdown_menu->Connect(ribbon_cmd.m_dropdown_ids[i], wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(giDataFrame::DoDispatchRibbonMenuClick), new giRibbonCommand(ribbon_cmd));
	}

	return m_dropdown_menu;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//wxRibbonGallery* giDataRibbonBuilder::PopulateColoursPanel(wxWindow* panel,
//	wxColour def, int gallery_id)
//{
//	wxRibbonGallery *gallery = wxDynamicCast(panel->FindWindow(gallery_id), wxRibbonGallery);
//	if (gallery)
//		gallery->Clear();
//	else
//		gallery = new wxRibbonGallery(panel, gallery_id);
//	wxMemoryDC& dc = m_bitmap_creation_dc;
//	wxRibbonGalleryItem *def_item =
//		AddColourToGallery(gallery, wxT("Default"), dc, &def);
//	gallery->SetSelection(def_item);
//	AddColourToGallery(gallery, wxT("BLUE"), dc);
//	AddColourToGallery(gallery, wxT("BLUE VIOLET"), dc);
//	AddColourToGallery(gallery, wxT("BROWN"), dc);
//	AddColourToGallery(gallery, wxT("CADET BLUE"), dc);
//	AddColourToGallery(gallery, wxT("CORAL"), dc);
//	AddColourToGallery(gallery, wxT("CYAN"), dc);
//	AddColourToGallery(gallery, wxT("DARK GREEN"), dc);
//	AddColourToGallery(gallery, wxT("DARK ORCHID"), dc);
//	AddColourToGallery(gallery, wxT("FIREBRICK"), dc);
//	AddColourToGallery(gallery, wxT("GOLD"), dc);
//	AddColourToGallery(gallery, wxT("GOLDENROD"), dc);
//	AddColourToGallery(gallery, wxT("GREEN"), dc);
//	AddColourToGallery(gallery, wxT("INDIAN RED"), dc);
//	AddColourToGallery(gallery, wxT("KHAKI"), dc);
//	AddColourToGallery(gallery, wxT("LIGHT BLUE"), dc);
//	AddColourToGallery(gallery, wxT("LIME GREEN"), dc);
//	AddColourToGallery(gallery, wxT("MAGENTA"), dc);
//	AddColourToGallery(gallery, wxT("MAROON"), dc);
//	AddColourToGallery(gallery, wxT("NAVY"), dc);
//	AddColourToGallery(gallery, wxT("ORANGE"), dc);
//	AddColourToGallery(gallery, wxT("ORCHID"), dc);
//	AddColourToGallery(gallery, wxT("PINK"), dc);
//	AddColourToGallery(gallery, wxT("PLUM"), dc);
//	AddColourToGallery(gallery, wxT("PURPLE"), dc);
//	AddColourToGallery(gallery, wxT("RED"), dc);
//	AddColourToGallery(gallery, wxT("SALMON"), dc);
//	AddColourToGallery(gallery, wxT("SEA GREEN"), dc);
//	AddColourToGallery(gallery, wxT("SIENNA"), dc);
//	AddColourToGallery(gallery, wxT("SKY BLUE"), dc);
//	AddColourToGallery(gallery, wxT("TAN"), dc);
//	AddColourToGallery(gallery, wxT("THISTLE"), dc);
//	AddColourToGallery(gallery, wxT("TURQUOISE"), dc);
//	AddColourToGallery(gallery, wxT("VIOLET"), dc);
//	AddColourToGallery(gallery, wxT("VIOLET RED"), dc);
//	AddColourToGallery(gallery, wxT("WHEAT"), dc);
//	AddColourToGallery(gallery, wxT("WHITE"), dc);
//	AddColourToGallery(gallery, wxT("YELLOW"), dc);
//
//	return gallery;
//}

//wxRibbonGalleryItem* giDataRibbonBuilder::AddColourToGallery(wxRibbonGallery *gallery,
//	wxString colour, wxMemoryDC& dc,
//	wxColour* value)
//{
//	wxRibbonGalleryItem* item = NULL;
//	wxColour c;
//	if (colour != wxT("Default"))
//		c = wxColour(colour);
//	if (!c.IsOk())
//		c = *value;
//	if (c.IsOk())
//	{
//		const int iWidth = 64;
//		const int iHeight = 40;
//
//		wxBitmap bitmap(iWidth, iHeight);
//		dc.SelectObject(bitmap);
//		wxBrush b(c);
//		dc.SetPen(*wxBLACK_PEN);
//		dc.SetBrush(b);
//		dc.DrawRectangle(0, 0, iWidth, iHeight);
//
//		colour = colour.Mid(0, 1) + colour.Mid(1).Lower();
//		wxSize size = dc.GetTextExtent(colour);
//		wxColour foreground = wxColour(~c.Red(), ~c.Green(), ~c.Blue());
//		if (abs(foreground.Red() - c.Red()) + abs(foreground.Blue() - c.Blue())
//			+ abs(foreground.Green() - c.Green()) < 64)
//		{
//			// Foreground too similar to background - use a different
//			// strategy to find a contrasting colour
//			foreground = wxColour((c.Red() + 64) % 256, 255 - c.Green(),
//				(c.Blue() + 192) % 256);
//		}
//		dc.SetTextForeground(foreground);
//		dc.DrawText(colour, (iWidth - size.GetWidth() + 1) / 2,
//			(iHeight - size.GetHeight()) / 2);
//		dc.SelectObjectAsSource(wxNullBitmap);
//
//		item = gallery->Append(bitmap, wxID_ANY);
//		gallery->SetItemClientObject(item, new ColourClientData(colour, c));
//	}
//	return item;
//}
