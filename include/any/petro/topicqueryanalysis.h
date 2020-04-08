/*!
 * The AnyPetro of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the domain data model etc.
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
#ifndef __ANYPETRO_TOPIC_QUERY_ANALYSIS_H__
#define __ANYPETRO_TOPIC_QUERY_ANALYSIS_H__

// refer to export macro
#include "anypetro.h"

// refer to string
#include "any/base/anystl.h"

// refer to accessor
#include "any/db/anyaccessor.h"
using namespace AnyDB;

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CTopicQueryAnalysis
	{
	public:
		/*!
		*
		**/
		struct TopicQuerySQL
		{
			long m_topicIdx;
			string m_topicName;
			string m_aliasName;
			string m_selectColumns;
			string m_fromTables;
			string m_whereCondition;
			string m_groupColumns;
			string m_orderColumns;

			/*!
			*
			**/
			TopicQuerySQL() : m_topicIdx(0), m_topicName(""), m_aliasName(""), m_selectColumns(""), m_fromTables(""), m_whereCondition(""), m_groupColumns(""), m_orderColumns("")
			{
			}

			/*!
			*
			**/
			const TopicQuerySQL &operator=(const TopicQuerySQL &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_topicIdx = other.m_topicIdx;
				m_topicName = other.m_topicName;
				m_aliasName = other.m_aliasName;
				m_selectColumns = other.m_selectColumns;
				m_fromTables = other.m_fromTables;
				m_whereCondition = other.m_whereCondition;
				m_groupColumns = other.m_groupColumns;
				m_orderColumns = other.m_orderColumns;

				return *this;
			}
		};
		typedef std::vector<TopicQuerySQL> TopicVector;
		typedef TopicVector::iterator topic_itr;
		typedef TopicVector::const_iterator topic_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CTopicQueryAnalysis();

		/*!
		*
		**/
		~CTopicQueryAnalysis();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Load();

		/*!
		*
		**/
		void Commit();

		//
		//
		//
		/*!
		*
		**/
		long GetToicCount();

		/*!
		*
		**/
		const TopicQuerySQL &GetTopic(int index);

		/*!
		*
		**/
		void UpdateTopic(const TopicQuerySQL &topic, bool isDelete = false);

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoLoadTopic(CAnyAccessor &accessor);

		/*!
		*
		**/
		static bool CompareTopicIdx(const TopicQuerySQL &first, const TopicQuerySQL &second)
		{
			return first.m_topicIdx < second.m_topicIdx;
		}

	public:
		// topics
		TopicVector m_topics;
		// whether commit
		bool m_isDirty;

		// table name
		static string m_topicTableName;
	};
}
#endif
