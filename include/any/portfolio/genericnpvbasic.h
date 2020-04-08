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
#ifndef __ANYPORTFOLIO_GENERIC_NPV_BASIC_H__
#define __ANYPORTFOLIO_GENERIC_NPV_BASIC_H__

// refer to STL
#include "any/base/anystl.h"
using namespace std;

// refer to geopoint
#include "any/base/anygeom.h"
using namespace AnyBase;

namespace AnyPortfolio
{
	//2014/10/8
	enum AbroadModeType
	{
		AMT_Shale = 0,//2016/6/21: shale version
		AMT_Mine_Tax,
		AMT_PSC,
		AMT_SERVICE_CONTRACT,
	};

	// valuation date
	struct ValuationDate
	{
		double m_start;	// can be YEAR or MONTH, even DAY
		double m_end;
		double m_duration;

		/*!
		*
		**/
		ValuationDate(int mode = AMT_Mine_Tax)
		{
			//2014/10/9, initialize different date
			if (mode == AMT_Mine_Tax)
			{
				 m_start = 20130101.;
				 m_end = 20201231.;
				 m_duration = 8.;
			}
			else if (mode == AMT_PSC)
			{
				m_start = 20041208.;
				m_end = 20321231.;
				m_duration = 29.;
			}
			else if (mode == AMT_SERVICE_CONTRACT)
			{
				//2014/10/20
				m_start = 20100101.;
				m_end = 20291231.;
				m_duration = 20.;
			}
			else if (mode == AMT_Shale)//2016/6/21
			{
				m_start = 20150101.;
				m_end = 20301231.;
				m_duration = 16.;
			}
		}
	};

	struct NPVVariableName
	{
		//2014/10/28: record the whole string between brackets, such as (aaa)->aaa
		string m_wholeStr;

		//
		string m_key;
		double m_value;
		
		//
		bool m_isGroup;
		bool m_isGroupYear;//current year

		//2014/9/25:NPVGROUP(StartYear)
		bool m_isGroupStartYear;//start year
		//2014/10/15:NPVGROUP(EndYear)
		bool m_isGroupEndYear;//start year
		//
		bool m_isLookup;
		bool m_isLookupOrder;
			
		//
		bool m_isTotal;
		bool m_isAccumlative;
		bool m_isExcluded;
		bool m_isPrevious;

		//2016/7/1: flag of min/max:NPVGROUP(Invest:aaa<Mx>/<Mn>)
		bool m_isMax;
		bool m_isMin;
		
		//2014/9/25: find year value in determined year
		//such as NPVGROUP(Invest: Total Investment<Find><-1>), find the value in previous year 
		bool m_isFindYear;
		int m_findYearNum;
		
		//2014/9/25: COUNTIF(Invest: Total Investment<NPVGROUP(StartYear)><NPVGROUP(Year)>,>0)
		bool m_isCountIF;
		int m_startCIF;//StartYear:2013
		int m_endCIF;//Year:2014...
		string m_conditionCIF;//>0

		//2014/9/26
		bool m_isSumIF;
		int m_startSIF;//StartYear:2013
		int m_endSIF;//Year:2014...

		//
		bool m_isNpv;
		bool m_isIRR;
		
		//2014/10/11
		bool m_isSolution;

		/*!
		*
		**/
		NPVVariableName() : m_key(""), m_isGroup(false),m_value(0.),\
			m_isGroupYear(false),m_isAccumlative(false),m_isTotal(false),m_isExcluded(false),m_isPrevious(false),\
			m_isLookup(false), m_isLookupOrder(false),m_isNpv(false),m_isIRR(false),m_isFindYear(false),m_findYearNum(-1),\
			m_isCountIF(false),m_startCIF(2013),m_endCIF(2014),m_conditionCIF(">0"),m_isGroupStartYear(false),\
			m_isSumIF(false),m_startSIF(2013),m_endSIF(2014),m_isSolution(false),m_isGroupEndYear(false),m_wholeStr(""),m_isMax(false),m_isMin(false)
		{
		}
	};
	typedef std::vector<NPVVariableName> VariableVector;

	//
	enum ResourceType
	{
		RT_Crude =  1 << 31,
		RT_Gas	   =  1 << 30,
	};

	// 
	enum MarketType
	{
		MT_Domestic = 1 << 23,
		MT_Export     = 1 << 22,
	};

	//
	enum StakeholderType
	{
	};

	//x versus multiple y
	typedef std::map<double, std::vector<double>> ValueMap;
	typedef ValueMap::iterator vm_itr;
	typedef ValueMap::const_iterator vm_citr;

	/*!
	*
	**/
	static bool CompareRecordValue(const CGeoPoint<double> &first, const CGeoPoint<double> &second)
	{
		return first.m_x < second.m_x;
	}

	/*!
	* generic parameter record
	**/
	struct ParameterRecord
	{
		// key
		string m_key;
		
		//category  such as Basic, Price... 
		string m_category;
		
		// name 
		string m_name;
		string m_oldName;

		// formula
		string m_formulae;
		std::vector<string> m_formulaes;

		//unit
		string m_unit;
		// is group value? 
		bool m_isSolutionValue;

		//
		bool m_isTotalShown;
		bool m_isOnlyTotalShown;

		//
		string m_dependedKey;
		bool m_isResolved;

		// value
		std::vector<CGeoPoint<double> > m_value;

		//tree related
		int m_pLevel;
		string m_parentName;
		std::vector<string> m_childrenNames;

		//newly added:2014/8/26
		//category  such as inflation parameters, commodity rate parameters etc
		string m_subCategory;
		bool m_isSlide;

		//x versus multiple y
		ValueMap m_valueMap;

		//2014/10/16:record variables, preventing from getting variables repeatedly
		VariableVector m_variables;

		/*!
		* 
		**/
		ParameterRecord()
		{
			Reset();
		}

		/*!
		* 
		**/
		ParameterRecord(const ParameterRecord &other)
		{
			*this = other;
		}

		/*!
		* 
		**/
		const ParameterRecord &operator=(const ParameterRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_key = other.m_key;
			m_category = other.m_category;
			m_name = other.m_name;
			m_formulae = other.m_formulae;
			m_unit = other.m_unit;
			m_isSolutionValue = other.m_isSolutionValue;

			//
			m_isTotalShown = other.m_isTotalShown;
			m_isOnlyTotalShown = other.m_isOnlyTotalShown;

			//
			m_dependedKey = other.m_dependedKey;
			m_isResolved = other.m_isResolved;

			//
			m_value.clear();
			m_value.assign(other.m_value.begin(), other.m_value.end());

			//
			m_formulaes.clear();
			m_formulaes.assign(other.m_formulaes.begin(), other.m_formulaes.end());

			//
			m_pLevel = other.m_pLevel;
			m_parentName = other.m_parentName;
			
			m_childrenNames.clear();
			m_childrenNames.assign(other.m_childrenNames.begin(),other.m_childrenNames.end());

			//
			m_oldName = other.m_oldName;

			//
			m_subCategory = other.m_subCategory;
			m_isSlide = other.m_isSlide;

			//
			m_valueMap = other.m_valueMap;

			//2014/10/16
			m_variables = other.m_variables;
			return *this;
		}

		/*!
		* 
		**/
		ParameterRecord(const ParameterRecord *other)
		{
			if(!other)
			{
				return;
			}

			m_key = other->m_key;
			m_category = other->m_category;
			m_name = other->m_name;
			m_formulae = other->m_formulae;
			m_unit = other->m_unit;
			m_isSolutionValue = other->m_isSolutionValue;

			m_isTotalShown = other->m_isTotalShown;
			m_isOnlyTotalShown = other->m_isOnlyTotalShown;

			m_dependedKey = other->m_dependedKey;
			m_isResolved = other->m_isResolved;

			m_value.clear();
			m_value.assign(other->m_value.begin(), other->m_value.end());

			//
			m_formulaes.clear();
			m_formulaes.assign(other->m_formulaes.begin(), other->m_formulaes.end());

			//
			m_pLevel = other->m_pLevel;
			m_parentName = other->m_parentName;

			m_childrenNames.clear();
			m_childrenNames.assign(other->m_childrenNames.begin(),other->m_childrenNames.end());
			
			//
			m_oldName = other->m_oldName;

			m_subCategory = other->m_subCategory;
			m_isSlide = other->m_isSlide;

			m_valueMap = other->m_valueMap;

			//2014/10/16
			m_variables = other->m_variables;
		}
				
		/*!
		* 
		**/
		void Reset()
		{
			m_key = "";
			m_category = "";
			m_name = "";
			m_unit = "";
			
			//
			m_formulae = "";
			m_formulaes.clear();
				
			//
			m_value.clear();
			m_isSolutionValue = false;

			m_isTotalShown = true;
			m_isOnlyTotalShown = false;

			//
			m_dependedKey = "";
			m_isResolved = false;
					
			//
			m_pLevel = 0;
			m_parentName = "";
			m_childrenNames.clear();

			//
			m_oldName = "";

			//
			m_subCategory = "";
			m_isSlide = false;

			m_valueMap.clear();

			//2014/10/16
			m_variables.clear();
		}

		/*!
		* 
		**/
		double GetValues(double x = ANY_NAN, int order = 2, int isByOrder = -1)
		{
			int count = m_valueMap.size();

			if (!count)
			{
				return ANY_NAN;
			}

			//changes to real order, 
			order --;

			std::vector<CGeoPoint<double> > vals;
			vm_citr itr = m_valueMap.begin();
			for (;itr != m_valueMap.end();itr++)
			{
				CGeoPoint<double> val(itr->first,order < itr->second.size() ? itr->second[order] : 0.);
				vals.push_back(val);
			}

			//
			std::sort(vals.begin(),vals.end(),CompareRecordValue);
			return DoGetValue(vals,m_isSlide,x,-1,isByOrder);
		}

		/*!
		* 
		**/
		double GetValue(double x = ANY_NAN, int xx = -1, int yy = -1)
		{
			return DoGetValue(m_value,m_isSlide,x,xx,yy);
		}

		/*!
		* 
		**/
		double DoGetValue(std::vector<CGeoPoint<double>> &vals, bool isSlide, double x, int xx, int yy)
		{
			int count = vals.size();

			if(!count)
			{
				return ANY_NAN;
			}

			if (xx == -1 && yy == -1)
			{
				// directly
				if(ISNAN(x))
				{
					return vals[0].m_y;
				}

				//only one record
				if (count == 1)
				{
					return vals[0].m_y;
				}

				if (!isSlide)
				{
					//outside the range
					if (x >= vals[count-1].m_x)
					{
						return vals[count-1].m_y;
					}
					else if (x < vals[0].m_x)
					{
						return 0./*vals[0].m_y*/;
					}

					// interpolation
					int i = 1;
					for(; i < count; i++)
					{
						if(x >= vals[i-1].m_x && x < vals[i].m_x)
						{
							return vals[i-1].m_y;
						}
					}
				}
				else
				{
					if (x < vals[0].m_x)
					{
						return vals[0].m_x * vals[0].m_y;
					}

					// interpolation
					double val = 0.;

					int i = 1;
					for(; i < count; i++)
					{
						if(x >= vals[i-1].m_x)
						{
							double max = x < vals[i].m_x ? x : vals[i].m_x;
							val += (max - vals[i-1].m_x) * vals[i-1].m_y;

							if (x < vals[i].m_x)
							{
								return val;
							}
						}
					}
				}				

				// exception
				return ANY_NAN;
			}
			else
			{
				if (xx != -1)
				{
					if (xx >=0 && xx < count)
					{
						return vals[xx].m_x;
					}
				}

				if (yy != -1)
				{
					if (yy >=0 && yy < count)
					{
						return vals[yy].m_y;
					}
				}

				return ANY_NAN;
			}
		}
	};
	
	//
	typedef std::vector<ParameterRecord> ParameterVector;
	typedef ParameterVector::iterator par_itr;
	typedef ParameterVector::const_iterator par_citr01;

	//
	typedef std::map<string,ParameterVector> DependedParaMap;
	typedef DependedParaMap::iterator dpm_itr;
	typedef DependedParaMap::const_iterator dpm_citr;

	//
	/*!
	*
	**/
	struct ParameterTreeNode : public ParameterRecord
	{
		//level
		int m_level;

		// relations
		ParameterTreeNode *m_parent;
		std::vector<ParameterTreeNode *> m_children;

		ParameterTreeNode(): m_level(0), m_parent(0)
		{
			
		}

		//
		ParameterTreeNode(const ParameterRecord &other)
		{
			m_key = other.m_key;
			m_category = other.m_category;
			m_name = other.m_name;
			m_formulae = other.m_formulae;
			m_unit = other.m_unit;
			m_isSolutionValue = other.m_isSolutionValue;

			//
			m_isTotalShown = other.m_isTotalShown;
			m_isOnlyTotalShown = other.m_isOnlyTotalShown;

			//
			m_dependedKey = other.m_dependedKey;
			m_isResolved = other.m_isResolved;

			//
			m_value.clear();
			m_value.assign(other.m_value.begin(), other.m_value.end());

			//
			m_formulaes.clear();
			m_formulaes.assign(other.m_formulaes.begin(), other.m_formulaes.end());

			//
			m_pLevel = other.m_pLevel;
			m_parentName = other.m_parentName;

			m_childrenNames.clear();
			m_childrenNames.assign(other.m_childrenNames.begin(),other.m_childrenNames.end());

			//
			m_oldName = other.m_oldName;

			//tree node related
			m_level = other.m_pLevel;

			//
			m_subCategory = other.m_subCategory;
			m_isSlide = other.m_isSlide;

			//
			m_valueMap = other.m_valueMap;

			//2014/10/16
			m_variables = other.m_variables;
		}
	};

	//
	typedef std::map<int, ParameterTreeNode*> ParaSolution;
	typedef ParaSolution::iterator psolution_itr;
	typedef ParaSolution::const_iterator psolution_citr;

	//save remark for m_solutionStr in price\invest\production...
	typedef std::map<string, string> SolutionRemarkMap;
	typedef SolutionRemarkMap::iterator srm_itr;
	typedef SolutionRemarkMap::const_iterator srm_citr;
}
#endif