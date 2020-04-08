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
#ifndef __ANYDB_ACCESSOR_IMPL_H__
#define __ANYDB_ACCESSOR_IMPL_H__

// Refer to _variant_t etc
#include "anyadobasic.h"

// Refer to EXPORT etc
#include "anydb.h"

// Refer to JTC
#include "any/thread/jtc.h"

// Refer to basic defintion
#include "anyaccessorbasic.h"

// any functor
#include "any/base/anymediator.h"
//#include "anybase\agm\reflection.hpp" // compile conflict with RCF
using namespace AnyBase;

//
namespace AnyDB
{
	/*!
	*
	**/
	class ANYDB_CLASS CAnyAccessorImpl
	{
		// Relatives
		friend class CAnyAccessor;

		// Max number of gates
		const static int MAX_CONNECTION = 50;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyAccessorImpl();

		/*!
		*
		**/
		virtual ~CAnyAccessorImpl();

	public:
		/*!
		*
		**/
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
		virtual bool DoLoadSchema() = 0;

		/*!
		*
		**/
		virtual bool CreateTable(const DBTableDesc &table) = 0;

		/*!
		*
		**/
		virtual bool CreateField(const DBFieldDesc &field) = 0;

		/*!
		*
		**/
		virtual long GetTableCount() = 0;

		/*!
		*
		**/
		virtual void GetTableDesc(short index, DBTableDesc &table) = 0;

		/*!
		*
		**/
		virtual void RenameTable(std::map<std::string,std::string> nameMap)=0;
		/*!
		*
		**/
		virtual long GetFieldCount(const DBTableDesc &table, bool isSchema) = 0;

		/*!
		*
		**/
		virtual void GetFieldDesc(short index, DBFieldDesc &field, bool isSchema) = 0;
		/*!
		*
		**/
		virtual void RenameField(std::string tablename ,std::map<std::string,std::string> nameMap) =0;
		/*!
		*
		**/
		virtual bool GetForeignDesc(const DBFieldDesc &field, DBFieldDesc &foreign) = 0;

		/*!
		*
		**/
		virtual bool IsPrimaryKey(const DBFieldDesc &fDesc) = 0;

		/*!
		*
		**/
		virtual bool IsForeignKey(const DBFieldDesc &fDesc) = 0;

		/*!
		*
		**/
		virtual void GetAllForeignKeys(std::vector<string>&m_pkTables, std::vector<string>&m_pkFields, std::vector<string>&m_fkTables, std::vector<string>&m_fkFields) = 0;

		/*!
		*
		**/
		virtual void GetAllPrimaryKeys(std::vector<string>&m_primaryTables, std::vector<string>&m_primaryFields) = 0;
	
		/*!
		*
		**/
		virtual unsigned char GetConnectiontype() = 0;

		//
		// SQL interface
		//		
		/*!
		*
		**/
		virtual bool BeginTrans() = 0;

		/*!
		*
		**/
		virtual bool CommitTrans() = 0;

		/*!
		*
		**/
		virtual bool RollbackTrans() = 0;

		/*!
		* General SQL execution against the whole DB
		*/ 
		virtual bool Execute(const string &sql,bool isBlob,long long& oldTimeStamp,string sql2) = 0;

			/*!
		* General SQL execution against the whole DB
		*/ 
		virtual bool Execute(const string &sql,bool isBlob) = 0;

		
		/*!
		* General SQL execution against the whole DB
		*/ 
		virtual bool BatchInsert(const string &sql) = 0;
			/*!
		* General SQL execution against the whole DB
		*/ 
		virtual bool BatchInsertFlush() = 0;

		/*!
		* General SQL execution against the whole DB
		*/ 
		virtual bool AddNew(std::vector<string>& colname,std::vector<string>& data,bool hasBlob=false,char* m_pBMPBuffer=0,int length=0)=0;

		/*!
		* General SQL execution against the whole DB
		*/ 
		virtual bool AddNewMultiblob(std::vector<string>& colname,std::vector<string>& data,bool hasBlob,std::vector<char*> m_pBMPBuffers,std::vector<long> lengths)=0;

		/*!
		*
		**/
		virtual long GetRecordCount(const char *sql) = 0;

		/*!
		* R
		**/
		virtual bool FetchField(long index, string &value) = 0;

		/*!
		*
		**/
		virtual bool MoveFirst(const char *sql) = 0;

		/*!
		*
		**/
		virtual bool MoveNext(const char *sql) = 0;

		/*!
		*
		**/
		virtual bool NextRecordset() = 0;

		/*!
		*
		**/
		virtual bool MovePrevious(const char *sql) = 0;

		/*!
		*
		**/
		virtual bool MoveAbsolutePosition( long numRecords,const char *sql) = 0;
		
		/*!
		* 
		**/
		virtual bool AppendBlobField(const char *fldName,char* m_pBMPBuffer,int length=0) = 0;
		virtual bool AppendBlobFieldSTMT(const string &sql, std::vector<char*> &parameters, std::vector<unsigned long> &lengths)=0;
		virtual bool FetchBlobFieldSTMT(const string &sql, std::vector<char*> &parameters, std::vector<unsigned long> &lengths)=0;
		virtual bool IsMySQL()=0;
		virtual bool IsSQLite() = 0;
		/*!
		* R
		**/
		virtual bool FetchField(const char *fldName, string &value) = 0;

		/*!
		* R
		**/
		virtual  char* FetchBlobField(const char *fldName,  char* pBuffer,long &length) = 0;
		
		/*!
		* recordset open method
		*/ 
		virtual bool Open(const string &sql) = 0;

		/*!
		* Check if there is a collision when committing by centralized method. 
		* This method should be called before Commit method
		* Input includes table name and sql operation type (DB_ADD,DA_DELETE or DB_UPDATE)
		**/
		virtual bool IsCentralizedCollision( const string &tableName,int opType,const string &dbName) = 0;

		/*!
		* Update centalized version table and synchronized with m_dbCentralizedTableVersion_map in DB after committing by centralized method. 
		* This method should be called after Commit method
		* Input includes table name and sql operation type (DB_ADD,DA_DELETE or DB_UPDATE)
		**/
		virtual bool UpdateAndReloadVersionTable( const string &tableName,int opType,const string &dbName)=0;

		
		/*!
		*  No use now, just as an extension for future
		*/ 
		virtual bool AllInOneExecute(const string &sql, bool isBlob,const string &dbName)=0;

		/*!
		* restore the database to a specific time
		* parameter restoreTime should be in format '2013-02-33 08:40'
		**/
		virtual bool RestoreDB( const string &restoreTime)=0;

		/*!
		* Prepare Sql Statement with form insert into tab values(?,?,?)
		* 
		**/
		virtual string PrepareSqlStatement(const string& tableName,int type,std::vector<int>& FilterFields=std::vector<int>())=0;

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		virtual bool BindInt(int index,int value)=0;

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		virtual bool BindLong(int index,long value)=0;

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		virtual bool BindString(int index,string value)=0;

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		virtual bool BindDouble(int index,double value)=0;

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		virtual bool BindFloat(int index,float value)=0;

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		virtual bool BindCharArray(int index,char* value)=0;

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		virtual bool BindChar(int index,char value)=0;

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		virtual bool BindBool(int index,bool value)=0;

		/*!
		*  Bind condition to Prepare Sql Statement
		**/
		virtual bool BindWhere(string condition)=0;
		/*!
		*  Bind all fileds
		**/
		//template<typename AgmClass>
		//bool BindAll(AgmClass &myClass,std::vector<void*> memberAddressVec, std::vector<int>& FilterFields=std::vector<int>());

		/*template<typename T>
		virtual	bool BindAll(T myclass)=0;*/
		/*!
		*  Return full Sql Statement
		**/
		virtual string GetSqlStatement()=0;

		/*!
		*  clear  Sql Statement map
		**/
		virtual bool ClearSqlStatement()=0;
		
		/*!
		* 
		**/
		virtual string GetForeignKeyTable(const string& srcTableName,const string& srcFieldName)=0;


		virtual bool IsConnectionException()=0;	

		/*!
		* whether output sql sentence to window
		**/
		virtual void SetShowInfoToWindow(bool isshowinfo)=0;
		
		/*!
		*  
		**/
		virtual string LockTables(std::vector<std::string>& tables,bool isRead)=0;	

		/*!
		*  
		**/
		virtual bool UnLockTables(std::vector<std::string>& tables,bool isRead)=0;	

		/*!
		*  
		**/
		virtual string LockRecord(string& tableName,string& fieldName,int recordIdx ,bool isRead)=0;	

		/*!
		*  
		**/
		virtual bool UnLockRecord(string& tableName,string& fieldName,int recordIdx ,bool isRead)=0;	
		
		/*!
		*  
		**/
		virtual void ClearLock()=0;	
	protected:
		//
		// Connection pool mechanism
		//
		/*!
		* Those gates in cache only corresponds to one data source
		**/
		static bool InitConnectionPool(const DBSourceDesc &source);

		/*!
		* 
		**/
		static void ReleaseConnectionPool();

		/*!
		* 
		**/
		static bool ReConnectionPool(const DBSourceDesc &source);
		/*!
		* 
		**/
		static void ReleaseOneConnectionPool(string name);

		/*!
		* 
		**/
		static bool ExpandConnectionPool(const DBSourceDesc &source, int poolsize);

		/*!
		*
		**/
		static CAnyAccessorImpl *GetConnection(string dbName);

		/*!
		*
		**/
		static bool LoadSchema(string dbName);

		/*!
		* Load Centralized Version Table to m_dbCentralizedTableVersion_map
		**/
		static bool LoadCentralizedVersionTable(const DBSourceDesc &source);

		
		/*!
		*  call back when failed
		**/
		static bool DoCallBack();

		/*!
		*  
		**/
		static bool RegisterCallBack(CAnyFunctor *func);

		/*!
		*  
		**/
		static bool EnableFunctor(bool isEnable);
		//
		//
		//
		/*!
		* Free memory cache for current connection before recycling
		**/
		virtual void DoFreeCache() = 0;

		/*!
		* take gateway back
		**/
		void RecycleConnection(string dbName);
	public:
		string m_username;
		string m_dbname;
		string m_userprivilege;
		unsigned char m_dbtype;
		int m_userid;
		int m_fieldid;
		bool m_viewall;

	protected:
		// Class-level protection
		static JTCMonitor m_monitor;
		// The cache mechanism of gateway corrsponding to the same dir
		// or not, up to ur decision
		static std::map<string,std::deque<CAnyAccessorImpl*>> m_connections;

		//a map to contain centralized version table, key stands for the dbsource.
		static std::map<string,DBVersionTable> m_dbCentralizedTableVersion_map;
		static CAnyFunctor* m_callback;
		static bool m_isfunctorEnable;
	};
}
#endif