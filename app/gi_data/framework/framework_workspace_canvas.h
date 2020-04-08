// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_WORKSPACE_CANVAS_H_
#define _GI_GUI_FRAMEWORK_WORKSPACE_CANVAS_H_

#include "wx/wx.h"

#include "any/base/anystl.h"

// 
// to define interface to deal with actions among those children canvases, e.g., when moving mouse etc
//
class giDataWorkspaceCanvas : public wxWindow
{
public:
	//
	giDataWorkspaceCanvas(wxWindow *parent, wxWindowID id) : wxWindow(parent, id)
	{
	}
	virtual ~giDataWorkspaceCanvas()
	{
	}
	DECLARE_NO_COPY_CLASS(giDataWorkspaceCanvas)
	DECLARE_EVENT_TABLE()

public:
	virtual void OnPaint(wxPaintEvent &event) = 0;
	virtual void OnSize(wxSizeEvent &event) = 0;
	void OnContextMenu(wxContextMenuEvent& event);
};

#endif