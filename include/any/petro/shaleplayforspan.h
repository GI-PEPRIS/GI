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
#ifndef __ANYPETRO_SHALE_FORSPAN_H__
#define __ANYPETRO_SHALE_FORSPAN_H__

// refer to EXPORT etc macroes
#include "anypetro.h"

#include "accumulationassessor.h"
#include "accumulationelement.h"
#include "any/math/anydistributionstrategy.h"
using namespace AnyMath;
#include "any/base/anygeom.h"
#include "any/base/anytokenstring.h"
using namespace AnyBase;
//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CShalePlayForspan : public CAccumulationAssessor
	{
	public:
		/*!
		*
		**/
		enum ParameterType
		{
			PT_Unknown = -1,
			PT_X,				// 每个充注单元EUR
			PT_V,				// 未检测区域每个单元的面积
			PT_U,				// 评估总区域的面积
			PT_R,				// 未检测区域占总区域的比例
			PT_S,				// 未检测区域中潜在可能储油区域所占比例
			PT_T,				// 甜点面积
			PT_Max
		};
		struct ParameterSetting
		{
			double m_min;
			double m_max;
			double m_mode;

			CAnyDistributionStrategy *m_distribution;
			double m_mean;
			double m_sd;

			/*!
			*
			**/
			ParameterSetting() : m_min(ANY_NAN), m_max(ANY_NAN), m_mode(ANY_NAN), m_distribution(0), m_mean(ANY_NAN), m_sd(ANY_NAN)
			{
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CShalePlayForspan(CAccumulationElement *curElement, int activityType = ST_Shale_Play_Forspan);
		~CShalePlayForspan();

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetParameter(int whichparameter, double min, double max, double mode);	// means for triangulation
		void SetParameter(int whichparameter, double min, double max);	 // means for lognormal
		const ParameterSetting &GetParameter(int whichparameter);

		void SetNYParameter(int type,double min, double max, double mode);
		void SetNYParameter(int type,double min, double max);

		void MakeSimulation(int simulations);

		const ParameterSetting &GetN()
		{
			return m_N;
		}
		const ParameterSetting &GetEUR()
		{
			return m_Y;
		}
		unsigned int Commit(bool isDeleted = false);
		

		bool GetParameterFromhis(string parastring);

	public:
		//
		ParameterSetting m_parameters[PT_Max];
		ParameterSetting m_N;
		ParameterSetting m_Y;
		
		CAccumulationElement *m_element;
		string m_remark;
		unsigned int m_seed;
		int m_ittnum;
	};
}
#endif
