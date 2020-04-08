// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#include "framework_data_frame.h"
#include "framework_data_app.h"
#include "framework_connect_login_dlg.h"

#include "framework_connect_mergedatabase_dlg.h"
#include "framework_connect_orgnization_dlg.h"
#include "framework_connect_mergedatabase_function.h"
#include "framework_connect_db_setup_dlg.h"

#include "gis/gis_solution_maplayer_manager.h"

// wx
#include "wx/toolbar.h"

//
#include "any/db/anyaccessorbasic.h"
#include "any/db/anyaccessor.h"
using namespace AnyDB;

//this app doesn't work with petro package 
//#include "any/petro/accumulationassessor.h"
//#include "any/petro/assessmentusermanager.h"
//using namespace AnyPetro;

//
BEGIN_EVENT_TABLE(giDataFrame,wxFrame)
	EVT_MENU(wxID_EXIT, giDataFrame::OnQuit)
	EVT_CLOSE(giDataFrame::OnWindowClose)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
giDataFrame::giDataFrame() : m_thread_pool_instance(0), wxFrame(NULL, wxID_ANY, "giData")
{
}

giDataFrame::~giDataFrame()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool giDataFrame::ShowFrame(bool show)
{
	DoInitAnyPackages();
	DoInitLayout();
	this->Show(show);

	Maximize(true);
	SetMinSize(wxSize(800, 600));
	//Center();
	return true;
}

// to do something before frame destroied
void giDataFrame::ExitFrame()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void giDataFrame::OnQuit(wxCommandEvent &event)
{
	
}

void giDataFrame::OnWindowClose(wxCloseEvent &event) 
{
	// firstly, dump GUI ENV
	DoUnInitLayout();

	// secondly, dump core settings
	DoUnInitAnyPackages();

	// lastly, to go silently
	OnCloseWindow(event);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void giDataFrame::DoInitAnyPackages() 
{
	// db package
	DBSourceDesc db_desc;
	giTheApp(giDataApp).ReadDBConfig(db_desc);
	bool rt = CAnyAccessor::InitDB(db_desc);
	assert(rt);

	if (rt) {
		// thread package
		m_thread_pool_instance = new JTCInitialize();
	}
}
void giDataFrame::DoUnInitAnyPackages() 
{
	//
	CAnyAccessor::ReleaseDB();

	//
	if (m_thread_pool_instance) delete m_thread_pool_instance;
	m_thread_pool_instance = 0;
}

//
void giDataFrame::DoInitLayout()
{
	// top region of this frame
	wxRibbonBar *ribbon_bar = new wxRibbonBar(this, -1, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_FLOW_HORIZONTAL
		| wxRIBBON_BAR_SHOW_PAGE_LABELS
		| wxRIBBON_BAR_SHOW_PANEL_EXT_BUTTONS
		| wxRIBBON_BAR_SHOW_TOGGLE_BUTTON
		| wxRIBBON_BAR_SHOW_HELP_BUTTON
	);
	m_ribbon_builder.SetProperty(ribbon_bar);
	m_ribbon_builder.CreateBasicPage();
	m_ribbon_builder.CreateMapPage();
	m_ribbon_builder.Realize();

	// main region of this frame
	wxPanel *aui_panel = new wxPanel(this, wxID_DEFAULT);
	m_aui_manager.SetManagedWindow(aui_panel);
	m_aui_manager.AddWorkspace("Work Space");
	m_aui_manager.AddSolution("GIS Solution"); // dock the left side
	m_aui_manager.AddSolution("DB Solution"); // in float mode

	m_aui_manager.Update();

	//
	wxSizer *frame_sizer = new wxBoxSizer(wxVERTICAL);
	frame_sizer->Add(ribbon_bar, 0, wxEXPAND);
	frame_sizer->Add(aui_panel, 1, wxEXPAND);
	SetSizer(frame_sizer);
}

//
void giDataFrame::DoUnInitLayout() 
{
	// 
	giGISMapLayerManager::GetLayerManager().Commit();

	m_aui_manager.UnInit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//

void giDataFrame::OnRibbonBarClicked(wxRibbonButtonBarEvent& event)
{
	DoDispatchRibbonEvent(&event);
}

void giDataFrame::OnRibbonBarClicked(wxRibbonToolBarEvent& event)
{	
	DoDispatchRibbonEvent(&event);
}

void giDataFrame::OnRibbonControlClicked(wxCommandEvent& event)
{
	DoDispatchRibbonEvent(&event);
}

void giDataFrame::OnRibbonControlClicked(wxSpinEvent& event)
{
	DoDispatchRibbonEvent(&event);
}

void giDataFrame::OnRibbonPanelExtended(wxRibbonPanelEvent &event) 
{
	DoDispatchRibbonEvent(&event);
}

inline void giDataFrame::DoDispatchRibbonEvent(wxEvent *event)
{
	wxString &func_key = GetEventFunctionKey(event->GetId(),event->GetEventType());
	if (func_key.size())
	{
		(giTheApp(giDataApp).GetFrame().*EventFunctionTableGlobal()[func_key])(event);
	}
}

// callback against dropdown menus
void giDataFrame::DoDispatchRibbonMenuClick(wxCommandEvent& event)
{
	giDataRibbonBuilder::giRibbonCommand *ribbon_cmd = dynamic_cast<giDataRibbonBuilder::giRibbonCommand *>(event.GetEventUserData());
	assert(ribbon_cmd);
	if (ribbon_cmd->m_name == "Connect")
	{
		wxString db_name = ribbon_cmd->m_dropdown_contents[event.GetId()-ribbon_cmd->m_id-1];
		DBSourceDesc db_desc;
		std::vector<DBSourceDesc> recent_dbs;
		giTheApp(giDataApp).ReadDBConfig(db_desc, recent_dbs);
		for (int i = 0; i < recent_dbs.size(); i++)
		{
			if (recent_dbs[i].m_dbName == db_name.ToStdString())
			{
				giTheApp(giDataApp).WriteDBConfig(recent_dbs[i]);
				break;
			}
		}
	}
	else if (ribbon_cmd->m_name == "Close")
	{
		wxString which_action = ribbon_cmd->m_dropdown_contents[event.GetId() - ribbon_cmd->m_id - 1];
		giTheApp(giDataApp).GetFrame().m_aui_manager.ClosePage("Work Space", which_action);
	}
	else if (ribbon_cmd->m_name == "Windows")
	{
		wxString which_page = ribbon_cmd->m_dropdown_contents[event.GetId() - ribbon_cmd->m_id - 1];
		giTheApp(giDataApp).GetFrame().m_aui_manager.FocusPage("Work Space", which_page);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// file/db
void giDataFrame::OnRibbonConnectDBClickEvent(wxEvent *event)
{
	giDataRibbonBuilder::giRibbonCommand *ribbon_cmd = dynamic_cast<giDataRibbonBuilder::giRibbonCommand *>(event->GetEventUserData());
	assert(ribbon_cmd);
	ribbon_cmd->m_dropdown_contents.clear();
	ribbon_cmd->m_dropdown_ids.clear();
	ribbon_cmd->m_dropdown_ids_checked.clear();

	DBSourceDesc db_desc;
	std::vector<DBSourceDesc> recent_dbs;
	giTheApp(giDataApp).ReadDBConfig(db_desc, recent_dbs);
	for (int i = 0; i < recent_dbs.size(); i++)
	{
		if (!recent_dbs[i].m_dbName.length())
			continue;

		ribbon_cmd->m_dropdown_ids.push_back(event->GetId()+i+1);
		ribbon_cmd->m_dropdown_contents.push_back(recent_dbs[i].m_dbName);
		if (recent_dbs[i].m_dbName == db_desc.m_dbName)
		{
			ribbon_cmd->m_dropdown_ids_checked.push_back(true);
		}
		else
		{
			ribbon_cmd->m_dropdown_ids_checked.push_back(false);
		}
	}
	((wxRibbonButtonBarEvent*)event)->PopupMenu(m_ribbon_builder.GetDropdownMenu(*ribbon_cmd));
}
RIBBON_REGISTER_EVENT_FUNC(wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, "CONNECT", OnRibbonConnectDBClickEvent, &giDataFrame::OnRibbonConnectDBClickEvent);

void giDataFrame::OnRibbonNewDBClickEvent(wxEvent *event)
{
	giDBSetupDlg setup_dlg(this);
	if (setup_dlg.ShowModal() == wxID_OK)
	{
		DBSourceDesc db_desc;
		setup_dlg.DoGetDBSetting(db_desc);
		giTheApp(giDataApp).WriteDBConfig(db_desc);
	}
}
RIBBON_REGISTER_EVENT_FUNC(wxEVT_RIBBONBUTTONBAR_CLICKED, "NEW", OnRibbonNewDBClickEvent, &giDataFrame::OnRibbonNewDBClickEvent);

void giDataFrame::OnRibbonUpdateDBClickEvent(wxEvent *event)
{
	if (wxMessageBox(_(wxT("Do you really want to update?")), _(wxT("GI Message")), wxYES_NO) == wxYES)
	{
		MergeDataBaseFunction func;
		func.UpdateDatabaseStructure();
	}
}
RIBBON_REGISTER_EVENT_FUNC(wxEVT_RIBBONBUTTONBAR_CLICKED, "UPDATE", OnRibbonUpdateDBClickEvent, &giDataFrame::OnRibbonUpdateDBClickEvent);
 
void giDataFrame::OnRibbonMergeDBClickEvent(wxEvent *event)
{
	SelectMergeDataBaseDlg *mergedlg = new SelectMergeDataBaseDlg(this);
	std::vector<DBSourceDesc> srcdatabases;
	DBSourceDesc targetdatabase;
	bool isupdatesamelement;
	if (mergedlg->ShowModal() == wxID_OK)
	{
		srcdatabases = mergedlg->m_srcdatabases;
		targetdatabase = mergedlg->m_targetdatabase;
		isupdatesamelement = mergedlg->m_updatesameelement;
		if (srcdatabases.size() == 0)
		{
			wxMessageBox(_(wxT("No source database selected!")), _(wxT("Info")));
			return;
		}
		else if (targetdatabase.m_dbName == "")
		{
			wxMessageBox(_(wxT("No target database selected!")), _(wxT("Info")));
			return;
		}
		MergeDataBaseFunction func;
		func.MergeDatabase(srcdatabases, targetdatabase, isupdatesamelement);
	}
	for (int i = 0; i < srcdatabases.size(); i++)
	{
		CAnyAccessor::ReleaseDB(srcdatabases[i]);
	}
	CAnyAccessor::ReleaseDB(targetdatabase);
	wxMessageBox(_(wxT("Merge DB Event!")), _(wxT("GI Message")));
}
RIBBON_REGISTER_EVENT_FUNC(wxEVT_RIBBONBUTTONBAR_CLICKED, "MERGE", OnRibbonMergeDBClickEvent, &giDataFrame::OnRibbonMergeDBClickEvent);

//
// file/view
void giDataFrame::OnRibbonGISSolutionCheckEvent(wxEvent *event)
{
	DoAuiManagerCheck(event);
}
RIBBON_REGISTER_EVENT_FUNC(wxEVT_CHECKBOX, "GIS Solution", OnRibbonGISSolutionCheckEvent, &giDataFrame::OnRibbonGISSolutionCheckEvent);

void giDataFrame::OnRibbonDBSolutionCheckEvent(wxEvent *event)
{
	DoAuiManagerCheck(event);
}
RIBBON_REGISTER_EVENT_FUNC(wxEVT_CHECKBOX, "DB Solution", OnRibbonDBSolutionCheckEvent, &giDataFrame::OnRibbonDBSolutionCheckEvent);

void giDataFrame::OnRibbonWorkspaceCheckEvent(wxEvent *event)
{
	DoAuiManagerCheck(event);
}
RIBBON_REGISTER_EVENT_FUNC(wxEVT_CHECKBOX, "Work Space", OnRibbonWorkspaceCheckEvent, &giDataFrame::OnRibbonWorkspaceCheckEvent);

void giDataFrame::DoAuiManagerCheck(wxEvent *event)
{
	giDataRibbonBuilder::giRibbonCommand *ribbon_cmd = dynamic_cast<giDataRibbonBuilder::giRibbonCommand *>(event->GetEventUserData());
	assert(ribbon_cmd);

	ribbon_cmd->m_is_checked = !ribbon_cmd->m_is_checked;
	m_aui_manager.GetPane(ribbon_cmd->m_name.Upper()).Show(ribbon_cmd->m_is_checked);
	m_aui_manager.Update();
}

// file/window pane
void giDataFrame::OnRibbonListWindowClickEvent(wxEvent *event)
{
	giDataRibbonBuilder::giRibbonCommand *ribbon_cmd = dynamic_cast<giDataRibbonBuilder::giRibbonCommand *>(event->GetEventUserData());
	assert(ribbon_cmd);
	ribbon_cmd->m_dropdown_contents.clear();
	ribbon_cmd->m_dropdown_ids.clear();
	ribbon_cmd->m_dropdown_ids_checked.clear();

	std::vector<wxString> pages;
	short focus_page_idx = m_aui_manager.GetPages("Work Space", pages);
	for (int i = 0; i < pages.size(); i++)
	{
		ribbon_cmd->m_dropdown_ids.push_back(event->GetId() + i + 1);
		ribbon_cmd->m_dropdown_contents.push_back(pages[i]);
		if (i == focus_page_idx)
		{
			ribbon_cmd->m_dropdown_ids_checked.push_back(true);
		}
		else
		{
			ribbon_cmd->m_dropdown_ids_checked.push_back(false);
		}
	}
	((wxRibbonButtonBarEvent*)event)->PopupMenu(m_ribbon_builder.GetDropdownMenu(*ribbon_cmd));
}
RIBBON_REGISTER_EVENT_FUNC(wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, "WINDOWS", OnRibbonListWindowClickEvent, &giDataFrame::OnRibbonListWindowClickEvent);

void giDataFrame::OnRibbonCloseWindowClickEvent(wxEvent *event)
{
	giDataRibbonBuilder::giRibbonCommand *ribbon_cmd = dynamic_cast<giDataRibbonBuilder::giRibbonCommand *>(event->GetEventUserData());
	assert(ribbon_cmd);

	((wxRibbonButtonBarEvent*)event)->PopupMenu(m_ribbon_builder.GetDropdownMenu(*ribbon_cmd));
}
RIBBON_REGISTER_EVENT_FUNC(wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, "CLOSE", OnRibbonCloseWindowClickEvent, &giDataFrame::OnRibbonCloseWindowClickEvent);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void giDataFrame::OnRibbonMapEditPanelExtendedEvent(wxEvent *event)
{
	wxMessageBox(_(wxT("Pannel Extended Event!")), _(wxT("GI Message")));
}
RIBBON_REGISTER_EVENT_FUNC(wxEVT_RIBBONPANEL_EXTBUTTON_ACTIVATED, "Map Edit", OnRibbonMapEditPanelExtendedEvent, &giDataFrame::OnRibbonMapEditPanelExtendedEvent);
