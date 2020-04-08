// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)
#include "framework_solution_explorer_treectrl.h"
#include "framework_data_macroes.h"

#include "wx/menu.h"
#include "wx/imaglist.h"
#include "wx/icon.h"
#include "wx/msgdlg.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
giDataExplorerTreeCtrl::giDataExplorerTreeCtrl(wxWindow *parent, const wxWindowID id, \
	const wxPoint& pos, const wxSize& size, wxString &name, long style) : m_explorer_event_id(id), m_root_node(0), \
	wxTreeCtrl(parent, id, pos, size, style)
{
	// event type from 10192, wxEVT_TREE_BEGIN_DRAG
	Connect(m_explorer_event_id, wxEVT_TREE_BEGIN_DRAG, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_BEGIN_DRAG, "BEGIN_DRAG");

	Connect(m_explorer_event_id, wxEVT_TREE_BEGIN_RDRAG, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_BEGIN_RDRAG, "BEGIN_RDRAG");

	Connect(m_explorer_event_id, wxEVT_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_BEGIN_LABEL_EDIT, "BEGIN_LABEL_EDIT");

	Connect(m_explorer_event_id, wxEVT_TREE_END_LABEL_EDIT, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_END_LABEL_EDIT, "END_LABEL_EDIT");

	Connect(m_explorer_event_id, wxEVT_TREE_DELETE_ITEM, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_DELETE_ITEM, "DELETE_ITEM");

	Connect(m_explorer_event_id, wxEVT_TREE_GET_INFO, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_GET_INFO, "GET_INFO");

	Connect(m_explorer_event_id, wxEVT_TREE_SET_INFO, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_SET_INFO, "SET_INFO");

	Connect(m_explorer_event_id, wxEVT_TREE_ITEM_EXPANDED, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_ITEM_EXPANDED, "ITEM_EXPANDED");

	Connect(m_explorer_event_id, wxEVT_TREE_ITEM_EXPANDING, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_ITEM_EXPANDING, "ITEM_EXPANDING");

	Connect(m_explorer_event_id, wxEVT_TREE_ITEM_COLLAPSED, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_ITEM_COLLAPSED, "TREE_COLLAPSED");

	Connect(m_explorer_event_id, wxEVT_TREE_ITEM_COLLAPSING, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_ITEM_COLLAPSING, "TREE_COLLAPSING");

	Connect(m_explorer_event_id, wxEVT_TREE_SEL_CHANGED, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_SEL_CHANGED, "SEL_CHANGED");

	Connect(m_explorer_event_id, wxEVT_TREE_SEL_CHANGING, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_SEL_CHANGING, "SEL_CHANGING");

	Connect(m_explorer_event_id, wxEVT_TREE_KEY_DOWN, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_KEY_DOWN, "KEY_DOWN");

	Connect(m_explorer_event_id, wxEVT_TREE_ITEM_ACTIVATED, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_ITEM_ACTIVATED, "ITEM_ACTIVATED");

	Connect(m_explorer_event_id, wxEVT_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_ITEM_RIGHT_CLICK, "RIGHT_CLICKED");

	Connect(m_explorer_event_id, wxEVT_TREE_ITEM_MIDDLE_CLICK, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_ITEM_MIDDLE_CLICK, "MIDDLE_CLICKED");

	Connect(m_explorer_event_id, wxEVT_TREE_END_DRAG, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_END_DRAG, "END_DRAG");

	Connect(m_explorer_event_id, wxEVT_TREE_STATE_IMAGE_CLICK, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_STATE_IMAGE_CLICK, "STATE_IMAGE_CLICK");

	Connect(m_explorer_event_id, wxEVT_TREE_ITEM_GETTOOLTIP, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_ITEM_GETTOOLTIP, "GETTOOLTIP");

	Connect(m_explorer_event_id, wxEVT_TREE_ITEM_MENU, wxTreeEventHandler(giDataExplorerTreeCtrl::OnExplorerTreeEvent));
	SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(id, wxEVT_TREE_ITEM_MENU, "ITEM_MENU");


}

giDataExplorerTreeCtrl::~giDataExplorerTreeCtrl()
{
	ReleaseNode();
}

void giDataExplorerTreeCtrl::ReleaseNode()
{
	this->DeleteAllItems();
	// below objects as client user data to referred above tree items 
	m_nodes.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void giDataExplorerTreeCtrl::LoadNodeImageIcons(IconVector &item_icons, int size_demanded)
{
	DoReleaseIcons(m_node_image_icons);
	if (size_demanded == -1)
	{
		return SetImageList(NULL);
	}
	m_node_image_icons.assign(item_icons.begin(), item_icons.end());

	// Make an image list containing small icons
	wxImageList *images = new wxImageList(size_demanded, size_demanded, true);
	DoLoadIcons(m_node_image_icons, images, size_demanded);

	// Inherited from its parent
	AssignImageList(images);
}
void giDataExplorerTreeCtrl::LoadNodeStateIcons(IconVector &item_icons, int size_demanded)
{
	DoReleaseIcons(m_node_state_icons);
	if (size_demanded == -1)
	{
		return SetStateImageList(NULL);
	}
	m_node_state_icons.assign(item_icons.begin(), item_icons.end());

	//
	wxImageList *states = new wxImageList(size_demanded, size_demanded, true);
	DoLoadIcons(m_node_state_icons,states,size_demanded);

	// Inherited from its parent
	AssignStateImageList(states);
}
inline void giDataExplorerTreeCtrl::DoReleaseIcons(IconVector &icons)
{
	for (int i = 0; i < icons.size(); i++)
	{
		delete icons[i].second;
	}
	icons.clear();
}
inline void giDataExplorerTreeCtrl::DoLoadIcons(IconVector &icons, wxImageList *images, int size)
{
	for (int i=0; i<icons.size(); i++)
	{
		int sizeOrig = icons[i].second->GetWidth();
		if (size == sizeOrig)
		{
			images->Add(*icons[i].second);
		}
		else
		{
			images->Add(wxBitmap(wxBitmap(*icons[i].second).ConvertToImage().Rescale(size, size)));
		}
	}
}
long giDataExplorerTreeCtrl::DoGetIconId(const IconVector &icons, wxString &node_name)
{
	for (int i = 0; i < icons.size(); i++)
	{
		if (icons[i].first.Upper().Contains(node_name.Upper()))
		{
			return i;
		}
	}
	return -1;
}

//
long giDataExplorerTreeCtrl::LoadTreeItems()
{
	//
	DeleteAllItems();
	// since each node is shared by treectrl, it no need to delete again
	m_nodes.clear();

	// to fill nodes vector and connect corresponding event function
	DoLoadTreeNodes();

	// brutely & forcely to construct tree using two level loops, simple
	if(m_nodes.size())
	{
		assert(m_nodes[0]->m_parent_id == -1);
		m_nodes[0]->m_id_from_tree = this->AddRoot(m_nodes[0]->m_name, m_nodes[0]->m_image_id, m_nodes[0]->m_image_selected_id, m_nodes[0]);

		std::function<void(TreeNodeItem *)> recursiveAppend;
		recursiveAppend = [this, &recursiveAppend](TreeNodeItem *parent)
		{
			for (int i = 0; i < m_nodes.size(); i++)
			{
				if (m_nodes[i]->m_parent_id == parent->m_id)
				{
					m_nodes[i]->m_id_from_tree = this->AppendItem(parent->m_id_from_tree, m_nodes[i]->m_name, \
						m_nodes[i]->m_image_id, m_nodes[i]->m_image_selected_id, (TreeNodeItem*)m_nodes[i]);
					recursiveAppend(m_nodes[i]);
				}
			}
		};

		recursiveAppend(m_nodes[0]);
	}

	//
	return m_nodes.size();
}

void giDataExplorerTreeCtrl::DoAddTreeNode(wxTreeItemId &parent, TreeNodeItem *node_item)
{
	assert(m_nodes_map.find(node_item->m_name) == m_nodes_map.end());
	this->AppendItem(parent, node_item->m_name, node_item->m_image_id, node_item->m_image_selected_id, node_item);

	m_nodes_map.insert(std::make_pair(node_item->m_name, node_item));
	m_nodes.push_back(node_item);
}



void giDataExplorerTreeCtrl::DoDeleteTreeNode(wxTreeItemId &focused, std::vector<TreeNodeItem *> &childs)
{
	wxTreeItemId parent = this->GetItemParent(focused);
	assert(parent.IsOk());

	//
	std::function<void(wxTreeItemId &, wxTreeItemId &)> recursiveMove;	
	recursiveMove = [this, &childs, &recursiveMove](wxTreeItemId &parent, wxTreeItemId &current) {
		wxTreeItemIdValue idvalue;
		wxTreeItemId child = GetFirstChild(current, idvalue);
		while (child.IsOk())
		{
			//
			TreeNodeItem *node_item = (TreeNodeItem*)this->GetItemData(child);
			node_item->m_parent_id = ((TreeNodeItem*)this->GetItemData(parent))->m_id;
			childs.push_back(node_item);

			//
			node_item->m_id_from_tree = this->AppendItem(parent, this->GetItemText(child), \
				this->GetItemImage(child), \
				this->GetItemState(child), node_item);
			this->SetItemData(child, 0);

			recursiveMove(node_item->m_id_from_tree, child);
			child = GetNextChild(current, idvalue);
		}
	};
	recursiveMove(parent, focused);
	
	//
	m_nodes_map.erase(this->GetItemText(focused));
	typedef NodeVector::iterator node_itr;
	node_itr itr = m_nodes.begin();
	for (; itr != m_nodes.end(); itr++)
	{
		if ((*itr)->m_id_from_tree == focused)
		{
			m_nodes.erase(itr);
			break;
		}
	}
	this->Delete(focused);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void giDataExplorerTreeCtrl::OnExplorerTreeEvent(wxTreeEvent &event)
{
	wxString &func_key = GetEventFunctionKey(event.GetId(),event.GetEventType());
	if (func_key.size())
	{
		(this->*EventFunctionTableGlobal()[func_key])(&event);
	}
}

//
//
void giDataExplorerTreeCtrl::OnItemMenu(wxTreeEvent *event)
{
	wxTreeItemId itemId = event->GetItem();
	if (!itemId.IsOk())
	{
		assert(false);
		return;
	}

	//m_lastId = itemId;
	SetFocusedItem(itemId);
	TreeNodeItem *node_item = itemId.IsOk() ? (TreeNodeItem *)GetItemData(itemId) : NULL;
	if (node_item)
	{
		wxArrayTreeItemIds selectids;
		GetSelections(selectids);	
		std::vector<MenuItem> &menu_items = selectids.size() > 1 ? node_item->m_menus_for_selections : node_item->m_menus_for_node;
		wxPoint clientpt = event->GetPoint();
		
		// TODO:
		// to define hierarchy menus given menu relation and set image
		// only support two level menu
		wxMenu menu;
		for (int i = 0; i < menu_items.size(); i++)
		{
			//
			if (menu_items[i].m_parent_menu_idx != -1)
			{
				continue;
			}

			//
			MenuItem &menu_item = menu_items[i];
			if (menu_item.m_menu_name == wxString("#"))
			{
				menu.AppendSeparator();
			}
			else if (menu_item.m_children.size()) 
			{
				wxMenu *child_menu = new wxMenu;
				for (int j = 0; j < menu_item.m_children.size(); j++)
				{
					child_menu->Append(menu_item.m_children[j].m_menu_idx, _(menu_item.m_children[j].m_menu_name));
				}
				menu.AppendSubMenu(child_menu, menu_item.m_menu_name);
			}
			else
			{
				menu.Append(menu_item.m_menu_idx, _(menu_item.m_menu_name));
			}
		}

		PopupMenu(&menu, clientpt);
	}
	event->Skip();
}
SOLUTION_EXPLORER_REGISTER_EVENT_FUNC(wxEVT_TREE_ITEM_MENU, "ITEM_MENU", OnItemMenu, &giDataExplorerTreeCtrl::OnItemMenu);

//
void giDataExplorerTreeCtrl::OnItemActivated(wxTreeEvent *event)
{
	wxTreeItemId itemId = event->GetItem();
	if (!itemId.IsOk())
	{
		assert(false);
		return;
	}

	TreeNodeItem *node_item = itemId.IsOk() ? (TreeNodeItem *)GetItemData(itemId) : NULL;
	DoItemActivated(node_item);
	//(this->*node_item->m_activated_function)(*event);
}
SOLUTION_EXPLORER_REGISTER_EVENT_FUNC(wxEVT_TREE_ITEM_ACTIVATED, "ITEM_ACTIVATED", OnItemActivated, &giDataExplorerTreeCtrl::OnItemActivated);

void giDataExplorerTreeCtrl::OnBeginDrag(wxTreeEvent *event)
{
	if (event->GetItem() != GetRootItem())
	{
		this->GetSelections(m_ids_selected);
		assert(m_ids_selected[0] == event->GetItem());

		event->Allow();
	}
}
SOLUTION_EXPLORER_REGISTER_EVENT_FUNC(wxEVT_TREE_BEGIN_DRAG, "BEGIN_DRAG", OnBeginDrag, &giDataExplorerTreeCtrl::OnBeginDrag);

void giDataExplorerTreeCtrl::OnEndDrag(wxTreeEvent *event)
{
	wxTreeItemId end_node = event->GetItem();
	if (!end_node.IsOk() || \
		!IsDraggable((TreeNodeItem*)this->GetItemData(m_ids_selected[0]), (TreeNodeItem*)this->GetItemData(end_node)))
	{
		wxMessageBox(_(wxT("It doesn't permit such drag action!")), _(wxT("GI Message")));
		return;
	}
	// TODO:
	// to recognize whether from node is prev to to node, or else
	// ...
	bool is_insert_below = IsMoveable((TreeNodeItem*)this->GetItemData(m_ids_selected[0]), (TreeNodeItem*)this->GetItemData(end_node));

	// TODO:
	// it is no need to update children of focused
	std::vector<TreeNodeItem *> nodes_updated;
	for (int i = 0; i < m_ids_selected.size(); i++)
	{
		wxTreeItemId begin_node = m_ids_selected[i];

		static std::function<void(wxTreeItemId &, wxTreeItemId &)> recursiveMove;
		recursiveMove = [this, &nodes_updated, &is_insert_below](wxTreeItemId &parent, wxTreeItemId &current) {
			//
			TreeNodeItem *current_node_item = (TreeNodeItem*)this->GetItemData(current);
			if (!current_node_item)
			{
				return;
			}
			current_node_item->m_parent_id = is_insert_below ? ((TreeNodeItem*)this->GetItemData(this->GetItemParent(parent)))->m_id : \
				((TreeNodeItem*)this->GetItemData(parent))->m_id;
			nodes_updated.push_back(current_node_item);

			//
			current_node_item->m_id_from_tree = is_insert_below ? \
				this->InsertItem(this->GetItemParent(parent), parent, \
							this->GetItemText(current), \
							this->GetItemImage(current), \
							this->GetItemState(current), current_node_item)
					: \
				this->PrependItem(parent, this->GetItemText(current), \
							this->GetItemImage(current), \
							this->GetItemState(current), current_node_item);
			this->SetItemData(current, 0);

			//
			wxTreeItemIdValue idvalue;
			wxTreeItemId child = GetFirstChild(current, idvalue);
			while (child.IsOk())
			{
				//
				TreeNodeItem *node_item = (TreeNodeItem*)this->GetItemData(child);
				node_item->m_parent_id = ((TreeNodeItem*)this->GetItemData(parent))->m_id;
				nodes_updated.push_back(node_item);

				//
				node_item->m_id_from_tree = this->AppendItem(current_node_item->m_id_from_tree, this->GetItemText(child), \
					this->GetItemImage(child), \
					this->GetItemState(child), node_item);
				this->SetItemData(child, 0);

				recursiveMove(node_item->m_id_from_tree, child);
				child = GetNextChild(current, idvalue);
			}
		};

		recursiveMove(end_node, m_ids_selected[i]);

		//
		this->Delete(begin_node);
	}

	DoEndDrag(nodes_updated);
}
SOLUTION_EXPLORER_REGISTER_EVENT_FUNC(wxEVT_TREE_END_DRAG, "END_DRAG", OnEndDrag, &giDataExplorerTreeCtrl::OnEndDrag);

void giDataExplorerTreeCtrl::OnBeginEditLabel(wxTreeEvent *event)
{
	if (event->GetItem() == this->GetRootItem())
	{
		event->Veto();
		return;
	}
	m_item_text_focused = GetItemText(event->GetItem());
}
SOLUTION_EXPLORER_REGISTER_EVENT_FUNC(wxEVT_TREE_BEGIN_LABEL_EDIT, "BEGIN_LABEL_EDIT", OnBeginEditLabel, &giDataExplorerTreeCtrl::OnBeginEditLabel);

void giDataExplorerTreeCtrl::OnEndEditLabel(wxTreeEvent *event)
{
	//
	bool isexist = false;
	wxString name_just_editted = event->GetLabel().ToStdString();
	if (event->GetItem() == this->GetRootItem() || \
		name_just_editted == "" || \
		name_just_editted == m_item_text_focused || \
		(isexist = m_nodes_map.find(name_just_editted) != m_nodes_map.end()))
	{
		if (isexist)
		{
			wxMessageBox(_(wxT("There is the same name!")), _(wxT("GI Message")));
		}
		event->Veto();
		return;
	}

	assert(m_nodes_map.find(m_item_text_focused) != m_nodes_map.end());
	TreeNodeItem *node_item = m_nodes_map[m_item_text_focused];
	if (node_item)
	{
		m_nodes_map.erase(m_nodes_map.find(m_item_text_focused));
		node_item->m_name = name_just_editted;
		m_nodes_map.insert(std::make_pair(name_just_editted, node_item));
	}
	DoUpdateTreeNode(node_item);
}
SOLUTION_EXPLORER_REGISTER_EVENT_FUNC(wxEVT_TREE_END_LABEL_EDIT, "END_LABEL_EDIT", OnEndEditLabel, &giDataExplorerTreeCtrl::OnEndEditLabel);

void giDataExplorerTreeCtrl::OnStateClick(wxTreeEvent *event)
{
}
SOLUTION_EXPLORER_REGISTER_EVENT_FUNC(wxEVT_TREE_STATE_IMAGE_CLICK, "STATE_IMAGE_CLICK", OnStateClick, &giDataExplorerTreeCtrl::OnStateClick);

