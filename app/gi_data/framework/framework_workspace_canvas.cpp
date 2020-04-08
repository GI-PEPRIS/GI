// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#include "framework_workspace_canvas.h"

#include "framework_data_aui_notebook.h"
#include "framework_data_macroes.h"

//
#include "any/map/anyview.h"
using namespace AnyMap;

//
// event table against it and its children
//
BEGIN_EVENT_TABLE(giDataWorkspaceCanvas, wxWindow)
	EVT_PAINT(giDataWorkspaceCanvas::OnPaint)
	EVT_SIZE(giDataWorkspaceCanvas::OnSize)
	EVT_CONTEXT_MENU(giDataWorkspaceCanvas::OnContextMenu)
END_EVENT_TABLE()

//
//
void giDataWorkspaceCanvas::OnContextMenu(wxContextMenuEvent& event)
{
	// TODO:
	// 
	wxMenu menu;
	menu.Append(0, _(wxT("Pan")));
	menu.Append(1, _(wxT("Zoom In")));
	menu.Append(2, _(wxT("Zoom Out")));
	menu.Append(3, _(wxT("Zoom by Rectangle")));
	menu.Append(4, _(wxT("Full Extent")));

	menu.AppendSeparator();
	menu.Append(5, _(wxT("Print Screen")));
	PopupMenu(&menu);
}