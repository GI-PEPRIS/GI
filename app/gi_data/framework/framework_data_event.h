// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_DATA_EVENT_H_
#define _GI_GUI_FRAMEWORK_DATA_EVENT_H_

//
#include <unordered_map>

template<typename Ctrl, typename Parameter>
class giDataEvent
{
protected:
	// the brief event registry entry
	// key: event id
	// content: event name is the name of control, event type
	typedef std::unordered_map<unsigned int, std::vector<std::pair<wxString, int>>> giEventEntryTable;
	// alike to wxEventFunction
	typedef void (Ctrl::*giEventFunction)(Parameter*);
	// key: name is the control name+event type
	typedef std::unordered_map<wxString, giEventFunction> giEventFunctionTable;

public:
	//
	giDataEvent(){}
	virtual ~giDataEvent(){}

public:
	//
	// static event registry and function variable
	// 
	static giEventEntryTable &EventEntryTableGlobal()
	{
		static giEventEntryTable global_event_entry_table;
		return global_event_entry_table;
	}
	static giEventFunctionTable &EventFunctionTableGlobal()
	{
		static giEventFunctionTable global_event_function_table;
		return global_event_function_table;
	}

	//
	// event entry registration
	// 
	static void RegisterEventEntry(unsigned int event_id, int event_type, const wxString &event_name)
	{
		if (!IsEventEntryRegistered(event_id, event_type))
		{
			EventEntryTableGlobal()[event_id].push_back(std::make_pair(event_name, event_type));
		}
	}
	static bool IsEventEntryRegistered(unsigned int event_id, int event_type)
	{
		giEventEntryTable::const_iterator it = EventEntryTableGlobal().find(event_id);
		if (it != EventEntryTableGlobal().end())
		{
			for (int i = 0; i < it->second.size(); i++)
			{
				if (it->second[i].second == event_type)
				{
					return true;
				}
			}
		}

		return false;
	}

	//
	//
	//
	static bool RegisterEventFunction(int event_type, const wxString &event_name, giEventFunction func)
	{
		wxString func_key = MergeEventFunctionKey(event_type, event_name);
		if (!IsEventFunctionRegistered(func_key))
		{
			EventFunctionTableGlobal()[func_key] = func;

			return true;
		}

		return false;
	}
	static bool IsEventFunctionRegistered(const wxString &func_key)
	{
		giEventFunctionTable::const_iterator it = EventFunctionTableGlobal().find(func_key);
		if (it != EventFunctionTableGlobal().end())
		{
			return true;
		}
		return false;
	}
	static wxString MergeEventFunctionKey(int event_type, const wxString &event_name)
	{
		wxString func_type;
		func_type << event_type;

		return (event_name + func_type).Upper();
	}
	static wxString GetEventFunctionKey(long event_id, int event_type)
	{
		if (!IsEventEntryRegistered(event_id,event_type))
		{
			assert(false);
			return wxString("");
		}

		wxString func_key;
		for (int i = 0; i < EventEntryTableGlobal()[event_id].size(); i++)
		{
			if (EventEntryTableGlobal()[event_id][i].second == event_type)
			{
				func_key = MergeEventFunctionKey(EventEntryTableGlobal()[event_id][i].second, EventEntryTableGlobal()[event_id][i].first);
				break;
			}
		}
		if (!IsEventFunctionRegistered(func_key))
		{
			//assert(false);
			return wxString("");
		}

		return func_key;
	}
};

#endif

