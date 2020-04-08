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
#ifndef __ANYPETRO_VOLUMETRIC_PREDICATOR_H__
#define __ANYPETRO_VOLUMETRIC_PREDICATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

// refer to its parent
#include "accumulationassessor.h"
// refer to kinds of resources
#include "accumulationresourcemanager.h"

// token string
#include "any/base/anytokenstring.h"
using namespace AnyBase;

// refer to distribution
#include "any/math/anydistributionstrategy.h"
using namespace AnyMath;

#include "accumulationpropertyrecord.h"
#include "accumulationpropertyset.h"

#include "any/db/anyaccessor.h"
using namespace AnyDB;

#include "anytrapmanagement.h"
//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CVolumetricPredicator : public CAccumulationAssessor
	{
	public:
		/*!
		*
		**/
		enum VolumetricMethodType
		{
			VMT_Unknown = -1,
			VMT_Deterministic,
			VMT_NonDeterministic,
			VMT_Max
		};
		enum VolumetricParameterType
		{
			VPT_ProductArea						= 1, //0
			VPT_GrossThickness					= 1 << 1,//2
			VPT_AveragePorosity					= 1 << 2,//4
			VPT_HC_Saturation						= 1 << 3,//8
			VPT_RockDensity						= 1 << 4,//16
			VPT_OilDensity								= 1 << 5,
			VPT_GasContent							= 1 << 6,
			VPT_GeometricFactor					= 1 << 7,
			VPT_Net2Gross							= 1 << 8,
			VPT_FormationVolumeFactor	= 1 << 9,
			VPT_RecoveryFactor					= 1 << 10,
			VPT_RecycleFactor						= 1 << 11,
			VPT_ConversionFactor				= 1 << 12,
			VPT_Ks								= 1 << 13,
			VPT_Kxi								= 1 << 14,

			VPT_Max										= 1 << 15
		};
		typedef std::vector<int> ResourceParameterTypes;
		typedef std::vector<string> ResourceTypesName;
		typedef std::map<int , std::vector<string> > ResourceParameterNames;

		/*!
		*
		**/
		struct VolumetricCorrelationPair
		{
			unsigned int m_from;
			unsigned int m_to;
		};

		/*!
		*
		**/
		enum VolumetricReturnType
		{
			VQT_Unknown = -1,
			VQT_GrossRockVolume,
			VQT_NetRockVolume,
			VQT_NetPoroVolume,
			VQT_HCPoroVolume,
			VQT_InplaceVolume,
			VQT_RecoverableVolume,
			VQT_ShaleDirectCFVolume,
			VQT_ShaleDirectVolume,
			VQT_MLRbitumA,//国土部氯仿A
			VQT_MLRHindex,//国土部H index
			VQT_MLRCindex,//国土部C index
			//页岩油
			VQT_ShaleDirectbitumVolume,
			VQT_ShaleDirecQSHInterlayer,
			//页岩气
			VQT_QSH_ShaleGas_05032013,
			VQT_DZT_ShaleGas_02542014,
			VQT_DZT_ShaleGas_LandFaceInterlayer,
			//岩石热解油和气
			VQT_ShaleDirectRockPyrolysisOilVolume,
			VQT_ShaleDirectRockPyrolysisGasVolume,
			

			VQT_Max,
		};

		/*!
		*
		**/
		struct ParameterDescription
		{
			// parameter type
			int m_type; 
			// parameter name
			string m_name;
			// deterministic or non-determinisitc
			bool m_isDeterminisitc;
			// number
			int m_number;
			// void means it may be a double value or a distribution
			void *m_value;
			
			// thickness contour cell(s)
			double m_minThickness;		// excede this effective thick, to calculate area
			double m_maxThickness;
			int m_cells;
			CGeoPoint<double> *m_thicknesses;

			/*!
			*
			**/
			ParameterDescription() : m_name(""),m_type(0), m_number(0), m_value(0), m_isDeterminisitc(false), m_cells(0), m_thicknesses(0),m_minThickness(0),m_maxThickness(0)
			{
			}

			/*!
			*
			**/
			ParameterDescription(const ParameterDescription &other)
			{
				Reset();
				*this = other;
			}

			void Reset()
			{
				m_type = 0;
				m_number = 0;
				m_value = 0;
				m_isDeterminisitc = false;
				m_cells = 0;
				m_thicknesses = 0;
				m_minThickness=0;
				m_maxThickness=0;
				m_name="";
			}

			/*!
			*
			**/
			~ParameterDescription()
			{
				Release();
			}

			/*!
			*
			**/
			const ParameterDescription &operator=(const ParameterDescription &other)
			{
				//
				if(this == &other)
				{
					return *this;
				}
				Release();
				
				//
				m_type = other.m_type;
				m_number = other.m_number;
				m_isDeterminisitc = other.m_isDeterminisitc;
				m_name = other.m_name;
				if(m_isDeterminisitc) // mean it is a double value
				{
					m_value = (double *)::malloc(m_number * sizeof(double));
					::memcpy(m_value, other.m_value, m_number * sizeof(double));
				}
				else
				{
					CAnyDistributionStrategy *otherDistribution = (CAnyDistributionStrategy *)other.m_value;
					assert(otherDistribution);
					if(otherDistribution)
					{
						m_value = CAnyDistributionStrategy::GetDistribution(otherDistribution->GetName());
						((CAnyDistributionStrategy *)(m_value))->InitSamples(otherDistribution->GetName(), otherDistribution->GetSamples(), otherDistribution->GetSampleSize(), otherDistribution->GetParameters());
						
					}
				}

				// reset contour cells
				m_minThickness = other.m_minThickness;
				m_maxThickness = other.m_maxThickness;
				m_cells = other.m_cells;
				if(m_cells)
				{
					m_thicknesses = (CGeoPoint<double> *)::malloc(m_cells * sizeof(CGeoPoint<double>));
					::memcpy(m_thicknesses, other.m_thicknesses, m_cells * sizeof(CGeoPoint<double>));
				}

				return *this;
			}

			/*!
			*
			**/
			void Release()
			{
				// release distribution
				if(m_isDeterminisitc)
				{
					if(m_value)
					{
						::free(m_value);
					}
				}
				else 
				{
					// as a distribution
					if(m_value)
					{
						delete  (CAnyDistributionStrategy *)m_value;
					}
				}
				m_number = 0;
				m_value = 0;

				// release contour info
				if(m_thicknesses)
				{
					::free(m_thicknesses);
				}
				m_thicknesses=0;
				m_cells = 0;
				m_minThickness = 0;
				m_maxThickness = 0.;
				Reset();
			}

			/*!
			*
			**/
			string ToParameterString(bool isDeterministic)
			{
				string str;
				str.reserve(1024);
				char parameter[512] = "";
				::sprintf(parameter, "%d|%s|%d|", m_type, m_name.c_str(), isDeterministic ? m_number : 1);
				str = parameter;
		
				if(isDeterministic)
				{
					double avg = *(double *)(m_value);
					int i = 1;
					for(; i < m_number; i++)
					{
						avg +=  *(((double *)(m_value) + i));
					}

					avg /= m_number;
					::sprintf(parameter, "%.3f ", avg);
					str += parameter;
				}
				else
				{
					assert(m_number == 1);
					CAnyDistributionStrategy *distribution = (CAnyDistributionStrategy *)(m_value);
					string name = distribution->GetName();
					string para;
					distribution->GetParameters().ToString(para);
					::sprintf(parameter, "%s|%s ", name.c_str(), para.c_str());
					str += parameter;
				}

				return str;				
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter, bool isDeterministic)
			{
				CAnyTokenString curToken("|","","");
				//curToken.SetToken("|");
				int count = curToken.Trim(parameter.c_str(), parameter.size());
				m_type = atoi(curToken.GetAt(0));
				m_name = curToken.GetAt(1);
				m_number = ::atoi(curToken.GetAt(2));
				m_isDeterminisitc = isDeterministic;

				if(isDeterministic)
				{
					assert(count == 4);
					double avg = ::atof(curToken.GetAt(3));
					assert(!m_value);
					if(m_value)
					{
						::free(m_value);
					}
					m_value = (double *)::malloc(m_number * sizeof(double));
					*((double *)(m_value)) = avg;
				}
				else
				{
					//
					assert(m_number);
					string probName = curToken.GetAt(3);
					string probPara = curToken.GetAt(4);
					m_value =  CAnyDistributionStrategy::GetDistribution(probName);
					CAnyDistributionStrategy::DistributionParameters parameter(probPara);
					((CAnyDistributionStrategy *)(m_value))->InitSamples(probName, 0, 0, parameter);
				}
			}
		};

		/*!
		* for kinds of resource type or different volumetric methods
		**/
		struct ResourcePredication
		{
			// resource type
			long m_resourceType;

			// predication type
			long m_methodType;

			// monte carlo setting
			long m_iterations;
			long m_seed;

			// correlation indication
			bool m_isCorrelated;
			// order vector respresenting different parameters in positive correlation
			std::vector<int> m_positives;
			// order vector representing different parameters in negative correlation
			std::vector<int> m_negatives;

			// generic volumetric parameters
			std::vector<ParameterDescription> m_parameters;

			// parameter values as MC middle results
			double **m_paraValues;

			// generic result samples
			int m_rtNumber;
			double *m_rtValues; // 可采
			double *m_geoValues; // 地质
			double *m_absoubValues;  // 吸附
			double *m_freeValues; // 游离

			double m_geovaluesdtm	;
			double m_absorbvaluesdtm;
			double m_freevaluesdtm	;
			double m_rtvaluesdtm	;


			double m_minQ;
			double m_maxQ;
			double m_Q;
			double m_swanson;


			int m_managementphase;
			/*!
			*
			**/
			ResourcePredication() : m_resourceType(CAccumulationResourceManager::VRT_Unknown), m_methodType(VMT_Unknown), m_iterations(1000), m_seed(19937), m_isCorrelated(false), \
				m_Q(0.), m_rtNumber(0), m_rtValues(0), m_geoValues(0), m_paraValues(0), m_minQ(0.), m_maxQ(0.),m_swanson(0.0),m_managementphase(0),m_absoubValues(0),m_freeValues(0)
			{
				m_geovaluesdtm		=0;
				m_absorbvaluesdtm	=0;
				m_freevaluesdtm		=0;
				m_rtvaluesdtm		=0;
				m_positives.clear();
				m_negatives.clear();
				m_parameters.clear();
			}

			/*!
			*
			**/
			ResourcePredication(const ResourcePredication &other)
			{
				Reset();
				*this = other;
			}

			void Reset()
			{
				m_resourceType = CAccumulationResourceManager::VRT_Unknown;
				m_methodType = VMT_Unknown;
				m_iterations = 1000;
				m_seed = 19937;
				m_isCorrelated = false;
				m_Q = 0.;
				m_minQ = 0.;
				m_maxQ = 0.;
				m_rtNumber = 0;
				m_rtValues = 0;
				m_geoValues = 0;
				m_paraValues = 0;
				m_swanson=0.0;
				m_absoubValues=0;
				m_freeValues=0;

				m_geovaluesdtm		=0;
				m_absorbvaluesdtm	=0;
				m_freevaluesdtm		=0;
				m_rtvaluesdtm		=0;
			}
			/*!
			*
			**/
			~ResourcePredication()
			{
				Release();
			}

			/*!
			*
			**/
			const ResourcePredication &operator=(const ResourcePredication &other)
			{
				//
				if(this == &other)
				{
					return *this;
				}
				Release();

				// predication type
				m_resourceType = other.m_resourceType;
				m_methodType = other.m_methodType;

				// monte carlo setting
				m_iterations = other.m_iterations;
				m_seed = other.m_seed;

				// correlation indication
				m_isCorrelated = other.m_isCorrelated;

				// order vector respresenting different parameters in positive correlation
				m_positives.assign(other.m_positives.begin(), other.m_positives.end());
				// order vector representing different parameters in negative correlation
				m_negatives.assign(other.m_negatives.begin(), other.m_negatives.end());
				// copy initial settings
				// Note:
				// both can't share VALUE pointer
				// ...
				int i = 0;
				int count = other.m_parameters.size();
				for(; i < count; i++)
				{
					ParameterDescription parameter;
					parameter = other.m_parameters[i];
					m_parameters.push_back(parameter);
				}

				// copy middle simulation results
				if(other.m_paraValues)
				{
					m_paraValues = (double **)::malloc(other.m_parameters.size() * sizeof(double *));
					i = 0;
					for(; i < count; i++)
					{
						m_paraValues[i] = (double *)::malloc(other.m_iterations * sizeof(double));
						::memcpy(m_paraValues[i], other.m_paraValues[i], other.m_iterations * sizeof(double));
					}
				}

				// copy results
				m_rtNumber = other.m_rtNumber;
				if(m_rtNumber)
				{
					m_rtValues = (double *)::malloc(m_rtNumber * sizeof(double));
					::memcpy(m_rtValues, other.m_rtValues, m_rtNumber * sizeof(double));

					m_geoValues = (double *)::malloc(m_rtNumber * sizeof(double));
					::memcpy(m_geoValues, other.m_geoValues, m_rtNumber * sizeof(double));

					if(other.m_absoubValues)
					{
						if(m_absoubValues)
						{
							::free(m_absoubValues);
						}
						m_absoubValues = (double *)::malloc(m_rtNumber * sizeof(double));
						::memcpy(m_absoubValues, other.m_absoubValues, m_rtNumber * sizeof(double));
					}
					if(other.m_freeValues)
					{
						if(m_freeValues)
						{
							::free(m_freeValues);
						}
						m_freeValues = (double *)::malloc(m_rtNumber * sizeof(double));
						::memcpy(m_freeValues, other.m_freeValues, m_rtNumber * sizeof(double));
					}

				}
				m_Q = other.m_Q;
				m_minQ = other.m_minQ;
				m_maxQ = other.m_maxQ;
				m_swanson= other.m_swanson;

				m_geovaluesdtm		=other.m_geovaluesdtm		;
				m_absorbvaluesdtm	=other.m_absorbvaluesdtm	;
				m_freevaluesdtm		=other.m_freevaluesdtm		;
				m_rtvaluesdtm		=other.m_rtvaluesdtm		;

				//
				return *this;
			}

			/*!
			*
			**/
			void Release()
			{
				// parameter inital setting
				int i = 0;
				int count = m_parameters.size();
				for(; i < count; i++)
				{
					m_parameters[i].Release();
					m_parameters[i].Reset();
				}
				m_parameters.clear();

				// middle parameter 
				if(m_paraValues)
				{
					int i = 0;
					for(; i < count; i++)
					{
						::free(m_paraValues[i]);
						m_paraValues[i]=0;
					}
					::free(m_paraValues);
				}
				m_paraValues = 0;
				
				// the last results
				if(m_rtValues)
				{
					::free(m_rtValues);
				}
				m_rtValues = 0;

				if(m_geoValues)
				{
					::free(m_geoValues);
				}

				if(m_absoubValues)
				{
					::free(m_absoubValues);
				}

				if(m_freeValues)
				{
					::free(m_freeValues);
				}

				m_geoValues = 0;
				m_rtNumber = 0;
				m_absoubValues=0;
				m_freeValues=0;

				m_geovaluesdtm		=0;
				m_absorbvaluesdtm	=0;
				m_freevaluesdtm		=0;
				m_rtvaluesdtm		=0;

				m_positives.clear();
				m_negatives.clear();

				Reset();
			}

			/*!
			*
			**/
			bool IsReady()
			{
				return (m_resourceType > CAccumulationResourceManager::VRT_Unknown && m_resourceType < CAccumulationResourceManager::VRT_Max) &&
					(m_methodType > VMT_Unknown && m_methodType < VMT_Max) &&
					m_parameters.size();
			}

			/*!
			*
			**/
			bool IsValid()
			{
				return m_Q >  0.;
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				string str;
				str.reserve(1024);
				char parameter[512] = "";
				::sprintf(parameter, "%d#%d#%d#%d#%d#", m_resourceType, m_methodType, m_iterations, m_seed,m_parameters.size());
				str = parameter;
				
				bool isDeterministic = (m_methodType == VMT_Deterministic);
				int i = 0;
				int count = m_parameters.size();
				for(; i < count; i++)
				{
					string cur = m_parameters[i].ToParameterString(isDeterministic);
					str += cur;
					if(i != count-1)
					{
						str += "#";
					}
				}

				return str;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken("#","","");
				//curToken.SetToken("#");
				int curCount = curToken.Trim(parameter.c_str(), parameter.size());
				if(curCount <= 4)
					return;
				m_resourceType = ::atoi(curToken.GetAt(0));
				m_methodType = ::atoi(curToken.GetAt(1));
				m_iterations = ::atoi(curToken.GetAt(2));
				m_seed = ::atoi(curToken.GetAt(3));
				//m_swanson = ::atof(curToken.GetAt(4));

				int count = ::atoi(curToken.GetAt(4));
				bool isDeterministic = (m_methodType == VMT_Deterministic);
				int i = 0;
				for(; i < count; i++)
				{
					if(curCount <= 4+i+1)
						return;
					string parameter = curToken.GetAt(4+i+1);
					ParameterDescription cur;
					cur.FromParameterString(parameter, isDeterministic);
					m_parameters.push_back(cur);
				}
			}
		};

		/*!
		*
		**/
		enum ParameterCorrelationType
		{
			PCT_Unknown = -1,
			PCT_Sample,
			PCT_Direct,
			PCT_Function,
			PCT_Max
		};

		/*!
		*
		**/
		struct ParameterCorrelationPair
		{
			// which segment and parameter type?
			CAccumulationElement *m_fromSegment;	// given x axis
			unsigned int m_fromParameter;	// parameter type

			// which segemtn and parameter type?
			CAccumulationElement *m_toSegment;		//	given y axis
			unsigned int m_toParameter;		// parameter type

			// correlation type
			int m_cortype;

			// 1) sample, to get upper and lower regression line
			double m_uSlope;
			double m_uIntercept;
			double m_lSlope;
			double m_lIntercept;

			// 2) direct
			double m_correlation;

			// 3) function with call to set formular(), replaceall()
			string m_formular;

			/*!
			*
			**/
			ParameterCorrelationPair() : m_fromSegment(0), m_fromParameter(0), m_toSegment(0), m_toParameter(0), m_correlation(0.),
				m_uSlope(0.), m_uIntercept(0.), m_lSlope(0.), m_lIntercept(0.)
			{
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				string str;
				str.reserve(1024);
				char parameter[512] = "";//m_fromSegment->GetIdx(),m_toSegment->GetIdx(),
				::sprintf(parameter, "%d|%d|%.3f|%.3f|%.3f|%.3f|%d|%.3f|%s", m_fromParameter, m_toParameter, m_uSlope,m_uIntercept,m_lSlope,m_lIntercept,
					m_cortype,m_correlation,m_formular.c_str());
				str = parameter;
		
				return str;				
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken("|","","");
				//curToken.SetToken("|");
				int count = curToken.Trim(parameter.c_str(), parameter.size());
				//int fromid = atoi(curToken.GetAt(0));
				//int toid = atoi(curToken.GetAt(1));
				//m_fromSegment = CAccumulationElement::GetElementByIdx(fromid,CAccumulationElement::GetRootElement());
				//m_toSegment = CAccumulationElement::GetElementByIdx(toid,CAccumulationElement::GetRootElement());
				m_fromParameter = atoi(curToken.GetAt(0));
				m_toParameter = atoi(curToken.GetAt(1));
				m_uSlope = ::atof(curToken.GetAt(2));
				m_uIntercept = ::atof(curToken.GetAt(3));
				m_lSlope = ::atof(curToken.GetAt(4));
				m_lIntercept = ::atof(curToken.GetAt(5));
				if(count>6)
				{
					m_cortype = atoi(curToken.GetAt(6));
					m_correlation = ::atof(curToken.GetAt(7));
					m_formular = curToken.GetAt(8);
				}
			}

			/*!
			*
			**/
			double CalculateCorrelation(std::vector<double> &xValues, std::vector<double> &yValues)
			{
				assert(xValues.size() == yValues.size());
				if(xValues.size() <= 0)
				{
					assert(false);
					return 0;
				}

				double xAvg = 0.;
				{
					int i = 0;
					for(; i < xValues.size(); i++)
					{
						xAvg += xValues[i];
					}
					xAvg /= xValues.size();
				}

				double yAvg = 0.;
				{
					int i = 0;
					for(; i < yValues.size(); i++)
					{
						yAvg += yValues[i];
					}
					yAvg /= yValues.size();
				}

				double xyMean = 0.;
				{
					int i = 0;
					for(; i < xValues.size(); i++)
					{
						xyMean += (xValues[i] - xAvg) * (yValues[i] - yAvg);
					}
					xyMean /= xValues.size();
				}

				double xVar = 0.;
				{
					int i = 0;
					for(; i < xValues.size(); i++)
					{
						xVar +=  (xValues[i] - xAvg) *  (xValues[i] - xAvg) ;
					}
					xVar /= xValues.size();
				}

				double yVar = 0.;
				{
					int i = 0;
					for(; i < yValues.size(); i++)
					{
						yVar +=  (yValues[i] - yAvg) *  (yValues[i] - yAvg) ;
					}
					yVar /= yValues.size();
				}

				m_correlation = xyMean / ::sqrt(xVar * yVar);
				assert(m_correlation >= 0. && m_correlation <= 1.);

				return m_correlation;
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CVolumetricPredicator(CAccumulationElement *curElement);

		/*!
		*
		**/
		virtual ~CVolumetricPredicator();

	public:
		//
		//
		//
		/*!
		*
		**/
		static long GetResourceTypeCount();

		/*!
		*
		**/
		static const string &GetResourceTypeName(int index);

		/*!
		*
		**/
		static long GetParameterCount();

		/*!
		*
		**/
		static void GetParameterDesc(int type, std::vector<string> &names, std::vector<int> &types);

		/*!
		*
		**/
		static unsigned int GetParameterType(int resourceType);

		/*!
		*
		**/
		bool MakePredication(ResourcePredication &predication);

		/*!
		*
		**/
		void SetPredication(const ResourcePredication &other)
		{
			m_predication = other;
		}

		/*!
		*
		**/
		ResourcePredication &GetPredication();

		/*!
		*
		**/
		void Release()
		{
			m_predication.Release();
		}

		//
		// running results against kinds of parameters
		//
		/*!
		*
		**/
		double GetMean(int order);

		/*!
		* parameter order
		**/
		double GetVariance(int order);

		/*!
		*
		**/
		void GetCorrelation(int order, std::vector<double> &samples, int pointcount = 40);

		/*!
		*
		**/
		double GetQuantile(double probability, bool isForGeological = false);

		//
		//
		//
		/*!
		*
		**/
		void Load();

		/*!
		*
		**/
		unsigned int Commit(bool isDeleted = false);

		/*!
		*
		**/
		unsigned int CommitWithPracticeIdx(long &practiceidx,bool isDeleted=false);
		
		//
		// for multiple segment evaluation
		//
		/*!
		*
		**/
		void ChangeHeightParameter(double diff, CVolumetricPredicator *bottom = 0);

		/*!
		*
		**/
		void SetCorrelationParameters(std::vector<ParameterCorrelationPair> &correlations);

		/*!
		*
		**/
		int GetParameterIndex(unsigned int parameterType);

		/*!
		* 读取体积法记录
		**/
		bool ReadPracticeData(string &parameter,CVolumetricPredicator::ResourcePredication &predication,std::vector<CVolumetricPredicator::ParameterCorrelationPair> &correlations);
	

		/*!
		* 根据参数类型获取它在当前参数序列中的位置
		**/
		int GetParameterIndexByType(unsigned int parameterType,ResourcePredication &predication);

		/*!
		* 设置remark提交信息
		**/
		void SetRemarkString(string remark)
		{
			m_remark = remark;
		}

		/*!
		*
		**/
		static int CompareValue(const void *a , const void *b);

		void CommitPostDrillData( double postdrillarea,double postdrillthick,double postdrillURF,double postdrillreserve);
private:
		//
		//
		//
		/*!
		*
		**/
		void DoDeterministicPredication(ResourcePredication &predication);
		void DoCollectDeterministicResult(ResourcePredication &predication);
		void DoNondeterministicPredication(ResourcePredication &predication);
		void DoCollectNondeterministicResult(ResourcePredication &predication);

		//
		void DoCollectDeterministicRockOil(ResourcePredication &predication);
		void DoCollectDeterministicRockGas(ResourcePredication &predication);
		void DoCollectDeterministicQSHBitumen(ResourcePredication &predication);
		void DoCollectDeterministicQSHInterlayer(ResourcePredication &predication);
		void DoCollectDeterministicQSHShaleGas(ResourcePredication &predication);
		void DoCollectDeterministicDZTShaleGas(ResourcePredication &predication);
		void DoCollectDeterministicLandFaceInterLayerShaleGas(ResourcePredication &predication);
		void DoCollectDeterministicMLRBitumen(ResourcePredication &predication);
		void DoCollectDeterministicMLRHindex(ResourcePredication &predication);
		void DoCollectDeterministicMLRCindex(ResourcePredication &predication);
		void DoCollectDeterministicFormulae(ResourcePredication &predication);

		void DoCollectNondeterministicRockOil(ResourcePredication &predication);
		void DoCollectNondeterministicRockGas(ResourcePredication &predication);
		void DoCollectNondeterministicQSHBitumen(ResourcePredication &predication);
		void DoCollectNondeterministicQSHInterlayer(ResourcePredication &predication);
		void DoCollectNondeterministicQshShaleGas(ResourcePredication &predication);
		void DoCollectNondeterministicDZTShaleGas(ResourcePredication &predication);
		void DoCollectNondeterministicLandFaceInterLayerShaleGas(ResourcePredication &predication);
		void DoCollectNondeterministicMLRBitumen(ResourcePredication &predication);
		void DoCollectNondeterministicMLRHindex(ResourcePredication &predication);
		void DoCollectNondeterministicMLRCindex(ResourcePredication &predication);


		void DoCollectNondeterministicFormulae(ResourcePredication &predication);


	

		/*!
		获取相关性结构持久化的字符串
		**/
		string GetCorrelationCommitString();

	public:
   	    // parameter correlation group/pairs
	    std::vector<ParameterCorrelationPair> m_correlations;

		// use TIME or GIVEN seed
		unsigned long m_userSeed;
		int m_resourcreclass;
		bool m_iscommitplate;

		// parameters
		ResourcePredication m_predication;
		// remark of activity record
		string m_remark;
		
		// resource and parameter names
		static ResourceParameterTypes m_resourceParameterTypes;
		static ResourceParameterNames m_resourceParameterNames;
		static ResourceTypesName m_volumetricResourceTypeName;
		//static char m_volumetricResourceTypeName[CAccumulationResourceManager::VRT_Max][127];
	};
}

#endif