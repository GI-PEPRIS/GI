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
#ifndef __ANYDB_SQLITE_RECORDSET_H__
#define __ANYDB_SQLITE_RECORDSET_H__
#include "sqlite3.h"
// Refer to EXPORT
#include "anydb.h"

// Refer to STL
#include "any/base/anystl.h"

// Refer to ADO's relatives
#include "anyadobasic.h"

// refer to dbfielddesc
#include "anyaccessorbasic.h"

// Namespace
namespace AnyDB
{
	// Forward class
	class CAnySqliteConnection;

	/*!
	* definition of CAnyMysqlRecordset
	*/
	class ANYDB_CLASS CAnySqliteRecordset
	{
		// Relatives
		friend class CAnySqliteAccessorImpl;

	protected:
		//
		//
		//
		/*!
		*
		**/
		CAnySqliteRecordset(CAnySqliteConnection *connection, const char *sql, sqlite3_stmt* recordset = 0);

		/*!
		*
		**/
		~CAnySqliteRecordset();

	protected:
		//
		//
		//
		/*!
		*
		**/
		void Reset(const char *sql, sqlite3_stmt* recordset = 0);

		/*!
		* Deprecated function
		**/
		bool Open(const char *sql);
		
		/*!
		*
		**/
		bool IsOpen();

		/*!
		*
		**/
		bool Close();

		//
		// Deprecated functions
		//
		/*!
		*
		**/
		bool AddNew(std::vector<string>& colname,std::vector<string>& data,bool hasBlob=false,char* m_pBMPBuffer=0,int length=0);

		/*!
		*
		**/
		bool AddNewMultiblob(std::vector<string>& colname,std::vector<string>& data,bool hasBlob,std::vector<char*> m_pBMPBuffers,std::vector<long> Bufferlengths);
		/*!
		*
		**/
		bool Update();

		/*!
		*
		**/
		bool CancelUpdate();

		/*!
		*
		**/
		bool Delete(AffectEnum AffectRecords);

		//
		//
		//
		/*!
		*
		**/
		long GetRecordCount();

		/*!
		*
		**/
		bool IsBOF();

		/*!
		*
		**/
		bool IsEOF();

		/*!
		*
		**/
		bool MoveFirst();
		
		/*!
		*
		**/
		bool MoveLast();

		/*!
		*
		**/
		bool MoveNext();

		/*!
		*
		**/
		_RecordsetPtr NextRecordset();

		/*!
		*
		**/
		bool MovePrev();

		/*!
		*
		**/
		bool Move(long numRecords);

		//
		//
		//
		/*!
		*
		**/
		long GetFieldCount() const;

		/*!
		*
		**/
		bool GetFieldValue(const char *fieldName, _variant_t &value) const;		

		/*!
		*
		**/
		bool GetFieldValue(long index, _variant_t &value) const;

		/*!
		* get blob data to value given a field name
		**/
		bool GetBlobFieldValue(const char *fieldName, _variant_t &value,long &lDataLength) const;
		bool GetBlobFieldValueSqlite( const char *fieldName, char* &pBuffer ,long &lDataLength) const;

		/*!
		* append blob data value to a given field
		**/
		bool AppendBlobFieldValue(const char *fieldName, _variant_t &value) const;

		/*!
		*
		**/
		bool SetFieldValue(const char *fieldName, const _variant_t &value);

		/*!
		*
		**/
		void GetFieldDesc(long index, DBFieldDesc &fDesc);

	private:
		//
		//
		//
		/*!
		*
		**/
		bool Release();

	private:
		// host connection
		CAnySqliteConnection *m_connection;
		// its corresponding sql
		string m_sql;
		// records
		sqlite3_stmt *m_recordset;
		// rows count
		int m_nrows;
	};
}

#endif // __ANYDB_MYSQL_GATEWAY_H__
