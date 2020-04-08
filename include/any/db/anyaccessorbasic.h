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
#ifndef __ANYDB_ACCESSOR_BASIC_H__
#define __ANYDB_ACCESSOR_BASIC_H__

// Refer to STL
#include "any/base/anystl.h"

//
namespace AnyDB
{
	/*!
	* db operation type
	**/
	enum DBOperation
	{
		DB_SELECT=1,
		DB_ADD=1 << 1,
		DB_UPDATE=1 << 2,
		DB_DELETE=1 << 3,
		DB_ADD_MASK=0x000000FF,
		DB_ADD_UNMASK=0xFFFFFF00,
		DB_UPDATE_MASK=0x0000FF00,
		DB_UPDATE_UNMASK=0xFFFF00FF,
		DB_DELETE_MASK=0x00FF0000,
		DB_DELETE_UNMASK=0xFF00FFFF
	};
	
		/*!
	* db commit state type
	**/
	enum DBCommitType
	{
	
		DB_COMMIT_ERROR=0,
		DB_COMMIT_SUCCESS,
		DB_OLD_VERSION=64
	
	};

	/*!
	* varieties of data source
	**/
	enum DBSourceType
	{
		DBS_Unknown = -1,
		DBS_SQLSERVER,
		DBS_MYSQL, 
		DBS_MDB,
		DBS_SQLITE,
		DBS_EXCEL,
		DBS_ORACLE,
		DBS_Max
	};
    
	static std::string DBSourceName[] = {
		"SQL Server",
		"MySQL",
		"Access",
		"Sqlite",
		"Excel",
		"Oracle",
		"Unknown",
	};

	enum DBAccessType
	{
		DBA_ADO,
		DBA_ODBC,
		DBA_NATIVE_MYSQL_API,
	};

	/*!
	*
	**/
	enum DBSourceMode
	{
		DBM_Unknown = 0,
		DBM_Read = 1 << 1,
		DBM_Write = 1 << 2,
		DBM_ReadWrite = 1 << 3,
		DBM_ShareDenyRead = 1 << 4,
		DBM_ShareDenyWrite = 1 << 5,
		DBM_ShareExclusive = 1 << 6,
		DBM_ShareDenyNone = 1 << 7
	};

	/*!
	*
	**/
	enum DBFieldType
	{
		DBF_Unknown = 0,
		DBF_Binary,
		DBF_Bool,
		DBF_Float,
		DBF_Int,
		DBF_Text,
		DBF_LongText,
		DBF_LongBinary,
		DBF_Date
	};

	/*!
	*
	**/
	struct DBConnectionDesc
	{
		// default datebase
		string m_default;
		// provider name
		string m_provider;
		// conneciton state
		long m_state;
		// priviledge mode
		unsigned long m_mode;
		// timeout 
		unsigned long m_timeout;

		/*!
		*
		**/
		DBConnectionDesc() : m_default(""), m_provider(""), m_state(0), m_mode(DBM_ReadWrite), m_timeout(unsigned(-1))
		{
		}

		/*!
		*
		**/
		const DBConnectionDesc &operator=(const DBConnectionDesc &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_default = other.m_default;
			m_provider = other.m_provider;
			m_state = other.m_state;
			m_mode = other.m_mode;
			m_timeout = other.m_timeout;

			return *this;
		}
	};

	/*!
	*
	**/
	struct DBSourceDesc
	{
		// source type mentioned by DBSourceType
		unsigned char m_type;
		unsigned char m_access_type;
		// Connection setting
		DBConnectionDesc m_conn; // deprecated
		short m_connections;

		// source name such as IP address etc
		string m_srcName;
		// db name
		string m_dbName;
		// user name
		string m_user;
		// password
		string m_pwd;

		/*!
		*
		**/
		DBSourceDesc() : m_connections(10), m_access_type(DBA_ADO), m_type(DBS_Unknown), m_srcName(""), m_dbName(""), m_user(""), m_pwd("")
		{
		}

		/*!
		*
		**/
		const DBSourceDesc &operator=(const DBSourceDesc &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_connections = other.m_connections;
			m_access_type = other.m_access_type;
			m_type = other.m_type;
			m_conn = other.m_conn;
			m_srcName = other.m_srcName;
			m_dbName = other.m_dbName;
			m_user = other.m_user;
			m_pwd = other.m_pwd;

			return *this;
		}

		/*!
		*
		**/
		bool operator==(const DBSourceDesc &other)
		{
			if(m_type != other.m_type ||
				m_access_type != other.m_access_type ||
				//m_conn != other.m_conn ||
				m_srcName != other.m_srcName || 
				m_dbName != other.m_dbName ||
				m_user != other.m_user ||
				m_pwd != other.m_pwd)
			{
				return false;
			}

			return true;
		}
	};

	/*!
	*
	**/
	struct DBTableDesc
	{
		// table name
		string m_name;
		// corresponding sql sentence
		string m_sql;

		/*!
		*
		**/
		DBTableDesc() : m_name(""), m_sql("")
		{
		}

		/*!
		*
		**/
		DBTableDesc(const DBTableDesc &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const DBTableDesc &operator=(const DBTableDesc &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_name = other.m_name;
			m_sql = other.m_sql;

			return *this;
		}
	};

	/*!
	*
	**/
	struct DBRecordDesc
	{
	};

	/*!
	*
	**/
	struct DBFieldDesc
	{
		// table name
		string m_table;
		// field name
		string m_name;
		// desicription
		string m_description;
		// field type
		short m_type;
		// field length
		short m_length;
		// is index
		bool m_isIndexed;
		// ordinal position
		int m_order;

		/*!
		*
		**/
		DBFieldDesc() : m_table(""), m_name(""), m_description(""),
			m_type(DBS_Unknown), m_length(0), m_isIndexed(false), m_order(-1)
		{
		}

		/*!
		*
		**/
		DBFieldDesc(const DBFieldDesc &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const DBFieldDesc &operator=(const DBFieldDesc &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_table = other.m_table;
			m_name = other.m_name;
			m_description = other.m_description;
			m_type = other.m_type;
			m_length = other.m_length;
			m_isIndexed = other.m_isIndexed;
			m_order = other.m_order;

			return *this;
		}
	};
	
	/*!
	* 
	**/
	struct VersionTablePair
	{
		VersionTablePair(){}
		VersionTablePair(string v1,long v2,int v3)
		{
			tableName=v1;
			timestamp=v2;
			operationState=v3;
		}

		string tableName;
		long timestamp;
		int operationState;//every 8 bits represent a ADD|UPDATE|DELETE state from 0-255 
		string author;
		string curtime;
	
	};

	/*!
	*
	**/
	struct DBVersionTable
	{
		std::map<string,VersionTablePair> vtPair;
	};

	/*!
	* struct used for generate sql statement by table name and opertion type
	**/
	struct TableNameAndOpType
	{
		TableNameAndOpType(string v1,int v2)
		{
			tableName=v1;
			operationType=v2;
		}
		bool operator <(const TableNameAndOpType& rs)const
		{
			if(tableName<rs.tableName)
			{
				return true;
			}
			else if(tableName==rs.tableName)
			{
				return operationType<rs.operationType;
			}
			else
			{
				return false;
			}
		}
		string tableName;
		int operationType;
	};
}

#endif