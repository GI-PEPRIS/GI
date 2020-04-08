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
#ifndef __ANYSDE_SDE_EVIDENCE_WEIGHT_MODEL_H__
#define __ANYSDE_SDE_EVIDENCE_WEIGHT_MODEL_H__

// refer to EXPORT & IMPORT
#include "anyrasterspatialanalysis.h"

//
namespace AnySDE
{
	/*!
	*
	**/
	class ANYSDE_CLASS CAnyEvidenceWeightModel : public CAnyRasterSpatialAnalysis
	{
	public:
		/*!
		* corresponding to m_cells defined by parent class
		**/
		struct CellFlag
		{
			double m_value;				// as average of 4 corner pts
			bool m_isValid;
			bool m_isNone;
			double m_probability;		// as the last result, sense to target layer only

			CellFlag() : m_value(ANY_NAN), m_isValid(false), m_isNone(false), m_probability(ANY_NAN)
			{
			}
		};
				
		/*!
		*
		**/
		struct TargetLayer
		{
			typedef boost::function<bool (double)> CompareFunction;

			CAnyViewHook *m_layer;						// host layer		
			string m_valueField;									// empty means directly adopts the pt.m_z

			double m_targetValid;								// value for differentiate whether is target
			CompareFunction m_validFunc;
			double m_targetNone;								// value for differentiate whether isn't target
			CompareFunction m_noneFunc;

			int m_discoveries;
			int m_dries;
			int m_number;
			CellFlag *m_flags;

			double m_pd;												// probability of discovery
			double m_od;

			/*!
			*
			**/
			TargetLayer()
			{
				// default compare function
				BindValidFunction(0);
				BindNoneFunction(1);

				//
				Init();
			}

			/*!
			*
			**/
			~TargetLayer()
			{
				Release();
			}

			/*!
			*
			**/
			void Init()
			{
				m_layer = 0;
				m_valueField = "";
				m_targetValid = ANY_NAN;
				m_targetNone = ANY_NAN;
				m_number = 0;
				m_discoveries = 0;
				m_dries = 0;
				m_pd = ANY_NAN;
				m_od = ANY_NAN;
				m_flags = 0;

				Release();
			}

			/*!
			*
			**/
			void Release(bool isCreate = false)
			{
				//free
				if (m_flags)
				{
					::free(m_flags);
				}
				m_flags = 0;

				//
				if (isCreate && m_number > 0)
				{
					m_flags = (CellFlag *)::malloc(sizeof(CellFlag)* m_number);
				}
			}

			/*!
			*2015/8/4
			**/
			void BindValidFunction(int selection)
			{
				if (selection == 0)
				{
					m_validFunc = boost::bind(&TargetLayer::GreaterAsTarget, this, _1);
				}
				else if (selection == 1)
				{
					m_validFunc = boost::bind(&TargetLayer::SmallerAsTarget, this, _1);
				}
				else if (selection == 2)
				{
					m_validFunc = boost::bind(&TargetLayer::GreaterAsTarget1, this, _1);
				}
				else if (selection == 3)
				{
					m_validFunc = boost::bind(&TargetLayer::SmallerAsTarget1, this, _1);
				}
			}

			/*!
			*2015/8/4
			**/
			void BindNoneFunction(int selection)
			{
				if (selection == 0)
				{
					m_noneFunc = boost::bind(&TargetLayer::GreaterAsNone, this, _1);
				}
				else if (selection == 1)
				{
					m_noneFunc = boost::bind(&TargetLayer::SmallerAsNone, this, _1);
				}
				else if (selection == 2)
				{
					m_noneFunc = boost::bind(&TargetLayer::GreaterAsNone1, this, _1);
				}
				else if (selection == 3)
				{
					m_noneFunc = boost::bind(&TargetLayer::SmallerAsNone1, this, _1);
				}
			}

			//
			//compare function
			//
			/*!
			*
			**/
			bool GreaterAsTarget(double value)
			{
				return value >= m_targetValid;
			}

			/*!
			*
			**/
			bool SmallerAsTarget(double value)
			{
				return value <  m_targetValid;
			}

			/*!
			*
			**/
			bool SmallerAsNone(double value)
			{
				return value < m_targetNone;
			}
			
			/*!
			*
			**/
			bool GreaterAsNone(double value)
			{
				return value >=  m_targetNone;
			}

			//
			//2016/1/22: new compare method
			//
			/*!
			*
			**/
			bool GreaterAsTarget1(double value)
			{
				return value > m_targetValid;
			}

			/*!
			*
			**/
			bool SmallerAsTarget1(double value)
			{
				return value <=  m_targetValid;
			}

			/*!
			*
			**/
			bool SmallerAsNone1(double value)
			{
				return value <= m_targetNone;
			}
			
			/*!
			*
			**/
			bool GreaterAsNone1(double value)
			{
				return value >  m_targetNone;
			}
		};

		/*!
		*
		**/
		struct EvidenceLayer : public TargetLayer
		{
			bool m_isEvidence;					// whether as an evidence
			double m_weightPlus;
			double m_weightNegative;
			double m_probabilities[4];		// 0-discovery against valid area, 1-discovery against none area, 2-no discovery against valid, 3-non discovery against none area 

			//2015/8/25: statistical info
			int m_first;				// evidence is valid and target is valid
			int m_second;		// evidence is valid and target is none
			int m_third;			// evidence is none and target is valid
			int m_fourth;			// evidence is none and target is none

			/*!
			*
			**/
			EvidenceLayer() : m_weightPlus(ANY_NAN), m_weightNegative(ANY_NAN), m_isEvidence(true), m_first(0), m_second(0), m_third(0), m_fourth(0)
			{
			}

			/*!
			*
			**/
			EvidenceLayer(const EvidenceLayer &other) 
			{
				*this = other;
			}

			/*!
			*
			**/
			const EvidenceLayer &operator=(const EvidenceLayer &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_isEvidence = other.m_isEvidence;
				m_weightPlus = other.m_weightPlus;
				m_weightNegative = other.m_weightNegative;
				m_probabilities[0] = other.m_probabilities[0];
				m_probabilities[1] = other.m_probabilities[1];
				m_probabilities[2] = other.m_probabilities[2];
				m_probabilities[3] = other.m_probabilities[3];

				m_layer = other.m_layer;
				m_valueField = other.m_valueField;
				m_targetValid = other.m_targetValid;
				m_targetNone = other.m_targetNone;
				m_number = other.m_number;
				m_discoveries = other.m_discoveries;
				m_dries = other.m_dries;
				m_pd = other.m_pd;
				m_od = other.m_od;
				m_flags = other.m_flags;

				m_first = other.m_first;			
				m_second = other.m_second;	
				m_third = other.m_third;		
				m_fourth = other.m_fourth;			

				//
				m_validFunc = other.m_validFunc;
				m_noneFunc = other.m_noneFunc;

				return *this;
			}
		};
		typedef std::vector<EvidenceLayer*> EvidenceVector;

	public:
			//
			//
			//
			/*!
			*
			**/
			CAnyEvidenceWeightModel(CAnyView &curView);
			CAnyEvidenceWeightModel(CAnyView &curView, CAnyViewHook *layer);
			~CAnyEvidenceWeightModel();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool MakeRasterization(const CGeoRect<double> &extent, int rows, int cols);
		
		/*!
		*
		**/
		void CalculatePriorProbability();
		void EscapeDependentEvidence();
		void CalculateEvidenceWeight();
		void CalculatePosteriorProbability();

		//
		//
		//
		bool MouseDown(const CGeoPoint<double> &scrPoint);
		bool MouseMove(const CGeoPoint<double> &scrPoint);
		bool MouseUp(const CGeoPoint<double> &scrPoint);
		bool DoubleClick(const CGeoPoint<double> &scrPoint);
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect = false);

		/*!
		*
		**/
		void ResetLayers();
	private:
		//
		//
		//
		/*!
		*
		**/
		void DoCheckIndependence();

		/*!
		*
		**/
		bool DoMakeRasterization(TargetLayer &tLayer, const CGeoRect<double> &extent, int rows, int cols, bool isTarget);

	public:
		// for this object, m_layer means the result layer, namely chance map
		// 
		TargetLayer m_target;
		EvidenceVector m_evidences;
	};
}
#endif