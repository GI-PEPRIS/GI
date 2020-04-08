// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_GIS_SOLUTION_MAPLAYER_MANAGER_H_
#define _GI_GUI_GIS_SOLUTION_MAPLAYER_MANAGER_H_

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
class giGISMapLayerManager
{
protected:
	//
	friend class giGISMapLayerExplorerTreeCtrl;
	friend class giDataFrame;

	//
	struct Hierachy
	{
		long m_id = -1;
		wxString m_name = "";

		// differencite parent id in category & theme in order to sort nodes in convinent way
		long m_parent_category_id = -1;
		long m_parent_theme_id = -1;

		//
		wxString m_remark;
	};

	// to specify research area extent & its geodetic & coordinate system
	// one category against the same specification
	struct CategoryRecord : public Hierachy
	{
		//
		bool m_is_activated = false;

		// foreign key
		long m_geographic_system_id = -1;
		long m_projected_system_id = -1;

		// location code
		wxString m_geographic_gridcode = "";
	};
	typedef std::vector<CategoryRecord> CategoryVector; // its order means list order

	// to organize map layers into the same topic and
	// could control the layers below one theme follow the same rendering rule
	struct ThemeRecord : public Hierachy
	{
	};
	typedef std::vector<ThemeRecord> ThemeVector;

	// map layer class and also as default rendering order
	// point, line, polygon, raster, contour, seismic survey, well, digital rock
	enum GIS_MapLayer_Class
	{
		GMLC_Unknown = -1,

		GMLC_Well,
		GMLC_Point,
		GMLC_Multi_Points,
		GMLC_Seismic_2D,
		GMLC_Seismic_3D,
		GMLC_Line,
		GMLC_Multi_Lines,
		GMLC_Contour,
		GMLC_Polygon,
		GMLC_Multi_Polys,
		GMLC_TIN,
		GMLC_Raster,
		GMLC_Digital_Rock,

		GMLC_Composite,
		GMLC_Max
	};
	struct MapLayerRecord : public Hierachy
	{
		//
		long m_parent_layer_id = -1; // as one of composite layer

		// foreign key
		long m_geographic_system_id = -1; // layer's standalone & source coord system, when imported, this maybe transfered into category specified
		long m_projected_system_id = -1;
		wxString m_geographic_gridcode = "";
		wxString m_datasource = ""; //maybe file path, maybe another database source

		// maybe indexed
		short m_feature_type = GMLC_Unknown;
		bool m_is_shown = true;
		bool m_can_selected = true;
		bool m_can_editted = true;

		//
		wxString m_related_layers = "";

		// rendering extent, default means no constraints
		float m_render_from_scale = 0.;
		float m_render_to_scale = 0.;

	};
	typedef std::vector<MapLayerRecord> MapLayerVector;

	struct MapLayerPropertyRecord
	{
		//primary key
		long m_layer_property_id;
		//
		long m_related_layer_id;
	};

	//
	struct MapLayerTreeNodeItem : giDataExplorerTreeCtrl::TreeNodeItem
	{
	};

public:
	//
	giGISMapLayerManager();
	virtual ~giGISMapLayerManager();

public:
	//
	const CategoryRecord &InsertCategory(const wxString &name, long parent_idx);
	const ThemeRecord &InsertTheme(const wxString &name, long parent_idx);
	const MapLayerRecord &InsertLayer(const wxString &name, long parent_idx);

	//
	void DeleteRecord(long id);
	void UpdateRecord(MapLayerTreeNodeItem *node_item);

	// to load all category, theme, layer records
	void Load();
	// current user could update cateory system
	bool Commit();

	//
	static giGISMapLayerManager &giGISMapLayerManager::GetLayerManager()
	{
		return SingletonHolder<giGISMapLayerManager, CreateUsingNew/*, NoDestroy*/>::Instance();
	}

	//
	bool IsCategory(long id);
	bool IsTheme(long id);
	bool IsMapLayer(long id);

private:
	//
	void DoLoadUserSchema(AnyDB::CAnyAccessor &accessor, std::vector<long> &category_ids, std::vector<long> &theme_ids, std::vector<long> &layer_ids);
	void DoLoadCategoryRecord(AnyDB::CAnyAccessor &accessor, const std::vector<long> &category_ids);
	void DoLoadThemeRecord(AnyDB::CAnyAccessor &accessor, const std::vector<long> &theme_ids);
	void DoLoadLayerRecord(AnyDB::CAnyAccessor &accessor, const std::vector<long> &layer_ids);

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

		// if T is theme or layer record 
		for (int i = 0; i < m_category_records.size(); i++)
		{
			if (m_category_records[i].m_id == parent_idx)
			{
				record.m_parent_category_id = parent_idx;
				break;
			}
		}
		// if T is theme or layer record
		for (int i = 0; i < m_theme_records.size(); i++)
		{
			if (m_theme_records[i].m_id == parent_idx)
			{
				record.m_parent_theme_id = parent_idx;
				break;
			}
		}

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
	bool DoUpdateRecord(MapLayerTreeNodeItem *node_item, std::vector<T> &records, std::vector<long> &ids_updated)
	{
		typedef std::vector<T>::iterator cat_itr;
		cat_itr itr = records.begin();
		for (; itr != records.end(); itr++)
		{
			if (itr->m_id == node_item->m_id)
			{
				itr->m_id = node_item->m_id;

				// if T is theme or layer record 
				itr->m_parent_category_id = node_item->m_parent_id;
				itr->m_parent_theme_id = node_item->m_parent_id;
				for (int i = 0; i < m_category_records.size(); i++)
				{
					if (m_category_records[i].m_id == node_item->m_parent_id)
					{
						//itr->m_parent_category_id = node_item->m_parent_id;
						itr->m_parent_theme_id = -1;
						break;
					}
				}
				// if T is theme or layer record
				for (int i = 0; i < m_theme_records.size(); i++)
				{
					if (m_theme_records[i].m_id == node_item->m_parent_id)
					{
						//itr->m_parent_theme_id = node_item->m_parent_id;
						itr->m_parent_category_id = -1;
						break;
					}
				}

				//
				itr->m_name = node_item->m_name;
				ids_updated.push_back(itr->m_id);
				return true;
			}
		}

		return false;
	}

protected:
	//
	wxString m_current_user;

	// butely & forcely to refresh db, even one kind of record is changed
	CategoryVector m_category_records;
	std::vector<long> m_update_category_ids;
	std::vector<long> m_insert_category_ids;
	std::vector<long> m_delete_category_ids;

	ThemeVector m_theme_records;
	std::vector<long> m_update_theme_ids;
	std::vector<long> m_insert_theme_ids;
	std::vector<long> m_delete_theme_ids;

	MapLayerVector m_layer_records;
	std::vector<long> m_update_layer_ids;
	std::vector<long> m_insert_layer_ids;
	std::vector<long> m_delete_layer_ids;
};

#endif

