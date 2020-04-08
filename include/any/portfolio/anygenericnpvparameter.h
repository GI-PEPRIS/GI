/*!
 * The AnyVis of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * kinds of information visualization etc.
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
#ifndef __ANYPORTFOLIO_GENERIC_NPV_PARAMETER_H__
#define __ANYPORTFOLIO_GENERIC_NPV_PARAMETER_H__

// refer to macroes
#include "anyportfolio.h"

// refer to generic basic
#include "genericnpvbasic.h"

//
namespace AnyPortfolio
{
	// forward class
	class CAnyGenericNPVFormulae;

	/*!
	*
	**/
	class ANYPORTFOLIO_CLASS CAnyGenericNPVParameter
	{
		// relatives
		friend class CAnyGenericNPVPriceStrategy;
		
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGenericNPVParameter(const ValuationDate &duration, CAnyGenericNPVParameter *depended = 0, int mode = AMT_Mine_Tax);

		/*!
		*
		**/
		~CAnyGenericNPVParameter();

	public:
		//
		//
		//
		/*!
		*
		**/
		static bool IsExist(const string &key, const ParameterVector &parameters);

		/*!
		*
		**/
		static void AddParameter(ParameterRecord &record, ParameterVector &parameters);

		/*!
		*
		**/
		static void UpdateParameter(const string &key, ParameterRecord &newRecord, ParameterVector &parameters);

		/*!
		*
		**/
		static void RemoveParameter(const string &key, ParameterVector &parameters);

		/*!
		*
		**/
		static ParameterRecord &FindParameter(const string &key, ParameterVector &parameters);

		//
		//
		//
		/*!
		*
		**/
		bool IsExist(const string &key);

		/*!
		*
		**/
		void AddParameter(const ParameterRecord &record);
		
		/*!
		*
		**/
		void RemoveParameter(const string &key);

		/*!
		*
		**/
		void ClearAll();

		/*!
		*
		**/
		ParameterRecord &FindParameter(const string &key);
		
		//
		//
		//
		/*!
		*
		**/
		static void DoDeleteNode(ParameterTreeNode *root, bool isSimpleDelete = true);

		/*!
		*
		**/
		static bool CanNodeBeInserted(ParameterTreeNode *root, ParameterTreeNode *node);
				
		/*!
		*
		**/
		static int GetMaxLevel(ParameterTreeNode *root, int maxLevel = -1);

		/*!
		*
		**/
		static void DoGetParameters(ParameterTreeNode *root, ParameterVector &parameters);

		/*!
		*
		**/
		static ParameterTreeNode * DoGetParameterTreeNode(ParameterTreeNode *root, const string &key);

		/*!
		*
		**/
		static void SetRecordInParameters(ParameterVector &parameters, ParameterTreeNode *root); 
		
		//
		//for complicated formula
		//
		/*!
		*
		**/
		void ReplaceVariables(CAnyGenericNPVFormulae *calculater, VariableVector &variables, int year, string &formula, ParameterRecord &npvRecord, \
			ParameterRecord &irrRecord, ParameterTreeNode *root, ParameterVector &parameters, ParameterVector &totalParameters);
		
		/*!
		*
		**/
		double GetValue(int year, NPVVariableName &var, ParameterTreeNode *root, ParameterVector &parameters, CAnyGenericNPVFormulae *calculater = 0);

		//
		//2014/10/14: for simple formula
		//
		/*!
		*
		**/
		void ReplaceVariables(CAnyGenericNPVFormulae *calculater, VariableVector &variables, int year, string &formula, ParameterRecord &record, \
			ParameterVector &parameters, ParameterVector &totalParameters, bool isNeedToReplace = true);

		/*!
		*
		**/
		double GetValue(int year, NPVVariableName &var, ParameterVector &parameters, CAnyGenericNPVFormulae *calculater = 0);

		//
		//
		//
		/*!
		* TODO:
		* in future, to use four bytes encoding different solution or evaluation models?
		*
		**/
		void SetSolution(int solution, int type)
		{
			m_solution = solution;
			m_type = type;
		}

		/*!
		*
		**/
		int GetSolution()
		{
			return m_solution;
		}

		/*!
		* 2014.9.4: solution type from int to string
		**/
		
		void SetSolutionStr(const string &solution)
		{
			m_solutionStr = solution;
		}

		/*!
		* 2014.9.4: solution type from int to string
		**/
		string GetSolutionStr()
		{
			return m_solutionStr;
		}
		/*!
		*
		**/
		ParameterVector &GetSolutionKinds()
		{
			return m_kinds;
		}

		/*!
		*
		**/
		void SetSolutionKinds(ParameterVector &kinds)
		{
			m_kinds = kinds;
		}

		/*!
		*
		**/
		void SetDuration(const ValuationDate &duration)
		{
			m_duration = duration;
		}

		//
		//
		//
		/*!
		*
		**/
		virtual bool Resolve();

		/*!
		*
		**/
		void DoSetDependedParameters(ParameterVector &total, CAnyGenericNPVParameter *depended);

		//
		//
		//
		/*!
		*
		**/
		double GetNPV(ParameterRecord &record, double rate, int startYear, int endYear);

		/*!
		*
		**/
		double GetIRR(ParameterRecord &record, int startYear, int endYear);
	
		//
		//
		//
		/*!
		*
		**/
		virtual void ResetParameters(const string &category);

		/*!
		*
		**/
		const ParameterVector &GetParameters();

		/*!
		*
		**/
		void SetParameter(const ParameterVector &parameters);

		//
		//
		//
		/*!
		*
		**/
		void SetScenarioMode(bool isScenarioMode = false);

		/*!
		*
		**/
		void SetScenarioVals(std::vector<double> &vals);

		//
		/*!
		*2018/10/11: basic parameters for abroad mode
		**/
		void SetScenarioBasicKeys (const std::vector<std::string> &abroad_basic_keys);

		//
		//
		//
		/*!
		* update itself -- for parameters
		**/
		void UpdateFormula(const string &oldKey, const string &newKey);

		/*!
		* update itself -- for parameter tree node
		**/
		void UpdateFormula(const string &oldKey, const string &newKey, const ParaSolution &solutions);

		/*!
		*
		**/
		void DoUpdateFormula(const string &oldKey, const string &newKey, ParameterTreeNode *root);

		//
		//
		//
		/*!
		*
		**/
		std::string GetParameterStr();

		/*!
		*
		**/
		static std::string DoGetParameterStr(const ParameterVector &parameters);

		/*!
		*
		**/
		std::string GetParameterStr(const ParaSolution &solutions);

		/*!
		*
		**/
		void GetParameterTreeNodesFromParameters(std::vector<ParameterTreeNode *> &nodes, const ParameterVector &parameters);

		//
		//solution remark
		//
		/*!
		*
		**/
		static std::string DoGetSolutionRemarkStr(const SolutionRemarkMap &map);

		/*!
		*
		**/
		void SetSolutionRemarkMap(const SolutionRemarkMap &map);

		/*!
		*
		**/
		const SolutionRemarkMap &GetSolutionRemarkMap();

		/*!
		*
		**/
		bool UpdateSolutionRemarkMap(const string &newKey, const string &oldKey, const string &remark = "");

		/*!
		*
		**/
		bool DoUpdateSolutionRemarkMap(SolutionRemarkMap &map, const string &newKey, const string &oldKey, const string &remark = "");

		/*!
		*
		**/
		bool DeleteSolutionRemarkMap(const string &key);

		//
		//
		//
		/*!
		*2014/10/17: get variables
		**/
		bool DoGetVariables(ParameterTreeNode *root, CAnyGenericNPVFormulae *calculater, VariableVector &variables, int year, string &formula, bool isClear = true);
	
		/*!
		*
		**/
		static void DoClearValue(ParameterTreeNode *root);
private:
		/*!
		*
		**/
		double DoGetIRR(ParameterRecord &record, double bkFirr, int startYear, int endYear);
	
	protected:
		/*!
		*
		**/
		int GetStartYear();
	//protected:
	public:
		//
		//
		//
		/*!
		*
		**/
		static bool CompareRecordKey(const ParameterRecord &first, const ParameterRecord &second)
		{
			if(!::strcmp((char *)first.m_key.c_str(), (char *)second.m_key.c_str()))
			{
				return true;
			}

			return false;
		}
	public:
		//
		CAnyGenericNPVFormulae *m_formulae;

		//for sensitive calculation
		double m_variable;
	protected:
		//
		ParameterVector m_parameters;
		//
		//CAnyGenericNPVFormulae *m_formulae;

		//kinds of name in solution
		ParameterVector m_kinds;

		// solution
		int m_solution;
		// type or kind
		int m_type;

		// depended
		CAnyGenericNPVParameter *m_depended;
		//
		ValuationDate m_duration;

		//for scenario mode
		bool m_isScenarioMode;
		std::vector<double> m_scenarioVals;

		//2018/10/11: basic parameters for abroad mode
		std::vector<std::string> m_abroad_basic_keys;

		//for save/load
		string m_parameterStr;

		//2014.9.4: solution type from int to string
		string m_solutionStr;
		SolutionRemarkMap m_solutionRemarkMap;

		//mode
		int m_mode;
	};
}
#endif

