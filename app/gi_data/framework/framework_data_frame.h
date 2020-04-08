// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_DATA_FRAME_H_
#define _GI_GUI_FRAMEWORK_DATA_FRAME_H_

//
#include "wx/wx.h"
#include "wx/ribbon/panel.h"
#include "wx/ribbon/toolbar.h"
#include "wx/ribbon/buttonbar.h"

//
#include "framework_data_event.h"
#include "framework_data_aui_manager.h"
#include "framework_ribbon_builder.h"

// forward class
class JTCInitialize; 

//
class giDataFrame : public wxFrame, public giDataEvent<giDataFrame, wxEvent>
{
	//
	friend class giDataRibbonBuilder;

public:
	giDataFrame();
	~giDataFrame();

public:
	// dont override show func as show func maybe triggered by onwindowclose event
	bool ShowFrame(bool show = true);
	void ExitFrame(); // to do something before frame destroied

	// event table funcs
	void OnQuit(wxCommandEvent &event);
	void OnWindowClose(wxCloseEvent &event);

	// handle functions against controls on ribbon bar
	void OnRibbonBarClicked(wxRibbonButtonBarEvent& event);
	void OnRibbonBarClicked(wxRibbonToolBarEvent& event);
	void OnRibbonControlClicked(wxCommandEvent& event);
	void OnRibbonControlClicked(wxSpinEvent& event);
	void OnRibbonPanelExtended(wxRibbonPanelEvent &event);

	void DoDispatchRibbonEvent(wxEvent* event);
	void DoDispatchRibbonMenuClick(wxCommandEvent& event);

	// file/database
	void OnRibbonConnectDBClickEvent(wxEvent *event);
	void OnRibbonNewDBClickEvent(wxEvent *event);
	void OnRibbonUpdateDBClickEvent(wxEvent *event);
	void OnRibbonMergeDBClickEvent(wxEvent *event);

	// file/view
	void OnRibbonGISSolutionCheckEvent(wxEvent *event);
	void OnRibbonDBSolutionCheckEvent(wxEvent *event);
	void OnRibbonWorkspaceCheckEvent(wxEvent *event);
	void DoAuiManagerCheck(wxEvent *event);

	// file/window
	void OnRibbonListWindowClickEvent(wxEvent *event);
	void OnRibbonCloseWindowClickEvent(wxEvent *event);

	//
	void OnRibbonMapEditPanelExtendedEvent(wxEvent *event);

private:
	void DoInitAnyPackages();
	void DoUnInitAnyPackages();

	void DoInitLayout();
	void DoUnInitLayout();

private:
	// declare event table
	DECLARE_EVENT_TABLE()

public:
	//
	giDataAuiManager m_aui_manager;
	giDataRibbonBuilder m_ribbon_builder;

	// initializations
	JTCInitialize *m_thread_pool_instance;

};

#endif