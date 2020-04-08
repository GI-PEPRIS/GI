/*!
 * The AnyBridge of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * rendering pipeline and key display implementatios etc.
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
#ifndef __ANYBRIDGE_WELL_TABLE_H__
#define __ANYBRIDGE_WELL_TABLE_H__

// refer to EXPORT and IMPORT
#include "anybridge.h"

// refer to datamodel
#include "anybridgedatamodel.h"

#include "any/base/anystl.h"

//
#include "any/db/anyaccessor.h"
using namespace AnyDB;

//
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyWellTable
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyWellTable(const std::string &item_name);
		
		/*!
		*
		**/
		~CAnyWellTable();

	public:
		/*!
		*
		*/
		static bool CreateTable(const std::string &tablename, std::vector<DBFieldDesc> &fields);

		/*!
		*
		*/
		static bool CreateField(const DBFieldDesc &field);

		/*!
		*
		*/
		bool CreateWellTables();

		/*!
		*
		*/
		bool DropWellTables();

		/*!
		*
		*/
		bool DropWellTables(CAnyAccessor &accessor);

		/*!
		*
		*/
		void GetBoreRelatedWellTables(std::vector<std::string> &boreidtables);

		/*!
		*
		*/
		void DeleteWellLayerData(const std::vector<int> &wellids, const std::string &filepath);

		/*!
		*
		*/
		void DeleteWellData(const std::vector<int> &wellids, const std::vector<int> geometryids);

		/*!
		*
		*/
		void DeleteWellDataByClassId(CAnyAccessor &accessor, int classid);

	public:
	
		//
		//well tables of 'wellid'
		//
		bool CreateWellBasicTable();//d_well_basic
		bool CreateWellBasicMoreTable();//d_well_basic_more
		bool CreateWellVariableTable();//d_well_variable

		//
		//well tables of 'boreid'
		//		
		bool CreateWellTraceTable();//d_well_trace
		bool CreateWellTracePropertyTable();//d_well_logtrace_property
		bool CreateWellPickTable();//d_well_pick
		bool CreateWellZoneTable();//d_well_zone
		bool CreateWellBurialHistoryTable();//d_well_burial_history
		bool CreateWellCalibrationTable();//d_well_calibration		
		bool CreateWellFractureTable();//d_well_fracture
		bool CreateWellImageTable();//d_well_image
		bool CreateWellLoggingTable();//d_well_logging
		bool CreateWellProductionTable();//d_well_production
		bool CreateWellPropertyTable();//d_well_property
		bool CreateWellShaleOperationTable();//d_well_shale_operation
		bool CreateWellFaultTable();//d_well_fault
		bool CreateWellPathTable();//d_well_path
		bool CreateWellInterpretationTable();//d_well_interpretation
		bool CreateWellMiningTestTable();//d_well_mining_test
		bool CreateWellOilTestTable();//d_well_oil_test

		//2019/4/8: development well tables
		bool CreateWellDevYieldTable();//d_well_dev_yield
		bool CreateWellDevGeoParaTable();//d_well_dev_geo_para
		bool CreateWellDevPressureTable();//d_well_dev_pressure
		bool CreateWellDevProductionTable();//d_well_dev_production
		
		//2019/8/8: d_well_sand_body_connection
		bool CreateWellSandBodyConnectionTable();//
		//
		//static methods
		//
		//d_well_pick
		static void SaveWellpick(std::vector<AnyWellPick> &picks, int boreid, const std::string &item_name);
		static void SaveWellpick(CAnyAccessor &accessor, std::vector<AnyWellPick> &picks, int boreid, const std::string &item_name);
		static bool LoadWellpick(std::vector<AnyWellPick> &picks, int boreid, const std::string &item_name);
		static bool LoadWellpick(CAnyAccessor &accessor, std::vector<AnyWellPick> &picks, int boreid, const std::string &item_name);
		static bool DeleteWellpick(int boreid, const std::string &item_name);
		static bool DeleteWellpick(CAnyAccessor &accessor, int boreid, const std::string &item_name);
		static bool CompareWellPick(const AnyWellPick &p1, const AnyWellPick &p2); 		

		//d_well_path
		static void SaveWellPath(std::vector<AnyWellPath> &paths, int boreid, const std::string &item_name);
		static void SaveWellPath(CAnyAccessor &accessor, std::vector<AnyWellPath> &paths, int boreid, const std::string &item_name);
		static bool LoadWellPath(std::vector<AnyWellPath> &paths, int boreid, const std::string &item_name);
		static bool LoadWellPath(CAnyAccessor &accessor, std::vector<AnyWellPath> &paths, int boreid, const std::string &item_name);
		static bool DeleteWellPath(int boreid, const std::string &item_name);
		static bool DeleteWellPath(CAnyAccessor &accessor, int boreid, const std::string &item_name);
		static bool CompareWellPath(const AnyWellPath &p1, const AnyWellPath &p2); 

		//d_well_interpretation
		static void SaveWellInterpretation(std::vector<AnyWellInterpretation> &interpretations, int boreid, const std::string &item_name);
		static void SaveWellInterpretation(CAnyAccessor &accessor, std::vector<AnyWellInterpretation> &interpretations, int boreid, const std::string &item_name);
		static bool LoadWellInterpretation(std::vector<AnyWellInterpretation> &interpretations, int boreid, const std::string &item_name);
		static bool LoadWellInterpretation(CAnyAccessor &accessor, std::vector<AnyWellInterpretation> &interpretations, int boreid, const std::string &item_name);
		static bool DeleteWellInterpretation(int boreid, const std::string &item_name);
		static bool DeleteWellInterpretation(CAnyAccessor &accessor, int boreid, const std::string &item_name);
		static bool CompareWellInterpretation(const AnyWellInterpretation &p1, const AnyWellInterpretation &p2); 

		//d_well_logging
		static void SaveWellLogging(std::vector<AnyWellLogging> &loggings, int boreid, const std::string &item_name);
		static void SaveWellLogging(CAnyAccessor &accessor, std::vector<AnyWellLogging> &loggings, int boreid, const std::string &item_name);
		static bool LoadWellLogging(std::vector<AnyWellLogging> &loggings, int boreid, const std::string &item_name);
		static bool LoadWellLogging(CAnyAccessor &accessor, std::vector<AnyWellLogging> &loggings, int boreid, const std::string &item_name);
		static bool DeleteWellLogging(int boreid, const std::string &item_name);
		static bool DeleteWellLogging(CAnyAccessor &accessor, int boreid, const std::string &item_name);
		static bool CompareWellLogging(const AnyWellLogging &p1, const AnyWellLogging &p2); 
		static void CalculateWellLogging(std::vector<AnyWellLogging> &loggings);


	public:
		std::string m_item_name;
	};
}

#endif
