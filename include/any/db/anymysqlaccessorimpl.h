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
#ifndef __ANYDB_MYSQL_ACCESSORIMPL_H__
#define __ANYDB_MYSQL_ACCESSORIMPL_H__
#include <WinSock2.h>
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")

// Refer to _variant_t etc
#include "anyadobasic.h"

// Refer to EXPORT
#include "anydb.h"

// Refer to STL
#include "any/base/anystl.h"

// Refer to its parent
#include "anyaccessorimpl.h"

// 
#pragma warning(disable : 4146)
#pragma warning(disable : 4275)

//
namespace AnyDB
{
	// Forward class
	class CAnyMysqlConnection;
	class CAnyMysqlRecordset;
	
	/*!
	*
	**/
	class ANYDB_CLASS CAnyMysqlAccessorImpl : public CAnyAccessorImpl, public JTCMonitor
	{
		// Relatives
		friend class CAnyAccessorImpl;

		// For those records in memory respectively for each table
		typedef std::map<const std::string, CAnyMysqlRecordset*> RecordsetMap;
		typedef RecordsetMap::iterator set_itr;
		typedef RecordsetMap::const_iterator set_citr;

	protected:
		//
		//
		//
		/*!
		*
		**/
		CAnyMysqlAccessorImpl(const DBSourceDesc &source);

		/*!
		*
		**/
		virtual ~CAnyMysqlAccessorImpl();

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
		bool DoLoadSchema();

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
		void GetTableDesc(short index, DBTableDesc &table);

		/*!
		*
		**/
		long GetFieldCount(const DBTableDesc &table, bool isSchema);

		/*!
		*
		**/
		void RenameTable(std::map<std::string,std::string> nameMap);
		/*!
		*
		**/
		void GetFieldDesc(short index, DBFieldDesc &field, bool isSchema);
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
		unsigned char GetConnectiontype();

		//
		// SQL interface
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
		*
		**/
		bool RollbackTrans();

		/*!
		* General SQL execution against the whole DB
		*/ 
		bool Execute(const string &sql, bool isBlob,long long& oldTimeStamp,string sql2);

		/*!
		* General SQL execution against the whole DB
		*/ 
		bool Execute(const string &sql, bool isBlob);
		/*!
		* General SQL execution against the whole DB
		*/ 
		bool BatchInsert(const string &sql);
		/*!
		* General SQL execution against the whole DB
		*/ 
		bool BatchInsertFlush();
		/*!
		*
		**/
		bool AddNew(std::vector<string>& colname,std::vector<string>& data,bool hasBlob=false,char* m_pBMPBuffer=0,int length=0);
		/*!
		*
		**/
		bool AddNewMultiblob(std::vector<string>& colname,std::vector<string>& data,bool hasBlob,std::vector<char*> m_pBMPBuffers,std::vector<long> lengths);
		/*!
		* No use now, just as an extension for future
		*/ 
		bool AllInOneExecute(const string &sql, bool isBlob, const string &dbName);

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
		bool MovePrevious(const char *sql);

		/*!
		*
		**/
		bool MoveAbsolutePosition(long numRecords,const char *sql);

		/*!
		* R
		**/
		bool FetchField(const char *fldName, string &value);


		/*!
		* append bolb data from a file  to a given field
		**/
		bool AppendBlobField(const char *fldName, char* m_pBMPBuffer,int length=0 );
		bool AppendBlobFieldSTMT(const string &sql, std::vector<char*> &parameters, std::vector<unsigned long> &lengths);
		bool FetchBlobFieldSTMT(const string &sql, std::vector<char*> &parameters, std::vector<unsigned long> &lengths);
		bool IsMySQL();
		bool IsSQLite();
		/*!
		* fetch a blob data in database to a buffer in RAM given a field
		**/
		 char* FetchBlobField(const char *fldName,  char* pBuffer,long &length);

		/*!
		* the detail of fetch blob data
		**/
		 char* DoGetBlobFieldValue(_variant_t &variant,  char* pBuffer ,long lDataLength);
		/*!
		* open a sql statement to a recordset
		**/
		bool Open(const string &sql);

		/*!
		* Check if there is a collision when committing by centralized method. 
		* This method should be called before Commit method
		* Input includes table name and sql operation type (DB_ADD,DA_DELETE or DB_UPDATE)
		**/
		bool IsCentralizedCollision( const string &tableName,int opType,const string &dbName);

		/*!
		* Update centalized version table and synchronized with m_dbCentralizedTableVersion_map in DB after committing by centralized method. 
		* This method should be called after Commit method
		* Input includes table name and sql operation type (DB_ADD,DA_DELETE or DB_UPDATE)
		**/
		bool UpdateAndReloadVersionTable( const string &tableName,int opType,const string &dbName);

		/*!
		* No use now, just as an extension for future (can be used in AllInOneExecute method)
		**/
		bool ExtractTableNameFromSql(string sql,string &tableName,int& opType);



		/*!
		* restore the ref_table_version to an old history version
		**/
		bool RestoreVersionTable(const string &restoreTime);
		

		/*!
		* restore the database to a specific time
		* parameter restoreTime should be in format '2013-02-33 08:40'
		**/
		bool RestoreDB( const string &restoreTime);

		/*!
		* R
		**/
		string PrepareSqlStatement(const string& tableName,int type, std::vector<int>& FilterFields=std::vector<int>());

		
		/*!
		*  Bind data to Prepare Sql Statement
		**/
		bool BindInt(int index,int value);

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		bool BindLong(int index,long value);

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		bool BindString(int index,string value);

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		bool BindDouble(int index,double value);

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		bool BindFloat(int index,float value);

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		bool BindCharArray(int index,char* value);

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		bool BindChar(int index,char value);

		/*!
		*  Bind data to Prepare Sql Statement
		**/
		bool BindBool(int index,bool value);

		/*!
		*  Bind condition to Prepare Sql Statement
		**/
		bool BindWhere(string condition);
		/*!
		*  Bind all fileds
		**/
		//template<typename AgmClass>
		//bool BindAll(AgmClass &myClass,std::vector<void*> memberAddressVec, std::vector<int>& FilterFields=std::vector<int>());

		//template<typename T>
		//bool BindAll2(T myclass){
		//	const Class &myClass=myclass.getClass();
		//	std::vector<void*> memberAddressVec;

		//	myclass.GetMemberAddressVec(memberAddressVec);
		//	//PrepareSqlStatement(/*m_fuzzyScoreTable.c_str()*/,DB_ADD);
		//	//BindAll(myClass,memberAddressVec);
		//}
		/*!
		*  Bind condition to Prepare Sql Statement
		**/
		int PreBind(int index);

		/*!
		*  Return full Sql Statement
		**/
		string GetSqlStatement();

		/*!
		*  clear Sql Statement map
		**/
		bool ClearSqlStatement();

		/*!
		*  Return full Sql Statement
		**/
		bool GetColumsName(const string &tableName,std::vector<string>& columVec,std::vector<int>& FilterFields=std::vector<int>());

		
		/*!
		* 
		**/
		string GetForeignKeyTable(const string& srcTableName,const string& srcFieldName);

		/*!
		*
		**/
		bool IsConnectionException();

		/*!
		* whether output sql sentence to window
		**/
		void SetShowInfoToWindow(bool isshowinfo);

		/*!
		*
		**/
		string GetTableName(string& sql);

		/*!
		*
		**/
		string Trim(string& sql);
		/*!
		*
		**/
		string GetWhereClause(string& sql);
		
		/*!
		*  
		**/
		string LockTables(std::vector<std::string>& tables,bool isRead);

		/*!
		*  
		**/
		bool UnLockTables(std::vector<std::string>& tables,bool isRead);

		/*!
		*  
		**/
		string LockRecord(string& tableName,string& fieldName,int recordIdx ,bool isRead);	

		/*!
		*  
		**/
		bool UnLockRecord(string& tableName,string& fieldName,int recordIdx ,bool isRead);	
		
		/*!
		*  
		**/
		void ClearLock();
	private:
		//
		//
		//
		/*!
		*
		**/
		void DoFreeCache();

		//
		//
		//
		/*!
		*
		**/
		bool DoGetFieldValue(_variant_t &variant, string &value);

		/*!
		*
		**/
		bool IsTableExist(const char *tableName);

	private:
		// One connection corresponding to one gate
		CAnyMysqlConnection *m_connection;
		// Recordset for those records from different tables
		RecordsetMap m_recordsets;
		// Current record set
		CAnyMysqlRecordset *m_curRecordset;

		//sourceType
		unsigned char m_sourceType;


		string m_generatedSQL;

		std::vector<int> m_bindedParameters;
		map<TableNameAndOpType,string> m_cachedPrepareSQLMap;
		string m_insertcache;
		int m_insertcacheCount;
	};


}
#endif // __ANYDB_Mysql_GATEWAY_H__
