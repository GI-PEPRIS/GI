// Copyright 2019, Xiujie Sheng
// All rights reserved.
// GUI framework of Geological Intelligence (GI)

// framework 
#include "framework_data_app.h"
#include "framework_data_frame.h"
#include "framework_connect_login_dlg.h"

// single instance checker
#include "wx/defs.h"
#include "wx/snglinst.h"
#include "wx/stdpaths.h"

// Base package
#include "any/base/loki/singleton.h"
using namespace AnyBase::Loki;

#include "any/db/anyaccessor.h"
using namespace AnyDB;

#include "any/thread/jtc.h"

// entry point
DECLARE_APP(giDataApp)
IMPLEMENT_APP(giDataApp)

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// inner class implementation

// as a server side to receive connection request & create a connection
wxConnectionBase *giDataApp::stServer::OnAcceptConnection(const wxString &topic) {
	if (topic.Lower() == wxT("DataApp")){
		// check whether there is a modelless dlg
		wxWindowList::Node *node = wxTopLevelWindows.GetFirst();
		while (node){
			wxDialog *dialog = wxDynamicCast(node->GetData(),wxDialog);
			if(dialog && dialog->IsModal()){
				return false;
			}
			node->GetNext();
		}

		return new stConnection;
	}

	return NULL;
}

// actions to kinds of topics
bool giDataApp::stConnection::OnExecute(const wxString &topic, wxChar *data, int size, wxIPCFormat format) {

	// by default, to raise app to the top
	giDataFrame *main_frame = wxDynamicCast(wxGetApp().GetTopWindow(), giDataFrame);
	if (main_frame) {
		main_frame->Raise();
	}

	// TODO:
	// dispatch given topics

	//
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// c'tor & d'ctor
giDataApp::giDataApp() : m_config_file(0), m_recent_dbs(0), \
	m_ipc_server(0), m_ipc_client(0)
{
}
giDataApp::~giDataApp()
{	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// entry & initialize
bool giDataApp::OnInit()
{
	// whether allow multiple exe instances
	const wxString exe_name = wxString::Format(wxT("GI DataApp:%s"), wxGetUserId().c_str());
	wxSingleInstanceChecker *checker = new wxSingleInstanceChecker(exe_name);
	if (checker->IsAnotherRunning()) {
		wxLogError(_("GI data application is already running!"));
		delete checker;
		return false;
	}
	delete checker;

	// parent intializations 
	if(!wxApp::OnInit()){
		return false;
	}
	
	// Create Config File()
	DoInitConfig();
	DoInitIPC();
	DoInitLocale();

	// login
	DoInitFrame();

	// to detect event
	return true;
}
void giDataApp::DoInitConfig(){
	wxString config_file_name = wxStandardPaths::Get().GetDataDir() + wxFileName::GetPathSeparator() + "config.ini";
	m_config_file = new wxFileConfig("", "", config_file_name);
	wxConfigBase::Set(m_config_file);

	m_recent_dbs = new wxFileHistory(10);
	m_recent_dbs->Load(*m_config_file);
}
void giDataApp::DoInitIPC(){
	wxString server_name = ReadConfig(wxT("GUI/IPC/SERVERNAME"), wxT(""));
	bool is_server = ReadConfig(wxT("GUI/IPC/ISSERVER"), false);
	if (is_server) {
		assert(server_name.size());
		m_ipc_server = new stServer;
		if (!m_ipc_server->Create(server_name)) {
			wxLogDebug(wxT("Failure to create an IPC server!"));
		}
	}
	else {
		wxLogNull log_null;
		m_ipc_client = new stClient;
		wxString server_ip = ReadConfig(wxT("GUI/IPC/SERVERHOST"), wxT("127.0.0.1"));

		wxConnectionBase *connection = m_ipc_client->MakeConnection(server_ip, server_name, wxT("REGISTER"));
		if (connection) {
			connection->Execute(wxT("Dumy"));
		}
		delete connection;
	}
}
void giDataApp::DoInitLocale() {
	//
	// language data
	static const wxLanguage langIds[] = {
		wxLANGUAGE_CHINESE_SIMPLIFIED,
		wxLANGUAGE_ENGLISH
	};

	// note that it makes no sense to translate these strings, they are
	// shown before we set the locale anyhow
	static const wxString langNames[] = {
		//_("System default"),
		_("Chinese"),
		_("English")
	};

	wxLanguage language_type = wxLANGUAGE_UNKNOWN;
	language_type = (wxLanguage)ReadConfig<int>(wxT("GUI/LANGUAGE/COUNTRY"), language_type);
	if(language_type == wxLANGUAGE_UNKNOWN){
		int lng = wxGetSingleChoiceIndex
		(
			_(_("Please select a language")),
			_(_("Language Setting")),
			WXSIZEOF(langNames),
			langNames
		);
		language_type = lng == -1 ? wxLANGUAGE_DEFAULT : langIds[lng];
		WriteConfig(wxT("GUI/LANGUAGE/COUNTRY"), language_type);
	}

	if(!m_locale.Init(language_type, wxLOCALE_DONT_LOAD_DEFAULT))
	{
		wxLogWarning(_(_("This language is not supported by current system.")));
	}
	wxLocale::AddCatalogLookupPathPrefix(_("."));

	// Initialize the catalogs we'll be using
	const wxLanguageInfo* pInfo = wxLocale::GetLanguageInfo(language_type);
	wxString language_path = wxStandardPaths::Get().GetDataDir() + wxFileName::GetPathSeparator() + "language";
	m_locale.AddCatalogLookupPathPrefix(language_path);
	if (language_type == langIds[0]) {
		if (!m_locale.AddCatalog(_("zh")))
		{
			wxLogError(_(_("Couldn't find/load the 'zh' catalog for locale '%s'.")),
				pInfo ? pInfo->GetLocaleName() : _(_("unknown")));
		}
	}
	else if(language_type == langIds[1]){
		if (!m_locale.AddCatalog(_("en"))){
			wxLogError(_(_("Couldn't find/load the 'en' catalog for locale '%s'.")),
				pInfo ? pInfo->GetLocaleName() : _(_("unknown")));
		}
	}

	// Now try to add wxstd.mo so that loading _("NOTEXIST.ING") file will produce
	// a localized error message:
	m_locale.AddCatalog(_("wxstd"));
}
void giDataApp::DoInitFrame() {
	giLoginDlg login_dlg(0);
	if (login_dlg.ShowModal() == wxID_OK) {
		GetFrame().ShowFrame(true);
	}
	else {
		//wxApp::Exit(); //this way causes lots of memory leaks
		wxCloseEvent event;
		GetFrame().OnCloseWindow(event);
	}
}

// exit & release
int giDataApp::OnExit()
{
	//
	DoExitApp();

	//
	return 0;
}
void giDataApp::DoExitApp() {
	if (m_config_file) delete m_config_file;
	if (m_recent_dbs) delete m_recent_dbs;
	if (m_ipc_server) delete m_ipc_server;
	if (m_ipc_client) delete m_ipc_client;
	m_config_file = 0;
	m_recent_dbs = 0;
	m_ipc_server = 0;
	m_ipc_client = 0;
}

void giDataApp::ReadDBConfig(DBSourceDesc &db_desc) 
{
	db_desc.m_type = ReadConfig<int>(wxT("DATASOURCE/RDBMS/DBTYPE"), 0);
	db_desc.m_srcName = ReadConfig<wxString>(wxT("DATASOURCE/RDBMS/DBSOURCE"), "");
	db_desc.m_dbName = ReadConfig<wxString>(wxT("DATASOURCE/RDBMS/DBNAME"), "");
	db_desc.m_user = ReadConfig<wxString>(wxT("DATASOURCE/RDBMS/USER"), "");
	db_desc.m_pwd = ReadConfig<wxString>(wxT("DATASOURCE/RDBMS/PWD"), "");
}
void giDataApp::WriteDBConfig(const DBSourceDesc &db_desc) 
{
	WriteConfig(wxT("DATASOURCE/RDBMS/DBTYPE"), db_desc.m_type);
	WriteConfig(wxT("DATASOURCE/RDBMS/DBSOURCE"), db_desc.m_srcName);
	WriteConfig(wxT("DATASOURCE/RDBMS/DBNAME"), db_desc.m_dbName);
	WriteConfig(wxT("DATASOURCE/RDBMS/USER"), db_desc.m_user);
	WriteConfig(wxT("DATASOURCE/RDBMS/PWD"), db_desc.m_pwd);

	bool isexist = false;
	for (int i = 0; i < m_recent_dbs->GetCount(); i++) 
	{
		// TODO:
		// to set the fist position in recent dbs
		DBSourceDesc recent_db;
		StringToDBSource(m_recent_dbs->GetHistoryFile(i), recent_db);
		if(recent_db.m_type == db_desc.m_type && recent_db.m_srcName == db_desc.m_srcName && \
			recent_db.m_dbName == db_desc.m_dbName && recent_db.m_user == db_desc.m_user && recent_db.m_pwd == db_desc.m_pwd)
		{
			isexist = true;
			break;
		}
	}
	if (!isexist) 
	{
		wxString dbstr;
		DBSourceToString(db_desc, dbstr);
		m_recent_dbs->AddFileToHistory(dbstr);
		m_recent_dbs->Save(*m_config_file);
	}
	SaveConfig();
}
void giDataApp::ReadDBConfig(DBSourceDesc &db_desc, std::vector<DBSourceDesc> &recent_dbs) 
{
	ReadDBConfig(db_desc);
	recent_dbs.clear();
	for (int i = 0; i < m_recent_dbs->GetCount(); i++)
	{
		DBSourceDesc recent_db;
		StringToDBSource(m_recent_dbs->GetHistoryFile(i), recent_db);
		recent_dbs.push_back(recent_db);
	}
}
void giDataApp::RemoveRecentDB(const DBSourceDesc &db_desc)
{
	DBSourceDesc db_desc_cur;
	ReadDBConfig(db_desc_cur);
	if (db_desc_cur.m_type == db_desc.m_type && db_desc_cur.m_srcName == db_desc.m_srcName && \
		db_desc_cur.m_dbName == db_desc.m_dbName && db_desc_cur.m_user == db_desc.m_user && db_desc_cur.m_pwd == db_desc.m_pwd)
	{
		WriteConfig(wxT("DATASOURCE/RDBMS/DBTYPE"), DBS_Unknown);
		WriteConfig(wxT("DATASOURCE/RDBMS/DBSOURCE"), "");
		WriteConfig(wxT("DATASOURCE/RDBMS/DBNAME"), "");
		WriteConfig(wxT("DATASOURCE/RDBMS/USER"), "");
		WriteConfig(wxT("DATASOURCE/RDBMS/PWD"), "");
	}
	for (int i = 0; i < m_recent_dbs->GetCount(); i++)
	{
		DBSourceDesc recent_db;
		StringToDBSource(m_recent_dbs->GetHistoryFile(i), recent_db);
		if (recent_db.m_type == db_desc.m_type && recent_db.m_srcName == db_desc.m_srcName && \
			recent_db.m_dbName == db_desc.m_dbName && recent_db.m_user == db_desc.m_user && recent_db.m_pwd == db_desc.m_pwd)
		{
			m_recent_dbs->RemoveFileFromHistory(i);
			m_recent_dbs->Save(*m_config_file);
			break;
		}
	}
	SaveConfig();
}

void giDataApp::DBSourceToString(const DBSourceDesc &db_desc, wxString& dbstr)
{
	dbstr = "";
	dbstr = dbstr + wxString::Format("%d", db_desc.m_type);
	dbstr = dbstr + "@#";
	dbstr = dbstr + db_desc.m_srcName;
	dbstr = dbstr + "@#";
	dbstr = dbstr + db_desc.m_dbName;
	dbstr = dbstr + "@#";
	dbstr = dbstr + db_desc.m_user;
	dbstr = dbstr + "@#";
	dbstr = dbstr + db_desc.m_pwd;
	dbstr = dbstr + "@#";
}
void giDataApp::StringToDBSource(const wxString& dbstr, DBSourceDesc &db_desc)
{
	string dbstring = dbstr.ToStdString();
	if (dbstring.find("@#") != string::npos)
	{
		db_desc.m_type = ::atoi(dbstring.substr(0, dbstring.find("@#")).c_str());
		dbstring = dbstring.substr(dbstring.find("@#") + 2);
	}
	if (dbstring.find("@#") != string::npos)
	{
		db_desc.m_srcName = dbstring.substr(0, dbstring.find("@#")).c_str();
		dbstring = dbstring.substr(dbstring.find("@#") + 2);
	}
	if (dbstring.find("@#") != string::npos)
	{
		db_desc.m_dbName = dbstring.substr(0, dbstring.find("@#")).c_str();
		dbstring = dbstring.substr(dbstring.find("@#") + 2);
	}
	if (dbstring.find("@#") != string::npos)
	{
		db_desc.m_user = dbstring.substr(0, dbstring.find("@#")).c_str();
		dbstring = dbstring.substr(dbstring.find("@#") + 2);
	}
	if (dbstring.find("@#") != string::npos)
	{
		db_desc.m_pwd = dbstring.substr(0, dbstring.find("@#")).c_str();
		dbstring = dbstring.substr(dbstring.find("@#") + 2);
	}
}

// framework themselves
inline giDataFrame &giDataApp::GetFrame() 
{
	return SingletonHolder<giDataFrame, CreateUsingNew, NoDestroy>::Instance();
}
inline giDataApp &giDataApp::GetApp() 
{
	return (*(giDataApp*)wxTheApp);
}

//
bool giDataApp::GetBitmap(const wxString &file, wxBitmap &bitmap) {

	wxString bitmap_file = wxStandardPaths::Get().GetDataDir() + wxFileName::GetPathSeparator() + "bitmaps";
	bitmap_file += "/";
	bitmap_file += file;
	wxImage image(bitmap_file);
	if (image.IsOk())
	{
		bitmap = wxBitmap(image);
		return true;
	}
	return false;
}

// 
bool giDataApp::IsCanLogin() {
	DBSourceDesc db_desc;
	ReadDBConfig(db_desc);

	// no need to initDB by advance
	return CAnyAccessor::IsCanConnected(db_desc);
}
bool giDataApp::IsCanLogin(const DBSourceDesc &db_desc) {
	return CAnyAccessor::IsCanConnected(db_desc);
}
bool giDataApp::IsLogining(const DBSourceDesc &db_desc) {
	return CAnyAccessor::IsLogining(db_desc);
}
bool giDataApp::IsCanLogin(const DBSourceDesc &db_desc, std::vector<std::string> &db_names) {
	// no need to initDB by advance
	return CAnyAccessor::IsCanConnected(db_desc, db_names);
}