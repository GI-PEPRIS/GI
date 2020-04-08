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
#ifndef __ANYDB_KEY_GENERATOR_H__
#define __ANYDB_KEY_GENERATOR_H__

// refer to EXPORT etc
#include "anydb.h"

// refer to current connection
#include "anyaccessor.h"

// refer to thread issues
#include "any/thread/jtc.h"

//
namespace AnyDB
{
	// Forward class
	class CAnyAccessor;

	/*!
	*
	**/
	class ANYDB_CLASS CAnyKeyGenerator : public JTCMonitor
	{
		// relatives
		friend class CAnyAccessor;

	protected:
		//
		//
		//
		/*!
		*
		**/
		CAnyKeyGenerator(CAnyAccessor *accessor, const string &keyName, int increment);

		/*!
		*
		**/
		~CAnyKeyGenerator();

	public:
		//
		//
		//
		/*!
		*
		**/
		unsigned long NextKey(CAnyAccessor *accessor);

		/*!
		*
		**/
		void SetNextKey(CAnyAccessor *accessor, long nextId);

		/*!
		*
		**/
		void Reset()
		{
			// tell generator to reload records
			m_nextId = m_maxId;
		}

	private:
		//
		//
		//
		/*!
		*
		**/
		void ReserveIds();

		/*!
		*
		**/
		void Load(long &nextId, long &maxIdx);

		/*!
		*
		**/
		void Commit(long nextId, long maxId);

	private:
		// keep select, update etc operations in the same connection
		// and set auto commit is false
		CAnyAccessor *m_accessor;

		// null means for the whole DB
		string m_keyName;
		// the current id
		long m_nextId;
		// reserved max id
		long m_maxId;
		// step
		int m_incrementBy;
	};
}

#endif