// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_DATA_DEFS_H_
#define _GI_GUI_FRAMEWORK_DATA_DEFS_H_

// idx for bitmaps
enum giBitmap
{
	GI_DATA_APP_LOGIN_BITMAP,
};

#define PX_BASESIZER_TO_UPPER_BORDER 6		//����sizer���ϱ߽�ľ���
#define PX_BASESIZER_TO_BOTTOM_BORDER 8		//����sizer���±߽�ľ���
#define PX_BASESIZER_TO_RIGHT_BORDER 7		//����sizer���ұ߽�ľ���

#define PX_SIZER_TO_SIZER_VECTICAL 10		//sizer֮����������
#define PX_SIZER_TO_SIZER_HORIZONTAL 10		//sizer֮��ĺ������

#define PX_SIZER_TO_1STCTRL_VECTICAL 5		//14//sizer����һ�пؼ����������
#define PX_SIZER_TO_1STCTRL_HORIZONTAL 23	//sizer������߿ؼ��ĺ������

#define PX_CTRL_TO_CTRL_VECTICAL 7			//�ؼ�֮����������
#define PX_CTRL_TO_CTRL_HORIZONTAL 8		//�ؼ�֮��ĺ������

#define PX_NORMAL_BTN_WIDTH 75				//��ť��ȣ������ť���ַ����Ƚϳ������ڳ��������и���
#define PX_NORMAL_BTN_HEIGHT 28				//��ť�߶�

#define PX_SMALL_BTN_WIDTH 25						
#define PX_SMALL_BTN_HEIGHT 25				

#define PX_LABEL_WIDTH 75

#define PX_SOLUTION_EXPLORER_WIDTH 260
#define PX_SOLUTION_EXPLORER_HEIGHT 650

// global app & frame
#define giTheApp(app) (*(static_cast<app*>(wxTheApp)))
#define giTheFrame(app) app::GetFrame()

// ribbon event macroes
#define RIBBON_REGISTER_EVENT_ENTRY(event_id, event_type, event_name) \
	giDataFrame::RegisterEventEntry(event_id, event_type, event_name) // for runntime calling inside one function

#define RIBBON_REGISTER_EVENT_FUNC(event_type, event_name, func_name, func) \
    static bool unused_ribbon_event_function_##func_name = \
		giDataFrame::RegisterEventFunction(event_type, event_name, func) // for initialze calling outside functions

// explorer event macroes
#define SOLUTION_EXPLORER_REGISTER_EVENT_ENTRY(event_id, event_type, event_name) \
	giDataExplorerTreeCtrl::RegisterEventEntry(event_id, event_type, event_name) // for runntime calling inside one function

#define SOLUTION_EXPLORER_REGISTER_EVENT_FUNC(event_type, event_name, func_name, func) \
    static bool unused_solution_explorer_event_function_##func_name = \
		giDataExplorerTreeCtrl::RegisterEventFunction(event_type, event_name, func) // for initialze calling outside functions

// in fact, page create function
#define WORKSPACE_NOTEBOOK_PAGE_ENTRY(page_name, PAGE_CLASS) \
	static bool unused_notebook_page_##PAGE_CLASS = \
			giDataAuiNotebook::RegisterNotebookPageFactory(page_name, [](wxWindow*parent, long id)->wxWindow*{return new PAGE_CLASS(parent, id);});

#endif
