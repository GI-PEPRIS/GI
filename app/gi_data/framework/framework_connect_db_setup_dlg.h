// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_DB_SETUP_H_
#define _GI_GUI_FRAMEWORK_DB_SETUP_H_

#include "wx/wx.h"
#include "wx/dialog.h"

// forward
namespace AnyDB{ struct DBSourceDesc; }

// connect to a source then list all dbs
class giDBSetupDlg : public wxDialog
{
	DECLARE_CLASS(giDBSetupDlg)
	DECLARE_EVENT_TABLE()

	enum {
		ID_BTN_CONNECT, 
		ID_BTN_CREATE,
		ID_BTN_DELETE,
		ID_BTN_OK,
		ID_BTN_CANCEL,

		ID_CMB_DATABASETYPE,
		ID_TXT_DATASOURCE,
		ID_TXT_USERNAME,
		ID_TXT_PASSWORD,
		
		ID_LIST_DB,

		// right menum
		ID_DELETEDATABASE2,
		ID_DELETEDATABASE3,
		ID_DELETEDATABASEMULTI,
	};

public:
	// ctor & d'ctor
	giDBSetupDlg(wxWindow *parent);
	~giDBSetupDlg();

public:
	// events
	void OnConnect(wxCommandEvent& event);
	void OnCreate(wxCommandEvent& event);
	void OnDelete(wxCommandEvent& event);
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnChangeDatabaseType(wxCommandEvent& event);

	//
	void DoInitLayout();
	void DoGetDBSetting(AnyDB::DBSourceDesc &db_desc);
	void DoSetDBSetting();
};

#endif
