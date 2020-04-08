// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)
#include "gis_solution_maplayer_manager.h"
#include "framework/framework_data_app.h"

#include "any/db/anyaccessor.h"
using namespace AnyDB;

//
// initialize category schema
giGISMapLayerManager::giGISMapLayerManager()
{
	Load();
}

giGISMapLayerManager::~giGISMapLayerManager()
{
}

//
//
// to load all category, theme, layer records
void giGISMapLayerManager::Load()
{
	CAnyAccessor accessor;

	// 
	std::vector<long> category_ids;
	std::vector<long> theme_ids;
	std::vector<long> layer_ids;
	DoLoadUserSchema(accessor, category_ids, theme_ids, layer_ids);

	// TODO: can load in isolated threads
	//
	m_category_records.clear();
	if (category_ids.size())
	{
		DoLoadCategoryRecord(accessor, category_ids);
	}

	m_theme_records.clear();
	if (theme_ids.size())
	{
		DoLoadThemeRecord(accessor, theme_ids);
	}

	m_layer_records.clear();
	if (layer_ids.size())
	{
		DoLoadLayerRecord(accessor, layer_ids);
	}
}

bool giGISMapLayerManager::IsCategory(long id)
{
	for (int i = 0; i < m_category_records.size(); i++)
	{
		if (m_category_records[i].m_id == id)
		{
			return true;
		}
	}

	return false;
}

bool giGISMapLayerManager::IsTheme(long id)
{
	for (int i = 0; i < m_theme_records.size(); i++)
	{
		if (m_theme_records[i].m_id == id)
		{
			return true;
		}
	}

	return false;
}

bool giGISMapLayerManager::IsMapLayer(long id)
{
	for (int i = 0; i < m_layer_records.size(); i++)
	{
		if (m_layer_records[i].m_id == id)
		{
			return true;
		}
	}

	return false;
}

//
void giGISMapLayerManager::DeleteRecord(long id)
{
	if (DoDeleteRecord<CategoryRecord>(id, m_category_records, m_delete_category_ids) || \
		DoDeleteRecord<ThemeRecord>(id, m_theme_records, m_delete_theme_ids) ||
		DoDeleteRecord<MapLayerRecord>(id, m_layer_records, m_delete_layer_ids))
	{
		return;
	}
}
void giGISMapLayerManager::UpdateRecord(MapLayerTreeNodeItem *node_item)
{
	if (DoUpdateRecord<CategoryRecord>(node_item, m_category_records, m_update_category_ids) || \
		DoUpdateRecord<ThemeRecord>(node_item, m_theme_records, m_update_theme_ids) ||
		DoUpdateRecord<MapLayerRecord>(node_item, m_layer_records, m_update_layer_ids))
	{
		return;
	}
}

void giGISMapLayerManager::DoLoadUserSchema(CAnyAccessor &accessor, std::vector<long> &category_ids, std::vector<long> &theme_ids, std::vector<long> &layer_ids)
{
	DBSourceDesc db_desc;
	giTheApp(giDataApp).ReadDBConfig(db_desc);
	m_current_user = db_desc.m_user;

	char sql_stmt[1024] = "select \
								categoryid, \
								themeid, \
								maplayerid from r_gis_maplayer_user_relation where username like '%s'";
	char sql[1024] = "";
	::sprintf(sql, sql_stmt, db_desc.m_user.c_str());

	if (accessor.Execute(sql))
	{
		long records = accessor.GetRecordCount();
		for (int i = 0; i < records; i++)
		{
			std::string temp = "";
			accessor.FetchField((long)0, temp);
			if(::atoi(temp.c_str()) > 0)
				category_ids.push_back(::atoi(temp.c_str()));

			accessor.FetchField((long)1, temp);
			if (::atoi(temp.c_str()) > 0)
				theme_ids.push_back(::atoi(temp.c_str()));

			accessor.FetchField((long)2, temp);
			if (::atoi(temp.c_str()) > 0)
				layer_ids.push_back(::atoi(temp.c_str()));

			accessor.MoveNext();
		}
	}
}
void giGISMapLayerManager::DoLoadCategoryRecord(CAnyAccessor &accessor, const std::vector<long> &category_ids)
{
	//
	std::string sql = "select \
							categoryid, \
							categoryname, \
							parentcategoryid, \
							geographicsystemid, \
							projectedsystemid, \
							geographicgridcode, \
							isactivated from r_gis_maplayer_category";

	std::string where_sql = " where categoryid in (";
	for (int i= 0; i < category_ids.size(); i++)
	{
		char temp[20];
		::itoa(category_ids[i], temp, 10);
		string tempstr(temp);
		where_sql = where_sql + tempstr + ", ";
	}
	where_sql = where_sql.substr(0, where_sql.length() - 2);
	where_sql = where_sql + ")";
	sql += where_sql;

	//
	bool rt = accessor.Execute(sql);
	long records = accessor.GetRecordCount();
	for (int i = 0; i < records; i++)
	{
		CategoryRecord category_record;

		std::string temp = "";
		accessor.FetchField((long)0, temp);
		category_record.m_id = ::atoi(temp.c_str());

		accessor.FetchField((long)1, temp);
		category_record.m_name = temp.c_str();

		accessor.FetchField((long)2, temp);
		category_record.m_parent_category_id = ::atoi(temp.c_str());

		accessor.FetchField((long)3, temp);
		category_record.m_geographic_system_id = ::atoi(temp.c_str());

		accessor.FetchField((long)4, temp);
		category_record.m_projected_system_id = ::atoi(temp.c_str());

		accessor.FetchField((long)5, temp);
		category_record.m_geographic_gridcode = temp.c_str();

		accessor.FetchField((long)6, temp);
		category_record.m_is_activated = temp.c_str();

		m_category_records.push_back(category_record);
		accessor.MoveNext();
	}

	//
	std::sort(m_category_records.begin(), m_category_records.end(), \
		[](const CategoryRecord &first, const CategoryRecord &second) {return first.m_parent_category_id < second.m_parent_category_id; });
}
void giGISMapLayerManager::DoLoadThemeRecord(CAnyAccessor &accessor, const std::vector<long> &theme_ids)
{
	//
	std::string sql = "select \
							themeid, \
							themename, \
							parentthemeid, \
							parentcategoryid \
							from r_gis_maplayer_theme";
	std::string where_sql = " where themeid in (";
	for (int i = 0; i < theme_ids.size(); i++)
	{
		char temp[20];
		::itoa(theme_ids[i], temp, 10);
		string tempstr(temp);
		where_sql = where_sql + tempstr + ", ";
	}
	where_sql = where_sql.substr(0, where_sql.length() - 2);
	where_sql = where_sql + ")";
	sql += where_sql;

	//
	bool rt = accessor.Execute(sql);
	long records = accessor.GetRecordCount();
	for (int i = 0; i < records; i++)
	{
		ThemeRecord theme_record;

		std::string temp = "";
		accessor.FetchField((long)0, temp);
		theme_record.m_id = ::atoi(temp.c_str());

		accessor.FetchField((long)1, temp);
		theme_record.m_name = temp.c_str();

		accessor.FetchField((long)2, temp);
		theme_record.m_parent_theme_id = ::atoi(temp.c_str());

		accessor.FetchField((long)3, temp);
		theme_record.m_parent_category_id = ::atoi(temp.c_str());

		m_theme_records.push_back(theme_record);
		accessor.MoveNext();
	}

	// the default first sort order
	std::sort(m_theme_records.begin(), m_theme_records.end(), \
		[](const ThemeRecord &first, const ThemeRecord &second) {return first.m_parent_category_id < second.m_parent_category_id; });
}
void giGISMapLayerManager::DoLoadLayerRecord(CAnyAccessor &accessor, const std::vector<long> &layer_ids)
{
	//
	std::string sql = "select \
							layerid, \
							layername, \
							parentlayerid, \
							parentcategoryid, \
							parentthemeid, \
							geographicsystemid, \
							projectedsystemid, \
							geographicgridcode, \
							datasource, \
							featuretype, \
							isshown, \
							canselect, \
							canedit, \
							relatedlayers,\
							renderfromscale, \
							rendertoscale from r_gis_maplayer";

	std::string where_sql = " where layerid in (";
	for (int i = 0; i < layer_ids.size(); i++)
	{
		char temp[20];
		::itoa(layer_ids[i], temp, 10);
		string tempstr(temp);
		where_sql = where_sql + tempstr + ", ";
	}
	where_sql = where_sql.substr(0, where_sql.length() - 2);
	where_sql = where_sql + ")";
	sql += where_sql;

	//
	bool rt = accessor.Execute(sql);
	long records = accessor.GetRecordCount();
	for (int i = 0; i < records; i++)
	{
		MapLayerRecord layer_record;

		std::string temp = "";
		accessor.FetchField((long)0, temp);
		layer_record.m_id = ::atoi(temp.c_str());

		accessor.FetchField((long)1, temp);
		layer_record.m_name = temp.c_str();

		accessor.FetchField((long)2, temp);
		layer_record.m_parent_layer_id = ::atoi(temp.c_str());

		accessor.FetchField((long)3, temp);
		layer_record.m_parent_category_id = ::atoi(temp.c_str());

		accessor.FetchField((long)4, temp);
		layer_record.m_parent_theme_id = ::atoi(temp.c_str());

		accessor.FetchField((long)5, temp);
		layer_record.m_geographic_system_id = ::atoi(temp.c_str());

		accessor.FetchField((long)5, temp);
		layer_record.m_geographic_system_id = ::atoi(temp.c_str());

		accessor.FetchField((long)6, temp);
		layer_record.m_projected_system_id = ::atoi(temp.c_str());

		accessor.FetchField((long)7, temp);
		layer_record.m_geographic_gridcode = temp.c_str();

		accessor.FetchField((long)8, temp);
		layer_record.m_datasource = temp.c_str();

		accessor.FetchField((long)9, temp);
		layer_record.m_feature_type = ::atoi(temp.c_str());

		accessor.FetchField((long)10, temp);
		layer_record.m_is_shown = ::atoi(temp.c_str());

		accessor.FetchField((long)11, temp);
		layer_record.m_can_selected = ::atoi(temp.c_str());

		accessor.FetchField((long)12, temp);
		layer_record.m_can_editted = ::atoi(temp.c_str());

		accessor.FetchField((long)13, temp);
		layer_record.m_related_layers = temp.c_str();

		accessor.FetchField((long)14, temp);
		layer_record.m_render_from_scale = ::atof(temp.c_str());

		accessor.FetchField((long)15, temp);
		layer_record.m_render_to_scale = ::atof(temp.c_str());
		m_layer_records.push_back(layer_record);
		accessor.MoveNext();
	}

	// the default sort order
	std::sort(m_layer_records.begin(), m_layer_records.end(), \
		[](const MapLayerRecord &first, MapLayerRecord &second) {return first.m_parent_category_id < second.m_parent_category_id; });
}

// current user could update cateory system
bool giGISMapLayerManager::Commit()
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
}

//
//
const giGISMapLayerManager::CategoryRecord &giGISMapLayerManager::InsertCategory(const wxString &name, long parent_idx)
{
	CategoryRecord &category = DoInsertRecord<CategoryRecord>(name, parent_idx, m_category_records);
	m_insert_category_ids.push_back(category.m_id);
	assert(category.m_parent_category_id == -1);
	category.m_parent_category_id = parent_idx; 

	return category;
}
const giGISMapLayerManager::ThemeRecord &giGISMapLayerManager::InsertTheme(const wxString &name, long parent_idx)
{
	ThemeRecord &theme = DoInsertRecord<ThemeRecord>(name, parent_idx, m_theme_records);
	m_insert_theme_ids.push_back(theme.m_id);

	assert(theme.m_parent_category_id == -1 || theme.m_parent_theme_id == -1);
	assert(theme.m_parent_category_id >= 0 || theme.m_parent_theme_id >= 0);
	return theme;
}
const giGISMapLayerManager::MapLayerRecord &giGISMapLayerManager::InsertLayer(const wxString &name, long parent_idx)
{
	MapLayerRecord &layer = DoInsertRecord<MapLayerRecord>(name, parent_idx, m_layer_records);
	m_insert_layer_ids.push_back(layer.m_id);

	assert(layer.m_parent_category_id == -1 || layer.m_parent_theme_id == -1);
	assert(layer.m_parent_category_id >= 0 || layer.m_parent_theme_id >= 0);
	return layer;
}

//
//
//
bool giGISMapLayerManager::CanLock()
{
	return true;
}

bool giGISMapLayerManager::UnLock()
{
	return true;
}

//
//
void giGISMapLayerManager::CommitInsert(AnyDB::CAnyAccessor &accessor)
{
	// insert category
	for (int i = 0; i < m_insert_category_ids.size(); i++)
	{
		const CategoryRecord *record = GetRecord<CategoryRecord>(m_insert_category_ids[i], m_category_records);
		assert(record);

		{
			char sql_stmt[1024] = "insert into r_gis_maplayer_category ( \
				categoryid, \
				categoryname, \
				parentcategoryid, \
				geographicsystemid, \
				projectedsystemid, \
				geographicgridcode, \
				isactivated, \
				remark) values (\
				%d, \
				'%s',\
				%d, \
				%d, \
				%d, \
                '%s', \
				%d, \
				'%s')";
			char insert_relation[1024] = { 0, };
			::sprintf(insert_relation, sql_stmt, \
				record->m_id, \
				record->m_name.ToStdString().c_str(), \
				record->m_parent_category_id, \
				record->m_geographic_system_id, \
				record->m_projected_system_id, \
				record->m_geographic_gridcode.ToStdString().c_str(), \
				record->m_is_activated, \
				record->m_remark);

			bool rt = accessor.Execute(insert_relation);
			assert(rt);
		}

		//
		{
			char sql_stmt[1024] = "insert into r_gis_maplayer_user_relation ( \
				relationid, \
				userid, \
				username, \
				categoryid) values (\
				%d, \
				%d,\
				'%s', \
				%d)";
			char insert_relation[1024] = "";
			::sprintf(insert_relation, sql_stmt, \
				accessor.NextKey("default", 100), \
				- 1, \
				m_current_user.ToStdString().c_str(), \
				m_insert_category_ids[i]);

			bool rt = accessor.Execute(insert_relation);
			assert(rt);
		}
	}
	m_insert_category_ids.clear();

	// insert themes
	for (int i = 0; i < m_insert_theme_ids.size(); i++)
	{
		const ThemeRecord *record = GetRecord<ThemeRecord>(m_insert_theme_ids[i], m_theme_records);
		assert(record);

		{
			char sql_stmt[1024] = "insert into r_gis_maplayer_theme ( \
				themeid, \
				themename, \
				parentthemeid, \
				parentcategoryid, \
				remark) values (\
				%d, \
				'%s',\
				%d, \
				%d, \
				'%s')";
			char insert_relation[1024] = "";
			::sprintf(insert_relation, sql_stmt, \
				record->m_id, \
				record->m_name.ToStdString().c_str(), \
				record->m_parent_theme_id, \
				record->m_parent_category_id, \
				record->m_remark);

			bool rt = accessor.Execute(insert_relation);
			assert(rt);
		}

		//
		{
			char sql_stmt[1024] = "insert into r_gis_maplayer_user_relation ( \
				relationid, \
				userid, \
				username, \
				themeid) values (\
				%d, \
				%d,\
				'%s', \
				%d)";
			char insert_relation[1024] = "";
			::sprintf(insert_relation, sql_stmt, \
				accessor.NextKey("default", 100), \
				- 1, \
				m_current_user.ToStdString().c_str(), \
				m_insert_theme_ids[i]);

			bool rt = accessor.Execute(insert_relation);
			assert(rt);
		}
	}
	m_insert_theme_ids.clear();

	// insert layers
	for (int i = 0; i < m_insert_layer_ids.size(); i++)
	{
		const MapLayerRecord *record = GetRecord<MapLayerRecord>(m_insert_layer_ids[i], m_layer_records);
		assert(record);

		{
			char sql_stmt[1024] = "insert into r_gis_maplayer ( \
				layerid, \
				layername, \
				parentlayerid, \
				parentthemeid, \
				parentcategoryid, \
				geographicsystemid, \
				projectedsystemid, \
				geographicgridcode, \
				datasource, \
				featuretype, \
				isshown, \
				canselect, \
				canedit, \
				relatedlayers, \
				renderfromscale, \
				rendertoscale, \
				remark) values (\
				%d, \
				'%s',\
				%d, \
				%d,\
				%d, \
				%d,\
				%d, \
				'%s',\
				'%s', \
				%d,\
				%d, \
				%d,\
				%d, \
				'%s',\
				%f, \
				%f, \
				'%s')";
			char insert_relation[1024] = "";
			::sprintf(insert_relation, sql_stmt, \
				record->m_id, \
				record->m_name.ToStdString().c_str(), \
				record->m_parent_layer_id, \
				record->m_parent_theme_id, \
				record->m_parent_category_id, \
				record->m_geographic_system_id, \
				record->m_projected_system_id, \
				record->m_geographic_gridcode.ToStdString().c_str(), \
				record->m_datasource.ToStdString().c_str(), \
				record->m_feature_type, \
				record->m_is_shown, \
				record->m_can_selected, \
				record->m_can_editted, \
				record->m_related_layers.ToStdString().c_str(), \
				record->m_render_from_scale, \
				record->m_render_to_scale,
				record->m_remark.ToStdString().c_str());

			bool rt = accessor.Execute(insert_relation);
			assert(rt);
		}

		//
		{
			char sql_stmt[1024] = "insert into r_gis_maplayer_user_relation ( \
				relationid, \
				userid, \
				username, \
				maplayerid) values (\
				%d, \
				%d,\
				'%s', \
				%d)";
			char insert_relation[1024] = "";
			::sprintf(insert_relation, sql_stmt, \
				accessor.NextKey("default", 100), \
				- 1, \
				m_current_user.ToStdString().c_str(), \
				m_insert_layer_ids[i]);

			bool rt = accessor.Execute(insert_relation);
			assert(rt);
		}
	}
	m_insert_layer_ids.clear();

}

//
void giGISMapLayerManager::CommitUpdate(AnyDB::CAnyAccessor &accessor)
{
	// 
	for (int i = 0; i < m_update_category_ids.size(); i++)
	{
		const CategoryRecord *record = GetRecord<CategoryRecord>(m_update_category_ids[i], m_category_records);
		assert(record);

		char sql_stmt[1024] = "update r_gis_maplayer_category set \
				categoryname = '%s', \
				parentcategoryid = %d, \
				geographicsystemid = %d, \
				projectedsystemid = %d, \
				geographicgridcode = '%s', \
				isactivated = %d, \
				remark = '%s' where categoryid = %d";
		char update_category[1024] = "";
		::sprintf(update_category, sql_stmt, \
				record->m_name.ToStdString().c_str(), \
				record->m_parent_category_id, \
				record->m_geographic_system_id, \
				record->m_projected_system_id, \
				record->m_geographic_gridcode.ToStdString().c_str(), \
				record->m_is_activated, \
				record->m_remark.ToStdString().c_str(), \
				m_update_category_ids[i]);

		bool rt = accessor.Execute(update_category);
		assert(rt);
	}
	m_update_category_ids.clear();

	for (int i = 0; i < m_update_theme_ids.size(); i++)
	{
		const ThemeRecord *record = GetRecord<ThemeRecord>(m_update_theme_ids[i], m_theme_records);
		assert(record);

		char sql_stmt[1024] = "update r_gis_maplayer_theme set \
				themename = '%s', \
				parentthemeid = %d, \
				parentcategoryid = %d, \
				remark = '%s' where themeid = %d";
		char update_theme[1024] = "";
		::sprintf(update_theme, sql_stmt, \
				record->m_name.ToStdString().c_str(), \
				record->m_parent_theme_id, \
				record->m_parent_category_id, \
				record->m_remark.ToStdString().c_str(), \
				m_update_theme_ids[i]);

		bool rt = accessor.Execute(update_theme);
		assert(rt);
	}
	m_update_theme_ids.clear();

	//
	for (int i = 0; i < m_update_layer_ids.size(); i++)
	{
		const MapLayerRecord *record = GetRecord<MapLayerRecord>(m_update_layer_ids[i], m_layer_records);
		assert(record);

		char sql_stmt[1024] = "update r_gis_maplayer set \
				layername = '%s', \
				parentlayerid = %d, \
				parentthemeid = %d, \
				parentcategoryid = %d, \
				geographicsystemid = %d, \
				projectedsystemid = %d, \
				geographicgridcode = '%s', \
				datasource = '%s', \
				isshown = %d, \
				canselect = %d, \
				canedit = %d, \
				relatedlayers = '%s', \
				renderfromscale = %f, \
				rendertoscale = %f, \
				remark = '%s' where layerid = %d";

		char update_layer[1024] = "";
		::sprintf(update_layer, sql_stmt, \
			record->m_name.ToStdString().c_str(), \
			record->m_parent_layer_id, \
			record->m_parent_theme_id, \
			record->m_parent_category_id, \
			record->m_geographic_system_id, \
			record->m_projected_system_id, \
			record->m_geographic_gridcode.ToStdString().c_str(), \
			record->m_datasource.ToStdString().c_str(), \
			record->m_is_shown, \
			record->m_can_selected, \
			record->m_can_editted, \
			record->m_related_layers, \
			record->m_render_from_scale, \
			record->m_render_to_scale, \
			record->m_remark.ToStdString().c_str(), \
			m_update_layer_ids[i]);

		bool rt = accessor.Execute(update_layer);
		assert(rt);
	}
	m_update_layer_ids.clear();
}

void giGISMapLayerManager::CommitDelete(AnyDB::CAnyAccessor &accessor)
{
	// 
	for (int i = 0; i < m_delete_category_ids.size(); i++)
	{
		{
			char sql_stmt[1024] = "delete from r_gis_maplayer_category where categoryid = %d";
			char delete_category[1024] = "";
			::sprintf(delete_category, sql_stmt, m_delete_category_ids[i]);

			bool rt = accessor.Execute(delete_category);
			assert(rt);
		}

		{
			char sql_stmt[1024] = "delete from r_gis_maplayer_user_relation where categoryid = %d and username like '%s'";
			char delete_relation[1024] = "";
			::sprintf(delete_relation, sql_stmt, m_delete_category_ids[i], m_current_user.ToStdString().c_str());

			bool rt = accessor.Execute(delete_relation);
			assert(rt);
		}
	}
	m_delete_category_ids.clear();

	//
	for (int i = 0; i < m_delete_theme_ids.size(); i++)
	{
		{
			char sql_stmt[1024] = "delete from r_gis_maplayer_theme where themeid = %d";
			char delete_theme[1024] = "";
			::sprintf(delete_theme, sql_stmt, m_delete_theme_ids[i]);

			bool rt = accessor.Execute(delete_theme);
			assert(rt);
		}

		{
			char sql_stmt[1024] = "delete from r_gis_maplayer_user_relation where themeid = %d and username like '%s'";
			char delete_relation[1024] = "";
			::sprintf(delete_relation, sql_stmt, m_delete_theme_ids[i], m_current_user.ToStdString());

			bool rt = accessor.Execute(delete_relation);
			assert(rt);
		}
	}
	m_delete_theme_ids.clear();

	//
	for (int i = 0; i < m_delete_layer_ids.size(); i++)
	{
		{
			char sql_stmt[1024] = "delete from r_gis_maplayer where layerid = %d";
			char delete_layer[1024] = "";
			::sprintf(delete_layer, sql_stmt, m_delete_layer_ids[i]);

			bool rt = accessor.Execute(delete_layer);
			assert(rt);
		}

		{
			char sql_stmt[1024] = "delete from r_gis_maplayer_user_relation where maplayerid = %d and username like '%s'";
			char delete_relation[1024] = "";
			::sprintf(delete_relation, sql_stmt, m_delete_layer_ids[i], m_current_user.ToStdString());

			bool rt = accessor.Execute(delete_relation);
			assert(rt);
		}
	}
	m_delete_layer_ids.clear();
}