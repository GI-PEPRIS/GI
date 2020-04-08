// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_WORKSPACE_NOTEBOOK_H_
#define _GI_GUI_FRAMEWORK_WORKSPACE_NOTEBOOK_H_

//
#include "framework_data_aui_notebook.h"

//
class giDataWorkspaceNotebook : public giDataAuiNotebook
{
public:
	giDataWorkspaceNotebook(wxWindow* parent, \
		const wxString &space_name, \
		wxWindowID id = wxID_ANY, \
		const wxPoint& pos = wxDefaultPosition, \
		const wxSize& size = wxDefaultSize, \
		long style = wxAUI_NB_DEFAULT_STYLE);

	~giDataWorkspaceNotebook();

public:
	//
	void CreatePage(const wxString &page_type, const wxString &page_name, const wxBitmap &icon);

private:
	//
	template<class T>
	void CreatePage(wxPanel * &panel, wxWindow * &canvas,
		const wxString &name, const wxWindowID id, const wxBitmap &icon)
	{
		wxBoxSizer* sizer;
		sizer = new wxBoxSizer(wxVERTICAL);

		panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
		canvas = new T(panel, id);

		sizer->Add(canvas, 1, wxALL | wxEXPAND, 5);
		panel->SetSizer(sizer);
		panel->Layout();
		sizer->Fit(panel);

		this->AddPage(panel, name, false, icon);
	}
};

#endif