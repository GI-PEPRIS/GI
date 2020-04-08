/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYMATH_BM_BURIAL_HISTORY_H__
#define __ANYMATH_BM_BURIAL_HISTORY_H__

#include "anyvis.h"

#include "boost/function.hpp"

#include "any/base/anystl.h"
#include "any/base/anygeom.h"
#include "any/base/anyformulaparser.h"
using namespace AnyBase;

//#include "yanqi/NumIntegrationWithVariableUpperLimit.h"
//using namespace std;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyBurialHistorySimulator
	{
	public:
		//
		struct GeologicalTimeScale
		{
			long m_idx;
			long m_parentidx;

			int m_level;
			double m_fromage;
			double m_toage;
			string m_name;

			std::vector<GeologicalTimeScale> m_children;

			/*!
			*
			**/
			GeologicalTimeScale()
			{
				m_idx = 0;
				m_parentidx = 0;
				m_level = 0;
				m_fromage = 0.;
				m_toage = 0.;
				m_name = "";

				m_children.clear();
			}
		};
		typedef std::vector<GeologicalTimeScale> TimeScaleVector;

		//
		typedef std::vector<CGeoPoint<double> > GeologicalLine;
		typedef std::vector<GeologicalLine> GeologicalLines;
		typedef std::map<string, GeologicalLine> GeologicalLayerMap;

		//
		struct GeologicalLayer
		{
			string m_name;
			string m_lithology;
			string m_burialformular;

			//
			int m_facies;

			//2017/3/9: lithology color,line style...
			int m_lithoColor;
			int m_lithLineStyle;

			//2017/3/21: vector query condition
			int m_realIdx;

			//
			double m_top;
			double m_base;
			double m_present_thickness;
			double m_eroded_thickness;
			double m_deposition_fromage;
			double m_deposition_toage;
			double m_eroded_fromage;
			double m_eroded_toage;
			
			//temperature related
			double m_ks;
			double m_kw;
			double m_fai0;
			double m_c;

			//2017/3/9: RO related, get value by calculation
			double m_a;
			double m_b;
			
			//2017/3/21: deposition thickness
			double m_deposition_thickness;
			
			//2017/3/29: record the burial line for each layer
			GeologicalLine m_burialLine;
			
			//2017/3/29: record the slope points for the layer which contains deposition thickness(>0)
			GeologicalLine m_depo_thick_slopes;
			
			//2017/3/29: for merging lines
			std::vector<GeologicalLine> m_burialLines;

			//2017/5/11: new variables for transient heat flow
			double m_cSolid;//c1-固体比热容
			double m_cWater;//c2-流体比热容

			double m_v;//热对流速度 单位: 米/百万年

			double m_rouSolid;//p1-固体密度
			double m_rouWater;//p2-流体密度
			
			//2017/6/9: toc value
			double m_toc;

			//2017/7/5: new properties for Dr. Xie 
			int m_property;//地层为1，虚地层（曾经沉积又被剥蚀）为2，剥蚀为3 ,沉积间断为4
			
			int m_lith_num;
			std::vector<double> m_lith_ratios;
			std::vector<std::string> m_lith_names;

			//2017/8/10: record marker for each layer
			int m_connecting_marker;

			//2017/11/27: hi0
			double m_hi0;
			int m_source_rock_method;

			/*!
			*
			**/
			GeologicalLayer()
			{
				m_name = "";
				m_top = 0.;
				m_base = 0.;
				m_present_thickness = 0.;
				m_eroded_thickness = 0.;
				m_deposition_fromage = 0.;
				m_deposition_toage = 0.;
				m_eroded_fromage = 0.;
				m_eroded_toage = 0.;
				m_lithology = "1-(φ0 *EXP(-C*depth))";
				m_facies = 0;
				m_burialformular = "Limestone:micrite";

				//
				m_kw = 0.63/* * 41.868*/;
				m_ks = 3.0/* * 41.868*/;
				m_fai0 = 0.48;
				m_c = 4.107e-4;//c = 4.107/10000.;

				//
				m_a = 0.;
				m_b = 0.;

				//
				m_lithoColor = RGB(135,206,250);//blue
				m_lithLineStyle = 0;

				//2017/3/21: deposition thickness
				m_deposition_thickness = 0.;
				m_realIdx = 0;

				//
				m_burialLine.clear();
				m_depo_thick_slopes.clear();

				//
				m_burialLines.clear();

				//new variables
				m_cSolid = 855.;
				m_cWater = 3712.951;

				m_v = 0;

				m_rouSolid = 2640;
				m_rouWater = 1040;

				//5%
				m_toc = 0.;

				//lithology related
				m_property = 1;

				m_lith_num = 1;
				m_lith_ratios.clear();
				m_lith_ratios.push_back(1.);

				m_lith_names.clear();
				m_lith_names.push_back("Limestone:micrite");

				//
				m_connecting_marker = -1;

				//
				m_hi0 = 0.;
				m_source_rock_method = 0;//0: LLNL, 1-5:PetroGenStyle
			}
		};
		typedef std::vector<GeologicalLayer> GeologicalLayerVector;

		//
		typedef boost::function<double (double, const string&)> Compression_Function;

	private:
		//
		//
		class RegainBurialHistoryUsingBack_Stripping_ForMultiFunction{
			//用于描述不同深度下计算地层骨架厚度的函数及其参数
			//当给定的顶、底面深度都处于本结构中的参数【FromDepth, ToDepth】范围内时，调用函数由myFunction定义的函数计算地层骨架厚度
			//myFunction中所需要的其它参数可以通过AddFunctionParameter逐个添加到本结构中并传递到myFunction
		public:
			double FromDepth, ToDepth;
			Compression_Function myFunction;
			int m_divisions;
			string m_formulae;

			// deprecated variables
			int nP;
			double *P;


			RegainBurialHistoryUsingBack_Stripping_ForMultiFunction(double minD, double maxD, int divisions, Compression_Function Function, const string& formulae){
				FromDepth=minD;
				ToDepth=maxD;
				myFunction=Function;
				P=0;
				nP=0;
				m_divisions = divisions;
				m_formulae = formulae;
			}
			~RegainBurialHistoryUsingBack_Stripping_ForMultiFunction(){
				if(P!=0){
					delete[] P;
					nP=0;
				}
			}
			int AddFunctionParameter(double x){
				double *a;
				a = new double[nP+1];
				for(int i=0; i<nP; i++){
					a[i]=P[i];
				}
				a[nP]=x;
				if(P!=0){
					delete[] P;
				}
				P=a;
				nP++;
				return nP;
			}
		};
		typedef std::vector<RegainBurialHistoryUsingBack_Stripping_ForMultiFunction*> CompressionFunctionVector;

		//
		//
		struct ReverseThicknessStripCursor
		{
			int m_layer_order;
			int m_fromtime_order;
			int m_totime_order;

			double m_maxtop;
			double m_maxbottom;
			double m_real_depth;
		};
		typedef std::deque<ReverseThicknessStripCursor> ReverseThicknessStripCursorDeque;

	public:
		CAnyBurialHistorySimulator();
		~CAnyBurialHistorySimulator();

	public:
		//
		//
		//
		void ClearFunctionVector();
		void RegisterFunction(double from, double to, Compression_Function function, const string& formulae, int divisions = 50);

		//
		void ExecuteStrip(int nLayer, double *Thickness, double **H,GeologicalLayerVector &layers);
		

	private:
		void RegainBurialHistoryUsingBack_Stripping(int nLayer, double *Thickness, std::vector<RegainBurialHistoryUsingBack_Stripping_ForMultiFunction *>UserFun, double **H);

		double CalLayerSkeletonThickness(double z1,double z2, Compression_Function myIntegrandFunction, const string& formulae, double *P, int nP);
		double NumericalIntegration_Self(double a, double b, Compression_Function IFun,const string& formulae, double *IFunPs, int IPs, int n);
		void DoInitializeThickness(int nLayer, double *Thickness, Compression_Function &myIntegrandFunction, int *UserFunNo, std::vector<RegainBurialHistoryUsingBack_Stripping_ForMultiFunction *>UserFun,double **H);
		void DoCalculateBoneThickness(int nLayer, double *Thickness, Compression_Function &myIntegrandFunction, int *UserFunNo, std::vector<RegainBurialHistoryUsingBack_Stripping_ForMultiFunction *>UserFun,double *Hs);
		void DoCalculateStrippedThickness(int nLayer, double *Thickness, Compression_Function &myIntegrandFunction, int *UserFunNo, std::vector<RegainBurialHistoryUsingBack_Stripping_ForMultiFunction *>UserFun,double *Hs, double **H);
		bool GetReverseStripCursor(int layeroder, int timeorder, ReverseThicknessStripCursor &layercursor);
		void DoAddEroadedThickness(GeologicalLayerVector &layers, double **H);
		int DoFindMaxDepthTime(int curlayer, double maxdepth, int curtime);
		double DoGetRealDepth(int curlayer, int curtime, int nexttime, double &top, double &bottom, Compression_Function &myIntegrandFunction, int *UserFunNo, std::vector<RegainBurialHistoryUsingBack_Stripping_ForMultiFunction *>UserFun,double *Hs);

		// when move this class to anymath, delete below functions
		double NumIntegrationWithVariableUpperLimit_K1(double x, double y, Compression_Function myIntegrandFunction, const string& formulae, double *P, int nP);
		double NumIntegrationWithVariableUpperLimit_K2(double x, double y, double h, Compression_Function myIntegrandFunction, const string& formulae, double *P, int nP);
		bool NumIntegrationWithVariableUpperLimit(double x0, double fx0, double h, Compression_Function myIntegrandFunction, const string& formulae, double *P, int nP, double &X);

	public:
		//
		CompressionFunctionVector m_functions;
		//
		GeologicalLayerVector m_layers;
		//2017/2/7: calculator
		CAnyFormulaParser m_parser;
		//
		ReverseThicknessStripCursorDeque m_stripped_cursors;
	};

}

#endif