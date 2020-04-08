/*!
 * The AnyBase package of PetroCOVERY Solution is a collection of native C++ classes that 
 * implement the fundamental algorithms & operations required to 
 * satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYBASE_HASH_H__ 
#define __ANYBASE_HASH_H__


// Refer to EXPORT etc
#include "anydb.h"

// Namespace AnyBase
namespace AnyDB
{
	class ANYDB_CLASS CAnyHash
	{
		//
		static const unsigned int NORECORD = -1;
		static const unsigned int LOWFIND = 1;
		static const unsigned int LOWUSED = 2;
		static const unsigned int HIGHFIND = 4;
		static const unsigned int HIGHUSED = 8;

		/*!
		* Description of the same key group repeatedly belonging to 
		* the same hash results
		**/
		struct HashRecord
		{
			// index to next key
			unsigned int m_next;	
			// data for current entry
			unsigned char *m_data;

			/*!
			* Initialization
			**/
			HashRecord() : m_next(0), m_data(0)
			{
			}
		};

		/*!
		* \breif 
		* Definition of Hash Container
		**/
		struct HashContainer
		{
			// Keys' position in current buffer allocation
			unsigned int m_keyOffset;
			// Length of key if const length
			unsigned int m_keyLength;

			// Number of records
			unsigned int m_records;
			// binary length?
			unsigned int m_blength;
			// Inidcator of kinds of has usages
			unsigned int m_flags;

			// Place for hash_keys
			unsigned int m_maxRecords;
			unsigned int m_increment;
			unsigned char *m_buffer;

			int m_curpos;
			/*!
			* Initialization
			**/
			HashContainer() : m_keyOffset(0), m_keyLength(0), m_records(0), 
				m_blength(0), m_flags(0), m_maxRecords(0), m_increment(0), m_buffer(0),m_curpos(0)
			{
			}

		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyHash();

		/*!
		*
		**/
		~CAnyHash();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool Init(unsigned int size, unsigned int keyOffset, unsigned int keyLength, unsigned int flags);

		/*!
		*
		**/
		void Free();

		/*!
		*
		**/
		void Reset();

		//
		//
		//
		/*!
		*
		**/
		unsigned char *GetElement(unsigned int idx);

		/*!
		*
		**/
		unsigned char *Search(const unsigned char *key, unsigned int length);

		//
		//
		//
		/*!
		*
		**/
		bool Insert(const unsigned char *data);

		/*!
		*
		**/
		bool Delete(const unsigned char *data);

		/*!
		*
		**/
		bool Update(const unsigned char *data, const unsigned char *oldKey, unsigned int oldKeyLength);

	private:
		//
		//
		//
		/*!
		*
		**/
		void FreeElements();

		/*!
		*
		**/
		unsigned char *First(const unsigned char *key, unsigned int length, unsigned int &state);

		/*!
		*
		**/
		unsigned char *Next(const unsigned char *key, unsigned int length, unsigned int curIdx);

		//
		//
		//
		//
		// Basic Hash's functions
		//
		/*!
		*
		**/
		unsigned int HashCalc(const unsigned char *key, unsigned int length);

		/*!
		*
		**/
		void HashSort(const unsigned char *key, unsigned int length, unsigned int *first, unsigned int *second);

		/*!
		*
		**/
		unsigned int HashMask(unsigned int hashnr, unsigned int buffmax, unsigned int maxlength);

		/*!
		*
		**/
		unsigned int HashRecMask(HashRecord *curRecord, unsigned int buffmax, unsigned int maxlength);

		/*!
		*
		**/
		unsigned int Rec_Hashnr(const unsigned char *data);

		/*!
		*
		**/
		int HashCmp(HashRecord *curRecord, const unsigned char *key, unsigned int length);

		/*!
		*
		**/
		unsigned char *HashKey(const unsigned char *record, unsigned int &length);

		/*!
		*
		**/
		void MoveLink(HashRecord *curRecord, unsigned int find, unsigned int nextlink, unsigned int newlink);

	private:
		// Corresponding hash container
		HashContainer m_hash;
	};

}

#endif