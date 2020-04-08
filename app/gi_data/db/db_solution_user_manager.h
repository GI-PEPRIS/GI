// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_DB_SOLUTION_USER_MANAGER_H_
#define _GI_GUI_DB_SOLUTION_USER_MANAGER_H_

//
#include "framework/framework_solution_explorer_treectrl.h"

//
#include "wx/string.h"

// Base package
#include "any/base/anyport.h"
#include "any/base/loki/singleton.h"
using namespace AnyBase::Loki;

namespace AnyDB
{
	class CAnyAccessor;
};



// singleton for all posible layer category definition
// TODO: should thread-safe
class giDBUserManager
{
protected:
	//
	friend class giDBUserExplorerTreeCtrl;
	friend class giDataFrame;

	struct Hierachy
	{
		long m_id = -1;
		wxString m_name = wxT("");
		long m_parentorgid = -1;
		wxString m_remark = wxT("");
	};

	struct OrganizationRecord : public Hierachy
	{
	};
	typedef std::vector<OrganizationRecord> OrganizationVector;

	struct UserRecord : public Hierachy
	{
	};
	typedef std::vector<UserRecord> UserVector;

	//
	struct UserTreeNodeItem : giDataExplorerTreeCtrl::TreeNodeItem
	{
	};

public:
	//
	giDBUserManager();
	virtual ~giDBUserManager();

public:
	//
	const OrganizationRecord &InsertOrganization(const wxString &name, long parent_idx);
	const UserRecord &InsertUser(const wxString &name, long parent_idx);


	//
	void DeleteRecord(long id);
	void UpdateRecord(UserTreeNodeItem *node_item);

	// to load all organization, user records
	void Load();
	bool Commit();

	//
	static giDBUserManager &giDBUserManager::GetUserManager()
	{
		return SingletonHolder<giDBUserManager, CreateUsingNew/*, NoDestroy*/>::Instance();
	}

	//
	bool IsOrganization(long id);
	bool IsUser(long id);

private:
	//
	void DoLoadOrganizationRecord(AnyDB::CAnyAccessor &accessor);
	void DoLoadUserRecord(AnyDB::CAnyAccessor &accessor);

	//
	bool CanLock();
	bool UnLock();

	//
	void CommitInsert(AnyDB::CAnyAccessor &accessor);
	void CommitUpdate(AnyDB::CAnyAccessor &accessor);
	void CommitDelete(AnyDB::CAnyAccessor &accessor);

	///
	template<class T>
	T &DoInsertRecord(const wxString &name, long parent_idx, std::vector<T> &records)
	{
		T record;
		CAnyAccessor accessor;
		record.m_id = accessor.NextKey("default", 100);
		record.m_name = name;
		record.m_parentorgid = parent_idx;
		records.push_back(record);
		return records[records.size() - 1];
	}
	//
	template<class T>
	const T *GetRecord(long id, const std::vector<T> &records)
	{
		// no need to sort then call std::find()
		// consider those inserted has bigger ids
		for (int i = records.size() - 1; i >= 0; i--)
		{
			if (records[i].m_id == id)
			{
				return &records[i];
			}
		}
		return 0;
	}
	//
	template<class T>
	bool DoDeleteRecord(long id, std::vector<T> &records, std::vector<long> &ids_deleted)
	{
		typedef std::vector<T>::iterator cat_itr;
		cat_itr itr = records.begin();
		for (; itr != records.end(); itr++)
		{
			if (itr->m_id == id)
			{
				ids_deleted.push_back(id);
				records.erase(itr);
				return true;
			}
		}
		return false;
	}
	template<class T>
	bool DoUpdateRecord(UserTreeNodeItem *node_item, std::vector<T> &records, std::vector<long> &ids_updated)
	{
		typedef std::vector<T>::iterator cat_itr;
		cat_itr itr = records.begin();
		for (; itr != records.end(); itr++)
		{
			if (itr->m_id == node_item->m_id)
			{
				itr->m_id = node_item->m_id;
				itr->m_parentorgid = node_item->m_parent_id;
				itr->m_name = node_item->m_name;
				ids_updated.push_back(itr->m_id);
				return true;
			}
		}
		return false;
	}
public:
	//
	template<class T>
	T &GetRecordByName(const wxString &name, std::vector<T> &records)
	{
		// no need to sort then call std::find()
		// consider those inserted has bigger ids
		for (int i = records.size() - 1; i >= 0; i--)
		{
			if (records[i].m_name == name)
			{
				return records[i];
			}
		}
		return records[0];
	}
protected:
	OrganizationVector m_organization_records;
	std::vector<long> m_update_organization_ids;
	std::vector<long> m_insert_organization_ids;
	std::vector<long> m_delete_organization_ids;
	UserVector m_user_records;
	std::vector<long> m_update_user_ids;
	std::vector<long> m_insert_user_ids;
	std::vector<long> m_delete_user_ids;
};

#endif