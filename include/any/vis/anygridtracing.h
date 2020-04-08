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
#ifndef __ANYVIS_CONTOUR_GRID_TRACING_H__
#define __ANYVIS_CONTOUR_GRID_TRACING_H__

// refer to macro
#include "anyvis.h"

// refer to parent
#include "anycontourtracingstrategy.h"

// refer to coordinate
#include "any/base/anygeom.h"
#include "any/base/anymediator.h"
using namespace AnyBase;

// refer to kriging
#include "any/math/anykriging.h"

// refer to distribution type
#include "any/math/anydistributionstrategy.h"
using namespace AnyMath;

#include "any/cgal/anydelunary.h"
using namespace AnyCGAL;

#include "any/math/anycokrigsimulator.h"
using namespace AnyMath;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyGridTracing : public CAnyContourTracingStrategy
	{
	private:
		struct IDWThreadParameter
		{
			int m_from;
			int m_to;

			int m_recNumber;
			CGeoPoint<double> *m_recs;
			int m_leastn;
			int m_foundn;

			//CGeoPoint<double> *m_leastpts;
			//int m_polys;
			int m_n;
			int m_direction;

			//double **m_a;
			//double *m_b;
			//double *m_c;
			//double *m_d;

			IDWThreadParameter() : m_from(0), m_to(0), /*m_a(0), m_b(0), m_c(0), m_d(0),m_leastpts(0),*/ \
				m_recs(0), m_recNumber(0), m_leastn(0), m_foundn(0)/*, m_polys(0)*/,m_n(0),m_direction(1)
			{
			}
		};
		void IDWThreadFunc(IDWThreadParameter &parameter);

	public:
		// kinds of weighting mechanism
		enum WeightingMethod
		{
			// Directly set grid points
			WM_Direct,
			// Inverse Distance Weighting
			WM_IDW,
			// Delaunay Triangulation
			WM_Delaunay,
			// Kriging
			WM_Ordinary_Kriging,
			// Kriging
			WM_Universal_Kriging,
			//cokriging
			WM_Co_Kriging,

			//2016/12/5: color
			WM_Color,

			//2019/5/27: scatter mode
			WM_Scatter,
		};
	protected:
		/*!
		*
		**/
		struct TracingInfo
		{
			int m_prevrow;
			int m_prevcol;
			int m_currow;
			int m_curcol;
			int m_nextrow;
			int m_nextcol;

			// vertical or horizontal position along two grid points
			double m_preva;
			double m_prevb;
			double m_cura;
			double m_curb;
			double m_nexta;
			double m_nextb;

			/*!
			*
			**/
			TracingInfo() 
				: m_prevrow(0.),
				m_prevcol(0.),
				m_currow(0.), 
				m_curcol(0.),
				m_nextrow(0.),
				m_nextcol(0.),
				m_preva(0.),
				m_prevb(0.),
				m_cura(0.),
				m_curb(0.),
				m_nexta(0.),
				m_nextb(0.)
			{
			}

			/*!
			*
			**/
			const TracingInfo &operator=(const TracingInfo &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_prevrow = other.m_prevrow;
				m_prevcol = other.m_prevcol;
				m_currow = other.m_currow;
				m_curcol = other.m_curcol;
				m_nextrow = other.m_nextrow;
				m_nextcol = other.m_nextcol;

				m_preva = other.m_preva;
				m_prevb = other.m_prevb;
				m_cura = other.m_cura;
				m_curb = other.m_curb;
				m_nexta = other.m_nexta;
				m_nextb = other.m_nextb;

				return *this;
			}
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGridTracing(CAnyContour *contour, short wType = WM_Universal_Kriging);

		/*!
		*
		**/
		~CAnyGridTracing();

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetWeightingType(short wType)
		{
			m_wType = wType;
		}

		/*!
		*
		**/
		short GetWeightingType() const
		{
			return m_wType;
		}

		//
		//
		//
		/*!
		*
		**/
		void Tessellate(int rows, int cols, CGeoRect<double> &extent, const CGeoRect<double> &newExtent = CGeoRect<double>());

		/*!
		*
		**/
		void TraceLine();

		//
		// fetch tesslated units
		/*!
		*
		**/
		void GetControlInfo(int &rows, int &cols);

		/*!
		*
		**/
		const CGeoPoint<double> &GetControlPoint(int row, int col);

		/*!
		*
		**/
		void GetControlGrid(const CGeoPoint<double> &pt, int &lbRow, int &lbCol);

		//
		//
		//
		/*!
		* 
 		**/
		bool MoveFirst(CGeoPoint<double> *pts, bool &isbordergrid);

		/*!
		*
		**/
		bool MoveNext(CGeoPoint<double> *pts, bool &isbordergrid);

		/*!
		*
		**/
		CGeoPoint<double> GetValue(int row, int col);

		//
		//
		//
		/*!
		*
		**/
		CGeoPoint<double> *MakeRasterization(const CGeoRect<double> &extent, const string &field, int rows, int cols);

		//
		//2017/9/25: cross validation
		//
		/*!
		*
		**/
		void CrossValidation(std::vector<CGeoPoint<double> > &result_pts, CAnyFunctor &progress);

		void SetBlankAreaNANValue(std::vector<std::vector<CGeoPoint<double>> > &blanks, bool isTempBlank=true, bool isNAN=true, double customvalue=ANY_NAN);

		void SetCustomZValue();

		/*!
		*2019/3/29: make the function as public 
		**/
		static CGeoPoint<double> * InterpolationLinearFilter(int incol, int inrow, CGeoPoint<double> *inpts, int outcol, int outrow, const CGeoRect<double> &outextent);

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoInverseDistanceWeighting(const CGeoPoint<double> *recs, int recNumber);
		void DoInverseDistanceWeighting_Threaded(const CGeoPoint<double> *recs, int recNumber);

		/*!
		*
		**/
		void DoKrigingWeighting(const CGeoPoint<double> *recs, int recNumber, CGeoPoint<double> *cokrigingrecs=0, int cokrigingrecNumber=0);

		//
		//
		//
		/*!
		* along four directions to trace the open lines
		**/
		void DoTraceOpenLine(double zvalue, TracingInfo &curInfo, unsigned char direction);

		/*!
		*
		**/
		void DoTraceCloseLine(double zvalue);

		/*!
		* find the next next grid
		**/
		bool DoTraceAlongDirection(TracingInfo &curInfo);

		/*!
		* find the next next grid
		**/
		bool DoSetNextGrid(TracingInfo &curInfo, int nextcol, int nextrow, unsigned char direction);

		/*!
		*
		**/
		void DoExtractContourLine(double zvalue, int ptNumber, bool isOpen = true);

		/*!
		*
		**/
		bool IsValidGridIndex(long gridIndex);

		/*!
		*
		**/
		double DoSimpleInterpolation(const CGeoRect<double> &extent);

		//
		//2016/10/28
		//
		/*!
		*
		**/
		static int ComparePointValue(const void *a, const void *b);
		
		/*!
		*sample interpolation
		**/
		CGeoPoint<double> * InterpolationLinear(int incol, int inrow, CGeoPoint<double> *inpts, int outcol, int outrow, const CGeoRect<double> &outextent);

		/*!
		*2018/1/11: another sample interpolation 
		**/
		//CGeoPoint<double> * InterpolationLinearFilter(int incol, int inrow, CGeoPoint<double> *inpts, int outcol, int outrow, const CGeoRect<double> &outextent);

		/*!
		*
		**/
		void EraseSimliarPoints(int recNumber, const CGeoPoint<double> *recs, std::vector<CGeoPoint<double>> &resultSamples);

		//
		//2017/9/25: cross validation
		//
		/*!
		*
		**/
		bool CrossValidation_Kriging(const CGeoPoint<double> *recs, int recNumber,CGeoPoint<double> *cokrigingrecs, int cokrigingrecNumber, CGeoPoint<double> &result_pt);

		/*!
		*
		**/
		bool CrossValidation_IDW(const CGeoPoint<double> *recs, int recNumber, CGeoPoint<double> &result_pt);

		//
		//2017/9/26: normal distribution scoring transform
		//
		/*!
		*
		**/
		static bool CompareSampleValue(const CGeoPoint<double> &x1, const CGeoPoint<double> &x2);

		/*!
		*
		**/
		double DoNormal2Sample(double normalvalue);

	public:
		// kriging method
		CAnyKriging m_kriging;

		//2019/7/12: build a krig simulator
		CAnyKrigSimulator *m_krig_simulator;

		//2017/11/20: build a simulator
		CAnyKrigSimulator *m_other_krig_simulator;

		//2016/11/29: get those variables in other class
		long m_rows;
		long m_cols;
		double m_xmin;
		double m_ymin;
		double m_xgridwidth;
		double m_ygridwidth;

		//2015/8/25:check pts in CAnyContour
		CGeoPoint<double> *m_pts;
		//2018/11/21:original zvalue of grid points
		CGeoPoint<double> *m_pts_original;
		//sample index: 10*10 grid
		std::vector<std::vector<int> > m_sampleIndex;
		double m_indexgridX;
		double m_indexgridY;
		int m_indexgridnumX;
		int m_indexgridnumY;

	private:
		// weighting method
		short m_wType;

		// gridnable points
		//long m_rows;
		//long m_cols;
		//CGeoPoint<double> *m_pts;

		// loop grids
		long m_currow;
		long m_curcol;

		//
		//double m_xmin;
		//double m_ymin;
		//double m_xgridwidth;
		//double m_ygridwidth;

		// direction spans for tracing
		double *m_hspans;
		double *m_vspans;
		double *m_vpos;
		double *m_hpos;

		//2016/11/7: delunary method
		CAnyDelunary m_delunary;

		//
		int m_taskcount;
		void *m_scheduler;

		//2017/9/26: normal distribution scoring transform
		CAnyDistributionStrategy *m_normaldistribution;
		std::vector<double> m_normal_fractiles;
		std::vector<CGeoPoint<double> > m_samples;
	};
}

#endif