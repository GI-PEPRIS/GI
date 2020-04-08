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
#ifndef __ANYSDE_SDE_LAYER_INTERFACE_H__
#define __ANYSDE_SDE_LAYER_INTERFACE_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// refer to grid cache
#include "anysdegridcache.h"

//
#include "any/db/anyaccessor.h"
using namespace AnyDB;

// Refer to grid index mechansim
#include "any/spatial/anygeoindex.h"
#include "any/spatial/anygeoindeximpl.h"
using namespace AnyIndex;

// refer to parent class
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to boost share_ptr
#include "boost/smart_ptr.hpp"
#include "boost/any.hpp"
using namespace boost;

//
namespace AnySDE
{
	// forward classes
	class CAnySdeQueryIndex;

	/*!
	*
	**/
	class ANYSDE_CLASS CAnySdeLayer : public CAnyViewHook
	{
		// relatives
		friend class CAnySdeDataset;
		friend class CAnySdeQueryIndex;

	public:		
		/*!
		*
		**/
		enum DatabaseType
		{
			SQLSERVER,
			ORACLE,
			ACCESS,
			MYSQL,
		};
				
		/*!
		*
		**/
		enum VersionType
		{
			RecordLevel,
			TableLevel,
			IndexLevel,
		};

	public:
		// Geometry vector
		// featre or property vector
		// TODO:
		// to consider HASH mechanism or other
		// ...
		typedef std::vector<boost::shared_ptr<CAnySdeGeometry> > GeometryVector;
		typedef GeometryVector::iterator geom_itr;
		typedef GeometryVector::const_iterator geom_citr;

		typedef std::vector<boost::any>  PropertyVector;	// a feature record
		typedef std::vector<PropertyVector > FeatureVector; // feature records

		//2016/1/26: map for field property
		struct FieldProperty
		{
			//color
			int m_color;
			int m_minColor;
			int m_maxColor;
			int m_shownColor;

			double m_symbolSize;
			int m_symbolStyle;
			//Label
			std::string m_label;
			AnyMap::LabelStyle m_labelstyle;

			//2016/8/31,zhihao: set size by field value
			std::string m_symbolSizeField;
			double m_minSymbolSize;
			double m_maxSymbolSize;

			//for symbol size field of polygon layer
			int m_polygonsymbolstyle;
			int m_polygonsymbolcolor;

			FieldProperty() : m_color(-1), m_minColor(0), m_maxColor(0),m_shownColor(0),m_symbolSize(-1), m_symbolStyle(-1), m_label(""),\
				m_symbolSizeField(""),m_minSymbolSize(3.),m_maxSymbolSize(10.),m_polygonsymbolstyle(-1),m_polygonsymbolcolor(-1)
			{
				
			}
		};
		typedef std::map<long,FieldProperty> FieldPropertyMap;

	protected:
		//
		//
		//
		/*!
		* by default, the feature table is "info_assessment_element", the geometry table is "info_assessment_element_geometry"
		* or "info_assessment_element_raster"
		**/
		CAnySdeLayer(long layerIdx, CAnyView &view, const string &file, const string &featureTable, \
			const string &geometryTable, const string &indexTable, const string &configureTable, const string &versiontreeTable, long elementIdx = 0);

		/*!
		*
		**/
		virtual ~CAnySdeLayer();

	public:
		//
		// inherited from view hook
		//
		/*!
		*
		**/
		 void Clone(const CAnyViewHook *prototype)
		 {
		 }
		 
		//
		//
		//
		/*!
		* feature geomery(raster) table
		**/
		bool CreateTable(string tablename, std::vector<DBFieldDesc> &fields);

		//
		// DB schema interface
		//
		/*!
		* note: directly use CAnyAccessor to finish CRUD operations against current feature table
		**/
		bool CreateField(const DBFieldDesc &field);

		/*!
		*
		**/
		bool CreateIndex(string tablename, string indexname, std::vector<string> fieldnames);

		//
		// properties of this layer
		//
		/*!
		* after call this function, MUST reset indexer
		**/
		void SetLayerExtent(const CGeoRect<double> &extent);

		/*!
		*
		**/
		void PrepareHierarchicalIndexer(short indexType);

		/*!
		*
		**/
		const CGeoRect<double> &GetLayerExtent();

		/*!
		*
		**/
		void PrepareCache();

		/*!
		*
		**/
		bool PrepareDBSchema();

		//
		// geometry interface
		//
		/*!
		* it had better only meeting with the last one to sort those geometries just added
		**/
		virtual bool AddGeometry(CAnySdeGeometry *geometry, bool isSort = true)
		{
			return false;
		}

		/*!
		*
		**/
		virtual bool UpdateGeometry(CAnySdeGeometry *geometry)
		{
			return false;
		}

		/*!
		* isSort has the same meaning as AddGeometry, decrease the SORTING times ASAP
		**/
		virtual bool RemoveGeometry(CAnySdeGeometry *geometry, bool isSort = true)
		{
			return false;
		}

		/*!
		*
		**/
		virtual bool GetGeometrys(CAnyAccessor &accessor, std::vector<long> &geometryIdxs, std::vector<int> &relationships, int looptype, std::vector<boost::shared_ptr<CAnySdeGeometry> > &geometries, CAnySdeIndexGrid *curGrid = NULL)
		{
			return false;
		}

		/*!
		*
		**/
		virtual bool AddRaster(void *image, double timestamp = 0)
		{
			return false;
		}

		/*!
		*
		**/
		virtual bool RemoveRaster(double timestamp)
		{
			return false;
		}

		//
		// persistence interface
		//
		/*!
		*
		**/
		virtual void Release() = 0;

		/*!
		*
		**/
		virtual void Load(const CGeoRect<double> &extent, short indexType = IT_RegularGrid) = 0;
		
		/*!
		*
		**/
		virtual void Commit(bool istoUAD = false, bool istoVer = false, bool modifyfeature = false, bool ischeckidadd = true) = 0;

		//
		// simple spatial analysis interface
		//
		/*!
		*
		**/
		virtual bool Query(const CGeoPoint<double> &pt, std::vector<unsigned long> &idxes)
		{
			return false;
		}

		/*!
		*
		**/
		virtual bool Query(const CGeoRect<double> &rect, std::vector<unsigned long> &idxes, bool isCircle = false)
		{
			return false;
		}

		/*!
		*
		**/
		virtual bool Query(const std::vector<CGeoPoint<double> > &poly, std::vector<unsigned long> &idxes)
		{
			return false;
		}

		/*!
		*
		**/
		boost::shared_ptr<CAnySdeGeometry> GetGeometrySelected(unsigned long selectIdx);

		/*!
		*
		**/
		static bool CompareFeatureProperty(const PropertyVector &first, const PropertyVector &second)
		{
			return boost::any_cast<int>(*first.begin()) < boost::any_cast<int>(*second.begin());
		}

	protected:
		//
		//
		//
		/*!
		*
		**/
		boost::shared_ptr<CAnySdeGeometry> DoGetGeometryById(CAnyAccessor &accessor, int geometryid, int wkbtype);

	public:
		// dummy field for assessment
		long m_elementIdx;

		// by default m_idx means layer idx
		// and here declare tile idx
		short m_tileIdx;

		// unique indicator inside data set
		long m_gateIdx; // encoded by m_idx(layeridx) and m_tileIdx

		// selection 
		std::vector<boost::shared_ptr<CAnySdeGeometry> > m_selectedGeometries;

		// POINTER grid cache
		CAnySdeGridCache::GridPointerCache &m_ptCache;
		CAnySdeGridCache::GridIdxCache &m_idxCache;
		int m_cachesize;

		// in order to enhance the rendering performance
		//int m_maxVertices;
		//CGeoPoint<double> *m_maxCoords;

		// Extent
		CGeoRect<double> m_layerExtent;
		double m_layerzmin;
		double m_layerzmax;

		//layer type
		unsigned int m_layerType;
		// database type
		int m_dbtype;

		// double index mechanism
		// TODO:
		// recursively make hierarchical space decomposition
		// ...
		CAnyGeoIndexImpl *m_renderingIndexer;
		CAnySdeQueryIndex *m_queryIndexer;
		int m_xShift;
		int m_yShift;
		int m_xCount;
		int m_yCount;
		unsigned long m_indexlimit;

		bool m_isIndexTableExist;

		// db schema
		string m_featureTable;
		string m_geometryTable;
		string m_indexTable;
		string m_configureTable;
		string m_versiontreeTable;

		// net key
		unsigned long m_nextKey;
		
		//2016/1/26: map for field property
		FieldPropertyMap m_fieldPropertyMap;

		// layer version
		int m_version;
		string m_whodo;

		//geometry simplification
		int m_simplifyMethod;
		double m_simplifyParameter;

		int m_symbolstyle;
	};
}

#endif
