// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_DATA_SOLUTION_BUILDER_H_
#define _GI_GUI_FRAMEWORK_DATA_SOLUTION_BUILDER_H_

//
#include "wx/wx.h"

//
class giDataSolutionNotebook;

// 
class giDataSolutionBuilder
{

public:
	//
	giDataSolutionBuilder(wxWindow *parent);
	~giDataSolutionBuilder();

public:
	// gis solution, which includes map catelogure explorer & layer's explorer
	//
	giDataSolutionNotebook *CreateSolution(const wxString &solution_name);

private:
	//
	wxWindow *m_parent;
	//
	long m_solution_event_id;
};

#endif