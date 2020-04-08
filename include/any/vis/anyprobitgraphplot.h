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
#ifndef __ANYVIS_PROBIT_MODEL_H__
#define __ANYVIS_PROBIT_MODEL_H__

// refer to macro
#include "anyvis.h"

// refer to distribution type
#include "any/math/anydistributionstrategy.h"
using namespace AnyMath;

// refer to view hook
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to axis parent
#include "anyaxises.h"

// refer to geometry basic
#include "any/base/anygeom.h"
using namespace AnyBase;

namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyProbitGraphPlot : public CAnyViewHook, private CAnyAxises
	{
	public:
		// sample vector
		typedef std::vector<CGeoPoint<double> > SampleVector;

		typedef std::map<string, CAnyDistributionStrategy*> DistributionMap;

		// added by haining 2013-03-27
		/*!
		*
		**/
		enum CurveType
		{
			CT_PDF					=	1,
			CT_CDF					=	1 << 1,
			CT_COMPLEMENT	=	1 << 2,
			CT_LOG					=	1 << 3,
			CT_TRUNCATION	=	1 << 4,
			CT_HISTOGRAM		=	1 << 5,
			CT_CURSOR			= 1 << 6,			
		};

		/*!
		*
		**/
		enum PlotingPositionMode
		{
			PPM_Unknown,
			PPM_Midpoint,
			PPM_Fractile,
			PPM_Max
		};

	public:

		/*!
		*
		**/
		CAnyProbitGraphPlot(CAnyView &curView,bool isMultiple = false);

		/*!
		*
		**/
		~CAnyProbitGraphPlot();

	public:
		
		//
		//
		//
		void Clone(const CAnyViewHook *prototype);

		/*!
		* if there is any sample, u can directly set 
		**/
		void SetLognormal(double max, double min);

		/*!
		* for get quantiles or current distribution parameter
		**/
		CAnyDistributionStrategy *GetLognormal();

		/*!
		* for get current distribution (haining, 2013-3-27)
		**/
		CAnyDistributionStrategy *GetDistribution();
		
		/*!
		* as far, it only render one group of samples
		**/
		void SetLognormal(const SampleVector &samples, short mode, bool isNormalized);

		/*!
		* 
		**/
		void SetLognormal(const CAnyDistributionStrategy::DistributionParameters &parameter);

		/*!
		* except for the default lognormal, it also support other distributions
		**/
		void RenderDistribution(const string &name, CAnyDistributionStrategy::DistributionParameters &parameter, int color);

		/*!
		*
		**/
		bool SetDistribution(const string &name, CAnyDistributionStrategy::DistributionParameters &parameters);

		/*!
		*
		**/
		bool SetMapExtent(CGeoRect<double> &mapExtent);

		/*!
		*
		**/
		bool GetMapExtent(CGeoRect<double> &mapExtent);
		
		/*!
		*
		**/
		const CAnyDistributionStrategy::DistributionStatistics GetStatistics();

		/*!
		*
		**/
		double GetQuantile(double probability);

		/*!
		*
		**/
		void SetSamples(CGeoPoint<double> *samples, int number, bool isNormalized);

		/*!
		*
		**/
		SampleVector GetSamples();

		/*!
		*
		**/
		void EraseDistribution(const string &name);

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
		//multiple curve mode
		//
		/*!
		*
		**/
		void AddDistribution(const std::string &name, CAnyDistributionStrategy *distribution);
		
		/*!
		*
		**/
		double GetQuantile(const std::string &name, double probability);
		
		//
		//
		//
		/*!
		*
		**/
		inline void ShowLogNormal(bool isShown = true);

		/*!
		*
		**/
		inline void HideLogNormal(bool isHiden = true);

		/*!
		*
		**/
		inline void SetLognormalColor(unsigned int color);
	private:
		//
		//
		//
		/*!
		* render axises
		**/
		void DoRenderGraphPlot(CAnyCanvas &canvas);

		/*!
		* render samples
		**/
		void DoRenderSamples(CAnyCanvas &canvas);

		/*!
		* render samples
		**/
		void DoRenderDistributions(CAnyCanvas &canvas);

		/*!
		* directly get quantile or factile using samples ordered
		**/
		double DoGetPlottingPosition(int rank, short type = PPM_Fractile);

		/*!
		*
		**/
		static bool CompareSampleValue(const CGeoPoint<double> &first, const CGeoPoint<double> &second);

		//
		//
		//
		/*!
		*
		**/
		void Release();

		/*!
		*
		**/
		void Release(CAnyDistributionStrategy * &distribution);

		/*!
		*
		**/
		void GetLimitation(double &minX, double &maxX);
	private:
		// lognormal accumulation line
		// 0 -  start(right:p90), 1 - end(right:p10)
		CGeoPoint<double> m_pts[2];

		// ploting position mode
		short m_mode;

		// for x axis
		SampleVector m_samples;
		//CGeoPoint<double> *m_samples;

		// for y axis using standard normal distribution
		CAnyDistributionStrategy *m_normal;

		// for default lognormal
		CAnyDistributionStrategy *m_lognormal;

		// for current distribution (haining,2013-03-27)
		CAnyDistributionStrategy *m_distribution;

		// other distribution 
		DistributionMap m_others;

		// added by haining, 2013-03-27
		CGeoRect<double> m_mapExtent;

		// sample space
		int m_number;

		//
		bool m_isMultiple;

		////whether to show log normal curve
		//bool m_isLogNormalShown;

		//bool m_isLogNormalHiden;

		unsigned int m_logNormalColor;

	public:
		//whether to show log normal curve
		bool m_isLogNormalShown;

		bool m_isLogNormalHiden;
	};
}
#endif