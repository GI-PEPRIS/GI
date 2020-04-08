// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#include "framework_connect_login_dlg.h"

#include "framework_data_app.h"
#include "framework_data_frame.h"
#include "framework_data_macroes.h"
#include "framework_connect_db_setup_dlg.h"

#include "wx/textctrl.h"

// wx classinfo & events 
IMPLEMENT_CLASS(giLoginDlg, wxDialog)
BEGIN_EVENT_TABLE(giLoginDlg, wxDialog)
	EVT_BUTTON(ID_BTN_OK, giLoginDlg::OnOK)
	EVT_BUTTON(ID_BTN_CANCEL, giLoginDlg::OnCancel)
	EVT_BUTTON(ID_BTN_SETUP, giLoginDlg::OnSetup)
	EVT_CLOSE(giLoginDlg::OnClose)
	EVT_COMBOBOX(ID_CMB_DATABASE, giLoginDlg::OnChangeDatabase)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

giLoginDlg::giLoginDlg(wxWindow *parent) : wxDialog(parent, wxID_ANY, _("giDataApp"), wxDefaultPosition, wxSize(-1,400))
{
	//
	DoInitLayout();
}

/*!
*
**/
void giLoginDlg::DoInitLayout()
{
	// layout first
	wxBoxSizer* root_sizer = new wxBoxSizer(wxVERTICAL);
	root_sizer->AddSpacer(PX_BASESIZER_TO_UPPER_BORDER);
	this->SetSizer(root_sizer);

	wxBitmap login_bitmap;
	if (giTheApp(giDataApp).GetBitmap("/login/data_app_envelope.jpg", login_bitmap)) {
		wxStaticBitmap *staticBitmap = new wxStaticBitmap(this, ID_STATIC_BITMAP, login_bitmap);
		root_sizer->Add(staticBitmap);
	}

	root_sizer->AddSpacer(PX_SIZER_TO_SIZER_VECTICAL);
	wxBoxSizer* login_area_sizer = new wxBoxSizer(wxHORIZONTAL);
	root_sizer->Add(login_area_sizer, 0, wxALIGN_CENTER, 0);

	login_area_sizer->AddSpacer(PX_SIZER_TO_SIZER_HORIZONTAL);
	wxBoxSizer *label_sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxStaticText *version_label = new wxStaticText(this, wxID_ANY, _(wxT("Database:")), wxDefaultPosition, wxSize(-1, PX_NORMAL_BTN_HEIGHT));
		label_sizer->Add(version_label, 0, wxALL | wxALIGN_LEFT, 0);
		label_sizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);

		wxStaticText *username_label = new wxStaticText(this, wxID_STATIC, _(wxT("User:")), wxDefaultPosition, wxSize(-1, PX_NORMAL_BTN_HEIGHT));
		label_sizer->Add(username_label, 0, wxALL | wxALIGN_LEFT, 0);
		label_sizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);

		wxStaticText *pwd_label = new wxStaticText(this, wxID_STATIC, _(wxT("Password:")), wxDefaultPosition, wxSize(-1, PX_NORMAL_BTN_HEIGHT));
		label_sizer->Add(pwd_label, 0, wxALL | wxALIGN_LEFT, 0);
		label_sizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);
	}
	login_area_sizer->Add(label_sizer, 0, wxALL, 0);
	login_area_sizer->AddSpacer(PX_SIZER_TO_SIZER_HORIZONTAL);

	wxBoxSizer* input_sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxComboBox *db_combox = new wxComboBox(this, ID_CMB_DATABASE, wxT(""), wxDefaultPosition, wxSize(290, PX_NORMAL_BTN_HEIGHT), 0, 0, wxCB_READONLY);
		input_sizer->Add(db_combox, 0, wxALL, 0);
		input_sizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);

		wxTextCtrl* username_textctrl = new wxTextCtrl(this, ID_TXT_USERNAME, wxT(""), wxDefaultPosition, wxSize(290, PX_NORMAL_BTN_HEIGHT), 0);
		input_sizer->Add(username_textctrl, 0, wxALL, 0);
		input_sizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);

		wxTextCtrl* pwd_textctrl = new wxTextCtrl(this, ID_TXT_PASSWORD, wxT(""), wxDefaultPosition, wxSize(290, PX_NORMAL_BTN_HEIGHT), wxTE_PASSWORD);
		input_sizer->Add(pwd_textctrl, 0, wxALL, 0);
		input_sizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);
	}
	login_area_sizer->Add(input_sizer, 0, wxALL, 0);
	login_area_sizer->AddSpacer(PX_SIZER_TO_SIZER_HORIZONTAL);

	wxBoxSizer* btn_sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxButton *ok_btn = new wxButton(this, ID_BTN_OK, _(wxT("OK")), wxDefaultPosition, wxSize(60, PX_NORMAL_BTN_HEIGHT), 0);
		btn_sizer->Add(ok_btn, 0, wxALL, 0);
		btn_sizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);

		wxButton *setup_btn = new wxButton(this, ID_BTN_SETUP, _(wxT("Setup")), wxDefaultPosition, wxSize(60, PX_NORMAL_BTN_HEIGHT), 0);
		btn_sizer->Add(setup_btn, 0, wxALL, 0);
		btn_sizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);

		wxButton* cancel_btn = new wxButton(this, ID_BTN_CANCEL, _(wxT("Cancel")), wxDefaultPosition, wxSize(60, PX_NORMAL_BTN_HEIGHT), 0);
		btn_sizer->Add(cancel_btn, 0, wxALL, 0);
		btn_sizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);
	}
	login_area_sizer->Add(btn_sizer, 0, wxALL, 0);

	wxBoxSizer* source_sizer = new wxBoxSizer(wxHORIZONTAL);
	{
		source_sizer->AddSpacer(25);
		wxTextCtrl *db_source_txt = new wxTextCtrl(this, ID_TXT_DBSOURCE, _(wxT("")), wxDefaultPosition, wxSize(410, 40), wxTE_MULTILINE | wxTE_NO_VSCROLL | wxNO_BORDER | wxTE_CENTRE);
		source_sizer->Add(db_source_txt, 0, wxALL | wxALIGN_CENTER_VERTICAL, 1);
		db_source_txt->SetBackgroundColour(wxColour(255, 255, 255));
		db_source_txt->Enable(false);
	}
	root_sizer->Add(source_sizer, 0, wxALL, 5);
	root_sizer->AddSpacer(PX_BASESIZER_TO_BOTTOM_BORDER);

	//
	DoSetDBSetting();

	//
	root_sizer->Fit(this);
	Center();

	this->SetBackgroundColour(wxColor(255,255,255));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// events
//

//
void giLoginDlg::OnOK(wxCommandEvent& event) 
{											   
	// maybe changed after calling setup dlg										   	
	DBSourceDesc db_desc;
	giTheApp(giDataApp).ReadDBConfig(db_desc);
	db_desc.m_srcName = dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_DBSOURCE))->GetValue();
	db_desc.m_dbName = dynamic_cast<wxComboBox*>(FindWindow(ID_CMB_DATABASE))->GetValue();
	db_desc.m_user = dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_USERNAME))->GetValue();
	db_desc.m_pwd = dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_PASSWORD))->GetValue();
	//
	std::vector<string> db_names;
	if (giTheApp(giDataApp).IsCanLogin(db_desc, db_names)) 
	{
		//
		bool is_db_exist = false;
		for (int i = 0; i < db_names.size(); i++)
		{
			if (db_names[i] == db_desc.m_dbName)
			{
				is_db_exist = true;
				break;
			}
		}
		if (!is_db_exist && (db_desc.m_type == DBS_SQLSERVER || db_desc.m_type == DBS_MYSQL))
		{
			giTheApp(giDataApp).RemoveRecentDB(db_desc);
			DoSetDBSetting();
			wxString message = "The database " + db_desc.m_dbName + " isn't found in datasource!";
			wxMessageBox(message, "GI Message");
		}
		// double check
		else if (giTheApp(giDataApp).IsLogining(db_desc)) 
		{
			wxMessageBox(_(wxT("The same user is logining!")), _(wxT("GI Message")));
			wxDialog::EndModal(wxID_CANCEL);
		}
		else 
		{
			giTheApp(giDataApp).WriteDBConfig(db_desc);
			wxDialog::EndModal(wxID_OK);
		}
	}
	else
	{
		giTheApp(giDataApp).RemoveRecentDB(db_desc);
		DoSetDBSetting();
		wxMessageBox(_(wxT("Please reset database connection!")), _(wxT("GI Message")));
	}
}
void giLoginDlg::OnCancel(wxCommandEvent& event) 
{
	wxDialog::EndModal(wxID_CANCEL);
}
void giLoginDlg::OnClose(wxCloseEvent& event) 
{
	wxDialog::EndModal(wxID_CANCEL);
}
void giLoginDlg::OnSetup(wxCommandEvent& event) 
{
	giDBSetupDlg setup_dlg(this);
	setup_dlg.ShowModal();
	DoSetDBSetting();
}
void giLoginDlg::OnChangeDatabase(wxCommandEvent& event) 
{
	wxComboBox *cmb_box = dynamic_cast<wxComboBox*>(FindWindow(ID_CMB_DATABASE));
	if (cmb_box->GetSelection() >= 0)
	{
		DBSourceDesc db_desc;
		std::vector<DBSourceDesc> recent_dbs;
		giTheApp(giDataApp).ReadDBConfig(db_desc, recent_dbs);
		dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_USERNAME))->SetValue(recent_dbs[cmb_box->GetSelection()].m_user);
		dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_PASSWORD))->SetValue(recent_dbs[cmb_box->GetSelection()].m_pwd);
		dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_DBSOURCE))->SetValue(recent_dbs[cmb_box->GetSelection()].m_srcName);
		giTheApp(giDataApp).WriteDBConfig(recent_dbs[cmb_box->GetSelection()]);
	}
}
void giLoginDlg::DoSetDBSetting()
{
	wxComboBox *cmb_box = dynamic_cast<wxComboBox*>(FindWindow(ID_CMB_DATABASE));
	cmb_box->Clear();
	dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_USERNAME))->SetValue("");
	dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_PASSWORD))->SetValue("");
	dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_DBSOURCE))->SetValue("");
	DBSourceDesc db_desc;
	std::vector<DBSourceDesc> recent_dbs;
	giTheApp(giDataApp).ReadDBConfig(db_desc, recent_dbs);
	for (int i = 0; i < recent_dbs.size(); i++)
	{
		cmb_box->Append(recent_dbs[i].m_dbName);
	}
	cmb_box->SetSelection(-1);
	for (int i = 0; i < recent_dbs.size(); i++)
	{
		if (recent_dbs[i].m_type == db_desc.m_type && recent_dbs[i].m_srcName == db_desc.m_srcName && \
			recent_dbs[i].m_dbName == db_desc.m_dbName && recent_dbs[i].m_user == db_desc.m_user && recent_dbs[i].m_pwd == db_desc.m_pwd)
		{
			cmb_box->SetSelection(i);
			dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_USERNAME))->SetValue(recent_dbs[i].m_user);
			dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_PASSWORD))->SetValue(recent_dbs[i].m_pwd);
			dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_DBSOURCE))->SetValue(recent_dbs[i].m_srcName);
			break;
		}
	}
}

