#ifndef _SELECTMERGEDATABASEDLG_H_
#define _SELECTMERGEDATABASEDLG_H_
#include "wx/spinctrl.h"
#include "wx/statline.h"
#include "wx\wxprec.h"
#include "wx\dialog.h"
#include "any/db/anyaccessorbasic.h"
using namespace AnyDB;
enum
{
	ID_SRCBTN,
	ID_DESBTN,
	ID_SRCPATHS,
	ID_DESPATH,
	ID_SRCTYPE,
	ID_DESTYPE,
	ID_UpdateSameelement,
};
class SelectMergeDataBaseDlg: public wxDialog
{    
	DECLARE_CLASS(SelectMergeDataBaseDlg)
	DECLARE_EVENT_TABLE()
public:
	SelectMergeDataBaseDlg(wxWindow *parent);
	void OnSelectSrcDatabases(wxCommandEvent& event);
	void OnSrcTypeChange(wxCommandEvent& event);
	void OnSelectDesDatabase(wxCommandEvent& event);
	void OnDesTypeChange(wxCommandEvent& event);
	void OnCheckBox(wxCommandEvent& event);
public:
	std::vector<DBSourceDesc> m_srcdatabases;
	DBSourceDesc m_targetdatabase;
	bool m_updatesameelement;
};
#endif

