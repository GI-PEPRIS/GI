/*!
 * The AnyMap of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * rendering pipeline and key display implementatios etc.
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
#ifndef __ANYBRIDGE_SHP_LAYER_H__
#define __ANYBRIDGE_SHP_LAYER_H__

// Refer to EXPORT & IMPORT
#include "..\anybridge.h"

// Refer to SHP basic definition
#include "anyshpbasic.h"

// Refer to SHP reader definition
#include "anyshpreader.h"
#include "dbf\anydbfreader.h"

// Refer to its parent
#include "any/map/anyview.h"
#include "any/map/anyviewhook.h"
#include "any/map/anycanvas.h"
using namespace AnyMap;

// Refer to geometry basic definition
#include "any/base/anygeom.h"

// Refer to simple LRU implementation
#include "any/base/anylightlru.h"
using namespace AnyBase;

// Refer to grid index mechansim
#include "any/spatial/anygeoindeximpl.h"
using namespace AnyIndex;

#include "boost/shared_ptr.hpp"
using namespace boost;
//
namespace AnyBridge
{
	/*!
	*
	*/
    class ANYBRIDGE_CLASS CAnyShpGrid
    {
		// Relatives
		friend class CAnyShpLayer;

	protected:
		// Pointers set for current SHP layer in this grid
		typedef std::vector<boost::shared_ptr<ShpGeometry> > ShpVector;
		typedef ShpVector::iterator shp_itr;
		typedef ShpVector::const_iterator shp_citr;

		/*!
		*
		**/
		struct QuickIndex
		{
			CAnyShpGrid *m_other;
			ShpGeometry **m_pointer;

			/*!
			*
			**/
			QuickIndex() : m_other(0), m_pointer(0)
			{
			}

			/*!
			*
			**/
			QuickIndex(const QuickIndex &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			~QuickIndex()
			{
				m_other = 0;
				m_pointer = 0;
			}

			/*!
			*
			**/
			const QuickIndex &operator=(const QuickIndex &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_other = other.m_other;
				m_pointer = other.m_pointer;

				return *this;
			}
		};
		typedef std::vector<QuickIndex> ShareVector;
		typedef ShareVector::iterator share_itr;
		typedef ShareVector::const_iterator share_citr;

    public:
        //
        //
        //
        /*!
        *
        */
		CAnyShpGrid() : m_id(0), m_layerIdx(0)
		{
		}

        /*!
        *
        */
        ~CAnyShpGrid()
		{
		}

	public:
        //
        //
        //
        /*!
        *
        */
        void Delete();
        
		/*!
		*
		*/
		int GetIdx() const
		{
			return m_id;
		}

		/*!
		*
		**/
		static bool CompareQuickIdx(const QuickIndex &first, const QuickIndex &second)
		{
			return first.m_other->m_id < second.m_other->m_id;
		}

		/*!
		*
		**/
		static bool CompareShapeIdx(const boost::shared_ptr<ShpGeometry> first, const boost::shared_ptr<ShpGeometry> second)
		{
			return first->m_idx < second->m_idx;
		}

    protected:
        // Grid id
        unsigned int m_id;

		// Belong to which layer
		short m_layerIdx;

		// Envolope
		CGeoRect<double> m_extent;

		std::vector<boost::shared_ptr<ShpGeometry> > m_shapes;
    };

	/*!
	*
	*/
    class ANYBRIDGE_CLASS CAnyShpLayer : public CAnyViewHook
    {
		// Not permit copy & assign operations
		CAnyShpLayer(const CAnyShpLayer &other);
		const CAnyShpLayer &operator=(const CAnyShpLayer &other);

        // Shp grid cache for rendering
		// One shape file should only have one grid cache for demands of different scale rendering
        typedef CAnyLightLru<CAnyShpGrid> GridCache;

		typedef std::map<string, GridCache> ShapeCache;
		typedef ShapeCache::iterator cache_itr;
		typedef ShapeCache::const_iterator cache_citr;

		// Readers for the same SHP file
		typedef std::map<string, CAnyShpReader *> ReaderVector;
		typedef ReaderVector::iterator reader_itr;
		typedef ReaderVector::const_iterator reader_citr;

    public:
		
        //
        //
        //
        /*!
        *
        */
        CAnyShpLayer(short layerIdx, CAnyView &view, const string &file);

        /*!
        *
        */
        virtual ~CAnyShpLayer();

    public:
        //
        //
        //
        /*!
        * grid size
        */
        bool Prepare(long xCount, long yCount, short indexType = IT_RegularGrid, int cachesize = 100);

		/*!
		*
		**/
		bool Query(const CGeoPoint<double> &pt, std::vector<unsigned long> &idxes);

		/*!
		*
		**/
		bool Query(const CGeoRect<double> &rect, std::vector<unsigned long> &idxes, bool isCircle = false);

		/*!
		*
		**/
		bool Query(const std::vector<CGeoPoint<double> > &poly, std::vector<unsigned long> &idxes);

		/*!
		*
		**/
		static bool CompareGeometryIdx(unsigned long first, unsigned long second)
		{
			return first < second;
		}

		//
		//
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype);

		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseMove(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseUp(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		bool DoubleClick(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);

		/*!
		*
		**/
		void PaintOneGrid(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, CAnyShpGrid *oneGrid, CGeoRect<double> &scrExtent, CGeoRect<double> &clipExtent);

		//
		//
		//
		/*!
		*
		**/
		static bool IsUsed(const string &layerName, boost::shared_ptr<ShpGeometry> oneGeometry);

		//
		//
		//
		/*!
		*
		**/
		static void ClearCache(bool isRemoveReader = true);

		/*!
		*
		**/
		static void ClearOneCache(const string &layerName, bool isRemoveReader = true);

		/*!
		*
		**/
		static int GetShapeType(const string &layerName);

		/*!
		*
		**/
		CAnyShpReader *GetReader();

		/*!
		*
		**/
		int GetCacheSize();

		
		/*!
		*
		**/
		int GetGridXCount();

		
		/*!
		*
		**/
		int GetGridYCount();
				
		/*!
		*
		**/
		void SetHighLight(std::vector<unsigned long> &idxes);

		static AnyMap::LineStyle* GetLineStyleFromDB(int classid, int isselectstyle);
		static AnyMap::PolyStyle* GetPolyStyleFromDB(int classid, int isselectstyle);
		static AnyMap::LabelStyle GetLabelStyleFromDB(int classid, int isselectstyle);
		static AnyMap::SymbolStyle* GetSymbolStyleFromDB(int classid, int isselectstyle);
		static void GetLabelposFromDB(int classid, int isselectstyle, int &labelpos, int &symbolstyle);

		static bool SetLineStyleToDB(AnyMap::LineStyle *lineStyle, int classid, int isselectstyle);
		static bool SetPolyStyleToDB(AnyMap::PolyStyle *polyStyle, int classid, int isselectstyle);
		static bool SetLabelStyleToDB(AnyMap::LabelStyle labelStyle, int classid, int isselectstyle);
		static bool SetSymbolStyleToDB(AnyMap::SymbolStyle *symbolStyle, int classid, int isselectstyle);
		static bool SetLabelposToDB(int labelpos, int symbolstyle, int classid, int isselectstyle);

		static void GetDescriptionAndRemarkFromDB(int classid, string &description, string &remark);
		static void SetDescriptionAndRemarkToDB(int classid, string &description, string &remark);

		static void GetShowScaleFromDB(int classid, int &useshowscale, double &maxshowscale, double &minshowscale, int &usetickshowscale, double &maxtickshowscale, double &mintickshowscale);
		static void SetShowScaleToDB(int classid, int useshowscale, double maxshowscale, double minshowscale, int usetickshowscale, double maxtickshowscale, double mintickshowscale);

		void GetShowChartFromDB(std::vector<int> &red, std::vector<int> &green, std::vector<int> &blue, std::vector<double> &height, std::vector<double> &width, std::vector<int> &whichfield);
		void GetShowChartFromDB(std::vector<int> &red, std::vector<int> &green, std::vector<int> &blue, std::vector<double> &height, std::vector<double> &width, std::vector<CGeoPoint<double> > &positions, std::vector<string> &datas);
		void SetShowChartToDB(std::vector<int> red, std::vector<int> green, std::vector<int> blue, std::vector<double> height, std::vector<double> width, std::vector<int> whichfield);

		static int GetClassidBySource(string source);
private:
		/*!
		*
		**/
		void PrepareGridCache();

		/*!
		*
		**/
		CAnyShpGrid *LoadGrid(long gridIdx);

		/*!
		*
		**/
		void LoadGrids(std::vector<long> &gridIdxs, std::vector<CAnyShpGrid *> &grids);

		/*!
		*
		**/
		void FromDisk(CAnyShpGrid *oneGrid, short layerIdx);

		/*!
		*
		**/
		void FromCache(CAnyShpGrid *oneGrid);

		/*!
		*
		**/
		bool IsLoaded(boost::shared_ptr<ShpGeometry> oneGeometry, short layerIdx, CAnyShpGrid *curGrid);

		/*!
		*
		**/
		bool IsSkipped(const CGeoRect<double> &clipBox, double xMin, double yMin, double xMax, double yMax, CGeoRect<double> &bounding);

		/*!
		*
		**/
		void DrawBackGrid(CAnyCanvas &canvas, int idx, const CGeoRect<double> &extent);

		/*!
		*
		**/
		void DrawLines(CAnyCanvas &canvas, const boost::shared_ptr<ShpGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, bool isForLight = false);

		/*!
		*
		**/
		void DrawPolys(CAnyCanvas &canvas, const boost::shared_ptr<ShpGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, bool isForLight = false);

		/*!
		*
		**/
		void DrawPoints(CAnyCanvas &canvas, const boost::shared_ptr<ShpGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, bool isForLight = false);

		/*!
		*
		**/
		void DrawPoint(CAnyCanvas &canvas, const boost::shared_ptr<ShpGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, bool isForLight = false);

		/*!
		*
		**/
		void DoDrawPoint(const boost::shared_ptr<ShpGeometry> oneGeometry, CGeoPoint<double> &mapCoord, CAnyCanvas &canvas, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, bool isForLight = false);

		/*!
		*
		**/
		void DoRenderSelectedGeometries(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent);

		/*!
		*
		**/
		void DoRenderLabel(CAnyCanvas &canvas, long geometryIdx, const CGeoPoint<double> &pos, CGeoPoint<double> *alongPts = 0, int num = 0);

		/*!
		*
		**/
		const boost::shared_ptr<ShpGeometry> DoFindSelectedGeometry(long idx);

		/*!
		*
		**/
		bool IsTooShort(CGeoPoint<double> &scrCoord, CGeoPoint<double> &prevCoord);

		/*!
		*
		*/
		bool UpdateIndexer(long xCount, long yCount, short indexType);

		/*!
		*
		**/
		void DoResetCache(const CAnyLightVector &parcelIds);

		//
		//
		//
		/*!
		*
		**/
		bool IsPolygon(const boost::shared_ptr<ShpGeometry> geometry);

		/*!
		*
		**/
		bool IsPolyline(const boost::shared_ptr<ShpGeometry> geometry);

		/*!
		*
		**/
		bool IsPoint(const boost::shared_ptr<ShpGeometry> geometry);

		/*!
		*
		**/
		bool IsPointSet(const boost::shared_ptr<ShpGeometry> geometry);

		//
		// TODO:
		//
		/*!
		*
		**/
		void DoQueryPointGrid(const CAnyShpGrid *curGrid, const CGeoRect<double> &curMapExtent, std::vector<unsigned long> &idxes);

		/*!
		*
		**/
		void DoQueryPointGrid(const CAnyShpGrid *curGrid, const std::vector<CGeoPoint<double> > &mapPts, std::vector<unsigned long> &idxes);
		
		/*!
		*
		**/
		void DoQueryPointGeometry(const boost::shared_ptr<ShpGeometry> geometry, const CGeoRect<double> &curMapExtent, std::vector<unsigned long> &idxes);

		/*!
		*
		**/
		void DoQueryPointGeometry(const boost::shared_ptr<ShpGeometry> geometry, const std::vector<CGeoPoint<double> > &mapPts, std::vector<unsigned long> &idxes);

		//
		//
		//
		/*!
		*
		**/
		void DoQueryPolylineGrid(const CAnyShpGrid *curGrid, const CGeoRect<double> &curMapExtent, std::vector<unsigned long> &idxes);

		/*!
		*
		**/
		void DoQueryPolylineGrid(const CAnyShpGrid *curGrid, const std::vector<CGeoPoint<double> > &mapPts, const CGeoRect<double> &curMapExtent, std::vector<unsigned long> &idxes);

		/*!
		*
		**/
		void DoQueryPolylineGeometry(const boost::shared_ptr<ShpGeometry> geometry, const CGeoRect<double> &curMapExtent, std::vector<unsigned long> &idxes);

		/*!
		*
		**/
		void DoQueryPolylineGeometry(const boost::shared_ptr<ShpGeometry> geometry, const std::vector<CGeoPoint<double> > &mapPts, std::vector<unsigned long> &idxes);

		//
		//
		//
		/*!
		*
		**/
		void DoQueryPolygonGrid(const CAnyShpGrid *curGrid, const CGeoPoint<double> &curMapPt, const CGeoRect<double> &curMapExtent, std::vector<unsigned long> &idxes);

		/*!
		*
		**/
		void DoQueryPolygonGrid(const CAnyShpGrid *curGrid, const std::vector<CGeoPoint<double> > &mapPts, const CGeoRect<double> &curMapExtent, std::vector<unsigned long> &idxes);

		/*!
		*
		**/
		void DoQueryPolygonGeometry(const boost::shared_ptr<ShpGeometry> geometry, const CGeoPoint<double> &curMapPt, const CGeoRect<double> &curMapExtent, std::vector<unsigned long> &idxes);

		/*!
		*
		**/
		void DoQueryPolygonGeometry(const boost::shared_ptr<ShpGeometry> geometry, const std::vector<CGeoPoint<double> > &mapPts, std::vector<unsigned long> &idxes);
		
		/*!
		*
		**/
		bool IsIntersect(CGeoPoint<double> p1, CGeoPoint<double> p2, CGeoPoint<double> p3, CGeoPoint<double> p4);
		
		/*!
		*
		**/
		double CrossProduct(CGeoPoint<double> pi, CGeoPoint<double> pj, CGeoPoint<double> pk);
	public:
		// SHP specification: shp ,idx and dbf three files
		CAnyShpReader *m_curShpReader;
		CAnyDbfReader *m_curDbfReader;

		// Layer idx following the order of different network layers
		unsigned long m_gateIdx;

		// selection 
		std::vector<boost::shared_ptr<ShpGeometry> > m_selectedGeometries;

		// Geometry index
		CAnyGeoIndexImpl *m_indexer;

		// Extent
		CGeoRect<double> m_layerExtent;

		// deprecated since causing slow
		//std::vector<unsigned long> m_renderedIdxes;

		// in order to enhance the rendering performance
		int m_maxVertices;
		CGeoPoint<double> *m_maxCoords;

		// Grid cache
		static ShapeCache m_caches;

		// Shapes Id in grid
		static std::map<string, std::vector<std::vector<int> > > m_cachesid;

		// Shapetype of each file
		static std::map<string, int> m_shapetypes;

		// static current layer index
		static unsigned int m_curLayerIdx;

		// Readers
		static ReaderVector m_readers;

		// m_caches size
		int m_cachesize;

		// grid x y count
		int m_xcount, m_ycount;
    };
}

#endif
