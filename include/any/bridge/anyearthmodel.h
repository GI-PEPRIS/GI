/*!
 * The ANYBRIDGE of PetroCOVERY Solution is a collection of native C++ classes that implement 
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
#ifndef __ANYBRIDGE_em_H__
#define __ANYBRIDGE_em_H__

// refer to EXPORT & IMPORT
#include "anybridge.h"

// refer to STL
#include "any/base/anystl.h"

// refer to data models
#include "anybridgedatamodel.h"

//
namespace AnyBridge
{
	// forward class
	class CAnyGeologicalCubeFeature;
	class CAnyGeologicalFeatureLayer;

	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyEarthModel
	{
	public:
		// for cube feature and feature layer also
		enum CubeFeatureKind
		{
			CFK_Horizon,
			CFK_Fault,
			CFK_Interval,
		};

		/*!
		* d_seismic_ipt_em
		**/
		struct ModelRecord
		{
			long m_primaryIdx;	// primary key
			long m_modelIdx;
			long m_projectIdx;  
			long m_elementIdx;

			string m_name;			// differenciate whether is the same earth model
			string m_remark;

			/*!
			*
			**/
			ModelRecord() : m_primaryIdx(0), m_modelIdx(0), m_projectIdx(0), m_elementIdx(0), m_name(""), m_remark("")
			{
			}

			/*!
			*
			**/
			ModelRecord(const ModelRecord &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const ModelRecord &operator=(const ModelRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_primaryIdx = other.m_primaryIdx;
				m_modelIdx = other.m_modelIdx;
				m_projectIdx = other.m_projectIdx;
				m_elementIdx = other.m_elementIdx;
				m_name = other.m_name;
				m_remark = other.m_remark;
				return *this;
			}
		};
		
		// features belong to the same seismic project
		typedef std::vector<CAnyGeologicalCubeFeature *> CubeFeatureVector;
		typedef CubeFeatureVector::iterator feature_itr;
		typedef CubeFeatureVector::const_iterator feature_citr;
		
		// features categroized by projects belong to the same earth model
		typedef std::map<long, CubeFeatureVector> ProjectFeatureMap;
		typedef ProjectFeatureMap::iterator prj_feature_itr;
		typedef ProjectFeatureMap::const_iterator prj_feature_citr;

		//
		typedef std::vector<CAnyGeologicalFeatureLayer *> FeatureLayerVector;
		typedef FeatureLayerVector::iterator lyr_itr;
		typedef FeatureLayerVector::const_iterator lyr_citr;

		typedef std::map<long, FeatureLayerVector> ProjectLayerMap;
		typedef ProjectLayerMap::iterator prj_layer_itr;
		typedef ProjectLayerMap::const_iterator prj_layer_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyEarthModel();

		/*!
		*
		**/
		~CAnyEarthModel();

		//
		//
		//
		/*!
		*
		**/
		void AddGeologicalFeatureLayer(long projectIdx, CAnyGeologicalFeatureLayer *layer);

		/*!
		*
		**/
		void AddCubeFeature(long projectIdx, CAnyGeologicalCubeFeature *feature);

		/*!
		*
		**/
		void CommitToDB();

		/*!
		*
		**/
		void LoadFromDB(long modelIdx);

		/*!
		*
		**/
		void RemoveFromDB(long projectIdx);

		//
		// directly load from given tables
		//
		/*!
		*
		**/
		long GetCubeFeatureCount(long projectIdx);

		/*!
		*
		**/
		CAnyGeologicalCubeFeature *GetCubeFeature(long projectIdx, int order);

		/*!
		*
		**/
		long GetFeatureLayerCount(long projectIdx);

		/*!
		*
		**/
		CAnyGeologicalFeatureLayer *GetFeatureLayer(long projectIdx, int order);

		//
		// relations in DB schema
		//
		/*!
		*
		**/
		static void GetSeismicSurvey(long projectIdx, std::vector<AnySeismic2DGeometry> &surveys);

		/*!
		*
		**/
		static void GetSeismicSurvey(long projectIdx, std::vector<AnySeismic3DGeometry> &surveys);

	private:
		//
		//
		//
		/*!
		*
		**/
		static bool CompareCubeFeatureIdx(CAnyGeologicalCubeFeature *first, CAnyGeologicalCubeFeature *second);

	public:
		// model record
		std::vector<ModelRecord> m_records;

		// features cateogried by different projects
		ProjectFeatureMap m_features;

		// layers categorized by different projects
		ProjectLayerMap m_layers;
	};
}
#endif