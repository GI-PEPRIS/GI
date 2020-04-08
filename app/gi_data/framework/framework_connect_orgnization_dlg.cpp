#include "framework_connect_orgnization_dlg.h"
#include "framework_connect_registeruser_dlg.h"
#include "framework_data_app.h"

#include "wx/artprov.h"

//#include "any/petro/assessmentusermanager.h"
//#include "any/petro/accumulationelement.h"
//using namespace AnyPetro;

#include "any/db/anyaccessor.h"
#include "any/db/anyaccessorbasic.h"
using namespace AnyDB;

IMPLEMENT_CLASS(OrgnaizationDlg, wxDialog)
BEGIN_EVENT_TABLE(OrgnaizationDlg, wxDialog)
EVT_TREE_ITEM_MENU(ID_TREE, OrgnaizationDlg::OnItemMenu)
EVT_CLOSE(OrgnaizationDlg::OnClose)
EVT_MENU(ID_ADDORG, OrgnaizationDlg::OnAddOrg)
EVT_MENU(ID_DELETEORG, OrgnaizationDlg::OnDeleteOrg)
EVT_MENU(ID_ADDUSER, OrgnaizationDlg::OnAddUser)
EVT_MENU(ID_DELETE_USER, OrgnaizationDlg::OnDeleteUser)
EVT_MENU(ID_VIEW_ALL, OrgnaizationDlg::OnSetViewall)
END_EVENT_TABLE()
OrgnaizationDlg::OrgnaizationDlg(wxWindow *parent) :wxDialog(parent, wxID_ANY, wxString(_(wxT("Orgnization Management"))), wxDefaultPosition, wxSize(400, 530))
{
	InitLayout();
	InitData();
}
void OrgnaizationDlg::InitLayout()
{
	wxSize iconSize = wxArtProvider::GetSizeHint(wxART_LIST);
	if (iconSize == wxDefaultSize)
		iconSize = wxSize(16, 16);
	wxImageList *imageList = new wxImageList(iconSize.x, iconSize.y);
	static const char* const icons[] =
	{
		wxART_NORMAL_FILE,
		wxART_FOLDER,
		wxART_FOLDER_OPEN
	};
	for (unsigned n = 0; n < WXSIZEOF(icons); n++)
	{
		imageList->Add(wxArtProvider::GetIcon(icons[n], wxART_LIST, iconSize));
	}
	wxTreeCtrl* tree = new wxTreeCtrl(this, ID_TREE, wxDefaultPosition, wxSize(150, 450));
	tree->SetImageList(imageList);
	tree->AddRoot(_("Orgnization"), Icon_FolderClosed, Icon_FolderOpened);
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(tree, wxSizerFlags(1).Expand());
	SetSizer(sizer);
	Show();
}
void OrgnaizationDlg::InitData()
{
	std::vector<int> field_id;
	std::vector<string> field_name;
	std::vector<bool> field_viewall;
	std::vector<string> user_name;
	std::vector<int> user_fieldid;
	GetDataFromDB(field_id, field_name, field_viewall, user_name, user_fieldid);
	wxTreeCtrl* tree = dynamic_cast<wxTreeCtrl*>(FindWindow(ID_TREE));
	wxTreeItemId rootId = tree->GetRootItem();
	for (int i = 0; i < field_id.size(); i++)
	{
		wxTreeItemId orgitemId = tree->AppendItem(rootId, wxString(field_name[i]), Icon_FolderClosed, Icon_FolderOpened);
		for (int j = 0; j < user_fieldid.size(); j++)
		{
			if (user_fieldid[j] == field_id[i])
			{
				tree->AppendItem(orgitemId, wxString(user_name[j]), -1, -1);
			}
		}
		tree->Expand(orgitemId);
	}
	tree->Expand(rootId);
}
void OrgnaizationDlg::GetDataFromDB(std::vector<int> &field_id, std::vector<std::string> &field_name, std::vector<bool> &field_viewall, std::vector<std::string> &user_name, std::vector<int> &user_fieldid)
{
	field_id.clear();
	field_name.clear();
	field_viewall.clear();
	user_name.clear();
	user_fieldid.clear();
	DBSourceDesc db_desc;
	giTheApp(giDataApp).ReadDBConfig(db_desc);
	CAnyAccessor::InitDB(db_desc);
	CAnyAccessor accessor;
	string sql = "select fieldid, fieldname, viewall from ref_oilfields";
	bool rt = accessor.Execute(sql);
	if (rt)
	{
		for (int i = 0; i < accessor.GetRecordCount(); i++)
		{
			string temp = "";
			accessor.FetchField((long)0, temp);
			field_id.push_back(::atoi(temp.c_str()));
			accessor.FetchField((long)1, temp);
			field_name.push_back(temp.c_str());
			accessor.FetchField((long)2, temp);
			field_viewall.push_back(::atoi(temp.c_str()));
			accessor.MoveNext();
		}
	}
	sql = "select name, fieldid from ref_sys_user";
	rt = accessor.Execute(sql);
	if (rt)
	{
		for (int i = 0; i < accessor.GetRecordCount(); i++)
		{
			string temp = "";
			accessor.FetchField((long)0, temp);
			user_name.push_back(temp.c_str());
			accessor.FetchField((long)1, temp);
			user_fieldid.push_back(::atoi(temp.c_str()));
			accessor.MoveNext();
		}
	}
}
void OrgnaizationDlg::OnClose(wxCloseEvent& event)
{
	EndModal(wxID_CANCEL);
}
void OrgnaizationDlg::OnItemMenu(wxTreeEvent& event)
{
	wxTreeCtrl* tree = dynamic_cast<wxTreeCtrl*>(FindWindow(ID_TREE));
	wxTreeItemId rootId = tree->GetRootItem();
	std::vector<wxTreeItemId> orgitemIds;
	wxTreeItemIdValue idvalue;
	wxTreeItemId child = tree->GetFirstChild(rootId, idvalue);
	while (child.IsOk())
	{
		orgitemIds.push_back(child);
		child = tree->GetNextChild(rootId, idvalue);
	}
	wxTreeItemId eventitemId = event.GetItem();
	string eventitemname = tree->GetItemText(eventitemId).ToStdString();
	wxMenu menu;
	if (eventitemId == rootId)
	{
		menu.Append(ID_ADDORG, _("Add orgnization"));
	}
	else
	{
		bool isorgitem = false;
		for (int i = 0; i < orgitemIds.size(); i++)
		{
			if (eventitemId == orgitemIds[i])
			{
				isorgitem = true;
				break;
			}
		}
		if (isorgitem)
		{
			menu.Append(ID_DELETEORG, _("Delete orgnization"));
			menu.Append(ID_ADDUSER, _("Add user"));
			menu.AppendCheckItem(ID_VIEW_ALL, _("Set as headquaters"));
			std::vector<int> field_id;
			std::vector<string> field_name;
			std::vector<bool> field_viewall;
			std::vector<string> user_name;
			std::vector<int> user_fieldid;
			GetDataFromDB(field_id, field_name, field_viewall, user_name, user_fieldid);
			for (int i = 0; i < field_name.size(); i++)
			{
				if (field_name[i] == eventitemname)
				{
					if (field_viewall[i])
					{
						menu.Check(ID_VIEW_ALL, true);
					}
					else
					{
						menu.Check(ID_VIEW_ALL, false);
					}
					break;
				}
			}
		}
		else
		{
			menu.Append(ID_DELETE_USER, _(wxT("Delete User")));
		}
	}
	tree->SetFocusedItem(eventitemId);
	wxPoint clientpt = event.GetPoint();
	PopupMenu(&menu, clientpt);
}
void OrgnaizationDlg::OnAddOrg(wxCommandEvent &event)
{
	wxTreeCtrl* tree = dynamic_cast<wxTreeCtrl*>(FindWindow(ID_TREE));
	wxTreeItemId rootId = tree->GetRootItem();
	wxTextEntryDialog dlg(this, _(wxT("Orgnization Name:")), _(wxT("Add Orgnization")), wxEmptyString);
	if (dlg.ShowModal() == wxID_OK)
	{
		string orgname = dlg.GetValue().ToStdString();
		CAnyAccessor accessor;
		int maxfieldid = 1;
		string sql = "select max(fieldid) from ref_oilfields";
		bool rt = accessor.Execute(sql);
		if (rt)
		{
			string temp = "";
			accessor.FetchField((long)0, temp);
			maxfieldid = ::atoi(temp.c_str());
			maxfieldid++;
		}
		char sentence1[1024] = "insert into ref_oilfields(fieldid, fieldname, viewall) values (%d, '%s', 1)";
		char sql1[1024] = { 0, };
		::sprintf(sql1, sentence1, maxfieldid, orgname.c_str());
		rt = accessor.Execute(sql1);
		if (rt)
		{
			tree->AppendItem(rootId, orgname, Icon_FolderClosed, Icon_FolderOpened);
		}
		char sentence2[1024] = "insert into ref_key_generator(keyid, nextid, maxid, name, oilfieldid) values(%d, %d, %d, 'default', '%d')";
		char sql2[1024] = { 0, };
		::sprintf(sql2, sentence2, maxfieldid, (maxfieldid - 1)*(1 << 25), (maxfieldid - 1)*(1 << 25) + 10, maxfieldid);
		rt = accessor.Execute(sql2);
	}
}
void OrgnaizationDlg::OnDeleteOrg(wxCommandEvent &event)
{
	if (wxMessageBox(_(wxT("Do you really want to delete?")), _(wxT("Info")), wxYES_NO) != wxYES)
	{
		return;
	}
	wxTreeCtrl* tree = dynamic_cast<wxTreeCtrl*>(FindWindow(ID_TREE));
	wxTreeItemId FocusedItem = tree->GetFocusedItem();
	CAnyAccessor accessor;
	char sentence[1024] = "delete from ref_oilfields where fieldname = '%s'";
	char sql[1024] = { 0, };
	::sprintf(sql, sentence, tree->GetItemText(FocusedItem).ToStdString().c_str());
	bool rt = accessor.Execute(sql);
	if (rt)
	{
		tree->Delete(FocusedItem);
	}
}
void OrgnaizationDlg::OnAddUser(wxCommandEvent &event)
{
	DBSourceDesc db_desc;
	giTheApp(giDataApp).ReadDBConfig(db_desc);
	wxArrayString choices;
	choices.Add(db_desc.m_dbName);
	RegisterUserDlg* registeruser = new RegisterUserDlg(this, choices, db_desc.m_srcName, db_desc.m_user, db_desc.m_pwd, db_desc.m_dbName);
	wxTreeCtrl* tree = dynamic_cast<wxTreeCtrl*>(FindWindow(ID_TREE));
	wxTreeItemId FocusedItem = tree->GetFocusedItem();
	std::vector<int> field_id;
	std::vector<string> field_name;
	std::vector<bool> field_viewall;
	std::vector<string> user_name;
	std::vector<int> user_fieldid;
	GetDataFromDB(field_id, field_name, field_viewall, user_name, user_fieldid);
	for (int offset = 0; offset < field_name.size(); offset++)
	{
		if (field_name[offset] == tree->GetItemText(FocusedItem).ToStdString())
		{
			registeruser->SetWithOrg(true, field_id[offset], db_desc.m_dbName);
			registeruser->ShowModal();
			tree->DeleteChildren(FocusedItem);
			CAnyAccessor accessor;
			char sentence[1024] = "select name from ref_sys_user where fieldid = %d";
			char sql[1024] = { 0, };
			::sprintf(sql, sentence, field_id[offset]);
			bool rt = accessor.Execute(sql);
			if (rt)
			{
				for (int i = 0; i < accessor.GetRecordCount(); i++)
				{
					string temp = "";
					accessor.FetchField((long)0, temp);
					string username = temp.c_str();
					tree->AppendItem(FocusedItem, username, -1, -1);
					accessor.MoveNext();
				}
			}
			tree->Expand(FocusedItem);
			break;
		}
	}
}
void OrgnaizationDlg::OnDeleteUser(wxCommandEvent &event)
{
	if (wxMessageBox(_(wxT("Do you really want to delete?")), _(wxT("Info")), wxYES_NO) != wxYES)
	{
		return;
	}
	DBSourceDesc db_desc;
	giTheApp(giDataApp).ReadDBConfig(db_desc);
	wxTreeCtrl* tree = dynamic_cast<wxTreeCtrl*>(FindWindow(ID_TREE));
	wxTreeItemId FocusedItem = tree->GetFocusedItem();
	string username = tree->GetItemText(FocusedItem).ToStdString();
	tree->Delete(FocusedItem);
	//删数据库
	{
		CAnyAccessor accessor;
		std::string cmd = "delete from a_bayes_net_node where whodo = '" + username + "'";
		accessor.Execute(cmd);
		cmd = "delete from a_bayes_net_branch where whodo = '" + username + "'";
		accessor.Execute(cmd);
		cmd = "delete from a_decision_tree_node where whodo = '" + username + "'";
		accessor.Execute(cmd);
		cmd = "delete from a_decision_tree_branch where whodo = '" + username + "'";
		accessor.Execute(cmd);
		cmd = "delete from a_pb_tree_node where whodo = '" + username + "'";
		accessor.Execute(cmd);
		cmd = "delete from a_pb_tree_branch where whodo = '" + username + "'";
		accessor.Execute(cmd);
		cmd = "delete from r_activity_template where username = '" + username + "'";
		accessor.Execute(cmd);
		std::vector<int> elementids;
		cmd = "select distinct elementid from a_practice where whodo = '" + username + "'";
		accessor.Execute(cmd);
		for (int i = 0; i < accessor.GetRecordCount(); i++)
		{
			std::string temp = "";
			accessor.FetchField((long)0, temp);
			elementids.push_back(::atoi(temp.c_str()));
			accessor.MoveNext();
		}
		/*for (int i = 0; i < elementids.size(); i++)
		{
			CAccumulationElement *element = new CAccumulationElement(NULL);
			CAccumulationElement::ElementRecord record;
			record.m_idx = elementids[i];
			element->SetRecord(record);
			accessor.SetShowInfoToWindow(false);
			element->DeleteAllElementActivities(accessor, username);
			element->DeleteAllElementActivitiesPractice(accessor, username);
			accessor.SetShowInfoToWindow(true);
			delete element;
			element = NULL;
		}*/
		cmd = "delete from i_el_evaluation where whodo = '" + username + "'";
		accessor.Execute(cmd);
		cmd = "delete from ref_sys_user where name = '" + username + "'";
		accessor.Execute(cmd);
	}
	//删角色、用户
	if (db_desc.m_type == DBS_SQLSERVER)
	{
		CAnyAccessor accessor;
		std::string cmd = "EXEC sp_droprolemember N'db_owner', N'" + username + "'";
		accessor.Execute(cmd);
		cmd = "DROP USER [" + username + "]";
		accessor.Execute(cmd);
	}
	else
	{
		CAnyAccessor accessor;
		std::string cmd = "revoke all privileges on " + db_desc.m_dbName + ".* from " + username;
		accessor.Execute(cmd);
	}
	//删登录名
	bool hasdatabase = false;
	if (db_desc.m_type == DBS_SQLSERVER)
	{
		CAnyAccessor accessor;
		std::string cmd = "EXEC sp_helplogins";
		accessor.Execute(cmd);
		accessor.NextRecordset();
		for (int i = 0; i < accessor.GetRecordCount(); i++)
		{
			std::string temp = "";
			accessor.FetchField((long)0, temp);
			if (string(temp.c_str()) == username)
			{
				hasdatabase = true;
				break;
			}
			accessor.MoveNext();
		}
	}
	else
	{
		CAnyAccessor accessor;
		std::string cmd = "show grants for " + username;
		accessor.Execute(cmd);
		if (accessor.GetRecordCount() > 0)
		{
			hasdatabase = true;
		}
	}
	if (!hasdatabase)
	{
		wxMessageDialog dialog(this, _(wxT("This user has no database, do you want to delete the user?")), _(wxT("Delete question")), wxCENTER | wxNO_DEFAULT | wxYES_NO | wxCANCEL | wxICON_QUESTION);
		if (dialog.ShowModal() == wxID_YES)
		{
			CAnyAccessor accessor;
			if (db_desc.m_type == DBS_MYSQL)
			{
				std::string cmd = "drop user " + username;
				accessor.Execute(cmd);
				cmd = "use mysql";
				accessor.Execute(cmd);
				cmd = "delete from user where user='" + username + "'";
				accessor.Execute(cmd);
			}
			else
			{
				std::string cmd = "EXEC sp_dropsrvrolemember N'" + username + "',N'sysadmin'";
				accessor.Execute(cmd);
				cmd = "DROP LOGIN [" + username + "]";
				accessor.Execute(cmd);
			}
		}
	}
}
void OrgnaizationDlg::OnSetViewall(wxCommandEvent &event)
{
	wxTreeCtrl* tree = dynamic_cast<wxTreeCtrl*>(FindWindow(ID_TREE));
	wxTreeItemId FocusedItem = tree->GetFocusedItem();
	std::vector<int> field_id;
	std::vector<string> field_name;
	std::vector<bool> field_viewall;
	std::vector<string> user_name;
	std::vector<int> user_fieldid;
	GetDataFromDB(field_id, field_name, field_viewall, user_name, user_fieldid);
	for (int offset = 0; offset < field_name.size(); offset++)
	{
		if (field_name[offset] == tree->GetItemText(FocusedItem).ToStdString())
		{
			CAnyAccessor accessor;
			bool viewall = field_viewall[offset];
			if (!viewall)
			{
				char sentence[1024] = "update ref_oilfields set viewall = 1 where fieldname = '%s'";
				char sql[1024] = { 0, };
				::sprintf(sql, sentence, tree->GetItemText(FocusedItem).ToStdString().c_str());
				bool rt = accessor.Execute(sql);
			}
			else
			{
				char sentence[1024] = "update ref_oilfields set viewall = 0 where fieldname = '%s'";
				char sql[1024] = { 0, };
				::sprintf(sql, sentence, tree->GetItemText(FocusedItem).ToStdString().c_str());
				bool rt = accessor.Execute(sql);
			}
			break;
		}
	}
}