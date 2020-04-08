/*!
 * The AnyDB of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the persistence-related architectural patterns such as MAPPER etc.
 *
 * Copyright (C) 2015 XIUJIE SHENG
 *
 * This library isn't a free software, so you cann't take the source code without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will not harm your computer or ongoing 
 * business if you illegally got it. 
 *
 * NOTE: 
 * AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
 * LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
 *
 * For more information, contact:
 *
 * China University of Geoseciences(Wuhan)
 * Resource Faculty
 *
 * Xiujie Sheng
 * herman.sheng@gmail.com
 */
#ifndef __ANYDB_ACCESSOR_H__
#define __ANYDB_ACCESSOR_H__

// Refer to EXPORT etc
#include "anydb.h"
// Refer to basic defintions
#include "anyaccessorbasic.h"
// refer to persistent object
#include "any/base/anyobject.h"
using namespace AnyBase;
#include "anyaccessorimpl.h"

#include "any/base/anymediator.h"
//
namespace AnyDB
{
	// forward class
	class CAnyAccessorImpl;
	class CAnyUnitWork;
	class CAnyKeyGenerator;

	/*!
	*
	**/
	class ANYDB_CLASS CAnyAccessor
	{
		// relatives
		friend class CAnyKeyGenerator;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyAccessor();

		/*!
		*
		**/
		CAnyAccessor(bool isTransaction);

		/*!
		*
		**/
		CAnyAccessor(int dbNum);

		/*!
		*
		**/
		CAnyAccessor(string& dbURI);

		/*!
		*
		**/
		~CAnyAccessor();

	private:
		//
		//
		//
		/*!
		*
		**/
		CAnyAccessor(const CAnyAccessor &other);

		/*!
		*
		**/
		const CAnyAccessor &operator =(const CAnyAccessor &other);

	protected:
		//
		// Connection 
		//
		/*!
		*
		**/
		void Connect();
		void Disconnect();

	public:
		// before calling initDB and setup connection pool
		static bool IsCanConnected(const DBSourceDesc &desc);
		static bool IsCanConnected(const DBSourceDesc &desc, std::vector<string> &db_names);
		static bool IsCanConnectedAdmin(const DBSourceDesc &desc, std::vector<string> &db_names);
		static bool IsAdministrator(const DBSourceDesc &desc);
		static bool IsLogining(const DBSourceDesc &desc);
		static bool IsDatabaseExist(const DBSourceDesc &desc);
		static bool CreateDatabase(const DBSourceDesc &desc);
		static bool DeleteDatabase(const DBSourceDesc &desc);
		static string InitDBFileDataOnly(const DBSourceDesc &desc);
		static string InitSQLDBFileDataOnly(const DBSourceDesc &desc);

		//
		// schema interface 
		//
		/*!
		*
		**/
		bool CreateTable(const DBTableDesc &table);

		/*!
		*
		**/
		bool CreateField(const DBFieldDesc &field);

		/*!
		*
		**/
		long GetTableCount();

		/*!
		*
		**/
		void GetTableDesc(short index, DBTableDesc &tDesc);

		/*!
		*
		**/
		void RenameTable(std::map<std::string,std::string> nameMap);
		/*!
		*
		**/
		long GetFieldCount(const DBTableDesc &tDesc, bool isSchema = false);

		/*!
		*
		**/
		void GetFieldDesc(short index, DBFieldDesc &field, bool isSchema = false);
		
		/*!
		*
		**/
		void RenameField(std::string tablename ,std::map<std::string,std::string> nameMap);
		/*!
		*
		**/
		bool GetForeignDesc(const DBFieldDesc &field, DBFieldDesc &foreign);

		/*!
		*
		**/
		bool IsPrimaryKey(const DBFieldDesc &fDesc);

		/*!
		*
		**/
		bool IsForeignKey(const DBFieldDesc &fDesc);

		
		/*!
		*
		**/
		void GetAllForeignKeys(std::vector<string>&m_pkTables, std::vector<string>&m_pkFields, std::vector<string>&m_fkTables, std::vector<string>&m_fkFields);

		/*!
		*
		**/
		void GetAllPrimaryKeys(std::vector<string>&m_primaryTables, std::vector<string>&m_primaryFields);
		
		/*!
		* 
		**/
		string GetForeignKeyTable(const string& srcTableName,const string& srcFieldName);
		
		/*!
		* 
		**/
		unsigned char GetConnectiontype();

		//
		// General SQL interface including CRUD and TRANS etc
		//		
		/*!
		*
		**/
		bool RollbackTrans();

		/*!
		* General SQL execution against the whole DB
		*/ 
		bool Execute(const string &sql,bool isBlob=false);

		/*!
		* General SQL execution against the whole DB
		*/ 
		bool Execute(const string &sql,long long& oldTimeStamp,string sql2="",bool isBlob=false);

		/*!
		* General SQL execution against the whole DB
		*/ 
		bool BatchInsert(const string &sql);

		/*!
		* General SQL execution against the whole DB
		*/ 
		bool BatchInsertFlush();

		/*!
		* General SQL execution against the whole DB
		*/ 
		bool AddNew(std::vector<string>& colname,std::vector<string>& data,bool hasBlob=false,char* m_pBMPBuffer=0,int length=0);

		/*!
		* General SQL execution against the whole DB
		*/ 
		bool AddNewMultiblob(std::vector<string>& colname,std::vector<string>& data,bool hasBlob,std::vector<char*> m_pBMPBuffers,std::vector<long> lengths);

		/*!
		*
		**/
		long NextKey(const string &keyName, int increment);

		/*!
		*
		**/
		void SetNextKey(long nextId);

		/*!
		*
		**/
		void ResetKey();

		/*!
		*
		**/
		long GetRecordCount(const char *sql = 0);

		/*!
		* R
		**/
		bool FetchField(long index, string &value);

		/*!
		*
		**/
		bool MoveFirst(const char *sql = 0);

		/*!
		*
		**/
		bool MoveNext(const char *sql = 0);
		
		/*!
		*
		**/
		bool NextRecordset();

		/*!
		*
		**/
		bool MovePrevious(const char *sql = 0);

		/*!
		*
		**/
		bool MoveAbsolutePosition(long numRecords, const char *sql = 0);

		/*!
		* R
		**/
		bool FetchField(const char *fldName, string &value);

		/*!
		*  append bolb data from a file  to a given field
		**/
		bool AppendBlobField(const char *fldName,char* m_pBMPBuffer,int length=0 );
		bool AppendBlobFieldSTMT(const string &sql, std::vector<char*> &parameters, std::vector<unsigned long> &lengths);
		bool FetchBlobFieldSTMT(const string &sql, std::vector<char*> &parameters, std::vector<unsigned long> &lengths);
		bool IsMySQL();
		bool IsSQLite();
		/*!
		*  fetch a blob data in database to a buffer in RAM given a field
		**/
		 char* FetchBlobField(const char *fldName,  char* pBuffer,long &length);

		/*!
		*  delete bolb data from a file  to a given field
		*  use sql update statement. e.g. update blobtable set blobfield=NULL where id=3
		**/
		bool DeleteBlobField(const char *sql);

		/*!
		* open a sql statement to a recordset
		**/
		bool Open(const string &sql);

		//
		// dynamic or running 
		//
		/*!
		* Prepare Sql Statement with form insert into tab values(?,?,?)
		**/
		string PrepareSqlStatement(const string& tableName,int type,std::vector<int>& FilterFields=std::vector<int>());

		/*!
		*  Bind condition to Prepare Sql Statement
		**/
		bool BindWhere(string condition);

		/*!
		*  Return full Sql Statement
		**/
		string GetSqlStatement();

		/*!
		*  clear Sql Statement map
		**/
		bool ClearSqlStatement();

		//
		// pesistence object management
		//
		/*!
		*
		**/
		static void RegisterAdded(CAnyObject *obj);

		/*!
		*
		**/
		static void RegisterRemoved(CAnyObject *obj);

		/*!
		*
		**/
		static CAnyObject *GetRegistered(long idx, const string &keyname);

		//
		// connection and pool management
		//
		/*!
		*
		**/
		static bool InitDB(const DBSourceDesc &desc);
		
		/*!
		*
		**/
		static bool RegisterFunctor(CAnyFunctor *func);

		/*!
		*
		**/
		static bool EnableFunctor(bool isEnable);

		/*!
		*
		**/
		static bool ReConnectDB(const DBSourceDesc &desc);

		/*!
		*
		**/
		static void ReleaseDB(bool isOnlyCommit = false);

		/*!
		* release specified DB
		**/
		static void ReleaseDB(const DBSourceDesc &desc);

		/*!
		*
		**/
		static void SwitchToDB(string& dbURI);

		/*!
		*
		**/
		static string GetCurrentDB();

		/*!
		*
		**/
		static bool ExpandDBPool(const DBSourceDesc &desc, int poolsize);

		/*!
		*
		**/
		static bool LoadSchema(int dbName=0);
		
		/*!
		*
		**/
		bool LoadSchema(const string dbName);

		//
		// trans and version control management
		//
		/*!
		*
		**/
		bool BeginTrans();

		/*!
		*
		**/
		bool CommitTrans();

		/*!
		* Check if there is a collision when committing by centralized method. 
		* This method should be called before Commit method and don't use it in select statement
		* Input includes table name and sql operation type (DB_ADD,DA_DELETE or DB_UPDATE)
		**/
		bool IsCentralizedCollision( const string &tableName,int opType=0);

		/*!
		* Update centalized version table and synchronized with m_dbCentralizedTableVersion_map in DB after committing by centralized method. 
		* This method should be called after Commit method  and don't use it in select statement
		* Input includes table name and sql operation type (DB_ADD,DA_DELETE or DB_UPDATE)
		**/
		bool UpdateAndReloadVersionTable( const string &tableName,int opType);

		/*!
		* restore the database to a specific time
		* parameter restoreTime should be in format '2013-02-33 08:40'
		**/
		bool RestoreDB( const string &restoreTime);

		/*!
		* whether output sql sentence to window
		**/
		void SetShowInfoToWindow(bool isshowinfo);

		/*!
		* 
		**/
		string LockTables(std::vector<std::string>& tables,bool isRead=false);

		/*!
		* 
		**/
		bool UnLockTables(std::vector<std::string>& tables,bool isRead=false);

		/*!
		* 
		**/
		string LockRecord(string tableName,string fieldName,int recordIdx ,bool isRead=false);

		/*!
		* 
		**/
		bool UnLockRecord(string tableName,string fieldName,int recordIdx ,bool isRead=false);
		
		/*!
		* 
		**/
		void ClearLock();

	public:
		bool m_useTransaction;// rename operation cannot included in a transaction.
		// 
		CAnyAccessorImpl *m_impl;

	private:
		
		//
		static CAnyUnitWork m_unitwork;
		//
		static CAnyKeyGenerator *m_keyGenerator;
		//
		static CAnyFunctor* m_callback;

		//
		static bool m_isfunctorEnable;
		//
		int m_selected_db;

		//static string m_dbURI_vec[10];
		//static int cur;
		static std::vector<string> m_dbURI_vec;
		static string m_currentURI;	
	};
}

#endif