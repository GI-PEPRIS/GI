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
#ifndef __ANYSDE_SDE_QUERY_INDEX_H__
#define __ANYSDE_SDE_QUERY_INDEX_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// refer to geometry vector
#include "anysdegeometrylayer.h"

//
#include "any/spatial/anygeoindeximpl.h"
using namespace AnyIndex;

//
namespace AnySDE
{
	// forward classes
	class CAnySdeLayer;
	class CAnySdeGeometry;

	/*!
	*
	**/
	class CAnySdeQueryIndex
	{
		// relatives
		friend class CAnySdeLayer;
		friend class CAnySdeGeometryLayer;
		friend class CAnySdeGeometryEditor;
		friend class CAnySdePointEditor;
		friend class CAnySdeLineEditor;
		friend class CAnySdePolygonEditor;
		friend class CAnySdeRasterEditor;
	public:
		/*!
		*
		**/
		enum IndexOperation
		{
			IO_None		= 1,
			IO_Add			= 1 << 1,
			IO_Update		= 1 << 2,
			IO_Delete		= 1 << 3,
		};

		/*!
		*
		**/
		enum IndexSelection
		{
			ISS_Unknown,	// need to apply geometry algorithm
			ISS_False,			// directly exclude 
			ISS_True,			// directly selected
		};
		
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
		struct IndexRecord
		{
			// tile code
			long m_gridIdx;
			// parent code
			long m_parentIdx;
			// for which geometry
			long m_geometryIdx;
			// spatial relationship
			unsigned short m_relationship;
			// DB operations
			unsigned int m_operation;
			// extent
			CGeoRect<double> m_extent;

			// indicating whether for PRIMARY\INTERMEDIATE\SECONDRY
			// ...
			unsigned char m_selection;

			int m_version;

			/*!
			*
			**/
			IndexRecord() : m_gridIdx(0), m_parentIdx(0), m_geometryIdx(0), m_relationship(0), m_operation(0), m_selection(ISS_Unknown), m_version(0)
			{
			}

			/*!
			*
			**/
			const IndexRecord &operator=(const IndexRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_gridIdx = other.m_gridIdx;
				m_parentIdx = other.m_parentIdx;
				m_geometryIdx = other.m_geometryIdx;
				m_relationship = other.m_relationship;
				m_operation = other.m_operation;
				m_extent = other.m_extent;
				m_selection = other.m_selection;
				m_version = other.m_version;

				return *this;
			}
		};

		typedef std::vector<IndexRecord *> RecordVector;
		typedef RecordVector::iterator rv_itr;
		typedef RecordVector::const_iterator rv_citr;

		class CommitTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			CommitTask(int taskcount, int index, std::vector<string> &cmds, CAnySdeQueryIndex *parent);
			~CommitTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			std::vector<string> m_cmds;
			CAnySdeQueryIndex *m_parent;
		};

	protected:
		//
		//
		//
		/*!
		*
		**/
		CAnySdeQueryIndex(CAnySdeLayer *layer);

		/*!
		*
		**/
		~CAnySdeQueryIndex();

	public:
		//
		//
		//
		/*!
		*
		**/
		void PrepareQueryIndexer(short indexType, long xCount, long yCount);

		/*!
		*
		**/
		void Commit(bool isreload = true, long indexlimit = 1000, bool isshowsql = true, bool isMT = false,bool istoUAD = false, bool istoVer = false, bool issort = true);

		/*!
		*
		**/
		void Load(const CGeoRect<double> &rect, long indexlimit = 1000, bool isshowsql = true);

		/*!
		*
		**/
		void Clear();

		//
		//
		//
		/*!
		*
		**/
		void MakePrimaryFilter(const CGeoRect<double> &rect, RecordVector &indexes, bool isshowsql = true);

		/*!
		*
		**/
		void MakePrimaryFilterByRenderGridId(CAnyAccessor &accessor, long gridid, RecordVector &indexes);

		/*!
		*
		**/
		void MakeIntermediateFilter(const CGeoPoint<double> &pt, RecordVector &indexes);

		/*!
		*
		**/
		void MakeIntermediateFilter(const CGeoRect<double> &rect, RecordVector &indexes);
		
		/*!
		*
		**/
		void MakeIntermediateFilter(const std::vector<CGeoPoint<double> > &poly, RecordVector &indexes);

		/*!
		*
		**/
		template<class T>
		void MakeSecondaryFilter(T &queryGeometry, RecordVector &indexes)
		{
			MEMORY_STAT
			TIME_STAT

			RecordVector sels;
			RecordVector tempindexes;
			std::vector<long> geometryidstoload;
			bool lastgeometryOK = true;
			bool lastgeometryneedload = false;
			CAnyAccessor accessor;
			for(int i = 0; i < indexes.size(); i++)
			{
				if(i == 0 || indexes[i]->m_geometryIdx != indexes[i - 1]->m_geometryIdx)
				{
					if(!lastgeometryOK && lastgeometryneedload)
					{
						geometryidstoload.push_back(indexes[i - 1]->m_geometryIdx);
						tempindexes.push_back(indexes[i - 1]);
					}
					lastgeometryOK = false;
					lastgeometryneedload = false;
				}
				if(lastgeometryOK)
					continue;
				if(indexes[i]->m_selection == ISS_False)
					continue;
				CAnySdeIndexGrid *oneGrid = m_layer->m_ptCache.GetUnit(m_layer->m_idx, indexes[i]->m_parentIdx);
				if(!oneGrid)
				{
					lastgeometryneedload = true;
					continue;
				}
				int geometries = oneGrid->m_geometries.size();
				if(geometries<=0)
					continue;
				int low = 0, high = geometries - 1, mid=0;
				while(low <= high)
				{
					mid = low + (high - low) / 2;
					if(oneGrid->m_geometries[mid]->m_idx == indexes[i]->m_geometryIdx)
						break;
					else if(oneGrid->m_geometries[mid]->m_idx > indexes[i]->m_geometryIdx)
						high = mid - 1;
					else
						low = mid + 1;
				}
				if(oneGrid->m_geometries[mid]->m_idx == indexes[i]->m_geometryIdx)
				{
					boost::shared_ptr<CAnySdeGeometry> geometry = oneGrid->m_geometries[mid];
					short relation = geometry->RelationTo(queryGeometry);
					if(relation != CAnySdeGeometry::SRT_Outside)
					{
						sels.push_back(indexes[i]);
						m_layer->m_selectedGeometries.push_back(geometry);
					}
					geometry.reset();
					lastgeometryOK = true;
				}
			}
			if(!lastgeometryOK && lastgeometryneedload)
			{
				geometryidstoload.push_back(indexes[indexes.size() - 1]->m_geometryIdx);
				tempindexes.push_back(indexes[indexes.size() - 1]);
			}
			std::vector<boost::shared_ptr<CAnySdeGeometry> > geometries;
			std::vector<int> relationships;
			(dynamic_cast<CAnySdeGeometryLayer *>(m_layer))->GetGeometrys(accessor, geometryidstoload, relationships, 0, geometries);
			for(int i = 0; i < geometries.size(); i++)
			{
				short relation = geometries[i]->RelationTo(queryGeometry);
				if(relation != CAnySdeGeometry::SRT_Outside)
				{
					sels.push_back(tempindexes[i]);
					m_layer->m_selectedGeometries.push_back(geometries[i]);
				}
			}
			for(int j = 0; j < geometries.size(); j++)
				geometries[j].reset();
			geometries.clear();
			indexes = sels;
		}

	private:
		//
		//
		//
		/*!
		*
		**/
		bool DoRemoveIndice(const CAnySdeGeometryLayer::GeometryVector &geometries);

		/*!
		*
		**/
		void DoInsertIndice(const CAnySdeGeometryLayer::GeometryVector &geometries);

		/*!
		*
		**/
		bool DoCreateIndexRecord(CAnySdeGeometry *geometry);

		/*!
		*
		**/
		bool DoLoadIndexRecords(long parcelIdx, CAnyAccessor &accessor);

		/*!
		*
		**/
		bool DoLoadIndexRecords(std::vector<long> parcelIdxs, CAnyAccessor &accessor);

		/*!
		*
		**/
		void ReduceIndicestoLimits();

		/*!
		*
		**/
		void FromRenderIDtoQueryIDs(const long renderingId, std::vector<long> &queryIds, int xCount, int yCount, int xShift, int yShift);
		
		/*!
		*
		**/
		void FromQueryIDtoRenderID(const long queryId, long &renderingId, int xCount, int yCount, int xShift, int yShift);

		//
		//
		//
		/*!
		*
		**/
		static bool CompareGridIdx(const IndexRecord *first, const IndexRecord *second)
		{
			return first->m_gridIdx < second->m_gridIdx;
		}

		/*!
		*
		**/
		static bool CompareGeometryIdx(const IndexRecord *first, const IndexRecord *second)
		{
			return first->m_geometryIdx < second->m_geometryIdx;
		}

		/*!
		*
		**/
		static bool CompareGridandGeometryIdx(const IndexRecord *first, const IndexRecord *second)
		{
			if(first->m_gridIdx < second->m_gridIdx)
				return true;
			if(first->m_gridIdx > second->m_gridIdx)
				return false;
			return first->m_geometryIdx < second->m_geometryIdx;
		}

		/*!
		*
		**/
		static bool CompareOperationFlag(const IndexRecord *first, const IndexRecord *second)
		{
			return first->m_operation < second->m_operation;
		}
				
		/*!
		*
		**/
		static bool CompareParentIdx(const IndexRecord *first, const IndexRecord *second)
		{
			return first->m_parentIdx < second->m_parentIdx;
		}
	public:
		// parent layer
		CAnySdeLayer *m_layer;
		// index mechanism
		CAnyGeoIndexImpl *m_indexer;
		// memory cache, range order: firstly by gridIdx, secondly by geometryIdx
		RecordVector m_indices;
		unsigned long m_limits;

		int m_taskcount;
		// configure parameter
		bool m_isDirectCreateIndex;
		int m_dbtype;
	};
}

#endif
