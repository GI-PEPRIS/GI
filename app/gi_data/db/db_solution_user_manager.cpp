// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

//
#include "db_solution_user_manager.h"
#include "framework/framework_data_app.h"

#include "any/db/anyaccessor.h"
using namespace AnyDB;

//
// initialize category schema
giDBUserManager::giDBUserManager()
{
	Load();
}

giDBUserManager::~giDBUserManager()
{
}

void giDBUserManager::Load()
{
	CAnyAccessor accessor;
	m_organization_records.clear();
	DoLoadOrganizationRecord(accessor);
	m_user_records.clear();
	DoLoadUserRecord(accessor);
}

bool giDBUserManager::IsOrganization(long id)
{
	for (int i = 0; i < m_organization_records.size(); i++)
	{
		if (m_organization_records[i].m_id == id)
		{
			return true;
		}
	}
	return false;
}

bool giDBUserManager::IsUser(long id)
{
	for (int i = 0; i < m_user_records.size(); i++)
	{
		if (m_user_records[i].m_id == id)
		{
			return true;
		}
	}
	return false;
}

//
void giDBUserManager::DeleteRecord(long id)
{
	if (DoDeleteRecord<OrganizationRecord>(id, m_organization_records, m_delete_organization_ids) || \
		DoDeleteRecord<UserRecord>(id, m_user_records, m_delete_user_ids))
	{
		return;
	}
}
void giDBUserManager::UpdateRecord(UserTreeNodeItem *node_item)
{
	if (DoUpdateRecord<OrganizationRecord>(node_item, m_organization_records, m_update_organization_ids) || \
		DoUpdateRecord<UserRecord>(node_item, m_user_records, m_update_user_ids))
	{
		return;
	}
}

void giDBUserManager::DoLoadOrganizationRecord(CAnyAccessor &accessor)
{
	std::string sql = "select orgid, parentorgid, orgname, remark from r_db_user_organization";
	bool rt = accessor.Execute(sql);
	long records = accessor.GetRecordCount();
	for (int i = 0; i < records; i++)
	{
		OrganizationRecord organization_record;
		std::string temp = "";
		accessor.FetchField((long)0, temp);
		organization_record.m_id = ::atoi(temp.c_str());
		accessor.FetchField((long)1, temp);
		organization_record.m_parentorgid = ::atoi(temp.c_str());
		accessor.FetchField((long)2, temp);
		organization_record.m_name = temp.c_str();
		accessor.FetchField((long)3, temp);
		organization_record.m_remark = temp.c_str();
		m_organization_records.push_back(organization_record);
		accessor.MoveNext();
	}
	std::sort(m_organization_records.begin(), m_organization_records.end(), \
		[](const OrganizationRecord &first, const OrganizationRecord &second) {return first.m_parentorgid < second.m_parentorgid; });
}

void giDBUserManager::DoLoadUserRecord(CAnyAccessor &accessor)
{
	std::string sql = "select userid, username, parentorgid, remark from r_db_user";
	bool rt = accessor.Execute(sql);
	long records = accessor.GetRecordCount();
	for (int i = 0; i < records; i++)
	{
		UserRecord user_record;
		std::string temp = "";
		accessor.FetchField((long)0, temp);
		user_record.m_id = ::atoi(temp.c_str());
		accessor.FetchField((long)1, temp);
		user_record.m_name = temp.c_str();
		accessor.FetchField((long)2, temp);
		user_record.m_parentorgid = ::atoi(temp.c_str());
		accessor.FetchField((long)3, temp);
		user_record.m_remark = temp.c_str();
		m_user_records.push_back(user_record);
		accessor.MoveNext();
	}
	std::sort(m_user_records.begin(), m_user_records.end(), \
		[](const UserRecord &first, const UserRecord &second) {return first.m_parentorgid < second.m_parentorgid; });
}
bool giDBUserManager::Commit()
{
	// against one connection
	CAnyAccessor accessor;
	// whether current user could control 
	if (!CanLock())
	{
		return false;
	}
	// TODO:
	// it had better to intersect those changes in order to decrease the access number
	// e.g, since those records be deleted, and they are no need to insert then be deleted asap
	// ...

	//
	CommitInsert(accessor);
	CommitUpdate(accessor);
	CommitDelete(accessor);

	//
	UnLock();

	return true;
}

//
//
const giDBUserManager::OrganizationRecord &giDBUserManager::InsertOrganization(const wxString &name, long parent_idx)
{
	OrganizationRecord &organization = DoInsertRecord<OrganizationRecord>(name, parent_idx, m_organization_records);
	m_insert_organization_ids.push_back(organization.m_id);
	assert(organization.m_parentorgid != -1);
	organization.m_parentorgid = parent_idx;
	return organization;
}
const giDBUserManager::UserRecord &giDBUserManager::InsertUser(const wxString &name, long parent_idx)
{
	UserRecord &user = DoInsertRecord<UserRecord>(name, parent_idx, m_user_records);
	m_insert_user_ids.push_back(user.m_id);
	assert(user.m_parentorgid != -1);
	user.m_parentorgid = parent_idx;
	return user;
}

//
//
//
bool giDBUserManager::CanLock()
{
	return true;
}

bool giDBUserManager::UnLock()
{
	return true;
}
//
//
void giDBUserManager::CommitInsert(AnyDB::CAnyAccessor &accessor)
{
	// insert organization
	for (int i = 0; i < m_insert_organization_ids.size(); i++)
	{
		const OrganizationRecord *record = GetRecord<OrganizationRecord>(m_insert_organization_ids[i], m_organization_records);
		assert(record);
		char sql_stmt[1024] = "insert into r_db_user_organization (orgid, parentorgid, orgname, remark) values (%d, %d, '%s', '%s')";
		char insert_organization[1024] = { 0, };
		::sprintf(insert_organization, sql_stmt, record->m_id, record->m_parentorgid, \
			record->m_name.ToStdString().c_str(), record->m_remark.ToStdString().c_str());
		bool rt = accessor.Execute(insert_organization);
		assert(rt);
	}
	m_insert_organization_ids.clear();
	// insert users
	for (int i = 0; i < m_insert_user_ids.size(); i++)
	{
		const UserRecord *record = GetRecord<UserRecord>(m_insert_user_ids[i], m_user_records);
		assert(record);
		char sql_stmt[1024] = "insert into r_db_user (userid, username, parentorgid, remark) values (%d, '%s', %d, '%s')";
		char insert_user[1024] = { 0, };
		::sprintf(insert_user, sql_stmt, record->m_id, record->m_name.ToStdString().c_str(), \
			record->m_parentorgid, record->m_remark.ToStdString().c_str());
		bool rt = accessor.Execute(insert_user);
		assert(rt);
	}
	m_insert_user_ids.clear();
}
void giDBUserManager::CommitUpdate(AnyDB::CAnyAccessor &accessor)
{
	for (int i = 0; i < m_update_organization_ids.size(); i++)
	{
		const OrganizationRecord *record = GetRecord<OrganizationRecord>(m_update_organization_ids[i], m_organization_records);
		assert(record);
		char sql_stmt[1024] = "update r_db_user_organization set orgname = '%s', parentorgid = %d, remark = '%s' where orgid = %d";
		char update_organization[1024] = "";
		::sprintf(update_organization, sql_stmt, record->m_name.ToStdString().c_str(), \
			record->m_parentorgid, record->m_remark.ToStdString().c_str(), m_update_organization_ids[i]);
		bool rt = accessor.Execute(update_organization);
		assert(rt);
	}
	m_update_organization_ids.clear();
	for (int i = 0; i < m_update_user_ids.size(); i++)
	{
		const UserRecord *record = GetRecord<UserRecord>(m_update_user_ids[i], m_user_records);
		assert(record);
		char sql_stmt[1024] = "update r_db_user set username = '%s', parentorgid = %d, remark = '%s' where userid = %d";
		char update_user[1024] = "";
		::sprintf(update_user, sql_stmt, record->m_name.ToStdString().c_str(), \
			record->m_parentorgid, record->m_remark.ToStdString().c_str(), m_update_user_ids[i]);
		bool rt = accessor.Execute(update_user);
		assert(rt);
	}
	m_update_user_ids.clear();
}
void giDBUserManager::CommitDelete(AnyDB::CAnyAccessor &accessor)
{
	for (int i = 0; i < m_delete_organization_ids.size(); i++)
	{
		char sql_stmt[1024] = "delete from r_db_user_organization where orgid = %d";
		char delete_organization[1024] = "";
		::sprintf(delete_organization, sql_stmt, m_delete_organization_ids[i]);
		bool rt = accessor.Execute(delete_organization);
		assert(rt);
	}
	m_delete_organization_ids.clear();
	for (int i = 0; i < m_delete_user_ids.size(); i++)
	{
		char sql_stmt[1024] = "delete from r_db_user where userid = %d";
		char delete_user[1024] = "";
		::sprintf(delete_user, sql_stmt, m_delete_user_ids[i]);
		bool rt = accessor.Execute(delete_user);
		assert(rt);
	}
	m_delete_user_ids.clear();
}