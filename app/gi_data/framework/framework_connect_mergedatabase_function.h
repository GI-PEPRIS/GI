#ifndef _MERGEDATABASEFUNCTION_H_
#define _MERGEDATABASEFUNCTION_H_
#include "wx/wx.h"
#include "wx/progdlg.h"
#include "any/db/anyaccessorbasic.h"
using namespace AnyDB;

class MergeDataBaseFunction
{
public:
	MergeDataBaseFunction() {}
	~MergeDataBaseFunction() {}
	void UpdateDatabaseStructure();
	bool MergeDatabase(std::vector<DBSourceDesc> &srcdatabases, DBSourceDesc &targetdatabase, bool isupdatesameelement);
private:
	void MergeTable(void *accessorsource, void *accessordest, std::string srctablename, std::string destablename, \
		std::vector<int> &keyidrangemin, std::vector<int> &keyidadd, \
		std::vector<int> &srcactivityid, std::vector<int> &srcactivityidchange, \
		std::vector<int> &srctemplateid, std::vector<int> &srctemplateidchange, \
		std::vector<int> &srcfactorid, std::vector<int> &srcfactoridchange, \
		std::vector<int> &srcprobid, std::vector<int> &srcprobidchange, wxProgressDialog &dialog, wxString directcmd, \
		std::map<int, string> &srcelementid_name, \
		std::map<string, int> &desname_elementid, std::map<int, int> &deselementid_parentid);
	void InitMergeTables(void *accessorstar, std::vector<std::string> &tables, std::vector<bool> &isdirectcopytable);
	void RepairInfoElementRecord(wxString &path, string currentusername, std::vector<int> &elementidsERROR);
	void RepairInfoElementRecordWhodo(wxString &path, string oldname, string newname);
	void RepairElementTrapRecord(wxString &path);
	void RepairManagementphaseRecord(wxString &path);
	void RepairGISCategoryRecord(wxString &path);
	void RepairGISThemeRecord(wxString &path);
	void RemoveOneElementRecord(wxString &path, int elementid);
	void RepairGISClassRecord(wxString &path);
	void RepairRefUserRecord(wxString &path);
	void FieldTypeToTXT(int databasetype, int fieldtype, int fieldlength, std::string &fieldtxt);
};
#endif