#include "framework_connect_mergedatabase_function.h"

#include "framework_data_app.h"

#include "any/base/anydirbasic.h"
#include "any/base/anystringbasic.h"
#include "any/base/anytimebasic.h"

#include "any/db/anyaccessor.h"
using namespace AnyDB;

//#include "any/petro/accumulationassessor.h"
//#include "any/petro/assessmentusermanager.h"
//#include "any/petro/accumulationelement.h"
//#include "any/petro/anypetrodata.h"
//using namespace AnyPetro;
//
//#include "any/geop/anysegylayer.h"
//using namespace AnyGeoP;
//
//#include "any/bridge/anywelltable.h"
//using namespace AnyBridge;

void MergeDataBaseFunction::UpdateDatabaseStructure()
{
	DBSourceDesc srcdatabase;
	giTheApp(giDataApp).ReadDBConfig(srcdatabase);
	DBSourceDesc targetdatabase = srcdatabase;
	if (srcdatabase.m_type == DBS_SQLSERVER || srcdatabase.m_type == DBS_MYSQL)
	{
		targetdatabase.m_dbName += "tmp";
		while (CAnyAccessor::IsDatabaseExist(targetdatabase))
			targetdatabase.m_dbName += "1";
		CAnyAccessor::CreateDatabase(targetdatabase);
		CAnyAccessor::InitSQLDBFileDataOnly(targetdatabase);
	}
	else if (srcdatabase.m_type == DBS_MDB || srcdatabase.m_type == DBS_SQLITE)
	{
		string path = wxString(targetdatabase.m_dbName).SubString(0, wxString(targetdatabase.m_dbName).find_last_of(".") - 1).ToStdString();
		path += "tmp";
		while (true)
		{
			TCHAR wbuf[1024] = { 0, };
			string fullpath = path;
			if (srcdatabase.m_type == DBS_MDB)
				fullpath = path + ".mdb";
			else if (srcdatabase.m_type == DBS_SQLITE)
				fullpath = path + ".db";
			CAnyStringBasic::Get().Ascii2Wcs((char*)fullpath.c_str(), wbuf, 1024);
			if (CAnyDirBasic::Get().IsFileExist(wbuf))
			{
				path += "1";
				continue;
			}
			break;
		}
		targetdatabase.m_srcName = "";
		targetdatabase.m_user = "";
		targetdatabase.m_pwd = "";
		targetdatabase.m_dbName = path;
		if (srcdatabase.m_type == DBS_MDB)
			targetdatabase.m_dbName = path + ".mdb";
		else if (srcdatabase.m_type == DBS_SQLITE)
			targetdatabase.m_dbName = path + ".db";
		CAnyAccessor::ReleaseDB();
		CAnyAccessor::InitDB(targetdatabase);
		CAnyAccessor::InitDBFileDataOnly(targetdatabase);
	}
	{
		CAnyAccessor::InitDB(targetdatabase);
		string targetdatabasestr = targetdatabase.m_srcName + targetdatabase.m_dbName;
		CAnyAccessor accessorDes(targetdatabasestr);
		CAnyAccessor::InitDB(srcdatabase);
		string srcdatabasesstr = srcdatabase.m_srcName + srcdatabase.m_dbName;
		CAnyAccessor accessorSrc(srcdatabasesstr);
		for (int i = 0; i < accessorDes.GetTableCount(); i++)
		{
			DBTableDesc tDesc;
			accessorDes.GetTableDesc(i, tDesc);
			string sql = "select top 1 * from " + tDesc.m_name;
			if (accessorDes.IsMySQL() || accessorDes.IsSQLite())
				sql = "select * from " + tDesc.m_name + " limit 1";
			std::vector<DBFieldDesc> desfDescs;
			bool rt = accessorDes.Execute(sql);
			if (!rt)
				continue;
			for (int j = 0; j < accessorDes.GetFieldCount(tDesc); j++)
			{
				DBFieldDesc fDesc;
				fDesc.m_table = tDesc.m_name;
				accessorDes.GetFieldDesc((long)j, fDesc);
				desfDescs.push_back(fDesc);
			}
			rt = accessorSrc.Execute(sql);
			if (!rt)
			{
				string sql;
				sql.reserve(1024);
				sql = "create table " + tDesc.m_name + " (";
				for (int i = 0; i < desfDescs.size(); i++)
				{
					if (i > 0)
						sql = sql + ", " + desfDescs[i].m_name + " ";
					else
						sql = sql + desfDescs[i].m_name + " ";
					std::string fieldtxt;
					FieldTypeToTXT(srcdatabase.m_type, desfDescs[i].m_type, desfDescs[i].m_length, fieldtxt);
					sql += fieldtxt;
				}
				sql += ")";
				accessorSrc.Execute(sql);
			}
			else
			{
				std::vector<DBFieldDesc> srcfDescs;
				for (int j = 0; j < accessorSrc.GetFieldCount(tDesc); j++)
				{
					DBFieldDesc fDesc;
					fDesc.m_table = tDesc.m_name;
					accessorSrc.GetFieldDesc((long)j, fDesc);
					srcfDescs.push_back(fDesc);
				}
				for (int j = 0; j < desfDescs.size(); j++)
				{
					bool find = false;
					for (int k = 0; k < srcfDescs.size(); k++)
					{
						if (srcfDescs[k].m_name == desfDescs[j].m_name)
						{
							find = true;
							break;
						}
					}
					if (!find)
					{
						string sql;
						sql.reserve(1024);
						sql = "alter table " + desfDescs[j].m_table + " add " + desfDescs[j].m_name + " ";
						std::string fieldtxt;
						FieldTypeToTXT(srcdatabase.m_type, desfDescs[j].m_type, desfDescs[j].m_length, fieldtxt);
						sql += fieldtxt;
						accessorSrc.Execute(sql);
					}
				}
				for (int j = 0; j < srcfDescs.size(); j++)
				{
					bool find = false;
					for (int k = 0; k < desfDescs.size(); k++)
					{
						if (desfDescs[k].m_name == srcfDescs[j].m_name)
						{
							find = true;
							break;
						}
					}
					if (!find)
					{
						string sql = "alter table " + tDesc.m_name + " drop column " + srcfDescs[j].m_name;
						accessorSrc.Execute(sql);
					}
				}
			}
		}
	}
	CAnyAccessor::ReleaseDB();
	if (srcdatabase.m_type == DBS_SQLSERVER || srcdatabase.m_type == DBS_MYSQL)
	{
		DBSourceDesc temp = targetdatabase;
		temp.m_dbName = "master";
		CAnyAccessor::InitDB(temp);
		{
			CAnyAccessor::SwitchToDB(temp.m_srcName + temp.m_dbName);
			CAnyAccessor accessor(false);
			char sentence0[1024] = "select spid from sysprocesses where dbid=db_id('%s')";
			char sql0[1024] = { 0, };
			::sprintf(sql0, sentence0, targetdatabase.m_dbName.c_str());
			bool rt0 = accessor.Execute(sql0);
			accessor.MoveFirst();
			int count = accessor.GetRecordCount();
			string* val = new string[count];
			for (int i = 0; i < count; i++)
			{
				accessor.FetchField((long)0, val[i]);
				accessor.MoveNext();
			}
			for (int i = 0; i < count; i++)
			{
				char sentence0[1024] = "kill %s";
				char sql0[1024] = { 0, };
				::sprintf(sql0, sentence0, val[i].c_str());
				bool rt0 = accessor.Execute(sql0);
			}
			delete[] val;
			char sentence[1024] = "Drop database \"%s\"";
			char sql[1024] = { 0, };
			::sprintf(sql, sentence, targetdatabase.m_dbName.c_str());
			accessor.Execute(sql);
		}
	}
	else if (srcdatabase.m_type == DBS_MDB || srcdatabase.m_type == DBS_SQLITE)
	{
		string cmd = string("del \"") + targetdatabase.m_dbName + "\"";
		::system(cmd.c_str());
	}
}
bool MergeDataBaseFunction::MergeDatabase(std::vector<DBSourceDesc> &srcdatabases, DBSourceDesc &targetdatabase, bool isupdatesameelement)
{
	if (targetdatabase.m_type == DBS_SQLSERVER || targetdatabase.m_type == DBS_MYSQL)
	{
		if (!CAnyAccessor::IsDatabaseExist(targetdatabase))
		{
			CAnyAccessor::ReleaseDB();
			CAnyAccessor::CreateDatabase(targetdatabase);
			CAnyAccessor::InitSQLDBFileDataOnly(targetdatabase);
			CAnyAccessor::InitDB(targetdatabase);
			{
				CAnyAccessor accessor;
				char sentence[1024] = "insert into ref_sys_user (userid, name, department, priority, authorities, fieldid) values(1, '%s', '', 0, 'all', 1)";
				char sql[1024] = "";
				::sprintf(sql, sentence, targetdatabase.m_user.c_str());
				accessor.Execute(sql);
			}
			CAnyAccessor::ReleaseDB(targetdatabase);
			CAnyAccessor::InitDB(targetdatabase);
			//CAccumulationAssessor::InitActivityRecords(0);
		}
	}
	else if (targetdatabase.m_type == DBS_MDB || targetdatabase.m_type == DBS_SQLITE)
	{
		if (!wxFile::Exists(targetdatabase.m_dbName.c_str()))
		{
			CAnyAccessor::ReleaseDB();
			CAnyAccessor::InitDB(targetdatabase);
			CAnyAccessor::InitDBFileDataOnly(targetdatabase);
			CAnyAccessor::InitDB(targetdatabase);
			{
				CAnyAccessor accessor;
				char sentence[1024] = "insert into ref_sys_user (userid, name, department, priority, authorities, fieldid) values(1, 'admin', '', 0, 'all', 1)";
				char sql[1024] = "";
				::sprintf(sql, sentence);
				accessor.Execute(sql);
			}
			CAnyAccessor::ReleaseDB(targetdatabase);
			CAnyAccessor::InitDB(targetdatabase);
			//CAccumulationAssessor::InitActivityRecords(0);
		}
	}
	{
		CAnyAccessor::InitDB(targetdatabase);
		string targetdatabasestr = targetdatabase.m_srcName + targetdatabase.m_dbName;
		CAnyAccessor desdb(targetdatabasestr);
		desdb.LoadSchema(targetdatabasestr);
		CAnyAccessor accessorDes(targetdatabasestr);
		if (accessorDes.GetTableCount() == 0)
		{
			wxMessageBox(_(wxT("Target database has no table, please initialize target database first!")), _(wxT("Info")));
			CAnyAccessor::ReleaseDB(targetdatabase);
			return false;
		}
		for (int databaseitr = 0; databaseitr < srcdatabases.size(); databaseitr++)
		{
			if (databaseitr > 0)
			{
				string srcdatabasesstr = srcdatabases[databaseitr - 1].m_srcName + srcdatabases[databaseitr - 1].m_dbName;
				CAnyAccessor::ReleaseDB(srcdatabases[databaseitr - 1]);
			}
			CAnyAccessor::InitDB(srcdatabases[databaseitr]);
			string srcdatabasesstr = srcdatabases[databaseitr].m_srcName + srcdatabases[databaseitr].m_dbName;
			CAnyAccessor srcdb(srcdatabasesstr);
			srcdb.LoadSchema(srcdatabasesstr);
			CAnyAccessor accessorSrc(srcdatabasesstr);
			std::vector<int> keyidrangemin;
			std::vector<int> keyidadd;
			{
				std::vector<int> srcfieldid;
				std::vector<string> srcfieldname;
				std::vector<int> srckeyidrangemin;
				std::vector<int> srckeynextid;
				int srcfieldidmax = 0;
				std::vector<int> desfieldid;
				std::vector<string> desfieldname;
				std::vector<int> deskeyidrangemin;
				std::vector<int> deskeynextid;
				int desfieldidmax = 0;
				// get existed src & des field info
				string sql;
				sql.reserve(1024);
				sql = "select fieldid, fieldname, nextid from ref_oilfields, ref_key_generator where ref_oilfields.fieldid = ref_key_generator.oilfieldid";
				bool rt = accessorSrc.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorSrc.GetRecordCount(); i++)
					{
						string temp = "";
						accessorSrc.FetchField((long)0, temp);
						srcfieldid.push_back(::atoi(temp.c_str()));
						if (srcfieldidmax < ::atoi(temp.c_str()))
							srcfieldidmax = ::atoi(temp.c_str());
						accessorSrc.FetchField((long)1, temp);
						srcfieldname.push_back(temp.c_str());
						accessorSrc.FetchField((long)2, temp);
						srckeynextid.push_back(::atoi(temp.c_str()));
						int rangemin = 0;
						while (rangemin + pow(2.0, 25) <= ::atoi(temp.c_str()))
						{
							rangemin += pow(2.0, 25);
						}
						srckeyidrangemin.push_back(rangemin);
						accessorSrc.MoveNext();
					}
				}
				rt = accessorDes.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorDes.GetRecordCount(); i++)
					{
						string temp = "";
						accessorDes.FetchField((long)0, temp);
						desfieldid.push_back(::atoi(temp.c_str()));
						if (desfieldidmax < ::atoi(temp.c_str()))
							desfieldidmax = ::atoi(temp.c_str());
						accessorDes.FetchField((long)1, temp);
						desfieldname.push_back(temp.c_str());
						accessorDes.FetchField((long)2, temp);
						deskeynextid.push_back(::atoi(temp.c_str()));
						int rangemin = 0;
						while (rangemin + pow(2.0, 25) <= ::atoi(temp.c_str()))
						{
							rangemin += pow(2.0, 25);
						}
						deskeyidrangemin.push_back(rangemin);
						accessorDes.MoveNext();
					}
				}
				bool isdatabasetypechange = false;
				if (srcdatabases[databaseitr].m_type != targetdatabase.m_type)
					isdatabasetypechange = true;
				// choose/add oil field
				if (srcfieldname.size() == 0 || isdatabasetypechange)
				{
					wxArrayString choices;
					for (int i = 0; i < desfieldname.size(); i++)
					{
						choices.Add(wxString(desfieldname[i]));
					}
					choices.Add(_(wxT("new")));
					wxSingleChoiceDialog dialog((wxWindow*)(&(giTheApp(giDataApp).GetFrame())), _(wxT("Choose Oil Field for:")) + srcdatabases[databaseitr].m_dbName, _(wxT("Choose Oil Field")), choices, (void **)NULL, wxCAPTION | wxSYSTEM_MENU | wxOK | wxCENTER | wxRESIZE_BORDER);
					while (dialog.ShowModal() != wxID_OK)
					{
						dialog.ShowModal();
					}
					// choose a des field as src field
					if (dialog.GetSelection() != choices.size() - 1)
					{
						if (srcfieldname.size() > 0 && isdatabasetypechange)
						{
							for (int i = 0; i < srcfieldname.size(); i++)
							{
								srcfieldname[i] = desfieldname[dialog.GetSelection()];
							}
						}
						else
						{
							srcfieldidmax++;
							srcfieldid.push_back(srcfieldidmax);
							srcfieldname.push_back(desfieldname[dialog.GetSelection()]);
						}
					}
					// create a new field for src
					else
					{
						wxTextEntryDialog fielddialog((wxWindow*)(&(giTheApp(giDataApp).GetFrame())), _(wxT("Set Field Name")));
						fielddialog.SetTitle(_(wxT("Set Field Name")));
						while (fielddialog.ShowModal() != wxID_OK && fielddialog.GetValue() == "")
						{
							fielddialog.ShowModal();
						}
						bool issame = true;
						while (issame)
						{
							issame = false;
							for (int i = 0; i < desfieldname.size(); i++)
							{
								if (desfieldname[i] == fielddialog.GetValue().ToStdString())
								{
									issame = true;
									break;
								}
							}
							if (issame)
							{
								wxMessageBox(_(wxT("Same name exist, please change other name.")), _(wxT("Info")));
								while (fielddialog.ShowModal() != wxID_OK && fielddialog.GetValue() == "")
								{
									fielddialog.ShowModal();
								}
							}
						}
						if (srcfieldname.size() > 0 && isdatabasetypechange)
						{
							for (int i = 0; i < srcfieldname.size(); i++)
							{
								srcfieldname[i] = fielddialog.GetValue().ToStdString();
							}
						}
						else
						{
							srcfieldidmax++;
							srcfieldid.push_back(srcfieldidmax);
							srcfieldname.push_back(fielddialog.GetValue().ToStdString());
						}
					}
					// add srckeyidrangemin, srckeynextid
					if (srckeyidrangemin.size() < srcfieldid.size())
					{
						sql = "select max(nextid) from ref_key_generator";
						bool rt = accessorSrc.Execute(sql);
						assert(rt);
						string temp = "";
						accessorSrc.FetchField((long)0, temp);
						int rangemin = 0;
						while (rangemin + pow(2.0, 25) <= ::atoi(temp.c_str()))
						{
							rangemin += pow(2.0, 25);
						}
						srckeyidrangemin.push_back(rangemin);
						srckeynextid.push_back(::atoi(temp.c_str()));
					}
				}
				// create keyidrangemin & keyidadd
				for (int i = 0; i < srcfieldname.size(); i++)
				{
					keyidrangemin.push_back(srckeyidrangemin[i]);
					bool find = false;
					for (int j = 0; j < desfieldname.size(); j++)
					{
						if (srcfieldname[i] == desfieldname[j])
						{
							find = true;
							keyidadd.push_back(deskeynextid[j] - srckeyidrangemin[i]);
							{
								char sentence[1024] = "";
								char sql[1024] = { 0, };
								::strcpy(sentence, "update ref_key_generator set nextid=%d, maxid=%d where oilfieldid = %d");
								::sprintf(sql, sentence, deskeynextid[j] + srckeynextid[i] - srckeyidrangemin[i], \
									deskeynextid[j] + srckeynextid[i] - srckeyidrangemin[i] + 500, desfieldid[j]);
								accessorDes.Execute(sql);
								deskeynextid[j] = deskeynextid[j] + srckeynextid[i] - srckeyidrangemin[i];
							}
							break;
						}
					}
					if (!find)
					{
						int maxdeskeyidrangemin = 0;
						for (int j = 0; j < desfieldname.size(); j++)
						{
							if (maxdeskeyidrangemin < deskeyidrangemin[j])
							{
								maxdeskeyidrangemin = deskeyidrangemin[j];
							}
						}
						maxdeskeyidrangemin += pow(2.0, 25);
						keyidadd.push_back(maxdeskeyidrangemin - srckeyidrangemin[i]);
						desfieldidmax++;
						{
							char sentence[1024] = "";
							char sql[1024] = { 0, };
							::strcpy(sentence, "insert into ref_oilfields (fieldid, fieldname, viewall) values (%d, '%s', 0)");
							::sprintf(sql, sentence, desfieldidmax, srcfieldname[i].c_str());
							accessorDes.Execute(sql);
							desfieldid.push_back(desfieldidmax);
							desfieldname.push_back(srcfieldname[i]);
						}
						int maxdeskeyid = 0;
						sql = "select max(keyid) from ref_key_generator";
						bool rt = accessorDes.Execute(sql);
						assert(rt);
						if (accessorDes.GetRecordCount())
						{
							string temp = "";
							accessorDes.FetchField((long)0, temp);
							maxdeskeyid = ::atoi(temp.c_str());
						}
						maxdeskeyid++;
						{
							char sentence[1024] = "";
							char sql[1024] = { 0, };
							::strcpy(sentence, "insert into ref_key_generator (keyid, nextid, maxid, name, oilfieldid) \
											   values (%d, %d, %d, 'default', %d)");
							::sprintf(sql, sentence, maxdeskeyid, (int)(maxdeskeyidrangemin + srckeynextid[i] - srckeyidrangemin[i]), \
								(int)(maxdeskeyidrangemin + srckeynextid[i] - srckeyidrangemin[i] + 500), desfieldidmax);
							accessorDes.Execute(sql);
							deskeyidrangemin.push_back(maxdeskeyidrangemin);
							deskeynextid.push_back(maxdeskeyidrangemin + srckeynextid[i] - srckeyidrangemin[i]);
						}
					}
				}
			}
			std::vector<int> srcactivityid;
			std::vector<int> srcactivityidchange;
			{
				std::vector<string> srcactivityname;
				std::vector<int> srcactivitytype;
				std::vector<int> desactivityid;
				std::vector<string> desactivityname;
				std::vector<int> desactivitytype;
				string sql = "select activityid, name, type from r_activity order by activityid";
				bool rt = accessorSrc.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorSrc.GetRecordCount(); i++)
					{
						string temp = "";
						accessorSrc.FetchField((long)0, temp);
						srcactivityid.push_back(::atoi(temp.c_str()));
						accessorSrc.FetchField((long)1, temp);
						srcactivityname.push_back(temp.c_str());
						accessorSrc.FetchField((long)2, temp);
						srcactivitytype.push_back(::atoi(temp.c_str()));
						accessorSrc.MoveNext();
					}
				}
				sql = "select activityid, name, type from r_activity order by activityid";
				rt = accessorDes.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorDes.GetRecordCount(); i++)
					{
						string temp = "";
						accessorDes.FetchField((long)0, temp);
						desactivityid.push_back(::atoi(temp.c_str()));
						accessorDes.FetchField((long)1, temp);
						desactivityname.push_back(temp.c_str());
						accessorDes.FetchField((long)2, temp);
						desactivitytype.push_back(::atoi(temp.c_str()));
						accessorDes.MoveNext();
					}
				}
				for (int i = 0; i < srcactivityid.size(); i++)
				{
					std::vector<string> namestochange;
					std::vector<int> activityidstochange;
					for (int j = 0; j < desactivityid.size(); j++)
					{
						/*if (CAccumulationAssessor::CompareActivityName(srcactivityname[i], desactivityname[j]))
						{
							namestochange.push_back(desactivityname[j]);
							activityidstochange.push_back(desactivityid[j]);
						}*/
					}
					if (namestochange.size() == 0)
					{
						for (int j = 0; j < desactivitytype.size(); j++)
						{
							if (desactivitytype[j] == srcactivitytype[i])
							{
								namestochange.push_back(desactivityname[j]);
								activityidstochange.push_back(desactivityid[j]);
								break;
							}
						}
					}
					if (namestochange.size() == 0)
						srcactivityidchange.push_back(-1);
					else if (namestochange.size() == 1)
						srcactivityidchange.push_back(activityidstochange[0]);
					else
					{
						bool find = false;
						for (int j = 0; j < namestochange.size(); j++)
						{
							if (namestochange[j] == srcactivityname[i])
							{
								find = true;
								srcactivityidchange.push_back(activityidstochange[j]);
								break;
							}
						}
						if (!find)
							srcactivityidchange.push_back(activityidstochange[0]);
					}
				}
			}
			std::vector<int> srctemplateid;
			std::vector<int> srctemplateidchange;
			{
				std::vector<string> srctemplatename;
				std::vector<int> destemplateid;
				std::vector<string> destemplatename;
				string sql = "select templateid, name from r_quick_template order by templateid";
				bool rt = accessorSrc.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorSrc.GetRecordCount(); i++)
					{
						string temp = "";
						accessorSrc.FetchField((long)0, temp);
						srctemplateid.push_back(::atoi(temp.c_str()));
						accessorSrc.FetchField((long)1, temp);
						srctemplatename.push_back(temp.c_str());
						accessorSrc.MoveNext();
					}
				}
				sql = "select templateid, name from r_quick_template order by templateid";
				rt = accessorDes.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorDes.GetRecordCount(); i++)
					{
						string temp = "";
						accessorDes.FetchField((long)0, temp);
						destemplateid.push_back(::atoi(temp.c_str()));
						accessorDes.FetchField((long)1, temp);
						destemplatename.push_back(temp.c_str());
						accessorDes.MoveNext();
					}
				}
				int maxdestemplateid = 0;
				for (int i = 0; i < destemplateid.size(); i++)
				{
					if (maxdestemplateid < destemplateid[i])
						maxdestemplateid = destemplateid[i];
				}
				std::vector<bool> deshastemplate;
				for (int i = 0; i < srctemplateid.size(); i++)
				{
					bool find = false;
					for (int j = 0; j < destemplateid.size(); j++)
					{
						if (((srctemplatename[i] == "2D油气条件概率评价模板" || srctemplatename[i] == "2D地质风险评价模板") && (destemplatename[j] == "2D油气条件概率评价模板" || destemplatename[j] == "2D地质风险评价模板")) || \
							((srctemplatename[i] == "3D油气条件概率评价模板" || srctemplatename[i] == "3D地质风险评价模板") && (destemplatename[j] == "3D油气条件概率评价模板" || destemplatename[j] == "3D地质风险评价模板")) || \
							((srctemplatename[i] == "2D方案可行性评价模板" || srctemplatename[i] == "2D技术可行性评价模板" || srctemplatename[i] == "2D实施可行性评价模板") && (destemplatename[j] == "2D方案可行性评价模板" || destemplatename[j] == "2D技术可行性评价模板" || destemplatename[j] == "2D实施可行性评价模板")) || \
							((srctemplatename[i] == "3D方案可行性评价模板" || srctemplatename[i] == "3D技术可行性评价模板" || srctemplatename[i] == "3D实施可行性评价模板") && (destemplatename[j] == "3D方案可行性评价模板" || destemplatename[j] == "3D技术可行性评价模板" || destemplatename[j] == "3D实施可行性评价模板")) || \
							(srctemplatename[i] == "含油气性评价简化版" && destemplatename[j] == "含油气性评价简化版") || \
							(srctemplatename[i] == "含油气性评价常规版" && destemplatename[j] == "含油气性评价常规版") || \
							(srctemplatename[i] == "油气成藏系统模板" && destemplatename[j] == "油气成藏系统模板") || \
							(srctemplatename[i] == "升级概率计算模板" && destemplatename[j] == "升级概率计算模板") || \
							(srctemplatename[i] == "低勘探程度评价模版" && destemplatename[j] == "低勘探程度评价模版") || \
							(srctemplatename[i] == "高勘探程度评价模版" && destemplatename[j] == "高勘探程度评价模版") || \
							(srctemplatename[i] == "目标区评价模版" && destemplatename[j] == "目标区评价模版") || \
							(srctemplatename[i] == "区块中等勘探程度模版" && destemplatename[j] == "区块中等勘探程度模版") || \
							(srctemplatename[i] == "区块低勘探程度模版" && destemplatename[j] == "区块低勘探程度模版") || \
							(srctemplatename[i] == "区块较低勘探程度模版" && destemplatename[j] == "区块较低勘探程度模版") || \
							(srctemplatename[i] == "区块价值评价模版" && destemplatename[j] == "区块价值评价模版"))
						{
							find = true;
							srctemplateidchange.push_back(destemplateid[j]);
							break;
						}
					}
					deshastemplate.push_back(find);
					if (!find)
					{
						maxdestemplateid++;
						srctemplateidchange.push_back(maxdestemplateid);
					}
				}
				// merge user defined template
				bool hastemplatekind = true;
				sql = "select templateid, name, whodo, whendo, type, remark, formula, templatekind from r_quick_template";
				rt = accessorSrc.Execute(sql);
				if (!rt)
				{
					hastemplatekind = false;
					sql = "select templateid, name, whodo, whendo, type, remark, formula from r_quick_template";
					rt = accessorSrc.Execute(sql);
				}
				if (rt)
				{
					for (int i = 0; i < accessorSrc.GetRecordCount(); i++)
					{
						string temp = "";
						accessorSrc.FetchField((long)0, temp);
						int templateid = ::atoi(temp.c_str());
						accessorSrc.FetchField((long)1, temp);
						string name = temp.c_str();
						accessorSrc.FetchField((long)2, temp);
						string whodo = temp.c_str();
						accessorSrc.FetchField((long)3, temp);
						int whendo = ::atoi(temp.c_str());
						accessorSrc.FetchField((long)4, temp);
						int type = ::atoi(temp.c_str());
						accessorSrc.FetchField((long)5, temp);
						string remark = temp.c_str();
						accessorSrc.FetchField((long)6, temp);
						string formula = temp.c_str();
						int templatekind = 0;
						if (hastemplatekind)
						{
							accessorSrc.FetchField((long)7, temp);
							templatekind = ::atoi(temp.c_str());
						}
						int templateidchange = -1;
						for (int j = 0; j < srctemplateid.size(); j++)
						{
							if (templateid == srctemplateid[j] && !deshastemplate[j])
							{
								templateidchange = srctemplateidchange[j];
								break;
							}
						}
						if (templateidchange != -1)
						{
							char sentence[1024] = "insert into r_quick_template (templateid, name, whodo, whendo, type, remark, formula, templatekind) values(%d,'%s','%s',%d,%d,'%s','%s',%d)";
							char sql1[1024] = { 0, };
							::sprintf(sql1, sentence, templateidchange, name.c_str(), whodo.c_str(), whendo, type, remark.c_str(), formula.c_str(), templatekind);
							accessorDes.Execute(sql1);
						}
						accessorSrc.MoveNext();
					}
				}
			}
			std::vector<int> srcfactorid;
			std::vector<int> srcfactoridchange;
			{
				std::vector<string> srcfactorname;
				std::vector<int> srcfactortemplateid;
				std::vector<int> desfactorid;
				std::vector<string> desfactorname;
				std::vector<int> desfactortemplateid;
				string sql = "select factorid, name, templateid from r_risk_factor order by factorid";
				bool rt = accessorSrc.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorSrc.GetRecordCount(); i++)
					{
						string temp = "";
						accessorSrc.FetchField((long)0, temp);
						srcfactorid.push_back(::atoi(temp.c_str()));
						accessorSrc.FetchField((long)1, temp);
						srcfactorname.push_back(temp.c_str());
						accessorSrc.FetchField((long)2, temp);
						srcfactortemplateid.push_back(::atoi(temp.c_str()));
						accessorSrc.MoveNext();
					}

				}
				sql = "select factorid, name, templateid from r_risk_factor order by factorid";
				rt = accessorDes.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorDes.GetRecordCount(); i++)
					{
						string temp = "";
						accessorDes.FetchField((long)0, temp);
						desfactorid.push_back(::atoi(temp.c_str()));
						accessorDes.FetchField((long)1, temp);
						desfactorname.push_back(temp.c_str());
						accessorDes.FetchField((long)2, temp);
						desfactortemplateid.push_back(::atoi(temp.c_str()));
						accessorDes.MoveNext();
					}
				}
				int maxdesfactorid = 0;
				for (int i = 0; i < desfactorid.size(); i++)
				{
					if (maxdesfactorid < desfactorid[i])
						maxdesfactorid = desfactorid[i];
				}
				std::vector<bool> deshasfactor;
				for (int i = 0; i < srcfactorid.size(); i++)
				{
					bool find = false;
					for (int j = 0; j < desfactorid.size(); j++)
					{
						if (find)
							break;
						if (srcfactorname[i] == desfactorname[j] || (srcfactorname[i] == "烃岩厚度" && desfactorname[j] == "烃源岩厚度") || \
							(srcfactorname[i] == "烃源岩厚度" && desfactorname[j] == "烃岩厚度") || (srcfactorname[i] == "输导层" && desfactorname[j] == "输导层类型") || \
							(srcfactorname[i] == "输导层类型" && desfactorname[j] == "输导层"))
						{
							for (int k = 0; k < srctemplateid.size(); k++)
							{
								if (srcfactortemplateid[i] == srctemplateid[k] && desfactortemplateid[j] == srctemplateidchange[k])
								{
									find = true;
									srcfactoridchange.push_back(desfactorid[j]);
									break;
								}
							}

						}
					}
					deshasfactor.push_back(find);
					if (!find)
					{
						maxdesfactorid++;
						srcfactoridchange.push_back(maxdesfactorid);
					}
				}
				// merge user defined factor
				sql = "select factorid, parentid, templateid, scoretype, name, uppervalue, lowervalue, svalue, weight, iscommon, formula from r_risk_factor";
				rt = accessorSrc.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorSrc.GetRecordCount(); i++)
					{
						string temp = "";
						accessorSrc.FetchField((long)0, temp);
						int factorid = ::atoi(temp.c_str());
						accessorSrc.FetchField((long)1, temp);
						int parentid = ::atoi(temp.c_str());
						accessorSrc.FetchField((long)2, temp);
						int templateid = ::atoi(temp.c_str());
						accessorSrc.FetchField((long)3, temp);
						int scoretype = ::atoi(temp.c_str());
						accessorSrc.FetchField((long)4, temp);
						string name = temp.c_str();
						accessorSrc.FetchField((long)5, temp);
						float uppervalue = ::atof(temp.c_str());
						accessorSrc.FetchField((long)6, temp);
						float lowervalue = ::atof(temp.c_str());
						accessorSrc.FetchField((long)7, temp);
						string svalue = temp.c_str();
						accessorSrc.FetchField((long)8, temp);
						float weight = ::atof(temp.c_str());
						accessorSrc.FetchField((long)9, temp);
						bool iscommon = ::atoi(temp.c_str());
						accessorSrc.FetchField((long)10, temp);
						string formula = temp.c_str();
						int factoridchange = -1;
						for (int j = 0; j < srcfactorid.size(); j++)
						{
							if (factorid == srcfactorid[j] && !deshasfactor[j])
							{
								factoridchange = srcfactoridchange[j];
								break;
							}
						}
						if (factoridchange != -1)
						{
							int templateidchange = -1;
							for (int j = 0; j < srctemplateid.size(); j++)
							{
								if (templateid == srctemplateid[j])
								{
									templateidchange = srctemplateidchange[j];
									break;
								}
							}
							int parentidchange = parentid;
							if (parentid != 0)
							{
								for (int j = 0; j < srcfactorid.size(); j++)
								{
									if (parentid == srcfactorid[j])
									{
										parentidchange = srcfactoridchange[j];
										break;
									}
								}
							}
							char sentence[1024] = "insert into r_risk_factor (factorid, parentid, templateid, scoretype, name, uppervalue, lowervalue, svalue, weight, iscommon, formula) values\
												  (%d,%d,%d,%d,'%s',%f,%f,'%s',%f,%d,'%s')";
							char sql1[1024] = { 0, };
							::sprintf(sql1, sentence, factoridchange, parentidchange, templateidchange, scoretype, name.c_str(), uppervalue, lowervalue, svalue.c_str(), weight, iscommon, formula.c_str());
							accessorDes.Execute(sql1);
						}
						accessorSrc.MoveNext();
					}
				}
			}
			std::vector<int> srcprobid;
			std::vector<int> srcprobidchange;
			{
				std::vector<string> srcprobname;
				std::vector<int> desprobid;
				std::vector<string> desprobname;
				string sql = "select probid, name from r_probability order by probid";
				bool rt = accessorSrc.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorSrc.GetRecordCount(); i++)
					{
						string temp = "";
						accessorSrc.FetchField((long)0, temp);
						srcprobid.push_back(::atoi(temp.c_str()));
						accessorSrc.FetchField((long)1, temp);
						srcprobname.push_back(temp.c_str());
						accessorSrc.MoveNext();
					}
				}
				sql = "select probid, name from r_probability order by probid";
				rt = accessorDes.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorDes.GetRecordCount(); i++)
					{
						string temp = "";
						accessorDes.FetchField((long)0, temp);
						desprobid.push_back(::atoi(temp.c_str()));
						accessorDes.FetchField((long)1, temp);
						desprobname.push_back(temp.c_str());
						accessorDes.MoveNext();
					}
				}
				for (int i = 0; i < srcprobid.size(); i++)
				{
					bool find = false;
					for (int j = 0; j < desprobid.size(); j++)
					{
						if (srcprobname[i] == desprobname[j])
						{
							find = true;
							srcprobidchange.push_back(desprobid[j]);
							break;
						}
					}
					if (!find)
						srcprobidchange.push_back(-1);
				}
			}
			std::map<int, string> srcelementid_name;
			std::map<string, int> desname_elementid;
			std::map<int, int> deselementid_parentid;
			if (isupdatesameelement)
			{
				string sql = "select elementid, name, parentid from i_el";
				bool rt = accessorSrc.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorSrc.GetRecordCount(); i++)
					{
						string temp = "";
						accessorSrc.FetchField((long)0, temp);
						int elementid = ::atoi(temp.c_str());
						accessorSrc.FetchField((long)1, temp);
						string name = temp.c_str();
						srcelementid_name[elementid] = name;
						accessorSrc.MoveNext();
					}
				}
				rt = accessorDes.Execute(sql);
				if (rt)
				{
					for (int i = 0; i < accessorDes.GetRecordCount(); i++)
					{
						string temp = "";
						accessorDes.FetchField((long)0, temp);
						int elementid = ::atoi(temp.c_str());
						accessorDes.FetchField((long)1, temp);
						string name = temp.c_str();
						accessorDes.FetchField((long)2, temp);
						int parentid = ::atoi(temp.c_str());
						desname_elementid[name] = elementid;
						deselementid_parentid[elementid] = parentid;
						accessorDes.MoveNext();
					}
				}
			}
			std::vector<std::string> tables;
			std::vector<bool> isdirectcopytable;
			InitMergeTables(&accessorSrc, tables, isdirectcopytable);
			wxProgressDialog dialog(_(wxT("Copy database ")) + srcdatabases[databaseitr].m_dbName, _(wxT("Copy database ")) + srcdatabases[databaseitr].m_dbName, 100, (wxWindow*)(&(giTheApp(giDataApp).GetFrame())));
			accessorSrc.SetShowInfoToWindow(false);
			accessorDes.SetShowInfoToWindow(false);
			bool sqliteattach = false;
			for (int i = 0; i < tables.size(); i++)
			{
				wxString directcmd = "";
				if (isdirectcopytable[i] && srcdatabases[databaseitr].m_type == targetdatabase.m_type)
				{
					if (srcdatabases[databaseitr].m_type == DBS_MDB)
					{
						directcmd = "[;database=" + srcdatabases[databaseitr].m_dbName + "]";
					}
					else if (srcdatabases[databaseitr].m_type == DBS_SQLSERVER)
					{
						directcmd = "[" + srcdatabases[databaseitr].m_dbName + "].[dbo]";
					}
					else if (srcdatabases[databaseitr].m_type == DBS_SQLITE && false)
					{
						if (!sqliteattach)
						{
							string cmd = "ATTACH DATABASE '" + srcdatabases[databaseitr].m_dbName + "' AS SRCDATABASE";
							bool rt = accessorDes.Execute(cmd);
							sqliteattach = true;
						}
						directcmd = "SRCDATABASE";
					}
				}
				MergeTable(&accessorSrc, &accessorDes, tables[i], tables[i], keyidrangemin, \
					keyidadd, srcactivityid, srcactivityidchange, srctemplateid, \
					srctemplateidchange, srcfactorid, srcfactoridchange, srcprobid, srcprobidchange, dialog, \
					directcmd, srcelementid_name, desname_elementid, deselementid_parentid);
			}
			if (sqliteattach)
			{
				string cmd = "DETACH DATABASE SRCDATABASE";
				accessorDes.Execute(cmd);
			}
			// modify elementid in sde feature tables
			for (int i = 0; i < tables.size(); i++)
			{
				std::vector<int> elementids;
				if (isdirectcopytable[i])
				{
					char sentence[1024] = "select elementid from %s";
					char sql[1024] = { 0, };
					::sprintf(sql, sentence, tables[i].c_str());
					bool rt = accessorDes.Execute(sql);
					if (rt && accessorDes.GetRecordCount())
					{
						for (int j = 0; j < accessorDes.GetRecordCount(); j++)
						{
							string temp = "";
							accessorDes.FetchField((long)0, temp);
							elementids.push_back(::atoi(temp.c_str()));
							accessorDes.MoveNext();
						}
					}
				}
				if (elementids.size() > 0)
					std::sort(elementids.begin(), elementids.end());
				int curelementid = -1;
				for (int j = 0; j < elementids.size(); j++)
				{
					if (curelementid == elementids[j])
						continue;
					curelementid = elementids[j];
					int elementid = elementids[j];
					for (int k = 0; k < keyidrangemin.size(); k++)
					{
						if (elementid >= keyidrangemin[k] && elementid < keyidrangemin[k] + pow(2.0, 25))
						{
							elementid += keyidadd[k];
							break;
						}
					}
					char sentence[1024] = "update %s set elementid = %d where elementid = %d";
					char sql[1024] = { 0, };
					::sprintf(sql, sentence, tables[i].c_str(), elementid, elementids[j]);
					accessorDes.Execute(sql);
				}
			}
			accessorSrc.SetShowInfoToWindow(true);
			accessorDes.SetShowInfoToWindow(true);
		}
	}
	string targetdatabasestr = targetdatabase.m_srcName + targetdatabase.m_dbName;
	wxProgressDialog dialog(_(wxT("processing...")), _(wxT("Repair element table")), 100, (wxWindow*)(&(giTheApp(giDataApp).GetFrame())));
	DBSourceDesc srcDesc;
	giTheApp(giDataApp).ReadDBConfig(srcDesc);
	string currentusername = srcDesc.m_user;
	if (currentusername != "")
	{
		if ((srcdatabases[0].m_type == DBS_SQLSERVER || srcdatabases[0].m_type == DBS_MYSQL) && (targetdatabase.m_type == DBS_MDB || targetdatabase.m_type == DBS_SQLITE))
		{
			RepairInfoElementRecordWhodo(wxString(targetdatabasestr), currentusername, "admin");
		}
		else if ((srcdatabases[0].m_type == DBS_SQLITE || srcdatabases[0].m_type == DBS_MDB) && (targetdatabase.m_type == DBS_SQLSERVER || targetdatabase.m_type == DBS_MYSQL))
		{
			RepairInfoElementRecordWhodo(wxString(targetdatabasestr), "admin", currentusername);
		}
	}
	std::vector<int> elementidsERROR;
	RepairInfoElementRecord(wxString(targetdatabasestr), currentusername, elementidsERROR);
	dialog.Update(20);
	for (int i = 0; i < elementidsERROR.size(); i++)
	{
		RemoveOneElementRecord(wxString(targetdatabasestr), elementidsERROR[i]);
		dialog.Update(20 + (i * 15) / elementidsERROR.size());
	}
	dialog.Update(50, _(wxT("Repair element_trap table")));
	RepairElementTrapRecord(wxString(targetdatabasestr));
	RepairManagementphaseRecord(wxString(targetdatabasestr));
	dialog.Update(60, _(wxT("Repair GIS category")));
	RepairGISCategoryRecord(wxString(targetdatabasestr));
	RepairGISThemeRecord(wxString(targetdatabasestr));
	dialog.Update(70, _(wxT("Repair GIS class record")));
	RepairGISClassRecord(wxString(targetdatabasestr));
	dialog.Update(80, _(wxT("Repair user record")));
	RepairRefUserRecord(wxString(targetdatabasestr));
	return true;
}
void MergeDataBaseFunction::MergeTable(void *accessorsource, void *accessordest, std::string srctablename, std::string destablename, \
	std::vector<int> &keyidrangemin, std::vector<int> &keyidadd, \
	std::vector<int> &srcactivityid, std::vector<int> &srcactivityidchange, \
	std::vector<int> &srctemplateid, std::vector<int> &srctemplateidchange, \
	std::vector<int> &srcfactorid, std::vector<int> &srcfactoridchange, \
	std::vector<int> &srcprobid, std::vector<int> &srcprobidchange, wxProgressDialog &dialog, wxString directcmd, \
	std::map<int, string> &srcelementid_name, \
	std::map<string, int> &desname_elementid, std::map<int, int> &deselementid_parentid)
{
	CAnyAccessor &accessorSrc = *((CAnyAccessor*)accessorsource);
	CAnyAccessor &accessorDes = *((CAnyAccessor*)accessordest);
	if (directcmd != "")
	{
		string sql = "drop table " + destablename;
		accessorDes.Execute(sql);
		if (accessorDes.IsSQLite())
			sql = "CREATE TABLE " + destablename + " AS SELECT * FROM " + directcmd.ToStdString() + "." + srctablename;
		else
			sql = "select * into " + destablename + " from " + directcmd.ToStdString() + "." + srctablename;
		accessorDes.Execute(sql);
		return;
	}
	std::vector<DBFieldDesc> desfields;
	std::vector<DBFieldDesc> srcfields;
	std::vector<DBFieldDesc> srctomovefields;
	std::vector<DBFieldDesc> destomovefields;
	std::vector<string> activityxxnames;
	std::vector<string> infoxxnames;
	bool destableexist = false;
	int destablecount = accessorDes.GetTableCount();
	for (int i = 0; i < destablecount; i++)
	{
		DBTableDesc tDesc;
		accessorDes.GetTableDesc(i, tDesc);
		if (tDesc.m_name == destablename)
		{
			destableexist = true;
			string sql = "select top 1 * from " + tDesc.m_name;
			if (accessorDes.IsMySQL() || accessorDes.IsSQLite())
				sql = "select * from " + tDesc.m_name + " limit 1";
			bool rt = accessorDes.Execute(sql);
			for (int j = 0; j < accessorDes.GetFieldCount(tDesc); j++)
			{
				DBFieldDesc fDesc;
				fDesc.m_table = tDesc.m_name;
				accessorDes.GetFieldDesc((long)j, fDesc);
				desfields.push_back(fDesc);
			}
			break;
		}
	}
	int srctablecount = accessorSrc.GetTableCount();
	for (int i = 0; i < srctablecount; i++)
	{
		DBTableDesc tDesc;
		accessorSrc.GetTableDesc(i, tDesc);
		if (tDesc.m_name == srctablename)
		{
			string sql = "select top 1 * from " + tDesc.m_name;
			if (accessorSrc.IsMySQL() || accessorSrc.IsSQLite())
				sql = "select * from " + tDesc.m_name + " limit 1";
			bool rt = accessorSrc.Execute(sql);
			for (int j = 0; j < accessorSrc.GetFieldCount(tDesc); j++)
			{
				DBFieldDesc fDesc;
				fDesc.m_table = tDesc.m_name;
				accessorSrc.GetFieldDesc((long)j, fDesc);
				srcfields.push_back(fDesc);
			}
			break;
		}
	}
	if (!destableexist)
	{
		for (int i = 0; i < srcfields.size(); i++)
		{
			srctomovefields.push_back(srcfields[i]);
			destomovefields.push_back(srcfields[i]);
		}
		string sql;
		sql.reserve(1024);
		sql = "create table " + destablename + " (";
		for (int i = 0; i < srcfields.size(); i++)
		{
			if (i > 0)
				sql = sql + ", " + srcfields[i].m_name + " ";
			else
				sql = sql + srcfields[i].m_name + " ";
			std::string fieldtxt;
			FieldTypeToTXT(accessorDes.GetConnectiontype(), srcfields[i].m_type, srcfields[i].m_length, fieldtxt);
			sql += fieldtxt;
		}
		sql += ")";
		accessorDes.Execute(sql);
	}
	else
	{
		for (int i = 0; i < srcfields.size(); i++)
		{
			for (int j = 0; j < desfields.size(); j++)
			{
				if (srcfields[i].m_name == desfields[j].m_name)
				{
					srctomovefields.push_back(srcfields[i]);
					destomovefields.push_back(desfields[j]);
					break;
				}
			}
		}
	}
	if (srctomovefields.size() == 0)
		return;
	string sql;
	sql.reserve(1024);
	sql = "select ";
	for (int i = 0; i < srctomovefields.size(); i++)
	{
		sql = sql + srctomovefields[i].m_name + ", ";
	}
	sql = sql.substr(0, sql.length() - 2);
	sql = sql + " from " + srctablename;
	accessorSrc.Execute(sql);
	int srcrecordcount = accessorSrc.GetRecordCount();
	dialog.Update(0, _(wxT("Copy table:")) + srctablename);
	bool hastop1star = false;
	string cmd, cmd1, cmd2;
	bool isfirstcmd = true;
	int srcrecordinterval = srcrecordcount / 100;
	if (srcrecordinterval == 0)
		srcrecordinterval = 1;
	int elementid_forupdate = -1;
	int parentid_forupdate = -1;
	for (int i = 0; i < srcrecordcount; i++)
	{
		if (i % srcrecordinterval == 0)
			dialog.Update(i * 100 / srcrecordcount, _(wxT("Copy table:")) + srctablename);
		elementid_forupdate = -1;
		std::vector<string> sourcedata;
		std::vector<string> fieldnames;
		std::vector<char*> parameters;
		std::vector<long> lens;
		bool caninsert = true;
		for (int j = 0; j < srctomovefields.size(); j++)
		{
			string temp = "";
			DBFieldDesc &fDesc = srctomovefields[j];
			if (fDesc.m_type != DBF_LongBinary)
			{
				accessorSrc.FetchField((long)j, temp);
			}
			else
			{
				long len = 0;
				char* parameter = 0;
				parameter = accessorSrc.FetchBlobField(fDesc.m_name.c_str(), parameter, len);
				if (len > 0)
				{
					fieldnames.push_back(fDesc.m_name.c_str());
					parameters.push_back(parameter);
					lens.push_back(len);
				}
			}
			if (fDesc.m_name == "elementid" || fDesc.m_name == "geometryid" || fDesc.m_name == "propertyid" || fDesc.m_name == "id" ||
				fDesc.m_name == "practiceid" || fDesc.m_name == "bayesnetworkid" || fDesc.m_name == "decisiontreeid" || fDesc.m_name == "probabilitytreeid" ||
				fDesc.m_name == "topicid" || fDesc.m_name == "templateIdx" || fDesc.m_name == "projectid" || fDesc.m_name == "wellid" ||
				fDesc.m_name == "boreid" || fDesc.m_name == "zoneid" || fDesc.m_name == "categoryid" || fDesc.m_name == "themeid" || fDesc.m_name == "datasetid" ||
				fDesc.m_name == "gateid" || fDesc.m_name == "fromid" || fDesc.m_name == "rasterid" || fDesc.m_name == "classid" ||
				fDesc.m_name == "blobid" || fDesc.m_name == "parentpracticeid" || fDesc.m_name == "featureid" ||
				(fDesc.m_name == "resourceid" && !wxString(destablename).StartsWith("a_npv")) ||
				fDesc.m_name == "riskid" || fDesc.m_name == "economicid" || fDesc.m_name == "selectionid" ||
				fDesc.m_name == "primaryid" || fDesc.m_name == "modelid" || fDesc.m_name == "userid" || fDesc.m_name == "groupid" ||
				fDesc.m_name == "repositoryid" || fDesc.m_name == "wavletid" || (destablename == "a_jobstream" && (fDesc.m_name == "jobid" || fDesc.m_name == "relid")))
			{
				int tempvalue = ::atoi(temp.c_str());
				if (fDesc.m_name == "elementid")
					elementid_forupdate = tempvalue;
				if ((fDesc.m_name == "boreid" || fDesc.m_name == "wellid" || fDesc.m_name == "elementid") && tempvalue == 0)
				{
					// do not change
				}
				else
				{
					for (int k = 0; k < keyidrangemin.size(); k++)
					{
						if (tempvalue >= keyidrangemin[k] && tempvalue < keyidrangemin[k] + pow(2.0, 25))
						{
							tempvalue += keyidadd[k];
							break;
						}
					}
				}
				sourcedata.push_back(wxString::Format("%d", tempvalue).ToStdString());
			}
			else if ((fDesc.m_name == "parentid" && destablename == "i_el") || fDesc.m_name == "seisparentid" || fDesc.m_name == "categoryparentid")
			{
				int tempvalue = ::atoi(temp.c_str());
				if (fDesc.m_name == "parentid")
					parentid_forupdate = tempvalue;
				if (tempvalue != 0)
				{
					for (int k = 0; k < keyidrangemin.size(); k++)
					{
						if (tempvalue >= keyidrangemin[k] && tempvalue < keyidrangemin[k] + pow(2.0, 25))
						{
							tempvalue += keyidadd[k];
							break;
						}
					}
				}
				sourcedata.push_back(wxString::Format("%d", tempvalue).ToStdString());
			}
			else if (fDesc.m_name == "activityid" && wxString(destablename).StartsWith("a_"))
			{
				int tempvalue = ::atoi(temp.c_str());
				int low = 0, high = srcactivityid.size() - 1, mid;
				while (low <= high)
				{
					mid = low + (high - low) / 2;
					if (srcactivityid[mid] == tempvalue)
					{
						tempvalue = srcactivityidchange[mid];
						break;
					}
					else if (srcactivityid[mid] > tempvalue)
						high = mid - 1;
					else
						low = mid + 1;
				}
				if (tempvalue == -1)
				{
					caninsert = false;
					break;
				}
				sourcedata.push_back(wxString::Format("%d", tempvalue).ToStdString());
			}
			else if ((fDesc.m_name == "templateidx" && destablename == "a_practice") || (fDesc.m_name == "templateid" && destablename == "a_practice_score") || \
				(fDesc.m_name == "templateid" && destablename == "a_template_blob"))
			{
				int tempvalue = ::atoi(temp.c_str());
				int low = 0, high = srctemplateid.size() - 1, mid;
				while (low <= high)
				{
					mid = low + (high - low) / 2;
					if (srctemplateid[mid] == tempvalue)
					{
						tempvalue = srctemplateidchange[mid];
						break;
					}
					else if (srctemplateid[mid] > tempvalue)
						high = mid - 1;
					else
						low = mid + 1;
				}
				if (tempvalue == -1)
				{
					caninsert = false;
					break;
				}
				sourcedata.push_back(wxString::Format("%d", tempvalue).ToStdString());
			}
			else if ((fDesc.m_name == "factorid" && destablename == "a_risk") ||
				(fDesc.m_name == "factorid" && destablename == "i_el_factor") ||
				(fDesc.m_name == "factorid" && destablename == "a_practice_score") ||
				(fDesc.m_name == "factorid" && destablename == "a_template_blob"))
			{
				int tempvalue = ::atoi(temp.c_str());
				int low = 0, high = srcfactorid.size() - 1, mid;
				while (low <= high)
				{
					mid = low + (high - low) / 2;
					if (srcfactorid[mid] == tempvalue)
					{
						tempvalue = srcfactoridchange[mid];
						break;
					}
					else if (srcfactorid[mid] > tempvalue)
						high = mid - 1;
					else
						low = mid + 1;
				}
				if (tempvalue == -1)
				{
					caninsert = false;
					break;
				}
				sourcedata.push_back(wxString::Format("%d", tempvalue).ToStdString());
			}
			else if ((fDesc.m_name == "probid" && destablename == "r_probability") || \
				((fDesc.m_name == "areaid" || fDesc.m_name == "mappedid" || fDesc.m_name == "postulatedid" || fDesc.m_name == "conditionalid" || \
					fDesc.m_name == "discoveredid" || fDesc.m_name == "ytfid" || fDesc.m_name == "betaid") && destablename == "i_el_overall"))
			{
				int tempvalue = ::atoi(temp.c_str());
				int low = 0, high = srcprobid.size() - 1, mid;
				while (low <= high)
				{
					mid = low + (high - low) / 2;
					if (srcprobid[mid] == tempvalue)
					{
						tempvalue = srcprobidchange[mid];
						break;
					}
					else if (srcprobid[mid] > tempvalue)
						high = mid - 1;
					else
						low = mid + 1;
				}
				if (tempvalue == -1)
				{
					caninsert = false;
					break;
				}
				sourcedata.push_back(wxString::Format("%d", tempvalue).ToStdString());
			}
			else if (fDesc.m_name == "boreids" && (destablename == "d_well_cross_section" || destablename == "d_well_log_template"))
			{
				string tempstr = temp.c_str();
				int parapos = 0;
				std::vector<int> boreids;
				//2018/10/19: prevent from upgrade errors
				wxString bore_str = tempstr;
				while (!bore_str.IsEmpty())
				{
					//get bore id
					wxString temp_str = bore_str.BeforeFirst(',');
					int boreid = wxAtoi(temp_str);
					boreids.push_back(boreid);
					bore_str = bore_str.AfterFirst(',');
				}
				for (int k = 0; k < boreids.size(); k++)
				{
					if (boreids[k] == 0)
						continue;
					for (int l = 0; l < keyidrangemin.size(); l++)
					{
						if (boreids[k] >= keyidrangemin[l] && boreids[k] < keyidrangemin[l] + pow(2.0, 25))
						{
							boreids[k] += keyidadd[l];
							break;
						}
					}
				}
				string newboreidstr = "";
				for (int k = 0; k < boreids.size(); k++)
				{
					char temp[1024] = "";
					//::sprintf(temp, "%d,", boreids[k]);
					//2018/10/19: keep the original format
					if (k == boreids.size() - 1)
					{
						::sprintf(temp, "%d", boreids[k]);
					}
					else
					{
						::sprintf(temp, "%d,", boreids[k]);
					}
					string tempstr(temp);
					newboreidstr += tempstr;
				}
				sourcedata.push_back(newboreidstr);
			}
			else
			{
				sourcedata.push_back(temp.c_str());
			}
		}
		//重名对象做合并操作
		if (elementid_forupdate != -1)
		{
			if (srcelementid_name.find(parentid_forupdate) != srcelementid_name.end())
			{
				string name = srcelementid_name[parentid_forupdate];
				if (desname_elementid.find(name) != desname_elementid.end())
				{
					int deselementid = desname_elementid[name];
					for (int j = 0; j < srctomovefields.size(); j++)
					{
						if (destablename == "i_el" && srctomovefields[j].m_name == "parentid")
							sourcedata[j] = wxString::Format("%d", deselementid).ToStdString();
					}
				}
			}
			if (srcelementid_name.find(elementid_forupdate) != srcelementid_name.end())
			{
				string name = srcelementid_name[elementid_forupdate];
				if (desname_elementid.find(name) != desname_elementid.end())
				{
					int deselementid = desname_elementid[name];
					int factorid = -1;
					string whodo = "";
					int managementphase = -1;
					for (int j = 0; j < srctomovefields.size(); j++)
					{
						if (srctomovefields[j].m_name == "elementid")
							sourcedata[j] = wxString::Format("%d", deselementid).ToStdString();
						else if (destablename == "i_el" && srctomovefields[j].m_name == "parentid")
							sourcedata[j] = wxString::Format("%d", deselementid_parentid[deselementid]).ToStdString();
						else if (srctomovefields[j].m_name == "factorid")
							factorid = ::atoi(sourcedata[j].c_str());
						else if (srctomovefields[j].m_name == "whodo")
							whodo = sourcedata[j];
						else if (srctomovefields[j].m_name == "managementphase")
							managementphase = ::atoi(sourcedata[j].c_str());
					}
					if (destablename == "i_el")
					{
						string sql = "delete from " + destablename + " where elementid = " + wxString::Format("%d", deselementid).ToStdString();
						accessorDes.Execute(sql);
						hastop1star = false;
					}
					else if (destablename == "i_el_evaluation")
					{
						string sql = "delete from " + destablename + " where elementid = " + wxString::Format("%d", deselementid).ToStdString() + \
							" and managementphase = " + wxString::Format("%d", managementphase).ToStdString() + \
							" and whodo = '" + whodo + "'";
						accessorDes.Execute(sql);
						hastop1star = false;
					}
					else if (destablename == "i_el_factor")
					{
						string sql = "delete from " + destablename + " where elementid = " + wxString::Format("%d", deselementid).ToStdString() + \
							" and factorid = " + wxString::Format("%d", factorid).ToStdString() + \
							" and whodo = '" + whodo + "'";
						accessorDes.Execute(sql);
						hastop1star = false;
					}
					else if (managementphase != -1 && destablename != "a_practice")
					{
						string sql = "delete from " + destablename + " where elementid = " + wxString::Format("%d", deselementid).ToStdString() + \
							" and managementphase = " + wxString::Format("%d", managementphase).ToStdString();
						accessorDes.Execute(sql);
						hastop1star = false;
					}
				}
			}
		}
		if (!caninsert)
		{
			for (int j = 0; j < parameters.size(); j++)
			{
				delete parameters[j];
			}
			accessorSrc.MoveNext();
			continue;
		}
		if (isfirstcmd)
			cmd1 = "insert into " + destablename + "(";
		cmd2 = ") values(";
		for (int j = 0; j < destomovefields.size(); j++)
		{
			if (destomovefields[j].m_type <= 4)
			{
				if (isfirstcmd)
					cmd1 = cmd1 + destomovefields[j].m_name + ", ";
				if (sourcedata[j] != "")
				{
					cmd2 = cmd2 + sourcedata[j] + ", ";
				}
				else
				{
					cmd2 = cmd2 + "null, ";
				}
			}
			else
			{
				if (isfirstcmd)
					cmd1 = cmd1 + destomovefields[j].m_name + ", ";
				if ((destablename == "ref_sql_topic" && destomovefields[j].m_name == "wherecondition") ||
					(destablename == "d_well_variable" && destomovefields[j].m_name == "name"))
				{
					char *commacontent = new char[1024];
					int pos = 0;
					for (int k = 0; k < sourcedata[j].length(); k++)
					{
						if (sourcedata[j][k] != '\'')
							commacontent[pos] = sourcedata[j][k];
						else
						{
							commacontent[pos] = '\'';
							pos++;
							commacontent[pos] = '\'';
						}
						pos++;
					}
					string commacontentstr;
					commacontentstr.assign(commacontent, pos);
					cmd2 = cmd2 + "'" + commacontentstr + "', ";
					delete[] commacontent;
				}
				else
				{
					bool find = false;
					if (destomovefields[j].m_type == DBF_LongBinary && (accessorDes.m_impl->m_dbtype == AnyDB::DBS_MYSQL || accessorDes.m_impl->m_dbtype == AnyDB::DBS_SQLITE))
					{
						for (int k = 0; k < fieldnames.size(); k++)
						{
							if (fieldnames[k] == destomovefields[j].m_name)
							{
								find = true;
								cmd2 = cmd2 + "?, ";
								break;
							}
						}
					}
					if (!find)
						cmd2 = cmd2 + "'" + sourcedata[j] + "', ";
				}
			}
		}
		if (isfirstcmd)
			cmd1 = cmd1.substr(0, cmd1.length() - 2);
		cmd2 = cmd2.substr(0, cmd2.length() - 2);
		cmd2 = cmd2 + ")";
		cmd = cmd1 + cmd2;
		isfirstcmd = false;
		if (fieldnames.size() > 0 && (accessorDes.m_impl->m_dbtype != AnyDB::DBS_MYSQL && accessorDes.m_impl->m_dbtype != AnyDB::DBS_SQLITE))
		{
			if (!hastop1star)
			{
				string sql = "select top 1 * from " + destablename;
				if (accessorDes.IsMySQL() || accessorDes.IsSQLite())
					sql = "select * from " + destablename + " limit 1";
				accessorDes.Execute(sql, true);
				hastop1star = true;
			}
			std::vector<string> tmpfieldnames;
			std::vector<string> tmpdatas;
			for (int j = 0; j < destomovefields.size(); j++)
			{
				bool find = false;
				for (int k = 0; k < fieldnames.size(); k++)
				{
					if (destomovefields[j].m_name == fieldnames[k])
					{
						find = true;
						break;
					}
				}
				if (!find)
				{
					tmpfieldnames.push_back(destomovefields[j].m_name);
					tmpdatas.push_back(sourcedata[j]);
				}
			}
			for (int j = 0; j < fieldnames.size(); j++)
				tmpfieldnames.push_back(fieldnames[j]);
			bool rt = accessorDes.AddNewMultiblob(tmpfieldnames, tmpdatas, true, parameters, lens);
			assert(rt);
		}
		else if (fieldnames.size() > 0 && (accessorDes.m_impl->m_dbtype == AnyDB::DBS_MYSQL || accessorDes.m_impl->m_dbtype == AnyDB::DBS_SQLITE))
		{
			std::vector<unsigned long> lengths;
			for (int j = 0; j < lens.size(); j++)
				lengths.push_back(lens[j]);
			accessorDes.AppendBlobFieldSTMT(cmd, parameters, lengths);
		}
		else if (accessorDes.m_impl->m_dbtype != AnyDB::DBS_SQLSERVER)
		{
			bool rt = accessorDes.Execute(cmd);
			assert(rt);
			hastop1star = false;
		}
		else
		{
			bool rt = accessorDes.BatchInsert(cmd);
			assert(rt);
			hastop1star = false;
			if (i % 100 == 99)
				accessorDes.BatchInsertFlush();
		}
		for (int j = 0; j < parameters.size(); j++)
		{
			delete parameters[j];
		}
		accessorSrc.MoveNext();
	}
	accessorDes.BatchInsertFlush();
}
void MergeDataBaseFunction::InitMergeTables(void *accessorstar, std::vector<std::string> &tables, std::vector<bool> &isdirectcopytable)
{
	CAnyAccessor &accessor = *((CAnyAccessor*)accessorstar);
	tables.clear();
	isdirectcopytable.clear();
	tables.push_back("i_el");
	tables.push_back("i_el_evaluation");
	tables.push_back("i_el_factor");
	tables.push_back("i_el_horizon");
	tables.push_back("i_el_segment");
	tables.push_back("i_el_geology");
	tables.push_back("i_el_overall");
	tables.push_back("i_el_oversea_project");
	tables.push_back("i_el_repository");
	tables.push_back("i_el_reservoir");
	tables.push_back("i_el_resource");
	tables.push_back("i_el_resource_shale");
	tables.push_back("i_el_pool");
	tables.push_back("i_el_block_basic");
	tables.push_back("i_el_block_basin");
	tables.push_back("i_el_block_primarystructure");
	tables.push_back("i_el_block_secondrystructure");
	tables.push_back("i_el_block_thirdstructure");
	tables.push_back("i_el_block_unit_exploration");
	tables.push_back("i_el_cap");
	tables.push_back("i_el_check");
	tables.push_back("i_el_document");
	tables.push_back("i_el_source");
	tables.push_back("i_el_survey");
	tables.push_back("i_el_seismic_deploy");
	tables.push_back("i_el_seismic_picture");
	tables.push_back("i_el_preservation");
	tables.push_back("i_el_volume_sample");
	tables.push_back("i_el_volume_stat");
	tables.push_back("i_el_exploration");
	tables.push_back("i_el_trap");
	tables.push_back("i_el_trap_development");
	tables.push_back("i_el_trap_wildcat_drill");
	tables.push_back("i_el_trap_exploration");
	tables.push_back("i_el_trap_geology_fault");
	tables.push_back("i_el_trap_wildcat_post");
	tables.push_back("i_el_trap_project");
	tables.push_back("i_el_trap_reserve");
	tables.push_back("i_el_trap_reserve_discard");
	tables.push_back("i_el_trap_survey");
	tables.push_back("i_el_trap_wildcat_well");
	tables.push_back("r_property_cap_rock_type");
	tables.push_back("r_pgeo_basin_type");
	tables.push_back("r_pgeo_exploration_degree");
	tables.push_back("r_pgeo_formation_type");
	tables.push_back("r_pgeo_geographic_environment");
	tables.push_back("r_pgeo_play_type");
	tables.push_back("r_pgeo_structural_belt");
	tables.push_back("r_pgeo_tectonic_strength");
	tables.push_back("r_pgeo_thermal_history");
	tables.push_back("r_pgeo_trap_type");
	tables.push_back("r_ppsv_composition_type");
	tables.push_back("r_ppsv_fault_strength");
	tables.push_back("r_ppsv_migration_relation");
	tables.push_back("r_ppsv_migration_way");
	tables.push_back("r_ppsv_water_type");
	tables.push_back("r_prsv_diagenetic_phase");
	tables.push_back("r_prsv_pore_type");
	tables.push_back("r_prsv_rock_type");
	tables.push_back("r_prsv_space_type");
	tables.push_back("r_ps_face_type");
	tables.push_back("r_ps_organic_type");
	tables.push_back("r_ps_pathway_type");
	tables.push_back("r_ps_rock_type");
	tables.push_back("r_ps_supplyway_type");
	tables.push_back("a_practice");
	tables.push_back("a_practice_blobdata");
	tables.push_back("a_practice_table");
	tables.push_back("a_practice_tablecheck");
	tables.push_back("a_practice_score");
	tables.push_back("a_risk");
	tables.push_back("a_template_blob");
	tables.push_back("a_resource");
	tables.push_back("a_parameter");
	tables.push_back("a_resource_detail");
	tables.push_back("a_correlation");
	tables.push_back("a_jobstream");
	tables.push_back("a_npv_policy");
	tables.push_back("a_npv_scenario");
	tables.push_back("a_npv_risk");
	tables.push_back("a_npv_resource");
	tables.push_back("a_npv_edp_basic");
	tables.push_back("a_npv_edp_schedule");
	tables.push_back("a_npv_cost_basic");
	tables.push_back("a_npv_cost_detail");
	tables.push_back("a_npv_cost_mmbs");
	tables.push_back("a_npv_price");
	tables.push_back("a_npv_tax");
	tables.push_back("a_npv_summary");
	tables.push_back("a_repository_genetic");
	tables.push_back("a_repository_scenario");
	tables.push_back("a_repository_pfolio");
	tables.push_back("a_bayes_net_node");
	tables.push_back("a_bayes_net_branch");
	tables.push_back("a_decision_tree_node");
	tables.push_back("a_decision_tree_branch");
	tables.push_back("a_pb_tree_node");
	tables.push_back("a_pb_tree_branch");
	tables.push_back("a_well_performance_dre_middle");
	tables.push_back("a_well_performance_dre_result");
	tables.push_back("a_well_performance_practice");
	tables.push_back("ref_sql_topic");
	tables.push_back("ref_pick_system");
	tables.push_back("r_report_grid");
	tables.push_back("r_report_grid_template");
	tables.push_back("r_rh_template");
	tables.push_back("r_rh_where_condition_template");
	tables.push_back("r_rh_dimcol_template");
	tables.push_back("r_kida_category");
	tables.push_back("r_kida_theme");
	tables.push_back("r_kida_class");
	tables.push_back("r_kida_dataset");
	tables.push_back("d_well_basic");
	tables.push_back("d_well_basic_more");
	tables.push_back("d_well_atttable");
	tables.push_back("d_well_geochemical_para");
	tables.push_back("d_well_geometry");
	tables.push_back("d_well_bore");
	tables.push_back("d_well_trace");
	tables.push_back("d_well_pick");
	tables.push_back("d_well_zone");
	tables.push_back("d_well_variable");
	tables.push_back("d_well_volume_sample");
	tables.push_back("d_well_burial_history");
	tables.push_back("d_well_calibration");
	tables.push_back("d_well_fracture");
	tables.push_back("d_well_fault");
	tables.push_back("d_well_path");
	tables.push_back("d_well_cross_section");
	tables.push_back("d_well_image");
	tables.push_back("d_well_interpretation");
	tables.push_back("d_well_logging");
	tables.push_back("d_well_log_template");
	tables.push_back("d_well_mining_test");
	tables.push_back("d_well_oil_test");
	tables.push_back("d_well_performance_basic");
	tables.push_back("d_well_performance_casing");
	tables.push_back("d_well_performance_deployment");
	tables.push_back("d_well_performance_geological_parameter");
	tables.push_back("d_well_performance_pressure");
	tables.push_back("d_well_performance_pressure_gradient");
	tables.push_back("d_well_performance_production");
	tables.push_back("d_well_performance_trajectory");
	tables.push_back("d_well_performance_tubing");
	tables.push_back("d_well_production");
	tables.push_back("d_well_property");
	tables.push_back("d_well_shale_operation");
	tables.push_back("d_seismic_project");
	tables.push_back("d_seismic_2dg");
	tables.push_back("d_seismic_3dg");
	tables.push_back("d_seismic_dataset");
	tables.push_back("i_el_geometry");
	tables.push_back("i_el_raster");
	tables.push_back("d_seismic_gate");
	tables.push_back("d_seismic_surveyinfo");
	tables.push_back("d_seismic_surveyinfoblob");
	tables.push_back("d_seismic_headinfo");
	tables.push_back("d_seismic_profileinfo");
	tables.push_back("d_seismic_tracedata");
	tables.push_back("d_seismic_wavlet");
	tables.push_back("r_gis_style");
	tables.push_back("r_gis_layer_remark");
	tables.push_back("r_gis_chart");
	tables.push_back("r_gis_color_range");
	tables.push_back("d_seismic_ipt_em");
	tables.push_back("d_seismic_ipt_em_feature");
	tables.push_back("d_seismic_ipt_em_property");
	tables.push_back("d_ipt_fault_feature");
	tables.push_back("d_ipt_fault_geometry");
	tables.push_back("d_ipt_horizon_feature");
	tables.push_back("d_ipt_horizon_geometry");
	tables.push_back("d_contour_setting");
	tables.push_back("d_basinsimulate_model");
	tables.push_back("d_basinsimulate_draft");
	tables.push_back("d_basinsimulate_depthmap");
	tables.push_back("d_basinsimulate_facemap");
	tables.push_back("d_basinsimulate_horizon");
	tables.push_back("d_basinsimulate_layer");
	tables.push_back("d_basinsimulate_fault");
	tables.push_back("d_basinsimulate_boundary");
	tables.push_back("d_basinsimulate_setting");
	tables.push_back("ref_sys_user");
	tables.push_back("r_prefer_axis_template");
	tables.push_back("r_prefer_settings");
	tables.push_back("r_gis_sde_element");
	tables.push_back("r_seis_style");
	tables.push_back("r_well_rock");
	tables.push_back("r_gfs_masterrecord");
	tables.push_back("r_gfs_chunkuuid");
	tables.push_back("r_gfs_chunklocation");
	tables.push_back("r_gfs_geolocationgrid");
	tables.push_back("r_gis_projection");
	tables.push_back("r_gis_geographic_coordinate");
	tables.push_back("r_geo_litho");
	for (int i = 0; i < tables.size(); i++)
		isdirectcopytable.push_back(false);
	int tcount = accessor.GetTableCount();
	for (int i = 0; i < tcount; i++)
	{
		DBTableDesc tDesc;
		accessor.GetTableDesc(i, tDesc);
		bool find = false;
		for (int j = 0; j < tables.size(); j++)
		{
			if (tDesc.m_name == tables[j])
			{
				find = true;
				break;
			}
		}
		if (!find)
		{
			if (wxString(tDesc.m_name).StartsWith("d_well_trace_") || wxString(tDesc.m_name).StartsWith("d_well_pick_") || wxString(tDesc.m_name).StartsWith("d_well_zone_") || \
				wxString(tDesc.m_name).StartsWith("d_well_burial_history_") || wxString(tDesc.m_name).StartsWith("d_well_calibration_") || wxString(tDesc.m_name).StartsWith("d_well_fracture_") || \
				wxString(tDesc.m_name).StartsWith("d_well_image_") || wxString(tDesc.m_name).StartsWith("d_well_logging_") || wxString(tDesc.m_name).StartsWith("d_well_production_") || \
				wxString(tDesc.m_name).StartsWith("d_well_property_") || wxString(tDesc.m_name).StartsWith("d_well_shale_operation_") || wxString(tDesc.m_name).StartsWith("d_well_fault_") || \
				wxString(tDesc.m_name).StartsWith("d_well_path_") || wxString(tDesc.m_name).StartsWith("d_well_interpretation_") || wxString(tDesc.m_name).StartsWith("d_well_mining_test_") || \
				wxString(tDesc.m_name).StartsWith("d_well_oil_test_"))
			{
				tables.push_back(tDesc.m_name);
				isdirectcopytable.push_back(false);
			}
			else
			{
				if (tDesc.m_name != "ref_key_generator" && tDesc.m_name != "r_resource_kind" && tDesc.m_name != "r_resource_unit" &&
					tDesc.m_name != "r_resource_class" && tDesc.m_name != "r_probability" && tDesc.m_name != "r_pb_user" &&
					tDesc.m_name != "r_quick_template" && tDesc.m_name != "r_risk_factor" && tDesc.m_name != "r_quick_standard" &&
					tDesc.m_name != "r_fuzzy_standard" && tDesc.m_name != "r_quick_rule" && tDesc.m_name != "r_fuzzy_member" &&
					tDesc.m_name != "r_activity" && tDesc.m_name != "r_activity_template" && tDesc.m_name != "r_activity_menu" &&
					tDesc.m_name != "ref_database_version" && tDesc.m_name != "i_el_volume" && tDesc.m_name != "ref_table_version" &&
					tDesc.m_name != "ref_table_version_resume" && tDesc.m_name != "i_el_integrated_analysis" && tDesc.m_name != "i_el_trap_repository" &&
					tDesc.m_name != "ref_oilfields" && tDesc.m_name != "i_el_evaluation" && tDesc.m_name != "a_repository_port" && tDesc.m_name != "ref_lock_table" &&
					tDesc.m_name != "r_oversea_tableinfos" &&
					!wxString(tDesc.m_name).EndsWith("_backupver") && tDesc.m_name != "i_el_evaluation_view" && tDesc.m_name != "r_behar_kinetics")
				{
					tables.push_back(tDesc.m_name);
					isdirectcopytable.push_back(true);
				}
			}
		}
	}
}
void MergeDataBaseFunction::RepairInfoElementRecord(wxString &path, string currentusername, std::vector<int> &elementidsERROR)
{
	string defaltdatabase = CAnyAccessor::GetCurrentDB();
	CAnyAccessor::SwitchToDB(string(path));
	//string defaltusername = CAssessmentUserManager::getCurrentUserName();
	//CAssessmentUserManager::setCurrentUserName("admin");
	CAnyAccessor accessor;
	std::vector<int> elementids;
	std::vector<int> parentids;
	std::vector<string> elementnames;
	std::vector<int> alreadyallocate;
	std::vector<int> elementidsOK;
	elementidsERROR.clear();
	{
		char sentence[1024] = "select elementid, parentid from i_el";
		char sql[1024] = "";
		::sprintf(sql, sentence);
		bool rt = accessor.Execute(sql);
		if (rt)
		{
			for (int i = 0; i < accessor.GetRecordCount(); i++)
			{
				string temp = "";
				accessor.FetchField((long)0, temp);
				elementids.push_back(::atoi(temp.c_str()));
				accessor.FetchField((long)1, temp);
				parentids.push_back(::atoi(temp.c_str()));
				alreadyallocate.push_back(0);
				accessor.MoveNext();
			}
		}
	}
	for (int i = 0; i < parentids.size(); i++)
	{
		if (parentids[i] == 0)
		{
			elementidsOK.push_back(elementids[i]);
			alreadyallocate[i] = 1;
		}
	}
	while (elementidsOK.size() < elementids.size())
	{
		int lastcount = elementidsOK.size();
		for (int i = 0; i < parentids.size(); i++)
		{
			if (alreadyallocate[i] == 1)
				continue;
			for (int j = 0; j < elementidsOK.size(); j++)
			{
				if (parentids[i] == elementidsOK[j])
				{
					elementidsOK.push_back(elementids[i]);
					alreadyallocate[i] = 1;
					break;
				}
			}
		}
		if (lastcount == elementidsOK.size())
			break;
		else
			lastcount = elementidsOK.size();
	}
	for (int i = 0; i < elementids.size(); i++)
	{
		if (alreadyallocate[i] == 0)
			elementidsERROR.push_back(elementids[i]);
	}
	elementids.clear();
	{
		char sentence[1024] = "select elementid, name from i_el_evaluation_view where whodo = '%s' and type < 2 order by name, elementid";
		char sql[1024] = "";
		::sprintf(sql, sentence, currentusername.c_str());
		bool rt = accessor.Execute(sql);
		if (rt)
		{
			for (int i = 0; i < accessor.GetRecordCount(); i++)
			{
				string temp = "";
				accessor.FetchField((long)0, temp);
				elementids.push_back(::atoi(temp.c_str()));
				accessor.FetchField((long)1, temp);
				elementnames.push_back(temp.c_str());
				accessor.MoveNext();
			}
		}
	}
	int changetoid = 0;
	for (int i = 0; i < elementnames.size(); i++)
	{
		if (i > 0 && elementnames[i] == elementnames[i - 1])
		{
			int rangemin1 = 0;
			while (rangemin1 + pow(2.0, 25) <= changetoid)
				rangemin1 += pow(2.0, 25);
			int rangemin2 = 0;
			while (rangemin2 + pow(2.0, 25) <= elementids[i])
				rangemin2 += pow(2.0, 25);
			if (rangemin2 == rangemin1)
			{
				{
					char sentence[1024] = "update i_el set parentid = %d where parentid = %d";
					char sql[1024] = { 0, };
					::sprintf(sql, sentence, changetoid, elementids[i]);
					accessor.Execute(sql);
				}
				{
					char sentence[1024] = "update r_gis_sde_element set elementid = %d where elementid = %d";
					char sql[1024] = { 0, };
					::sprintf(sql, sentence, changetoid, elementids[i]);
					accessor.Execute(sql);
				}
				elementidsERROR.push_back(elementids[i]);
			}
			else
			{
				changetoid = elementids[i];
			}
		}
		else
		{
			changetoid = elementids[i];
		}
	}
	// repair i_el_factor 'whodo' field
	{
		char sentence[1024] = "update i_el_factor set whodo = 'admin' where whodo is null";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence);
		accessor.Execute(sql);
	}
	// whether is common is 'element' level, for 'template' value, always not common
	{
		char sentence[1024] = "update r_risk_factor set iscommon = 0";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence);
		accessor.Execute(sql);
	}
	CAnyAccessor::SwitchToDB(defaltdatabase);
	//CAssessmentUserManager::setCurrentUserName(defaltusername);
}
void MergeDataBaseFunction::RepairInfoElementRecordWhodo(wxString &path, string oldname, string newname)
{
	if (oldname == newname)
		return;
	string defaltdatabase = CAnyAccessor::GetCurrentDB();
	CAnyAccessor::SwitchToDB(string(path));
	//string defaltusername = CAssessmentUserManager::getCurrentUserName();
	//CAssessmentUserManager::setCurrentUserName("admin");
	{
		CAnyAccessor accessor;
		char sentence[1024] = "select * from i_el_evaluation where whodo = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str());
		bool rt = accessor.Execute(sql);
		if (rt && accessor.GetRecordCount())
		{
			CAnyAccessor::SwitchToDB(defaltdatabase);
			//CAssessmentUserManager::setCurrentUserName(defaltusername);
			return;
		}
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update i_el_evaluation set whodo = '%s' where whodo = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update i_el_factor set whodo = '%s' where whodo = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update i_el_repository set whodo = '%s' where whodo = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update i_el_document set whodo = '%s' where whodo = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update i_el_raster set whodo = '%s' where whodo = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update a_practice set whodo = '%s' where whodo = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update a_practice_score set whodo = '%s' where whodo = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update r_rh_template set username = '%s' where username = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update r_rh_dimcol_template set username = '%s' where username = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update r_rh_where_condition_template set username = '%s' where username = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update r_prefer_settings set whodo = '%s' where whodo = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update r_quick_template set whodo = '%s' where whodo = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		char sentence[1024] = "update r_well_rock set whodo = '%s' where whodo = '%s'";
		char sql[1024] = "";
		::sprintf(sql, sentence, newname.c_str(), oldname.c_str());
		accessor.Execute(sql);
	}
	{
		CAnyAccessor accessor;
		std::vector<int> classids;
		std::vector<string> usernames;
		{
			char sentence[1024] = "select classid, usernames from r_kida_class";
			char sql[1024] = "";
			::sprintf(sql, sentence);
			accessor.Execute(sql);
			for (int i = 0; i < accessor.GetRecordCount(); i++)
			{
				string temp = "";
				accessor.FetchField((long)0, temp);
				classids.push_back(::atoi(temp.c_str()));
				temp = "";
				accessor.FetchField((long)1, temp);
				usernames.push_back(temp.c_str());
				accessor.MoveNext();
			}
		}
		for (int i = 0; i < classids.size(); i++)
		{
			string newusername = "";
			if (usernames[i] == "")
			{
				newusername = newname + "@#";
			}
			else
			{
				std::vector<string> curuservec;
				int pos = 0;
				while ((pos = usernames[i].find("@#")) != std::string::npos)
				{
					string name = usernames[i].substr(0, pos);
					curuservec.push_back(name);
					usernames[i] = usernames[i].substr(pos + 2);
				}
				for (int j = 0; j < curuservec.size(); j++)
				{
					if (curuservec[j] == oldname)
					{
						newusername = newusername + newname + "@#";
					}
					else
					{
						newusername = newusername + curuservec[j] + "@#";
					}
				}
			}
			char sentence[1024] = "update r_kida_class set usernames = '%s' where classid = %d";
			char sql[1024] = "";
			::sprintf(sql, sentence, newusername.c_str(), classids[i]);
			accessor.Execute(sql);
		}
	}
	CAnyAccessor::SwitchToDB(defaltdatabase);
	//CAssessmentUserManager::setCurrentUserName(defaltusername);
}
void MergeDataBaseFunction::RepairElementTrapRecord(wxString &path)
{
	string defaltdatabase = CAnyAccessor::GetCurrentDB();
	CAnyAccessor::SwitchToDB(string(path));
	//string defaltusername = CAssessmentUserManager::getCurrentUserName();
	//CAssessmentUserManager::setCurrentUserName("admin");
	CAnyAccessor accessor;
	std::vector<string> tablenames;
	tablenames.push_back("i_el_trap");
	tablenames.push_back("i_el_trap_project");
	tablenames.push_back("i_el_trap_exploration");
	tablenames.push_back("i_el_trap_development");
	tablenames.push_back("i_el_trap_geology_fault");
	tablenames.push_back("i_el_trap_survey");
	std::vector<bool> dataexist;
	bool needmodify = false;
	for (int i = 0; i < tablenames.size(); i++)
	{
		char sentence[1024] = "select elementid from %s";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence, tablenames[i].c_str());
		bool rt = accessor.Execute(sql);
		if (rt && accessor.GetRecordCount())
			dataexist.push_back(true);
		else
		{
			dataexist.push_back(false);
			needmodify = true;
		}
	}
	if (needmodify)
	{
		std::map<int, int> elementid_parentid;
		std::map<int, int> elementid_elementtype;
		{
			char sentence[1024] = "select elementid, parentid, type from i_el";
			char sql[1024] = { 0, };
			::sprintf(sql, sentence);
			bool rt = accessor.Execute(sql);
			if (rt && accessor.GetRecordCount())
			{
				for (int i = 0; i < accessor.GetRecordCount(); i++)
				{
					string temp = "";
					accessor.FetchField((long)0, temp);
					int elementid = ::atoi(temp.c_str());
					accessor.FetchField((long)1, temp);
					int parentid = ::atoi(temp.c_str());
					accessor.FetchField((long)2, temp);
					int type = ::atoi(temp.c_str());
					elementid_parentid[elementid] = parentid;
					elementid_elementtype[elementid] = type;
					accessor.MoveNext();
				}
			}
		}
		for (std::map<int, int>::iterator iter = elementid_parentid.begin(); iter != elementid_parentid.end(); iter++)
		{
			/*int elementid = iter->first;
			if (elementid_elementtype[elementid] != CAccumulationElement::ET_Trap)
				continue;
			std::vector<int> parentchain;
			parentchain.push_back(elementid);
			int tempelementid = elementid;
			while (true)
			{
				if (elementid_parentid.find(tempelementid) == elementid_parentid.end())
					break;
				parentchain.push_back(elementid_parentid[tempelementid]);
				tempelementid = elementid_parentid[tempelementid];
			}
			bool isthridtrap = true;
			for (int j = parentchain.size() - 1; j >= 0; j--)
			{
				if (elementid_elementtype[parentchain[j]] == CAccumulationElement::ET_Trap)
				{
					if (j - 1 >= 0 && elementid_elementtype.find(parentchain[j - 1]) != elementid_elementtype.end() \
						&& elementid_elementtype[parentchain[j - 1]] == CAccumulationElement::ET_Trap)
						isthridtrap = false;
					break;
				}
			}
			if (isthridtrap)
			{
				for (int i = 0; i < tablenames.size(); i++)
				{
					if (dataexist[i])
						continue;
					int propertyid = accessor.NextKey("default", 100);
					char sentence[1024] = "insert into %s(propertyid, elementid) values (%d, %d)";
					char sql[1024] = { 0, };
					::sprintf(sql, sentence, tablenames[i].c_str(), propertyid, elementid);
					accessor.Execute(sql);
				}
			}*/
		}
	}
	CAnyAccessor::SwitchToDB(defaltdatabase);
	//CAssessmentUserManager::setCurrentUserName(defaltusername);
}
void MergeDataBaseFunction::RepairManagementphaseRecord(wxString &path)
{
	string defaltdatabase = CAnyAccessor::GetCurrentDB();
	CAnyAccessor::SwitchToDB(string(path));
	//string defaltusername = CAssessmentUserManager::getCurrentUserName();
	//CAssessmentUserManager::setCurrentUserName("admin");
	std::vector<string> tablenames;
	tablenames.push_back("i_el_volume_stat");
	tablenames.push_back("i_el_trap_project");
	tablenames.push_back("i_el_trap_reserve");
	tablenames.push_back("i_el_trap_reserve_discard");//
	tablenames.push_back("i_el_trap_survey");
	tablenames.push_back("i_el_trap");
	tablenames.push_back("i_el_trap_development");
	tablenames.push_back("i_el_trap_exploration");
	tablenames.push_back("i_el_trap_geology_fault");
	tablenames.push_back("a_practice");//
	tablenames.push_back("i_el_evaluation");//
	CAnyAccessor accessor;
	for (int i = 0; i < tablenames.size(); i++)
	{
		/*char sentence[1024] = "update %s set managementphase = %d where managementphase is null or managementphase = 0";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence, tablenames[i].c_str(), CAnyTrapManagement::TEP_Preliminary | CAnyTrapManagement::TRA_Preliminary_Found);
		bool rt = accessor.Execute(sql);*/
	}
	CAnyTimeBasic::TimeReport report;
	CAnyTimeBasic timeBasic;
	timeBasic.GetNow(report);
	double nowtime = report.m_year * 10000. + report.m_month * 100. + report.m_day + 0.01*report.m_hour + 0.0001 * report.m_minute;
	{
		char sentence[1024] = "update i_el_trap_project set fromdate = %f where fromdate is null or fromdate = 0";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence, nowtime);
		bool rt = accessor.Execute(sql);
	}
	{
		char sentence[1024] = "update i_el_trap_project set todate = %f where todate is null or todate = 0";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence, nowtime);
		bool rt = accessor.Execute(sql);
	}
	{
		char sentence[1024] = "update i_el_trap_exploration set discoverydate = %f where discoverydate is null or discoverydate = 0";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence, nowtime);
		bool rt = accessor.Execute(sql);
	}
	{
		char sentence[1024] = "update i_el_trap set trapsphasetype = 'Ⅰ' where trapsphasetype is null or trapsphasetype = ''";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence);
		bool rt = accessor.Execute(sql);
	}
	{
		char sentence[1024] = "update i_el_trap set trapsphasetype = 'Ⅰ' where trapsphasetype = 'I'";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence);
		bool rt = accessor.Execute(sql);
	}
	{
		char sentence[1024] = "update i_el_trap set trapsphasetype = 'Ⅱ' where trapsphasetype = 'II'";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence);
		bool rt = accessor.Execute(sql);
	}
	{
		char sentence[1024] = "update i_el_trap set trapsphasetype = 'Ⅲ' where trapsphasetype = 'III'";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence);
		bool rt = accessor.Execute(sql);
	}
	{
		char sentence[1024] = "update i_el_trap_wildcat_well set aprovalstatus = '报审' where aprovalstatus is null or aprovalstatus = ''";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence);
		bool rt = accessor.Execute(sql);
	}
	CAnyAccessor::SwitchToDB(defaltdatabase);
	//CAssessmentUserManager::setCurrentUserName(defaltusername);
}
void MergeDataBaseFunction::RepairGISCategoryRecord(wxString &path)
{
	string defaltdatabase = CAnyAccessor::GetCurrentDB();
	CAnyAccessor::SwitchToDB(string(path));
	//string defaltusername = CAssessmentUserManager::getCurrentUserName();
	//CAssessmentUserManager::setCurrentUserName("admin");
	CAnyAccessor accessor;
	std::vector<int> categoryids;
	std::vector<string> categorynames;
	std::vector<int> categoryidsERROR;
	{
		string sql;
		sql.reserve(1024);
		sql = "select categoryid, name from r_kida_category order by name";
		bool rt = accessor.Execute(sql);
		if (rt)
		{
			for (int i = 0; i < accessor.GetRecordCount(); i++)
			{
				string temp = "";
				accessor.FetchField((long)0, temp);
				categoryids.push_back(::atoi(temp.c_str()));
				accessor.FetchField((long)1, temp);
				categorynames.push_back(temp.c_str());
				accessor.MoveNext();
			}
		}
	}
	int changetoid = 0;
	for (int i = 0; i < categorynames.size(); i++)
	{
		if (i > 0 && categorynames[i] == categorynames[i - 1])
		{
			{
				char sentence[1024] = "update r_kida_class set categoryid = %d where categoryid = %d";
				char sql[1024] = { 0, };
				::sprintf(sql, sentence, changetoid, categoryids[i]);
				accessor.Execute(sql);
			}
			{
				char sentence[1024] = "update r_kida_category set categoryparentid = %d where categoryparentid = %d";
				char sql[1024] = { 0, };
				::sprintf(sql, sentence, changetoid, categoryids[i]);
				accessor.Execute(sql);
			}
			categoryidsERROR.push_back(categoryids[i]);
		}
		else
		{
			changetoid = categoryids[i];
		}
	}
	for (int i = 0; i < categoryidsERROR.size(); i++)
	{
		char sentence[1024] = "delete from r_kida_category where categoryid = %d";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence, categoryidsERROR[i]);
		accessor.Execute(sql);
	}
	CAnyAccessor::SwitchToDB(defaltdatabase);
	//CAssessmentUserManager::setCurrentUserName(defaltusername);
}
void MergeDataBaseFunction::RepairGISThemeRecord(wxString &path)
{
	string defaltdatabase = CAnyAccessor::GetCurrentDB();
	CAnyAccessor::SwitchToDB(string(path));
	//string defaltusername = CAssessmentUserManager::getCurrentUserName();
	//CAssessmentUserManager::setCurrentUserName("admin");
	CAnyAccessor accessor;
	std::vector<int> themeids;
	std::vector<string> themenames;
	std::vector<int> themeidsERROR;
	{
		string sql;
		sql.reserve(1024);
		sql = "select themeid, name from r_kida_theme order by name";
		bool rt = accessor.Execute(sql);
		if (rt)
		{
			for (int i = 0; i < accessor.GetRecordCount(); i++)
			{
				string temp = "";
				accessor.FetchField((long)0, temp);
				themeids.push_back(::atoi(temp.c_str()));
				accessor.FetchField((long)1, temp);
				themenames.push_back(temp.c_str());
				accessor.MoveNext();
			}
		}
	}
	int changetoid = 0;
	for (int i = 0; i < themenames.size(); i++)
	{
		if (i > 0 && themenames[i] == themenames[i - 1])
		{
			char sentence[1024] = "update r_kida_class set themeid = %d where themeid = %d";
			char sql[1024] = { 0, };
			::sprintf(sql, sentence, changetoid, themeids[i]);
			accessor.Execute(sql);
			themeidsERROR.push_back(themeids[i]);
		}
		else
		{
			changetoid = themeids[i];
		}
	}
	for (int i = 0; i < themeidsERROR.size(); i++)
	{
		char sentence[1024] = "delete from r_kida_theme where themeid = %d";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence, themeidsERROR[i]);
		accessor.Execute(sql);
	}
	CAnyAccessor::SwitchToDB(defaltdatabase);
	//CAssessmentUserManager::setCurrentUserName(defaltusername);
}
void MergeDataBaseFunction::RemoveOneElementRecord(wxString &path, int elementid)
{
	/*string defaltdatabase = CAnyAccessor::GetCurrentDB();
	CAnyAccessor::SwitchToDB(string(path));
	string defaltusername = CAssessmentUserManager::getCurrentUserName();
	CAssessmentUserManager::setCurrentUserName("admin");
	CAccumulationElement *element = new CAccumulationElement(0);
	CAccumulationElement::ElementRecord elementRecord = element->GetRecord();
	elementRecord.m_idx = elementid;
	element->SetRecord(elementRecord);
	element->SetIdx(elementid);
	CAnyAccessor accessor;
	accessor.SetShowInfoToWindow(false);
	element->DeleteAllElementActivities(accessor);
	element->DeleteAllElementActivitiesPractice(accessor);
	element->DeleteActivities();
	element->DeleteAllElementInfoXXData(accessor);
	accessor.SetShowInfoToWindow(true);
	element->Commit(true);
	delete element;
	element = NULL;
	CAnyAccessor::SwitchToDB(defaltdatabase);
	CAssessmentUserManager::setCurrentUserName(defaltusername);*/
}
void MergeDataBaseFunction::RepairGISClassRecord(wxString &path)
{
	string defaltdatabase = CAnyAccessor::GetCurrentDB();
	CAnyAccessor::SwitchToDB(string(path));
	//string defaltusername = CAssessmentUserManager::getCurrentUserName();
	//CAssessmentUserManager::setCurrentUserName("admin");
	CAnyAccessor accessor;
	std::vector<int> classids;
	std::vector<string> sources;
	std::vector<int> classidsERROR;
	std::vector<std::string> itemnames;
	std::vector<std::string> itemnamesERROR;
	{
		string sql;
		sql.reserve(1024);
		sql = "select classid, source, name from r_kida_class order by source";
		bool rt = accessor.Execute(sql);
		if (rt)
		{
			for (int i = 0; i < accessor.GetRecordCount(); i++)
			{
				string temp = "";
				accessor.FetchField((long)0, temp);
				classids.push_back(::atoi(temp.c_str()));
				accessor.FetchField((long)1, temp);
				sources.push_back(temp.c_str());
				accessor.FetchField((long)2, temp);
				itemnames.push_back(temp.c_str());
				accessor.MoveNext();
			}
		}
	}
	int currentid = 0;
	for (int i = 0; i < sources.size(); i++)
	{
		if (i > 0 && sources[i] == sources[i - 1])
		{
			classidsERROR.push_back(classids[i]);
			itemnamesERROR.push_back(itemnames[i]);
		}
		else
		{
			currentid = classids[i];
		}
	}
	for (int i = 0; i < classidsERROR.size(); i++)
	{
		{
			char sentence[1024] = "delete from i_el_raster where classid = %d";
			char sql[1024] = "";
			::sprintf(sql, sentence, classidsERROR[i]);
			accessor.Execute(sql);
		}
		{
			char sentence[1024] = "delete from i_el_geometry where classid = %d";
			char sql[1024] = "";
			::sprintf(sql, sentence, classidsERROR[i]);
			accessor.Execute(sql);
		}
		{
			char sentence[1024] = "delete from r_gis_style where classid = %d";
			char sql[1024] = "";
			::sprintf(sql, sentence, classidsERROR[i]);
			accessor.Execute(sql);
		}
		{
			char sentence[1024] = "delete from r_gis_layer_remark where classid = %d";
			char sql[1024] = "";
			::sprintf(sql, sentence, classidsERROR[i]);
			accessor.Execute(sql);
		}
		{
			char sentence[1024] = "delete from r_gis_chart where classid = %d";
			char sql[1024] = "";
			::sprintf(sql, sentence, classidsERROR[i]);
			accessor.Execute(sql);
		}
		{
			char sentence[1024] = "delete from r_gis_color_range where classid = %d";
			char sql[1024] = "";
			::sprintf(sql, sentence, classidsERROR[i]);
			accessor.Execute(sql);
		}
		//CAnyPetroData::DelGisSdeRecord(classidsERROR[i]);
		{
			//CAnySegyLayer::RemoveFromDB(classidsERROR[i], 0);
			//CAnySegyLayer::RemoveFromDB(classidsERROR[i], 1);
		}
		{
			std::vector<int> projectids;
			{
				char sentence[1024] = "select projectid from d_seismic_2dg where classid = %d";
				char sql[1024] = { 0, };
				::sprintf(sql, sentence, classidsERROR[i]);
				accessor.Execute(sql);
				for (int i = 0; i < accessor.GetRecordCount(sql); i++)
				{
					string temp = "";
					accessor.FetchField((long)0, temp);
					projectids.push_back(::atoi(temp.c_str()));
					accessor.MoveNext(sql);
				}
			}
			{
				char sentence[1024] = "select projectid from d_seismic_3dg where classid = %d";
				char sql[1024] = { 0, };
				::sprintf(sql, sentence, classidsERROR[i]);
				accessor.Execute(sql);
				for (int i = 0; i < accessor.GetRecordCount(sql); i++)
				{
					string temp = "";
					accessor.FetchField((long)0, temp);
					projectids.push_back(::atoi(temp.c_str()));
					accessor.MoveNext(sql);
				}
			}
			for (int i = 0; i < projectids.size(); i++)
			{
				char sentence[1024] = "delete from d_seismic_ipt_em where projectid = %d";
				char sql[1024] = "";
				::sprintf(sql, sentence, projectids[i]);
				accessor.Execute(sql);
			}
			for (int i = 0; i < projectids.size(); i++)
			{
				char sentence[1024] = "delete from d_seismic_ipt_em_feature where projectid = %d";
				char sql[1024] = "";
				::sprintf(sql, sentence, projectids[i]);
				accessor.Execute(sql);
			}
			for (int i = 0; i < projectids.size(); i++)
			{
				char sentence[1024] = "delete from d_seismic_ipt_em_property where projectid = %d";
				char sql[1024] = "";
				::sprintf(sql, sentence, projectids[i]);
				accessor.Execute(sql);
			}
		}
		{
			char sentence[1024] = "delete from r_kida_class where classid = %d";
			char sql[1024] = { 0, };
			::sprintf(sql, sentence, classidsERROR[i]);
			accessor.Execute(sql);
		}
		{
			//CAnyWellTable wt(itemnamesERROR[i]);
			//wt.DeleteWellDataByClassId(accessor, classidsERROR[i]);
		}
	}
	CAnyAccessor::SwitchToDB(defaltdatabase);
	//CAssessmentUserManager::setCurrentUserName(defaltusername);
}
void MergeDataBaseFunction::RepairRefUserRecord(wxString &path)
{
	string defaltdatabase = CAnyAccessor::GetCurrentDB();
	CAnyAccessor::SwitchToDB(string(path));
	//string defaltusername = CAssessmentUserManager::getCurrentUserName();
	//CAssessmentUserManager::setCurrentUserName("admin");
	CAnyAccessor accessor;
	std::vector<int> userids;
	std::vector<string> usernames;
	std::vector<int> useridsERROR;
	{
		string sql;
		sql.reserve(1024);
		sql = "select userid, name from ref_sys_user order by name";
		bool rt = accessor.Execute(sql);
		if (rt)
		{
			for (int i = 0; i < accessor.GetRecordCount(); i++)
			{
				string temp = "";
				accessor.FetchField((long)0, temp);
				userids.push_back(::atoi(temp.c_str()));
				accessor.FetchField((long)1, temp);
				usernames.push_back(temp.c_str());
				accessor.MoveNext();
			}
		}
	}
	for (int i = 0; i < usernames.size(); i++)
	{
		if (i > 0 && usernames[i] == usernames[i - 1])
		{
			useridsERROR.push_back(userids[i]);
		}
	}
	for (int i = 0; i < useridsERROR.size(); i++)
	{
		char sentence[1024] = "delete from ref_sys_user where userid = %d";
		char sql[1024] = { 0, };
		::sprintf(sql, sentence, useridsERROR[i]);
		accessor.Execute(sql);
	}
	CAnyAccessor::SwitchToDB(defaltdatabase);
	//CAssessmentUserManager::setCurrentUserName(defaltusername);
}
void MergeDataBaseFunction::FieldTypeToTXT(int databasetype, int fieldtype, int fieldlength, std::string &fieldtxt)
{
	if (databasetype == DBS_MDB)
	{
		if (fieldtype == DBF_Int)
			fieldtxt = "long";
		else if (fieldtype == DBF_Binary)
			fieldtxt = "byte";
		else if (fieldtype == DBF_Bool)
			fieldtxt = "long";
		else if (fieldtype == DBF_Date)
			fieldtxt = "datetime";
		else if (fieldtype == DBF_Float)
			fieldtxt = "float";
		else if (fieldtype == DBF_Text)
		{
			char sentence[1024] = " varchar(%d)";
			char sqlchar[1024] = "";
			::sprintf(sqlchar, sentence, fieldlength);
			fieldtxt = sqlchar;
		}
		else if (fieldtype == DBF_LongText)
			fieldtxt = "memo";
		else if (fieldtype == DBF_LongBinary)
			fieldtxt = "image";
		else
			fieldtxt = "varchar(255)";
	}
	else if (databasetype == DBS_SQLSERVER)
	{
		if (fieldtype == DBF_Int)
			fieldtxt = "int";
		else if (fieldtype == DBF_Binary)
			fieldtxt = "tinyint";
		else if (fieldtype == DBF_Bool)
			fieldtxt = "int";
		else if (fieldtype == DBF_Date)
			fieldtxt = "datetime";
		else if (fieldtype == DBF_Float)
			fieldtxt = "float";
		else if (fieldtype == DBF_Text)
		{
			char sentence[1024] = " varchar(%d)";
			char sqlchar[1024] = "";
			::sprintf(sqlchar, sentence, fieldlength);
			fieldtxt = sqlchar;
		}
		else if (fieldtype == DBF_LongText)
			fieldtxt = "text";
		else if (fieldtype == DBF_LongBinary)
			fieldtxt = "image";
		else
			fieldtxt = "varchar(255)";
	}
	else if (databasetype == DBS_MYSQL)
	{
		if (fieldtype == DBF_Int)
			fieldtxt = "integer";
		else if (fieldtype == DBF_Binary)
			fieldtxt = "tinyint";
		else if (fieldtype == DBF_Bool)
			fieldtxt = "integer";
		else if (fieldtype == DBF_Date)
			fieldtxt = "datetime";
		else if (fieldtype == DBF_Float)
			fieldtxt = "double";
		else if (fieldtype == DBF_Text)
		{
			char sentence[1024] = " nvarchar(%d)";
			char sqlchar[1024] = "";
			::sprintf(sqlchar, sentence, fieldlength);
			fieldtxt = sqlchar;
		}
		else if (fieldtype == DBF_LongText)
			fieldtxt = "text";
		else if (fieldtype == DBF_LongBinary)
			fieldtxt = "longblob";
		else
			fieldtxt = "nvarchar(255)";
	}
	else if (databasetype == DBS_SQLITE)
	{
		if (fieldtype == DBF_Int)
			fieldtxt = "integer";
		else if (fieldtype == DBF_Binary)
			fieldtxt = "integer";
		else if (fieldtype == DBF_Bool)
			fieldtxt = "integer";
		else if (fieldtype == DBF_Date)
			fieldtxt = "real";
		else if (fieldtype == DBF_Float)
			fieldtxt = "real";
		else if (fieldtype == DBF_Text)
			fieldtxt = "text";
		else if (fieldtype == DBF_LongText)
			fieldtxt = "text";
		else if (fieldtype == DBF_LongBinary)
			fieldtxt = "blob";
		else
			fieldtxt = "text";
	}
}