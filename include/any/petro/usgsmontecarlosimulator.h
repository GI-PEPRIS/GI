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
#ifndef __ANYPETRO_ACCUMULATION_USGS_SIMULATOR_H__
#define __ANYPETRO_ACCUMULATION_USGS_SIMULATOR_H__

// refer to EXPORT etc macroes
#include "anypetro.h"
// refer to its parent
#include "accumulationassessor.h"

// refer to functor
#include "any/base/anymediator.h"
using namespace AnyBase;

//
#include "any/thread/jtc.h"

// refer to distribution
#include "any/math/anydistributionstrategy.h"
// random generator
#include "any/math/anyrandomgenerator.h"
using namespace AnyMath;

#include "boost/function.hpp"

namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CUSGSMonteCarloSimulator : public CAccumulationAssessor, public CAnyObservable, public ParallelExecutor<CUSGSMonteCarloSimulator>
	{
	public:
		/*!
		*
		**/
		enum ResourcePredicationType
		{
			RPT_Unknown = -1,
			RPT_Normal,
			RPT_With_Geological_Risk,
			RPT_With_Accessibility_Risk,
			RPT_Max
		};
		
		/*!
		*
		**/
		/*volatile*/ struct SimulationParameter
		{
			// risk or probability definition
			double m_fluids;
			double m_rocks;
			double m_timing;
			double m_geologic;
			double m_accessibility;

			// calculation
			// resource type
			short m_resourceType;

			//resource type
			int m_resourcecategory;
			//resource class
			int m_resourceclass;
			//choice of distribution
			int m_disnum;
			int m_dissize;
			// number of undiscovered oil fields
			CAnyDistributionStrategy *m_number;
			// field size/distribution
			CAnyDistributionStrategy *m_size;
			// gas/oil ratio
			double m_goRatio;
			// ngl/gas ratio
			double m_ngRatio;

			// iterations
			long m_iterations;

			// undiscovered predication
			double **m_oils;
			double **m_gases;
			double **m_ngls;
			double *m_largestField;

			double m_minQ;
			double m_avgQ;
			double m_maxQ;
			double m_swasonQ;

			string m_undiscoverdisname;
			string m_fieldsizedisname;
			//char m_undiscoverdisname[100];
			//char m_fieldsizedisname[100];
			int m_seed;
			/*!
			*
			**/
			SimulationParameter() : m_resourcecategory(0),m_resourceclass(0),m_fluids(0.), m_rocks(0.), m_timing(0.), m_geologic(0.), m_accessibility(0.), \
				m_iterations(50000), m_resourceType(0), m_number(0), m_size(0), m_goRatio(0.), m_ngRatio(0.), \
				m_oils(0), m_gases(0), m_ngls(0), m_largestField(0),m_disnum(0),m_dissize(0),m_minQ(0),m_avgQ(0),m_maxQ(0),m_swasonQ(0),\
				m_undiscoverdisname(""),m_fieldsizedisname(""),m_seed(0)
			{
			//	::memset(m_undiscoverdisname,0,100);
			//	::memset(m_fieldsizedisname,0,100);
			}

			/*!
			*
			**/
			~SimulationParameter()
			{
				Release();
			}

			/*!
			*
			**/
			/*volatile*/ SimulationParameter &operator=(/*volatile*/ SimulationParameter &other) /*volatile*/
			{
				if(this == &other)
				{
					return *this;
				}

				//
				Release();

				// risk or probability definition
				m_fluids = other.m_fluids;
				m_rocks = other.m_rocks;
				m_timing = other.m_timing;
				m_geologic = other.m_geologic;
				m_accessibility = other.m_accessibility;
				m_seed = other.m_seed;
				// calculation
				// iterations
				m_iterations = other.m_iterations;
				// resource type
				m_resourceType = other.m_resourceType;
				// number of undiscovered oil fields
				m_number = CAnyDistributionStrategy::GetDistribution(other.m_number->GetName());
				m_number->InitSamples(other.m_number->GetName(), 0, 0, other.m_number->GetParameters());
				// field size/distribution
				m_size = CAnyDistributionStrategy::GetDistribution(other.m_size->GetName());
				m_size->InitSamples(other.m_size->GetName(), 0, 0, other.m_size->GetParameters());
				// gas/oil ratio
				m_goRatio = other.m_goRatio;
				// ngl/gas ratio
				m_ngRatio = other.m_ngRatio;

				m_resourcecategory = other.m_resourcecategory;
				m_resourceclass= other.m_resourceclass;

				m_disnum = other.m_disnum;
				m_dissize= other.m_dissize;
				m_undiscoverdisname=other.m_undiscoverdisname;
				m_fieldsizedisname=other.m_fieldsizedisname;
				// undiscovered predication

	/*			::memset(m_undiscoverdisname,0,100);
				::memset(m_fieldsizedisname,0,100);
				::memcpy(m_undiscoverdisname, other.m_undiscoverdisname, 100);
				::memcpy(m_fieldsizedisname, other.m_fieldsizedisname, 100);*/
			
				if(IsReady())
				{
					int i = 0;
					for(; i < RPT_Max; i++)
					{
						::memcpy(m_oils[i], other.m_oils[i], sizeof(double) * m_iterations);
						::memcpy(m_gases[i], other.m_gases[i], sizeof(double) * m_iterations);
						::memcpy(m_ngls[i], other.m_ngls[i], sizeof(double) * m_iterations);
					}
					::memcpy(m_largestField, other.m_largestField, sizeof(double) * RPT_Max);
				}

				return *this;
			}

			/*!
			*
			**/
			void Release() /*volatile*/
			{
				// risk or probability definition
				m_fluids = 0.;
				m_rocks = 0.;
				m_timing = 0.;
				m_geologic = 0.;
				m_accessibility = 0.;
				m_seed = 0;
				m_resourcecategory = 0;
				m_resourceclass= 0;

				m_disnum =0;
				m_dissize= 0;

				// calculation
				// iterations
				m_iterations = 50000;
				// resource type
				m_resourceType = 0;
				// number of undiscovered oil fields
				if(m_number)
				{
					delete m_number;
				}
				m_number = 0;
				// field size/distribution
				if(m_size)
				{
					delete m_size;
				}
				m_size = 0;
				// gas/oil ratio
				m_goRatio = 0.;
				// ngl/gas ratio
				m_ngRatio = 0.;

				//m_undiscoverdisname ="";
				//m_fieldsizedisname = "";

				// undiscovered predication
				if(m_oils)
				{
					int i = 0;
					for(; i < RPT_Max; i++)
					{
						::free(m_oils[i]);
					}
					::free(m_oils);
					m_oils=NULL;
				}
				if(m_gases)
				{
					int i = 0;
					for(; i < RPT_Max; i++)
					{
						::free(m_gases[i]);
					}
					::free(m_gases);
					m_gases=NULL;
				}
				if(m_ngls)
				{
					int i = 0;
					for(; i < RPT_Max; i++)
					{
						::free(m_ngls[i]);
					}
					::free(m_ngls);
					m_ngls=NULL;
				}
				if(m_largestField)
				{
					::free(m_largestField);
				}
				m_largestField = 0;

				m_undiscoverdisname="";
				m_fieldsizedisname="";
			}

			/*!
			*
			**/
			bool IsReady() volatile
			{
				if(m_iterations < 10000 || !m_number || !m_size)
				{
					return false;
				}
				//assert(!m_oils && !m_gases && !m_ngls && !m_largestField);

				if(m_oils==NULL)
				{
					m_oils = (double **)::malloc(sizeof(double*) * RPT_Max);
					for(int i = 0; i < RPT_Max; i++)
					{
						m_oils[i] = (double *)::malloc(sizeof(double) * m_iterations);
						::memset(m_oils[i], 0x00, sizeof(double) * m_iterations);
					}
				}
				if(m_gases==NULL)
				{
					m_gases = (double **)::malloc(sizeof(double*) * RPT_Max);
					for(int i = 0; i < RPT_Max; i++)
					{
						m_gases[i] = (double *)::malloc(sizeof(double) * m_iterations);
						::memset(m_gases[i], 0x00, sizeof(double) * m_iterations);
					}
				}
				if(m_ngls==NULL)
				{
					m_ngls = (double **)::malloc(sizeof(double*) * RPT_Max);
					for(int i = 0; i < RPT_Max; i++)
					{
						m_ngls[i] = (double *)::malloc(sizeof(double) * m_iterations);
						::memset(m_ngls[i], 0x00, sizeof(double) *m_iterations);
					}
				}
				if(m_largestField==NULL)
				{
					m_largestField = (double *)::malloc(sizeof(double) * RPT_Max);
					::memset(m_largestField, 0x00, sizeof(double) * RPT_Max);
				}
				

				return true;
			}

			bool IsValid()
			{
				if(m_iterations < 10000 || !m_number || !m_size)
				{
					return false;
				}

				if(!m_oils || !m_gases || !m_ngls || !m_largestField)
				{
					return false;
				}
				
				return true;
			}

			string ToParameterString()
			{
				char parameter[1024] = "";
				//获取分布参数
				string strdisparanumber;
				m_number->GetParameters().ToString(strdisparanumber);
				string numname = m_number->GetName();
				if(numname=="geological pareto")
				{
					numname="geological";
				}
				string strnum = numname+"|"+ strdisparanumber;

				string strdisparasize;
				m_size->GetParameters().ToString(strdisparasize);
				string sizename = m_size->GetName();
				if(sizename=="geological pareto")
				{
					sizename="geological";
				}
				string strsize = sizename+"|"+ strdisparasize;

				::sprintf(	parameter, "%d#%d#%d#%d#%d#%.3f#%.3f#%ld#%.4f#%.4f#%.4f#%.4f#%.4f", 
							m_resourceType, m_resourcecategory,m_resourceclass,m_disnum,m_dissize,m_goRatio,
							m_ngRatio,m_iterations,m_fluids,m_rocks,m_timing,m_geologic,m_accessibility);//,m_undiscoverdisname,m_fieldsizedisname);
				//处理seed
				char seedparameter[100] = "";
				::sprintf(	seedparameter, "%d", m_seed);
				string seedstr = seedparameter;

				string str = parameter;
				str = str + "#"+strnum+"#"+strsize+"#"+seedstr;
				return str;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter) //volatile
			{
				CAnyTokenString curToken;
				curToken.SetToken("#","","");

				int count = curToken.Trim(parameter.c_str(), parameter.size());
				//assert(count == 10);

				m_resourceType = ::atoi(curToken.GetAt(0));
				m_resourcecategory = ::atoi(curToken.GetAt(1));
				m_resourceclass = ::atoi(curToken.GetAt(2));
				m_disnum = ::atoi(curToken.GetAt(3));
				m_dissize = ::atof(curToken.GetAt(4));
				m_goRatio = ::atof(curToken.GetAt(5));
				m_ngRatio = ::atof(curToken.GetAt(6));
				m_iterations = ::atoi(curToken.GetAt(7));
				m_fluids = ::atof(curToken.GetAt(8));
				m_rocks = ::atof(curToken.GetAt(9));
				m_timing = ::atof(curToken.GetAt(10));
				m_geologic = ::atof(curToken.GetAt(11));
				m_accessibility = ::atof(curToken.GetAt(12));
				//m_undiscoverdisname = curToken.GetAt(13);
				//m_fieldsizedisname = curToken.GetAt(14);


				string strnum = curToken.GetAt(13);
				{
					CAnyTokenString discurToken;
					discurToken.SetToken("|","","");
					int count = discurToken.Trim(strnum.c_str(), strnum.size());
					string probName = discurToken.GetAt(0);
					string probPara = discurToken.GetAt(1);
					if(probName=="geological")
					{
						probName="geological pareto";
					}
					if(m_number)
					{
						delete m_number;
						m_number=0;
					}
					m_number =  CAnyDistributionStrategy::GetDistribution(probName);
					CAnyDistributionStrategy::DistributionParameters parameter(probPara);
					CGeoPoint<double> *samples;
					samples = (CGeoPoint<double> *)::malloc(sizeof(CGeoPoint<double>) * 5);
					for(int i=0;i<5;i++)
					{
						samples[i].m_x=i+1;
						samples[i].m_y=i+1;
					}
					((CAnyDistributionStrategy *)(m_number))->InitSamples(probName, 0, 0, parameter);
					m_undiscoverdisname = probName;
				}
				string strsize = curToken.GetAt(14);
				{
					CAnyTokenString discurToken;
					discurToken.SetToken("|","","");
					int count = discurToken.Trim(strsize.c_str(), strsize.size());
					string probName = discurToken.GetAt(0);
					string probPara = discurToken.GetAt(1);
					if(probName=="geological")
					{
						probName="geological pareto";
					}
					if(m_size)
					{
						delete m_size;
						m_size=0;
					}
					m_size =  CAnyDistributionStrategy::GetDistribution(probName);
					CAnyDistributionStrategy::DistributionParameters parameter(probPara);
					CGeoPoint<double> *samples;
					samples = (CGeoPoint<double> *)::malloc(sizeof(CGeoPoint<double>) * 5);
					for(int i=0;i<5;i++)
					{
						samples[i].m_x=i+1;
						samples[i].m_y=i+1;
					}
					((CAnyDistributionStrategy *)(m_size))->InitSamples(probName, 0, 0, parameter);
					m_fieldsizedisname = probName;
				}
				if(count>15)
				{
					m_seed = ::atoi(curToken.GetAt(15));
				}
				else
				{
					m_seed=0;
				}
			}
		};

		
		class USGSTask: public CAnySignalTask<void()>,public JTCMonitor
		{
		public:
			USGSTask(volatile SimulationParameter& m_parameter,int taskcount,int m_index);
			~USGSTask();
			void DoExecuteTask();
			void Notify(short type=0);
			volatile SimulationParameter* m_parameter;
			int m_index;
			int m_taskcount;
			unsigned long m_userSeed;
			unsigned long m_sysdSeed;
			static int m_notifycount;
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CUSGSMonteCarloSimulator(CAccumulationElement *curElement);

		/*!
		*
		**/
		~CUSGSMonteCarloSimulator();

	public:
		//
		//
		//
		/*!
		* deprecated function
		**/
		void DoExecuteTask();
		void run();

		/*!
		*
		**/
		void DoPrepare()
		{
		}
		void DoWork(long start, long stop);
		void DoFinish()
		{
		}

		/*!
		* Let sub-class have its specified event types
		*/
		void Notify(short type);

		/*!
		*
		*/
		void Register(CAnyObserver *oneObserver);

		void Update();

		//
		//
		//
		/*!
		*
		**/
		bool MakeSimulation(SimulationParameter &parameter, CAnyFunctor &progress);

		/*!
		*
		**/
		SimulationParameter &GetParameter()
		{
			return m_parameter;
		}

		/*!
		*
		**/
		CAccumulationAssessor::PracticeBlobDataVector &GetBlobParameter()
		{
			return m_blobparameterVec;
		}

		//
		// acitivity persistence issues
		//
		/*!
		*
		**/
		void Load();

		/*!
		*
		**/
		unsigned int Commit(bool isActivity = true);

	/*	void SetThreadParameter(SimulationParameter *parameter);*/
		/*!
		*
		**/
		bool MakeSimulationMT(/*volatile*/ SimulationParameter &parameter, CAnyFunctor *progress/*,CAnyThreadPool *m_pool*//*,boost::function0<void> func*/);

	private:
		// parameter
		SimulationParameter m_parameter;
		CAccumulationAssessor::PracticeBlobDataVector m_blobparameterVec;
		CAnyObserver *m_observer;

		int m_index;
		int m_stepsize;
		int m_max;
		int m_taskcount;
		int m_finishedtaskcount;
		CAnyFunctor* m_progress;

	public:
		string m_remark;
		unsigned long m_userSeed;
		unsigned long m_sysdSeed;
		//report
		std::vector<std::vector<string>> m_paravector;
		//std::vector<std::vector<string>> m_riskparavector;

		char *m_resgroupbitmap;
		int m_resgroupbitmaplength;
		char *m_disbitmap;
		int m_disbitmaplength;
		std::vector<std::vector<string>> m_datagroup;
		std::vector<std::vector<string>> m_resgroup;

	};
}
#endif