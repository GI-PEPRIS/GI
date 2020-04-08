// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

//
#include "db_solution_user_explorer_treectrl.h"

#include "wx/msgdlg.h"
#include "wx/generic/textdlgg.h"

#include "any/db/anykeygenerator.h"
using namespace AnyDB;

//
// menu schem against kinds of tree node
//
// root's sub menu schema
static const std::vector<wxString> kRootMenu = {"New Organization", "Commit"};
static const std::unordered_map<wxString, std::vector<wxString> > KRootMenuSchema = { \
{kRootMenu[0],{}}, \
{kRootMenu[1],{}}, \
};
static const std::unordered_map<wxString, wxObjectEventFunction> KRootMenuHandler = { \
{kRootMenu[0], wxCommandEventHandler(giDBUserExplorerTreeCtrl::OnRootMenu)}, \
{kRootMenu[1], wxCommandEventHandler(giDBUserExplorerTreeCtrl::OnRootMenu)}, \
};

//
// organization's menu schema
static const std::vector<wxString> kOrganizationMenu = {"New User", "Rename", "Remove"};
static const std::unordered_map<wxString, std::vector<wxString> > kOrganizationMenuSchema = { \
{kOrganizationMenu[0],{}}, \
{kOrganizationMenu[1],{}}, \
{kOrganizationMenu[2],{}}, \
};
static const std::unordered_map<wxString, wxObjectEventFunction> kOrganizationMenuHandler = { \
{kOrganizationMenu[0], wxCommandEventHandler(giDBUserExplorerTreeCtrl::OnOrganizationMenu)} , \
{kOrganizationMenu[1], wxCommandEventHandler(giDBUserExplorerTreeCtrl::OnOrganizationMenu)}, \
{kOrganizationMenu[2], wxCommandEventHandler(giDBUserExplorerTreeCtrl::OnOrganizationMenu)}, \
};

// user's menu schema
static const std::vector<wxString> kUserMenu = {"Rename", "Remove"};
static const std::unordered_map<wxString, std::vector<wxString> > kUserMenuSchema = { \
{kUserMenu[0],{}}, \
{kUserMenu[1],{}}, \
};
static const std::unordered_map<wxString, wxObjectEventFunction> kUserMenuHandler = { \
{kUserMenu[0], wxCommandEventHandler(giDBUserExplorerTreeCtrl::OnUserMenu)} , \
{kUserMenu[1], wxCommandEventHandler(giDBUserExplorerTreeCtrl::OnUserMenu)}, \
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
giDBUserExplorerTreeCtrl::giDBUserExplorerTreeCtrl(wxWindow *parent, const wxWindowID id, \
	const wxPoint& pos, const wxSize& size, wxString &name, long style) : \
	m_user_manager(giDBUserManager::GetUserManager()), \
	giDataExplorerTreeCtrl(parent, id, pos, size, name, style)
{
}

giDBUserExplorerTreeCtrl::~giDBUserExplorerTreeCtrl()
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void giDBUserExplorerTreeCtrl::DoCreateMenuSchema(UserTreeNodeItem* node_item, \
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
void giDBUserExplorerTreeCtrl::DoLoadTreeNodes()
{
	// root node
	DoLoadRootNode();
	// organization nodes
	DoLoadOrganizationNode();
	// user node
	DoLoadUserNode();
	// TODO:
	// feature node

	// common setting
	//for (int i = 0; i < m_nodes.size(); i++)
	//{
	//	m_nodes[i]->m_activated_function = static_cast<wxTreeEventFunction>(&giDBUserExplorerTreeCtrl::OnItemActivated);
	//}

	//
	std::sort(m_nodes.begin(), m_nodes.end(), \
		[](const TreeNodeItem *first, const TreeNodeItem *second) {return first->m_parent_id < second->m_parent_id; });
}

// root node
void giDBUserExplorerTreeCtrl::DoLoadRootNode()
{
	// basic 
	UserTreeNodeItem *node = new UserTreeNodeItem;
	node->m_id = 0;
	node->m_name = _("Orgnization");
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

// organization node
void giDBUserExplorerTreeCtrl::DoLoadOrganizationNode()
{
	for (int i = 0; i < m_user_manager.m_organization_records.size(); i++)
	{
		// node basic def
		UserTreeNodeItem *node = (UserTreeNodeItem *)DoAllocateNode<OrganizationRecord>(m_user_manager.m_organization_records[i]);

		// index
		// menu schema def
		DoCreateMenuSchema(node, kOrganizationMenu, kOrganizationMenuSchema, kOrganizationMenuHandler);
		m_nodes_map.insert(std::make_pair(node->m_name, node));
		m_nodes.push_back(node);
	}
}

// user node
void giDBUserExplorerTreeCtrl::DoLoadUserNode()
{
	for (int i = 0; i < m_user_manager.m_user_records.size(); i++)
	{
		// node basic def
		UserTreeNodeItem *node = (UserTreeNodeItem *)DoAllocateNode<UserRecord>(m_user_manager.m_user_records[i]);

		// index
		// menu schema def
		DoCreateMenuSchema(node, kUserMenu, kUserMenuSchema, kUserMenuHandler);
		m_nodes_map.insert(std::make_pair(node->m_name, node));
		m_nodes.push_back(node);
	}
}
void giDBUserExplorerTreeCtrl::DoUpdateTreeNode(TreeNodeItem *node_item)
{
	assert(dynamic_cast<UserTreeNodeItem*>(node_item));
	m_user_manager.UpdateRecord((UserTreeNodeItem*)node_item);
}

void giDBUserExplorerTreeCtrl::DoItemActivated(TreeNodeItem *node_def)
{
	wxMessageBox(_(wxT("Item Activated Event!")), _(wxT("GI Message")));
}

bool giDBUserExplorerTreeCtrl::IsDraggable(TreeNodeItem *from, TreeNodeItem *to)
{
	return (m_user_manager.IsUser(from->m_id) && m_user_manager.IsOrganization(to->m_id));
}
bool giDBUserExplorerTreeCtrl::IsMoveable(TreeNodeItem *from, TreeNodeItem *to)
{
	return ((m_user_manager.IsUser(from->m_id) && m_user_manager.IsUser(to->m_id)) || (m_user_manager.IsOrganization(from->m_id) && m_user_manager.IsOrganization(to->m_id)));
}
void giDBUserExplorerTreeCtrl::DoEndDrag(std::vector<TreeNodeItem *> &node_updated)
{
	//for (int i = 0; i < node_updated.size(); i++)
	{
		m_user_manager.UpdateRecord((UserTreeNodeItem*)node_updated[0]);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// event function
//
void giDBUserExplorerTreeCtrl::OnRootMenu(wxCommandEvent &event)
{
	MenuItem *sub_menu = dynamic_cast<MenuItem *>(event.GetEventUserData());
	assert(sub_menu);
	if (sub_menu->m_menu_name == kRootMenu[0]) // new organization
	{
		wxTextEntryDialog dialog(this, wxEmptyString, _("Please input name"), "New organization");
		if (dialog.ShowModal() == wxID_OK)
		{
			if (dialog.GetValue().IsEmpty() || m_nodes_map.find(dialog.GetValue()) != m_nodes_map.end())
			{
				wxMessageBox(_(wxT("There is the same name or the same isn't empty!")), _(wxT("GI Message")));
				return;
			}
			// update db
			const OrganizationRecord &organization = m_user_manager.InsertOrganization(dialog.GetValue(), sub_menu->m_host_node_idx);
			// menu schema def
			UserTreeNodeItem *node_item = (UserTreeNodeItem*)DoAllocateNode<OrganizationRecord>(organization);
			DoCreateMenuSchema(node_item, kOrganizationMenu, kOrganizationMenuSchema, kOrganizationMenuHandler);
			// update memory & tree
			DoAddTreeNode(this->GetFocusedItem(), node_item);
			Expand(GetFocusedItem());
		}
	}
	else if (sub_menu->m_menu_name == kRootMenu[1]) //commit
	{
		m_user_manager.Commit();
	}
}
void giDBUserExplorerTreeCtrl::OnOrganizationMenu(wxCommandEvent &event)
{
	MenuItem *sub_menu = dynamic_cast<MenuItem *>(event.GetEventUserData());
	assert(sub_menu);

	if (sub_menu->m_menu_name == kOrganizationMenu[0])//new user
	{
		wxTextEntryDialog dialog(this, wxEmptyString, _("Please input name"), "New user"); 
		if (dialog.ShowModal() == wxID_OK)
		{
			if (m_nodes_map.find(dialog.GetValue()) != m_nodes_map.end())
			{
				wxMessageBox(_(wxT("There is the same name!")), _(wxT("GI Message")));
				return;
			}
			// upate db
			const UserRecord &user = m_user_manager.InsertUser(dialog.GetValue(), sub_menu->m_host_node_idx);
			UserTreeNodeItem *node_item = (UserTreeNodeItem*)DoAllocateNode<UserRecord>(user);
			DoCreateMenuSchema(node_item, kUserMenu, kUserMenuSchema, kUserMenuHandler);
			DoAddTreeNode(GetFocusedItem(), node_item);
			Expand(GetFocusedItem());
		}
	}
	else if (sub_menu->m_menu_name == kOrganizationMenu[1])//rename
	{
		wxString curname = GetItemText(GetFocusedItem());
		wxTextEntryDialog dialog(this, wxEmptyString, _("Please input name"), "New name");
		if (dialog.ShowModal() == wxID_OK)
		{
			if (m_nodes_map.find(dialog.GetValue()) != m_nodes_map.end())
			{
				wxMessageBox(_(wxT("There is the same name!")), _(wxT("GI Message")));
				return;
			}
			// upate db
			OrganizationRecord &organization = m_user_manager.GetRecordByName<OrganizationRecord>(curname, m_user_manager.m_organization_records);
			organization.m_name = dialog.GetValue();
			UserTreeNodeItem *node_item = (UserTreeNodeItem*)DoAllocateNode<OrganizationRecord>(organization);
			m_user_manager.UpdateRecord(node_item);
			SetItemText(GetFocusedItem(), dialog.GetValue());
			m_nodes_map.erase(curname);
			m_nodes_map.insert(std::make_pair(dialog.GetValue(), node_item));
		}
	}
	else if (sub_menu->m_menu_name == kOrganizationMenu[2]) // remove
	{
		if (wxMessageBox(_(wxT("Are you sure to remove current organization?")), _(wxT("GI Message")), wxYES_NO) == wxYES)
		{
			std::vector<TreeNodeItem *> childs;
			DoDeleteTreeNode(this->GetFocusedItem(), childs);
			m_user_manager.DeleteRecord(sub_menu->m_host_node_idx);
			if (childs.size())
			{
				m_user_manager.UpdateRecord((UserTreeNodeItem*)childs[0]);
			}
		}
	}
}
void giDBUserExplorerTreeCtrl::OnUserMenu(wxCommandEvent &event)
{
	MenuItem *sub_menu = dynamic_cast<MenuItem *>(event.GetEventUserData());
	assert(sub_menu);
	if (sub_menu->m_menu_name == kUserMenu[0])//rename
	{
		wxString curname = GetItemText(GetFocusedItem());
		wxTextEntryDialog dialog(this, wxEmptyString, _("Please input name"), "New name");
		if (dialog.ShowModal() == wxID_OK)
		{
			if (m_nodes_map.find(dialog.GetValue()) != m_nodes_map.end())
			{
				wxMessageBox(_(wxT("There is the same name!")), _(wxT("GI Message")));
				return;
			}
			// upate db
			UserRecord &user = m_user_manager.GetRecordByName<UserRecord>(curname, m_user_manager.m_user_records);
			user.m_name = dialog.GetValue();
			UserTreeNodeItem *node_item = (UserTreeNodeItem*)DoAllocateNode<UserRecord>(user);
			m_user_manager.UpdateRecord(node_item);
			SetItemText(GetFocusedItem(), dialog.GetValue());
			m_nodes_map.erase(curname);
			m_nodes_map.insert(std::make_pair(dialog.GetValue(), node_item));
		}
	}
	else if (sub_menu->m_menu_name == kUserMenu[1]) // remove
	{
		if (wxMessageBox(_(wxT("Are you sure to remove current user?")), _(wxT("GI Message")), wxYES_NO) == wxYES)
		{
			std::vector<TreeNodeItem *> childs;
			DoDeleteTreeNode(this->GetFocusedItem(), childs);
			m_user_manager.DeleteRecord(sub_menu->m_host_node_idx);
			if (childs.size())
			{
				m_user_manager.UpdateRecord((UserTreeNodeItem*)childs[0]);
			}
		}
	}
}
