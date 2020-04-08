// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#include "framework_data_aui_notebook.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
giDataAuiNotebook::giDataAuiNotebook(wxWindow* parent, \
	const wxString &name, \
	wxWindowID id, const wxPoint& pos, const wxSize& size, long style) \
	: wxAuiNotebook(parent, id, pos, size, style)
{
	this->SetName(name);
}

giDataAuiNotebook::~giDataAuiNotebook()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
giDataAuiNotebook::giNotebookPageFactoryTable &giDataAuiNotebook::NotebookPageFactoryGlobal()
{
	static giNotebookPageFactoryTable global_notebook_page_factory_table;
	return global_notebook_page_factory_table;
}

bool giDataAuiNotebook::RegisterNotebookPageFactory(const wxString &type, create_fn create_factory)
{
	giNotebookPageFactoryTable &page_table = NotebookPageFactoryGlobal();

	assert(page_table.find(type) == page_table.end());
	if (page_table.find(type) == page_table.end())
	{
		PageFactoryEntry entry;
		entry.m_page_type = type;
		entry.m_page_create_factory = std::move(create_factory);
		page_table.insert(std::pair<wxString, PageFactoryEntry>(type, entry));

		return true;
	}

	return false;
}

giDataAuiNotebook::PageFactoryEntry *giDataAuiNotebook::GetNotebookPageFactoryEntry(const wxString &type)
{
	giNotebookPageFactoryTable &page_table = NotebookPageFactoryGlobal();

	assert(page_table.find(type) != page_table.end());
	if (page_table.find(type) == page_table.end())
	{
		return nullptr;
	}

	return &page_table[type];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void giDataAuiNotebook::PageChanging(wxAuiNotebookEvent& event)
{

}
void giDataAuiNotebook::PageChanged(wxAuiNotebookEvent& event)
{

}
void giDataAuiNotebook::PageClose(wxAuiNotebookEvent& event)
{

}
void giDataAuiNotebook::PageClosed(wxAuiNotebookEvent& event)
{

}
void giDataAuiNotebook::PageDragDone(wxAuiNotebookEvent& event)
{

}
void giDataAuiNotebook::RightDown(wxAuiNotebookEvent& event)
{

}