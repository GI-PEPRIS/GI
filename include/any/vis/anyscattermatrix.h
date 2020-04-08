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
#ifndef __ANYVIS_SCATTER_MATRIX_H__
#define __ANYVIS_SCATTER_MATRIX_H__

// refer to export macroes
#include "anyvis.h"

// refer to parents
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to axis parent
#include "anyaxises.h"

// refer to geometry basic
#include "any/base/anygeom.h"
using namespace AnyBase;

// refer to fitting macroes
#include "any/math/anyfittingstrategy.h"
using namespace AnyMath;

//2015/5/27
#include "any/thread/jtc.h"

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyScatterMatrix : public CAnyViewHook, protected CAnyAxises
	{
	public:
		/*!
		*
		**/
		enum ScatterViewMode
		{
			// matrix or singleton view mode
			SVM_View_Matrix												= 1,						// tree map
			SVM_View_Singleton											= 1 << 1,				// as one scatter plot
			SVM_View_Multiple											= 1 << 2,				// render kinds of polyline or points

			// as sticks or points
			SVM_Rendering_Vertical_Stick								= 1 << 3,
			SVM_Rendering_Horizontal_Stick							= 1 << 4,
			SVM_Rendering_Point											= 1 << 5,
			SVM_Rendering_Poly											= 1 << 6,
			SVM_Rendering_Regression								= 1 << 7,
			SVM_Rendering_Fitting										= 1 << 8, 
			SVM_Rendering_Histogram									= 1 << 9,
			SVM_Rendering_Interleave									= 1 << 10,

			// pick ways
			SVM_Pick_Poly													= 1 << 11,
			SVM_Pick_Rect													= 1 << 12,
			
			// regression line
			SVM_Regression_Whole										= 1 << 13,	 // to merge regression line
			SVM_Regression_Group										= 1 << 14, // into different groups

			// order standards
			SVM_Order_Idx													= 1 << 15,
			SVM_Order_Value												= 1 << 16,

			// log
			SVM_X_Log														= 1 << 17,
			SVM_Y_Log														= 1 << 18,
			//Gird
			SVM_Grid															= 1 << 19,
			
			//render kinds of poly line or points with mark
			SVM_View_Multiple_Marked								= 1 << 20,
			SVM_View_Hyperbola										= 1 << 21,
			SVM_View_DepthArea										= 1 << 22,
			SVM_View_Exceedence										= 1 << 23,

			// whether adopt the view hook mechanism
			SVM_Map_Operation										= 1 << 24,

			// render axis from 0, not from the minimum value of samples
			SVM_Axis_X_Start_From_Zero								= 1 << 25,
			SVM_Axis_Y_Start_From_Zero								= 1 << 26,

			SVM_Axis_X_To_P10								 		= 1 << 27,
			
			//render legend
			SVM_Rendering_Legend									= 1 << 28,

			//whether axis ticks are integer
			SVM_Axis_X_Integer										= 1 << 29,
			SVM_Axis_Y_Integer										= 1 << 30,

			//intercept point
			SVM_Intercept											= 1 << 31,
		};

		/*!
		*
		**/
		enum ScatterOtherMode
		{
			SOM_Rendering_Pie				= 1,
			SOM_Rendering_Stick				= 1 << 1,	

			//intercept
			SOM_X_Intercept					= 1 << 2,
			SOM_Y_Intercept					= 1 << 3,
			SOM_Intercept_Drag				= 1 << 4,

			SOM_Rendering_Stat_Value		= 1 << 5,
			SOM_Order_Ascending				= 1 << 6,

			SOM_Rendering_Stat_String_Count	= 1 << 7,
			SOM_Rendering_Stat_Count		= 1 << 8,

			//double Y axis
			SOM_Rendering_Double_Y_Axises	= 1 << 9,

			//2014/9/11: prospect mode
			SOM_Rendering_Prospect_Mode		= 1 << 10,

			//2015/4/14: whether or not overlay?
			SOM_Rendering_No_Overlay		= 1 << 11,

			//2015/5/18
			SOM_Rendering_Line     			 = 1 << 12,
			SOM_Rendering_Line_Editing       = 1 << 13,
			SOM_Rendering_Line_Color_Filling = 1 << 14,

			//2015/5/19
			SOM_Tick_X_Time					 = 1 << 15,
			SOM_Tick_Y_Time					 = 1 << 16,

			//2015/6/3
			SOM_Tick_X_String				 = 1 << 17,
			SOM_Tick_Y_String				 = 1 << 18,

			//2015/6/8:log axis
			SOM_X_Log_Axis					 = 1 << 19,
			SOM_Y_Log_Axis					 = 1 << 20,

			//2015/6/16:polar coordinates
			SOM_Polar_Coordinates			 = 1 << 21,

			//2015/7/3: render ellipse
			SOM_Rendering_Ellipse			 = 1 << 22,

			//2015/10/8:reverse axis
			SOM_X_Reverse_Axis				 = 1 << 23,
			SOM_Y_Reverse_Axis				 = 1 << 24,

			//2015/12/2
			SOM_Rendering_Gantt				 = 1 << 25,

			//2017/10/19: handle map extent, 4.5->5, 8->10...
			SOM_Extent_Interger_X			 = 1 << 26,
			SOM_Extent_Interger_Y			 = 1 << 27,

			//2019/3/28: matrix with histogram
			SOM_View_Matrix_Histogram        = 1 << 28,

		};

		/*!
		*
		**/
		enum InterceptOperation
		{
			IO_Default								= 0,
			IO_Intercept_Horizontal					= 1,
			IO_Intercept_Vertical					= 2,
		};

		//
		enum AppBuildType
		{
			APP_Play_General = 0,	 // 区带评价 
			APP_Play_Seismic,  // 地震部署
			APP_Trap_Prospect, // 评价项目
			APP_Trap_Wildcat,  // 圈闭预探井优选
		};

		/*!
		*
		**/
		enum ScatterSceneMode
		{
			//multiple scene
			SCM_Multiple = SVM_View_Multiple|SVM_Rendering_Point|SVM_Rendering_Poly|SVM_Order_Idx,
			
			//linear predication
			SCM_Linear_Predication = SVM_View_Singleton | SVM_Rendering_Point| SVM_Pick_Poly | SVM_Regression_Group | SVM_Order_Value,

			//multiple with mark scene
			SCM_Multiple_Marked = SCM_Multiple|SVM_View_Multiple_Marked,		
				
			//depth area
			SCM_DepthArea = SVM_View_Singleton | SVM_Rendering_Point | SVM_Rendering_Poly | SVM_Order_Idx | SVM_View_DepthArea,

			//hyperbola
			SCM_Hyperbola = SVM_View_Singleton | SVM_Rendering_Point | SVM_Order_Idx | SVM_View_Hyperbola|SVM_Axis_X_Start_From_Zero|SVM_Axis_Y_Start_From_Zero|SVM_Axis_X_To_P10,
		};

		/*!
		*
		**/
		struct ScatterElement
		{
			long m_idx;				            // as default  order standard. ex., for pool size, it maybe as discovery sequence order in year
			long m_groupIdx;
			double m_value;						// as another order standard
			std::string m_name;						// point name
			unsigned char m_axisOrder;    // x or y or z etc given to specify the axis rendering order

			bool m_isPicked;
			bool m_isShown;	// decide which points to be shown on SVM_View_Exceedence mode
			bool m_isOrderByIdx;
			bool m_isLogged;

			//set color and symbol by column
			std::string m_colNameColor;
			std::string m_colNameSymbol;
			std::string m_colNameLabel;
						
			//value as string
			std::string m_stringValue;

			// symbol, color setting for plot
			int m_color;
			int m_symbolStyle;

			//
			int m_lineColor;
			int m_lineStyle;
			bool m_isLineShown;//2015/5/12: for SVM_View_DepthArea mode, show lines or not
			double m_lineWidth;//2015/5/22
			bool m_isLineColorTransparent;//2017/1/16: whether the line color is transparent?

			//whether is a legal value
			bool m_isValueLegal;

			//
			bool m_isLabelShown;
			
			//size
			double m_txtSize;
			double m_symbolSize;
			int m_labelColor;//2015/5/22

			//2015/5/19:back value
			double m_bkValue;	

			//2016/12/1: used to record dimension name
			std::string m_dimName;

			//2016/12/9: used to paint selected point in modes except 'singleton'
			bool m_isSelPicked;

			/*!
			*
			**/
			ScatterElement() : m_idx(0), m_groupIdx(0), m_value(0.), m_name(""), \
				m_axisOrder(0), m_isPicked(false), m_isShown(true), m_isOrderByIdx(true), m_isLogged(false), \
				m_color(-1),m_symbolStyle(-1),m_lineColor(-1),m_lineStyle(0),m_isValueLegal(true),m_isLabelShown(false),m_stringValue(" "),\
				m_colNameColor(""),m_colNameSymbol(""),m_colNameLabel(""),m_txtSize(9.),m_symbolSize(2.),m_isLineShown(true)/*2015/5/12*/,m_bkValue(0.),m_lineWidth(1.),m_labelColor(0),\
				m_dimName(""),m_isSelPicked(false),m_isLineColorTransparent(true)
			{
			}

			/*!
			*
			**/
			const ScatterElement &operator=(const ScatterElement &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_idx = other.m_idx;
				m_groupIdx = other.m_groupIdx;
				m_value = other.m_value;
				m_name = other.m_name;
				m_axisOrder = other.m_axisOrder;

				m_isPicked = other.m_isPicked;
				m_isShown = other.m_isShown;
				m_isOrderByIdx = other.m_isOrderByIdx;
				m_isLogged = other.m_isLogged;

				//set color and symbol
				m_colNameColor = other.m_colNameColor;
				m_colNameSymbol = other.m_colNameSymbol;
				m_colNameLabel = other.m_colNameLabel;

				//symbol, color setting
				m_color = other.m_color;
				m_symbolStyle = other.m_symbolStyle;

				//line setting
				m_lineColor = other.m_lineColor;
				m_lineStyle = other.m_lineStyle;
				m_isLineShown = other.m_isLineShown;//2015/5/12

				//
				m_isValueLegal = other.m_isValueLegal;

				//label
				m_isLabelShown = other.m_isLabelShown;

				m_stringValue = other.m_stringValue;

				//size
				m_txtSize = other.m_txtSize;
				m_symbolSize = other.m_symbolSize;

				//2015/5/19
				m_bkValue = other.m_bkValue;
				m_lineWidth = other.m_lineWidth;
				m_labelColor = other.m_labelColor;

				//
				m_dimName = other.m_dimName;

				//
				m_isSelPicked = other.m_isSelPicked;

				//
				m_isLineColorTransparent = other.m_isLineColorTransparent;

				return *this;
			}
		};
		typedef std::vector<ScatterElement> ElementVector;

		/*!
		* straight fitting line
		**/
		struct ScatterLine
		{
			long m_startIdx;
			long m_endIdx;
			CGeoPoint<double> m_startPt;
			CGeoPoint<double> m_endPt;

			double m_slope;
			double m_interception;

			/*!
			*
			**/
			const ScatterLine &operator=(const ScatterLine &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_startIdx = other.m_startIdx;
				m_endIdx = other.m_endIdx;
				m_startPt = other.m_startPt;
				m_endPt = other.m_endPt;
				m_slope = other.m_slope;
				m_interception = other.m_interception;

				return *this;
			}
		};

		// For those records in memory respectively for each table
		typedef std::map<const std::string, std::vector<ScatterElement> > DimensionMap;
		typedef DimensionMap::iterator dim_itr;
		typedef DimensionMap::const_iterator dim_citr;

		// as pick polygon
		typedef std::vector<CGeoPoint<double> > PickPolygon;
		typedef std::vector<ScatterLine> RegressionLine;

		//
		//
		//
		typedef std::map<string,std::map<string,int>> ColorSymbolLabelMap;
		typedef ColorSymbolLabelMap::iterator csl_itr;

		//
		//
		//
		/*!
		*
		**/
		enum StatType
		{
			ST_Histogram				= 0,
			ST_Pie						= 1,
			ST_Value					= 2,
			ST_String_Count				= 3,
		};

		//
		//
		//
		/*!
		* 
		**/
		enum HistogramStyle
		{
			Histogram_Style_Overlay = 0,
			Histogram_Style_Separate,
		};

		//record count in each range
		typedef std::map<int,std::vector<int>> StatCountMap;
		
		//record each range
		typedef std::map<int,std::vector<string>> StatRangeMap;
		
		//record string value for groups of data
		typedef std::map<int,std::map<string,double>> StatValueMap;

		//record string count for groups of data
		typedef std::map<string,int> StringIntMap;
		typedef std::map<int,StringIntMap> StatStringCountMap;
		
		/*!
		* 
		**/
		struct StatisticalInfo
		{
			//common
			int m_fractiles;
			std::vector<int> m_colors;
			std::vector<bool> m_isShown;
			std::vector<bool> m_isLabelShown;
			std::vector<string> m_names;
			CGeoRect<double> m_mapExtent;
			int m_style;
			std::vector<double> m_txtSizes;
			
			StatCountMap m_statCountVec;
			StatRangeMap m_statRangeVec;

			//for statistic by value
			std::vector<double> m_values;
			std::vector<int> m_orders;
			bool m_isDescend;
			
			//for string count
			string m_name;
			std::vector<string> m_colorColNames;
			StatStringCountMap m_statStringCountVec;
			StatStringCountMap m_statCurStringCountMap;
			
			//pie
			int m_rows;
			int m_cols;
			StatValueMap m_statValueVec;			
			
			//for histogram
			double m_minX;
			double m_maxX;

			//2016/11/15: right y extent
			CGeoRect<double> m_mapExtentRight;

			StatisticalInfo() : m_fractiles(10),m_style(Histogram_Style_Overlay),m_isDescend(true),\
				m_rows(1),m_cols(1),m_name(""),m_minX(-1.),m_maxX(-1.)
			{
				
			}
			
			const StatisticalInfo &operator=(const StatisticalInfo &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_fractiles = other.m_fractiles;
				m_colors = other.m_colors;
				m_isShown = other.m_isShown;
				m_isLabelShown = other.m_isLabelShown;
				m_statCountVec = other.m_statCountVec;
				m_statRangeVec = other.m_statRangeVec;
				m_names = other.m_names;

				//
				m_values = other.m_values;
				m_isDescend = other.m_isDescend;
				m_orders = other.m_orders;

				m_txtSizes = other.m_txtSizes;

				m_style = other.m_style;
				m_mapExtent = other.m_mapExtent;

				m_rows = other.m_rows;
				m_cols = other.m_cols;
								
				m_statCurStringCountMap = other.m_statCurStringCountMap;
				m_statStringCountVec = other.m_statStringCountVec;
				
				m_statValueVec = other.m_statValueVec;

				m_name = other.m_name;
				m_colorColNames = other.m_colorColNames;

				m_minX = other.m_minX;
				m_maxX = other.m_maxX;

				//2016/11/15: right y extent
				m_mapExtentRight = other.m_mapExtentRight;

				return *this;
			}
		};
		
		//
		typedef std::map<int, CAnyFittingStrategy::FittingLine> FittingMap;
		typedef FittingMap::iterator fit_itr;
		typedef FittingMap::const_iterator fit_citr;

		/*!
		*2015/5/18:for SOM_Rendering_Line_Editing
		**/
		enum LineOperation
		{
			Line_Op_Default = 0,
			Line_Op_Create_Line,
			Line_Op_Create_Point,
			Line_Op_Move,
			Line_Op_Reshape,
			Line_Op_Rotation,//2016/11/14: line rotation
		};

		//
		typedef std::vector<ElementVector> LineElement;//ElementVector: ScatterElement x,y
		typedef std::vector<LineElement> LineElements;
		typedef LineElements::iterator line_itr;
		typedef LineElements::const_iterator line_citr;

		//map extent for LineElements
		typedef std::map<int,CGeoRect<double>> LineExtent;
		typedef std::map<int,int> LineColor;
		typedef std::map<int,std::vector<CGeoPoint<double>>> LinePts;
	
		//2015/7/3
		struct EllipseInfo
		{
			double m_shortAxis;
			double m_longAxis;
			double m_seta;
			
			//drawing attribute
			int m_color;
			double m_lineWidth;
			int m_lineStyle;
			bool m_isAlpha;

			//
			EllipseInfo()
			{
				Init();
			}

			//
			void Init()
			{
				m_shortAxis = -1.;
				m_longAxis = -1.;
				m_seta = -1.;

				m_color = RGB(255,0,0);
				m_lineWidth = 1.;
				m_lineStyle = 0;
				m_isAlpha = false;
			}

			//
			bool IsValid()
			{
				return (m_shortAxis > 0. && m_longAxis > 0.);
			}
		};
		typedef std::vector<EllipseInfo> EllipseInfos;

	protected://2015/5/27: multi-thread's task
		
		/*!
		*
		**/
		struct CrossPoint
		{
			int m_color;
			CGeoPoint<double> m_pt;

			//2017/3/29: line style
			int m_linestyle;

			//constructor
			CrossPoint()
			{
				m_color = 0;
				m_linestyle = 0;//solid line
			}
		};
		typedef std::vector<CrossPoint> CrossPoints;

		/*!
		*
		**/
		static bool CompareCorssPoint(const CrossPoint &cp1, const CrossPoint &cp2);
		
		/*!
		*
		**/
		class FillingColorTask: public CAnySignalTask<void()>,public JTCMonitor
		{
			public:
				FillingColorTask(int taskcount,int index, CAnyCanvas &canvas,const CGeoRect<double> &scrExtent, CAnyCPUScheduler *scheduler, CAnyScatterMatrix *scatter);
				~FillingColorTask();
				void DoExecuteTask();
			private:
				int m_index;
				int m_taskcount;
				CAnyCanvas &m_canvas;
				CGeoRect<double> m_scrExtent;
				CAnyCPUScheduler *m_scheduler;
				CAnyScatterMatrix *m_scatter;
		};
		friend class FillingColorTask;
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyScatterMatrix(CAnyView &curView, 
			unsigned int mode = SVM_View_Singleton | SVM_Pick_Poly | SVM_Regression_Whole | SVM_Rendering_Point | SVM_Rendering_Regression | SVM_Order_Idx);

		/*!
		*
		**/
		~CAnyScatterMatrix();

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
		**/
		void Add(const string &name, std::vector<ScatterElement> &pts, bool isLeftY = true);

		/*!
		*
		**/
		void Erase(const string &name);

		/*!
		*
		**/
		void EraseAll();

		/*!
		*
		**/
		void Sort(const string &name, unsigned int mode);

		/*!
		*
		**/
		int GetDimensionCount();

		/*!
		*
		**/
		//void Reset();

		/*!
		*
		**/
		const string GetDimensionName(int order);

		/*!
		*
		**/
		ScatterElement *GetData(const string &name, int &number);
		
		//
		//
		//
		/*!
		*
		**/
		void SetMode(unsigned int mode, bool isOtherMode = false);

		/*!
		*
		**/
		unsigned int GetMode(bool isOtherMode = false) const;

		//
		//
		//
		/*!
		*
		**/
		void AddFittingLine(int type, const CAnyFittingStrategy::FittingLine &curLine);

		/*!
		*
		**/
		void EraseFittingLine(int type);

		/*!
		*
		**/
		bool IsExistFittingLine(int type);

		/*!
		*
		**/
		int GetFittingLineCount();

		/*!
		*
		**/
		const CAnyFittingStrategy::FittingLine &GetFittingLine(int type);

		/*!
		*
		**/
		double GetFittingLineYValue(const CAnyFittingStrategy::FittingLine &line, double x);

		/*!
		*2015/10/28
		**/
		std::string GetFittingLineFormula(int type);

		//
		//
		//
		/*!
		*
		**/
		void GetPickedNames(string &names);

		/*!
		*
		**/
		void GetPickedElements(ElementVector &elements);

		/*!
		*
		**/
		const PickPolygon &GetPickedPoints();
		
		//
		//
		//
		/*!
		*
		**/
		void ClearRegression(bool isIncludeLine = true);

		/*!
		*
		**/
		int GetRegressionCount();

		/*!
		*
		**/
		bool IsRegressionLineOverlap();

		/*!
		*
		**/
		const ScatterLine &GetRegressionLine(int order);

		/*!
		*
		**/
		void SetRegressionLine(int order, const ScatterLine &line, bool isScrPt = true);

		/*!
		*
		**/
		void AddRegressionLine(ScatterLine &line, bool isMapPt = true);

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
		//file path setter and getter
		//
		/*!
		*
		**/
		void SetFilePath(string &path);

		/*!
		*
		**/
		const string &GetFilePath();

		//
		//dimension x setter and getter
		//
		/*!
		*
		**/
		void SetDimX(string &dimX);

		/*!
		*
		**/
		const string &GetDimX();

		//
		//dimension x setter and getter
		//
		/*!
		*
		**/
		void SetDimY(string &dimY);

		/*!
		*
		**/
		const string &GetDimY();

		//
		//
		//
		/*!
		*
		**/
		void SetAxisExt(double min = 0x7fffffff, double max = -0x7fffffff);

		/*!
		*
		**/
		void SetAxisFlag(double flagX = 0x7fffffff, double flagY = 0x7fffffff);

		/*!
		*
		**/
		void GetAxisFlag(double &flagX, double &flagY);

		/*!
		*2015/5/11: x flag lines
		**/
		void SetAxisXFlags(std::vector<double> &flagXs);

		/*!
		*2015/5/11: y flag lines
		**/
		void SetAxisYFlags(std::vector<double> &flagYs);
		
		/*!
		*2015/5/29: get x flag lines
		**/
		const std::vector<double> & GetAxisXFlags();

		/*!
		*2015/5/29: get y flag lines
		**/
		const std::vector<double> & GetAxisYFlags();

		//
		//
		//
		/*!
		*
		**/
		void SetHyperbolaColorStyle(bool isHyperbolaStyle);

		/*!
		*
		**/
		void SetCurrentFittingType(int type = CAnyFittingStrategy::FT_Max);

		//
		//
		//
		/*!
		*
		**/
		const AxisInfo & GetAxisInfo();

		/*!
		*
		**/
		void SetAxisInfo(const AxisInfo &axisInfo);

		/*!
		*
		**/
		const AxisInfo & GetLastAxisInfo();

		/*!
		*
		**/
		void SetLastAxisInfo(const AxisInfo &axisInfo);

		/*!
		*
		**/
		void SetAxisAutoMode(bool isAutoMode = true);

		/*!
		*
		**/
		bool IsAxisAutoMode();

		//
		//
		//
		/*!
		*
		**/
		const StatisticalInfo & GetStatisticalInfo(int type = ST_Histogram);

		/*!
		*
		**/
		void SetStatisticalInfo(const StatisticalInfo &histogramInfo, int type = ST_Histogram);
		
		//
		//
		//
		/*!
		*
		**/
		void SetHistogramLinePoints(const std::vector<double> &pts, unsigned int color = RGB(255,0,0));

		/*!
		*
		**/
		void SetHistogramTickLabels(const std::vector<std::string> &labels);
		
		//
		//
		//
		/*!
		*
		**/
		void SetScatterlayerScrExtent(const CGeoRect<double> &extent);

		/*!
		*
		**/
		void SetScatterLayerMode(bool isLayerMode = false);

		/*!
		*
		**/
		bool IsScatterLayerMode();

		//
		//
		//
		/*!
		*
		**/
		static void DoRenderMarkedPoint(CAnyCanvas &canvas,const CGeoPoint<double> &scrPt, SymbolStyle &style, \
			int order = -1, bool isDefaultColor = false, int symbolStyle = -1, int color = 0, double symbolSize = -1., double lineWidth = -1., int lineStyle = 0, int lineColor = RGB(0,0,0));

		/*!
		*
		**/
		static void GetStringWithoutExcessiveZero(std::string &str);

		/*!
		*
		**/
		static std::string Trim(std::string &str);

		//
		//
		//
		/*!
		*
		**/
		void SetTotalNumberString(string &str);

		/*!
		*
		**/
		void SetRateString(string &str);

		/*!
		*
		**/
		void SetHitString(string &str);

		/*!
		*2016/1/18: add int lineKind = 0, int lineColor = RGB(0,0,0), double lineWidth = 1.
		**/
		static void DoRenderRectangleWithBorderLine(CAnyCanvas &canvas, CGeoRect<double>& rect, SymbolStyle &style, int lineKind = 0, int lineColor = RGB(0,0,0), double lineWidth = 1.);

		/*!
		*
		**/
		static void SetLineStyle(LineStyle &style, int lineStyle, int color, bool isAlpha = true, double width = 1.);

		//
		//2015/5/18
		//
		/*!
		*
		**/
		void SetLineOperation(int operation); 

		
		/*!
		*
		**/
		int GetLineOperation(); 

		/*!
		*
		**/
		void SetLines(const LineElements &lines);

		/*!
		*
		**/
		bool SetLine(int lineId, const LineElement &line);

		/*!
		*
		**/
		bool GetLine(int lineId, LineElement &line);

		/*!
		*for Line_Op_Create_Point
		**/
		void SetCurrentLineId(int lineId);

		/*!
		*
		**/
		const LineElements &GetLines();

		/*!
		*picking the sample point, for re-shaping 
		**/
		bool GetLineElement(int &lineId, int &elementId, CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		bool RemoveLineElement(int lineId, int elementId);

		/*!
		*pick the line, for dragging
		**/
		int GetLine(CGeoPoint<double> &scrPt);
		
		/*!
		*
		**/
		void RemoveAllLines();

		/*!
		*
		**/
		bool RemoveLine(int lineId);

		/*!
		*
		**/
		void ClearTempLine();

		//
		//2015/6/3:for string axis tick
		//
		/*!
		*
		**/
		void SetTickStrs(const std::vector<std::string> &xTickStrs, const std::vector<std::string> &yTickStrs);

		//
		//2015/6/16:polar related
		//
		/*!
		*
		**/
		void SetPolarLengths(const std::vector<double> &polarLengths);

		//
		//2015/7/3:ellipse related
		//
		/*!
		*
		**/
		void SetEllipses(const EllipseInfos &ellipses);

		/*!
		*
		**/
		EllipseInfos & GetEllipses();

		/*!
		*
		**/
		void RenderEllipse(CAnyCanvas &canvas, const CGeoPoint<double> &centerPt, const EllipseInfo &ellipse, double maxPolarLength, double mapRadius);

		/*!
		*
		**/
		void ResetMapExtent(const CGeoRect<double> &extent, bool isLeft = true);

		/*!
		*2017/1/20: get color by min/max value
		**/
		static inline unsigned int DoGetColor(double curValue, double minValue, double maxValue, int minColor, int midColor, int maxColor);

		/*!
		*2018/4/4: pick elements from outside
		**/
		void PickElements(const CGeoRect<double> &extent, const PickPolygon &pickPolygon, unsigned long pick_mode);
		
	private:
		//
		//
		//
		/*!
		*
		**/
		void Clear();

		/*!
		*
		**/
		double GetAxisStep(dim_citr &first, double &min, double &max);

		//
		//
		//
		/*!
		*
		**/
		void DoRenderScatterAxis(CAnyCanvas &canvas, CGeoRect<double> &renderingExtent, dim_citr &xaxis, dim_citr &yaxis, double min = 0., double max = 0., bool isX = true);

		/*!
		*
		**/
		void DoRenderScatterPlot(CAnyCanvas &canvas, CGeoRect<double> &renderingExtent, dim_citr &xaxis, dim_citr &yaxis, int order = 0,bool isX = true);

		/*!
		*
		**/
		void GetPlotColorAndSymbol(int index, const string & colName, string &stringValue, int &val, const string &type = "color");

		/*!
		*
		**/
		int DoGetPlotValueByString(ColorSymbolLabelMap& map, const string &colName, const string &strVal);

		/*!
		*
		**/
		void SetMarkedLineStyle(LineStyle &style, int order = 0);

		/*!
		*
		**/
		void DoRenderPickExtent(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderHints(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderRegressionLine(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderFittingLine(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoGetMapExtent(dim_citr &yaxis, dim_citr &xaxis, CGeoRect<double> &mapExtent);

		/*!
		*2016/12/1:add bool isRenderHints, call the method in DoRenderHints method
		**/
		void DoPickElements(PickPolygon &pickPolygon, bool isRectangle = false, bool isRenderHints = false);

		/*!
		*
		**/
		void DoGetPickExtent(const PickPolygon &pickPoly, CGeoRect<double> &cmpExtent);

		/*!
		*
		**/
		void DoGetPickOrder(const PickPolygon &pickPoly, int &startIdx, int &endIdx);

		/*!
		*
		**/
		void DoGetRegressionLine(std::vector<CGeoPoint<double> > &scrPts, std::vector<CGeoPoint<double> > &mapPts, int startIdx, int endIdx);

		/*!
		*
		**/
		//void DoLinearRegression(double *x, double *y, int number, double &a, double &b);
		
		/*!
		*
		**/
		void DoRenderMultiple(CAnyCanvas &canvas, int dims);

		/*!
		*
		**/
		void DoRenderLegend(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderFlagLine(CAnyCanvas &canvas);

		/*!
		*2015/5/11:render x
		**/
		void DoRenderFlagLineX(CAnyCanvas &canvas, double x, int color);

		/*!
		*2015/5/11: render y
		**/
		void DoRenderFlagLineY(CAnyCanvas &canvas, double y, int color);
			
		/*!
		*
		**/
		void DoRenderTreeMap(CAnyCanvas &canvas, int dims);

		/*!
		*
		**/
		void DoRenderMatrixHistogram(CAnyCanvas &canvas, dim_citr &yaxis, dim_citr &xaxis);

		/*!
		*
		**/
		void DoRenderMatrixHistogramPlot(CAnyCanvas &canvas, dim_citr &axis);

		/*!
		*
		**/
		void InitHistogram(StatisticalInfo &info, double &minX, double &maxX, dim_citr &axis, bool isGettingXExtent = true);

		//
		//
		//
		/*!
		*
		**/
		void DoRenderHistogram(CAnyCanvas &canvas);
	
		/*!
		*
		**/
		void DoRenderHistogramLine(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderHistogramTickLabels(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderPie(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderStick(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderStatByValue(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderStatByStringCount(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderRectangle(CAnyCanvas &canvas, StatisticalInfo &info, int order, double startX, double endX,\
			double startY, double endY, bool isInteger = true, const string &name = "", int color = 0);

		/*!
		*
		**/
		void DoRenderStatByCount(CAnyCanvas &canvas);

		//
		//
		//
		/*!
		*
		**/
		void InitHistogram(StatisticalInfo &info, double &minX, double &maxX, bool isGettingXExtent = true);

		/*!
		*
		**/
		void InitPie(StatisticalInfo &info);

		/*!
		*
		**/
		void InitStatByStringCount(StatisticalInfo &info);

		/*!
		*
		**/
		int GetStatisticalShownCount(const StatisticalInfo &info);

		///*!
		//*
		//**/
		//void GetMinMax(double &min, double &max, bool isLeftY = true);

		/*!
		*
		**/
		//void GetLogMinMax(double &min, double &max);
		
		/*!
		*2014/12/2
		**/
		bool IsPointInMapextent(CGeoPoint<double> &scrPt);

		//
		//2015/5/18
		//
		/*!
		*
		**/
		//bool SetLineElement(int lineId, int elementId, double x, double y);

		/*!
		*
		**/
		//void DoRenderLineElements(CAnyCanvas &canvas, bool isDirect = false);

		/*!
		*
		**/
		//void ResetLineElements();

		//
		//2015/6/16:polar related
		//
		/*!
		*
		**/
		void DoRenderPolarCoordinates(CAnyCanvas &canvas);

	public:
		/*!
		*
		**/
		double GetPolygonArea(CGeoPoint<double> *scrPts, int number);

		/*!
		*
		**/
		static bool CompareElementAsIdx(const ScatterElement &first, const ScatterElement &second);
		
		/*!
		*
		**/
		static bool CompareElementAsValue(const ScatterElement &first, const ScatterElement &second);

		/*!
		*
		**/
		static bool CompareElementAsValueDesc(const ScatterElement &first, const ScatterElement &second);

		/*!
		*
		**/
		static bool CompareRegressionLine(const ScatterLine &first, const ScatterLine &second);

		//
		//
		//
		/*!
		*
		**/
		static void InitDefaultColors(std::vector<int> &colors, bool isInitialized = true, int number = 0);

		
		/*!
		*
		**/
		static bool CompareElementsByAscending(const ElementVector &first, const ElementVector &second);

		/*!
		*2018/11/30: whether to show ticks?
		**/
		void SetTickShown(bool show_tick_x = true, bool show_tick_y = true);

	protected:
		/*!
		*
		**/
		void GetMinMax(double &min, double &max, bool isLeftY = true);

		/*!
		*
		**/
		void GetLogMinMax(double &min, double &max);

		//
		//2016/12/13: used in CAnyLogGraphPlot
		//
		/*!
		*
		**/
		bool SetLineElement(int lineId, int elementId, double x, double y);

		/*!
		*
		**/
		void DoRenderLineElements(CAnyCanvas &canvas, bool isDirect = false);

		/*!
		*
		**/
		void ResetLineElements();

		//
		//2016/12/13: used in CAnyBurialHistoryPlot
		//
		/*!
		*
		**/
		void DoLinearRegression(double *x, double *y, int number, double &a, double &b);

	protected:
		// for hyperbola maxX
		double m_hyperbolaMaxX;
		bool m_isHyperbolaStyle;
	
		int m_buildType;

		// intersected dimensions
		DimensionMap m_dims;

		//
		CGeoRect<double> m_leftYExtent;
		CGeoRect<double> m_rightYExtent;

		//2016/9/22: customized extent
		CGeoRect<double> m_customLeftYExtent;
		CGeoRect<double> m_customRightYExtent;

		typedef std::map<string,bool> VerticalAxisMap;
		typedef VerticalAxisMap::iterator vam_itr;
		typedef VerticalAxisMap::const_iterator vam_citr;

		VerticalAxisMap m_yAxisMap;
	//private:
		// intersected dimensions
		//DimensionMap m_dims;

		//for histogram mode
		StatisticalInfo m_histogramInfo;
		std::vector<double> m_histogramPoints;
		std::vector<std::string> m_histogramTickLabels;
		unsigned int m_histogramPointsColor;

		//for pie mode
		StatisticalInfo m_pieInfo;

		//for stat by value mode
		StatisticalInfo m_valueInfo;

		//for stat by string count
		StatisticalInfo m_strCountInfo;

		// extent to pick elements in rectangle
		CGeoRect<double> m_pickExtent;
		CGeoRect<double> m_backupPickExtent;//2016/6/3: backup the pick extent

		// extent to pick element in polygon
		PickPolygon m_pickPolygon;
		PickPolygon m_backupPickPolygon;

		// picked elements' point 
		PickPolygon m_pickedPoints;

		// regression line candidates
		RegressionLine m_regressionLines;
		// kinds of fitting line
		FittingMap m_fittingLines;

		// position for hints
		CGeoPoint<double> m_hintPt;
		// view mode
		unsigned int m_mode;

		//other mode
		unsigned int m_otherMode;

		//for restoring scene
		string m_path;
		string m_dimX;
		string m_dimY;

		//axis extent
		double m_min;
		double m_max;

		//intercept : flag line position of axis
		double m_flagX;
		double m_flagY;

		//2015/5/11: a series of flag lines, including vertical and horizontal lines
		std::vector<double> m_flagXs;
		std::vector<double> m_flagYs;

		//intercept mouse related
		bool m_isInterceptMouseDown;
		bool m_isInterceptMouseMove;
		int m_interceptOp;
		int m_interceptOrder;//2015/5/11: get render order, -1: m_flagX/m_flagX; >0 value in m_flagXs/m_flagYs

		//total number string
		string m_totalNumStr;
		string m_rateStr;
		string m_hitStr;

		//record current fitting line's type
		int m_curFittingType;

		//2014/8/29: axis name - leftY/rightY
		//typedef std::map<string,bool> VerticalAxisMap;
		//typedef VerticalAxisMap::iterator vam_itr;
		//typedef VerticalAxisMap::const_iterator vam_citr;

		//VerticalAxisMap m_yAxisMap;

		////
		//CGeoRect<double> m_leftYExtent;
		//CGeoRect<double> m_rightYExtent;

		//2015/4/14: for SOM_Rendering_No_Overlay mode
		std::vector<CGeoPoint<double>> m_ptPositions;

		/////////////////////////////2015/5/18: for SOM_Rendering_Line_Editing////////////////////////////////////////////
		LineElements m_lines;
		int m_lineOperation;
		CGeoPoint<double> m_startPt;
		int m_lineId;
		int m_elementId;

		//for add line
		LineElement m_tempLine;
		ElementVector m_tempLinePt;//latest point

		LineColor m_lineColor;
		LinePts m_linePts;

		LineExtent m_lineExtent;
		//2015/5/26
		CGeoRect<double> m_lineBorder;
		//2015/5/28
		std::vector<int> m_lineCoordX;

		//2015/6/16: a group of polar point's length
		std::vector<double> m_polarLengths;

		//2015/7/3
		EllipseInfos m_ellipses;

		//2016/12/1: return picked elements
		ElementVector m_pickedElements;
		
		//2016/12/21: backup ticks
		std::vector<std::string> m_xBkTickStrs;
		std::vector<std::string> m_yBkTickStrs;
	public:
		//for setting color and symbol according to a column
		ColorSymbolLabelMap m_colors;
		ColorSymbolLabelMap m_symbols;

		std::string m_xTitle;
		std::string m_yTitle;

		//2016/11/15: right y
		std::string m_yTitleRight;

		//2016/1/25: for identifying the drag action
		bool m_isInterceptMouseUp;

		//2016/1/25: flag line color
		int m_flagXColor;
		int m_flagYColor;
		std::vector<int> m_flagXColors;
		std::vector<int> m_flagYColors;

		//2016/11/14: rotation point for line rotation
		CGeoPoint<double> m_rotationScrPt;
		int m_rotationLineId;

		//2016/12/14: record mouse action's line id
		int m_mouseActionLineId;
		bool m_isLineActionMouseUp;
	};
}

#endif