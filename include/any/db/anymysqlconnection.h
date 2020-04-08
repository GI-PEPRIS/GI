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
#ifndef __ANYDB_MYSQL_CONNECTION_H__
#define __ANYDB_MYSQL_CONNECTION_H__

// Refer to EXPORT
#include "anydb.h"
#include "anymysqlaccessorimpl.h"

// Refer to basic
#include "anyaccessorbasic.h"

// Refer to ADO relatives
#include "anyadobasic.h"

// Refer to STL
#include "any/base/anystl.h"
#include <map>
// Namespace
namespace AnyDB
{
	/*!
	*
	*/
	class ANYDB_CLASS CAnyMysqlConnection
	{
		/*!
		*
		**/
		struct ForeignKeySchema
		{
			string m_pkTable;
			string m_pkField;
			string m_fkTable;
			string m_fkField;
		};
		typedef std::vector<ForeignKeySchema> ForeignKeyVector;

		/*!
		*
		**/
		struct PrimaryKeySchema
		{
			string m_table;
			string m_field;
		};
		typedef std::vector<PrimaryKeySchema> PrimaryKeyVector;

		// Relatives
		friend class CAnyMysqlAccessorImpl;
		friend class CAnyMysqlRecordset;

	protected:
		//
		//
		//
		/*!
		*
		**/
		CAnyMysqlConnection(const DBSourceDesc &sourcen,CAnyMysqlAccessorImpl* parent);

		/*!
		*
		**/
		~CAnyMysqlConnection();

	protected:
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
		//
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

		//
		//
		//
		/*!
		*
		**/
		bool CreateDB(const char *adoSource);

		/*!
		*
		**/
		bool CreateTable(const DBTableDesc &table);

		/*!
		*
		**/
		bool CreateField(const DBFieldDesc &field);

		//
		//
		//
		/*!
		*
		**/
		bool Connect(const DBSourceDesc &source);

		/*!
		*
		**/
		bool LoadSchema();

		/*!
		*
		**/
		MYSQL_RES* CAnyMysqlConnection::Execute(const char *sql,bool &result, _variant_t& ra=_variant_t(0L));

		/*!
		*
		**/
		bool Disconnect();

		//
		//
		//
		/*!
		*
		**/
		MYSQL* GetConnection();

		/*!
		*
		**/
		bool IsOpen();

		//
		//
		//
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
		void RenameTable(std::map<std::string,std::string> nameMap);

		/*!
		*
		**/
		long GetFieldCount(const DBTableDesc &table);

		/*!
		*
		**/
		void GetFieldDesc(short index, DBFieldDesc &field);

		/*!
		*
		**/
		void RenameField(std::string tablename ,std::map<std::string,std::string> nameMap);
		//
		//
		//
		/*!
		*
		**/
		bool GetForeignDesc(const DBFieldDesc &field, DBFieldDesc &foreign);

		/*!
		*
		**/
		bool IsTableExist(const char *tableName);

		/*!
		*
		**/
		bool IsPrimaryKey(const DBFieldDesc &field);

		/*!
		*
		**/
		bool IsForeignKey(const DBFieldDesc &field);
	
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
		//bool ReConnect();

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
		bool AppendBlobFieldSTMT( const string &sql, std::vector<char*> &parameters, std::vector<unsigned long> &lengths);
		bool FetchBlobFieldSTMT( const string &sql, std::vector<char*> &parameters, std::vector<unsigned long> &lengths);
	private:
		//
		//
		//
		/*!
		*
		**/
		string DoMakeSource(const DBSourceDesc &source);

		/*!
		*
		**/
		bool OpenForeignKeys();

		/*!
		*
		**/
		bool OpenPrimaryKeys();

		/*!
		*
		**/
		static int GetAnyFieldType(short adoType);

		/*!
		*
		**/
		static int GetAdoFieldType(short anyType);
	protected:
		// Connection handle
		MYSQL* m_connection;
		MYSQL_STMT* m_connection_stmt;
		//
		string m_adoSource;
		//sourceType
		unsigned char m_sourceType;
		//
		ForeignKeyVector m_foreignKeys;
		//
		PrimaryKeyVector m_primaryKeys;

		CAnyMysqlAccessorImpl* m_parent;

		// show sql sentence to window
		bool m_isshowinfo;
	};
}
#endif