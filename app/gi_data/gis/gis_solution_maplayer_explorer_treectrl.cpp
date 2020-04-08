// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

//
#include "gis_solution_maplayer_explorer_treectrl.h"

#include "wx/msgdlg.h"
#include "wx/generic/textdlgg.h"

#include "any/db/anykeygenerator.h"
using namespace AnyDB;

//
// menu schem against kinds of tree node
//
// root's sub menu schema
static const std::vector<wxString> kRootMenu = { "Import...", "New Category", "#", "Commit" };
static const std::unordered_map<wxString, std::vector<wxString> > KRootMenuSchema = { \
{kRootMenu[0],{}}, \
{kRootMenu[1],{}}, \
{kRootMenu[2],{}}, \
{kRootMenu[3],{}}, \
};
static const std::unordered_map<wxString, wxObjectEventFunction> KRootMenuHandler = { \
{kRootMenu[0], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnRootMenu)}, \
{kRootMenu[1], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnRootMenu)}, \
{kRootMenu[2], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnRootMenu)}, \
{kRootMenu[3], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnRootMenu)}, \
};

//
// category's menu schema
static const std::vector<wxString> kCategoryMenu = { "New Theme", "Import", "Create Map Layer", "#", \
	"Rename", "Remove" , "#", \
	"Full Map Extent", "Turn Layers On", "Turn Layers Off", "#", \
	"Property"};
static const std::vector<wxString> kCategoryImportMenu = { "Map", "Contour", "Well", "2D Seimic", "3D Seismic", "Image", "Digital Rock" };
static const std::unordered_map<wxString, std::vector<wxString> > KCategoryMenuSchema = { \
{kCategoryMenu[0], {}} , \
{kCategoryMenu[1], kCategoryImportMenu }, \
{kCategoryMenu[2], {}}, \
{kCategoryMenu[3], {}}, \
{kCategoryMenu[4], {}}, \
{kCategoryMenu[5], {}}, \
{kCategoryMenu[6], {}}, \
{kCategoryMenu[7], {}}, \
{kCategoryMenu[8], {}}, \
{kCategoryMenu[9], {}}, \
{kCategoryMenu[10], {}}, \
{kCategoryMenu[11], {}}, \
};
static const std::unordered_map<wxString, wxObjectEventFunction> KCategoryMenuHandler = { \
// first menu
{kCategoryMenu[0], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)} , \
{kCategoryMenu[1], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kCategoryMenu[2], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kCategoryMenu[3], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kCategoryMenu[4], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kCategoryMenu[5], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kCategoryMenu[6], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kCategoryMenu[7], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kCategoryMenu[8], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kCategoryMenu[9], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kCategoryMenu[10], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kCategoryMenu[11], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \

// second(import) menu
{kCategoryImportMenu[0], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
{kCategoryImportMenu[1], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
{kCategoryImportMenu[2], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
{kCategoryImportMenu[3], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
{kCategoryImportMenu[4], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
{kCategoryImportMenu[5], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
{kCategoryImportMenu[6], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
};

//
// theme menu schema
static const std::vector<wxString> kThemeMenu = { "New Theme", "Import", "Create Map Layer", "#", \
	"Rename", "Remove" , "#", \
	"Full Map Extent", "Turn Layers On", "Turn Layers Off" };
static const const std::vector<wxString> kThemeImportMenu = { "Map", "Contour", "Well", "2D Seimic", "3D Seismic", "Image", "Digital Rock" };
static const std::unordered_map<wxString, std::vector<wxString> > KThemeMenuSchema = { \
{kThemeMenu[0],{}} , \
{kThemeMenu[1], kThemeImportMenu }, \
{kThemeMenu[2],{}}, \
{kThemeMenu[3],{}}, \
{kThemeMenu[4],{}}, \
{kThemeMenu[5], {}}, \
{kThemeMenu[6], {}}, \
{kThemeMenu[7], {}}, \
{kThemeMenu[8], {}}, 
{kThemeMenu[9],{}},
};
static const std::unordered_map<wxString, wxObjectEventFunction> KThemeMenuHandler = { \
// sub menu
{kThemeMenu[0], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)} , \
{kThemeMenu[1], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kThemeMenu[2], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kThemeMenu[3], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kThemeMenu[4], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kThemeMenu[5], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kThemeMenu[6], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kThemeMenu[7], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kThemeMenu[8], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \
{kThemeMenu[9], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryMenu)}, \


// import menu
{kThemeImportMenu[0], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
{kThemeImportMenu[1], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
{kThemeImportMenu[2], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
{kThemeImportMenu[3], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
{kThemeImportMenu[4], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
{kThemeImportMenu[5], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \
{kThemeImportMenu[6], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu)}, \

};

// maplayer including line, point, polygon etc menu schema
static const std::vector<wxString> kMapLayerMenu = { "Analysis...", "Configuration" , "Property Table", "#", \
"Rename", "Remove", "Copy", "Full Extent", "#", \
"Append...", "Is Picked", "Is Editted", "Clip", "#", \
"Versions", "#"};
//static const const std::vector<wxString> kMapLayerImportMenu = { "Map", "Contour", "Well", "2D Seimic", "3D Seismic", "Image", "Digital Rock" };
static const std::unordered_map<wxString, std::vector<wxString> > KMapLayerMenuSchema = { \
{kMapLayerMenu[0],{}} , \
{kMapLayerMenu[1], {} }, \
{kMapLayerMenu[2], {}}, \
{kMapLayerMenu[3], {} }, \
{kMapLayerMenu[4], {}}, \
{kMapLayerMenu[5], {} }, \
{kMapLayerMenu[6], {}}, \
{kMapLayerMenu[7], {} }, \
{kMapLayerMenu[8], {}}, \
{kMapLayerMenu[9], {} }, \
{kMapLayerMenu[10], {}}, \
{kMapLayerMenu[11], {} }, \
{kMapLayerMenu[12], {}}, \
{kMapLayerMenu[13], {} }, \
{kMapLayerMenu[14], {}}, \
{kMapLayerMenu[15], {} }, \
};
static const std::unordered_map<wxString, wxObjectEventFunction> KMapLayerMenuHandler = { \
// sub menu
{kMapLayerMenu[0], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)} , \
{kMapLayerMenu[1], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[2], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[3], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[4], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[5], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[6], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[7], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[8], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[9], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[10], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[11], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[12], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[13], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[14], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \
{kMapLayerMenu[15], wxCommandEventHandler(giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu)}, \

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
giGISMapLayerExplorerTreeCtrl::giGISMapLayerExplorerTreeCtrl(wxWindow *parent, const wxWindowID id, \
	const wxPoint& pos, const wxSize& size, wxString &name, long style) : \
	m_layer_manager(giGISMapLayerManager::GetLayerManager()), \
	giDataExplorerTreeCtrl(parent, id, pos, size, name, style)
{
}

giGISMapLayerExplorerTreeCtrl::~giGISMapLayerExplorerTreeCtrl()
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void giGISMapLayerExplorerTreeCtrl::DoCreateMenuSchema(MapLayerTreeNodeItem* node_item, \
	const std::vector<wxString> &menus, \
	const std::unordered_map<wxString, std::vector<wxString> > &menu_schema, \
	const std::unordered_map<wxString, wxObjectEventFunction> &menu_handlers)
{
	//
	typedef std::unordered_map<wxString, std::vector<wxString> >::const_iterator c_itr;
	for (int i = 0; i < menus.size(); i++)
	{
		c_itr menu_item_itr = menu_schema.find(menus[i]);

		MenuItem sub_menu;
		sub_menu.m_menu_idx = m_explorer_event_id++;
		sub_menu.m_menu_name = menu_item_itr->first;
		sub_menu.m_host_node_idx = node_item->m_id;
		sub_menu.m_host_node_name = node_item->m_name;

		if (menu_item_itr->second.size())
		{
			for (int j = 0; j < menu_item_itr->second.size(); j++)
			{
				MenuItem children_menu;
				children_menu.m_menu_idx = m_explorer_event_id++;
				children_menu.m_parent_menu_idx = sub_menu.m_menu_idx;
				children_menu.m_menu_name = menu_item_itr->second[j];
				children_menu.m_host_node_idx = node_item->m_id;
				children_menu.m_host_node_name = node_item->m_name;

				sub_menu.m_children.push_back(children_menu);
				Connect(children_menu.m_menu_idx, wxEVT_COMMAND_MENU_SELECTED, menu_handlers.find(children_menu.m_menu_name)->second, new MenuItem(children_menu));
			}
		}
		else
		{
			Connect(sub_menu.m_menu_idx, wxEVT_COMMAND_MENU_SELECTED, menu_handlers.find(sub_menu.m_menu_name)->second, new MenuItem(sub_menu));
		}

		node_item->m_menus_for_node.push_back(sub_menu);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// virtual functions
//
void giGISMapLayerExplorerTreeCtrl::DoLoadTreeNodes()
{
	// root node
	DoLoadRootNode();
	// category nodes
	DoLoadCategoryNode();
	// theme node
	DoLoadThemeNode();
	// layer node
	DoLoadLayerNode();
	// TODO:
	// feature node

	// common setting
	//for (int i = 0; i < m_nodes.size(); i++)
	//{
	//	m_nodes[i]->m_activated_function = static_cast<wxTreeEventFunction>(&giGISMapLayerExplorerTreeCtrl::OnItemActivated);
	//}

	//
	std::sort(m_nodes.begin(), m_nodes.end(), \
		[](const TreeNodeItem *first, const TreeNodeItem *second) {return first->m_parent_id < second->m_parent_id; });
}

// root node
void giGISMapLayerExplorerTreeCtrl::DoLoadRootNode()
{
	// basic 
	MapLayerTreeNodeItem *node = new MapLayerTreeNodeItem;
	node->m_id = 0;
	node->m_name = _("Map Layer");
	node->m_parent_id = -1;

	node->m_image_id = DoGetIconId(m_node_image_icons, wxString("hardname")); // TODO:
	node->m_image_selected_id = DoGetIconId(m_node_image_icons, wxString("hardname_selected")); // TODO:
	node->m_state_id = DoGetIconId(m_node_state_icons, wxString("checked"));

	// menu
	DoCreateMenuSchema(node, kRootMenu, KRootMenuSchema, KRootMenuHandler);

	//
	assert(!m_root_node);
	m_root_node = node;
	m_nodes_map.insert(std::make_pair(node->m_name, node));
	m_nodes.push_back(node);
}

// category node
void giGISMapLayerExplorerTreeCtrl::DoLoadCategoryNode()
{
	for (int i = 0; i < m_layer_manager.m_category_records.size(); i++)
	{
		// node basic def
		MapLayerTreeNodeItem *node = (MapLayerTreeNodeItem *)DoAllocateNode<CategoryRecord>(m_layer_manager.m_category_records[i]);

		// index
		// menu schema def
		DoCreateMenuSchema(node, kCategoryMenu, KCategoryMenuSchema, KCategoryMenuHandler);
		m_nodes_map.insert(std::make_pair(node->m_name, node));
		m_nodes.push_back(node);
	}
}

// theme node
void giGISMapLayerExplorerTreeCtrl::DoLoadThemeNode()
{
	for (int i = 0; i < m_layer_manager.m_theme_records.size(); i++)
	{
		MapLayerTreeNodeItem *node = (MapLayerTreeNodeItem *)DoAllocateNode<ThemeRecord>(m_layer_manager.m_theme_records[i]);
		
		// menu schema
		DoCreateMenuSchema(node, kThemeMenu, KThemeMenuSchema, KThemeMenuHandler);

		//
		m_nodes_map.insert(std::make_pair(node->m_name, node));
		m_nodes.push_back(node);
	}// theme records
}

// layer node
void giGISMapLayerExplorerTreeCtrl::DoLoadLayerNode()
{
	for (int i = 0; i < m_layer_manager.m_layer_records.size(); i++)
	{
		MapLayerTreeNodeItem *node = (MapLayerTreeNodeItem *)DoAllocateNode<MapLayerRecord>(m_layer_manager.m_layer_records[i]);


		//if (m_layer_manager.m_layer_records[i].m_feature_type == GIS_MapLayer_Class::GMLC_Line ||
		//	m_layer_manager.m_layer_records[i].m_feature_type == GIS_MapLayer_Class::GMLC_Point)
		{
			// menu schema
			DoCreateMenuSchema(node, kMapLayerMenu, KMapLayerMenuSchema, KMapLayerMenuHandler);
		}

		//
		m_nodes_map.insert(std::make_pair(node->m_name, node));
		m_nodes.push_back(node);
	}
}

void giGISMapLayerExplorerTreeCtrl::DoUpdateTreeNode(TreeNodeItem *node_item)
{
	assert(dynamic_cast<MapLayerTreeNodeItem*>(node_item));
	m_layer_manager.UpdateRecord((MapLayerTreeNodeItem*)node_item);
}

void giGISMapLayerExplorerTreeCtrl::DoItemActivated(TreeNodeItem *node_def)
{
	wxMessageBox(_(wxT("Item Activated Event!")), _(wxT("GI Message")));
}

bool giGISMapLayerExplorerTreeCtrl::IsDraggable(TreeNodeItem *from, TreeNodeItem *to) 
{ 
	return !((m_layer_manager.IsCategory(from->m_id) && m_layer_manager.IsTheme(to->m_id)) || \
		(m_layer_manager.IsCategory(from->m_id) && m_layer_manager.IsMapLayer(to->m_id)) || \
		(m_layer_manager.IsTheme(from->m_id) && m_layer_manager.IsMapLayer(to->m_id)));
}
bool giGISMapLayerExplorerTreeCtrl::IsMoveable(TreeNodeItem *from, TreeNodeItem *to)
{
	return ((m_layer_manager.IsCategory(from->m_id) && m_layer_manager.IsCategory(to->m_id)) || \
		(m_layer_manager.IsTheme(from->m_id) && m_layer_manager.IsTheme(to->m_id)) || \
		(m_layer_manager.IsMapLayer(from->m_id) && m_layer_manager.IsMapLayer(to->m_id)));
}
void giGISMapLayerExplorerTreeCtrl::DoEndDrag(std::vector<TreeNodeItem *> &node_updated)
{
	//for (int i = 0; i < node_updated.size(); i++)
	{
		m_layer_manager.UpdateRecord((MapLayerTreeNodeItem*)node_updated[0]);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// event function
//
void giGISMapLayerExplorerTreeCtrl::OnRootMenu(wxCommandEvent &event)
{
	MenuItem *sub_menu = dynamic_cast<MenuItem *>(event.GetEventUserData());
	assert(sub_menu);

	if (sub_menu->m_menu_name == kRootMenu[0]) // import
	{
		wxMessageBox(_(wxT("To list all category in different user, then pick one user!")), _(wxT("GI Message")));

	}
	else if (sub_menu->m_menu_name == kRootMenu[1]) // new category
	{
		// TODO: firstly to specify geographic coord system & projected coord system
		// ...
		//wxMessageBox(_(wxT("New category means to define geograph coord & projected coord!")), _(wxT("GI Message")));
		wxTextEntryDialog dialog(this, wxEmptyString, _("Please input name"), "New category");
		if (dialog.ShowModal() == wxID_OK)
		{
			if (dialog.GetValue().IsEmpty() || m_nodes_map.find(dialog.GetValue()) != m_nodes_map.end())
			{
				wxMessageBox(_(wxT("There is the same name or the same isn't empty!")), _(wxT("GI Message")));
				return;
			}

			// update db
			const CategoryRecord &category = m_layer_manager.InsertCategory(dialog.GetValue(), sub_menu->m_host_node_idx);
			// menu schema def
			MapLayerTreeNodeItem *node_item = (MapLayerTreeNodeItem*)DoAllocateNode<CategoryRecord>(category);
			DoCreateMenuSchema(node_item, kCategoryMenu, KCategoryMenuSchema, KCategoryMenuHandler);
			// update memory & tree
			DoAddTreeNode(this->GetFocusedItem(), node_item);
		}
	}
	else if (sub_menu->m_menu_name == kRootMenu[3]) //commit
	{
		m_layer_manager.Commit();
	}
}


//
void giGISMapLayerExplorerTreeCtrl::OnCategoryMenu(wxCommandEvent &event)
{
	MenuItem *sub_menu = dynamic_cast<MenuItem *>(event.GetEventUserData());
	assert(sub_menu);

	if (sub_menu->m_menu_name == kCategoryMenu[0])
	{
		//wxMessageBox(_(wxT("New theme means those layers belonging the same topic!")), _(wxT("GI Message")));
		// TODO: firstly to specify geographic coord system & projected coord system
		// ...
		//wxMessageBox(_(wxT("New category means to define geograph coord & projected coord!")), _(wxT("GI Message")));
		wxTextEntryDialog dialog(this, wxEmptyString, _("Please input name"), "New theme"); // new theme
		if (dialog.ShowModal() == wxID_OK)
		{
			if (m_nodes_map.find(dialog.GetValue()) != m_nodes_map.end())
			{
				wxMessageBox(_(wxT("There is the same name!")), _(wxT("GI Message")));
				return;
			}

			// upate db
			const ThemeRecord &theme = m_layer_manager.InsertTheme(dialog.GetValue(), sub_menu->m_host_node_idx);
			MapLayerTreeNodeItem *node_item = (MapLayerTreeNodeItem*)DoAllocateNode<ThemeRecord>(theme);
			DoCreateMenuSchema(node_item, kThemeMenu, KThemeMenuSchema, KThemeMenuHandler);
			DoAddTreeNode(GetFocusedItem(), node_item);
		}
	}
	else if (sub_menu->m_menu_name == kCategoryMenu[1])
	{
		assert(false);
	}
	else if (sub_menu->m_menu_name == kCategoryMenu[2]) // create map layer
	{
		//wxMessageBox(_(wxT("To create new map layer!")), _(wxT("GI Message")));
		//wxMessageBox(_(wxT("New theme means those layers belonging the same topic!")), _(wxT("GI Message")));
		// TODO: firstly to specify geographic coord system & projected coord system
		// ...
		//wxMessageBox(_(wxT("New category means to define geograph coord & projected coord!")), _(wxT("GI Message")));
		wxTextEntryDialog dialog(this, wxEmptyString, _("Please input name"), "New layer");
		if (dialog.ShowModal() == wxID_OK)
		{
			if (m_nodes_map.find(dialog.GetValue()) != m_nodes_map.end())
			{
				wxMessageBox(_(wxT("There is the same name!")), _(wxT("GI Message")));
				return;
			}

			// update db
			const MapLayerRecord &layer = m_layer_manager.InsertLayer(dialog.GetValue(), sub_menu->m_host_node_idx);
			MapLayerTreeNodeItem *node_item = (MapLayerTreeNodeItem*)DoAllocateNode<MapLayerRecord>(layer);
			DoCreateMenuSchema(node_item, kMapLayerMenu, KMapLayerMenuSchema, KMapLayerMenuHandler);
			// update tree
			DoAddTreeNode(GetFocusedItem(), node_item);
		}
	}
	else if (sub_menu->m_menu_name == kCategoryMenu[5]) // remove
	{
		if (wxMessageBox(_(wxT("Are you sure to remove current category?")), _(wxT("GI Message")), wxYES_NO) == wxYES)
		{
			std::vector<TreeNodeItem *> childs;
			DoDeleteTreeNode(this->GetFocusedItem(), childs);

			//
			m_layer_manager.DeleteRecord(sub_menu->m_host_node_idx);
			if(childs.size())
			{
				m_layer_manager.UpdateRecord((MapLayerTreeNodeItem*)childs[0]);
			}
		}
	}
}
void giGISMapLayerExplorerTreeCtrl::OnCategoryImportMenu(wxCommandEvent &event)
{
	MenuItem *children_menu = dynamic_cast<MenuItem *>(event.GetEventUserData());
	assert(children_menu);

	if (children_menu->m_menu_name == kCategoryImportMenu[0])
	{
		wxMessageBox(_(wxT("To import map layer")), _(wxT("GI Message")));
	}
}
void giGISMapLayerExplorerTreeCtrl::OnMapLayerMenu(wxCommandEvent &event)
{

}