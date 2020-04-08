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
#ifndef __ANYBRIDGE_LAS_LOG_TOKENIZER_H__
#define __ANYBRIDGE_LAS_LOG_TOKENIZER_H__

// refer to EXPORT and IMPORT
#include "anybridge.h"

// refer to its parent
#include "anytokenizer.h"

//forward class
namespace AnyDB
{
	class CAnyAccessor;
}

//
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CLASLog : public CAnyTokenizer
	{
	public:
		/*!
		*
		**/
		struct VersionInfo
		{
			int m_ver;
			bool m_isWrapped;
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CLASLog(const string &fileName) : CAnyTokenizer(fileName), m_isdepth(false), m_curlineoffset(0), m_wellcount(0), m_well_type(""), m_item_name("")
		{}

		/*!
		*
		**/
		~CLASLog()
		{}

	public:
		/*!
		*
		**/
		int Extract(long elementid, long classid, int num = 0, int startline = 0, int endline = -1);

		/*!
		*
		**/
		int Extract_SingleTrace(long elementid, long classid, int num = 0, int startline = 0, int endline = -1);

		/*!
		*
		**/
		int Extract_MT(CAnyAccessor &accessor, CAnyAccessor &accessor_trace, long elementid, long classid, int num, int startline, int endline, AnyWellLogTrace &existtrace, int &existboreid, bool iscommit, int &nextkey, std::map<int, int> &wellid_boreid);

		/*!
		*
		**/
		int Extract_MT_SingleTrace(CAnyAccessor &accessor, CAnyAccessor &accessor_trace, long elementid, long classid, int num, int startline, int endline, int &nextkey, std::map<int, int> &wellid_boreid, std::map<int, std::vector<int> > &boreid_datatypes, std::map<int, std::vector<int> > &boreid_traceids);

		/*!
		*
		**/
		int DoExtract(long elementid, long classid, int num, int startline, int endline, AnyWellLogTrace &existtrace, int &existboreid, bool iscommit);

		/*!
		*
		**/
		bool IsCommentLine(const string &curLine);

		/*!
		*
		**/
		bool IsBlockLine(const string &curLine);

		/*!
		*
		**/
		bool IsEmptyLine(const string &curLine);

		/*!
		*
		**/
		unsigned char* DoEncoding(std::vector<AnyTraceDescription> &descriptions, std::vector<AnyTraceSample> &samples);

		/*!
		*
		**/
		bool DoDecoding(unsigned char* parameter, std::vector<AnyTraceDescription> &descriptions, std::vector<AnyTraceSample> &samples);
		
		/*!
		*
		**/
		bool SaveLogTrace(AnyWellLogTrace &logtrace, int boreid, const std::vector<int> &lengths = std::vector<int>());
		
		/*!
		*2018/11/19: SaveLogTrace with input para 'CAnyAccessor &accessor'
		**/
		bool SaveLogTrace(CAnyAccessor &accessor, AnyWellLogTrace &logtrace, int boreid, const std::vector<int> &lengths = std::vector<int>());

		/*!
		*
		**/
		bool SaveLogTrace_Addmode(CAnyAccessor &accessor, AnyWellLogTrace &logtrace, int boreid, const std::vector<int> &lengths);

		/*!
		*
		**/
		bool LoadLogTrace(AnyWellLogTrace &logtrace, int boreid);
				
		/*!
		*2018/7/11: LoadLogTrace with input para 'CAnyAccessor &accessor'
		**/
		bool LoadLogTrace(CAnyAccessor &accessor, AnyWellLogTrace &logtrace, int boreid);

		/*!
		*
		**/
		bool DeleteLogTrace(int boreid, int datatype, bool isAll = false, bool only_canvas_curve = false);
				
		/*!
		*2018/4/12: DeleteLogTrace with input para 'CAnyAccessor &accessor'
		**/
		bool DeleteLogTrace(CAnyAccessor &accessor, int boreid, int datatype, bool isAll = false, bool only_canvas_curve = false);

		/*!
		*
		**/
		int GetMaxDatatypeValuebyDatatype(int boreid, int datatype);
			
		/*!
		*
		**/
		long long GetTraceDataLens(unsigned char* &parameter);

		/*!
		*
		**/
		bool InitWellCount();
		
		/*!
		*
		**/
		void GetOneLogtraceData(AnyWellLogTrace &logtrace, int num = 0);
	public:
		//
		//
		//
		/*!
		*
		**/
		template<typename T>
		bool Bind(CAnyTokenString &curToken);

	public:
		// version info to decide how to "TOKENIZING" LAS 
		VersionInfo m_version;

		// trace description
		std::vector<AnyTraceDescription> m_tDescriptions;

		// trace sample values
		std::vector<AnyTraceSample> m_tSamples;

		//
		AnyWell m_well;

		//
		AnyWellLogTrace m_trace;

		// depth of current line
		double m_currentdepth;

		// whether current line is depth
		bool m_isdepth;
		int m_curlineoffset;

		// samples data style
		int m_samplestyle;

		// existed wells in current well layer
		std::vector<AnyWell> m_alreadyexistedwells;
	public:

		// d_well_trace
		static string m_traceTable;
		int m_wellcount;

		//2018/6/5: well type, lgcreport/las/custom...
		std::string m_well_type;

		//2018/12/6: record item name
		std::string m_item_name;
	};
}

#endif
