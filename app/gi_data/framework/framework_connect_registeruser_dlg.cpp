
#include "framework_connect_registeruser_dlg.h"
#include "framework_data_app.h"
#include "framework_data_macroes.h"

#include "wx/wx.h"
#include "wx/numdlg.h"

#include "any/db/anyaccessor.h"
#include "any/db/anyadobasic.h"
using namespace AnyDB;

//#include "any/petro/assessmentusermanager.h"
//using namespace AnyPetro;

#include <mysql.h>
#pragma comment(lib, "libmysql.lib")

IMPLEMENT_CLASS(RegisterUserDlg, wxDialog)
	BEGIN_EVENT_TABLE(RegisterUserDlg, wxDialog)
	EVT_BUTTON(ID_REGISTERBUTTON, RegisterUserDlg::OnRegister)
END_EVENT_TABLE()

//
RegisterUserDlg::RegisterUserDlg(wxWindow *parent, wxArrayString choices, wxString datasource, wxString username, wxString password, wxString dbname): 
condatasource(datasource), conusername(username), conpassword(password), condbname(dbname), m_withOrg(false), wxDialog(parent, wxID_ANY, wxString(_(wxT("User Register"))))
{
	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(boxSizer);
	boxSizer->AddSpacer(PX_BASESIZER_TO_UPPER_BORDER);
	wxStaticText* usernameLabel = new wxStaticText(this, wxID_STATIC, _(wxT("Username:")), wxDefaultPosition, wxSize(160, -1), 0);
	boxSizer->Add(usernameLabel, 0, wxLEFT|wxRIGHT, 0);
	boxSizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);
	wxTextCtrl* usernameCtrl = new wxTextCtrl(this, ID_USERNAMEREG, wxT(""), wxDefaultPosition, wxSize(160, -1), 0);
	boxSizer->Add(usernameCtrl, 0, wxLEFT|wxRIGHT, 0);
	boxSizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);
	wxStaticText* passwordLabel1 = new wxStaticText(this, wxID_STATIC, _(wxT("Password:")), wxDefaultPosition, wxSize(160, -1), 0);
	boxSizer->Add(passwordLabel1, 0, wxLEFT|wxRIGHT, 0);
	boxSizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);
	wxTextCtrl* passwordCtrl1 = new wxTextCtrl(this, ID_PASSWORD1, wxT(""), wxDefaultPosition, wxSize(160, -1), wxTE_PASSWORD);
	boxSizer->Add(passwordCtrl1, 0, wxLEFT|wxRIGHT, 0);
	boxSizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);
	wxStaticText* passwordLabel2 = new wxStaticText(this, wxID_STATIC, _(wxT("Confirm Password:")), wxDefaultPosition, wxSize(160, -1), 0);
	boxSizer->Add(passwordLabel2, 0, wxLEFT|wxRIGHT, 0);
	boxSizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);
	wxTextCtrl* passwordCtrl2 = new wxTextCtrl(this, ID_PASSWORD2, wxT(""), wxDefaultPosition, wxSize(160, -1), wxTE_PASSWORD);
	boxSizer->Add(passwordCtrl2, 0, wxLEFT|wxRIGHT, 0);
	boxSizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);
	{
		wxStaticText* databaselistLabel = new wxStaticText(this, wxID_STATIC, _(wxT("Select Database:")), wxDefaultPosition, wxSize(160, -1), 0);
		boxSizer->Add(databaselistLabel, 0, wxLEFT|wxRIGHT, 0);
		boxSizer->AddSpacer(PX_CTRL_TO_CTRL_VECTICAL);
		databaselist = new wxCheckListBox(this, ID_CHECKLISTBOX, wxDefaultPosition, wxSize(160, 100), 0, 0, wxLB_NEEDED_SB|wxLB_HSCROLL);
		databaselist->InsertItems(choices, 0);
		boxSizer->Add(databaselist, 0, wxLEFT|wxRIGHT, 0);
		boxSizer->AddSpacer(15);
	}
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* Register = new wxButton(this, ID_REGISTERBUTTON, _(wxT("Register")), wxDefaultPosition, wxSize(PX_NORMAL_BTN_WIDTH, PX_NORMAL_BTN_HEIGHT), 0 );
	buttonSizer->Add(Register, 0, wxRIGHT, 0);
	buttonSizer->AddSpacer(PX_CTRL_TO_CTRL_HORIZONTAL);
	wxButton* cancel = new wxButton(this, wxID_CANCEL, _(wxT("Cancel")), wxDefaultPosition, wxSize(PX_NORMAL_BTN_WIDTH, PX_NORMAL_BTN_HEIGHT), 0 );
	buttonSizer->Add(cancel, 0, wxRIGHT, 0);
	boxSizer->Add(buttonSizer, 0, wxRIGHT, 0);
	boxSizer->AddSpacer(PX_BASESIZER_TO_BOTTOM_BORDER);
	boxSizer->Fit(this);
	Center();
}
void RegisterUserDlg::OnRegister(wxCommandEvent& event)
{
	DBSourceDesc db_desc;
	giTheApp(giDataApp).ReadDBConfig(db_desc);
	string regusername = dynamic_cast<wxTextCtrl *>(FindWindow(ID_USERNAMEREG))->GetValue().ToStdString();
	string regpassword1 = dynamic_cast<wxTextCtrl *>(FindWindow(ID_PASSWORD1))->GetValue().ToStdString();
	string regpassword2 = dynamic_cast<wxTextCtrl *>(FindWindow(ID_PASSWORD2))->GetValue().ToStdString();
	if(regusername.length() == 0)
	{
		wxMessageBox(_(wxT("please set username!")), _("Info"));
		return;
	}
	if(regpassword1.compare(regpassword2) != 0)
	{
		wxMessageBox(_(wxT("password not match!")), _("Info"));
		return;
	}
	{
		DBSourceDesc srcDesc;
		if(db_desc.m_type == DBS_SQLSERVER)
			srcDesc.m_type = DBS_SQLSERVER;
		else
			srcDesc.m_type = DBS_MYSQL;
		srcDesc.m_srcName = condatasource.c_str();
		srcDesc.m_user = conusername.c_str();
		srcDesc.m_pwd = conpassword.c_str();
		_ConnectionPtr m_pConnection;
		std::vector<string> loginnames;
		if(db_desc.m_type == DBS_SQLSERVER)
		{
			for(int i=0;i<6;i++)
			{
				try
				{	
					HRESULT hr;
					hr = m_pConnection.CreateInstance("ADODB.Connection");
					string connectionstr = "Provider=SQLOLEDB;Data Source=" + condatasource.ToStdString() + ";";
					if(SUCCEEDED(hr))
					{
						m_pConnection->PutConnectionTimeout(5);
						hr = m_pConnection->Open(connectionstr.c_str(), srcDesc.m_user.c_str(), srcDesc.m_pwd.c_str(), -1);
						if(SUCCEEDED(hr))
						{
							_variant_t vNULL;
							vNULL.vt = VT_ERROR;
							vNULL.scode = DISP_E_PARAMNOTFOUND;
							string sql = "EXEC sp_helplogins";
							_RecordsetPtr m_pRecordset = m_pConnection->Execute((_bstr_t)sql.c_str(), &vNULL, adCmdText);
							while(!m_pRecordset->adoEOF)
							{
								string loginname = (std::string)(_bstr_t)m_pRecordset->GetFields()->GetItem((long)0)->Value; 
								loginnames.push_back(loginname);
								m_pRecordset->MoveNext(); 
							}
							m_pConnection->Close();																						
						}
					}
					break;
				}
				catch(_com_error e)
				{
					if(i==5)
					{
						wxMessageBox((std::string)e.Description());
					}
					m_pConnection->Close();
				}
			}
		}
		else
		{
			MYSQL* pConnection = new MYSQL;
			mysql_init(pConnection);
			if(mysql_real_connect(pConnection, srcDesc.m_srcName.c_str(), srcDesc.m_user.c_str(), srcDesc.m_pwd.c_str(), srcDesc.m_dbName.c_str(), 3306, NULL, 0))
			{
				string sql = "use mysql";
				if(!mysql_real_query(pConnection, sql.c_str(), strlen(sql.c_str())))
				{
					sql = "select user from user";
					if(!mysql_real_query(pConnection, sql.c_str(), strlen(sql.c_str())))
					{
						MYSQL_RES* recordset = mysql_store_result(pConnection);
						MYSQL_ROW row;
						while(row = mysql_fetch_row(recordset))
						{
							loginnames.push_back(row[0]);
						}
						mysql_free_result(recordset);
					}
				}
				mysql_close(pConnection);
			}
		}
		bool isLoginNameExist=false;
		for(int i = 0; i < loginnames.size(); i++)
		{
			if(loginnames[i] == regusername)
			{
				if(m_withOrg)
				{
					isLoginNameExist=true;
				}
				else
				{
					wxMessageBox(_(wxT("Name already exist!")), _(wxT("Info")));
					CAnyAccessor::ReleaseDB(srcDesc);
					return;
				}
			
			}
		}
		/*
		登录名针对整个服务器，用户针对数据库；
		先创建登录名，然后设置登录名的权限；
		然后为每个数据库创建用户(一般与登录名同名)，再设置用户的权限
		*/
		if(!isLoginNameExist)
		{
			if(db_desc.m_type == DBS_SQLSERVER)
			{
				{
					CAnyAccessor accessor;
					string cmd = "USE [master];";
					cmd = cmd + "CREATE LOGIN [" + regusername + "] WITH PASSWORD=N'" + regpassword1 + "', DEFAULT_DATABASE = [master], CHECK_EXPIRATION=OFF, CHECK_POLICY=OFF";
					accessor.Execute(cmd);
				}
				//only one admin 
				if(false && dynamic_cast<wxCheckBox *>(FindWindow(ID_ISADMIN))->IsChecked())
				{
					CAnyAccessor accessor;
					string cmd = "EXEC sp_addsrvrolemember N'" + regusername + "',N'sysadmin'";
					accessor.Execute(cmd);
				}
				else
				{
					CAnyAccessor accessor(false);
					string cmd = "EXEC sp_addsrvrolemember '" + regusername + "','dbcreator'";
					accessor.Execute(cmd);
					cmd = "EXEC sp_addsrvrolemember '" + regusername + "','processadmin'";
					accessor.Execute(cmd);
				}
			}
			else
			{
				CAnyAccessor accessor(false);
				string cmd = "create user " + regusername + " identified by '" + regpassword1 + "'";
				accessor.Execute(cmd);
				cmd = "grant all privileges on master.* to " + regusername;
				accessor.Execute(cmd);
				cmd = "grant all privileges on mysql.* to " + regusername;
				accessor.Execute(cmd);
			}
		}
		else
		{
			wxMessageBox(_(wxT("User already exists. Following operation will add user to database!")), _(wxT("Info")));
		}
		bool hasdatabase = false;
		for(int i = 0; i < dynamic_cast<wxCheckListBox *>(FindWindow(ID_CHECKLISTBOX))->GetCount(); i++)
		{
			if(dynamic_cast<wxCheckListBox *>(FindWindow(ID_CHECKLISTBOX))->IsChecked(i))
			{
				string databaseName=dynamic_cast<wxCheckListBox *>(FindWindow(ID_CHECKLISTBOX))->GetString(i).ToStdString();
				CAnyAccessor accessor;
				//get current database's user. check whether user is already in.
				bool userexist = false;
				char sentenceun[1024] = "select name from ref_sys_user";
				bool rt = accessor.Execute(sentenceun);
				string val="";
				if(accessor.MoveFirst())
				{
					do 
					{
						accessor.FetchField(0L,val);
						if(val==regusername)
						{
							//wxMessageBox(_(wxT("Name already exist!")), _(wxT("Info")));
							userexist = true;
							break;
						}
					} while (accessor.MoveNext());
				}
				string cmd = "USE [" + dynamic_cast<wxCheckListBox *>(FindWindow(ID_CHECKLISTBOX))->GetString(i).ToStdString() + "];";
				if (!userexist)
				{
					if (db_desc.m_type == DBS_SQLSERVER)
					{
						cmd = cmd + "CREATE USER [" + regusername + "] FOR LOGIN [" + regusername + "]";
						accessor.Execute(cmd);
						cmd = "EXEC sp_addrolemember N'db_owner', N'" + regusername + "'";
						accessor.Execute(cmd);
					}
					else
					{
						cmd = "grant all privileges on " + databaseName + ".* to " + regusername;
						accessor.Execute(cmd);
					}
				}
				//CAssessmentUserManager::UserRecord userrecord;
				//userrecord.username = regusername;
				if (m_withOrg)
				{
					//userrecord.m_oilfiledid = m_fieldid;
				}
				else
				{
					cmd = "select fieldid,fieldname from ref_oilfields";
					accessor.Execute(cmd);
					{
						wxArrayString choices;
						wxArrayInt selections;
						wxArrayInt fieldid;
						for(int j = 0; j < accessor.GetRecordCount(); j++)
						{
							string temp = ""; 
							accessor.FetchField((long)1, temp);
							choices.Add(_(temp.c_str()));
							accessor.FetchField((long)0, temp);
							fieldid.Add(::atoi(temp.c_str()));
							accessor.MoveNext();
						}
						wxSingleChoiceDialog Choicedlg(this, _(wxT("Choose Oil Field：")) + dynamic_cast<wxCheckListBox *>(FindWindow(ID_CHECKLISTBOX))->GetString(i), _(wxT("Choose Oil Field：")), choices);
						if(Choicedlg.ShowModal() == wxID_OK)
						{
							//userrecord.m_oilfiledid = fieldid[Choicedlg.GetSelection()];
						}
						else
						{
							if(db_desc.m_type == DBS_SQLSERVER)
							{
								cmd = "EXEC sp_droprolemember N'db_owner', N'" + regusername + "'";
								accessor.Execute(cmd);
								cmd = "DROP USER [" + regusername + "]";
								accessor.Execute(cmd);
							}
							else
							{
								cmd = "revoke all privileges on " + condbname + ".* from " + regusername;
								accessor.Execute(cmd);
							}
							continue;
						}
					}
				}
				{
					string cmd = "select * from r_activity";
					bool rt = accessor.Execute(cmd);
					if(rt && accessor.GetRecordCount())
					{
						//for (int i = 0; i < accessor.GetRecordCount(); i++)
							//userrecord.authorities.push_back(true);
					}
					for(int i = 0; i < accessor.GetTableCount(); i++)
					{
						//userrecord.readvalidtables.push_back(true);
						//userrecord.writevalidtables.push_back(true);
					}
				}
				//if (!userexist)
					//CAssessmentUserManager::addUser(userrecord);
				//CAssessmentUserManager::commitUser(accessor, userrecord);
				//CAccumulationAssessor::InitActivityTemplate(accessor, regusername, 0);
				hasdatabase = true;
			}
		}
		if(!hasdatabase)
		{
			CAnyAccessor accessor;
			if(db_desc.m_type == DBS_SQLSERVER)
			{
				string cmd = "EXEC sp_dropsrvrolemember N'" + regusername + "',N'sysadmin'";
				accessor.Execute(cmd);
				cmd = "DROP LOGIN [" + regusername + "]";
				accessor.Execute(cmd);
			}
			else
			{
				string cmd = "drop user " + regusername;
				accessor.Execute(cmd);
				cmd = "use mysql";
				accessor.Execute(cmd);
				cmd = "delete from user where user='"+ regusername + "'";
				accessor.Execute(cmd);
			}
		}
		{
			//CAnyAccessor accessor;
			//CAssessmentUserManager::loadUser(accessor);
		}
		if(hasdatabase)
			wxMessageBox(_(wxT("Register Complete!")), _("Info"));
		Destroy();
	}
}
void RegisterUserDlg::SetWithOrg(bool withOrg, int fieldid, std::string& dbname)
{
	m_withOrg = withOrg;
	databaselist->Check(0, true);
	databaselist->Enable(false);
	m_fieldid = fieldid;
}