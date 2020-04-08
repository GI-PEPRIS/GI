#ifndef _REGISTERUSERDLG_H_
#define _REGISTERUSERDLG_H_

#include "wx/spinctrl.h"
#include "wx/statline.h"
#include "wx\wxprec.h"
#include "wx\dialog.h"
#include "wx\checklst.h"
#include "string"
#include "string.h"
enum {
	ID_USERNAMEREG = 10000,
	ID_PASSWORD1,
	ID_PASSWORD2,
	ID_ISADMIN,
	ID_PRIORITY,
	ID_CHECKLISTBOX,
	ID_REGISTERBUTTON,
	ID_OILFIELD,
	ID_PRIVILEGE
};

class RegisterUserDlg: public wxDialog
{    
    DECLARE_CLASS(RegisterUserDlg)
	DECLARE_EVENT_TABLE()
public:
	void OnRegister(wxCommandEvent& event);
    RegisterUserDlg(wxWindow *parent, wxArrayString choices, wxString datasource, wxString username, wxString password, wxString dbname);
	void SetWithOrg(bool withOrg, int fieldid, std::string& dbname);
private:
	wxString condatasource;
	wxString conusername;
	wxString conpassword;
	wxString condbname;
	bool m_withOrg;
	wxCheckListBox* databaselist;
	std::string m_orgname;
	int m_fieldid;
};

#endif
   
