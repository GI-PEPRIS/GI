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
#ifndef __ANYBRIDGE_LGC_REPORT_TOKENIZER_H__
#define __ANYBRIDGE_LGC_REPORT_TOKENIZER_H__

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
	class ANYBRIDGE_CLASS CLGCReport : public CAnyTokenizer
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CLGCReport(const string &fileName) : CAnyTokenizer(fileName), m_wellcount(0), m_islogcurveserial(false), m_well_type(""), m_item_name("")
		{
		}

		/*!
		*
		**/
		~CLGCReport()
		{
		}

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
		int DoExtract(long elementid, long classid, int num, int startline, int endline, bool singletracemode);

		/*!
		*
		**/
		int Extract_MT(CAnyAccessor &accessor, CAnyAccessor &accessor_trace, long elementid, long classid, int num, int startline, int endline, int &nextkey, bool singletracemode);

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
		bool SaveLogTrace(AnyWellLogTrace &logtrace, int boreid);
		
		/*!
		*
		**/
		bool SaveLogTrace(CAnyAccessor &accessor, AnyWellLogTrace &logtrace, int boreid);

		/*!
		*
		**/
		bool SaveLogTrace_Addmode(CAnyAccessor &accessor, AnyWellLogTrace &logtrace, int boreid);

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
		bool DeleteLogTrace(int boreid, int datatype);

		/*!
		*
		**/
		static void SaveWellpick(std::vector<AnyWellPick> &picks, int boreid);

		/*!
		*
		**/
		static bool LoadWellpick(std::vector<AnyWellPick> &picks, int boreid);

		/*!
		*
		**/
		static bool DeleteWellpick(int boreid);
		
		/*!
		*2018/4/12: DeleteWellpick with input para 'CAnyAccessor &accessor'
		**/
		static bool DeleteWellpick(CAnyAccessor &accessor, int boreid);

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
		static void WellAdjust(std::vector<double> &md, std::vector<double> &alpha, std::vector<double> &beta, std::vector<double> &tvd, std::vector<double> &xshift, std::vector<double> &yshift);
		static void WellAdjust_dipazimuthToxyshift(std::vector<double> &mds, std::vector<double> &dipangles, std::vector<double> &azimuths, \
			std::vector<double> &xshifts, std::vector<double> &yshifts, std::vector<double> &tvds);
		static void WellAdjust_xyshiftTodipazimuth(std::vector<double> &mds, std::vector<double> &dipangles, std::vector<double> &azimuths, \
			std::vector<double> &xshifts, std::vector<double> &yshifts, std::vector<double> &tvds);
		static void WellAdjust_Earthmodel(std::vector<double> &mds, std::vector<double> &dipangles, std::vector<double> &azimuths, \
			std::vector<double> &xshifts, std::vector<double> &yshifts, std::vector<double> &tvds, \
			double md_top, double md_bot, double layerdipangle_top, double layerdipangle_bot, double layerazimuth_top, double layerazimuth_bot, \
			double &dipangle_top, double &dipangle_bot, double &azimuth_top, double &azimuth_bot, double &tvd_top, double &tvd_bot, \
			double &xshift_top, double &xshift_bot, double &yshift_top, double &yshift_bot, double &totalshift_top, double &totalshift_bot, \
			double &GT, double &TVT, double &TST);

		//
		//2018/6/6: well path related
		//
		/*!
		*
		**/
		static void SaveWellPath(std::vector<AnyWellPath> &paths, int boreid);

		/*!
		*
		**/
		static void SaveWellPath(CAnyAccessor &accessor, std::vector<AnyWellPath> &paths, int boreid);

		/*!
		*
		**/
		static bool LoadWellPath(std::vector<AnyWellPath> &paths, int boreid);

		/*!
		*
		**/
		static bool LoadWellPath(CAnyAccessor &accessor, std::vector<AnyWellPath> &paths, int boreid);

		/*!
		*
		**/
		static bool DeleteWellPath(int boreid);

		/*!
		*
		**/
		static bool DeleteWellPath(CAnyAccessor &accessor, int boreid);

		/*!
		*
		**/
		static bool CompareWellPath(const AnyWellPath &p1, const AnyWellPath &p2); 

		//
		//2018/7/5: well pick new methods
		//
		/*!
		*
		**/
		static bool CompareWellPick(const AnyWellPick &p1, const AnyWellPick &p2); 

		/*!
		*
		**/
		static void SaveWellpick(CAnyAccessor &accessor, std::vector<AnyWellPick> &picks, int boreid);

		/*!
		*
		**/
		static bool LoadWellpick(CAnyAccessor &accessor, std::vector<AnyWellPick> &picks, int boreid);

		//
		//2018/7/18: well interpretation related
		//
		/*!
		*
		**/
		static void SaveWellInterpretation(std::vector<AnyWellInterpretation> &interpretations, int boreid);

		/*!
		*
		**/
		static void SaveWellInterpretation(CAnyAccessor &accessor, std::vector<AnyWellInterpretation> &interpretations, int boreid);

		/*!
		*
		**/
		static bool LoadWellInterpretation(std::vector<AnyWellInterpretation> &interpretations, int boreid);

		/*!
		*
		**/
		static bool LoadWellInterpretation(CAnyAccessor &accessor, std::vector<AnyWellInterpretation> &interpretations, int boreid);

		/*!
		*
		**/
		static bool DeleteWellInterpretation(int boreid);

		/*!
		*
		**/
		static bool DeleteWellInterpretation(CAnyAccessor &accessor, int boreid);

		/*!
		*
		**/
		static bool CompareWellInterpretation(const AnyWellInterpretation &p1, const AnyWellInterpretation &p2); 

		//
		//2018/10/15: well logging related
		//
		/*!
		*
		**/
		static void SaveWellLogging(std::vector<AnyWellLogging> &loggings, int boreid);

		/*!
		*
		**/
		static void SaveWellLogging(CAnyAccessor &accessor, std::vector<AnyWellLogging> &loggings, int boreid);

		/*!
		*
		**/
		static bool LoadWellLogging(std::vector<AnyWellLogging> &loggings, int boreid);

		/*!
		*
		**/
		static bool LoadWellLogging(CAnyAccessor &accessor, std::vector<AnyWellLogging> &loggings, int boreid);

		/*!
		*
		**/
		static bool DeleteWellLogging(int boreid);

		/*!
		*
		**/
		static bool DeleteWellLogging(CAnyAccessor &accessor, int boreid);

		/*!
		*
		**/
		static bool CompareWellLogging(const AnyWellLogging &p1, const AnyWellLogging &p2); 

		/*!
		*
		**/
		static void CalculateWellLogging(std::vector<AnyWellLogging> &loggings);

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

		// trace description
		std::vector<AnyTraceDescription> m_tDescriptions;

		// trace sample values
		std::vector<AnyTraceSample> m_tSamples;

		//
		AnyWellPick m_wellpicktmp;

		//
		AnyWell m_well;

		//
		std::vector<AnyWellPick> m_wellpicks;

		//
		AnyWellLogTrace m_trace;
	public:

		// d_well_trace
		static string m_traceTable;
		int m_wellcount;
		bool m_islogcurveserial;

		std::vector<double> m_md;
		std::vector<double> m_alpha;
		std::vector<double> m_beta;

		//2018/6/5: well type, lgcreport/las/custom...
		std::string m_well_type;

		//2018/12/6: record item name
		std::string m_item_name;
	};
}

#endif
