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
#ifndef __ANYBASE_FORMULAR_PARSER_H__
#define __ANYBASE_FORMULAR_PARSER_H__

// Refer to EXPORT definition
#include "anyportfolio.h"

#define ANZFUNKTKONST 10

#include <string>
#include <vector>
#include <iostream>
#include <exception>
using namespace std;

namespace AnyPortfolio
{
	class ANYPORTFOLIO_CLASS CAnyFormulaParser  
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyFormulaParser();

		/*!
		*
		**/
		virtual ~CAnyFormulaParser();
	public:
		//
		//
		//
		void StripFormula(string& strFormula);
		string GetFormula();
		void SetFormula(string &formula);
		void SetFunctConst(int index, double val);
		
		//Interface
		double Calculation(string strFormula, double xValue, int& errorPosition, string& errorText, bool strip = true);
	
		void ReplaceAll(string &str,const string &old_value,const string &new_value);  
	protected:
		//
		//
		//
		virtual double SignFactor(int& nPosition, string& strCharacter);
		virtual double Expression(int& nPosition, string& strCharacter);
		virtual double SimpleExpression(int& nPosition, string& strCharacter);
		virtual double Term(int& nPosition, string& strCharacter);
		virtual double Factor(int& nPosition, string& strCharacter);
		
		double Char_n(int& nPosition, string& strCharacter);
		string StrChar_(char DecimalZahl);

		string GetNextToken(string& strSrc, const string strDelim);
		double SINQ(double Winkel_grad);
		double COSQ(double Winkel_grad);
		double DEG(double x /* rad */) ;
		double RAD(double x /* grad */);
		double Cot(double x);
		long double Signl(long double x);
		double ArSinh(double x);
		double ArCosh(double x);
		double ArTanh(double x);
		double ArCoth(double x);
		double Sqr(double x);		

		//
		string Capital(string& name);
		string Mid(const string& str,int begin,int len);

	protected:
		//Implementation
		string m_strFormula;
		string m_strFunction;
		string m_strErrortext;

		static string g_strF;

		double m_dFktValue;
		double m_dFunctionConstant[ANZFUNKTKONST];
		std::vector<std::string> m_strStandardFunction;

		//record last character
		string m_lastCharacter;
	};
}
#endif
