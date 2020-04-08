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
#ifndef __ANYVIS_RISK_FACTOR_RATIO_PLOT_H__
#define __ANYVIS_RISK_FACTOR_RATIO_PLOT_H__

// refer to macro
#include "anyvis.h"

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to geopoint
#include "any/base/anygeom.h"
#include "any/base/anyvectop.h"
using namespace AnyBase;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyRiskFactorRatioPlot : public CAnyViewHook
	{
	public:

		/*!
		*
		**/
		struct RiskFactor
		{
			std::string m_name;
			int m_validColor;
			int m_invalidColor;
			std::vector<double> m_vals;

			/*!
			*
			**/
			RiskFactor()
			{
				Reset();
			}

			/*!
			*
			**/
			void Reset()
			{
				m_name = "";
				m_validColor = RGB(0,191,255);//deep sky blue
				m_invalidColor = RGB(255,215,0);//golden
				m_vals.clear();
			}
		};
		typedef std::vector<RiskFactor> RiskFactors;
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyRiskFactorRatioPlot(CAnyView &curView);

		/*!
		*
		**/
		virtual ~CAnyRiskFactorRatioPlot();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype);

		//
 		//
		//
		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseMove(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseUp(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		bool DoubleClick(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);

		//
		//
		//
		/*!
		*
		**/
		void SetMapPort();

		/*!
		*
		**/
		bool IsFactorValid();
	private:
		/*!
		*
		**/
		void ResetFactors();

	public:
		//
		RiskFactors m_factors;
		std::string m_leftLabel;
		std::string m_rightLabel;
	};
}
#endif