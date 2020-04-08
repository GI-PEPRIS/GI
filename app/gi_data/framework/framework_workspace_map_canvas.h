// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_WORKSPACE_MAP_CANVAS_H_
#define _GI_GUI_FRAMEWORK_WORKSPACE_MAP_CANVAS_H_

#include "framework_workspace_canvas.h"

#include "any/base/anystl.h"

//
namespace AnyMap
{
	class CAnyView;
}

//
class giDataWorkspaceMapCanvas : public giDataWorkspaceCanvas
{
public:
	//
	static wxString kPageType;
	static wxBitmap kPageIcon;

	//
	giDataWorkspaceMapCanvas(wxWindow *parent, wxWindowID id);
	~giDataWorkspaceMapCanvas();

	DECLARE_NO_COPY_CLASS(giDataWorkspaceMapCanvas)

public:
	//
	void ResetView(AnyMap::CAnyView *other);

	//
	//
	//
	void OnPaint(wxPaintEvent &event);
	void OnSize(wxSizeEvent &event);
	void OnContextMenu(wxContextMenuEvent& event);
	void OnClose(wxCloseEvent& event);

private:
	//
	std::unique_ptr<AnyMap::CAnyView> m_view;
};

#endif