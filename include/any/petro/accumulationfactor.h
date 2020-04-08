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
#ifndef __ANYPETRO_ACCUMULATION_FACTOR_H__
#define __ANYPETRO_ACCUMULATION_FACTOR_H__

// refer to export etc macro
#include "anypetro.h"

// Refer to its parent
#include "anypetroinfo.h"

// refer to anydb
#include "any/db/anyaccessor.h"
using namespace AnyDB;

// refer to boost share_ptr
#include "boost/smart_ptr.hpp"
using namespace boost;

//
namespace AnyPetro
{
	// Forward class
	class CRiskQuickScore;

	//
	/*!
	*
	**/
	class ANYPETRO_CLASS CAccumulationFactor : public CAnyPetroInfo
	{
	public:
		/*!
		*
		**/
		enum FactorType
		{
			FVT_Unknown,
			FVT_String,
			FVT_Float,
			FVT_Max
		};

		/*!
		* The entity of CAccumulationFactor
		**/
		struct FactorRecord
		{
			// foreign key
			long m_factorid;
			// username
			string m_whodo;
			// host object
			long m_elementid;
			// hierarchical level
			long m_parentid;
			// factor name
			string m_name;
			// default from factor template
			float m_weight;
			// quantitative specification
			float m_fValue;
			// qualification description
			string m_sValue;
			// certainty score
			float m_quickScore;
			// uncertainty score
			float m_fuzzyScore;
			// from fuzzy member function
			float m_fuzzyUpper;
			// from fuzzy memeber function
			float m_fuzzyLower;
			// positive or negative for accumulation system
			short m_role; // > 0 positive 0 unsure < 0 negative
			// whether is common factor
			bool m_isCommon;
			// whether is conditional factor
			bool m_isCondition;
			// remark while scoring
			string m_remark;

			// non-table fields
			// ...
			// hierarchical layer
			short m_level;
			// whehter to be rendered in parallel coordinate
			bool m_isShown;

			/*!
			*
			**/
			FactorRecord() : m_factorid(0), m_whodo(""), m_elementid(0), m_parentid(0), m_name("")
				, m_weight(0.), m_fValue(0.), m_sValue(""), m_quickScore(0.), m_fuzzyScore(0.), \
				m_fuzzyLower(0.), m_fuzzyUpper(0.), m_role(0), m_remark(""), m_level(-1), m_isShown(true), \
				m_isCommon(0), m_isCondition(0)
			{
			}

			/*!
			*
			**/
			FactorRecord(const FactorRecord &other)
			{
				m_factorid = other.m_factorid;
				m_whodo = other.m_whodo;
				m_elementid = other.m_elementid;
				m_parentid = other.m_parentid;
				m_name = other.m_name;
				m_weight = other.m_weight;
				m_fValue = other.m_fValue;
				m_sValue = other.m_sValue;
				m_quickScore = other.m_quickScore;
				m_fuzzyScore = other.m_fuzzyScore;
				m_fuzzyUpper = other.m_fuzzyUpper;
				m_fuzzyLower = other.m_fuzzyLower;
				m_role = other.m_role;
				m_isCommon = other.m_isCommon;
				m_isCondition = other.m_isCondition;
				m_remark = other.m_remark;

				m_level = other.m_level;
				m_isShown = other.m_isShown;
			}

			/*!
			*
			**/
			const FactorRecord &operator=(const FactorRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_factorid = other.m_factorid;
				m_whodo = other.m_whodo;
				m_elementid = other.m_elementid;
				m_parentid = other.m_parentid;
				m_name = other.m_name;
				m_weight = other.m_weight;
				m_fValue = other.m_fValue;
				m_sValue = other.m_sValue;
				m_quickScore = other.m_quickScore;
				m_fuzzyScore = other.m_fuzzyScore;
				m_fuzzyUpper = other.m_fuzzyUpper;
				m_fuzzyLower = other.m_fuzzyLower;
				m_role = other.m_role;
				m_isCommon = other.m_isCommon;
				m_isCondition = other.m_isCondition;
				m_remark = other.m_remark;

				m_level = other.m_level;
				m_isShown = other.m_isShown;

				return *this;
			}
		};
		typedef std::vector<FactorRecord> FactorVector;
		typedef FactorVector::iterator factor_itr;
		typedef FactorVector::const_iterator factor_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAccumulationFactor();

		/*!
		*
		**/
		CAccumulationFactor(CAccumulationFactor *parent, const FactorRecord &record);

		/*!
		*
		**/
		~CAccumulationFactor();

	public:
		//
		//	kida semantics
		//
		/*!
		*
		**/
		unsigned int CommitActivity(unsigned short type)
		{
			// TODO:
			// ...
			return 0;
		}

		//
		//
		/*!
		*
		**/
		const string &GetName() const
		{
			return m_name;
		}

		/*!
		*
		**/
		virtual void SetName(const string &name)
		{
			m_name = m_record.m_name = name;
		}

		//
		// inheritance interface
		//
		/*!
		*
		**/
		virtual unsigned int Commit(bool isDeleted = false);

		//
		//
		//
		/*!
		*
		**/
		void SetRecord(const FactorRecord &record);

		/*!
		* have a chance to directly modify
		**/
		const FactorRecord &GetRecord() const;

		/*!
		*
		**/
		void SetElementIdx(long idx);

		//
		//
		//
		/*!
		*
		**/
		bool IsNegative();

		/*!
		*
		**/
		float GetMaturityRisk();

		//
		//
		//
		/*!
		*
		**/
		static CAccumulationFactor *Load(long elementidx = 0);

		/*!
		*
		**/
		static CAccumulationFactor *LoadNODB(long elementidx,std::map<int,FactorVector>& factorMap);

		/*!
		*
		**/
		static char* LoadRemarkImage(int elementid, int factorid, long &length);

		/*!
		*
		**/
		static void SaveBitmap(int elementid, int factorid, char* imagedata, int length = 0);

		/*!
		*
		**/
		bool IsCommon();
	public:
		//
		//
		//
		/*!
		*
		**/
		void DoCommitComponents(bool isDelete);

		/*!
		*
		**/
		static void DoCreateFactor(CAccumulationFactor *curFactor, FactorVector &factors, int level);

		/*!
		*
		**/
		static void GetCurRecord(CAnyAccessor &accessor, FactorRecord &record);

		/*!
		*
		**/
		static bool CompareParentFactorIdx(const FactorRecord &first, const FactorRecord &second);


	private:
		// Initialization of 
		FactorRecord m_record;
		

		// scoring strategy
		CRiskQuickScore &m_strategy;

	public:
		// table name
		static string m_factorTable;
	};
}

#endif
