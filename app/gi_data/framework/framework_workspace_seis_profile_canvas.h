// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_WORKSPACE_SEIS_PROFILE_CANVAS_H_
#define _GI_GUI_FRAMEWORK_WORKSPACE_SEIS_PROFILE_CANVAS_H_

#include "framework_workspace_canvas.h"

#include "any/base/anystl.h"

//
namespace AnyMap
{
	class CAnyView;
}

//
class giDataWorkspaceSeisProfileCanvas : public giDataWorkspaceCanvas
{
public:
	//
	static wxString kPageType;
	static wxBitmap kPageIcon;

	//
	giDataWorkspaceSeisProfileCanvas(wxWindow *parent, wxWindowID id);
	~giDataWorkspaceSeisProfileCanvas();

	DECLARE_NO_COPY_CLASS(giDataWorkspaceSeisProfileCanvas)
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