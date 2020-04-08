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
#ifndef __ANYBRIDGE_em_CUBE_FEATURE_H__
#define __ANYBRIDGE_em_CUBE_FEATURE_H__

// refer to EXPORT & IMPORT
#include "anybridge.h"

// refer to STL
#include "any/base/anystl.h"
#include "any/base/anyport.h"

// refer to data models
#include "anybridgedatamodel.h"
#include "cubesampleiterator.h"

// refer to tokenizer
#include "anytokenizer.h"

// visitor pattern
#include "any/base/loki/visitor.h"
using namespace AnyBase::Loki;

// namespace 
namespace AnyBridge
{
	// forward class 
	class CAnyEarthModel;

	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyGeologicalCubeFeature : public CAnyTokenizer, public BaseVisitable<>
	{
		// relatives
		friend class CAnyEarthModel;

	public:
		//
		LOKI_DEFINE_VISITABLE()

		// 
		enum FeatureSampleType
		{
			FST_GridUnknown = -1,
			FST_Grid1d,				// for 2d seismic
			FST_Grid1dSet,
			FST_2D,					// for 3d seismic
			FST_QuadMesh,
			FST_PointSet,
			FST_PolyineSet,
			FST_OrderedPolylineSet,
		};

		// cube sample
		struct FeatureSample
		{
			int m_inLineOrder;
			int m_xLineOrder;
			CGeoPoint<double> m_point;	// x, y, z

			/*!
			*
			**/
			FeatureSample() : m_inLineOrder(-1), m_xLineOrder(-1)
			{
				m_point.m_x = m_point.m_y = m_point.m_z = m_point.m_w = ANY_NAN;
			}

			/*!
			*
			**/
			FeatureSample(const FeatureSample &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const FeatureSample &operator=(const FeatureSample &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_inLineOrder = other.m_inLineOrder;
				m_xLineOrder = other.m_xLineOrder;
				m_point = other.m_point;

				return *this;
			}

			/*!
			*
			**/
			static bool CompareOrder(const FeatureSample &a, const FeatureSample &b)
			{
				if(a.m_inLineOrder < b.m_inLineOrder)
					return true;
				if(a.m_inLineOrder > b.m_inLineOrder)
					return false;
				if(a.m_xLineOrder < b.m_xLineOrder)
					return true;
				if(a.m_xLineOrder > b.m_xLineOrder)
					return false;
				return false;
			}
		};
		typedef std::vector<FeatureSample> SampleVector;
		typedef SampleVector::iterator sample_itr;
		typedef SampleVector::const_iterator sample_citr;

		/*!
		* d_seismic_ipt_em_feature table
		**/
		struct FeatureRecord
		{
			long m_featureIdx;			// as primary key
			long m_projectIdx;
			
			short m_featureKind;		// feature kind
			short m_featureType;		// feature type		
			string m_name;
			long m_isshown;
			SampleVector m_samples;
			string m_remark;

			/*!
			*
			**/
			FeatureRecord() : m_featureIdx(-1), m_projectIdx(-1), m_featureKind(-1), m_featureType(-1), m_name(""), m_isshown(false), m_remark("")
			{
			}

			/*!
			*
			**/
			FeatureRecord(const FeatureRecord &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const FeatureRecord &operator=(const FeatureRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_featureIdx = other.m_featureIdx;
				m_projectIdx = other.m_projectIdx;
				m_featureKind = other.m_featureKind;
				m_featureType = other.m_featureType;
				m_name = other.m_name;
				m_isshown = other.m_isshown;
				m_samples = other.m_samples;
				m_remark = other.m_remark;

				return *this;
			}
		};

		/*!
		* d_seismic_ipt_em_property table
		**/
		struct FeatureProperty
		{
			long m_featureIdx;			// as primary key
			long m_projectIdx;
			
			int m_linecolorr;
			int m_linecolorg;
			int m_linecolorb;
			float m_linewidth;
			float m_linepatternfirst;
			float m_linepatternsecond;
			int m_linepatternlen;

			/*!
			*
			**/
			FeatureProperty() : m_featureIdx(-1), m_projectIdx(-1), m_linecolorr(255), m_linecolorg(0), m_linecolorb(0), m_linewidth(1), \
				m_linepatternfirst(0), m_linepatternsecond(0), m_linepatternlen(0)
			{
			}

			/*!
			*
			**/
			FeatureProperty(const FeatureProperty &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const FeatureProperty &operator=(const FeatureProperty &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_featureIdx = other.m_featureIdx;
				m_projectIdx = other.m_projectIdx;
				m_linecolorr = other.m_linecolorr;
				m_linecolorg = other.m_linecolorg;
				m_linecolorb = other.m_linecolorb;
				m_linewidth = other.m_linewidth;
				m_linepatternfirst = other.m_linepatternfirst;
				m_linepatternsecond = other.m_linepatternsecond;
				m_linepatternlen = other.m_linepatternlen;

				return *this;
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGeologicalCubeFeature(long projectIdx, short shapeKind, short shapeType, const string &fileName);

		/*!
		*
		**/
		virtual ~CAnyGeologicalCubeFeature();

	public:
		//
		//
		//
		/*!
		*
		**/
		void CommitToDB();

		/*!
		*
		**/
		void LoadFromDB(long featureid);
		
		/*!
		*
		**/
		void RemoveFromDB();
		
		/*!
		*
		**/
		void UpdatePropertyToDB();

		//
		// tokenizer
		// 
		/*!
		*
		**/
		int Extract(long elementid, long classid, int num = 0, int startline = 0, int endline = -1);
		int ExtractByPts(long elementid, long classid, int num, int startline, int endline, std::vector<CGeoPoint<double> > &pts);
		//
		// kinds of iterator for cube sample
		//
		/*!
		*
		**/
		bool GetProfile(SampleVector &directions, std::vector<SampleVector> &lines);

		/*!
		*
		**/
		bool IsCommentLine(const string &curLine);

		/*!
		*
		**/
		bool IsBlockLine(const string &curLine);

		/*!
		*
		**/
		bool IsEmptyLine(const string &curLine);

	public:
		//
		//
		//
		/*!
		*
		**/
		template<typename T>
		bool Bind(CAnyTokenString &curToken);

	public:
		// host model
		CAnyEarthModel *m_model;

		// persistence
		FeatureRecord m_record;		
		FeatureProperty m_property;

		// iterator
		CubeSampleIterator *m_iterator;
		std::vector<AnySeismic2DGeometry> m_2dsurveys;
		std::vector<AnySeismic3DGeometry> m_3dsurveys;

		// for tokenize	
		int m_inlinepos;
		int m_xlinepos;
		int m_depthpos;
		int m_xpos;
		int m_ypos;
		int m_partpos;
		int m_unittype;
	};
}
#endif
