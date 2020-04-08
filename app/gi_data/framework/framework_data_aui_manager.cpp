// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#include "wx/aui/auibook.h"

#include "framework_data_aui_manager.h"

#include "framework_solution_builder.h"
#include "framework_solution_notebook.h"
#include "framework_workspace_notebook.h"

#include "framework_workspace_map_canvas.h"
#include "framework_workspace_well_section_canvas.h"
#include "framework_workspace_seis_profile_canvas.h"
#include "framework_workspace_cube_canvas.h"


BEGIN_EVENT_TABLE(giDataAuiManager, wxAuiManager)
	EVT_AUI_RENDER(giDataAuiManager::OnRender)
	EVT_AUI_PANE_CLOSE(giDataAuiManager::OnPaneClose)

	EVT_AUINOTEBOOK_PAGE_CHANGING(wxID_ANY, giDataAuiManager::OnNotebookPageChanging)
	EVT_AUINOTEBOOK_PAGE_CHANGED(wxID_ANY, giDataAuiManager::OnNotebookPageChanged)
	EVT_AUINOTEBOOK_PAGE_CLOSE(wxID_ANY, giDataAuiManager::OnNotebookPageClose)
	EVT_AUINOTEBOOK_PAGE_CLOSED(wxID_ANY, giDataAuiManager::OnNotebookPageClosed)
	EVT_AUINOTEBOOK_TAB_RIGHT_DOWN(wxID_ANY, giDataAuiManager::OnNotebookRightDown)
	EVT_AUINOTEBOOK_DRAG_DONE(wxID_ANY, giDataAuiManager::OnNotebookPageDragDone)
END_EVENT_TABLE()


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void giDataAuiManager::AddWorkspace(const wxString &space_name) 
{
	assert(!GetPane(space_name.Upper()).window);
	if (!GetPane(space_name.Upper()).window)
	{
		long notebook_style = wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_EXTERNAL_MOVE | wxNO_BORDER | wxAUI_NB_CLOSE_ON_ALL_TABS;
		giDataWorkspaceNotebook *workspace = new giDataWorkspaceNotebook(this->GetManagedWindow(), space_name.Upper(), wxID_ANY);
		
		workspace->Freeze();

		//
		workspace->CreatePage(giDataWorkspaceMapCanvas::kPageType, wxT(""), giDataWorkspaceMapCanvas::kPageIcon);
		//workspace->CreatePage(giDataWorkspaceWellSectionCanvas::kPageType, wxT(""), giDataWorkspaceWellSectionCanvas::kPageIcon);
		//workspace->CreatePage(giDataWorkspaceSeisProfileCanvas::kPageType, wxT(""), giDataWorkspaceSeisProfileCanvas::kPageIcon);
		//workspace->CreatePage(giDataWorkspaceCubeCanvas::kPageType, wxT(""), giDataWorkspaceCubeCanvas::kPageIcon);

		//
		wxAuiPaneInfo pane_info = wxAuiPaneInfo().Name(space_name.Upper()).Center().CaptionVisible(false).PaneBorder(false);
		this->AddPane(workspace, pane_info);

		workspace->Thaw();

		assert(m_notebooks.find(space_name) == m_notebooks.end());
		m_notebooks.insert(std::pair<wxString, wxAuiNotebook*>(space_name, workspace));
		workspace->SetBackgroundColour(wxColour(255, 255, 255));
	}

}

// solution and its explorers
void giDataAuiManager::AddSolution(const wxString &solution_name)
{
	assert(!GetPane(solution_name.Upper()).window);
	if (!GetPane(solution_name.Upper()).window)
	{
		giDataSolutionBuilder solution_builder(this->GetManagedWindow());
		giDataSolutionNotebook *solution_book = solution_builder.CreateSolution(solution_name);

		wxAuiPaneInfo pane_info = wxAuiPaneInfo().Name(solution_name.Upper()).Left()./*Layer(1).*/\
			/*Position(0).*/PaneBorder(true).Caption(_(solution_name))/*.MaximizeButton(false).CloseButton(false)*/;

		this->AddPane(solution_book, pane_info);

		assert(m_notebooks.find(solution_name) == m_notebooks.end());
		m_notebooks.insert(std::pair<wxString, wxAuiNotebook*>(solution_name, solution_book));
	}
}

short giDataAuiManager::GetPages(const wxString &pane_name, std::vector<wxString> &pages)
{
	giDataAuiNotebook *note_book = dynamic_cast<giDataAuiNotebook*>(this->GetPane(pane_name.Upper()).window);
	assert(note_book);

	for (int i = 0; i < note_book->GetPageCount(); i++)
	{
		pages.push_back(note_book->GetPageText(i));

	}
	return note_book->GetSelection();
}

void giDataAuiManager::ClosePage(const wxString &pane_name, const wxString &action)
{

}
void giDataAuiManager::FocusPage(const wxString &pane_name, const wxString &which_page)
{
	giDataAuiNotebook *note_book = dynamic_cast<giDataAuiNotebook*>(this->GetPane(pane_name.Upper()).window);
	assert(note_book);

	for (int i = 0; i < note_book->GetPageCount(); i++)
	{
		if (note_book->GetPageText(i) == which_page)
		{
			note_book->SetSelection(i);
			break;
		}
	}

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void giDataAuiManager::OnRender(wxAuiManagerEvent& event)
{
	wxAuiManager::OnRender(event);

	//get current frame
	//CAssessorFrame *hostframe = dynamic_cast<CAssessorFrame *>(GetManagedWindow());
	//assert(hostframe);

	//hostframe->PaintLogo(event);
}
void giDataAuiManager::OnPaneClose(wxAuiManagerEvent& event)
{
	wxString pane_name = event.pane->name;
}

//
void giDataAuiManager::OnNotebookPageChanging(wxAuiNotebookEvent& event)
{
	giDataAuiNotebook *ctrl = (giDataAuiNotebook*)event.GetEventObject();
}
void giDataAuiManager::OnNotebookPageChanged(wxAuiNotebookEvent& event)
{

}
void giDataAuiManager::OnNotebookPageClose(wxAuiNotebookEvent& event)
{

}
void giDataAuiManager::OnNotebookPageClosed(wxAuiNotebookEvent& event)
{

}
void giDataAuiManager::OnNotebookRightDown(wxAuiNotebookEvent& event)
{
	giDataAuiNotebook *ctrl = (giDataAuiNotebook*)event.GetEventObject();
	assert(m_notebooks.find(ctrl->GetName())!=m_notebooks.end());
	
}
void giDataAuiManager::OnNotebookPageDragDone(wxAuiNotebookEvent& event)
{

}