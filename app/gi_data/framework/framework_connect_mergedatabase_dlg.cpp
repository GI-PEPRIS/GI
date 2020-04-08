#include "framework_connect_mergedatabase_dlg.h"

#include "framework_data_frame.h"
#include "framework_data_app.h"
#include "framework_data_macroes.h"

#include "wx/wx.h"
#include "wx/valtext.h"
#include "wx/valgen.h"
#include "wx/combobox.h"

#include <fstream>

IMPLEMENT_CLASS(SelectMergeDataBaseDlg, wxDialog)
	BEGIN_EVENT_TABLE(SelectMergeDataBaseDlg, wxDialog)
	EVT_BUTTON(ID_SRCBTN, SelectMergeDataBaseDlg::OnSelectSrcDatabases)
	EVT_BUTTON(ID_DESBTN, SelectMergeDataBaseDlg::OnSelectDesDatabase)
	EVT_CHOICE(ID_SRCTYPE, SelectMergeDataBaseDlg::OnSrcTypeChange)
	EVT_CHOICE(ID_DESTYPE, SelectMergeDataBaseDlg::OnDesTypeChange)
	EVT_CHECKBOX(ID_UpdateSameelement, SelectMergeDataBaseDlg::OnCheckBox)
END_EVENT_TABLE()

SelectMergeDataBaseDlg::SelectMergeDataBaseDlg(wxWindow *parent): wxDialog(parent, wxID_ANY, wxString(_(wxT("Select Database"))), \
	wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxMINIMIZE_BOX | wxMAXIMIZE_BOX)
{
	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	boxSizer->AddSpacer(PX_BASESIZER_TO_UPPER_BORDER);
	this->SetSizer(boxSizer);
	{
		wxBoxSizer* srcSizer = new wxBoxSizer(wxHORIZONTAL);
		boxSizer->Add(srcSizer);
		srcSizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
		wxStaticText* datasourceLabel = new wxStaticText(this, wxID_ANY, _(wxT("Source:")), wxDefaultPosition, wxSize(PX_LABEL_WIDTH, -1), 0);
		srcSizer->Add(datasourceLabel, 0, wxALL|wxALIGN_CENTER, 0);
		srcSizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
		wxChoice* datasourcetype = new wxChoice(this, ID_SRCTYPE, wxDefaultPosition, wxSize(120, -1));
		for (int pos = 0; pos <= AnyDB::DBS_SQLITE; pos++)
			datasourcetype->Append(AnyDB::DBSourceName[pos]);
		datasourcetype->SetSelection(-1);
		srcSizer->Add(datasourcetype, 0, wxALL|wxALIGN_CENTER, 0);
		srcSizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
		wxButton* datasourcebtn = new wxButton(this, ID_SRCBTN, _(wxT("...")), wxDefaultPosition, wxSize(PX_NORMAL_BTN_WIDTH, PX_NORMAL_BTN_HEIGHT), 0 );
		datasourcebtn->Enable(false);
		srcSizer->Add(datasourcebtn, 0, wxALL|wxALIGN_CENTER, 0);
		srcSizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
	}
	boxSizer->AddSpacer(PX_SIZER_TO_SIZER_VECTICAL);
	wxListBox* datasourcelist = new wxListBox(this, ID_SRCPATHS, wxDefaultPosition, wxSize(280,250), 0, 0, wxLB_NEEDED_SB|wxLB_HSCROLL|wxLB_EXTENDED);
	datasourcelist->Enable(false);
	boxSizer->Add(datasourcelist, 0, wxALL|wxALIGN_CENTER, 0);
	boxSizer->AddSpacer(PX_SIZER_TO_SIZER_VECTICAL);
	{
		wxBoxSizer* desSizer = new wxBoxSizer(wxHORIZONTAL);
		boxSizer->Add(desSizer);
		desSizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
		wxStaticText* targetdatabaseLabel = new wxStaticText(this, wxID_STATIC, _(wxT("Target:")), wxDefaultPosition, wxSize(PX_LABEL_WIDTH, -1), 0);
		desSizer->Add(targetdatabaseLabel, 0, wxALL|wxALIGN_CENTER, 0);
		desSizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
		wxChoice* targetdatabasetype = new wxChoice(this, ID_DESTYPE, wxDefaultPosition, wxSize(120, -1));
		for (int pos = 0; pos <= AnyDB::DBS_SQLITE; pos++)
			targetdatabasetype->Append(AnyDB::DBSourceName[pos]);
		targetdatabasetype->SetSelection(-1);
		desSizer->Add(targetdatabasetype, 0, wxALL|wxALIGN_CENTER, 0);
		desSizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
		wxButton* targetdatabasebtn = new wxButton(this, ID_DESBTN, _(wxT("...")), wxDefaultPosition, wxSize(PX_NORMAL_BTN_WIDTH, PX_NORMAL_BTN_HEIGHT), 0 );
		targetdatabasebtn->Enable(false);
		desSizer->Add(targetdatabasebtn, 0, wxALL|wxALIGN_CENTER, 0);
		desSizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
	}
	boxSizer->AddSpacer(PX_SIZER_TO_SIZER_VECTICAL);
	wxTextCtrl* targetdatabaseCtrl = new wxTextCtrl(this, ID_DESPATH, wxT(""), wxDefaultPosition, wxSize(280, -1));
	targetdatabaseCtrl->Enable(false);
	boxSizer->Add(targetdatabaseCtrl, 0, wxALL|wxALIGN_CENTER, 0);
	boxSizer->AddSpacer(PX_SIZER_TO_SIZER_VECTICAL);

	wxCheckBox *updatesamelement = new wxCheckBox(this, ID_UpdateSameelement, _(wxT("Is update same element")), wxDefaultPosition, wxDefaultSize);
	updatesamelement->SetValue(m_updatesameelement);
	boxSizer->Add(updatesamelement, 0, wxALL | wxALIGN_CENTER, 0);
	boxSizer->AddSpacer(PX_SIZER_TO_SIZER_VECTICAL);

	wxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, _("OK")), 0);
	buttonSizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, _("Cancel")), 0);
	buttonSizer->AddSpacer(PX_BASESIZER_TO_RIGHT_BORDER);
	boxSizer->Add(buttonSizer, 0, wxALIGN_RIGHT);

	boxSizer->AddSpacer(PX_BASESIZER_TO_BOTTOM_BORDER);

	boxSizer->Fit(this);
	Center();
}
void SelectMergeDataBaseDlg::OnSelectSrcDatabases( wxCommandEvent& event )
{
	if(dynamic_cast<wxChoice *>(this->FindWindow(ID_SRCTYPE))->GetSelection() == DBS_SQLSERVER || dynamic_cast<wxChoice *>(this->FindWindow(ID_SRCTYPE))->GetSelection() == DBS_MYSQL)
	{
		DBSourceDesc srcDesc;
		giTheApp(giDataApp).ReadDBConfig(srcDesc);
		if(dynamic_cast<wxChoice *>(this->FindWindow(ID_SRCTYPE))->GetSelection() != srcDesc.m_type)
		{
			wxTextEntryDialog dialog(this, _(wxT("IP")), _(wxT("IP")));
			if(dialog.ShowModal() == wxID_OK)
				srcDesc.m_srcName = dialog.GetValue();
			wxTextEntryDialog dialog1(this, _(wxT("user name")), _(wxT("user name")));
			if(dialog1.ShowModal() == wxID_OK)
				srcDesc.m_user = dialog1.GetValue();
			wxTextEntryDialog dialog2(this, _(wxT("password")), _(wxT("password")));
			if(dialog2.ShowModal() == wxID_OK)
				srcDesc.m_pwd = dialog2.GetValue();
			srcDesc.m_type = dynamic_cast<wxChoice *>(this->FindWindow(ID_SRCTYPE))->GetSelection();
		}
		wxArrayString choices;
		std::vector<string> db_names;
		if (giTheApp(giDataApp).IsCanLogin(srcDesc, db_names))
		{
			for (int i = 0; i < db_names.size(); i++)
			{
				choices.push_back(db_names[i]);
			}
		}
		wxMultiChoiceDialog Choicedlg(this, _(wxT("Select Database")), _(wxT("Select Database")), choices);
		if(Choicedlg.ShowModal() == wxID_OK)
		{
			for(int i = 0; i < Choicedlg.GetSelections().Count(); i++)
			{
				if(choices[Choicedlg.GetSelections()[i]].ToStdString() == m_targetdatabase.m_dbName && srcDesc.m_type == m_targetdatabase.m_type)
				{
					wxMessageBox(_(wxT("Source database and target database can not be same!")),_(wxT("Info")));
					return;
				}
			}
			dynamic_cast<wxListBox *>(this->FindWindow(ID_SRCPATHS))->Clear();
			m_srcdatabases.clear();
			for(int i = 0; i < Choicedlg.GetSelections().Count(); i++)
			{
				DBSourceDesc srcdatabase = srcDesc;
				srcdatabase.m_dbName = choices[Choicedlg.GetSelections()[i]].ToStdString();
				m_srcdatabases.push_back(srcdatabase);
				dynamic_cast<wxListBox *>(this->FindWindow(ID_SRCPATHS))->Append(wxString(srcdatabase.m_dbName));
			}
		}
	}
	else if (dynamic_cast<wxChoice *>(this->FindWindow(ID_SRCTYPE))->GetSelection() == DBS_MDB || dynamic_cast<wxChoice *>(this->FindWindow(ID_SRCTYPE))->GetSelection() == DBS_SQLITE)
	{
		wxFileDialog dlg(this, _(wxT("Select Database")), wxEmptyString, wxEmptyString, wxT("MDB files (*.mdb)|*.mdb|DB files (*.db)|*.db"), wxFD_OPEN | wxFD_MULTIPLE);
		if (dynamic_cast<wxChoice *>(this->FindWindow(ID_SRCTYPE))->GetSelection() == DBS_MDB)
			dlg.SetFilterIndex(0);
		else if (dynamic_cast<wxChoice *>(this->FindWindow(ID_SRCTYPE))->GetSelection() == DBS_SQLITE)
			dlg.SetFilterIndex(1);
		if (dlg.ShowModal() == wxID_OK)
		{
			wxArrayString srcpaths;
			dlg.GetPaths(srcpaths);
			for(int i = 0; i < srcpaths.GetCount(); i++)
			{
				if (!srcpaths[i].EndsWith(wxT(".mdb")) && !srcpaths[i].EndsWith(wxT(".db")))
				{
					wxMessageBox(_(wxT("Please select a legal file type!")),_(wxT("Info")));
					return;
				}
				wxFile *file= new wxFile;
				if (!file->Exists(srcpaths[i]))
				{
					wxMessageBox(_(wxT("File not exists, please select a legal file!")),_(wxT("Info")));
					if (file)
						delete file;
					return;
				}
				if (srcpaths[i] == m_targetdatabase.m_dbName && m_targetdatabase.m_type == dynamic_cast<wxChoice *>(this->FindWindow(ID_SRCTYPE))->GetSelection())
				{
					wxMessageBox(_(wxT("Source database and target database can not be same!")),_(wxT("Info")));
					if (file)
						delete file;
					return;
				}
				if (file)
					delete file;
			}
			dynamic_cast<wxListBox *>(this->FindWindow(ID_SRCPATHS))->Clear();
			m_srcdatabases.clear();
			for(int i = 0; i < srcpaths.GetCount(); i++)
			{
				DBSourceDesc srcDesc;
				srcDesc.m_type = dynamic_cast<wxChoice *>(this->FindWindow(ID_SRCTYPE))->GetSelection();
				srcDesc.m_dbName = srcpaths[i].ToStdString();
				m_srcdatabases.push_back(srcDesc);
				dynamic_cast<wxListBox *>(this->FindWindow(ID_SRCPATHS))->Append(srcpaths[i]);
			}
		}
	}
}
void SelectMergeDataBaseDlg::OnSelectDesDatabase( wxCommandEvent& event )
{
	if(dynamic_cast<wxChoice *>(this->FindWindow(ID_DESTYPE))->GetSelection() == DBS_SQLSERVER || dynamic_cast<wxChoice *>(this->FindWindow(ID_DESTYPE))->GetSelection() == DBS_MYSQL)
	{
		DBSourceDesc desDesc;
		giTheApp(giDataApp).ReadDBConfig(desDesc);
		if(dynamic_cast<wxChoice *>(this->FindWindow(ID_DESTYPE))->GetSelection() != desDesc.m_type)
		{
			wxTextEntryDialog dialog(this, _(wxT("IP")), _(wxT("IP")));
			if(dialog.ShowModal() == wxID_OK)
				desDesc.m_srcName = dialog.GetValue();
			wxTextEntryDialog dialog1(this, _(wxT("user name")), _(wxT("user name")));
			if(dialog1.ShowModal() == wxID_OK)
				desDesc.m_user = dialog1.GetValue();
			wxTextEntryDialog dialog2(this, _(wxT("password")), _(wxT("password")));
			if(dialog2.ShowModal() == wxID_OK)
				desDesc.m_pwd = dialog2.GetValue();
			desDesc.m_type = dynamic_cast<wxChoice *>(this->FindWindow(ID_DESTYPE))->GetSelection();
		}
		wxArrayString choices;
		std::vector<string> db_names;
		if (giTheApp(giDataApp).IsCanLogin(desDesc, db_names))
		{
			for (int i = 0; i < db_names.size(); i++)
			{
				choices.push_back(db_names[i]);
			}
		} 
		choices.Add("New");
		wxSingleChoiceDialog Choicedlg(this, _(wxT("Select Database")), _(wxT("Select Database")), choices);
		if(Choicedlg.ShowModal() == wxID_OK)
		{
			wxString despath = "";
			if(Choicedlg.GetSelection() == choices.size() - 1)
			{
				wxTextEntryDialog dialog(this, _(wxT("Select Database")), _(wxT("Select Database")));
				if(dialog.ShowModal() == wxID_OK)
					despath = dialog.GetValue();
				else
					return;
			}
			else
				despath = Choicedlg.GetStringSelection();
			for(int i = 0; i < m_srcdatabases.size(); i++)
			{
				if(m_srcdatabases[i].m_dbName == despath.ToStdString() && m_srcdatabases[i].m_type == desDesc.m_type)
				{
					wxMessageBox(_(wxT("Source database and target database can not be same!")),_(wxT("Info")));
					return;
				}
			}
			m_targetdatabase = desDesc;
			m_targetdatabase.m_dbName = despath.ToStdString();
			dynamic_cast<wxTextCtrl*>(this->FindWindow(ID_DESPATH))->SetValue(despath);
		}
	}
	else if (dynamic_cast<wxChoice *>(this->FindWindow(ID_DESTYPE))->GetSelection() == DBS_MDB || dynamic_cast<wxChoice *>(this->FindWindow(ID_DESTYPE))->GetSelection() == DBS_SQLITE)
	{
		wxFileDialog dlg(this, _(wxT("Select Database")), wxEmptyString, wxEmptyString, wxT("MDB files (*.mdb)|*.mdb|DB files (*.db)|*.db"), wxFD_OPEN);
		if (dynamic_cast<wxChoice *>(this->FindWindow(ID_DESTYPE))->GetSelection() == DBS_MDB)
			dlg.SetFilterIndex(0);
		else if (dynamic_cast<wxChoice *>(this->FindWindow(ID_DESTYPE))->GetSelection() == DBS_SQLITE)
			dlg.SetFilterIndex(1);
		if (dlg.ShowModal() == wxID_OK)
		{
			wxString despath = dlg.GetPath();
			if (!despath.EndsWith(wxT(".mdb")) && !despath.EndsWith(wxT(".db")))
			{
				wxMessageBox(_(wxT("Please select a legal file type!")),_(wxT("Info")));
				return;
			}
			for(int i = 0; i < m_srcdatabases.size(); i++)
			{
				if (m_srcdatabases[i].m_dbName == despath.ToStdString() && m_srcdatabases[i].m_type == dynamic_cast<wxChoice *>(this->FindWindow(ID_DESTYPE))->GetSelection())
				{
					wxMessageBox(_(wxT("Source database and target database can not be same!")),_(wxT("Info")));
					return;
				}
			}
			m_targetdatabase.m_type = dynamic_cast<wxChoice *>(this->FindWindow(ID_DESTYPE))->GetSelection();
			m_targetdatabase.m_dbName = despath.ToStdString();
			m_targetdatabase.m_srcName = "";
			m_targetdatabase.m_user = "";
			m_targetdatabase.m_pwd = "";
			dynamic_cast<wxTextCtrl *>(this->FindWindow(ID_DESPATH))->SetValue(despath);
		}
	}
}
void SelectMergeDataBaseDlg::OnSrcTypeChange( wxCommandEvent& event )
{
	dynamic_cast<wxButton *>(this->FindWindow(ID_SRCBTN))->Enable(true);
	dynamic_cast<wxListBox *>(this->FindWindow(ID_SRCPATHS))->Enable(true);
	dynamic_cast<wxListBox *>(this->FindWindow(ID_SRCPATHS))->Clear();
	m_srcdatabases.clear();
}
void SelectMergeDataBaseDlg::OnDesTypeChange( wxCommandEvent& event )
{
	dynamic_cast<wxButton *>(this->FindWindow(ID_DESBTN))->Enable(true);
	dynamic_cast<wxTextCtrl *>(this->FindWindow(ID_DESPATH))->Enable(false);
	dynamic_cast<wxTextCtrl *>(this->FindWindow(ID_DESPATH))->SetValue("");
	m_targetdatabase.m_dbName = "";
	m_targetdatabase.m_type = dynamic_cast<wxChoice *>(this->FindWindow(ID_DESTYPE))->GetSelection();
}
void SelectMergeDataBaseDlg::OnCheckBox(wxCommandEvent& event)
{
	m_updatesameelement = dynamic_cast<wxCheckBox *>(this->FindWindow(ID_UpdateSameelement))->GetValue();
}
