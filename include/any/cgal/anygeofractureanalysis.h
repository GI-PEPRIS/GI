 /* The AnyCGAL of PetroCOVERY solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy management 
 * and rendering of geometries being a leading one.
 *
 * Copyright (C) 2015 Xiujie Sheng
 *
 * This library isn't a free software, so you cann't take the sourcecode without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
 * if you illegally got it. 
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
#ifndef __ANYCGAL_GEOFRACTURE_ANALYSIS_H__
#define __ANYCGAL_GEOFRACTURE_ANALYSIS_H__

// macro
#include "anycgal.h"
#include "anydelunary.h"
#include "geosurfacefit.h"
#include "geovectordo.h"

#include "any/base/anygeom.h"
using namespace AnyBase;

namespace AnyCGAL
{
	/*!
	*
	**/
	class ANYCGAL_CLASS CAnyGeoFractureAnalysis
	{
	public:
		//
		typedef std::map<CGeoVectorDo*, CGeoSurfaceFit*> GeoFractureMap;
		typedef GeoFractureMap::iterator fracture_itr;
		typedef GeoFractureMap::const_iterator fracture_citr;

		typedef std::map<CGeoVectorDo*, CGeoVectorDo::GeoPointVector > GeoAdjacentMap;
		typedef GeoAdjacentMap::iterator adjacent_itr;
		typedef GeoAdjacentMap::const_iterator adjacent_citr;

		//
		struct FaultPolygon
		{
			std::vector<CGeoPoint<double> > m_points;
			CGeoRect<double> m_extent;
		};

		/*!
		*
		**/
		enum FitAlgorithm
		{
			FA_Unknown = -1,
			FA_Gauss,
			FA_GaussWithCompletePivoting ,
			FA_HouseHolder,
			FA_Max,
			FA_MoretonSequin,
		};
		struct GeoFractureProperty
		{
			//
			// generic
			//
			// 地层厚度
			double m_thickness;
			 // 弹性模量,elastic modulus,岩石弹性模量, MPa, 石英砂岩
			double m_E;
			//泊松比,Poisson ratio
			double m_u;
			//拟合算法
			int m_algorithm;
			// 拟合系数
			int m_fittingCoefficient;
			// 数据点加密
			int m_interpolation;

			// 
			// Tensile
			//
			//抗拉强度 
			double m_criticalPullTensileStress;
			// 抗压强度 
			double m_criticalPushTensileStress;
			// 纵横张裂缝
			bool m_hasLongitudinalTensileFracture;
			bool m_hasTransverseTensileFracture;
			//张破裂门槛
			double m_criticalTensileI;

			// 张裂缝密度与张破裂率关系
			// Y=0.6467X7.2441
			// 张裂缝间距=1/张缝密度
			double m_tensileFractureDensity_I_A;
			double m_tensileFractureDensity_I_B;

			// 根据一个油田统计,张裂缝长度（L）与张裂缝间距（D）的关系为：
			// L=2.94D+1.17，单位：m，一般张裂缝长度与张裂缝间距的比值（L/D）大致为3-10倍。
			double m_tensileFractureLength_Width_A;
			double m_tensileFractureLength_Width_B;

			// 张裂缝长度（L）与张裂缝高度（H）之间还具有以下关系：
			// L=3.4H+279，单位：cm，其相关系数（R）为0.82
			double m_tensileFractureLength_Height_A;
			double m_tensileFractureLength_Height_B;

			//
			// shearing
			//
			// 粘聚力
			// cohesive strength 
			// MPa
			double m_cohesiveStrength;
			// 内摩擦角
			// friction angle
			// degree
			double m_frictionAngle;
			// 内摩擦系数
			double m_frictionCoefficient;
			// 剪裂角
			double m_shearingAngleInRadius;
			// 剪破裂门槛
			double m_criticalShearingI;
			// 剪裂缝密度与剪破裂率关系
			// Y=0.6467X7.2441
			// 剪裂缝间距=1/剪缝密度
			double m_shearingFractureDensity_I_A;
			double m_shearingFractureDensity_I_B;
			// 根据一个油田统计,剪裂缝长度（L）与剪裂缝间距（D）的关系为：
			// L=2.94D+1.17，单位：m，一般剪裂缝长度与剪裂缝间距的比值（L/D）大致为3-10倍。
			double m_shearingFractureLength_Width_A;
			double m_shearingFractureLength_Width_B;

			// 剪裂缝长度（L）与剪裂缝高度（H）之间还具有以下关系：
			// L=3.4H+279，单位：cm，其相关系数（R）为0.82
			double m_shearingFractureLength_Height_A;
			double m_shearingFractureLength_Height_B;

			GeoFractureProperty()
			{
				m_thickness = 120;
				m_E = 16.14;
				m_u = 0.079;
				m_algorithm = FA_Gauss;
				m_fittingCoefficient = 0;
				m_interpolation = 0;

				m_criticalPullTensileStress = 3.13;
				m_criticalPushTensileStress = 44.76;
				m_hasLongitudinalTensileFracture = true;
				m_hasTransverseTensileFracture = true;
				m_criticalTensileI = 0.5;

				m_tensileFractureDensity_I_A = 1;
				m_tensileFractureDensity_I_B = 1;
				m_tensileFractureLength_Width_A = 50;
				m_tensileFractureLength_Width_B = 0;
				m_tensileFractureLength_Height_A = 100;
				m_tensileFractureLength_Height_B = 0;

				m_cohesiveStrength = 12.43;
				m_frictionAngle = 37.29;
				m_frictionCoefficient = ::tan(m_frictionAngle / 180.0 * 3.141516);;
				m_shearingAngleInRadius =  (45 - m_frictionAngle / 2.) / 180.0 * 3.141516;
				m_criticalShearingI = 0.5;
				m_shearingFractureDensity_I_A = 1;
				m_shearingFractureDensity_I_B = 1;
				m_shearingFractureLength_Width_A = 50;
				m_shearingFractureLength_Width_B = 0;

				m_shearingFractureLength_Height_A = 100;
				m_shearingFractureLength_Height_B = 0;
			}

			void SetFrictionAngle(double angle)
			{
				m_frictionAngle = angle;
				m_frictionCoefficient = ::tan(m_frictionAngle / 180.0 * 3.141516);;
				m_shearingAngleInRadius =  (45 - m_frictionAngle / 2.) / 180.0 * 3.141516;
			}
		};
		//
		enum GeoFractureOutputPoint
		{
			GFOP_Unknown,
			GFOP_Curvature_Max,						// 最大主曲率图
			GFOP_Curvature_Min,						// 最小主曲率图
			GFOP_Stress_Max,						// 最大主应力图
			GFOP_Stress_Min,						// 最小主应力图
			GFOP_Tensile,							// 张裂缝图
			GFOP_Shearing,							// 剪裂缝图
			GFOP_Fracture,							// 裂缝图
			GFOP_Max
		};
		enum GeoFractureOutputLine
		{
			GFOL_Unknown,
			GFOL_Curvature_Max,						// 最大主曲率图
			GFOL_Curvature_Min,						// 最小主曲率图
			GFOL_Stress_Max,						// 最大主应力图
			GFOL_Stress_Min,						// 最小主应力图
			GFOL_Tensile_Longitude,					// 纵张裂缝图,line
			GFOL_Tensile_Latitude,					// 横张裂缝图,line
			GFOL_Shearing_Plus,						// 剪裂缝图+,line
			GFOL_Shearing_Minus,					// 剪裂缝图-,line
			GFOL_Max
		};
		enum GeoFractureOuputRose
		{
			GFOR_Unknown,
			GFOR_MaxCurvature,
			GFOR_MinCurvature,
			GFOR_TensileFracture,
			GFOR_TensileFractureLongitudinal,
			GFOR_TensileFractureTransverse,
			GFOR_ShearingFracture,
			GFOR_Fracture,
			GFOR_Max
		};
		struct GeoFractureLine
		{
			CGeoPoint<double> m_from;
			CGeoPoint<double> m_to;
		};
		
	private:
		//
		struct CalculateMeshGeofractureThreadParameter
		{
			int m_from;
			int m_to;

			const CAnyDelunary::MESH &m_mesh;
			std::vector<CAnyDelunary::EDGEINDEX> &m_edges_orderbystart;
			std::vector<CAnyDelunary::EDGEINDEX> &m_edges_orderbyend;

			CalculateMeshGeofractureThreadParameter(int from, int to, const CAnyDelunary::MESH &mesh, \
				std::vector<CAnyDelunary::EDGEINDEX> &start, std::vector<CAnyDelunary::EDGEINDEX> &end) : m_from(from), m_to(to), m_mesh(mesh),\
				m_edges_orderbystart(start), m_edges_orderbyend(end)
			{
			}
		};
		void CalculateMeshGeofractureThreadFunc(const CalculateMeshGeofractureThreadParameter &parameter);

		//
		struct CalculateSecondGeofractureThreadParameter
		{
			int m_from;
			int m_to;
		};
		void CalculateSecondGeofractureThreadFunc(const CalculateSecondGeofractureThreadParameter &parameter);
		void CalculateThirdGeofractureThreadFunc(const CalculateSecondGeofractureThreadParameter &parameter);
		void CalculateStressThreadFunc(const CalculateSecondGeofractureThreadParameter &parameter);
		void CalculateGeofractureThreadFunc(const CalculateSecondGeofractureThreadParameter &parameter);
		
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGeoFractureAnalysis();
		~CAnyGeoFractureAnalysis();

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetSample(CGeoPoint<double> *samples, int number); // non-direct
		void SetSample(CGeoPoint<double> *samples, int rows, int cols);	// direct
		CGeoPoint<double> *GetSample(int &number);
		void FreeSample();

		//
		//
		//
		/*!
		*
		**/
		void MakeGeologicalMesh();
		void MakeGeologicalMesh_Threaded();
		void FreeGeologicalMesh();
		void FreeGeoFracture();

		//
		//
		//
		/*!
		*
		**/
		void GetGeoFractureAsPoint(short type, std::vector<CGeoPoint<double> > &samples);
		void GetGeoFractureAsPoint_Directed(short type, std::vector<CGeoPoint<double> > &samples);

		void GetGeoFractureAsLine(short type, std::vector<GeoFractureLine> &lines);

		//2017/9/21: get the lines roughly
		void GetGeoFractureAsLine_Rough(short type, std::vector<GeoFractureLine> &lines, const CGeoRect<double> &extent, int rows, int cols);

		void GetGeoFractureAsRose(short type, std::vector<CGeoPoint<double> > &samples);
		void GetGeoFractureAsRose_Rough(short type, std::vector<CGeoPoint<double> > &samples, const CGeoRect<double> &extent, int rows, int cols);

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoCalculateStress(); // 通过主曲率计算地层应力
		void DoCalculateFracture();
		void DoCalculateStress_Threaded(); // 通过主曲率计算地层应力
		void DoCalculateFracture_Threaded();

		void DoVisitMesh(std::vector<CAnyDelunary::EDGEINDEX> &edges_orderbystart,std::vector<CAnyDelunary::EDGEINDEX> &edges_orderbyend);
		void DoGetAdjacents(std::vector<CAnyDelunary::EDGEINDEX> &edges_orderbystart, int whichstart,int notinclude, const CAnyDelunary::MESH &mesh, CGeoVectorDo::GeoPointVector &adjacents,CGeoVectorDo::GeoIndexVector &subscribes);
		
		CGeoSurfaceFit *DoCalculateVertexCurvature(CGeoVectorDo *cur, CGeoVectorDo::GeoPointVector &adjacents);
		void DoCalculateVertexStress(CGeoVectorDo *cur);

		void DoCalculateLine(const CGeoVectorDo *cur, double azimuth, GeoFractureLine &line);

		bool IsInsideFaultPolygon(double x, double y);
		void DoGetDetailedParameter(CGeoVectorDo *cur, double &thickness, double &E, double &u);

	public:
		// for seismic horizon, it had better direct mesh mode
		bool m_isDirectMesh;	
		int m_rows;	//
		int m_cols;

		// structure definition
		int m_sampleNumber;
		CGeoPoint<double> *m_samples;
		CAnyDelunary *m_delunary;

		// fault polygons
		std::vector<FaultPolygon> m_fault_polygons;

		// detailed parameter
		std::vector<CGeoPoint<double> > m_thick_samples;	// 厚度分布
		std::vector<CGeoPoint<double> > m_e_samples;		// 弹性模量
		std::vector<CGeoPoint<double> > m_u_samples;		// 泊松比

		//
		GeoFractureProperty m_setting;
		GeoFractureMap m_geofracture;
		std::vector<fracture_itr> m_geofracture_indices;

		GeoAdjacentMap m_adjacents;

		// kinds of limits
		int m_adjacentlimits;
		int m_taskcount;
		void *m_scheduler;
	};
}

#endif
