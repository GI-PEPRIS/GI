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
			// �ز���
			double m_thickness;
			 // ����ģ��,elastic modulus,��ʯ����ģ��, MPa, ʯӢɰ��
			double m_E;
			//���ɱ�,Poisson ratio
			double m_u;
			//����㷨
			int m_algorithm;
			// ���ϵ��
			int m_fittingCoefficient;
			// ���ݵ����
			int m_interpolation;

			// 
			// Tensile
			//
			//����ǿ�� 
			double m_criticalPullTensileStress;
			// ��ѹǿ�� 
			double m_criticalPushTensileStress;
			// �ݺ����ѷ�
			bool m_hasLongitudinalTensileFracture;
			bool m_hasTransverseTensileFracture;
			//�������ż�
			double m_criticalTensileI;

			// ���ѷ��ܶ����������ʹ�ϵ
			// Y=0.6467X7.2441
			// ���ѷ���=1/�ŷ��ܶ�
			double m_tensileFractureDensity_I_A;
			double m_tensileFractureDensity_I_B;

			// ����һ������ͳ��,���ѷ쳤�ȣ�L�������ѷ��ࣨD���Ĺ�ϵΪ��
			// L=2.94D+1.17����λ��m��һ�����ѷ쳤�������ѷ���ı�ֵ��L/D������Ϊ3-10����
			double m_tensileFractureLength_Width_A;
			double m_tensileFractureLength_Width_B;

			// ���ѷ쳤�ȣ�L�������ѷ�߶ȣ�H��֮�仹�������¹�ϵ��
			// L=3.4H+279����λ��cm�������ϵ����R��Ϊ0.82
			double m_tensileFractureLength_Height_A;
			double m_tensileFractureLength_Height_B;

			//
			// shearing
			//
			// ճ����
			// cohesive strength 
			// MPa
			double m_cohesiveStrength;
			// ��Ħ����
			// friction angle
			// degree
			double m_frictionAngle;
			// ��Ħ��ϵ��
			double m_frictionCoefficient;
			// ���ѽ�
			double m_shearingAngleInRadius;
			// �������ż�
			double m_criticalShearingI;
			// ���ѷ��ܶ���������ʹ�ϵ
			// Y=0.6467X7.2441
			// ���ѷ���=1/�����ܶ�
			double m_shearingFractureDensity_I_A;
			double m_shearingFractureDensity_I_B;
			// ����һ������ͳ��,���ѷ쳤�ȣ�L������ѷ��ࣨD���Ĺ�ϵΪ��
			// L=2.94D+1.17����λ��m��һ����ѷ쳤������ѷ���ı�ֵ��L/D������Ϊ3-10����
			double m_shearingFractureLength_Width_A;
			double m_shearingFractureLength_Width_B;

			// ���ѷ쳤�ȣ�L������ѷ�߶ȣ�H��֮�仹�������¹�ϵ��
			// L=3.4H+279����λ��cm�������ϵ����R��Ϊ0.82
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
			GFOP_Curvature_Max,						// ���������ͼ
			GFOP_Curvature_Min,						// ��С������ͼ
			GFOP_Stress_Max,						// �����Ӧ��ͼ
			GFOP_Stress_Min,						// ��С��Ӧ��ͼ
			GFOP_Tensile,							// ���ѷ�ͼ
			GFOP_Shearing,							// ���ѷ�ͼ
			GFOP_Fracture,							// �ѷ�ͼ
			GFOP_Max
		};
		enum GeoFractureOutputLine
		{
			GFOL_Unknown,
			GFOL_Curvature_Max,						// ���������ͼ
			GFOL_Curvature_Min,						// ��С������ͼ
			GFOL_Stress_Max,						// �����Ӧ��ͼ
			GFOL_Stress_Min,						// ��С��Ӧ��ͼ
			GFOL_Tensile_Longitude,					// �����ѷ�ͼ,line
			GFOL_Tensile_Latitude,					// �����ѷ�ͼ,line
			GFOL_Shearing_Plus,						// ���ѷ�ͼ+,line
			GFOL_Shearing_Minus,					// ���ѷ�ͼ-,line
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
		void DoCalculateStress(); // ͨ�������ʼ���ز�Ӧ��
		void DoCalculateFracture();
		void DoCalculateStress_Threaded(); // ͨ�������ʼ���ز�Ӧ��
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
		std::vector<CGeoPoint<double> > m_thick_samples;	// ��ȷֲ�
		std::vector<CGeoPoint<double> > m_e_samples;		// ����ģ��
		std::vector<CGeoPoint<double> > m_u_samples;		// ���ɱ�

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
