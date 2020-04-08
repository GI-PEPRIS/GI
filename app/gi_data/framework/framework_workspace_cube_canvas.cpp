// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#include "framework_workspace_cube_canvas.h"

#include "framework_data_aui_notebook.h"
#include "framework_data_macroes.h"

//
#include "any/ogre/anyogresampleview.h"
using namespace AnyOGRE;

//
//
//
BEGIN_EVENT_TABLE(giDataWorkspaceCubeCanvas, giDataWorkspaceCanvas)
	EVT_PAINT(giDataWorkspaceCubeCanvas::OnPaint)
	EVT_SIZE(giDataWorkspaceCubeCanvas::OnSize)
	EVT_CONTEXT_MENU(giDataWorkspaceCubeCanvas::OnContextMenu)

END_EVENT_TABLE()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
giDataWorkspaceCubeCanvas::giDataWorkspaceCubeCanvas(wxWindow *parent, wxWindowID id) : m_view(nullptr), \
	giDataWorkspaceCanvas(parent, id)
{
}
giDataWorkspaceCubeCanvas::~giDataWorkspaceCubeCanvas()
{
}
wxString giDataWorkspaceCubeCanvas::kPageType = wxT("Cube");
wxBitmap giDataWorkspaceCubeCanvas::kPageIcon;
WORKSPACE_NOTEBOOK_PAGE_ENTRY(giDataWorkspaceCubeCanvas::kPageType, giDataWorkspaceCubeCanvas)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void giDataWorkspaceCubeCanvas::OnPaint(wxPaintEvent &event)
{
	PAINTSTRUCT ps;
	HWND hwnd = (HWND)GetHandle();

	BeginPaint(hwnd, &ps);
	{
		if (m_view)
		{
			m_view->OnPaint();
		}
	}
	EndPaint(hwnd, &ps);

	event.Skip();
}

void giDataWorkspaceCubeCanvas::OnSize(wxSizeEvent &event)
{
	int w = 0;
	int h = 0;
	GetSize(&w, &h);
	if (w > 2 && h > 2)
	{
		if(m_view)
		{
			m_view->OnSize(w, h);
		}
	}
	event.Skip();
}

void giDataWorkspaceCubeCanvas::OnContextMenu(wxContextMenuEvent& event)
{

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void giDataWorkspaceCubeCanvas::ResetView(AnyOGRE::CAnyOgreSampleView *other)
{
	m_view = std::unique_ptr<CAnyOgreSampleView>(other);
}

//
