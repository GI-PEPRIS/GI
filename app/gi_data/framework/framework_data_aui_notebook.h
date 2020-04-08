// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_DATA_AUI_NOTEBOOK_H_
#define _GI_GUI_FRAMEWORK_DATA_AUI_NOTEBOOK_H_

#include "wx/wx.h"
#include "wx/aui/auibook.h"

#include "any/base/anystl.h"

// builder pattern
class giDataAuiNotebook : public wxAuiNotebook
{
public:
	//
	typedef wxWindow* (*create_fn)(wxWindow*, long);
	struct PageFactoryEntry
	{
		wxString m_page_type = wxT("");
		create_fn m_page_create_factory;
	};
	typedef std::unordered_map<wxString, PageFactoryEntry> giNotebookPageFactoryTable;

public:
	giDataAuiNotebook(wxWindow* parent, \
		const wxString &solution_name, \
		wxWindowID id = wxID_ANY, \
		const wxPoint& pos = wxDefaultPosition, \
		const wxSize& size = wxDefaultSize, \
		long style = wxAUI_NB_DEFAULT_STYLE);

	virtual ~giDataAuiNotebook();

public:
	//
	static giNotebookPageFactoryTable &NotebookPageFactoryGlobal();
	static bool RegisterNotebookPageFactory(const wxString &type, create_fn create_factory);
	static PageFactoryEntry *GetNotebookPageFactoryEntry(const wxString &type);

protected:
	//
	virtual void PageChanging(wxAuiNotebookEvent& event);
	virtual void PageChanged(wxAuiNotebookEvent& event);
	virtual void PageClose(wxAuiNotebookEvent& event);
	virtual void PageClosed(wxAuiNotebookEvent& event);
	virtual void PageDragDone(wxAuiNotebookEvent& event);
	virtual void RightDown(wxAuiNotebookEvent& event);

private:

};

#endif
