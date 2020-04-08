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
#ifndef __ANYPETRO_ACCUMULATION_PROPERTY_SET_H__
#define __ANYPETRO_ACCUMULATION_PROPERTY_SET_H__

// refer to export etc macro
#include "anypetro.h"

// Refer to its parent
#include "anypetroinfo.h"

// refer to kinds of property records
#include "accumulationpropertyrecord.h"

// refer to anydb
#include "any/db/anyaccessor.h"
using namespace AnyDB;

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CAccumulationPropertySet : public CAnyPetroInfo
	{
		// property vector
		typedef std::vector<PropertyRecord *> RecordVector;
		typedef RecordVector::iterator rec_itr;
		typedef RecordVector::const_iterator rec_citr;

		// table map
		typedef std::map<int, string> NameMap;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAccumulationPropertySet(short type);

		/*!
		*
		**/
		~CAccumulationPropertySet();

	public:
		//
		//	kida semantics
		//
		/*!
		*
		**/
		unsigned int CommitActivity(unsigned short type);
		
		/*!
		*
		**/
		void SetElementIdx(long idx);

		/*!
		*
		**/
		long GetElementIdx() const;

		//
		// persistance interface
		//
		/*!
		* Note:
		* this funcation had betteer be subject to parent's commit
		**/
		unsigned int Commit(bool isDeleted = false);

		/*!
		* clear memory status
		**/
		void Rollback();

		//
		//
		//
		/*!
		*
		**/
		void Load(long elementIdx,int type=0);

		/*!
		*
		**/
		const string &GetTableName() const;

		/*!
		*
		**/
		static const string &GetTableName(int type);

		/*!
		*
		**/
		static PropertyRecord *MakePropertyRecord(int type);

		/*!
		*
		**/
		int GetRecordCount();

		/*!
		*
		**/
		PropertyRecord *GetRecord(int order);

		/*!
		*
		**/
		PropertyRecord *FindRecord(long idx);

		/*!
		*
		**/
		void AddRecord(const PropertyRecord *record);

		/*!
		*
		**/
		void UpdateRecord(const PropertyRecord *record);

		/*!
		*
		**/
		void DeleteRecord(const PropertyRecord *record);

		/*!
		清空所有record记录
		**/
		void RemoveAllRecord();

		/*!
		通过elementid 在 info_element_Trap 找对应的propertyidx
		**/
		//int FindRecordidxbyElementidxInTrapinfo(long elementidx);

		/*!
		通过elementid 在 info_element_Trap 找对应的projectid
		**/
		//int FindProjectbyElementidxInTrapinfo(long elementidx);

		static void UpdateRecordByTypeandRecodr(int type,PropertyRecord *record);
	private:
		//
		//
		//
		/*!
		*
		**/
		PropertyRecord *GeTableRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetExplorationRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetPoolRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetVolumeRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetVolumeParaRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetOverallRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetSegmentRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetGeologyRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetSourceRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetReservoirRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetCapRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetPreservationRecord(CAnyAccessor &accessor);
		
		/*!
		*
		**/
		PropertyRecord *DoGetTrapRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetTrapExplorationRecord(CAnyAccessor &accessor);
		
		/*!
		*
		**/
		PropertyRecord *DoGetTrapProjectRecord(CAnyAccessor &accessor);
	
		/*!
		*
		**/
		PropertyRecord *DoGetTrapRepositoryRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		PropertyRecord *DoGetTrapDevelopRecord(CAnyAccessor &accessor);
		
		/*!
		*
		**/
		PropertyRecord *DoGetSurveyRecord(CAnyAccessor &accessor);
		
		/*!
		*
		**/
		PropertyRecord *DoGetSurveyCheckRecord(CAnyAccessor &accessor);
		
		/*!
		*
		**/
		PropertyRecord *DoGetSeismicDeployRecord(CAnyAccessor &accessor);



		PropertyRecord *DoGetSeismicPicRecord(CAnyAccessor &accessor);


		PropertyRecord *DoGetShaleWellBasicRecord(CAnyAccessor &accessor);

		PropertyRecord *DoGetShaleWellProductionRecord(CAnyAccessor &accessor);

		PropertyRecord *DoGetShaleBoreRecord(CAnyAccessor &accessor);

		PropertyRecord *DoGetShaleVolRecord(CAnyAccessor &accessor);

		PropertyRecord *DoGetShaleWellVariableRecord(CAnyAccessor &accessor);

		PropertyRecord *DoGetShalePlayOverallRecord(CAnyAccessor &accessor);
	
		PropertyRecord *DoGetShaleTargetOverallRecord(CAnyAccessor &accessor);

		PropertyRecord *DoGetShaleWellOverallRecord(CAnyAccessor &accessor);

		PropertyRecord *DoGetBlockBasinbasicRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetBlockPrimarystructBasicRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetBlockSecondStructBasicRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetBlockThirdStructBasicRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetBlockBlockBasicRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetBlockBlockExpDegreeRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetMlrResourceResultsRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetMlrCalibratedRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetElementResourceRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetElementResourceShaleRecord(CAnyAccessor &accessor);


		PropertyRecord *DoGetPerformanceWellBasicRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetPerformanceDeploymentRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetPerformanceDeploymentCasingRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetPerformanceDeploymenTubingRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetPerformanceDeploymenttrajectoryRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetPerformanceDeploymentGeologicalParaRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetPerformancePressureRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetPerformancePressureGradientRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetPerformanceProductionRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetPerformancePracticeRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetPerformanceDreMiddleRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetPerformanceDreResultRecord(CAnyAccessor &accessor);
		
	
		/*!
		*2016/7/21: new trap tables
		**/
		PropertyRecord *DoGetTrapGeologyFaultRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetTrapSurveyRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetTrapWildcatWellRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetTrapPostRecord(CAnyAccessor &accessor);
		PropertyRecord *DoGetTrapDrillRecord(CAnyAccessor &accessor);

		PropertyRecord *DoGetOverSeaProjectRecord(CAnyAccessor &accessor);
		//
		//
		//
		/*!
		*
		**/
		void GetUpdateSentence(const PropertyRecord *curRecord, char *sentence, char *sql);

		/*!
		*
		**/
		void GetInsertSentence(const PropertyRecord *curRecord, char *sentence, char *sql);

		/*!
		*
		**/
		static bool ComparePropertyIdx(const PropertyRecord *first, const PropertyRecord *second);

		/*!
		*
		**/
		static bool ComparePropertyElementidx(const PropertyRecord *first, const PropertyRecord *second);

		
	private:
		// Initialization of 
		RecordVector m_records;

		// parent id
		long m_elementIdx;

	public:
		// table name
		static NameMap m_tables;
	};
}

#endif