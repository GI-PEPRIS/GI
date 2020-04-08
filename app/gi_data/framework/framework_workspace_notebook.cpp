// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#include "framework_workspace_notebook.h"
#include "framework_data_macroes.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
giDataWorkspaceNotebook::giDataWorkspaceNotebook(wxWindow* parent, \
	const wxString &space_name, \
	wxWindowID id, const wxPoint& pos, const wxSize& size, long style) \
	: giDataAuiNotebook(parent, space_name, id, pos, size, style)
{
}

giDataWorkspaceNotebook::~giDataWorkspaceNotebook()
{
}

void giDataWorkspaceNotebook::CreatePage(const wxString &page_type, const wxString &page_name, const wxBitmap &icon)
{
	PageFactoryEntry *factory_entry = giDataAuiNotebook::GetNotebookPageFactoryEntry(page_type);
	assert(factory_entry);

	if (factory_entry)
	{
		wxBoxSizer* sizer;
		sizer = new wxBoxSizer(wxVERTICAL);

		wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
		wxWindow *page = factory_entry->m_page_create_factory(panel, wxID_ANY);
		sizer->Add(page, 1, wxALL | wxEXPAND, 5);
	
		panel->SetSizer(sizer);
		panel->Layout();
		sizer->Fit(panel);

		wxString inner_name = page_type;
		if(!page_name.IsEmpty()) inner_name = inner_name + wxT(":") + page_name;
		this->AddPage(panel, inner_name, false, icon);
	}
}
