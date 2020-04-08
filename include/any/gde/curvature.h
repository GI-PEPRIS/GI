/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYGDE_CURVATURE_H__
#define __ANYGDE_CURVATURE_H__

#define SMALLVAL	1e-20

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"
#include "anygdedataset.h"

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CCurvature : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CCurvature();
		~CCurvature();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoHandle(HandlerStruct &handlerstruct);

		/*!
		*
		**/
		void DoGetTraceSample(std::vector<double> &results, int &cmpcount);

		/*!
		*
		**/
		void DoGetTraceHead(std::vector<double> &results);

	public:
		bool m_bUseAziDip; //use azimuth/dip method
		std::vector<CAnyGdeDataSet*> m_datasets;//0:倾角或主测线视倾角,1:方位角或联络线视倾角
		std::vector<bool> m_isgdes;
		std::vector<int> m_enumUnits;//0:角度,1弧度

		int m_nOutSampNum;
		float m_fCdpInterval;
		float m_fLineInterval;
		int m_enumDevMethod;
		float m_fVelocity;
		bool m_bOutputMean;
		bool m_bOutputGaussian;
		bool m_bOutputMaximun;
		bool m_bOutputMinimun;
		bool m_bOutputMostPositive;
		bool m_bOutputMostNegative;
		bool m_bOutputDip;
		bool m_bOutputStrike;
		bool m_bOutputCurvature;
		bool m_bOutputShapeIndex;

		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;
	};
}
#endif
