// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#include "framework_workspace_well_section_canvas.h"

#include "framework_data_aui_notebook.h"
#include "framework_data_macroes.h"

//
#include "any/map/anyview.h"
using namespace AnyMap;

//
//
//
BEGIN_EVENT_TABLE(giDataWorkspaceWellSectionCanvas, giDataWorkspaceCanvas)
EVT_PAINT(giDataWorkspaceWellSectionCanvas::OnPaint)
EVT_SIZE(giDataWorkspaceWellSectionCanvas::OnSize)

END_EVENT_TABLE()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
giDataWorkspaceWellSectionCanvas::giDataWorkspaceWellSectionCanvas(wxWindow *parent, wxWindowID id) : m_view(new CAnyView(AnyMap::VT_Win)), \
giDataWorkspaceCanvas(parent, id)
{
}
giDataWorkspaceWellSectionCanvas::~giDataWorkspaceWellSectionCanvas()
{
}
wxString giDataWorkspaceWellSectionCanvas::kPageType = wxT("Log Section");
wxBitmap giDataWorkspaceWellSectionCanvas::kPageIcon;
WORKSPACE_NOTEBOOK_PAGE_ENTRY(giDataWorkspaceWellSectionCanvas::kPageType, giDataWorkspaceWellSectionCanvas)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void giDataWorkspaceWellSectionCanvas::OnPaint(wxPaintEvent &event)
{
	PAINTSTRUCT ps;
	HWND hwnd = (HWND)GetHandle();

	BeginPaint(hwnd, &ps);
	{
		m_view->OnPaint(false);
	}
	EndPaint(hwnd, &ps);

	event.Skip();
}

void giDataWorkspaceWellSectionCanvas::OnSize(wxSizeEvent &event)
{
	int w = 0;
	int h = 0;
	GetSize(&w, &h);
	if (w > 2 && h > 2)
	{
		AnyMap::ScreenPort port;
		port.m_bufBase.m_x = 0;
		port.m_bufBase.m_y = 0;
		port.m_base.m_x = w / 2;
		port.m_base.m_y = h / 2;
		port.m_extent.m_minX = 0;
		port.m_extent.m_maxX = w;
		port.m_extent.m_minY = 0;
		port.m_extent.m_maxY = h;

		m_view->Attach(GetHandle(), port);
	}
	//m_view->ZoomFull();//̫������ʱȥ��
	//m_view->Refresh(false);
	event.Skip();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void giDataWorkspaceWellSectionCanvas::ResetView(AnyMap::CAnyView *other)
{
	m_view = std::unique_ptr<CAnyView>(other);
}

//
