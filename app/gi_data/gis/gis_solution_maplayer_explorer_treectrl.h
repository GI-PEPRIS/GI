// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_GIS_SOLUTION_MAPLAYER_EXPLORER_TREECTRL_H_
#define _GI_GUI_GIS_SOLUTION_MAPLAYER_EXPLORER_TREECTRL_H_

#include "framework/framework_solution_explorer_treectrl.h"

#include "gis_solution_maplayer_manager.h"

//
//
//
class giGISMapLayerExplorerTreeCtrl : public giDataExplorerTreeCtrl
{
	//
	typedef giDataExplorerTreeCtrl::TreeNodeItem TreeNodeItem;

	//
	typedef giGISMapLayerManager::CategoryRecord CategoryRecord;
	typedef giGISMapLayerManager::ThemeRecord ThemeRecord;
	typedef giGISMapLayerManager::MapLayerRecord MapLayerRecord;
	typedef giGISMapLayerManager::GIS_MapLayer_Class GIS_MapLayer_Class;
	typedef giGISMapLayerManager::MapLayerTreeNodeItem MapLayerTreeNodeItem;


public:
	//
	giGISMapLayerExplorerTreeCtrl(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, wxString &name, long style);
	~giGISMapLayerExplorerTreeCtrl();

public:
	//
	//
	//
public:	
	// define item menu function respectively , one menu, one short function
	void OnRootMenu(wxCommandEvent &event);

	void OnCategoryMenu(wxCommandEvent &event);
	void OnCategoryImportMenu(wxCommandEvent &event);

	//
	void OnMapLayerMenu(wxCommandEvent &event);

private:
	//
	//
	//
	virtual void DoLoadTreeNodes();
	virtual void DoItemActivated(TreeNodeItem *node_item);
	virtual bool IsDraggable(TreeNodeItem *from, TreeNodeItem *to);
	virtual bool IsMoveable(TreeNodeItem *from, TreeNodeItem *to);
	virtual void DoEndDrag(std::vector<TreeNodeItem *> &node_updated);
	virtual void DoUpdateTreeNode(TreeNodeItem *node_item);

	//
	//
	void DoLoadRootNode();
	void DoLoadCategoryNode();
	void DoLoadThemeNode();
	void DoLoadLayerNode();

	//
	void DoCreateMenuSchema(MapLayerTreeNodeItem* node_item, \
		const std::vector<wxString> &menus, \
		const std::unordered_map<wxString, std::vector<wxString> > &menu_schema, \
		const std::unordered_map<wxString, wxObjectEventFunction> &menu_handlers);

	//
	template<class T>
	MapLayerTreeNodeItem *DoAllocateNode(const T& node_item)
	{
		// basic
		MapLayerTreeNodeItem *node = new MapLayerTreeNodeItem;
		node->m_id = node_item.m_id;
		node->m_name = node_item.m_name;
		node->m_parent_id = node_item.m_parent_category_id != -1 ? node_item.m_parent_category_id : node_item.m_parent_theme_id;

		node->m_image_id = DoGetIconId(m_node_image_icons, wxString("hardname")); // TODO:
		node->m_image_selected_id = DoGetIconId(m_node_image_icons, wxString("hardname_selected")); // TODO:
		node->m_state_id = DoGetIconId(m_node_state_icons, wxString("checked"));

		return node;
	}

private:
	//
	giGISMapLayerManager &m_layer_manager;
};

#endif

