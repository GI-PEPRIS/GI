// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_LOGIN_DLG_H_
#define _GI_GUI_FRAMEWORK_LOGIN_DLG_H_

#include "wx/dialog.h"
#include "wx/spinctrl.h"
#include "wx/statline.h"
#include "wx/wxprec.h"

// connect to data source & verify PWD
//
class giLoginDlg: public wxDialog
{     
	enum
	{
		ID_CMB_DATABASE,
		ID_TXT_USERNAME,
		ID_TXT_PASSWORD,
		
		ID_BTN_OK,
		ID_BTN_CANCEL,
		
		ID_BTN_SETUP,		// select or swtich to other datasource 

		ID_STATIC_BITMAP,	// login logo
		ID_TXT_DBSOURCE,	// db info
	};
	
	DECLARE_CLASS(giLoginDlg)
	DECLARE_EVENT_TABLE()

public:
	// ctor
    giLoginDlg(wxWindow *parent);
	
public:
	// events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
	void OnSetup(wxCommandEvent& event);
	void OnChangeDatabase(wxCommandEvent& event);
	void DoSetDBSetting();

private:
	// 
	void DoInitLayout();
};

#endif
   
