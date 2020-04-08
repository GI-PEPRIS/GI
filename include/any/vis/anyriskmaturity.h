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
#ifndef __ANYVIS_RISK_MATURITY_H__
#define __ANYVIS_RISK_MATURITY_H__

// refer to export macro
#include "anyvis.h"

// refer to common encapsulated
#include "anyaxises.h"

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyRiskMaturity : public CAnyViewHook, private CAnyAxises
	{
		//
		typedef std::vector<CGeoPoint<double>> MaturityVector;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyRiskMaturity(CAnyView &curView, double probability = 0.);

		/*!
		*
		**/
		~CAnyRiskMaturity();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype);

		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);

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

	public:
		//
		//
		//
		/*!
		*
		**/
		void RenderProbability(double probability);

		/*!
		*
		*/
		void RenderHints(const CGeoPoint<short> &scrPoint);

	private:
		//
		//
		//
		/*!
		*
		**/
		int GetIndicator(const CGeoPoint<double> &pos);

		/*!
		*
		**/
		static bool CompareIndicator(const CGeoPoint<double> &first, const CGeoPoint<double> &second);

	private:
		//
		double m_probability;
		//
		CGeoPoint<double> m_hintPos;
		//
		MaturityVector m_maturities;
		//
		const static int MAXINDICATORS = 8;
		char *m_indicators[MAXINDICATORS+1];
	};
}

#endif