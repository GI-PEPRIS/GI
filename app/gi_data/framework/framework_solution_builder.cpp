// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#include "framework_solution_builder.h"

#include "framework_solution_explorer_treectrl.h"
#include "framework_solution_notebook.h"
#include "framework_data_macroes.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
giDataSolutionBuilder::giDataSolutionBuilder(wxWindow *parent) : m_parent(parent), m_solution_event_id(0)
{
}

giDataSolutionBuilder::~giDataSolutionBuilder()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
giDataSolutionNotebook *giDataSolutionBuilder::CreateSolution(const wxString &solution_name)
{
	//
	long notebook_style = wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_EXTERNAL_MOVE | wxNO_BORDER | wxAUI_NB_BOTTOM;
	notebook_style &= ~(wxAUI_NB_CLOSE_BUTTON | wxAUI_NB_CLOSE_ON_ACTIVE_TAB | wxAUI_NB_CLOSE_ON_ALL_TABS);

	giDataSolutionNotebook *solution_notebook = new giDataSolutionNotebook(m_parent, solution_name, wxID_ANY,
		wxDefaultPosition,
		wxSize(PX_SOLUTION_EXPLORER_WIDTH, PX_SOLUTION_EXPLORER_HEIGHT),
		notebook_style);

	//
	solution_notebook->Freeze();
	//
	if (solution_name.Upper() == "GIS SOLUTION")
	{
		// map catalogue explorer and reserve 1000 event ids
		m_solution_event_id = solution_notebook->CreateMapCatelogueExplorer(m_solution_event_id);
	}
	// don't user elseif since m_solution_event_id is in continuous way
	if (solution_name.Upper() == "DB SOLUTION")
	{
		m_solution_event_id = solution_notebook->CreateDBUserManagementExplorer(m_solution_event_id);
	}
	solution_notebook->Thaw();

	return solution_notebook;
}