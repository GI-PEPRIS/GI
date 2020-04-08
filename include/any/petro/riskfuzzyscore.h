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
#ifndef __ANYPETRO_RISK_FUZZY_SCORE_H__
#define __ANYPETRO_RISK_FUZZY_SCORE_H__

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

#include "any/math/anydistributionstrategy.h"
#include "any/math/anyrandomgenerator.h"
using namespace AnyMath;
//
#include "any/base/agm/reflection.hpp"
using namespace agm::reflection;

#include "riskquickscore.h"
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CRiskFuzzyScore : public CAccumulationAssessor
	{
		// sinleton
		typedef SingletonHolder<CRiskFuzzyScore, CreateUsingNew> Singleton;

	public:
		/*!
		*
		**/
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
		struct FuzzyScoreStandard : public QuickOperationFlag
		{
			CLASS(FuzzyScoreStandard, agm::reflection::NullClass);
			// score idx
			FIELD2(public,long, m_idx);
			// scoring type
			FIELD2(public,long, m_templateid);
			// linguistic defintion
			FIELD2(public,string, m_favorability);
			// upper score
			FIELD2(public,double, m_upper);
			// lower score
			FIELD2(public,double, m_lower);
			// right shift
			FIELD2(public,double, m_rightupper);
			// left shift
			FIELD2(public,double, m_leftlower);
			// remark
			FIELD2(public,string, m_remark);

			/*!
			*
			**/
			FuzzyScoreStandard() : m_idx(0), m_templateid(0), m_favorability("")
				, m_lower(0.), m_upper(0.), m_rightupper(0.), m_leftlower(0.), m_remark("")
			{
			}

			/*!
			*
			**/
			FuzzyScoreStandard(long id,long tid,string favor,double upper,double lower,double right,double left,string remark) : m_idx(id), m_templateid(tid), m_favorability(favor)
				, m_upper(upper), m_lower(lower), m_rightupper(right), m_leftlower(left), m_remark(remark)
			{
			}

			/*!
			*
			**/
			const FuzzyScoreStandard &operator=(const FuzzyScoreStandard &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_operation = other.m_operation;
				m_idx = other.m_idx;
				m_templateid = other.m_templateid;
				m_favorability = other.m_favorability;
				m_lower = other.m_lower;
				m_upper = other.m_upper;
				m_rightupper = other.m_rightupper;
				m_leftlower = other.m_leftlower;
				m_remark = other.m_remark;

				return *this;
			}
		};
		typedef std::vector<FuzzyScoreStandard> FuzzyStandardVector;
		typedef FuzzyStandardVector::iterator stand_itr;
		typedef FuzzyStandardVector::const_iterator stand_citr;

		/*!
		*
		**/
		struct FuzzyScoreRule : public QuickOperationFlag
		{
			// unique id
			long m_ruleid;
			// foreign key
			long m_factorIdx;
			// if condition
			string m_condition;
			// other if condition
			long m_nextid;
			// condition operator
			long m_operator;
			// related score id
			long m_scoreid;
			// related score type
			long m_scoreType;

			/*!
			*
			**/
			FuzzyScoreRule() : m_ruleid(0), m_factorIdx(0), m_condition(""), m_nextid(0)
				, m_operator(0), m_scoreid(0), m_scoreType(0)
			{
			}

			/*!
			*
			**/
			const FuzzyScoreRule &operator=(const FuzzyScoreRule &other)
			{
				if(this == &other)
				{
					return *this;
				}

				// parent
				m_operation = other.m_operation;
				// unique id
				m_ruleid = other.m_ruleid;
				// foreign key
				m_factorIdx = other.m_factorIdx;
				// if condition
				m_condition = other.m_condition;
				// other if condition
				m_nextid = other.m_nextid;
				// condition operator
				m_operator = other.m_operator;
				// related score id
				m_scoreid = other.m_scoreid;
				// related score type
				m_scoreType = other.m_scoreType;

				return *this;
			}
		};
		typedef std::vector<FuzzyScoreRule> FuzzyRuleVector;
		typedef FuzzyRuleVector::iterator rule_itr;
		typedef FuzzyRuleVector::const_iterator rule_citr;

		/*!
		*
		**/
		struct FuzzyFunctionMember : public QuickOperationFlag
		{
			// member id
			long m_memberIdx;
			// foreign key
			long m_factorIdx;
			// value type such as cateogrial, ordinal, rational etc
			long m_valueType;
			// function type such as triangular, trapedoial
			long m_memberType;
			// member name
			string m_name;
			// corresponding geological favorability
			string m_favorability;
			// the shift of left side
			double m_leftlower;
			// lower
			double m_lower;
			// upper 
			double m_upper;
			// the shift of right side
			double m_rightupper;
			// qualititative description like categorial value
			string m_svalue;

			/*!
			*
			**/
			FuzzyFunctionMember() : m_memberIdx(0), m_factorIdx(0), m_valueType(0), m_memberType(0)
				, m_name(""), m_favorability(""), m_upper(0.), m_lower(0.), m_rightupper(0.), m_leftlower(0.), m_svalue("")
			{
			}

				/*!
			*
			**/
			FuzzyFunctionMember(long memberIdx,long factorIdx,long valueType,long memberType,string name,string favorability,
				double upper,double lower,double rightupper,double leftlower,string svalue) : m_memberIdx(memberIdx), m_factorIdx(factorIdx), m_valueType(valueType), m_memberType(memberType)
				, m_name(name), m_favorability(favorability), m_upper(upper), m_lower(lower), m_rightupper(rightupper), m_leftlower(leftlower), m_svalue(svalue)
			{
			}

			/*!
			*
			**/
			const FuzzyFunctionMember &operator=(const FuzzyFunctionMember &other)
			{
				if(this == &other)
				{
					return *this;
				}

				// parent
				m_operation = other.m_operation;
				// member id
				m_memberIdx = other.m_memberIdx;
				// foreign key
				m_factorIdx = other.m_factorIdx;
				// value type such as cateogrial, ordinal, rational etc
				m_valueType = other.m_valueType;
				// function type such as triangular, trapedoial
				m_memberType = other.m_memberType;
				// member name
				m_name = other.m_name;
				// corresponding geological favorability
				m_favorability = other.m_favorability;
				// upper 
				m_upper = other.m_upper;
				// lower
				m_lower = other.m_lower;
				// the shift of right side
				m_rightupper = other.m_rightupper;
				// the shift of left side
				m_leftlower = other.m_leftlower;
				// qualititative description like categorial value
				m_svalue = other.m_svalue;

				return *this;
			}
		};
		typedef std::vector<FuzzyFunctionMember> FuzzyMemberVector;
		typedef FuzzyMemberVector::iterator member_itr;
		typedef FuzzyMemberVector::const_iterator member_citr;
	/*!
	* Row defintion
	**/
	struct RowData
	{
		long m_idx;
		char m_marginFactorName[80];
		char m_conditionFactorName[80];
		double m_fuzzyLower;
		double m_fuzzyScore;
		double m_fuzzyUpper;
		long m_distributionChoice;
		int m_weight;

		// dumy fileds whic not list in grid table
		CAnyDistributionStrategy *m_distribution;
		float m_fValue;
		string m_sValue;

		/*!
		*
		**/
		RowData()
		{
			::strcpy(m_marginFactorName, "");
			::strcpy(m_conditionFactorName, "");
			m_fuzzyLower = 0.;
			m_fuzzyScore = 0.;
			m_fuzzyUpper = 0.;
			m_distributionChoice = 0;
			m_weight = 0;
			m_idx = 0;
			m_distribution = 0;
			m_fValue = 0.;
			m_sValue = "";
		}
	};
	typedef std::vector<RowData> RowVector;
	public:
		//
		//
		//
		/*!
		*
		**/
		CRiskFuzzyScore();

		/*!
		*
		**/
		CRiskFuzzyScore(CAccumulationElement *curElement);

		/*!
		*
		**/
		~CRiskFuzzyScore();

	private:
		CRiskFuzzyScore(const CRiskFuzzyScore &other);
		const CRiskFuzzyScore &operator=(const CRiskFuzzyScore &other);

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
		int GetFuzzyRuleCount();

		/*!
		*
		**/
		FuzzyScoreRule &GetFuzzyRule(int index);

		/*!
		*
		**/
		void FindFuzzyRule(long factorIdx, FuzzyRuleVector &rules);

		/*!
		*
		**/
		void UpdateFuzzyRule(const FuzzyScoreRule &rule, bool isDelete = false);

		//
		//
		//
		/*!
		*
		**/
		int GetFuzzyMemberCount();

		/*!
		*
		**/
		FuzzyFunctionMember &GetFuzzyMember(int index);

		/*!
		*
		**/
		void FindFuzzyMember(long factorIdx, FuzzyMemberVector &members);

		/*!
		*
		**/
		void UpdateFuzzyMember(FuzzyFunctionMember &member, bool isDelete = false);

		//
		//
		//
		/*!
		*
		**/
		int GetFuzzyStandardCount();

		/*!
		*
		**/
		FuzzyScoreStandard GetFuzzyStandard(int index);

		/*!
		*
		**/
		void UpdateFuzzyStandard(const FuzzyScoreStandard &standard, bool isDelete = false);

		//
		// persistence for fuzzy uncertainty risk evaluation
		//
		/*!
		*
		**/
		void SetProbName(const string &name)
		{
			assert(name.size());
			m_probName = name;
		}

		/*!
		*
		**/
		void SetProbPara(const string &para)
		{
			assert(para.size());
			m_probPara = para;
		}

		/*!
		*
		**/
		void SetUncertainty(double min, double avg, double max)
		{
			m_minrisk = min;
			m_avgrisk = avg;
			m_maxrisk = max;
		}

		//
		//
		//
		/*!
		*
		**/
		static CRiskFuzzyScore &GetSingleton(short type);

		void DoMonteSimulate();
		void DoGetRandoms(CGeoPoint<double> *samples, int iterations, string &mode, double lower, double mid, double upper);
	private:
		//
		//
		//
		/*!
		*
		**/
		void DoLoadScore(CAnyAccessor &accessor, FuzzyScoreStandard &standard);

		/*!
		*
		**/
		void DoLoadScores(CAnyAccessor &accessor);

		/*!
		*
		**/
		void DoLoadMember(CAnyAccessor &accessor, FuzzyFunctionMember &member);

		/*!
		*
		**/
		void DoLoadMembers(CAnyAccessor &accessor);

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
		int DoCommitFuzzyMember(CAnyAccessor &accessor);

		/*!
		*
		**/
		void DoCommitFuzzyStandard(CAnyAccessor &accessor);
	public:
		//
		//
		//
		/*!
		*
		**/
		static bool CompareStandardIdx(const FuzzyScoreStandard &first, const FuzzyScoreStandard &second)
		{
			return first.m_idx < second.m_idx;
		}

		/*!
		*
		**/
		static bool CompareTemplateIdx(const FuzzyScoreStandard &first, const FuzzyScoreStandard &second)
		{
			return first.m_idx < second.m_idx;
		}

		/*!
		*
		**/
		static bool CompareRuleIdx(const FuzzyScoreRule &first, const FuzzyScoreRule &second)
		{
			return first.m_ruleid < second.m_ruleid;
		}

		/*!
		*
		**/
		static bool CompareRuleFactor(const FuzzyScoreRule &first, const FuzzyScoreRule &second)
		{
			return first.m_factorIdx < second.m_factorIdx;
		}

		/*!
		*
		**/
		static bool CompareRuleScore(const FuzzyScoreRule &first, const FuzzyScoreRule &second)
		{
			return first.m_scoreType < second.m_scoreType;
		}

		/*!
		*
		**/
		static bool CompareMemberFactor(const FuzzyFunctionMember &first, const FuzzyFunctionMember &second)
		{
			return first.m_factorIdx < second.m_factorIdx;
		}

		/*!
		* deprecated
		**/
		static bool CompareMemberIdx(const FuzzyFunctionMember &first, const FuzzyFunctionMember &second)
		{
			return first.m_memberIdx < second.m_memberIdx;
		}

	private:
		//
		bool m_isFuzzyStandardDirty;
		FuzzyStandardVector m_fuzzyStandards;
		FuzzyStandardVector m_deletedFuzzyStandards;

		//
		bool m_isFuzzyMemberDirty;
		FuzzyMemberVector m_fuzzyMembers;
		FuzzyMemberVector m_deletedFuzzyMembers;

		//
		bool m_isFuzzyRuleDirty;
		FuzzyRuleVector m_fuzzyRules;

		// for fuzzy inference/uncertainty persistence
		string m_probName;
		string m_probPara;
		double m_minrisk;
		double m_avgrisk;
		double m_maxrisk;

	public:
		// fuzzy-related tables
		static string m_fuzzyScoreTable;
		static string m_fuzzyMemberTable;
		static string m_fuzzyRuleTable;

		RowVector m_rows;
		// current setting
		int m_seedType;
		long m_seedValue;

		// random number
		long m_iterations;

		// the number of histogram frequency
		long m_fractiles;
		int m_curRow;
		int m_curCol;
		std::vector<string> parentNames;
		CGeoPoint<double> *samples;
		CAnyDistributionStrategy::DistributionParameters parameters;
		CAnyRandomGenerator *generator;
		CAnyDistributionStrategy **parentDistributions;
		int iterations;
	};
}

#endif