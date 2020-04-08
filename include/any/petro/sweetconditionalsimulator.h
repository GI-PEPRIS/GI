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
#ifndef __ANYPETRO_SWEET_CONDITIONAL_SIMULATOR_H__
#define __ANYPETRO_SWEET_CONDITIONAL_SIMULATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"
// refer to its parent
#include "accumulationassessor.h"

//
#include "any/thread/task.h"

//
#include "any/base/anygeom.h"
using namespace AnyBase;

#include "any/math/anyconditionalsimulator.h"
using namespace AnyMath;
#include "any/vis/anycontour.h"
using namespace AnyVis;

#include "any/base/loki/visitor.h"
using namespace AnyBase::Loki;

//
namespace AnyPetro
{
	class ANYPETRO_CLASS CSweetConditionalSimulator : public CAccumulationAssessor, public CAnyConditionalSimulator, public BaseVisitable<>
	{
	public:
		//
		LOKI_DEFINE_VISITABLE()

		/*!
		*
		**/
		struct VarianceCalculationParameter
		{
			long m_elementid;

			// cube extent
			double m_minX;
			double m_maxX;
			double m_minY;
			double m_maxY;
			double m_minZ;
			double m_maxZ;

			// basic
			double *m_x;
			double *m_y;
			double *m_z;
			double *m_v;
			int m_n;
			double m_dirP[3];
			double m_H0[3];
			int m_nH[3];
			double m_origin[3];
			double m_HTolerate;
			double m_dirTolerate;
			ExperimentalVariogram_Structure **m_2dEvs;
			ExperimentalVariogram_Structure ***m_3dEvs;

			ExperimentalVariogram_Structure ***m_Ori3dEvs;
			ExperimentalVariogram_Structure **m_Ori2dEvs;

			// for interpolation
			double m_a; 
			double m_C0;
			double m_C;
			double m_dhx;
			double m_dhy;
			double m_dhz;
			double m_IR;//m_interR=sqrt(75.0);
			double m_IA;//m_interstep=10;
			double m_interdirection;
			
			int		m_simtype;
			AnyVis::CAnyContour *m_primaryHook;
			AnyVis::CAnyContour *m_secondrayHook;
			AnyVis::CAnyContour *m_thirdHook;
			int		m_covaricetype;
			int		m_computetype;
			bool   m_isRanddomdir;
			int    m_Randomdirnum;
			int m_intertype;
			int m_interisotype;
			int m_interspheretype;

			int m_quantile;

			//kringgrid 插值
			double ***m_kringGrid;
			int m_kringnH[3];

			//普通插值
			int    m_dataintertype;//克里金或普通插值
			int    m_usenum;
			double m_iterationprec;
			int    m_iterationnum;
			double ***m_Grid;
			int m_genalnH[3];

			//模拟
			complex<double> ***m_S;
			bool   m_isusefusiondata;//是否使用融合数据
			bool   m_isuseconditiondata;//是否使用条件数据

			VarianceCalculationParameter() : m_elementid(0),m_simtype(1),m_x(0), m_y(0), m_z(0), m_v(0), m_n(0),  m_HTolerate(0), m_dirTolerate(0), \
				m_a(0), m_C0(0), m_C(0), m_dhx(1), m_dhy(1), m_dhz(1),m_isRanddomdir(false),m_Randomdirnum(8)
			{
				//m_nH(0), m_2d(0), m_3d(0), m_IR(0.), m_IA(0.)m_dirP(0), m_H0(0),
				m_2dEvs=0;
				m_3dEvs=0;
				//m_Ori3dEvs=0;
				//m_Ori2dEvs=0;
				m_primaryHook=0;
				m_secondrayHook=0;
				m_simtype=0;
				m_nH[0]=16;m_nH[1]=16;m_nH[2]=16;

				m_dirP[0]=1;m_dirP[1]=1;m_dirP[2]=1;
				m_H0[0]=5;m_H0[1]=5;m_H0[2]=5;
				m_origin[0]=0;m_origin[1]=0;m_origin[2]=0;

				m_dirTolerate = 10;
				m_HTolerate=10;
				m_covaricetype=1;
				m_computetype=0;

				m_intertype =0;
				m_interisotype=0;
				m_interspheretype=0;
				m_interdirection=10;
				m_IR=sqrt(75.0);
				m_IA=10;
				m_quantile=50;
				m_dataintertype=1;
				
				m_Grid=0;
				m_S=0;
				m_usenum=10;
				m_iterationprec=0.1;
				m_iterationnum=1000;
				m_isusefusiondata=true;
				m_isuseconditiondata=true;

				m_kringGrid=0;
				m_kringnH[0]=0;m_kringnH[1]=0;m_kringnH[2]=0;
				m_genalnH[0]=0;m_genalnH[1]=0;m_genalnH[2]=0;
				
			}

			void Release()
			{
				m_elementid=0;
				m_simtype=1;
				m_x=0;m_y=0; m_z=0;m_v=0;m_n=0;m_HTolerate=0;m_dirTolerate=0;
				m_a=0;m_C0=0;m_C=0;m_dhx=1;m_dhy=1;m_dhz=1;m_isRanddomdir=false;m_Randomdirnum=8;
				m_2dEvs=0;
				m_3dEvs=0;
				//m_Ori3dEvs=0;
				//m_Ori2dEvs=0;
				m_primaryHook=0;
				m_secondrayHook=0;
				m_thirdHook=0;
				m_simtype=0;
				

				m_dirP[0]=1;m_dirP[1]=1;m_dirP[2]=1;
				m_H0[0]=5;m_H0[1]=5;m_H0[2]=5;
				m_origin[0]=0;m_origin[1]=0;m_origin[2]=0;

				m_dirTolerate = 10;
				m_HTolerate=10;
				m_covaricetype=1;
				m_computetype=0;

				m_intertype =0;
				m_interisotype=0;
				m_interspheretype=0;
				m_interdirection=10;
				m_IR=sqrt(75.0);
				m_IA=10;
				m_quantile=50;
				m_dataintertype=1;

				m_usenum=10;
				m_iterationprec=0.1;
				m_iterationnum=1000;
				m_isusefusiondata=true;
				m_isuseconditiondata=true;

				if(m_x) ::free(m_x);
				if(m_y) ::free(m_y);
				if(m_z) ::free(m_z);
				if(m_v) ::free(m_v);

				if(m_2dEvs)
				{
					int i = 0;
					for (;i<m_nH[0];i++)
					{
						delete [] m_2dEvs[i];
					}
					delete [] m_2dEvs;
					m_2dEvs = 0;
				}
				if(m_3dEvs)
				{
					int i = 0;
					for (;i<m_nH[0];i++)
					{
						int j = 0;
						for (;j<m_nH[1];j++)
						{
							delete [] m_3dEvs[i][j];
						}
					}
					i = 0;
					for (;i<m_nH[0];i++)
					{
						delete [] m_3dEvs[i];
					}
					delete [] m_3dEvs;	
					m_3dEvs = 0;
				}
				/*if(m_Ori3dEvs)
				{
				int i = 0;
				for (;i<m_nH[0];i++)
				{
				int j = 0;
				for (;j<m_nH[1];j++)
				{
				delete [] m_Ori3dEvs[i][j];
				}
				}
				i = 0;
				for (;i<m_nH[0];i++)
				{
				delete [] m_Ori3dEvs[i];
				}
				delete [] m_Ori3dEvs;	
				m_Ori3dEvs = 0;
				}
				if(m_Ori2dEvs)
				{
				int i = 0;
				for (;i<m_nH[0];i++)
				{
				delete [] m_Ori2dEvs[i];
				}

				delete [] m_Ori2dEvs;
				m_Ori2dEvs = 0;
				}*/
				if(m_Grid)
				{
					int i = 0;
					for (;i<m_genalnH[0];i++)
					{
						int j = 0;
						for (;j<m_genalnH[1];j++)
						{
							delete [] m_Grid[i][j];
						}
					}
					i = 0;
					for (;i<m_genalnH[0];i++)
					{
						delete [] m_Grid[i];
					}
					delete [] m_Grid;	
					m_Grid = 0;
				}
				
				if(m_S)
				{
					int i = 0;
					for (;i<m_nH[0];i++)
					{
						int j = 0;
						for (;j<m_nH[1];j++)
						{
							delete [] m_S[i][j];
						}
					}
					i = 0;
					for (;i<m_nH[0];i++)
					{
						delete [] m_S[i];
					}
					delete [] m_S;	
					m_S = 0;
				}

				if(m_kringGrid)
				{
					int i = 0;
					for (;i<m_kringnH[0];i++)
					{
						int j = 0;
						for (;j<m_kringnH[1];j++)
						{
							delete [] m_kringGrid[i][j];
						}
					}
					i = 0;
					for (;i<m_kringnH[0];i++)
					{
						delete [] m_kringGrid[i];
					}
					delete [] m_kringGrid;	
					m_kringGrid = 0;
					
				}
				m_genalnH[0]=0;m_genalnH[1]=0;m_genalnH[2]=0;
				m_kringnH[0]=0;m_kringnH[1]=0;m_kringnH[2]=0;
				m_nH[0]=16;m_nH[1]=16;m_nH[2]=16;
			}

			// TODO:
			// assignment function
			// ...
		};

		enum VariogramModel
		{
			VM_SPHERICAL=0,
			VM_EXPONETIAL,
			VM_GUASSIAN,
			VM_LINEAR,
		};

		enum VarianceDataType
		{
			VDT_Simulation=0,
			VDT_Fusion,
		};

		enum VarianceCalculationType
		{
			VCT_Unknown,
			VCT_2D_Anisotropic,
			VCT_2D_Isotropic,
			VCT_3D_Anisotropic,
			VCT_3D_Isotropic,
			VCT_Max
		};

		enum VarianceInterpolationType
		{
			VIT_Unknown,
			VIT_Direct,
			VIT_Sphere_Direct,
			VIT_Sphere_Poly,
			VIT_Sphere_User,
			VIT_Exponetial_User,
			VIT_Guassian_User,
			VIT_Linear_User,
			VIT_Max
		};

		/*!
		*
		**/
		struct GridCalculationUnit
		{
			int m_type;

			int m_xStart;
			int m_xEnd;
			int m_yStart;
			int m_yEnd;
			int m_zStart;
			int m_zEnd;

			VarianceCalculationParameter *varianceparameter;
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CSweetConditionalSimulator(CAccumulationElement *curElement);
		~CSweetConditionalSimulator();

	public:
		//
		// data and variance
		//
		/*!
		*
		**/
		unsigned int Commit(bool isDeleted = false);
		void SetData(CGeoPoint<double> *data, int number);
		CGeoPoint<double> *GetData(int &number);
		void ReleaseData();

		void SetVarianceParameter(VarianceCalculationParameter &fromparameter,VarianceCalculationParameter &toparameter);
		VarianceCalculationParameter &GetVarianceParameter(int type);
		void CalcExperimentalVariance(short type,VarianceCalculationParameter *varianceparameter, bool isthreaded = false);
		bool InterpolateVariance(short type, VarianceCalculationParameter *varianceparameter,bool isanisostropic = true,bool isforVariancedata=false);
		void ReleaseVarianceParameter();

		void SetCurrentVarianceParameter(int type)
		{
			m_currentvarianceparametertype=type;
			if(type==VarianceDataType::VDT_Simulation)
			{
				m_currentvarianceparameter=&(m_varianceparameters[VarianceDataType::VDT_Simulation]);
			}
			else if(type==VarianceDataType::VDT_Fusion)
			{
				m_currentvarianceparameter=&(m_varianceparameters[VarianceDataType::VDT_Fusion]);
			}
		}
		VarianceCalculationParameter *GetCurrentVarianceParameter()
		{
			return m_currentvarianceparameter;
		}

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoCalcExperimentalVariance(const GridCalculationUnit unit);
		void DoAllocateCalculationUnits(int type,VarianceCalculationParameter *varianceparameter);

	private:
		// data
		int m_number;
		CGeoPoint<double> *m_data;

		// thread
		
		int m_xGridStep;
		int m_yGridStep;
		int m_zGridStep;
		

	public:
		// parameter
		std::vector<VarianceCalculationParameter> m_varianceparameters;
		VarianceCalculationParameter *m_currentvarianceparameter;
		int m_currentvarianceparametertype;
		int m_taskCount;
		std::vector<GridCalculationUnit> m_units;

	};
}
#endif
