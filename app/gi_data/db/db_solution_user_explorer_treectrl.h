// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_DB_SOLUTION_USER_EXPLORER_TREECTRL_H_
#define _GI_GUI_DB_SOLUTION_USER_EXPLORER_TREECTRL_H_

#include "framework/framework_solution_explorer_treectrl.h"

#include "db_solution_user_manager.h"

//
//
//
class giDBUserExplorerTreeCtrl : public giDataExplorerTreeCtrl
{
	//
	typedef giDataExplorerTreeCtrl::TreeNodeItem TreeNodeItem;

	//
	typedef giDBUserManager::OrganizationRecord OrganizationRecord;
	typedef giDBUserManager::UserRecord UserRecord;
	typedef giDBUserManager::UserTreeNodeItem UserTreeNodeItem;


public:
	//
	giDBUserExplorerTreeCtrl(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, wxString &name, long style);
	~giDBUserExplorerTreeCtrl();
public:
	// define item menu function respectively , one menu, one short function
	void OnRootMenu(wxCommandEvent &event);
	void OnOrganizationMenu(wxCommandEvent &event);
	void OnUserMenu(wxCommandEvent &event);

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
	void DoLoadOrganizationNode();
	void DoLoadUserNode();

	//
	void DoCreateMenuSchema(UserTreeNodeItem* node_item, \
		const std::vector<wxString> &menus, \
		const std::unordered_map<wxString, std::vector<wxString> > &menu_schema, \
		const std::unordered_map<wxString, wxObjectEventFunction> &menu_handlers);

	//
	template<class T>
	UserTreeNodeItem *DoAllocateNode(const T& node_item)
	{
		// basic
		UserTreeNodeItem *node = new UserTreeNodeItem;
		node->m_id = node_item.m_id;
		node->m_name = node_item.m_name;
		node->m_parent_id = node_item.m_parentorgid;

		node->m_image_id = DoGetIconId(m_node_image_icons, wxString("hardname")); // TODO:
		node->m_image_selected_id = DoGetIconId(m_node_image_icons, wxString("hardname_selected")); // TODO:
		node->m_state_id = DoGetIconId(m_node_state_icons, wxString("checked"));

		return node;
	}


private:
	//
	giDBUserManager &m_user_manager;
};

#endif
