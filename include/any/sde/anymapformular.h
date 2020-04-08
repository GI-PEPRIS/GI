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
#ifndef __ANYSDE_SDE_MAP_FORMULAR_H__
#define __ANYSDE_SDE_MAP_FORMULAR_H__

// refer to EXPORT & IMPORT
#include "anysde.h"

// refer to map algebra
#include "anymapalgebra.h"

//
namespace AnySDE
{
	/*!
	*
	**/
	class ANYSDE_CLASS CAnyMapFormular
	{
		const static int ANZFUNKTKONST1 = 10;

	public:
		//
		typedef std::map<string, CAnyMapAlgebra *> LayerMap;
		typedef LayerMap::iterator layer_itr;
		typedef LayerMap::const_iterator layer_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyMapFormular();

		/*!
		*
		**/
		~CAnyMapFormular();

	public:
		//
		//
		//
		/*!
		*
		**/
		void RegisterLayer(CAnyMapAlgebra *layer);

		/*!
		*
		**/
		void RemoveLayer(const string &name);

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
		void Calculation(string strFormula, const CAnyMapAlgebra &xMap, CAnyMapAlgebra &result, int& errorPosition, string& errorText, bool strip = true);

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
		CAnyMapAlgebra Expression(int& nPosition, string& strCharacter);

		/*!
		*
		**/
		CAnyMapAlgebra SimpleExpression(int& nPosition, string& strCharacter);

		/*!
		*
		**/
		CAnyMapAlgebra Term(int& nPosition, string& strCharacter);

		/*!
		*
		**/
		CAnyMapAlgebra SignFactor(int& nPosition, string& strCharacter);

		/*!
		*
		**/
		CAnyMapAlgebra Factor(int& nPosition, string& strCharacter);

		/*!
		*
		**/
		std::string Capital( string& name );

	public:
		// maps in formular
		LayerMap m_layers;
		int m_layerrows;
		int m_layercols;
		// back map
		CAnyMapAlgebra m_bkMap;

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