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
#ifndef __ANYPORTFOLIO_GENERIC_NPV_FORMULAR_H__
#define __ANYPORTFOLIO_GENERIC_NPV_FORMULAR_H__

// refer to parent
//#include "anybase\anyformulaparser.h"
//using namespace AnyBase;

#include "anyformulaparser.h"

// refer to generic structs
#include "genericnpvbasic.h"

//
namespace AnyPortfolio
{
	// forward class
	class CAnyGenericNPVParameter;

	/*!
	* generica call back mechanism
	**/
	class CAnyGenericNPVFormulae : public CAnyFormulaParser
	{

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGenericNPVFormulae(ParameterVector &parameters);

		/*!
		*
		**/
		CAnyGenericNPVFormulae();

		/*!
		*
		**/
		~CAnyGenericNPVFormulae();

	public:
		//
		void Reset(ParameterVector &parameters);
		
		//
		void GetVariable(VariableVector &variables, bool isReGet = false);

		//re-write
		virtual double Factor(int& nPosition, string& strCharacter);
		
		/*!
		*
		**/
		static string Trim(string &str);
	private:

		

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

		/*!
		*
		**/
		ParameterRecord &DoFind(const string &key);

		/*!
		*2014/9/24
		**/
		string GetStringInMethod(const string &formula, int& nPosition, string& strCharacter, int &wBegin);

		/*!
		*
		**/
		bool GetVars(const string &str, int& nPosition, int &wBeginn);

	private:
		//
		ParameterVector m_parameters;

		//
		VariableVector m_variables;
		
		//
		bool m_isGettingVariables;
	};
}
#endif