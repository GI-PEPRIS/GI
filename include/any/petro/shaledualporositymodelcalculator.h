/*!
 * The AnyPetro of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the domain data model etc.
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
#ifndef __ANYPETRO_SHALE_DUAL_POROSITY_MODEL_PREDICATOR_H__
#define __ANYPETRO_SHALE_DUAL_POROSITY_MODEL_PREDICATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"
#include "accumulationelement.h"
#include "accumulationassessor.h"
#include "accumulationresourcemanager.h"
using namespace AnyPetro;

// anybase
#include "any/base/anystl.h"
#include "any/base/anyport.h"

// anymath
#include "any/math/anysequentialgausssimulator.h"
using namespace AnyMath;

#include "any/db/anyaccessor.h"
using namespace AnyDB;

#include "any/map/anyviewhook.h"
using namespace AnyMap;

#include "any/base/anyvectop.h"
#include "any/base/anyformulaparser.h"
using namespace AnyBase;

namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CShaleDualPorosityModelCalculator : public CAccumulationAssessor
	{
	public:

		enum CalType
		{
			CT_Bitumen_A_QSH0503_2013_Sinopec,
			CT_Interlayer_QSH0503_2013_Sinopec,
			CT_Shale_Gas_QSH0503_2013_Sinopec,
			CT_Shale_Gas_DZT0254_2014_China,
			CT_MLR_Bitumen_A,
			CT_Shale_Gas_LandFace,
		};

		enum UnitType
		{
			UT_M,
			UT_Km,
		};

		// variable type
		enum VariableParameterType
		{
			VPT_Unknown = -1,
			VPT_Area,										// Extent in rectangle or polygon
			VPT_Thick,
			VPT_Porosity_Matrix,
			VPT_Porosity_Matrix_SG,
			VPT_Porosity_HC,
			VPT_TOC,
			VPT_Surface,
			VPT_G,
			VPT_Press,
			VPT_PL,
			VPT_GS,
			VPT_Sat,
			VPT_Dens,
			VPT_Sw,
			VPT_T,
			VPT_Pi,

			VPT_Max=999999,
		};
		typedef std::map<short, std::vector<CGeoPoint<double> > > VariableParameterMap;
		typedef std::map<short, CAnyViewHook * > VariableHookMap;

		typedef VariableParameterMap::iterator var_itr;
		typedef VariableParameterMap::const_iterator var_citr;

		// variable simulator
		typedef std::map<short, CAnySequentialGaussSimulator> VariableSimulatorMap;
		typedef VariableSimulatorMap::iterator sim_itr;
		typedef VariableSimulatorMap::const_iterator sim_citr;

		/*!
		* well per�����Ծ��ػ����ݱ�
		**/
		struct RockEvalParameter
		{
			//
			long m_pidx;
			long m_wellid;
			long m_elementidx;
			string m_name;

			// ��������
			double m_x;
			double m_y;
			double m_depth;								// ĳһ��ȵĲ���ֵ
			double m_toc;								// �л�̼�������ػ����Ի��߲⾮�������ݼ���
			double m_s1;								// �ѽ���
			double m_s2;								// �ܽ���
			double m_tmax;								// �����¶�
			double m_hi;								// ��ָ��
			double m_oi;								// oxygen
			double m_pi;								// ����ָ����s1/(s1+s2)
			double m_hc_porosity;						// ��������ָ�ֱ꣬�Ӽ����л���
			double m_matrix;							// ��������ָ�ֱ꣬�Ӽ����޻���
			double m_vl;
			double m_pl;
			double m_gs;								//�������Ͷ�

			bool m_isused;								
			/*!
			*
			**/
			RockEvalParameter() : m_pidx(0), m_wellid(0), m_name(""), m_elementidx(0),m_matrix(0),\
				m_x(0),m_y(0),m_depth(0.), m_vl(0.0),m_pl(0.0),m_gs(0.0),\
				m_toc(0.), m_s1(0.), m_s2(0.), m_tmax(0.), m_hi(0.), m_oi(0.), m_pi(0.), m_hc_porosity(0),m_isused(true)
			{
			}

			const RockEvalParameter &operator=(const RockEvalParameter &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_pidx					=other.m_pidx;
				m_wellid				=other.m_wellid;	
				m_elementidx			=other.m_elementidx;
				m_name					=other.m_name;	
				m_depth					=other.m_depth;			
				m_toc					=other.m_toc;			
				m_s1					=other.m_s1;			
				m_s2					=other.m_s2;			
				m_tmax					=other.m_tmax;			
				m_hi					=other.m_hi;			
				m_oi					=other.m_oi;			
				m_pi					=other.m_pi;			
				m_hc_porosity			=other.m_hc_porosity;    
				m_x						=other.m_x; 
				m_y						=other.m_y; 
				m_isused				=other.m_isused;
				m_matrix				=other.m_matrix;
				m_vl					=other.m_vl;
				m_pl					=other.m_pl;
				m_gs					=other.m_gs;
				return *this;
			}

			bool IsReady()
			{
				return m_toc && m_tmax && m_s1 && m_hi;
			}
		};
		typedef std::map<long, std::vector<RockEvalParameter> > RockParameterMap;
		typedef RockParameterMap::iterator rock_itr;
		typedef RockParameterMap::const_iterator rock_citr;

		/*!
		*
		**/
		enum GenerationModelType
		{
			GMT_Unknown=-1,
			GMT_Depth_Tmax,		// ��ȣ�X�ᣩ��TMAX��Y�ᣩģ�ͣ����ڷǵػ����ݾ���TMAX��ȡ�����ڼ���TOC��
			GMT_Tmax_HI,		// TMAX��X�ᣩ��HI��Y�ᣩģ�ͣ����ڷǵػ����ݾ���HI��ȡ
			GMT_Tmax_F,			// TMAX��X�ᣩ��F��Y�ᣩģ�ͣ����ڷǵػ����ݾ���F��ȡ
			GMT_Passey,
			GMT_Other,			// 
			GMT_Max
		};

		/*!
		* ��������������TOC����
		**/
		enum LogCurveType
		{
			LCT_Unknown,
			LCT_GR,								// ٤��
			LCT_Resis,							// ǳ���������
			LCT_Density,						// �ܶ�
			LCT_Sonic,							// ����
			LCT_RT,								// ����������
			LCT_Neutron,						// ����
			LCT_GS,				//GS���������Ͷ�
			//�����Ľ�������
			LCT_Matrix_Porosity,				// ���ͺ�Ļ��ʿ�϶������
			LCT_Organic_Porosity,					// ���ͺ���л���϶������
			LCT_HC_TOC,							// ���ͺ��TOC��������

			LCT_Max
		};
		struct LogCurve
		{
			//
			long m_wellid;
			string m_name;
			double m_x;
			double m_y;
			long m_horizonid;
			double m_fromdepth;							// Ŀ�ĵز�
			double m_todepth;							// 

			//
			double m_baseline;							// ����TOC���͵Ĳ⾮��Ӧֵ����
			short m_type;								// ��������
			std::vector<CGeoPoint<double> > m_curve;	// ��ȷ�Χ�ڣ��⾮��Ӧֵ
			double m_coef;								// �𲽻ع�ϵ��

			/*!
			*
			**/
			LogCurve() : m_wellid(0.), m_name(""), m_horizonid(ANY_NAN), m_fromdepth(0.), m_todepth(0.), m_x(0), m_y(0)
			{
			}
			LogCurve(const LogCurve &other)
			{
				*this = other;
			}

			const LogCurve &operator=(const LogCurve &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_wellid = other.m_wellid;
				m_name = other.m_name;
				m_x = other.m_x;
				m_y = other.m_y;
				m_horizonid = other.m_horizonid;
				m_fromdepth = other.m_fromdepth;
				m_todepth = other.m_todepth;
				m_baseline = other.m_baseline;
				m_type = other.m_type;
				m_curve.clear();
				m_curve.assign(other.m_curve.begin(), other.m_curve.end());
				m_coef = other.m_coef;

				return *this;
			}

		};
		typedef std::map<long, std::vector<LogCurve> > LogCurveMap;
		typedef LogCurveMap::iterator log_itr;
		typedef LogCurveMap::const_iterator log_citr;

		/*!
		* ���Ծ��������ʱ����������ڶ�ά���ģ�⣩
		**/
		struct GeologicalParameter
		{
			//
			long m_pidx;
			long m_wellid;
			string m_name;
			long m_elementidx;

			double m_x;
			double m_y;
			long m_horizonid;								// ��λ
			double m_fromdepth;
			double m_todepth;

			double m_hc_toc;								// TOC�������⾮���߻�ȡ����ֱ�ӵػ����ݼ���
			double m_hc_porosity;							// �л��ʿ�϶�ȣ��⾮���߻�ȡ����ֱ�ӵػ����ݼ���

			double m_matrix_porosity;						// ���ʿ�϶�ȣ�ͨ��LCT_Matrix���͵Ĳ⾮���߻�ȡ
			double m_thickness;								// �Ӻ�� 2
			double m_net_thickness;							// ����� 3

			double m_vl;
			double m_pl;
			double m_gs;									//�������Ͷ�
			/*!
			*
			**/
			GeologicalParameter() : m_wellid(0.), m_name(""), m_pidx(0),m_elementidx(0),\
				m_x(ANY_NAN), m_y(ANY_NAN), m_horizonid(ANY_NAN), m_fromdepth(0.), m_todepth(0.), m_gs(0.0),\
				m_hc_toc(0.), m_hc_porosity(0.), m_matrix_porosity(0.), m_thickness(0.), m_net_thickness(0.),m_vl(0),m_pl(0)
			{
			}

			const GeologicalParameter &operator=(const GeologicalParameter &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_pidx	= other.m_pidx;
				m_elementidx =other.m_elementidx;
				m_wellid = other.m_wellid;
				m_name = other.m_name;	
				m_horizonid = other.m_horizonid;	
				m_fromdepth = other.m_fromdepth;
				m_todepth = other.m_todepth;
				m_matrix_porosity = other.m_matrix_porosity;	
				m_hc_toc = other.m_hc_toc;
				m_hc_porosity = other.m_hc_porosity;				
				m_thickness = other.m_thickness;					
				m_net_thickness = other.m_net_thickness;				
				m_x  = other.m_x; 
				m_y = other.m_y; 
				m_vl=other.m_vl;
				m_pl=other.m_pl;
				m_gs					=other.m_gs;
				return *this;
			}

		};
		typedef std::map<long, GeologicalParameter> GeologicalParameterMap;
		typedef GeologicalParameterMap::iterator geo_itr;
		typedef GeologicalParameterMap::const_iterator geo_citr;


		/*!
		*	˫��ģ�͵�ȫ�ּ������
		**/
		enum PasseyMethod
		{
			Passey_Unknown = -1,
			Passey_Sonic,											// ��������
			Passey_Density,											// �����ܶ�
			Passey_Neutron,											// ��������
			Passey_Regression,										// ֱ�ӻع�
			Passey_Max
		};
		enum GenerationModelMethod
		{
			Generation_Model_Unknown = -1,
			Generation_Model_Direct,					// ֱ�������������	hi-tmax
			Generation_Model_Model,						// ��������ģ�� hi-tmax
			Generation_Model_Max
		};
		struct ModelParameter
		{	
			// �м����������
			// ����ת��ϵ��
			double m_hc_hi0;					// �����ԭʼ��ָ��
			double m_hc_f;						// ����ϵ�� 

			double m_hc_alpha;					// hi0/1200
			double m_hc_gamma;					// 1.2

			// ��ʯ�͸��Ҹ��ܶ�
			double m_hc_pb;
			double m_hc_pk;
			double m_bg;
			double m_MM;						// ԭ������(g/mol)
			double m_matrix_ground_porosity;	// �ر���ʼ��϶��
			double m_matrix_wb;					// �ز�ˮ�ܶ�

			// ���������ֱ��PLOT��hi-tmax�������ϵ��
			short m_model_method;
			double m_model_mintmax;				// ��������¶�
			double m_model_maxtmax;				// ��������¶�
			double m_model_beta;				//
			double m_model_theta;				//
			double m_model_c;					//  constant
			std::vector<CGeoPoint<double> > m_tmax_hi_line;
			std::vector<CGeoPoint<double> > m_tmax_f_line;

			// �л���ͼ��
			double m_depth_tmax_slope;				// depth-tmax��б��
			double m_depth_tmax_intercept;			// depth-tmax�Ľؾ�

			double m_toc_vl_slope;					 // toc-vl��б��
			double m_toc_vl_intercept;				// toc-vl�Ľؾ�

			// �⾮���߼���TOC����
			short m_passey_method;						// enum 
			double m_passey_slope;						// 
			double m_passey_intercept;

			double m_passey_resis_alpha;				// ֱ�ӻع���������߲���
			double m_passey_sonic_beta;
			double m_passey_gr_gamma;
			double m_passey_density_theta;
			double m_passey_c;                 // constant

			bool m_passey_resis_alpha_used;
			bool m_passey_sonic_beta_used;
			bool m_passey_gr_gamma_used;
			bool m_passey_density_theta_used;
			bool m_passey_c_used;

			// simulation
			double m_simulation_gridwidth;
			double m_simulation_gridheight;
			double m_simulation_gridrows;
			double m_simulation_gridcols;
			double m_simulation_seed;
			double m_simulation_iterations;

			// ��������ٷֱȣ��������=1
			double m_resource_foil;
			double m_resource_fgas;
			double m_resource_fvf;
			double m_resource_bg;
			double m_resource_gor;				// 
			double m_resource_m;				// ��Ȼ����ԭ������

			double m_effectstress;				//��ЧӦ��ϵ��


			//
			ModelParameter() : m_hc_hi0(0.), m_hc_gamma(1.2), m_hc_pb(1.6), m_hc_pk(1.4), m_hc_f(0.8), m_matrix_ground_porosity(40), m_matrix_wb(0.9),\
				m_model_beta(0.), m_model_theta(0.), m_model_c(0.), m_model_method(Generation_Model_Direct), m_model_mintmax(0.), m_model_maxtmax(500), m_depth_tmax_slope(0.), m_depth_tmax_intercept(0.),\
				m_passey_method(-1), m_passey_slope(0.), m_passey_intercept(0.),m_passey_resis_alpha(0.), m_passey_sonic_beta(0.),m_passey_gr_gamma(0.),m_passey_density_theta(0.),m_passey_c(0.), \
					m_resource_foil(0.2), m_resource_fgas(0.8), m_resource_fvf(400), m_resource_bg(0.003), m_resource_gor(10000), m_resource_m(800.), m_effectstress(0.02),\
					m_simulation_seed(199327),m_simulation_iterations(1000),m_toc_vl_slope(0),m_toc_vl_intercept(0),m_bg(0.0046),m_MM(20),m_passey_resis_alpha_used(true),m_passey_sonic_beta_used(true),m_passey_gr_gamma_used(true),
			m_passey_density_theta_used(true),m_passey_c_used(true)
			{
			}

			const ModelParameter &operator=(const ModelParameter &other)
			{
				m_hc_hi0								=other.m_hc_hi0;
				m_hc_f									=other.m_hc_f;
				m_hc_alpha							=other.m_hc_alpha;
				m_hc_gamma						=other.m_hc_gamma;
				m_hc_pb								=other.m_hc_pb;
				m_hc_pk								=other.m_hc_pk;
				m_model_method						=other.m_model_method;
				m_model_mintmax				=other.m_model_mintmax;
				m_model_maxtmax				=other.m_model_maxtmax;
				m_model_beta						=other.m_model_beta;
				m_model_theta						=other.m_model_theta;
				m_model_c							=other.m_model_c;
				m_depth_tmax_slope						=other.m_depth_tmax_slope;	// slope
				m_depth_tmax_intercept					= other.m_depth_tmax_intercept;
				m_passey_method 				=other.m_passey_method;
				m_passey_slope = other.m_passey_slope;
				m_passey_intercept = other.m_passey_intercept;
				m_passey_resis_alpha					=other.m_passey_resis_alpha;
				m_passey_sonic_beta					=other.m_passey_sonic_beta	;
				m_passey_gr_gamma				=other.m_passey_gr_gamma;
				m_passey_density_theta					=other.m_passey_density_theta;
				m_passey_c							=other.m_passey_c;
				m_simulation_gridwidth		=other.m_simulation_gridwidth;
				m_simulation_gridheight		=other.m_simulation_gridheight;
				m_simulation_gridrows		=other.m_simulation_gridrows;
				m_simulation_gridcols			=other.m_simulation_gridcols;
				m_simulation_seed				=other.m_simulation_seed;
				m_simulation_iterations		=other.m_simulation_iterations;
				m_resource_foil					=other.m_resource_foil	;
				m_resource_fgas					=other.m_resource_fgas;
				m_resource_fvf						=other.m_resource_fvf;
				m_resource_bg						=other.m_resource_bg;
				m_resource_gor					=other.m_resource_gor;
				m_resource_m 						=other.m_resource_m;
				m_effectstress						=other.m_effectstress;
				m_toc_vl_slope						=other.m_toc_vl_slope		;		
				m_toc_vl_intercept					=other.m_toc_vl_intercept	;
				m_passey_resis_alpha_used			=other.m_passey_resis_alpha_used;
				m_passey_sonic_beta_used			=other.m_passey_sonic_beta_used;
				m_passey_gr_gamma_used				=other.m_passey_gr_gamma_used;
				m_passey_density_theta_used			=other.m_passey_density_theta_used;
				m_passey_c_used						=other.m_passey_c_used;

				m_tmax_hi_line.clear();
				m_tmax_hi_line.assign(other.m_tmax_hi_line.begin(),other.m_tmax_hi_line.end());
				m_tmax_f_line.clear();
				m_tmax_f_line.assign(other.m_tmax_f_line.begin(),other.m_tmax_f_line.end());

				return *this;
			}
		};

		/*!
		*
		**/
		struct ResourcePredication
		{
			double m_oil;
			double m_freegas;
			double m_solutiongas;
			double m_absorbgas;
			
			double m_total;
			//ҳ����
			double m_geooil;
			double m_absorboil;
			double m_Moil;//�ɶ�ϵ����,������
			double m_rfoil;
			ResourcePredication() : m_oil(0.), m_freegas(0.), m_solutiongas(0.), m_absorbgas(0.), m_total(0.),m_Moil(0),m_geooil(0),m_absorboil(0),m_rfoil(0)
			{
			}
			ResourcePredication(const ResourcePredication &other)
			{
				*this = other;
			}
			const ResourcePredication &operator=(const ResourcePredication &other)
			{
				if(this != &other)
				{
					m_oil = other.m_oil;
					m_freegas = other.m_freegas;
					m_solutiongas = other.m_solutiongas;
					m_absorbgas = other.m_absorbgas;
					m_total = other.m_total;
					m_Moil = other.m_Moil;
					m_geooil= other.m_geooil;
					m_absorboil= other.m_absorboil;
					m_rfoil=other.m_rfoil;
				}
				return *this;
			}
		};
		typedef std::vector<ResourcePredication> ResourcePredicationVector;


		struct ctlgrid
		{
			int m_row;
			int m_col;
			double m_zvalue;
			std::vector<double> m_pointsZ;
			ctlgrid() : m_row(0), m_col(0), m_zvalue(0)
			{
				m_pointsZ.clear();
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CShaleDualPorosityModelCalculator(CAccumulationElement *curElement, int activityType=CAccumulationAssessor::ST_Shale_Target_EUR_Passey,long elementid=0);
		~CShaleDualPorosityModelCalculator();

	public:
		//
		//
		unsigned int Commit(bool isDeleted = false);

		/*!
		* basic parameter
		**/
		void GetAllWellids(std::vector<long> &wellids);
		void GetAllWellidsWithoutElement(std::vector<long> &wellids);
		void LoadParameter(long wellid);
		void LoadParameterWithoutElement(long wellid);
		void LoadGeologicalParameter(long wellid,GeologicalParameter &parameter);

		//
		bool DeleteAllRockParameter(long wellid=0);
		bool ClearRockParameter(const RockEvalParameter &parameter);
		void UpdateRockParameter(const RockEvalParameter &parameter);
		void CommitRockParameter();
		void CalculateRockHCPorosity(); // �������о����л���϶��
		void CalculateRockMatrixPorosity(); // �������о����л���϶��

		void ClearLogCurve(long wellid, short curvetype);
		void UpdateLogCurve(const LogCurve &parameter);
		void CommitLogCurve();
		bool IsLogCurveExist(long wellid, short curvetype);
		LogCurve *GetLogCurve(long wellid, short curvetype);

		//
		bool DeleteAllwellParameter(long wellid=0);
		void ClearGeologicalParameter(const GeologicalParameter &parameter);
		void UpdateGeologicalParameter(const GeologicalParameter &parameter);
		bool IsGeologicalParameterExist(long wellid);	//����geological�����Ƿ��ж�Ӧ��wellid��¼
		const GeologicalParameter *GetGeologicalParameter(long wellid);
		void CommitGeologicalParameter();

		void UpdateModelParameter(const ModelParameter &parameter);
		void CommitModelParameter();

		void AddGeoparametersRecord(long newwellid);

		bool CommitBasicParameterData(  long elementid,std::vector<std::vector<string>> &basicparas,std::vector<std::vector<string>> &basiclineparas,std::vector<std::vector<string>> &basicthiparas,std::vector<std::vector<string>> &basictfparas);
		int GetBasicPracticeParaData(long practiceid,int blobtype,std::vector<std::vector<string>> &group);

		void DoGetBasicParaPracticeRecord(long elementid,long activityid,std::vector<long> &practicesids,std::vector<double> &whens);
		//
		//
		//
		/*!
		* hi-tmax plot for hydrocarbon generation model
		**/
		void GetHydrocarbonGenerationPlot(std::vector<CGeoPoint<double> > &samples);
		void FitHydrocarbonGenerationModel(short methodtype, const std::vector<CGeoPoint<double> > &samples, std::vector<CGeoPoint<double> > &line);
		double TMAX2HI(double tmax);

		void GetHydrocarbonExpulsionPlot(std::vector<CGeoPoint<double> > &samples);
		void FitHydrocarbonExpulsionModel(short methodtype, std::vector<CGeoPoint<double> > &samples, std::vector<CGeoPoint<double> > &line,bool isuseTmaxhi=false);
		void CShaleDualPorosityModelCalculator::FitHydrocarbonExpulsionModelForTocCalPanel(	short methodtype, std::vector<CGeoPoint<double> > &samples, std::vector<CGeoPoint<double> > &line, 
																							std::vector<double> &oris1,
																							std::vector<double> &oris2,
																							std::vector<double> &oritoc,
																							std::vector<double> &orihi,
																							bool isuseTmaxhi=false);
		double TMAX2F(double tmax);
		void GetApproxS1S2Toc(double hi,double &s1,double &s2,double &toc);
		void GetAutoFixedHiTmaxLine(int n, double *Tmax, double *HI, double HI0, double C, double T0, double T1,double minTmax,double maxTmax,std::vector<CGeoPoint<double> > &line,double &hi0);
		void CheckTmaxFSamples(std::vector<CGeoPoint<double> > &samples,std::vector<CGeoPoint<double> > &realsamples);
		/*!
		* toc calibrated
		**/
		void GetDepthTmaxPlot(std::vector<CGeoPoint<double> > &samples); // depth-tmax
		void FitDepthTmaxModel(const std::vector<CGeoPoint<double> > &samples, double &slope, double &intercept);

		void GetTOCVLPlot(std::vector<CGeoPoint<double> > &samples);
		void FitTOCVLModel(const std::vector<CGeoPoint<double> > &samples, double &slope, double &intercept);

		void SetPasseyMethod(short methodtype, double basevalue)
		{
			m_modelparameter.m_passey_method = methodtype;
		}
		void GetPasseyPlot(short methodtype, const LogCurve &toccurve, const LogCurve &resiscurve, const LogCurve &othercurve, std::vector<CGeoPoint<double> > &samples);
		void FitDirectPasseyModel(const std::vector<CGeoPoint<double> > &samples, double &slope, double &intercept);
		void FitRegressionPasseyModel(long wellid);

		//
		void CalculateExplainedCurve(short curvetype);	// direcly calculate all wells inside geoparameters
		void CalculatePasseyTocCurve(long wellid);	// calculate one
		void CalculateMatrixPorosityCurve(long wellid);
		void CalculateOrganicPorosityCurve(long wellid);

		/*!
		* prepare and simulation
		**/
		void GetGeoLogicalVariable(short variabletype,std::vector<CGeoPoint<double> > &samples);
		void UpdateGeologicalVariable(short variabletype, const std::vector<CGeoPoint<double> > &samples);
		void DeleteGeologicalVariable(short variabletype);		
		CAnySequentialGaussSimulator &GetSimulator(short variabletype);	// ������������
		bool MakeSimulation(int rows, int cols, int iteration);
		LogCurve *DoGetLogCurve(long wellid, short curvetype);

		bool DoGetExtentBounding(CGeoRect<double> &bounding);
		CGeoPoint<double> *DoCalcCellValue(CGeoPoint<double> *cells,int rows,int cols);

		bool CommitLogData(long wellid,std::vector<std::vector<string>> curveparas,std::vector<std::vector<string>> &layergroup,std::vector<std::vector<string>> &paragroup,
			std::vector<std::vector<string>> &toccurvedata,std::vector<std::vector<string>> &orgcurvedata);
		int GetPracticeData(long practiceid,int blobtype,std::vector<std::vector<string>> &group);

		void DoResetTocCurvebyHis(long wellid,CShaleDualPorosityModelCalculator::LogCurve *toccurve);
		void ResetOrganicPorosityCurveByhis(long wellid,LogCurve *organicCurve);
		void ResetTocPorosityCurveByhis(long wellid,LogCurve *tocCurve);

		LogCurve *DoResetExplainedCurve(const GeologicalParameter &para, short curvetype);
		void OutSetPasseyTocCurve(long wellid,std::vector<CGeoPoint<double>> &pionts);

		//Tiny Vol
		void UpdateGeologicalHookVariable(short variabletype, CAnyViewHook *hook);
		void DeleteGeologicalHookVariable(short variabletype);
		void MakeTinyVolSimulation(CAccumulationResourceManager::VolFuncRecord &VolFuncRecord);
		void DoCalculateTinyVolCenters(int order2,CAccumulationResourceManager::VolFuncRecord &VolFuncRecord,int rows, int cols, std::vector<CGeoPoint<double> > &ctlpoints,std::vector<CGeoPoint<double> > &centers,double &gridwidth,double &gridhight);
		void GetTinyVolValidCenter(std::vector<CGeoPoint<double>> &centers,std::vector<bool> &is_valid_centers,std::vector<CAccumulationResourceManager::TinyVolctlgrid> &ctlgrids,std::vector<CGeoPoint<double>> &areapts,double min,double max,int &valid_number);
		bool DoGetTinyVolExtentBounding(int order2,CAccumulationResourceManager::VolFuncRecord &VolFuncRecord,CGeoRect<double> &bounding);	
		void PrepearTinyVolSimData(std::vector<CGeoPoint<double> > &ctlpoints,std::vector<CGeoPoint<double> > &centers,CGeoRect<double> &bounding,CAccumulationResourceManager::VolFuncRecord &VolFuncRecord);
		void CalOneTinyVolResource(int itnum,int centernum,CAccumulationResourceManager::VolFuncRecord &VolFuncRecord,CAccumulationResourceManager::TinyVolResourcePredication &respredication,double p=1);
		CAnySequentialGaussSimulator &GetTinyVolSimulator(short type);
		bool IsInsideExtent(const CGeoPoint<double> &pt, const std::vector<CGeoPoint<double> > &polygon);
		void CalIntersectionPolygon(std::vector<CGeoPoint<double>> &subjectpoints,std::vector<CGeoPoint<double>> &areapoints,std::vector<CGeoPoint<double>> &resultpoints);
		void CtlpointstoCenters1(std::vector<CGeoPoint<double> > &ctlpoints,std::vector<CGeoPoint<double> > &centers,int row,int col);
		void CtlpointstoCenters2(CGeoPoint<double> *ctlpoints,std::vector<CGeoPoint<double> > &centers,int row,int col);
		void CtlpointstoCenters3(std::vector<std::vector<double> > &allsimulations,std::vector<std::vector<double> > &centersimulations,int itnum,int row,int col);
private:
		//
		void DoFitHydrocarbonGenerationModel(const std::vector<CGeoPoint<double> > &samples);
		void DoCalculateCenters(int rows, int cols, std::vector<CGeoPoint<double> > &centers);
		

		//
		
		double DoGetLogCurveValue(LogCurve *curve, double depth);
		double DoGetPasseyDeltaR(double gr, double grbase, double wave, double wavebase);
		void DoCalculateOrganicToc(short curvetype, GeologicalParameter &para);	// deprecated
		void DoCalculatePasseyToc(short curvetype, GeologicalParameter &para);
		void DoCalculateRegressionToc(GeologicalParameter &para);

		// ���Իع�
		void DoLinearRegression(double *x, double *y, int number, double &a, double &b);
		void DoCalculateBeta(double **xmatrix, double **ymatrix, double **betas, int cols, int rows);

		//
		void S1S2Simulation(int n, double *Tmax, double *s1, double *s2, double *s1s2);

		void GetValidCenter(std::vector<CGeoPoint<double> > &centers,std::vector<bool> &is_valid_centers,int &valid_number);
public:
		// data 
		VariableParameterMap m_varsamples;
		VariableSimulatorMap m_varsimulators;
		VariableHookMap		 m_variablehooks;
		


		// parameter per well
		RockParameterMap m_rockparameters;
		LogCurveMap m_logcurves;
		GeologicalParameterMap m_geoparameters;

		// 
		ModelParameter m_modelparameter;

		//
		ResourcePredicationVector m_resources;
		std::vector<CGeoPoint<double> > m_centersabudance;//����Դ���
		CAccumulationElement *m_element;
		long m_elementidx;

		std::vector<ctlgrid> m_ctlgrid;
		double m_minctlgridvalue;
		double m_maxctlgridvalue;

		int m_volcalstyle;
		int m_volcaltype;
		int m_volapptype;//0 : �ǳ��� 1�� Ȧ��
		std::vector<double> m_volcalparas;
		std::vector<CAnyViewHook *> m_volhooks;

		int m_unittype;
		double m_allarea;

		//2017/10/10: record valid cell num
		int m_valid_cell_num;

		// given geological success probability
		double m_geological_probability;
		ResourcePredicationVector m_resources_geological_probability;

	};
}

#endif
