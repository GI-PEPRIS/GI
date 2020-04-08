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
#ifndef __ANYBASIN_HYPER_BASIN_SIMULATOR_HORIZON_BATCH_SIMULATED_H__
#define __ANYBASIN_HYPER_BASIN_SIMULATOR_HORIZON_BATCH_SIMULATED_H__
//
#include "anybasin.h"
#include "anyhyperbasinbasic.h"

//
#include "any/cgal/anyhypermesh.h"
using namespace AnyCGAL;
#include "any/vis/anyburialhistoryplot.h"
using namespace AnyVis;
#include "any/gde/hugearray.h"

namespace AnyBasin
{
	// forward
	class CAnyHyperBasinSimulator;

	/*!
	*
	**/
	class CHorizonBatchSimulated
	{
	public:
		//
		CHorizonBatchSimulated()
		{
			m_is_eroded = false;
			m_thread_number = omp_get_max_threads();
			m_compresscachezip = 0;
			m_compresscachezipisok = 0;
			m_compresscacheziplen = 0;
			m_compresscacheunziplen = 0;
			m_compresscachezip_mini = 0;
			m_compresscachezipisok_mini = 0;
			m_compresscacheziplen_mini = 0;
			m_compresscacheunziplen_mini = 0;
		}
		~CHorizonBatchSimulated()
		{
			for(int i = 0; i < m_bottom_vertexes_simulated.size(); i++)
			{
				delete m_bottom_vertexes_simulated[i];
			}
			m_bottom_vertexes_simulated.clear();
			m_top_vertexes_simulated.clear();
			for(int i = 0; i < m_meshes_simulated.size(); i++)
			{
				delete m_meshes_simulated[i];
			}
			m_meshes_simulated.clear();
			::free(m_compresscachezip);
			m_compresscachezip = 0;
			m_compresscachezipisok = 0;
			m_compresscacheziplen = 0;
			m_compresscacheunziplen = 0;
			::free(m_compresscachezip_mini);
			m_compresscachezip_mini = 0;
			m_compresscachezipisok_mini = 0;
			m_compresscacheziplen_mini = 0;
			m_compresscacheunziplen_mini = 0;
		}
		VertexSimulated* GetBottomVertex(int offset)
		{
			if(m_bottom_vertexes_simulated.size() <= offset)
				return 0;
			return (VertexSimulated*)(m_bottom_vertexes_simulated[offset]);
		}
		VertexSimulated* GetTopVertex(int offset)
		{
			if(m_top_vertexes_simulated.size() <= offset)
				return 0;
			return (VertexSimulated*)(m_top_vertexes_simulated[offset]);
		}
		MeshSimulated* GetMesh(int offset)
		{
			if(m_meshes_simulated.size() <= offset)
				return 0;
			return (MeshSimulated*)(m_meshes_simulated[offset]);
		}
		CHorizonBatchSimulated(const CHorizonBatchSimulated &other)
		{
			*this = other;
		}
		const CHorizonBatchSimulated &operator=(const CHorizonBatchSimulated &other)
		{
			if(this != &other)
			{
				m_simulator = other.m_simulator;
				m_layer_idx = other.m_layer_idx;
				m_horizon_idx = other.m_horizon_idx;
				m_geological_event = other.m_geological_event;
				m_is_eroded = other.m_is_eroded;

				m_end_point = other.m_end_point;

				m_initial_vertex_batch = other.m_initial_vertex_batch;
				m_initial_mesh_batch = other.m_initial_mesh_batch;
				for(int i = 0; i < m_bottom_vertexes_simulated.size(); i++)
				{
					delete m_bottom_vertexes_simulated[i];
				}
				m_bottom_vertexes_simulated.clear();
				m_top_vertexes_simulated.clear();
				for(int i = 0; i < m_meshes_simulated.size(); i++)
				{
					delete m_meshes_simulated[i];
				}
				m_meshes_simulated.clear();
				for(int i = 0; i < other.m_bottom_vertexes_simulated.size(); i++)
				{
					VertexSimulated *vertexsimulated = new VertexSimulated;
					*vertexsimulated = *((VertexSimulated *)other.m_bottom_vertexes_simulated[i]);
					m_bottom_vertexes_simulated.push_back(vertexsimulated);
				}
				m_top_vertexes_simulated = other.m_top_vertexes_simulated;
				for(int i = 0; i < other.m_meshes_simulated.size(); i++)
				{
					MeshSimulated *meshsimulated = new MeshSimulated;
					*meshsimulated = *((MeshSimulated*)(other.m_meshes_simulated[i]));
					m_meshes_simulated.push_back(meshsimulated);
				}
				::free(m_compresscachezip);
				m_compresscachezip = (char*)(::malloc(other.m_compresscacheziplen));
				memcpy(m_compresscachezip, other.m_compresscachezip, other.m_compresscacheziplen);
				m_compresscachezipisok = other.m_compresscachezipisok;
				m_compresscacheziplen = other.m_compresscacheziplen;
				m_compresscacheunziplen = other.m_compresscacheunziplen;
			}
			return *this;
		}

	public:
		//
		void SetSimulator(CAnyHyperBasinSimulator *simulator)
		{
			m_simulator = simulator;
		}
		//
		//
		//
		bool GetLithology(const std::string &lithname, CAnyBurialHistoryPlot::GeologicalLithologyMap &lithmap, CAnyBurialHistoryPlot::GeologicalLithology &lithology);
		void InitFaceDefinitionData(std::vector<string> &face_definition_names, FaceDefinitions &face_definitions, CAnyBurialHistoryPlot::GeologicalLithologyMap &lithmap);
		void InitMaxBuryDepthData(); // the deepest horizon of current layer and its matrix-related variables
		void InitGeologicalAgeData(std::vector<double> &depositionvelocities);	
		void InitBorderData();
		void InitRockSourceData();
		void InitOpenBoundary(bool isopenboundary);
		void GetMeshShape(MeshSimulated *curmesh);
		void ModifyVertexColor(int colorsource, int bottomortop);
		double GetVertexColor(int colorsource, VertexSimulated *curvertex);

		//
		//
		// steady heat simulaiton
		void GetIfItIsTheTopestStrSeg(); 
		void GetFromNearbyStrSeg(CHorizonBatchSimulated &lefthorizonsimulated, CHorizonBatchSimulated &tophorizonsimulated);

		//
		//
		// transit heat simulation
		void GetIfItIsTheTopestStrSegPart01();
		void GetFromNearbyStrSegPart01(CHorizonBatchSimulated &lefthorizonsimulated, CHorizonBatchSimulated &tophorizonsimulated);

		//
		void GetT() ;  //GetT()函数中有热导率计算过程
		void GetTotalDensity(); //这里包含了静水压力和水密度的计算
		void GetTotalHeatCapacity();   //由于第一个StrSeg采用稳态热传导求解温度，比热容实际上在这里没有实际用处，只是将其计算出来
		void GetQr();

		//
		void GetTotalThermalCond();
		void GetTotalDensity(CHorizonBatchSimulated &lefthorizonsimulated, CHorizonBatchSimulated &tophorizonsimulated); //
		
		void SetFluidPressureIfItIsTheTopestStrSeg();
		void SetFluidPressure(CHorizonBatchSimulated &tophorizon);

		void CalcuWaterDensityAndStaticPressure();
		void CalcuWaterDensityAndStaticPressure(CHorizonBatchSimulated &lefthorizonsimulated, CHorizonBatchSimulated &tophorizonsimulated);

		void GetIfItIsTheTopestStrSegPart02(); 
		void GetFromNearbyStrSegPart02(CHorizonBatchSimulated &lefthorizonsimulated, CHorizonBatchSimulated &tophorizonsimulated);

		//
		// overpressure
		//
		void GetErosionThickness01(CHorizonBatchSimulated &virtualhorizon);
		void GetIfItIsTheTopestStrSegOP01();
		void GetFromNearbyStrSegOP01(CHorizonBatchSimulated &lefthorizonsimulated, CHorizonBatchSimulated &tophorizonsimulated);
		void RealThicknessCalculating();

		void GetParaOfOverpressureEquation();
		void GetParaOfOverpressureEquation(CHorizonBatchSimulated &lefthorizonsimulated, CHorizonBatchSimulated &tophorizonsimulated);
		void GetvWater();
		void GetStaticPAndPlOfTheFirstStrSeg();
		void GetStaticPAndPlOfTheSecondStrSeg(CHorizonBatchSimulated &lefthorizonsimulated, CHorizonBatchSimulated &tophorizonsimulated);

		void GetMatrixThicknessInTheEnd();
		double DifferencePoromEndPorom(CHorizonBatchSimulated &thefirsthorizonsimulated);
		void CalculateRockSourceResult(CHorizonBatchSimulated &endhorizonsimulated, CHorizonBatchSimulated &lefthorizonsimulated, int k, int bachespercurrentstep);

	private:
		//
		double DoGetMatrixThickness(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		double DoGetCurrentPorosity(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		double DoGetMatrixDensity(MeshSimulated *curmesh,VertexSimulated *bottomvertex);
		double DoGetMatrixThermalCond(MeshSimulated *curmesh);
		double DoGetMatrixHeatCapacity(MeshSimulated *curmesh, VertexSimulated *curvertex);

		double DoGetBuryBottomDepth(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		double DoGetPorosity(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		double DoGetPerm_Anisotr(MeshSimulated *curmesh, VertexSimulated *vertex);
		double DoGetPermeability(MeshSimulated *curmesh, VertexSimulated *vertex);
		double DoGetT(MeshSimulated *curmesh, VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		double DoGetT(MeshSimulated *curmesh, VertexSimulated *curvertex, VertexSimulated *leftbottomvertex, VertexSimulated *topbottomvertex);
		double DoGetTm(MeshSimulated *curmesh);

		double DoGetTotalThermalCond(MeshSimulated *curmesh, double Tm);
		double DoGetPoreFluidThermalCond(MeshSimulated *curmesh, double Tm);
		double DoGetWaterThermalCond(MeshSimulated *curmesh, double Tm);
		double DoGetOilThermalCond(MeshSimulated *curmesh, double Tm);
		double DoGetGasThermalCond(MeshSimulated *curmesh, double Tm);
		double DoGetIceThermalCond(MeshSimulated *curmesh);
		double DoGetGasHydratesThermalCond(MeshSimulated *curmesh);
		double DoGetThermalCondAnisotr(MeshSimulated *curmesh);

		//
		double DoPorosityToDepthExpDivByComp(double InitPoro, double CompF,double Depth);
		void DoGetBorderData(short bordertype, VertexSimulated *curvertex);

		//
		void DoGetIfItIsTheTopestStrSeg(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGetFromNearbyStrSeg(MeshSimulated *curmesh, MeshSimulated *leftmesh, MeshSimulated *topmesh, \
			bool leftmesheroded, VertexSimulated *topvertex, VertexSimulated *bottomvertex,\
			VertexSimulated *lefttopvertex, VertexSimulated *leftbottomvertex,\
			VertexSimulated *toptopvertex, VertexSimulated *topbottomvertex);

		//
		void DoGetIfItIsTheTopestStrSegPart01(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGetFromNearbyStrSegPart01(MeshSimulated *curmesh, MeshSimulated *leftmesh, MeshSimulated *topmesh, \
			bool leftmesheroded, VertexSimulated *topvertex, VertexSimulated *bottomvertex,\
			VertexSimulated *lefttopvertex, VertexSimulated *leftbottomvertex,\
			VertexSimulated *toptopvertex, VertexSimulated *topbottomvertex);
		void DoGetIfItIsTheTopestStrSegPart02(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGetFromNearbyStrSegPart02(MeshSimulated *curmesh, MeshSimulated *leftmesh, MeshSimulated *topmesh, \
			bool leftmesheroded, VertexSimulated *topvertex, VertexSimulated *bottomvertex,\
			VertexSimulated *lefttopvertex, VertexSimulated *leftbottomvertex,\
			VertexSimulated *toptopvertex, VertexSimulated *topbottomvertex);
	
		void DoCalcuWaterDensityAndStaticPressure(MeshSimulated *curmesh,VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoCalculateWaterDensityAndStaticPressure(MeshSimulated *curmesh,VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		double DoGetStaticPressure(MeshSimulated *curmesh,VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		double DoGetWaterDensity(MeshSimulated *curmesh,VertexSimulated *vertex);

		void DoCalculateWaterDensityAndStaticPressure(MeshSimulated *curmesh, VertexSimulated *topbottomvertex,VertexSimulated *lefttopvertex,VertexSimulated *leftbottomvertex,VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		void DoCalcuWaterDensityAndStaticPressure(MeshSimulated *curmesh,VertexSimulated *topbottomvertex,VertexSimulated *lefttopvertex,VertexSimulated *leftbottomvertex,VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		double DoGetStaticPressure(MeshSimulated *curmesh,VertexSimulated  *topbottomvertex,VertexSimulated *lefttopvertex,VertexSimulated *leftbottomvertex,VertexSimulated *topvertex,VertexSimulated *bottomvertex);

		void DoGetStaticPAboveSeaLevel(MeshSimulated *curmesh,VertexSimulated *curvertex);
		void DoGetStaticU(MeshSimulated *curmesh,VertexSimulated *topvertex, VertexSimulated *bottomvertex);

		double DoGetPoreFluidHeatCapacity(MeshSimulated *curmesh,VertexSimulated *curtex);
		double DoGetWaterHeatCapacity(MeshSimulated *curmesh,VertexSimulated *curtex);
		double DoGetOilHeatCapacity(MeshSimulated *curmesh,VertexSimulated *curtex);
		double DoGetGasHeatCapacity(MeshSimulated *curmesh,VertexSimulated *curtex);
		double DoGetIceHeatCapactiy(MeshSimulated *curmesh,VertexSimulated *curtex);
		double DoGetGasHydratesHeatCapactiy(MeshSimulated *curmesh,VertexSimulated *curtex);

		void DoGetQr(MeshSimulated *curmesh);

		//
		// overpressure
		void DoGetIfItIsTheTopestStrSegOP01(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGetStaticPAndPlOfTheFirstStrSeg(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGetFromNearbyStrSegOP01(MeshSimulated *curmesh, MeshSimulated *leftmesh, MeshSimulated *topmesh, \
			bool leftmesheroded, VertexSimulated *topvertex, VertexSimulated *bottomvertex,\
			VertexSimulated *lefttopvertex, VertexSimulated *leftbottomvertex,\
			VertexSimulated *toptopvertex, VertexSimulated *topbottomvertex);
		void DoRealThicknessCalculating(MeshSimulated *curmesh,VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		void DoGetPoroFromEffectiveStress(MeshSimulated *curmesh,VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		void DoGetThickness(MeshSimulated *curmesh,VertexSimulated *curvertex);
		void DoGetDepths(MeshSimulated *curmesh,VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		void DoGetDepths(MeshSimulated *curmesh,VertexSimulated *lefttopvertex, VertexSimulated *leftbottomvertex,\
			VertexSimulated *toptopvertex, VertexSimulated *topbottomvertex, \
			VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		void DoGetUl(MeshSimulated *curmesh,VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		void DoGetEffectiveStress(MeshSimulated *curmesh,VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		void DoGetPl(MeshSimulated *curmesh,VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		double DoGetRand(double a, double b);
		void DoGetTotalHeatCapacity(MeshSimulated *curmesh,VertexSimulated *curvertex);

		double DoGetPermeabilityFromPorosity(double aPorosity,int NumPoroPermPairs,std::vector<double>&LogPerms,std::vector<double>&Poros);
		double DoLinerInterpolate(double t,double t0,double p0,double t1,double p1);

		void DoGetParaOfOverpressureEquation(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGetCOC(MeshSimulated *curmesh, VertexSimulated *bottomvertex);
		void DoGetWaterViscosity(MeshSimulated *curmesh, VertexSimulated *bottomvertex);
		void DoGetParaOfOverpressureEquation(MeshSimulated *curmesh,MeshSimulated *leftmesh,\
			VertexSimulated *topvertex, VertexSimulated *bottomvertex, \
			VertexSimulated *lefttopvertex, VertexSimulated *leftbottomvertex, VertexSimulated *toptopvertex, VertexSimulated *topbottomvertex);
		void DoGetPoroFromEffectiveStress(MeshSimulated *curmesh,MeshSimulated *leftmesh,\
			VertexSimulated *topvertex,VertexSimulated *bottomvertex,\
			VertexSimulated *lefttopvertex,VertexSimulated *leftbottomvertex,VertexSimulated *toptopvertex, VertexSimulated *topbottomvertex);
		void DoGetUl(MeshSimulated *curmesh,VertexSimulated *topbottomvertex,VertexSimulated *lefttopvertex,VertexSimulated *leftbottomvertex,VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		void DoGetTotalDensity(MeshSimulated *curmesh,VertexSimulated *topbottomvertex,VertexSimulated *lefttopvertex,VertexSimulated *leftbottomvertex,VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		void DoGetPl(MeshSimulated *curmesh,VertexSimulated *topbottomvertex,VertexSimulated *topvertex,VertexSimulated *bottomvertex);
		void DoGetStaticPAndPlOfTheSecondStrSeg(MeshSimulated *curmesh,VertexSimulated *topvertex, VertexSimulated *bottomvertex, \
			VertexSimulated *lefttopvertex, VertexSimulated *leftbottomvertex, \
			VertexSimulated *toptopvertex, VertexSimulated *topbottomvertex);

		// 排烃
		void DoGetaG(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetGeneratedOilAndGas(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetMAdxAndExpOfOilAndGas(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetGeneratedOilAndGas(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *leftmesh, VertexSimulated *leftvertex);
		void DoGetMAdxAndExpOfOilAndGas(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *leftmesh, VertexSimulated *leftvertex);
		void DoGetZeroOilAndGas(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void OilCrackingInRockPoros(VertexSimulated *curvertex, VertexSimulated *topvertex, VertexSimulated *leftRvertex, VertexSimulated *rightvertex, VertexSimulated *frontvertex, \
			VertexSimulated *backvertex, VertexSimulated *bottomvertex);
		void OilCrackingInRockPoros(VertexSimulated *curvertex, VertexSimulated *leftbottomvertex, VertexSimulated *topvertex, VertexSimulated *leftRvertex, VertexSimulated *rightvertex, \
			VertexSimulated *frontvertex, VertexSimulated *backvertex, VertexSimulated *bottomvertex);
		void OilCrackingInRockPoros(VertexSimulated *curvertex, VertexSimulated *leftvertex);
		// 赋值和计算
		double DoReturnMin(double x1,double x2,double x3);
		double DoReturnMax(double x1,double x2,double x3);
		SolutionOfCE DoCubicEquation(double a,double b,double c,double d);
		void DoGetGroupkij(int NCom,std::vector<std::vector<double> >&kij,std::vector<std::vector<double> >&GasOilkij,std::vector<PropertiesVariable> &aProperties);
		double DoGetVOfRRE(int NCom,std::vector<double>&z,std::vector<double>&K, double aPoint);
		void DoGetaEOSParas(double &aa,double &bb,double &cc,double &dd,double A,double B,int aEOS);
		void DoGetFaii(int NCom,int aEOS,std::vector<double>&Faii,std::vector<double>&ai,std::vector<double>&bi,std::vector<double>&x,double a,double b,std::vector<std::vector<double> >&kij,double A,double B,double Z);
		void DoGetfi_K(int NCom,std::vector<double>&fiL,std::vector<double>&fiV,std::vector<double>&FaiiL,std::vector<double>&FaiiV,std::vector<double>&K,std::vector<double>&x,std::vector<double>&y,double Pm);
		void DoGetErrorValue_fiLfiV(double &ErrorValue_fiLfiV,int NCom,std::vector<double>&fiL,std::vector<double>&fiV);
		void DoBubblePressureAdjusted(int NCom,double &Pm,std::vector<double>&x,std::vector<double>&K);
		void DoDewPressureAdjusted(int NCom,double &Pm,std::vector<double>&y,std::vector<double>&K);
		void DoGetvLvV(double &vL,double &vV,double R,double Tm,double ZL,double ZV,double Pm );
		void DoGetMWLMWV(int NCom,double &MWL,double &MWV,std::vector<double>&MW,std::vector<double>&x,std::vector<double>&y);
		void DoGetLVDensity(double &OilDensity, double &GasDensity, double vL,double vV,double MWL,double MWV);
		void DoGetpTcpPc(int NCom,std::vector<double>&xi,std::vector<std::vector<double>>&kij,std::vector<double>&Tci,std::vector<double>&pci, std::vector<double>&Omegai,double R,\
			double &a,double &b,std::vector<double>&aci,std::vector<double>&bi,std::vector<double>&mi,std::vector<double>&Alphai, std::vector<double>&ai,double &pTc,double &pPc,int aEOS);
		double Dorrand();
		double DoGetRand();
		double DoGetRand0_1();
		double DoRandomRange( double b);
		template <class T> T DoReturnMaxValue(T Array[],int n);

		// 相态
		void DoGetMolFraC1InWater(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetProperties(MeshSimulated *curmesh, VertexSimulated *curvertex, int aNCom,std::vector<PropertiesVariable> &aProperties,std::vector<std::vector<double> > &akij,int aaEOS);
		void DoGetProperties(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetpTcpPc(MeshSimulated *curmesh, VertexSimulated *curvertex);
		double DoGetVOfRRE(MeshSimulated *curmesh, VertexSimulated *curvertex, double aPoint);
		void DoGetInitKi(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetParasOfComsInEOS(MeshSimulated *curmesh, VertexSimulated *curvertex, std::vector<double>&xi,double &aLV,double &bLV);
		void DoGetaEOSParas(MeshSimulated *curmesh, VertexSimulated *curvertex, double &aa,double &bb,double &cc,double &dd,double A,double B);
		void DoGetFaii(MeshSimulated *curmesh, VertexSimulated *curvertex, std::vector<double>&Faii,std::vector<double>&xx,double aLV,double bLV,double A,double B,double Z);
		void DoGetfi_K(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetfi_KSC(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetErrorValue_fiLfiV(MeshSimulated *curmesh, VertexSimulated *curvertex, double &ErrorValue_fiLfiV);
		void DoBubblePressureAdjusted(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetvLvV(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetvLvVSC(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetMWLMWV(MeshSimulated *curmesh, VertexSimulated *curvertex, std::vector<double>&xx,std::vector<double>&yy);
		void DoGetMWLMWVSC(MeshSimulated *curmesh, VertexSimulated *curvertex, std::vector<double>&xx,std::vector<double>&yy);
		void DoGetLVDensity(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetLVDensitySC(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetLDensity(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetLDensitySC(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetVDensity(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetVDensitySC(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetBubblePointPressure(MeshSimulated *curmesh, VertexSimulated *curvertex);
		double DoNewtonIterationFornv(MeshSimulated *curmesh, VertexSimulated *curvertex, double aPoint);
		void DoGetInitKi(int NCom,std::vector<double>&KK, std::vector<double>&Pci,double Pmm, std::vector<double>&Omegai,std::vector<double>&Tci,double Tmm);
		void DoGetParasOfComsInEOS(int NCom,std::vector<double>&xiI,std::vector<std::vector<double> >&kij,std::vector<double>&Tci,std::vector<double>&pci, \
			double TmM,double PmM,std::vector<double>&Omegai,double R,double &a,double &b,std::vector<double>&aci,std::vector<double>&bi,std::vector<double>&mi,std::vector<double>&Alphai, std::vector<double>&ai,\
			std::vector<double>&Ai,std::vector<double>&Bi,int aEOS);
		double DoNewtonIterationFornv(int NCom1,std::vector<double>&zZ,std::vector<double>&KK, double aPoint);
		void DoGetGOR(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetBo(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoFlashCalculationSC(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoFlashCalculation(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoFlashCalculation(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *leftmesh, VertexSimulated *leftvertex);

		// 粘度、相对渗透率、界面张力、毛管压力
		void DoGetSe(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetKrwKrow(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetKrwKrg(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetKrgKrog(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetKr(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetTcVc(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetTcLTcV(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetRouMLRouMV(MeshSimulated *curmesh, VertexSimulated *curvertex);
		//void DoGetIFTOilAndWater(MeshSimulated *curmesh, VertexSimulated *curvertex);
		//void DoGetIFTGasAndWater(MeshSimulated *curmesh, VertexSimulated *curvertex);
		//void DoGetPXigema(MeshSimulated *curmesh, VertexSimulated *curvertex);
		//void DoGetIFTGasOil(MeshSimulated *curmesh, VertexSimulated *curvertex);
		//void DoGetIFT(MeshSimulated *curmesh, VertexSimulated *curvertex);
		//void DoGetPcbMA(MeshSimulated *curmesh, VertexSimulated *curvertex);
		//void DoGetPcb(MeshSimulated *curmesh, VertexSimulated *curvertex);
		//void DoGetPc(MeshSimulated *curmesh, VertexSimulated *curvertex, VertexSimulated *leftvertex);
		void DoGetTcL(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetTcV(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetIFTOilAndWater(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetIFTGasAndWater(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetPXigema(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetIFTGasOil(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetIFT(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetPcbMA(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetPcOW(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetPcGW(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetPcGO(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetPc(MeshSimulated *curmesh, VertexSimulated *curvertex);

		void DoGetVCell(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetVP(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetSo(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetSg(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetSw(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetVOil(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetVGas(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetVOilGas(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetPo(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetSoSgSw(MeshSimulated *curmesh, VertexSimulated *curvertex);
		double DoGetOWBDNearbyStrSeg(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *Nearbymesh, VertexSimulated *Nearbyvertex);
		double DoGetGWBDNearbyStrSeg(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *Nearbymesh, VertexSimulated *Nearbyvertex);
		double DoGetGOBDNearbyStrSeg(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *Nearbymesh, VertexSimulated *Nearbyvertex);
		void DoGetLVMass(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetLVMass0(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetKrPc(MeshSimulated *curmesh, VertexSimulated *curvertex, VertexSimulated *leftvertex);
		void DoGetViscosityKrPc(MeshSimulated *curmesh, VertexSimulated *curvertex, VertexSimulated *leftvertex);
		void DoGetWaterViscosity1(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetOilGasViscosity(MeshSimulated *curmesh, VertexSimulated *curvertex);
		// 新加入的
		void DoGainHCGIPerUnitInitTOC(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *leftmesh, VertexSimulated *leftvertex);
		void DoGainHCGIPerUnitInitTOC(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoSourceRockRelated(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoSourceRockRelated(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *leftmesh, VertexSimulated *leftvertex);
		void DoSetToItsOrifOilToGas(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGainInitTOC(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetHCGIPerUnitInitTOC(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *leftmesh, VertexSimulated *leftvertex);
		void DoGetHCGIPerUnitInitTOC(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetInitTOC(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetTTI(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *leftmesh, VertexSimulated *leftvertex);
		void DoGetTTI(MeshSimulated *curmesh, VertexSimulated *curvertex);

		void DoGetRo(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *leftmesh, VertexSimulated *leftvertex);
		void DoGetRo(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetRoFromEasyRo(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *leftmesh, VertexSimulated *leftvertex);
		void DoGetRoFromEasyRo(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetRoFromBasinRo(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *leftmesh, VertexSimulated *leftvertex);
		void DoGetRoFromBasinRo(MeshSimulated *curmesh, VertexSimulated *curvertex);
		void DoGetRoFromSimpleRo(MeshSimulated *curmesh, VertexSimulated *curvertex, MeshSimulated *leftmesh, VertexSimulated *leftvertex);
		void DoGetRoFromSimpleRo(MeshSimulated *curmesh, VertexSimulated *curvertex);
		double DoEasyRo(double TLast, double tLast, double T, double t,int NN,std::vector<double>&f,std::vector<double>&E,double A,double Roo,double f0 );
		double DoSimpleRo(double TLast, double tLast, double T, double t,double &f,double aerf,double beita,double A,double Roo, double f0);

		//
		void DoGetTTI(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		double DoTTIF(double TLast, double tLast, double T, double t,double LastTMax,double TTILast);

		void DoGetRo(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGetRoFromEasyRo(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGetRoFromBasinRo(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGetRoFromSimpleRo(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGetHCGIPerUnitInitTOC(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGetInitTOC(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGainHCGIPerUnitInitTOC(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);
		void DoGainInitTOC(MeshSimulated *curmesh, VertexSimulated *topvertex, VertexSimulated *bottomvertex);

		//
		void DoGetTmax(VertexSimulated *leftbottomvertex, VertexSimulated *bottomvertex, VertexSimulated *topvertex);
		void DoGetTTI(VertexSimulated *leftbottomvertex, VertexSimulated *bottomvertex);
		void DoGetRo(VertexSimulated *leftbottomvertex, VertexSimulated *bottomvertex);
		void DoGetRoFromEasyRo(VertexSimulated *leftbottomvertex, VertexSimulated *bottomvertex);
		void DoGetRoFromBasinRo(VertexSimulated *leftbottomvertex, VertexSimulated *bottomvertex);
		void DoGetRoFromSimpleRo(VertexSimulated *leftbottomvertex, VertexSimulated *bottomvertex);
		void DoGetHCGIPerUnitInitTOC(VertexSimulated *leftbottomvertex, VertexSimulated *bottomvertex);
		void DoGainHCGIPerUnitInitTOC(MeshSimulated *curmesh,bool leftmesheroded,VertexSimulated *leftbottomvertex, VertexSimulated *bottomvertex);

		//以下为渝渗相关函数=======================================================================
		double GetSgOfaSS2ToPcbOfaSS1(double Pcb1,double Pcb2,double BD,double lamuda2);
		double GetSgOfaSS1ToPcbOfaSS2(double Pcb2,double Pcb1,double BD,double lamuda1);
		void GetSoOfSS1SS2Case0(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double aSS2So);
		void GetSoOfSS1SS2Case1(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double aSS1So);
		double FunDivWaterOil(double So1,MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double BDOW,double TotalVOil);
		void GetSoDichotomyWaterOil(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double BDOW,double TotalVOil);
		void GetSoOfSS1SS2Case2(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double BDOW);
		void GetParasOfSS1SS2Case0_1_2OnlyGas(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2);
		double FunDivOilGas(double Sg1,MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double BDGO,double TotalVGas);
		void GetSgDichotomyOilGas(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double BDGO,double TotalVGas);
		void GetSgOfSS1SS2Case3_4_5(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double BDGO);
		double FunDivOnlyGas(double Sg1,MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double BDGW,double TotalVGas);
		void GetSgDichotomyOnlyGas(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double BDGW,double TotalVGas);
		void GetSgOfSS1SS2Case3_4_5OnlyGas(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double BDGW);
		void GetSoOfSS1SS2Case3(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double aSS2So);
		void GetSoOfSS1SS2Case4(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double aSS1So);
		void GetSoOfSS1SS2Case5(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double BDOW);
		void ReBalanceOil(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double OriaSS1VGas);
		void PreTreat01(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2);
		void PreTreat02(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2,double BDGO);
		void ReAssignmentOilandGas(MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2);
		void BalanceTwoCells(MeshSimulated *aSSmesh,VertexSimulated *aSS,MeshSimulated *aSS1mesh,VertexSimulated *aSS1,MeshSimulated *aSS2mesh,VertexSimulated *aSS2);
		void CopyfOilToGasFrom(MeshSimulated *aSSOnemesh,VertexSimulated *aSSOne,std::vector<double> &fOilToGas,int NOilToGas);
		void GetAveragefOilToGas(std::vector<VertexSimulated*> &aSSs, std::vector<MeshSimulated*> &aSSmeshs);
		void BalanceForNeighbors3D(std::vector<VertexSimulated*> &aSSs, std::vector<MeshSimulated*> &aSSmeshs) ;
		void SearchForOnePcCycle3D(std::vector<std::vector<std::vector<MeshSimulated*> > > &aSSmesh,std::vector<std::vector<std::vector<VertexSimulated*> > > &aSS,int NRow,int NCol,int NZ);
	public:
		void Percolating3D(std::vector<std::vector<std::vector<MeshSimulated*> > > &aSSmesh,std::vector<std::vector<std::vector<VertexSimulated*> > > &aSS,int NRow,int NCol,int NZ);
		void CheckData(MeshSimulated* aSSmesh, VertexSimulated* aSS);
	public:
		//
		CAnyHyperBasinSimulator *m_simulator;

		// meta info
		int m_layer_idx;
		int m_horizon_idx;
		int m_geological_event;
		bool m_is_eroded;
		int m_face_map_idx; // to get litho info

		//记录最后一个点的时间坐标
		int m_current_layer;
		int m_current_horizon;
		int m_current_time_step;
		int m_end_point;
		
		//
		int m_connect_marker;
		int m_horizon_virtual_idx;

		// iterator, the same as m_initial_meshes
		IsoMeshBatch m_initial_mesh_batch;
		IsoVertexBatch m_initial_vertex_batch;

		// vertex data
		VertexContainer m_bottom_vertexes_simulated;
		VertexContainer m_top_vertexes_simulated;

		// mesh data
		MeshContainer m_meshes_simulated;

		char* m_compresscachezip;
		int m_compresscachezipisok;
		int m_compresscacheziplen;
		int m_compresscacheunziplen;

		char* m_compresscachezip_mini;
		int m_compresscachezipisok_mini;
		int m_compresscacheziplen_mini;
		int m_compresscacheunziplen_mini;

		// for openmp
		int m_thread_number;
	};
}


#endif