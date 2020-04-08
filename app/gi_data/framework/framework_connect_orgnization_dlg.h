#ifndef _ORGNIZATIONDLG_H_
#define _ORGNIZATIONDLG_H_

#include "wx/spinctrl.h"
#include "wx/statline.h"
#include "wx/wxprec.h"
#include "wx/dialog.h"
#include "wx/treectrl.h"

enum {
	ID_TREE,
	ID_ADDORG,
	ID_DELETEORG,
	ID_ADDUSER,
	ID_DELETE_USER,
	ID_VIEW_ALL
};
enum
{
	Icon_File,
	Icon_FolderClosed,
	Icon_FolderOpened
};
class OrgnaizationDlg : public wxDialog
{
	DECLARE_CLASS(OrgnaizationDlg)
	DECLARE_EVENT_TABLE()
public:
	OrgnaizationDlg(wxWindow *parent);
	void InitLayout();
	void InitData();
	void GetDataFromDB(std::vector<int> &field_id, std::vector<std::string> &field_name, std::vector<bool> &field_viewall, std::vector<std::string> &user_name, std::vector<int> &user_fieldid);
	void OnClose(wxCloseEvent& event);
	void OnItemMenu(wxTreeEvent& event);
	void OnAddOrg(wxCommandEvent &event);
	void OnDeleteOrg(wxCommandEvent &event);
	void OnAddUser(wxCommandEvent &event);
	void OnDeleteUser(wxCommandEvent &event);
	void OnSetViewall(wxCommandEvent &event);
};
#endif

