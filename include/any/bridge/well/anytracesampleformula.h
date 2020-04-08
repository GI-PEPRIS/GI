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
#ifndef __ANYBRIDGE_TRACE_SAMPLE_FORMULA_H__
#define __ANYBRIDGE_TRACE_SAMPLE_FORMULA_H__

// refer to EXPORT & IMPORT
#include "..\anybridge.h"

// refer to ANYTRACESAMPLE
#include "..\anybridgedatamodel.h"

#include "anytracesamplealgebra.h"

// namespace
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyTraceSampleFormula
	{
		const static int ANZFUNKTKONST1 = 10;

	public:
		//
		typedef std::map<std::string, CAnyTraceSampleAlgebra *> TraceSampleMap;
		typedef TraceSampleMap::iterator tsm_itr;
		typedef TraceSampleMap::const_iterator tsm_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyTraceSampleFormula();

		/*!
		*
		**/
		~CAnyTraceSampleFormula();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Register(CAnyTraceSampleAlgebra *algebra);

		/*!
		*
		**/
		void Remove(const string &name);

		/*!
		*
		**/
		void RemoveAll();

		//
		//
		//
		/*!
		*
		**/
		void Calculation(string strFormula, const CAnyTraceSampleAlgebra &xMap, CAnyTraceSampleAlgebra &result, int& errorPosition, string& errorText, bool strip = true);

		/*!
		* deprecated function?
		**/
		void SetFunctConst(int index, double val);

		//
		//
		//
		/*!
		*
		**/
		void StripFormula(string& strFormula);

		/*!
		*
		**/
		void ReplaceAll(string &str,const string &old_value,const string &new_value);

	private:
		
		//
		//
		//
		/*!
		*
		**/
		string Mid(const string& str,int begin,int len);

		/*!
		*
		**/
		double Char_n(int& nPosition, string& strCharacter);

		/*!
		*
		**/
		string StrChar_(char DecimalZahl);

		/*!
		*
		**/
		CAnyTraceSampleAlgebra Expression(int& nPosition, string& strCharacter);

		/*!
		*
		**/
		CAnyTraceSampleAlgebra SimpleExpression(int& nPosition, string& strCharacter);

		/*!
		*
		**/
		CAnyTraceSampleAlgebra Term(int& nPosition, string& strCharacter);

		/*!
		*
		**/
		CAnyTraceSampleAlgebra SignFactor(int& nPosition, string& strCharacter);

		/*!
		*
		**/
		CAnyTraceSampleAlgebra Factor(int& nPosition, string& strCharacter);

		/*!
		*
		**/
		std::string Capital( string& name );

	public:
		// maps in formular
		TraceSampleMap m_sampleMap;
		
		// back map
		CAnyTraceSampleAlgebra m_bkMap;

		// formular parser
		string m_formular;
		string m_function;
		string m_error;
		std::vector<std::string> m_standards;
		double m_constants[ANZFUNKTKONST1];

		//
		string g_strF;
	};
}
#endif