// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_WORKSPACE_CUBE_CANVAS_H_
#define _GI_GUI_FRAMEWORK_WORKSPACE_CUBE_CANVAS_H_

#include "framework_workspace_canvas.h"

#include "any/base/anystl.h"

//
namespace AnyOGRE
{
	class CAnyOgreSampleView;
}

//
class giDataWorkspaceCubeCanvas : public giDataWorkspaceCanvas
{
public:
	//
	static wxString kPageType;
	static wxBitmap kPageIcon;

	//
	giDataWorkspaceCubeCanvas(wxWindow *parent, wxWindowID id);
	~giDataWorkspaceCubeCanvas();

	DECLARE_NO_COPY_CLASS(giDataWorkspaceCubeCanvas)
	DECLARE_EVENT_TABLE()

protected:
	//
	void ResetView(AnyOGRE::CAnyOgreSampleView *other);

	//
	//
	//
	void OnPaint(wxPaintEvent &event);
	void OnSize(wxSizeEvent &event);
	void OnContextMenu(wxContextMenuEvent& event);

private:
	//
	std::unique_ptr<AnyOGRE::CAnyOgreSampleView> m_view;
};

#endif