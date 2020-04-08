// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_WORKSPACE_WELL_SECTION_CANVAS_H_
#define _GI_GUI_FRAMEWORK_WORKSPACE_WELL_SECTION_CANVAS_H_

#include "framework_workspace_canvas.h"

#include "any/base/anystl.h"

//
namespace AnyMap
{
	class CAnyView;
}

//
class giDataWorkspaceWellSectionCanvas : public giDataWorkspaceCanvas
{
public:
	//
	static wxString kPageType;
	static wxBitmap kPageIcon;

	//
	giDataWorkspaceWellSectionCanvas(wxWindow *parent, wxWindowID id);
	~giDataWorkspaceWellSectionCanvas();

	DECLARE_NO_COPY_CLASS(giDataWorkspaceWellSectionCanvas)
	DECLARE_EVENT_TABLE()

protected:
	//
	void ResetView(AnyMap::CAnyView *other);

	//
	//
	//
	void OnPaint(wxPaintEvent &event);
	void OnSize(wxSizeEvent &event);

private:
	//
	std::unique_ptr<AnyMap::CAnyView> m_view;
};

#endif