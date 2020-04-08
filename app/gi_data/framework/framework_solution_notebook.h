// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_SOLUTION_NOTEBOOK_H_
#define _GI_GUI_FRAMEWORK_SOLUTION_NOTEBOOK_H_

#include "framework_data_aui_notebook.h"

// forward
class giDataExplorerTreeCtrl;

//
class giDataSolutionNotebook : public giDataAuiNotebook
{
public:
	giDataSolutionNotebook(wxWindow* parent, \
		const wxString &solution_name, \
		wxWindowID id = wxID_ANY, \
		const wxPoint& pos = wxDefaultPosition, \
		const wxSize& size = wxDefaultSize, \
		long style = wxAUI_NB_DEFAULT_STYLE);

	~giDataSolutionNotebook();

public:
	// DB Solution
	long CreateDBUserManagementExplorer(long explorer_window_id);

	// GIS Solution 
	long CreateMapCatelogueExplorer(long explorer_window_id);
	long CreateVectorMapAnalysisExplorer(long explorer_window_id);
	long CreateRasterMapAnalysisExplorer(long explorer_window_id);
	long CreateContourMapAnalysisExplorer(long explorer_window_id);

	// events

private:


};

#endif