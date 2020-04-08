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
#ifndef __ANYPETRO_PROPERTY_REFERENCE_RECORD_H__
#define __ANYPETRO_PROPERTY_REFERENCE_RECORD_H__

// refer to export etc macro
#include "anypetro.h"

#include "any/base/anyport.h"
#include "any/base/loki/singleton.h"
using namespace AnyBase;
using namespace AnyBase::Loki;

// refer to DB
#include "any/db/anyaccessor.h"
using namespace AnyDB;

//
namespace AnyPetro
{
	/*!
	* references to geology info
	**/
	enum ReferenceRecordType
	{
		Ref_Unknown,
		Ref_Geology_Basin_Type,
		Ref_Geology_Play_Type,
		Ref_Geology_Trap_Type,
		Ref_Geology_Exploration_Degree,
		Ref_Geology_Formation_Type,
		Ref_Geology_Tectonic_Strength,
		Ref_Geology_Structural_Belt,
		Ref_Geology_Geographic_Environment,
		Ref_Geology_Thermal_History,
		Ref_Source_Rock_Type,
		Ref_Source_Face_Type,
		Ref_Source_Organic_Type,
		Ref_Source_Pathway_Type,
		Ref_Source_Supplyway_Type,
		Ref_Reservoir_Rock_Type,
		Ref_Reservoir_Space_Type,
		Ref_Reservoir_Pore_Type,
		Ref_Reservoir_Diagenetic_Phase,
		Ref_Cap_Rock_Type,
		Ref_Preservation_Fault_Strength,
		Ref_Preservation_Water_Type,
		Ref_Preservation_Migration_Relation,
		Ref_Preservation_Migration_Way,
		Ref_Preservation_Composition_Type,
		Ref_ResourceName_Type,

		Ref_Max
	};

	/*!
	* common property record as a singleton
	**/
	class ANYPETRO_CLASS CPropertyReferenceRecord
	{
		// sinleton
		typedef SingletonHolder<CPropertyReferenceRecord, CreateUsingNew> Singleton;

	public:
		/*!
		*
		**/
		struct ReferenceRecord
		{
			// persistance idx
			long m_idx;
			// name
			string m_name;
			// remark
			string m_remark;

			/*!
			*
			**/
			ReferenceRecord() : m_idx(0), m_name(""), m_remark("")
			{
			}

			/*!
			*
			**/
			const ReferenceRecord &operator=(const ReferenceRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_idx = other.m_idx;
				m_name = other.m_name;
				m_remark = other.m_remark;

				return *this;
			}
		};
		typedef std::vector<ReferenceRecord> RecordVector;
		typedef RecordVector::iterator rec_itr;
		typedef RecordVector::const_iterator rec_citr;

		typedef std::map<int, RecordVector > RecordMap;
		typedef RecordMap::iterator map_itr;
		typedef RecordMap::const_iterator map_citr;

		typedef std::map<int, string> TableNameMap;
		typedef TableNameMap::iterator name_itr;
		typedef TableNameMap::const_iterator name_citr;

	public:
		/*!
		*
		**/
		CPropertyReferenceRecord();

		/*!
		*
		**/
		~CPropertyReferenceRecord();

	private:
		CPropertyReferenceRecord(const CPropertyReferenceRecord &other);
		const CPropertyReferenceRecord &operator=(const CPropertyReferenceRecord &other);

	public:
		//
		// singleton
		//
		/*!
		*
		**/
		static CPropertyReferenceRecord &GetSingleton(short type);

		//
		//
		//
		/*!
		*
		**/
		int GetRecordCount(int type);

		/*!
		*
		**/
		const ReferenceRecord &GetRecordByOrder(int type, int order);

		/*!
		*
		**/
		const ReferenceRecord &GetRecordByIdx(int type, int idx);

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoInitTableNames();

		/*!
		*
		**/
		bool DoLoadRecords(int type);

		/*!
		*
		**/
		void DoLoadRecordVector(CAnyAccessor &accessor, RecordVector &records);

		//
		//
		//
		/*!
		*
		**/
		static bool CompareRecordByIdx(const ReferenceRecord &first, const ReferenceRecord &second);

	private:
		// records
		RecordMap m_records;

		// table names
		static TableNameMap m_tableNames;
	};
};

#endif