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
#ifndef __ANYPETRO_RISK_QUICK_SCORE_H__
#define __ANYPETRO_RISK_QUICK_SCORE_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

// refer to its parent
#include "accumulationassessor.h"

// refer to stl
#include "any/base/anystl.h"

// Refer to "test object"
#include "any/base/loki/singleton.h"
using namespace AnyBase::Loki;

// refer to AnyDB relatives
#include "any/db/anyaccessor.h"
using namespace AnyDB;

// refer to functor
#include "any/base/anymediator.h"
using namespace AnyBase;

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CRiskQuickScore : public CAccumulationAssessor
	{
		// sinleton
		typedef SingletonHolder<CRiskQuickScore, CreateUsingNew> Singleton;
		friend class CRiskFuzzyScore;

	public:
		/*!
		*
		**/
		enum TPTYPE
		{
			ID_TPTYPE_GEO,
			ID_TPTYPE_PRJ,
			ID_TPTYPE_ECO,
			ID_TPTYPE_ENV,

		};


		struct QuickOperationFlag
		{
			// operation flag: 0 - nothing, 1 - add, 2 - update, 4 - delete
			unsigned char m_operation;

			/*!
			*
			**/
			QuickOperationFlag() : m_operation(0)
			{
			}
		};

		/*!
		*
		**/
		struct QuickScoreTemplate : public QuickOperationFlag
		{
			long m_templateIdx;
			string m_name;
			string m_who;
			double m_when;
			string m_remark;
			//type
			long m_type;
			string m_formula;
			long long m_ts;
			int m_define;//模板类别 地质 经济 工程 环保
			/*!
			*
			**/
			QuickScoreTemplate() : m_templateIdx(0), m_name(""), m_who(""), m_when(0), m_remark(""),m_type(0),m_formula(""),m_ts(-2L),m_define(-1)
			{
			}

			/*!
			*
			**/
			QuickScoreTemplate(long id,string name,string who,double when,string remark,long type,string formula="",int define=-1,long long ts=0L ) : m_templateIdx(id), m_name(name), m_who(who), m_when(when), m_remark(remark),m_type(type),m_formula(formula),m_ts(ts),m_define(define)
			{
			}

			/*!
			*
			**/
			const QuickScoreTemplate &operator=(const QuickScoreTemplate &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_templateIdx = other.m_templateIdx;
				m_name = other.m_name;
				m_who = other.m_who;
				m_when = other.m_when;
				m_remark = other.m_remark;
				m_type=other.m_type;
				m_formula=other.m_formula;
				m_ts=other.m_ts;
				m_define = other.m_define;
				return *this;
			}
		};
		typedef std::vector<QuickScoreTemplate> QuickTemplateVector;
		typedef QuickTemplateVector::iterator template_itr;
		typedef QuickTemplateVector::const_iterator template_citr;

		/*!
		* scoring template or solutions
		**/
		struct QuickScoreStandard : public QuickOperationFlag
		{
			// score idx
			long m_idx;
			// template idx
			long m_templateidx;
			// score type
			long m_scoreType;
			// lower score
			double m_lower;
			// upper score
			double m_upper;
			// remark
			string m_remark;
			
			
			/*!
			*
			**/
			QuickScoreStandard() : m_idx(0), m_templateidx(0), m_scoreType(0), m_lower(0.), m_upper(0.), m_remark("")
			{
			}

			/*!
			*
			**/
			QuickScoreStandard(long id,long tid,long st,double lower,double upper,string remark) : m_idx(id), m_templateidx(tid), m_scoreType(st), m_lower(lower), m_upper(upper), m_remark(remark)
			{
			}

			/*!
			*
			**/
			const QuickScoreStandard &operator=(const QuickScoreStandard &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_idx = other.m_idx;
				m_templateidx = other.m_templateidx;
				m_scoreType = other.m_scoreType;
				m_lower = other.m_lower;
				m_upper = other.m_upper;
				m_remark = other.m_remark;
				m_operation = other.m_operation;
				

				return *this;
			}
		};
		typedef std::vector<QuickScoreStandard> QuickStandardVector;
		typedef QuickStandardVector::iterator stand_itr;
		typedef QuickStandardVector::const_iterator stand_citr;

		/*!
		* risk factor as template factor
		**/
		struct ScoreFactor : public QuickOperationFlag
		{
			// table fields
			// ...
			// factor idx
			long m_idx;
			// parent idx
			long m_parentIdx;
			// template idx
			long m_templateIdx;
			// score type
			long m_scoreType;
			// factor's name
			string m_name;
			// upper value
			double m_upper;
			// lower value
			double m_lower;
			// full string content
			string m_sValue;
			// default weight
			double m_weight;
			// whether is a marginal factor
			bool m_isCommon;
			//
			string m_formula;
			/*!
			*
			**/
			ScoreFactor() : m_idx(0), m_parentIdx(0), m_templateIdx(0), m_scoreType(0), m_name(""), m_upper(0.), m_lower(0.), m_sValue(""), m_weight(0.), m_isCommon(0),m_formula("")
			{
			}

			/*!
			*
			**/
			ScoreFactor(long id,long pid,long tid,long st,string name,double upper,double lower,string sv,double weight,bool com,string formula="") : m_idx(id), m_parentIdx(pid), m_templateIdx(tid), m_scoreType(st), m_name(name), m_upper(upper), m_lower(lower), m_sValue(sv), m_weight(weight), m_isCommon(com),m_formula(formula)
			{
			}

			/*!
			*
			**/
			const ScoreFactor &operator=(const ScoreFactor &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_idx = other.m_idx;
				m_parentIdx = other.m_parentIdx;
				m_templateIdx = other.m_templateIdx;
				m_scoreType = other.m_scoreType;
				m_name = other.m_name;
				m_upper = other.m_upper;
				m_lower = other.m_lower;
				m_sValue = other.m_sValue;
				m_operation = other.m_operation;
				m_weight = other.m_weight;
				m_isCommon = other.m_isCommon;
				m_formula=other.m_formula;
				return *this;
			}
		};
		typedef std::vector<ScoreFactor> FactorVector;
		typedef FactorVector::iterator factor_itr;
		typedef FactorVector::const_iterator factor_citr;

		/*!
		*
		**/
		struct QuickScoreRule : public QuickOperationFlag
		{
			// Foreign key
			long m_scoreIdx;
			// Foreign key from "scorefactor"
			long m_factorIdx;
			// upper limit for current grade
			double m_upper;
			// lower limit for current grade
			double m_lower;
			// string content for current grade
			string m_sValue;
			// qualitative description
			string m_favorability;
			//reamrk
			string m_remark;

			/*!
			*
			**/
			QuickScoreRule() 
				: m_scoreIdx(0), m_factorIdx(0), m_upper(0.), m_lower(0.), m_sValue(""), m_favorability(""),m_remark("")
			{
			}

			/*!
			*
			**/
			QuickScoreRule(long id,long fid,double upper,double lower,string sv,string favor,string remark) 
				: m_scoreIdx(id), m_factorIdx(fid), m_upper(upper), m_lower(lower), m_sValue(sv), m_favorability(favor),m_remark(remark)
			{
			}

			/*!
			*
			**/
			const QuickScoreRule &operator=(const QuickScoreRule &other)
			{
				if(this == &other)
				{
					return *this;
				}

				// Foreign key
				m_scoreIdx = other.m_scoreIdx;
				// Foreign key from "scorefactor"
				m_factorIdx = other.m_factorIdx;
				// upper limit for current grade
				m_upper = other.m_upper;
				// lower limit for current grade
				m_lower = other.m_lower;
				// string content for current grade
				m_sValue = other.m_sValue;
				// geological favorability
				m_favorability = other.m_favorability;
				// operation status
				m_operation = other.m_operation;
				m_remark=other.m_remark;

				return *this;
			}
		};
		typedef std::vector<QuickScoreRule> QuickRuleVector;
		typedef QuickRuleVector::iterator rule_itr;
		typedef QuickRuleVector::const_iterator rule_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CRiskQuickScore(int type = ST_Risk_Maturity);

		/*!
		*
		**/
		CRiskQuickScore(CAccumulationElement *curElement, int type = ST_Risk_Maturity);

		/*!
		*
		**/
		~CRiskQuickScore();

	private:
		CRiskQuickScore(const CRiskQuickScore &other);
		const CRiskQuickScore &operator=(const CRiskQuickScore &other);

	public:
		//
		// tables for construction of scoring system
		//
		/*!
		*
		**/
		void Load();

		/*!
		*
		**/
		unsigned int Commit(bool isActivity = false);

		/*!
		*
		**/
		void Rollback();

		//
		// Edit current scoring system
		//
		/*!
		*
		**/
		int GetQuickRuleCount();

		/*!
		*
		**/
		QuickScoreRule &GetQuickRule(int index);

		/*!
		*
		**/
		void FindQuickRules(long factorIdx, QuickRuleVector &rules);

		/*!
		*
		**/
		void UpdateQuickRule(const QuickScoreRule &rule, bool isDelete = false);

		//
		//
		//
		/*!
		*
		**/
		int GetFactorCount();

		/*!
		*
		**/
		const ScoreFactor &GetFactor(int index);

		/*!
		*
		**/
		const ScoreFactor &FindFactor(long idx);

		/*!
		*
		**/
		bool UpdateFactor(const ScoreFactor &factor, bool isDelete = false);

		//
		//
		//
		/*!
		*
		**/
		int GetQuickStandardCount();

		/*!
		*
		**/
		QuickScoreStandard &GetQuickStandard(int index);

		/*!
		*
		**/
		QuickScoreStandard &FindQuickStandard(long idx);

		/*!
		*
		**/
		bool UpdateQuickStandard(const QuickScoreStandard &standard, bool isDelete = false);

		//
		//
		//
		/*!
		*
		**/
		bool SetScoringTemplate(long templateIdx,long seimicIdx=0);

		/*!
		*
		**/
		long GetScoringTemplate();

		/*!
		*
		**/
		int GetQuickTemplateCount();


		/*!
		*
		**/
		QuickScoreTemplate &FindQuickTemplate(long idx);

		/*!
		*
		**/
		QuickScoreTemplate &GetQuickTemplate(int index);

		/*!
		*
		**/
		bool UpdateQuickTemplate(const QuickScoreTemplate &scoreTemplate, bool isDelete = false);

		/*!
		*
		**/
		static void InitScoreTemplate();

		//
		//
		//
		/*!
		*
		**/
		double GetMaturityRisk(long factorIdx, double value);

		/*!
		*
		**/
		double GetDelphiScore(CAnyAccessor &accessor, long templateIdx, long elementIdx, long factorIdx);

		/*!
		*
		**/
		void GetScoreHistory(CAnyAccessor &accessor, long templateIdx, long elementIdx, long factorIdx, std::vector<double>&score, std::vector<string>&username);

		/*!
		*
		**/
		void CommitFactorActivity(CAnyAccessor &accessor, long templateIdx, long elementIdx, long factorIdx, string username, double value, string remark = "");

		/*!
		*
		**/
		void DeletePreviousScore(CAnyAccessor &accessor, long templateIdx, long elementIdx, string username);

		/*!
		*
		**/
		double GetMaturityRisk(long factorIdx, string &Value);

		/*!
		*
		**/
		bool IsCommon(long factorIdx);

		//
		//
		//
		/*!
		*
		**/
		static CRiskQuickScore &GetSingleton(short type);

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoLoadTemplate(CAnyAccessor &accessor, QuickScoreTemplate &scoreTemplate);

		/*!
		*
		**/
		void DoLoadScore(CAnyAccessor &accessor, QuickScoreStandard &scoreStandard);

		/*!
		*
		**/
		void DoLoadFactor(CAnyAccessor &accessor, ScoreFactor &factor);

		/*!
		*
		**/
		void DoLoadRules(CAnyAccessor &accessor);

		/*!
		*
		**/
		double DoGetStringValueScore(const string &curValue, const string &ruleValue);

		/*!
		*
		**/
		unsigned int DoCommitActivity();

		/*!
		*
		**/
		int DoCommitFactor();

		/*!
		*
		**/
		int DoCommitRule();

		/*!
		*
		**/
		int DoCommitStandard();

		/*!
		*
		**/
		int DoCommitTemplate();

		/*!
		*
		**/
		bool IsBeingUsed(const ScoreFactor &factor);

		/*!
		*
		**/
		bool IsBeingUsed(const QuickScoreTemplate &scoreTemplate);

		/*!
		*
		**/
		bool IsBeingUsed(const QuickScoreStandard &standard);
	public:
		
		/*!
		*
		**/
		static bool CompareStandardIdx(const QuickScoreStandard &first, const QuickScoreStandard &second)
		{
			return first.m_idx < second.m_idx;
		}

		/*!
		*
		**/
		static bool CompareTemplateIdx(const QuickScoreTemplate &first, const QuickScoreTemplate &second)
		{
			return first.m_templateIdx < second.m_templateIdx;
		}

		/*!
		*
		**/
		static bool CompareRuleFactor(const QuickScoreRule &first, const QuickScoreRule &second)
		{
			return first.m_factorIdx < second.m_factorIdx;
		}

		/*!
		*
		**/
		static bool CompareFactorIdx(const ScoreFactor &first, const ScoreFactor &second)
		{
			return first.m_idx < second.m_idx;
		}

	private:
		// scoring template or schema
		QuickTemplateVector m_quickTemplates;
		// not directly use "delete" flag
		QuickTemplateVector m_deletedTemplates;
		// which template is playing
		

		// which template is playing
		long m_curSeismicTemplateIdx;

	
		// scoring standards against different scoring template
		QuickStandardVector m_quickStandards;
		// not directly use "delete" flag since scoreid maybe foreigned by rule table
		QuickStandardVector m_deletedStandards;

		// risk factors against different scoring template
		FactorVector m_factors;
		// not directly use "delete" flag
		FactorVector m_deletedFactors;
		// scoring rule against different factors
		QuickRuleVector m_quickRules;
		// not directly use "delete" flag
		QuickRuleVector m_deletedRules;

		// commit status
		bool m_isQuickRuleDirty;
		bool m_isFactorDirty;
		bool m_isQuickStandardDirty;
		bool m_isQuickTemplateDirty;
		
	public:
		// persistence tables
		static string m_quickScoreTable;
		static string m_riskFactorTable;
		static string m_quickRuleTable;
		static string m_quickTemplateTable;

		int m_type;//ST_Risk_Maturity or ST_Risk_Condition
		int m_probabilitytreeid;//default:-1
		//
		bool m_isSeismic;
		std::set<std::string> m_defaultTemplateSet;

		long m_curTemplateIdx;
	};
}

#endif