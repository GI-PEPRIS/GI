// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#include "framework_connect_db_setup_dlg.h"
#include "framework_data_app.h"
#include "framework_data_macroes.h"

// db sources
#include "any/db/anyaccessorbasic.h"
#include "any/db/anyaccessor.h"
using namespace AnyDB;
//#include "any/petro/accumulationassessor.h"
//#include "any/petro/assessmentusermanager.h"
//using namespace AnyPetro;

#include "any/base/anyfilebasic.h"

///////////
IMPLEMENT_CLASS(giDBSetupDlg, wxDialog)
BEGIN_EVENT_TABLE(giDBSetupDlg, wxDialog)
	EVT_BUTTON(ID_BTN_CONNECT, giDBSetupDlg::OnConnect)
	EVT_BUTTON(ID_BTN_CREATE, giDBSetupDlg::OnCreate)
	EVT_BUTTON(ID_BTN_DELETE, giDBSetupDlg::OnDelete)
	EVT_BUTTON(ID_BTN_OK, giDBSetupDlg::OnOK)
	EVT_BUTTON(ID_BTN_CANCEL, giDBSetupDlg::OnCancel)
	EVT_COMBOBOX(ID_CMB_DATABASETYPE, giDBSetupDlg::OnChangeDatabaseType)
	EVT_LISTBOX_DCLICK(ID_LIST_DB, giDBSetupDlg::OnOK)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
giDBSetupDlg::giDBSetupDlg(wxWindow *parent) :wxDialog(parent, wxID_ANY, _("Connect to a database"), wxDefaultPosition, wxSize(560, -1), wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP) {
	DoInitLayout();	
}
giDBSetupDlg::~giDBSetupDlg(){
}

///////////////////////////////////////////////////
//
//
void giDBSetupDlg::DoInitLayout()
{
	wxBoxSizer* root_sizer = new wxBoxSizer(wxVERTICAL);
	root_sizer->AddSpacer(PX_BASESIZER_TO_UPPER_BORDER);
	this->SetSizer(root_sizer);

	wxBoxSizer* downareaSizer = new wxBoxSizer(wxHORIZONTAL);
	root_sizer->Add(downareaSizer);
	root_sizer->AddSpacer(PX_SIZER_TO_SIZER_VECTICAL);

	wxBoxSizer* inputSizer = new wxBoxSizer(wxVERTICAL);
	downareaSizer->AddSpacer(PX_BASESIZER_TO_RIGHT_BORDER);
	downareaSizer->Add(inputSizer, 0, wxALL | wxALIGN_CENTER, 0);

	int label_width = 65;
	wxBoxSizer* first_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	{
		wxStaticText* databasetypeLabel = new wxStaticText(this, wxID_ANY, _("DB Type:"), wxDefaultPosition, wxSize(label_width, -1), wxALIGN_LEFT);
		first_row_sizer->Add(databasetypeLabel, 0,  wxTOP | wxBOTTOM | wxALIGN_CENTER_VERTICAL, 0);
		first_row_sizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);

		wxComboBox* databasetypeBox = new wxComboBox(this, ID_CMB_DATABASETYPE, wxT(""), wxDefaultPosition, wxSize(290, -1), 0, 0, wxCB_READONLY);
		first_row_sizer->Add(databasetypeBox, 0, wxALL, 0);
		first_row_sizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
		for (int pos = 0; pos <= AnyDB::DBS_SQLITE; pos++)
		{
			databasetypeBox->Insert(AnyDB::DBSourceName[pos], pos);
		}

		//add new button
		wxButton *connect_btn = new wxButton(this, ID_BTN_CONNECT, _("Connect"), wxDefaultPosition, wxSize(75, 30), 0);
		first_row_sizer->Add(connect_btn, 0, wxALL, 0);
		first_row_sizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
	}
	inputSizer->Add(first_row_sizer, 0, wxEXPAND, 0);
	inputSizer->AddSpacer(PX_SIZER_TO_SIZER_VECTICAL);

	wxBoxSizer* second_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	{
		wxStaticText *server_label = new wxStaticText(this, wxID_ANY, _("DB Server:"), wxDefaultPosition, wxSize(label_width, -1), wxALIGN_LEFT);
		second_row_sizer->Add(server_label, 0, wxTOP | wxBOTTOM | wxALIGN_TOP, 0);
		second_row_sizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);

		wxTextCtrl* datasourceCtrl = new wxTextCtrl(this, ID_TXT_DATASOURCE, wxT(""), wxDefaultPosition, wxSize(290, -1), 0);
		second_row_sizer->Add(datasourceCtrl, 0, wxALL, 0);
		second_row_sizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);

		wxButton *create_btn = new wxButton(this, ID_BTN_CREATE, _(wxT("Create")), wxDefaultPosition, wxSize(PX_NORMAL_BTN_WIDTH, PX_NORMAL_BTN_HEIGHT), 0);
		create_btn->Enable(false);
		second_row_sizer->Add(create_btn, 0, wxALL, 0);
		second_row_sizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
	}
	inputSizer->Add(second_row_sizer, 0, wxEXPAND, 0);
	inputSizer->AddSpacer(PX_SIZER_TO_SIZER_VECTICAL);

	wxBoxSizer* third_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	{
		wxStaticText* usernameLabel = new wxStaticText(this, wxID_ANY, _(wxT("User:")), wxDefaultPosition, wxSize(label_width, -1), wxALIGN_LEFT);
		third_row_sizer->Add(usernameLabel, 0, wxTOP | wxBOTTOM | wxALIGN_TOP, 0);
		third_row_sizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);

		wxTextCtrl* usernameCtrl = new wxTextCtrl(this, ID_TXT_USERNAME, wxT(""), wxDefaultPosition, wxSize(290, -1), 0);
		third_row_sizer->Add(usernameCtrl, 0, wxALL, 0);
		third_row_sizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);

		wxButton *delete_btn = new wxButton(this, ID_BTN_DELETE, _(wxT("Delete")), wxDefaultPosition, wxSize(75, 30), 0);
		delete_btn->Enable(false);
		third_row_sizer->Add(delete_btn, 0, wxALL, 0);
		third_row_sizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
	}
	inputSizer->Add(third_row_sizer, 0, wxEXPAND, 0);
	inputSizer->AddSpacer(PX_SIZER_TO_SIZER_VECTICAL);

	wxBoxSizer* fourth_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	{
		wxStaticText* passwordLabel = new wxStaticText(this, wxID_ANY, _(wxT("Password:")), wxDefaultPosition, wxSize(label_width, -1), wxALIGN_LEFT);
		fourth_row_sizer->Add(passwordLabel, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER_VERTICAL, 0);
		fourth_row_sizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);

		wxTextCtrl* passwordCtrl = new wxTextCtrl(this, ID_TXT_PASSWORD, wxT(""), wxDefaultPosition, wxSize(290, -1), wxTE_PASSWORD);
		fourth_row_sizer->Add(passwordCtrl, 0, wxALL | wxALIGN_CENTER_VERTICAL, 0);
		//fourth_row_sizer->Add(third_row_sizer, 0, wxEXPAND);
		fourth_row_sizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
	}
	inputSizer->Add(fourth_row_sizer);
	inputSizer->AddSpacer(PX_SIZER_TO_SIZER_VECTICAL);

	wxBoxSizer* five_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	{
		wxStaticText* dbdLabel = new wxStaticText(this, wxID_ANY, _("Database:"), wxDefaultPosition, wxSize(label_width, -1), wxALIGN_LEFT);
		five_row_sizer->Add(dbdLabel, 0, wxTOP | wxBOTTOM | wxALIGN_TOP, 0);
		five_row_sizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
		wxListBox *db_listbox = new wxListBox(this, ID_LIST_DB, wxDefaultPosition, wxSize(290, 140));
		five_row_sizer->Add(db_listbox, 0, wxALL, 0);
	}
	inputSizer->Add(five_row_sizer);
	inputSizer->AddSpacer(PX_SIZER_TO_SIZER_VECTICAL);

	wxBoxSizer* six_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	{
		wxButton *ok_btn = new wxButton(this, ID_BTN_OK, _(wxT("OK")), wxDefaultPosition, wxSize(75, 30), 0);
		ok_btn->Enable(false);
		wxButton* cancelButton = new wxButton(this, ID_BTN_CANCEL, _(wxT("Cancel")), wxDefaultPosition, wxSize(75, 30), 0);

		six_row_sizer->Add(ok_btn, 0, wxALL, 5);
		six_row_sizer->Add(2, 2, 0, wxGROW | wxALL, 2);
		six_row_sizer->Add(cancelButton, 0, wxALL, 5);
	}
	inputSizer->Add(six_row_sizer, 0, wxALL | wxALIGN_CENTER, 0);
	root_sizer->AddSpacer(PX_BASESIZER_TO_BOTTOM_BORDER);

	root_sizer->Fit(this);
	Center();
	this->SetBackgroundColour(wxColor(255, 255, 255));

	DoSetDBSetting();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void giDBSetupDlg::OnConnect(wxCommandEvent& event) 
{
	DBSourceDesc db_desc;
	DoGetDBSetting(db_desc);
	dynamic_cast<wxListBox*>(FindWindow(ID_LIST_DB))->Clear();
	dynamic_cast<wxButton*>(FindWindow(ID_BTN_CREATE))->Enable(false);
	dynamic_cast<wxButton*>(FindWindow(ID_BTN_DELETE))->Enable(false);
	dynamic_cast<wxButton*>(FindWindow(ID_BTN_OK))->Enable(false);
	std::vector<string> db_names;
	if (giTheApp(giDataApp).IsCanLogin(db_desc, db_names)) 
	{
		dynamic_cast<wxButton*>(FindWindow(ID_BTN_CREATE))->Enable(true);
		for (int i = 0; i < db_names.size(); i++) 
		{
			dynamic_cast<wxListBox*>(FindWindow(ID_LIST_DB))->Insert(db_names[i], i);
		}
		if (db_names.size())
		{
			dynamic_cast<wxListBox*>(FindWindow(ID_LIST_DB))->SetSelection(0);
			dynamic_cast<wxButton*>(FindWindow(ID_BTN_DELETE))->Enable(true);
			dynamic_cast<wxButton*>(FindWindow(ID_BTN_OK))->Enable(true);
		}
	}
	else 
	{
		wxMessageBox(_(wxT("Please assure connection info!")), _(wxT("GI Message")));
	}
}

// to create new db
void giDBSetupDlg::OnCreate(wxCommandEvent& event) 
{
	DBSourceDesc db_desc;
	db_desc.m_type = dynamic_cast<wxComboBox*>(FindWindow(ID_CMB_DATABASETYPE))->GetSelection();
	if (db_desc.m_type == DBS_SQLSERVER || db_desc.m_type == DBS_MYSQL)
	{
		db_desc.m_srcName = dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_DATASOURCE))->GetValue();
		db_desc.m_user = dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_USERNAME))->GetValue();
		db_desc.m_pwd = dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_PASSWORD))->GetValue();
		wxTextEntryDialog tdlg(this, _(wxT("Database Name:")), _(wxT("Please insert database name")), wxEmptyString);
		if (tdlg.ShowModal() == wxID_OK && !tdlg.GetValue().IsEmpty())
		{
			db_desc.m_dbName = tdlg.GetValue().ToStdString();
			bool isExist = CAnyAccessor::IsDatabaseExist(db_desc);
			if (isExist)
			{
				wxMessageBox(_(wxT("Database already exists!")), _(wxT("GI Message")));
				return;
			}
			CAnyAccessor::ReleaseDB();
			CAnyAccessor::CreateDatabase(db_desc);
			CAnyAccessor::InitSQLDBFileDataOnly(db_desc);
		}
		else
			return;
	}
	else if (db_desc.m_type == DBS_MDB || db_desc.m_type == DBS_SQLITE)
	{
		wxFileDialog dialog(this, _(wxT("Create file dialog")), wxEmptyString, "", wxT("MDB files (*.mdb)|*.mdb|DB files (*.db)|*.db"), wxFD_OPEN);
		if (db_desc.m_type == DBS_MDB)
			dialog.SetFilterIndex(0);
		else if (db_desc.m_type == DBS_SQLITE)
			dialog.SetFilterIndex(1);
		if (dialog.ShowModal() == wxID_OK)
		{
			db_desc.m_dbName = dialog.GetPath().ToStdString();
			if (!wxFile::Exists(db_desc.m_dbName.c_str()))
			{
				CAnyAccessor::ReleaseDB();
				CAnyAccessor::InitDB(db_desc);
				CAnyAccessor::InitDBFileDataOnly(db_desc);
			}
		}
		else
			return;
	}
	wxListBox *list_box = dynamic_cast<wxListBox*>(FindWindow(ID_LIST_DB));
	bool find = false;
	for (int i = 0; i < list_box->GetCount(); i++)
	{
		if (list_box->GetString(i).ToStdString() == db_desc.m_dbName)
		{
			find = true;
			list_box->SetSelection(i);
			break;
		}
	}
	if (!find)
	{
		list_box->Append(db_desc.m_dbName);
		list_box->SetSelection(list_box->GetCount() - 1);
		DBSourceDesc db_desc_backup;
		giTheApp(giDataApp).ReadDBConfig(db_desc_backup);
		giTheApp(giDataApp).WriteDBConfig(db_desc);
		giTheApp(giDataApp).WriteDBConfig(db_desc_backup);
	}
	if (list_box->GetCount() && list_box->GetSelection() >= 0)
	{
		dynamic_cast<wxButton*>(FindWindow(ID_BTN_DELETE))->Enable(true);
		dynamic_cast<wxButton*>(FindWindow(ID_BTN_OK))->Enable(true);
	}
	// init reference
	CAnyAccessor::InitDB(db_desc);
	{
		//CAnyAccessor accessor;
		//CAssessmentUserManager::UserRecord userrecord;
		//userrecord.userid = 1;
		//userrecord.username = (db_desc.m_type == DBS_MDB || db_desc.m_type == DBS_SQLITE) ? "admin" : db_desc.m_user;
		//userrecord.m_oilfiledid = 1;
		//CAssessmentUserManager::commitUser(accessor, userrecord);
	}
	//CAccumulationAssessor::InitActivityRecords(0);
	CAnyAccessor::ReleaseDB();
}

// only admin role & there are not any users are using current db
void giDBSetupDlg::OnDelete(wxCommandEvent& event) 
{	
	DBSourceDesc db_desc;
	DoGetDBSetting(db_desc);
	if (db_desc.m_dbName == "")
		return;
	wxMessageDialog dialog(this, _(wxT("Are you sure to drop " + wxString(db_desc.m_dbName) + "?")), _(wxT("GI Message")), wxCENTER | wxNO_DEFAULT | wxYES_NO | wxICON_QUESTION);
	if (dialog.ShowModal() == wxID_YES)
	{
		if (db_desc.m_type == DBS_SQLSERVER || db_desc.m_type == DBS_MYSQL)
		{
			bool rt = CAnyAccessor::DeleteDatabase(db_desc);
			if (!rt)
			{
				wxMessageBox(_(wxT("Database is in use!")), _(wxT("GI Message")));
				return;
			}
		}
		else
		{
			if(wxFile::Exists(db_desc.m_dbName))
			{
				wxRemoveFile(db_desc.m_dbName);
			}
		}
		wxListBox *list_box = dynamic_cast<wxListBox*>(FindWindow(ID_LIST_DB));
		for (int i = 0; i < list_box->GetCount(); i++)
		{
			if (list_box->GetString(i).ToStdString() == db_desc.m_dbName)
			{
				list_box->Delete(i);
				if(list_box->GetCount())
					list_box->SetSelection(i > 0 ? i - 1 : 0);
				if (!list_box->GetCount() || list_box->GetSelection() < 0)
				{
					dynamic_cast<wxButton*>(FindWindow(ID_BTN_DELETE))->Enable(false);
					dynamic_cast<wxButton*>(FindWindow(ID_BTN_OK))->Enable(false);
				}
				giTheApp(giDataApp).RemoveRecentDB(db_desc);
				break;
			}
		}
	}
}

// select existing db
void giDBSetupDlg::OnOK(wxCommandEvent& event) 
{
	DBSourceDesc db_desc;
	DoGetDBSetting(db_desc);
	if(db_desc.m_dbName == "")
		return wxDialog::EndModal(wxID_CANCEL);
	if (giTheApp(giDataApp).IsCanLogin(db_desc)) 
	{
		if (giTheApp(giDataApp).IsLogining(db_desc)) 
		{
			wxMessageBox(_(wxT("The same user is logining!")), _(wxT("GI Message")));
			//wxDialog::EndModal(wxID_CANCEL);
		}
		else 
		{
			giTheApp(giDataApp).WriteDBConfig(db_desc);
			wxDialog::EndModal(wxID_OK);
		}
	}
	else
	{
		wxMessageBox(_(wxT("Please assure connection inputs!")), _(wxT("GI Message")));
		//wxDialog::EndModal(wxID_CANCEL);
	}
}

// do nothing
void giDBSetupDlg::OnCancel(wxCommandEvent& event) 
{
	wxDialog::EndModal(wxID_CANCEL);
}
void giDBSetupDlg::OnChangeDatabaseType(wxCommandEvent& event) 
{
	if (dynamic_cast<wxComboBox*>(FindWindow(ID_CMB_DATABASETYPE))->GetSelection() == DBS_SQLSERVER || dynamic_cast<wxComboBox*>(FindWindow(ID_CMB_DATABASETYPE))->GetSelection() == DBS_MYSQL)
	{
		dynamic_cast<wxButton*>(FindWindow(ID_BTN_CONNECT))->Enable(true);
		dynamic_cast<wxButton*>(FindWindow(ID_BTN_CREATE))->Enable(false);
		dynamic_cast<wxButton*>(FindWindow(ID_BTN_DELETE))->Enable(false);
		dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_DATASOURCE))->Enable(true);
		dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_USERNAME))->Enable(true);
		dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_PASSWORD))->Enable(true);
		dynamic_cast<wxListBox*>(FindWindow(ID_LIST_DB))->Clear();
		dynamic_cast<wxButton*>(FindWindow(ID_BTN_OK))->Enable(false);
	}
	else if (dynamic_cast<wxComboBox*>(FindWindow(ID_CMB_DATABASETYPE))->GetSelection() == DBS_MDB || dynamic_cast<wxComboBox*>(FindWindow(ID_CMB_DATABASETYPE))->GetSelection() == DBS_SQLITE)
	{
		dynamic_cast<wxButton*>(FindWindow(ID_BTN_CONNECT))->Enable(false);
		dynamic_cast<wxButton*>(FindWindow(ID_BTN_CREATE))->Enable(true);
		dynamic_cast<wxButton*>(FindWindow(ID_BTN_DELETE))->Enable(false);
		dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_DATASOURCE))->Enable(false);
		dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_USERNAME))->Enable(false);
		dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_PASSWORD))->Enable(false);
		dynamic_cast<wxListBox*>(FindWindow(ID_LIST_DB))->Clear();
		dynamic_cast<wxButton*>(FindWindow(ID_BTN_OK))->Enable(false);
		DBSourceDesc db_desc;
		std::vector<DBSourceDesc> recent_dbs;
		giTheApp(giDataApp).ReadDBConfig(db_desc, recent_dbs);
		wxListBox *list_box = dynamic_cast<wxListBox*>(FindWindow(ID_LIST_DB));
		for (int i = 0; i < recent_dbs.size(); i++)
		{
			if (recent_dbs[i].m_type == dynamic_cast<wxComboBox*>(FindWindow(ID_CMB_DATABASETYPE))->GetSelection())
			{
				list_box->Append(recent_dbs[i].m_dbName);
			}
		}
		if (list_box->GetCount())
		{
			list_box->SetSelection(0);
			dynamic_cast<wxButton*>(FindWindow(ID_BTN_DELETE))->Enable(true);
			dynamic_cast<wxButton*>(FindWindow(ID_BTN_OK))->Enable(true);
		}
	}
}
void giDBSetupDlg::DoGetDBSetting(DBSourceDesc &db_desc) {
	wxListBox *list_box = dynamic_cast<wxListBox*>(FindWindow(ID_LIST_DB));
	db_desc.m_type = dynamic_cast<wxComboBox*>(FindWindow(ID_CMB_DATABASETYPE))->GetSelection();
	if (db_desc.m_type == DBS_SQLSERVER || db_desc.m_type == DBS_MYSQL)
	{
		db_desc.m_srcName = dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_DATASOURCE))->GetValue();
		if (list_box->GetCount() && list_box->GetSelection() >= 0)
			db_desc.m_dbName = list_box->GetString(list_box->GetSelection());
		else
			db_desc.m_dbName = "";
		db_desc.m_user = dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_USERNAME))->GetValue();
		db_desc.m_pwd = dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_PASSWORD))->GetValue();
	}
	else if (db_desc.m_type == DBS_MDB || db_desc.m_type == DBS_SQLITE)
	{
		db_desc.m_srcName = "";
		if (list_box->GetCount() && list_box->GetSelection() >= 0)
			db_desc.m_dbName = list_box->GetString(list_box->GetSelection());
		else
			db_desc.m_dbName = "";
		db_desc.m_user = "";
		db_desc.m_pwd = "";
	}
}
void giDBSetupDlg::DoSetDBSetting() 
{
	DBSourceDesc db_desc;
	giTheApp(giDataApp).ReadDBConfig(db_desc);
	dynamic_cast<wxComboBox*>(FindWindow(ID_CMB_DATABASETYPE))->SetSelection(db_desc.m_type);
	dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_DATASOURCE))->SetValue(db_desc.m_srcName);
	dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_USERNAME))->SetValue(db_desc.m_user);
	dynamic_cast<wxTextCtrl*>(FindWindow(ID_TXT_PASSWORD))->SetValue(db_desc.m_pwd);
	dynamic_cast<wxListBox*>(FindWindow(ID_LIST_DB))->Clear();
	wxCommandEvent event;
	OnChangeDatabaseType(event);
}
