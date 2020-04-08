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
#ifndef __ANYVIS_CONTOUR_H__
#define __ANYVIS_CONTOUR_H__

// refer to macro
#include "anyvis.h"

// refer to parent
#include "anyaxises.h"

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

//2015/5/27
#include "any/thread/jtc.h"

//
namespace AnyVis
{
	// forward class
	class CAnyContourTracingStrategy;
	class CAnyContourSurfaceStrategy;

	/*!
	*
	**/
	class ANYVIS_CLASS CAnyContour  : public CAnyViewHook, private CAnyAxises
	{
		// relatives
		friend class CAnyContourTracingStrategy;
		friend class CAnyGridTracing;
		friend class CAnyContourSurfaceStrategy;
		friend class CAnyTINTracing;
	public:
		/*!
		*
		**/
		enum ContourTracingStrategy
		{
			CTS_Unknown = -1,
			CTS_Grid,
			CTS_Delaunay,
			CTS_Max
		};

		/*!
		*
		**/
		enum ContourRenderingStyle
		{
			CRS_Contour_Line			= 1,
			CRS_Contour_Filling			= 1 << 1,
			CRS_Surface_Grid			= 1 << 2,
			CRS_Surface_Filling			= 1 << 3,
			CRS_Sample_Value			= 1 << 4,		// render sample value
			CRS_Sample_Grid				= 1 << 5,		// render interpolated grid and corresponding value
			CRS_Sample_Color_By_Value	= 1 << 6,		//2015/8/10, assign sample color by sample value
			CRS_Grid_Value_W			= 1 << 7,		//2018/4/25: render contour by w value(not z)
		};

		/*!
		*
		**/
		struct ContourColor
		{
			//
			unsigned char m_r;
			unsigned char m_g;
			unsigned char m_b;
			unsigned char m_a; // alpha

			/*!
			*
			**/
			ContourColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0) : m_r(r), m_g(g), m_b(b), m_a(a)
			{
			}

			/*!
			*
			**/
			const ContourColor &operator=(const ContourColor &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_r = other.m_r;
				m_g = other.m_g;
				m_b = other.m_b;
				m_a = other.m_a;

				return *this;
			}
		};

		struct KrigingPara
		{
			int m_krigingType;
			int m_kernelType;
			int m_universalType;
			double m_nugget;
			double m_sill;
			double m_range;
			double m_nuggetA;
			double m_sillA;
			double m_rangeA;
			double m_nuggetB;
			double m_sillB;
			double m_rangeB;
			double m_nuggetAB;
			double m_sillAB;
			double m_rangeAB;
			bool m_isNeighbor;
			bool m_isAutoEstimatePara;
			int m_neighborNum;
			bool m_isAnisotropy;
			double m_AnisotropyScale;
			double m_AnisotropyAngle;
			int m_lag;

			//2016/11/7:set default value of 'm_isNeighbor' from 'false' to 'true'
			KrigingPara():m_krigingType(0),m_kernelType(0),m_universalType(0),m_nugget(0.),m_sill(1.),m_range(1.),\
				m_nuggetA(0.),m_sillA(0.),m_rangeA(0.),m_nuggetB(0.),m_sillB(0.),m_rangeB(0.),m_nuggetAB(0.),m_sillAB(0.),m_rangeAB(0.),\
				m_isNeighbor(true),m_neighborNum(100),m_isAnisotropy(false),m_AnisotropyScale(1.),m_AnisotropyAngle(0.),m_isAutoEstimatePara(true),m_lag(20)
			{
				
			}

			KrigingPara(const KrigingPara &other)
			{
				m_krigingType = other.m_krigingType;
				m_kernelType = other.m_kernelType;
				m_universalType = other.m_universalType;
				m_nugget = other.m_nugget;
				m_sill = other.m_sill;
				m_range = other.m_range;
				m_nuggetA = other.m_nuggetA;
				m_sillA = other.m_sillA;
				m_rangeA = other.m_rangeA;
				m_nuggetB = other.m_nuggetB;
				m_sillB = other.m_sillB;
				m_rangeB = other.m_rangeB;
				m_nuggetAB = other.m_nuggetAB;
				m_sillAB = other.m_sillAB;
				m_rangeAB = other.m_rangeAB;
				m_isNeighbor = other.m_isNeighbor;
				m_neighborNum = other.m_neighborNum;
				m_isAnisotropy = other.m_isAnisotropy;
				m_AnisotropyScale = other.m_AnisotropyScale;
				m_AnisotropyAngle = other.m_AnisotropyAngle;
				m_isAutoEstimatePara=other.m_isAutoEstimatePara;
				m_lag=other.m_lag;
			}

			/*!
			*
			**/
			const KrigingPara &operator=(const KrigingPara &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_krigingType = other.m_krigingType;
				m_kernelType = other.m_kernelType;
				m_universalType = other.m_universalType;
				m_nugget = other.m_nugget;
				m_sill = other.m_sill;
				m_range = other.m_range;
				m_nuggetA = other.m_nuggetA;
				m_sillA = other.m_sillA;
				m_rangeA = other.m_rangeA;
				m_nuggetB = other.m_nuggetB;
				m_sillB = other.m_sillB;
				m_rangeB = other.m_rangeB;
				m_nuggetAB = other.m_nuggetAB;
				m_sillAB = other.m_sillAB;
				m_rangeAB = other.m_rangeAB;
				m_isNeighbor = other.m_isNeighbor;
				m_neighborNum = other.m_neighborNum;
				m_isAnisotropy = other.m_isAnisotropy;
				m_AnisotropyScale = other.m_AnisotropyScale;
				m_AnisotropyAngle = other.m_AnisotropyAngle;
				m_isAutoEstimatePara=other.m_isAutoEstimatePara;
				m_lag=other.m_lag;
				return *this;
			}

			/*!
			*2015/10/22: check whether the parameter is same?
			**/
			bool IsKrigingParaSame(const KrigingPara &other)
			{
				if (m_krigingType == other.m_krigingType && m_kernelType == other.m_kernelType && m_universalType == other.m_universalType && m_nugget == other.m_nugget &&\
					m_sill == other.m_sill && m_range == other.m_range && m_nuggetA == other.m_nuggetA && m_sillA == other.m_sillA &&\
					m_rangeA == other.m_rangeA && m_nuggetB == other.m_nuggetB && m_sillB == other.m_sillB && m_rangeB == other.m_rangeB &&\
					m_nuggetAB == other.m_nuggetAB && m_sillAB == other.m_sillAB && m_rangeAB == other.m_rangeAB && m_isNeighbor == other.m_isNeighbor &&\
					m_neighborNum == other.m_neighborNum && m_isAnisotropy == other.m_isAnisotropy && m_AnisotropyScale == other.m_AnisotropyScale && m_AnisotropyAngle == other.m_AnisotropyAngle &&\
					m_isAutoEstimatePara == other.m_isAutoEstimatePara && m_lag == other.m_lag)
				{
					return true;
				}

				return false;
			}
		};

		typedef std::map<double,double> SampleAttrMap;
		typedef SampleAttrMap::iterator sam_itr;
		typedef SampleAttrMap::const_iterator sam_citr;

		//2015/1/20:customized contour line settings
		typedef std::map<long,bool> CountourLineStatusMap;//<0,false>
		
		struct LineStatus
		{
			AnyMap::LineStyle m_lineStyle;
			AnyMap::LabelStyle m_labelStyle;
			bool m_isShown;

			const LineStatus &operator=(const LineStatus &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_isShown = other.m_isShown;
				m_lineStyle = other.m_lineStyle;

				return *this;
			}
		};
		typedef std::map<long,LineStatus> CountourLineStyleMap;//<0,linestyle>
		
		/*!
		*
		**/
		struct ContourSetting
		{
			// tracing strategy
			int m_tracingType;

			// rendering style
			unsigned int m_style;
			
			// contour interval
			double m_interval;

			//contour line smooth strategy
			int m_smoothType;
			// interpolated points for one contour line
			double m_interNumber; 
			// interval of control points for one contour line
			int m_controlpointInterval;

			// rows
			double m_rows;
			// cols
			double m_cols;
			// min x
			double m_xMin;
			// max x
			double m_xMax;
			// min y
			double m_yMin;
			// max y
			double m_yMax;
			// min z
			double m_zMin;
			// max z
			double m_zMax;

			//customized z min and max
			bool m_isZValueCustom;
			double m_zCustomMin;
			double m_zCustomMax;

			// color setting: three-color controlling
			ContourColor m_cMin;
			ContourColor m_cMid;
			ContourColor m_cMax;

			// which line should be tagged as zvalue
			int m_tIsolations;

			//tagged line
			LineStyle m_taggedLineStyle;
			LabelStyle m_taggedLabelStyle;
			int m_taggedLinePattern;
			bool m_isTaggedLineLabelShown;
			
			//other line
			LineStyle m_otherLineStyle;
			LabelStyle m_otherLabelStyle;
			int m_otherLinePattern;
			bool m_isOtherLineLabelShown;

			// scene recovery
			// file path or name and column setting
			string m_source;
			int m_xColumn;
			int m_yColumn;
			int m_zColumn;

			//2014/11/25
			int m_z1Column;
			
			//camera angels
			double m_angleX;
			double m_angleY;
			double m_angleZ;

			//sample symbol settings
			bool m_isSymbolLabelShown;
			int m_symbolStyle;
			int m_symbolColor;
			double m_symbolSize;
			double m_symbolLabelSize;

			//grid label status
			bool m_isGridLabelShown;
			int m_gridLabelColor;
			double m_gridLabelSize;

			//color scale label
			bool m_isColorScaleLabelShown;
			int m_colorScaleLabelCount;
			int m_colorScaleLabelColor;
			double m_colorScaleLabelSize;

			//2014.8.14
			bool m_isColorScaleLabelInteger;

			//kriging
			KrigingPara m_kriPara;
			
			// weight type
			short m_weightType;

			// group attributes of samples(m_pts)
			bool m_isGroupMode;
			std::vector<int> m_groupColors;
			SampleAttrMap m_symbolColorMap;
			SampleAttrMap m_symbolStyleMap;
			SampleAttrMap m_symbolSizeMap;
			SampleAttrMap m_symbolLabelMap;
			SampleAttrMap m_symbolLabelShownMap;
			SampleAttrMap m_symbolLabelSizeMap;
			
			//2014/11/25
			int m_groupColumn;

			//2015/9/2: times * pt.m_x...
			double m_xTimes;
			double m_yTimes;
			double m_zTimes;

			//2015/9/14: inverse distance weighting setting
			int m_leastn; // at least n points take into consideration
			int m_foundn; // founded number
			int m_npoly;//power of polynome
			int m_directionn;//

			//2016/7/13: used to get rid of similar points
			double m_distance;

			//2016/7/15: decimal digit of label
			int m_decimalDigit;

			//2016/10/9: units
			std::string m_xUnit;
			std::string m_yUnit;
			std::string m_zUnit;
						
			//2016/10/9: multiple thread
			bool m_isMTPainted;

			//2016/10/9: whether to handle crossed line
			bool m_hanldeCrossedLine;

			//2016/10/9
			double m_rowDistance;
			double m_colDistance;

			//2016/10/9: contour line settings, to save the attributes
			CountourLineStatusMap m_lineStatusMap;
			CountourLineStyleMap m_lineStyleMap;
			CountourLineStyleMap m_labelStyleMap;

			//2016/10/28: customized extent
			CGeoRect<double> m_customExtent;
			
			//2016/11/18: save blank area
			std::vector<std::vector<CGeoPoint<double>> > m_blanks;
			//non-blank area
			std::vector<std::vector<CGeoPoint<double>> > m_nonblanks;
			//NAN Value area
			std::vector<std::vector<CGeoPoint<double>> > m_NANValueArea;
			//NAN Value area borders
			std::vector<std::vector<CGeoPoint<double>> > m_NANValueArea_borders;
			//valid area(opposit of NAN value area)
			std::vector<std::vector<CGeoPoint<double>> > m_validArea;
			//final painted area(intersection of valid&nonblank area)
			std::vector<std::vector<CGeoPoint<double>> > m_paintedArea;

			//2016/11/29: save interpolation pts
			CGeoPoint<double> *m_pts;
			CGeoPoint<double> *m_pts_original;
			
			//2016/12/30: row/col tick number
			int m_rowTickNumber;
			int m_colTickNumber;

			//2017/2/24: backup of the following variables
			double m_bkRows;
			double m_bkCols;
			short m_bkWeightType;

			//2017/9/22: backup of m_isGroupMode
			int m_bk_is_group_mode;

			//2017/9/26: normal distribution transform?
			bool m_is_normal_distribution_transform;

			//2017/11/16: is semi-variogram?
			bool m_is_semi_variogram;

			//2018/2/26: customized tick lags, 10,20,50...
			double m_x_tick_lags;
			double m_y_tick_lags;

			//2018/3/6: save picked areas
			std::vector<std::vector<CGeoPoint<double>> > m_picked_areas;

			//2018/12/21: save cut area borders
			std::vector<std::vector<CGeoPoint<double>> > m_picked_areas_borders;

			//2018/4/25: store min/max of grid w value 
			double m_wMin;
			double m_wMax;

			//2018/12/19: color range against color
			double m_zvalue_range_min;
			double m_zvalue_range_mid;
			double m_zvalue_range_max;

			/*!
			*
			**/
			ContourSetting() : m_tracingType(CTS_Grid), m_style(CRS_Contour_Line | CRS_Contour_Filling /*| CRS_Surface_Grid | CRS_Surface_Filling*/)
				, m_interval(10.), m_smoothType(0),m_controlpointInterval(1),m_interNumber(20.), m_rows(10.), m_cols(10.), m_cMin(0, 255, 0)/*(255, 0, 0)*/, m_cMid(255, 255, 0), m_cMax(255, 0, 0)/*(0, 255, 0)*/, m_tIsolations(5)
				, m_xMin(ANY_NAN), m_xMax(ANY_NAN), m_yMin(ANY_NAN), m_yMax(ANY_NAN), m_zMin(ANY_NAN), m_zMax(ANY_NAN), \
				m_source(""), m_xColumn(0), m_yColumn(0), m_zColumn(0),
				m_taggedLinePattern(0),m_otherLinePattern(0),m_isOtherLineLabelShown(false),m_isTaggedLineLabelShown(true),
				m_angleX(0.),m_angleY(0.),m_angleZ(0.),m_zCustomMin(-1.),m_zCustomMax(-1.),m_isZValueCustom(false),\
				m_symbolStyle(0),m_symbolColor(0),m_symbolSize(2.),m_isSymbolLabelShown(false),m_symbolLabelSize(8.),
				m_isGridLabelShown(false),m_gridLabelColor(0),m_gridLabelSize(5.),\
				m_isColorScaleLabelShown(true),m_colorScaleLabelCount(6),m_colorScaleLabelColor(0),m_colorScaleLabelSize(7.),\
				m_weightType(3/*CAnyGridTracing::WM_Ordinary_Kriging*/),m_isGroupMode(false),m_isColorScaleLabelInteger(false),\
				m_z1Column(-1),m_groupColumn(-1),m_xTimes(1.),m_yTimes(1.),m_zTimes(1.),m_leastn(4),m_foundn(1024),m_npoly(0),m_directionn(0),m_distance(0.0000001),m_decimalDigit(2),\
				m_xUnit(""),m_yUnit(""),m_zUnit(""),m_isMTPainted(false),m_hanldeCrossedLine(false),m_rowDistance(1.), m_colDistance(1.),m_pts(0),m_pts_original(0),m_rowTickNumber(5),m_colTickNumber(5),\
				m_bkRows(-1.),m_bkCols(-1.),m_bkWeightType(-1),m_bk_is_group_mode(-1),m_is_normal_distribution_transform(false),m_is_semi_variogram(false),\
				m_x_tick_lags(0.),m_y_tick_lags(0.),m_wMin(ANY_NAN), m_wMax(ANY_NAN), m_zvalue_range_min(ANY_NAN), m_zvalue_range_mid(ANY_NAN), m_zvalue_range_max(ANY_NAN)
			{
				//
				m_taggedLineStyle.m_width = 2;
			}

			/*!
			*
			**/
			~ContourSetting()
			{
				//Release();			
			}

			/*!
			*
			**/
			const ContourSetting &operator=(const ContourSetting &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_tracingType = other.m_tracingType;
				m_style = other.m_style;

				m_interval = other.m_interval;
				m_smoothType=other.m_smoothType;
				m_interNumber = other.m_interNumber;
				m_controlpointInterval=other.m_controlpointInterval;

				m_rows = other.m_rows;
				m_cols = other.m_cols;
				m_xMin = other.m_xMin;
				m_xMax = other.m_xMax;
				m_yMin = other.m_yMin;
				m_yMax = other.m_yMax;
				m_zMin = other.m_zMin;
				m_zMax = other.m_zMax;
				m_cMin = other.m_cMin;
				m_cMid = other.m_cMid;
				m_cMax = other.m_cMax;
				m_tIsolations = other.m_tIsolations;

				//
				m_taggedLineStyle = other.m_taggedLineStyle;
				m_taggedLinePattern = other.m_taggedLinePattern;
				m_taggedLabelStyle = other.m_taggedLabelStyle;
				m_isTaggedLineLabelShown = other.m_isTaggedLineLabelShown;

				//
				m_otherLineStyle = other.m_otherLineStyle;
				m_otherLinePattern = other.m_otherLinePattern;
				m_otherLabelStyle = other.m_otherLabelStyle;
				m_isOtherLineLabelShown = other.m_isOtherLineLabelShown;

				//
				m_source = other.m_source;
				m_xColumn = other.m_xColumn;
				m_yColumn = other.m_yColumn;
				m_zColumn = other.m_zColumn;

				//
				m_angleX = other.m_angleX;
				m_angleY = other.m_angleY;
				m_angleZ = other.m_angleZ;

				//
				m_isZValueCustom = other.m_isZValueCustom;
				m_zCustomMin = other.m_zCustomMin;
				m_zCustomMax = other.m_zCustomMax;

				//
				m_isSymbolLabelShown = other.m_isSymbolLabelShown;
				m_symbolStyle = other.m_symbolStyle;
				m_symbolColor = other.m_symbolColor;
				m_symbolSize = other.m_symbolSize;
				m_symbolLabelSize = other.m_symbolLabelSize;

				//
				m_isGridLabelShown = other.m_isGridLabelShown;
				m_gridLabelColor = other.m_gridLabelColor;
				m_gridLabelSize = other.m_gridLabelSize;

				//
				m_isColorScaleLabelShown = other.m_isColorScaleLabelShown;
				m_colorScaleLabelCount = other.m_colorScaleLabelCount;
				m_colorScaleLabelColor = other.m_colorScaleLabelColor;
				m_colorScaleLabelSize = other.m_colorScaleLabelSize;
				m_isColorScaleLabelInteger = other.m_isColorScaleLabelInteger;

				//
				m_kriPara = other.m_kriPara;
				m_weightType = other.m_weightType;

				//
				m_isGroupMode = other.m_isGroupMode;
				m_groupColors = other.m_groupColors;
				
				m_symbolColorMap = other.m_symbolColorMap;
				m_symbolStyleMap = other.m_symbolStyleMap;
				m_symbolSizeMap = other.m_symbolSizeMap;
				m_symbolLabelMap = other.m_symbolLabelMap;
				m_symbolLabelShownMap = other.m_symbolLabelShownMap;
				m_symbolLabelSizeMap = other.m_symbolLabelSizeMap;

				//
				m_z1Column = other.m_z1Column;
				m_groupColumn = other.m_groupColumn;

				//
				m_xTimes = other.m_xTimes;
				m_yTimes = other.m_yTimes;
				m_zTimes = other.m_zTimes;

				//
				m_leastn = other.m_leastn;
				m_foundn = other.m_foundn;
				m_npoly = other.m_npoly;
				m_directionn=other.m_directionn;

				//
				m_distance = other.m_distance;
				m_decimalDigit = other.m_decimalDigit;

				//2016/10/9
				m_xUnit = other.m_xUnit;
				m_yUnit = other.m_yUnit;
				m_zUnit = other.m_zUnit;
				
				m_isMTPainted = other.m_isMTPainted;
				m_hanldeCrossedLine = other.m_hanldeCrossedLine;

				m_rowDistance = other.m_rowDistance;
				m_colDistance = other.m_colDistance;

				m_lineStatusMap = other.m_lineStatusMap;
				m_lineStyleMap = other.m_lineStyleMap;
				m_labelStyleMap = other.m_labelStyleMap;

				//
				m_customExtent = other.m_customExtent;

				//
				m_blanks = other.m_blanks;
				m_NANValueArea=other.m_NANValueArea;
				m_NANValueArea_borders=other.m_NANValueArea_borders;
				m_nonblanks=other.m_nonblanks;
				m_validArea=other.m_validArea;
				m_paintedArea=other.m_paintedArea;

				//
				//Release(other.m_pts,other.m_rows, other.m_cols);
				
				//2016/12/30: tick number
				m_rowTickNumber = other.m_rowTickNumber;
				m_colTickNumber = other.m_colTickNumber;
				
				//2017/2/24: backup of the following variables
				m_bkRows = other.m_bkRows;
				m_bkCols = other.m_bkCols;
				m_bkWeightType = other.m_bkWeightType;
				
				//
				m_bk_is_group_mode = other.m_bk_is_group_mode;

				//
				m_is_normal_distribution_transform = other.m_is_normal_distribution_transform;

				//
				m_is_semi_variogram = other.m_is_semi_variogram;

				//2018/2/26: customized tick lags, 10,20,50...
				m_x_tick_lags = other.m_x_tick_lags;
				m_y_tick_lags = other.m_y_tick_lags;

				//2018/3/6: picked areas
				m_picked_areas = other.m_picked_areas;
				m_picked_areas_borders = other.m_picked_areas_borders;

				//2018/4/25: min/ max of w value
				m_wMin = other.m_wMin;
				m_wMax = other.m_wMax;

				//
				m_zvalue_range_min = other.m_zvalue_range_min;
				m_zvalue_range_mid = other.m_zvalue_range_mid;
				m_zvalue_range_max = other.m_zvalue_range_max;

				return *this;
			}

			/*!
			*2016/11/29: release interpolation pts
			**/
			void Release(CGeoPoint<double> *pts = 0, int rows = -1, int cols = -1)
			{
				if(m_pts)
				{
					::free(m_pts);
				}
				m_pts = 0;

				//
				if (pts)
				{
					if (rows == -1)
					{
						rows = m_rows;
					}

					if (cols == -1)
					{
						cols = m_cols;
					}

					int size = rows * cols * sizeof(CGeoPoint<double>);
					m_pts = (CGeoPoint<double> *)::malloc(size);
					::memcpy(m_pts,pts,size);
				}
			}
						
			/*!
			*2016/11/29: release pts_original
			**/
			void ReleaseOriginalPts(CGeoPoint<double> *pts = 0, int rows = -1, int cols = -1)
			{
				if(m_pts_original)
				{
					::free(m_pts_original);
				}
				m_pts_original = 0;

				//
				if (pts)
				{
					if (rows == -1)
					{
						rows = m_rows;
					}

					if (cols == -1)
					{
						cols = m_cols;
					}

					int size = rows * cols * sizeof(CGeoPoint<double>);
					m_pts_original = (CGeoPoint<double> *)::malloc(size);
					::memcpy(m_pts_original,pts,size);
				}
			}
		};

		/*!
		*
		**/
		struct ContourLine
		{
			// z value
			float m_zvalue;

			// color
			unsigned int m_color;

			// bounding
			CGeoRect<double> m_bounding;

			// points
			CGeoPoint<double> *m_pts;
			int m_ptNumber;
						
			/*!
			*
			**/
			ContourLine() : m_zvalue(ANY_NAN), m_ptNumber(0), m_pts(0)
			{
				m_bounding.m_minX = 0x7FFFFFFF;
				m_bounding.m_maxX = -0x7FFFFFFF;
				m_bounding.m_minY = 0x7FFFFFFF;
				m_bounding.m_maxY = -0x7FFFFFFF;
			}

			/*!
			*
			**/
			const ContourLine &operator=(const ContourLine &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_zvalue = other.m_zvalue;
				m_color = other.m_color;
				m_ptNumber = other.m_ptNumber;
				if(m_pts)
				{
					::free(m_pts);
				}
				m_pts = (CGeoPoint<double> *)::malloc(m_ptNumber * sizeof(CGeoPoint<double>));
				::memcpy(m_pts, other.m_pts, m_ptNumber * sizeof(CGeoPoint<double>));
				m_bounding = other.m_bounding;

				return *this;
			}
		};
		//
		typedef std::vector<ContourLine> ContourVector;
		typedef ContourVector::iterator con_itr;
		typedef ContourVector::const_iterator con_citr;
				
		/*!
		*	classical contour operations
		**/
		enum ContourMapOperation
		{
			Contour_MO_Unknown,
			Contour_MO_Blank,
			Contour_MO_Pick,
		};
 
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyContour(CAnyView &curView);

		/*!
		*
		**/
		virtual ~CAnyContour();

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
		void Reset(CGeoPoint<double> *pts, int number, ContourSetting &setting,CGeoPoint<double> *cokrigingPts = 0, int cokrigingNumber = 0, bool isOnlyInterpolation = false,\
			bool isInit = false);

		/*!
		*
		**/
		bool BindPtsWithGroupId();

		/*!
		* 2014/11/26
		**/
		static bool BindPtsWithGroupId(ContourSetting &setting, CGeoPoint<double> *pts, int number);

		/*!
		*
		**/
		CAnyContourTracingStrategy *GetTracingStrategy() const
		{
			assert(m_tracing);
			return m_tracing;
		}

		/*!
		*
		**/
		void ResetContourSetting(const ContourSetting &setting);

		/*!
		*
		**/
		const ContourSetting &GetContourSetting();

		/*!
		*
		**/
		void SetMapOperation(long operation)
		{
			m_operation = operation;
		}

		/*!
		*
		**/
		long GetMapOperation()
		{
			return m_operation;
		}

		/*!
		*
		**/
		void RemoveBlankArea()
		{
			m_setting.m_picked_areas.clear();
			m_setting.m_blanks.clear();
			m_blanks.clear();
		}

		/*!
		*
		**/
		const ContourVector &GetContourVector()
		{
			return m_contours;
		}

		/*!
		*
		**/
		static void SetLinePattern(LineStyle &style, int linePattern);

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
		// override for map algebra
		//
		/*!
		*
		**/
		CGeoPoint<double> *MakeRasterization(const CGeoRect<double> &extent, const string &field, int rows, int cols);

		//
		// spatial analysis for volumetric
		//
		/*!
		*
		**/
		double GetPolygonArea(CGeoPoint<double> *scrPts, int number);

		/*!
		*
		**/
		void ClearPolygonArea();

		/*!
		*
		**/
		bool IsLoatedAtArea(CGeoPoint<double> *mapPts, int number);

		/*!
		*
		**/
		const CGeoPoint<double> *GetData(int &number);

		/*!
		*
		**/
		const CGeoPoint<double> *GetCoKrigingData(int &number);

		/*!
		*
		**/
		const CGeoRect<double> & GetContourMapExtent(bool isPaintExtent = true);

		/*!
		*
		**/
		void SetContourMapExtent(const CGeoRect<double> &extent);

		//
		//
		//
		/*!
		*2015/1/21 get contour line according ti coordinate
		**/
		int FindContourLine(const CGeoPoint<double> &coord);
		
		/*!
		*
		**/
		void GetBlankAreas(const std::vector<CGeoPoint<double> > &trackMapPts, std::vector<std::vector<CGeoPoint<double>> > &blanks, std::vector<std::vector<CGeoPoint<double>> > &picked_areas, std::vector<std::vector<CGeoPoint<double>> > &picked_areas_borders);

		/*!
		*
		**/
		void DoSetBlankAreas(const std::vector<std::vector<CGeoPoint<double> > > &trackMapPts);

		/*!
		*
		**/
		void DoSetBlankArea(const std::vector<CGeoPoint<double> > &trackMapPts);

		/*!
		*
		**/
		void SetBlankArea();

		/*!
		*
		**/
		void ResetGridValue(CGeoPoint<double> *pts,CGeoPoint<double> *pts_original=0);

		/*!
		*
		**/
		double GetZValue(const CGeoPoint<double> &mapPt);

		/*!
		*
		**/
		void DoCutContourLines(const std::vector<CGeoPoint<double> > &trackMapPts, ContourVector &newcontours);

		void GetPanitedAreas();

	protected:
		//
		//
		//
		/*!
		*
		**/
		void GetMaxMin(double &max, double &min, short which);

		/*!
		*
		**/
		unsigned int DoGetZValueColor(double zvalue);

		/*!
		*
		**/
		void DoFillContour(CAnyCanvas &canvas, CGeoPoint<double> *mapPts, CGeoPoint<double> *scrPts, int number, bool isbordergrid=false, double same_zvalue = ANY_NAN);

		/*!
		*2015/8/28
		**/
		void FillContourMT(CAnyCanvas &canvas, CGeoPoint<double> *mapPts, CGeoPoint<double> *scrPts, int number, double same_zvalue = ANY_NAN);

		/*!
		*2015/8/28
		**/
		void DoFillContourMT();

		/*!
		*
		**/
		void DoRenderAxises(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderBorderLines(CAnyCanvas &canvas, unsigned short flag, int ticks);

		/*!
		*
		**/
		void DoFillingContour(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderContourLine(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderColorLabel(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderPolygonArea(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderSamples(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderGridLine(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderBlankArea(CAnyCanvas &canvas);

		//
		//
		//
		/*!
		*
		**/
		void GetCameraAngles(double &angleX, double &angleY, double &angleZ);

		/*!
		*
		**/
		void DoExtractTrackPoint(CGeoPoint<double> *scrPts, int number, std::vector<CGeoPoint<double> > &mapPts);

		//
		//
		//
		/*!
		*
		**/
		static void DoInsertIntoSampleAttrMap(SampleAttrMap &map, double id, double val);

		/*!
		*2018/4/8: render label
		**/
		void DoRenderLabel(CAnyCanvas &canvas, LabelStyle &labelStyle, const CGeoPoint<double> &pos, const std::string &label, CGeoPoint<double> *alongPts = 0, int num = 0);

	public:
		//
		CAnyContourTracingStrategy *m_tracing;
			
		//2016/10/9: set ContourSetting as public member
		ContourSetting m_setting;
				
		//2015/10/26
		bool m_isBlankSplineInterpolation;

		//erase picked areas
		bool m_isPickedAreaReverse;

		// traced lines
		int m_maxPtNumber;
		ContourVector m_contours;

		ContourVector m_contours_painting;
	protected:
		// discrete points
		int m_ptNumber;
		CGeoPoint<double> *m_pts;

		// cokriging points
		int m_cokrigingPtNumber;
		CGeoPoint<double> *m_cokrigingPts;

		// map extent
		CGeoRect<double> m_extent;
		CGeoRect<double> m_bkExtent;

		//// traced lines
		//int m_maxPtNumber;
		//ContourVector m_contours;

		//2016/10/9: move to public
		// contour setting
		//ContourSetting m_setting;

		// strategic object
		CAnyContourSurfaceStrategy *m_surface;

		// area(s) picked directly in map coordinates
		std::vector<std::vector<CGeoPoint<double>> > m_areas;
		
		// blank areas for map output
		std::vector<std::vector<CGeoPoint<double>> > m_blanks;
		
		// map operation
		long m_operation;

		//
		unsigned int m_lastStyle;
		bool m_isMouseAction;

		//2018/4/8: rectangle positions for labels
		std::vector<CGeoRect <double>> m_labelRectPositions;

		//2015/8/28: multi-thread
		CAnyCanvas *m_canvas;
		CGeoPoint<double> *m_mapPts;
		CGeoPoint<double> *m_scrPts;
		int m_number;
		int m_taskCount;
		int m_index;
		int m_step;

		/*!
		*2015/8/28
		**/
		class FillingColorTask: public CAnySignalTask<void()>,public JTCMonitor
		{
			public:
				FillingColorTask(int taskcount,int index, int step, CAnyCanvas &canvas,CGeoPoint<double> *mapPts, CGeoPoint<double> *scrPts, int number, CAnyContour *hook, double same_zvalue);
				~FillingColorTask();
				void DoExecuteTask();
			private:
				int m_index;
				int m_taskCount;
				CAnyCanvas &m_canvas;
				CGeoPoint<double> *m_mapPts;
				CGeoPoint<double> *m_scrPts;
				int m_number;
				int m_step;
				CAnyContour *m_hook;

				//2019/8/14: handle same z value
				double m_same_zvalue;
		};
		friend class FillingColorTask;
	};
}
#endif