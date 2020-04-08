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
#ifndef __ANYVIS_PROBABILITY_DISTRIBUTION_H__
#define __ANYVIS_PROBABILITY_DISTRIBUTION_H__

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

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyProbabilityDistribution : public CAnyViewHook, private CAnyAxises
	{
	public:
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
			CT_STATISTICS			= 1 << 7,	
			CT_CDF_LOG			= 1 << 8,//2019/3/27: add 'log_cdf' mode
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyProbabilityDistribution(CAnyView &curView);

		/*!
		*
		**/
		~CAnyProbabilityDistribution();

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
		bool SetDistribution(const string &name, CAnyDistributionStrategy::DistributionParameters &parameters);

		/*!
		*
		**/
		CAnyDistributionStrategy *GetDistribution() const;

		/*!
		*
		**/
		void Release();

		/*!
		*
		**/
		void SetSamples(CGeoPoint<double> *samples, int number);

		/*!
		*
		**/
		double GetSampleSize();

		/*!
		*
		**/
		string GetDistributionName();

		/*!
		*
		**/
		void SetFractileCursor(const CGeoPoint<double> &cursor);

		//
		//
		//
		/*!
		*
		**/
		void SetCurveType(unsigned short types);

		/*!
		*
		**/
		unsigned short GetCurveType();

		/*!
		*
		**/
		unsigned int GetParaType();

		/*!
		*
		**/
		const CAnyDistributionStrategy::DistributionParameters GetParameters();

		/*!
		*
		**/
		const CAnyDistributionStrategy::DistributionStatistics GetStatistics();

		/*!
		*
		**/
		double GetMean();

		/*!
		*
		**/
		double GetSD();

		/*!
		*
		**/
		double GetQuantile(double probability);

		//
		//2018/7/23: new functions
		//
		/*!
		*
		**/
		void SetTitles(const std::string &x_title, const std::string &y_title);

		/*!
		*
		**/
		void SetRenderedMinQuantile(double quantile = 0.01);

		/*!
		*
		**/
		void SetAxisInteger(bool is_x_integer = false, bool is_y_integer = false);

		/*!
		*2019/5/29: custom extent
		**/
		void SetCustomExtent(const CGeoRect<double> &extent);

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

	private:
		//
		//
		//
		/*!
		*
		**/
		int DoPickFractiles(const CGeoPoint<double> &pickPt);

		/*!
		*
		**/
		void DoRenderPDF(CAnyCanvas &canvas, const CGeoRect<double> &mapExtent);

		/*!
		*
		**/
		void DoRenderCDF(CAnyCanvas &canvas, const CGeoRect<double> &mapExtent);

		/*!
		*
		**/
		void DoRenderComplement(CAnyCanvas &canvas, const CGeoRect<double> &mapExtent);

		/*!
		*
		**/
		void DoRenderHistogram(CAnyCanvas &canvas, const CGeoRect<double> &mapExtent);

		/*!
		*
		**/
		void DoRenderStatisitcs(CAnyCanvas &canvas, const CGeoRect<double> &mapExtent);

		/*!
		*
		**/
		void DoRenderFractileCursor(CAnyCanvas &canvas);
		
		/*!
		*
		**/
		void DoRenderLogCDF(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderLogCDFLine(CAnyCanvas &canvas,  std::vector<CGeoPoint<double> > &mapPts, CAnyDistributionStrategy *normal_distribution);

		/*!
		*
		**/
		void GetPDFMaxY(CGeoRect<double> &mapExtent);

	private:
		// sample space
		CGeoPoint<double> *m_samples;
		int m_number;

		// distribution setting
		unsigned short m_curveType;
		CAnyDistributionStrategy *m_distribution;

		// discrete number for pdf, cdf etc curve
		int m_divisions;

		// cursor line corresponding to key fractiles
		CGeoPoint<double> m_cursor;

		// key fractiles in screen point for "user" distribution
	    //  "p100","p75", "p50", "p25","p0"
		CGeoPoint<double> m_fractiles[5];
		short m_pickOrder;

		bool m_isLog;
		double m_maxy;

	private:

		//2018/7/23: titles
		std::string m_x_title;
		std::string m_y_title;
	
		//default min quantile is 0.01
		//and then calculate the related x value
		double m_min_quantile;

		bool m_is_x_integer;
		bool m_is_y_integer;

		//2019/5/29: custom extent
		CGeoRect<double> m_extent_custom;

		//2019/6/17: max y of the pdf
		CGeoPoint<double> m_scrpt_maxy_pdf;
	};
}
#endif
