// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_SOLUTION_EXPLORER_TREECTRL_H_
#define _GI_GUI_FRAMEWORK_SOLUTION_EXPLORER_TREECTRL_H_

#include "wx/treectrl.h"
#include "wx/event.h"

//
#include "any/base/anyobject.h"
#include "any/base/anymediator.h"
using namespace AnyBase;

#include "framework_data_event.h"

//
//
//
class giDataExplorerTreeCtrl : public wxTreeCtrl, \
	public CAnyObserver, public CAnyObservable, \
	public giDataEvent<giDataExplorerTreeCtrl, wxTreeEvent>
{
public:
	//
	struct MenuItem : public wxObject
	{
		long m_menu_idx;
		long m_parent_menu_idx;
		long m_host_node_idx;

		long m_image_idx;
		wxString m_menu_name;
		wxString m_host_node_name;

		//
		std::vector<MenuItem> m_children;

		//
		MenuItem() : m_menu_idx(0), m_parent_menu_idx(-1), m_host_node_idx(-1), m_menu_name(""), m_host_node_name("")
		{

		}
	};

	//
	enum NodeState
	{
		Node_Normal,
		Node_Selected,
		Node_Open			//???
	};

	//
	struct TreeNodeItem : public wxTreeItemData  
	{
		// basic
		wxString m_name;
		long m_id;
		wxTreeItemId m_id_from_tree;
		wxString m_tool_tip; //description or remark etc

		// tree id
		wxTreeItemId m_tree_item_location;

		// structure
		long m_parent_id;
		int m_cur_level;

		// subscript against image icons
		int m_image_id;
		int m_image_selected_id;

		// subscript of state icons
		int m_state_id;
		NodeState m_state;

		// dynamic generation of sub menus
		std::vector<MenuItem> m_menus_for_node;
		std::vector<MenuItem> m_menus_for_selections;

		// maybe assessment element, layer hook, etc
		CAnyObject *m_object_on_behalf;

		//
		//wxTreeEventFunction m_activated_function;

		//
		TreeNodeItem() : m_id(0), m_parent_id(-1), m_object_on_behalf(0), \
			m_image_id(0), m_image_selected_id(-1), m_state_id(0)
		{
		}
	};

	// node container
	typedef std::vector<TreeNodeItem*> NodeVector;
	typedef std::unordered_map<wxString, TreeNodeItem*> NodeNameMap; // quickly position

	// icon
	typedef std::pair<wxString, wxIcon*> IconEntry;
	typedef std::vector<IconEntry> IconVector;

public:
	//
	//
	giDataExplorerTreeCtrl(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, wxString &name, long style);
	virtual ~giDataExplorerTreeCtrl();

public:
	//
	void LoadNodeImageIcons(IconVector &item_icons, int size_demanded);
	void LoadNodeStateIcons(IconVector &item_icons, int size_demanded);

	long LoadTreeItems();

	//
	// observable & observer
	//
	void Update(short type, void *para){}
	void Notify(short type){}
	void Register(CAnyObserver *oneObserver){}

	//
	//
	//
	void OnExplorerTreeEvent(wxTreeEvent &event);	
	
	void OnItemMenu(wxTreeEvent *event);
	void OnItemActivated(wxTreeEvent *event);
	virtual void DoItemActivated(TreeNodeItem *node_def) = 0;

	void OnBeginDrag(wxTreeEvent *event);
	void OnEndDrag(wxTreeEvent *event);
	void OnBeginEditLabel(wxTreeEvent *event);
	void OnEndEditLabel(wxTreeEvent *event);
	void OnStateClick(wxTreeEvent *event);

protected:
	//
	virtual void DoLoadTreeNodes() = 0;
	virtual void DoAddTreeNode(wxTreeItemId &parent, TreeNodeItem *node_item);
	virtual void DoDeleteTreeNode(wxTreeItemId &focused, std::vector<TreeNodeItem *> &childs);
	virtual void DoUpdateTreeNode(TreeNodeItem *node_item) = 0;

	virtual bool IsDraggable(TreeNodeItem *from, TreeNodeItem *to) { return true; }
	virtual bool IsMoveable(TreeNodeItem *from, TreeNodeItem *to) { return false; };
	virtual void DoEndDrag(std::vector<TreeNodeItem *> &node_updated) = 0;

	//
	void DoReleaseIcons(IconVector &icons);
	void DoLoadIcons(IconVector &icons, wxImageList *images, int size);
	long DoGetIconId(const IconVector &icons, wxString &icon_name);

	//
	void ReleaseNode();


protected:
	// after 1000 for menu and item
	long m_explorer_event_id;

	// tree nodes
	NodeVector m_nodes; 
	NodeNameMap m_nodes_map;
	TreeNodeItem *m_root_node;

	//
	IconVector m_node_image_icons;
	IconVector m_node_state_icons;

	//
	wxArrayTreeItemIds m_ids_selected;
	wxString m_item_text_focused;
};

#endif