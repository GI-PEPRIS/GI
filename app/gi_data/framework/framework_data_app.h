// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

#ifndef _GI_GUI_FRAMEWORK_DATA_APP_H_
#define _GI_GUI_FRAMEWORK_DATA_APP_H_

#include "wx/wx.h"
#include "wx/ipc.h"
#include "wx/fileconf.h"
#include "wx/filehistory.h"

//
#include "framework_data_macroes.h"

// refer to dbsourcedesc
#include "any/db/anyaccessorbasic.h"
using namespace AnyDB;

//forward class
class giDataFrame;

// entry/exit function, app's configurations, global initialization
// 
class giDataApp : public wxApp
{
	// simple network among apps
	//
	// as server side
	class stServer : public wxServer
	{
	public:
		// accept
		wxConnectionBase *OnAcceptConnection(const wxString &topic);
	};
	// as connection
	class stConnection : public wxConnection
	{
	public:
		stConnection() {}
		~stConnection() {}

		// action to topic
		bool OnExecute(const wxString &topic, wxChar *data, int size, wxIPCFormat format);
	};
	// as client side
	class stClient : public wxClient
	{
	public:
		//
		stClient() {};
		wxConnectionBase *OnMakeConnection() { return new stConnection; }
	};


public:
	// c'tor & d'ctor
	giDataApp();
	~giDataApp();

public:
	// entry/exit point
	virtual bool OnInit();
	virtual int OnExit();

	// app configurations
	template<typename T>
	T ReadConfig(const wxString& key, T const &defVal) const{
		assert(m_config_file);
		return m_config_file->ReadObject<T>(key, defVal);
	}
	wxString ReadConfig(const wxString& key, const wxString& defVal = wxEmptyString) const{
		return m_config_file->Read(key, defVal);
	}
	bool WriteConfig(const wxString& key, int const &value)
	{
		assert(m_config_file);
		return m_config_file->Write(key, value);
	}
	bool WriteConfig(const wxString& key, wxString const &value)
	{
		assert(m_config_file);
		return m_config_file->Write(key, value);
	}
	bool SaveConfig() {
		assert(m_config_file);
		return m_config_file->Flush();
	}
	// data source configurations
	void ReadDBConfig(DBSourceDesc &db_desc);
	void ReadDBConfig(DBSourceDesc &db_desc, std::vector<DBSourceDesc> &recent_dbs);
	void WriteDBConfig(const DBSourceDesc &db_desc);
	bool IsCanLogin();
	bool IsCanLogin(const DBSourceDesc &db_desc);
	bool IsLogining(const DBSourceDesc &db_desc);
	bool IsCanLogin(const DBSourceDesc &db_desc, std::vector<std::string> &db_names);

	// recent dbs
	void DBSourceToString(const DBSourceDesc &db_desc, wxString& dbstr);
	void StringToDBSource(const wxString& dbstr, DBSourceDesc &db_desc);
	void RemoveRecentDB(const DBSourceDesc &db_desc);

	// ipc

	// for resources
	bool GetBitmap(const wxString &file, wxBitmap &bitmap);

	//
	static giDataFrame &GetFrame();
	static giDataApp &GetApp();

private:
	//
	void DoInitConfig();
	void DoInitIPC();
	void DoInitLocale();
	void DoInitFrame();

	void DoExitApp();


private:
	// configurations
	wxFileConfig *m_config_file;
	// recent databases
	wxFileHistory *m_recent_dbs;

	// ipc 
	stServer *m_ipc_server;
	stClient *m_ipc_client;

	// locale(language)
	wxLocale m_locale;
};

#endif