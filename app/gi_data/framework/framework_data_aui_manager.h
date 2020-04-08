// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_DATA_AUI_MANAGER_H_
#define _GI_GUI_FRAMEWORK_DATA_AUI_MANAGER_H_

#include "wx/wx.h"
#include "wx/aui/framemanager.h"
#include "wx/aui/auibook.h"

#include "any/base/anystl.h"

// builder pattern
class giDataAuiManager : public wxAuiManager
{
public:
	//
	void AddWorkspace(const wxString &space_name);
	void AddSolution(const wxString &solution_name);

	// aui framework events
	void OnRender(wxAuiManagerEvent& event);
	void OnPaneClose(wxAuiManagerEvent& evt);

	// page events
	void OnNotebookPageChanging(wxAuiNotebookEvent& event);
	void OnNotebookPageChanged(wxAuiNotebookEvent& event);
	void OnNotebookPageClose(wxAuiNotebookEvent& event);
	void OnNotebookPageClosed(wxAuiNotebookEvent& event);
	void OnNotebookRightDown(wxAuiNotebookEvent& event);
	void OnNotebookPageDragDone(wxAuiNotebookEvent& event);

protected:
	//
	friend class giDataFrame;
	short GetPages(const wxString &pane_name, std::vector<wxString> &pages);
	void ClosePage(const wxString &pane_name, const wxString &action);
	void FocusPage(const wxString &pane_name, const wxString &which_page);

private:
	DECLARE_EVENT_TABLE()

	std::unordered_map<wxString, wxAuiNotebook*> m_notebooks;
};

#endif
