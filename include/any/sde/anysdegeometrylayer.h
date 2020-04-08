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
#ifndef __ANYSDE_SDE_GEOMETRY_LAYER_H__
#define __ANYSDE_SDE_GEOMETRY_LAYER_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// adaption
#include "anysdelayer.h"

// refer to stl
#include "any/base/anystl.h"
#include "any/base/anydbgmacro.h"
using namespace AnyBase;

#include "any/bridge/gis/anyshplayer.h"
using namespace AnyBridge;

#include "any/vis/anyvectorsymbolplot.h"
using namespace AnyVis;

// refer to boost share_ptr
#include "boost/smart_ptr.hpp"
using namespace boost;

//
namespace AnySDE
{
	// forward class
	class CAnySdeGeometry;
	class CAnySdeGeometryEditor;

	/*!
	*
	**/
	class ANYSDE_CLASS CAnySdeGeometryLayer : public CAnySdeLayer
	{
		// relatives
		friend class CAnySdeQueryIndex;

		// Not permit copy & assign operations
		CAnySdeGeometryLayer(const CAnySdeGeometryLayer &other);
		const CAnySdeGeometryLayer &operator=(const CAnySdeGeometryLayer &other);

		struct ImportThreadParameter
		{
			anystring m_fileName;
			int m_from;
			int m_to;
			CAnyShpReader *m_shpreader;
			CAnyDbfReader *m_dbfeader;
		};

		struct LoadThreadParameter_Peng1
		{
			CAnyLightVector &m_parcelIds;
			std::vector<std::vector<int> > &m_relationships;
			long m_index;
			long m_taskcount;
			LoadThreadParameter_Peng1(CAnyLightVector &parcelIds, std::vector<std::vector<int> > &relationships) : \
				m_parcelIds(parcelIds), m_relationships(relationships), m_index(0), m_taskcount(0)
			{
			}
		};

		struct LoadThreadParameter_Peng2
		{
			CAnySdeIndexGrid *m_grid;
			std::vector<long> &m_idxes;
			std::vector<int> &m_relationships;
			long m_from;
			long m_to;
			LoadThreadParameter_Peng2(CAnySdeIndexGrid *oneGrid, std::vector<long> &idxes, std::vector<int> &relationships) : \
				m_grid(oneGrid), m_idxes(idxes), m_relationships(relationships), m_from(0), m_to(0)
			{
			}
		};

		struct LoadThreadParameter_Peng3
		{
			CAnyLightVector &m_parcelIds;
			long m_from;
			long m_to;
			LoadThreadParameter_Peng3(CAnyLightVector &parcelIds) : m_parcelIds(parcelIds), m_from(0), m_to(0)
			{
			}
		};

		struct LoadGridThreadParameter
		{
			CAnyAccessor &m_accessor;
			CAnyLightVector &m_parcelIds;
			long m_from;
			long m_to;

			LoadGridThreadParameter(CAnyAccessor &accessor,CAnyLightVector &parcelIds) : m_accessor(accessor), m_parcelIds(parcelIds), m_from(0), m_to(0)
			{
			}
		};
		struct LoadGeometryThreadParameter
		{
			CAnyAccessor &m_accessor;
			CAnySdeIndexGrid *m_grid;
			std::vector<long> &m_idxes;

			long m_from;
			long m_to;

			LoadGeometryThreadParameter(CAnyAccessor &accessor, CAnySdeIndexGrid *oneGrid, std::vector<long> &idxes) : m_accessor(accessor), m_grid(oneGrid), m_idxes(idxes), m_from(0), m_to(0)
			{
			}
		};
		struct SortGeometryThreadParameter
		{
			CAnyAccessor &m_accessor;
			CAnyLightVector &m_parcelIds;
			long m_from;
			long m_to;
			CAnySdeIndexGrid::BorderGeometryVector &m_borders;

			SortGeometryThreadParameter(CAnyAccessor &accessor,CAnyLightVector &parcelIds,CAnySdeIndexGrid::BorderGeometryVector &borders) : m_accessor(accessor), m_parcelIds(parcelIds), m_from(0), m_to(0),m_borders(borders)
			{
			}
		};

		class LoadTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			LoadTask(int taskcount, int index, CAnySdeGeometryLayer* layer, CAnyLightVector &parcelIds, std::vector<std::vector<int> > &relationships, CAnyCPUScheduler *scheduler);
			~LoadTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnySdeGeometryLayer *m_layer;
			CAnyLightVector &m_parcelIds;
			std::vector<std::vector<int> > &m_relationships;
			CAnyCPUScheduler *m_scheduler;
		};

		class CommitTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			CommitTask(int taskcount, int index, CAnySdeGeometryLayer* layer, int operationtype, \
				int toaddstart = -1, int toaddend = -1, bool istoUAD = false, bool istoVer = false, bool modifyfeature = false, double nowtime = 0);
			~CommitTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnySdeGeometryLayer *m_layer;
			int m_operationtype;
			int m_toaddstart;
			int m_toaddend;
			bool m_istoUAD;
			bool m_istoVer;
			bool m_modifyfeature;
			double m_nowtime;
		};

		class ImportFromSHPTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			ImportFromSHPTask(int taskcount, int index, CAnySdeGeometryLayer* layer, std::vector<boost::shared_ptr<ShpGeometry> > &shpgeometries, CAnyCPUScheduler *scheduler);
			~ImportFromSHPTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnySdeGeometryLayer *m_layer;
			std::vector<boost::shared_ptr<ShpGeometry> > &m_shpgeometries;
			std::vector<boost::shared_ptr<CAnySdeGeometry> > m_geometries;
			CAnyCPUScheduler *m_scheduler;
		};

		class ImportFromDBFTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			ImportFromDBFTask(int taskcount, int index, std::vector<string> &cmds);
			~ImportFromDBFTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			std::vector<string> m_cmds;
		};

		class RenderParcelTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			RenderParcelTask(int taskcount, int index, CAnySdeGeometryLayer* layer, CAnyCPUScheduler *scheduler, std::vector<long> &gridIdxsToLoad,\
				CAnyCanvas &canvas, const CGeoRect<double> &validExtent, CGeoRect<double> &scrExtent, CGeoRect<double> &clipExtent, CAnyLightVector &parcelIds);
			~RenderParcelTask();
			void DoExecuteTask();
		
		private:
			std::vector<long> &m_gridIdxsToLoad;
			CAnyCanvas &m_canvas;
			CAnyLightVector &m_parcelIds;

			int m_taskcount;
			int m_index;
			CAnySdeGeometryLayer *m_layer;
			CAnyCPUScheduler *m_scheduler;
			CGeoRect<double> m_validExtent;
			CGeoRect<double> m_scrExtent;
			CGeoRect<double> m_clipExtent;
		};
	public:
		struct GisProj
		{
			int type;
			string name;
			string proj;
			double lon_0;
			double lat_0;
			double lat_1;
			double lat_2;
			double x_0;
			double y_0;
			double k;
			string units;
			int zonetype;
			int iscurrent;
			int issystem;
			GisProj() : type(-1), name(""), proj(""), lon_0(99999), lat_0(99999), lat_1(99999), lat_2(99999), x_0(0), y_0(0), k(99999), units(""), zonetype(99999),iscurrent(0),issystem(1)
			{
			}
			const GisProj &operator=(const GisProj &other)
			{
				if(this == &other)
				{
					return *this;
				}
				type = other.type;
				name = other.name;
				proj = other.proj;
				lon_0 = other.lon_0;
				lat_0 = other.lat_0;
				lat_1 = other.lat_1;
				lat_2 = other.lat_2;
				x_0 = other.x_0;
				y_0 = other.y_0;
				k = other.k;
				units = other.units;
				zonetype=other.zonetype;
				iscurrent=other.iscurrent;
				issystem=other.issystem;
				return *this;
			}
		};
		struct GisCoord
		{
			int type;
			string name;
			string datnum;
			string ellps;
			double a;
			double b;
			double rf;
			string ellps_name;
			double deltaX;
			double deltaY;
			double deltaZ;
			double rX;
			double rY;
			double rZ;
			double scale;
			int iscurrent;
			int issystem;
			GisCoord() : type(-1), name(""), datnum(""), ellps(""), a(-1), b(-1), rf(-1), ellps_name(""), \
				deltaX(0), deltaY(0), deltaZ(0), rX(0), rY(0), rZ(0), scale(0),iscurrent(0),issystem(1)
			{
			}
			const GisCoord &operator=(const GisCoord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				type = other.type;
				name = other.name;
				datnum = other.datnum;
				ellps = other.ellps;
				a = other.a;
				b = other.b;
				rf = other.rf;
				ellps_name = other.ellps_name;
				deltaX = other.deltaX;
				deltaY = other.deltaY;
				deltaZ = other.deltaZ;
				rX = other.rX;
				rY = other.rY;
				rZ = other.rZ;
				scale = other.scale;
				iscurrent=other.iscurrent;
				issystem=other.issystem;
				return *this;
			}
		};
		/*!
		*	classical contour operations
		**/
		enum SDEGeometryMapOperation
		{
			SDEGeometry_MO_Unknown,
			SDEGeometry_MO_Blank,
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySdeGeometryLayer(long layerIdx, CAnyView &view, const string &file, const string &featureTable, \
			const string &geometryTable, const string &indexTable, const string &configureTable, const string &versiontreeTable, long elementIdx = 0);

		/*!
		*
		**/
		~CAnySdeGeometryLayer();

	public:
		//
		//
		//
		/*!
		*
		**/
		unsigned int GetLayerType();

		/*!
		*20170526
		**/
		void SetLayerType(int layertype);

		//
		// override
		//
		/*!
		*
		**/
		CGeoPoint<double> *MakeRasterization(const CGeoRect<double> &extent, const string &field, int rows, int cols);

		//
		// load & create geometry & index
		//
		/*!
		*
		**/
		void Release();
		void Load(const CGeoRect<double> &extent, short indexType = IT_RegularGrid);
		void LoadAllExtent(const CGeoRect<double> &extent, short indexType = IT_RegularGrid);
		void LoadMT(const CGeoRect<double> &extent, short indexType = IT_RegularGrid);
		void LoadMTF_Peng(const CGeoRect<double> &extent, short indexType = IT_RegularGrid);
		void LoadThread_Peng_Loop1(const LoadThreadParameter_Peng1 &parameter);
		void LoadThread_Peng_Loop2(const LoadThreadParameter_Peng1 &parameter);
		void LoadThread_Peng_Loop3(const LoadThreadParameter_Peng3 &parameter);
		void LoadAsSimpleTask(const CGeoRect<double> &extent, short indexType = IT_RegularGrid);
		void LoadGridThread(const LoadGridThreadParameter &parameter);
		void LoadGeometryThread(const LoadGeometryThreadParameter &parameter);
		void SortGeometryThread(const SortGeometryThreadParameter &parameter);

		void Update();
		void ReCreateIndexAndLoad(const CGeoRect<double> &extent, short indexType = IT_RegularGrid);
		void LoadConfigure();

		void ImportFromSHP(CAnyShpReader *shpreader, CAnyFunctor &progress);
		void ImportFromSHPMT(CAnyShpReader *shpreader, CAnyFunctor &progress);
		bool ImportFromSHPMTF(CAnyShpReader *shpreader, CAnyFunctor &progress);
		void ImportSHPThread(const ImportThreadParameter &parameter);

		void ImportFromDBF(CAnyDbfReader *curReader, CAnyFunctor &progress);
		void ImportFromDBFMT(CAnyDbfReader *curReader, CAnyFunctor &progress);
		bool ImportFromDBFMTF(CAnyDbfReader *curReader, CAnyFunctor &progress);
		void ImportDBFThread(const ImportThreadParameter &parameter);

		void ImportFromPoints(std::vector<std::vector<CGeoPoint<double> > > &points, int type);

		void ExportToSHPFile(string filename);

		bool InsertIndex(boost::shared_ptr<CAnySdeGeometry> geometry);
		bool AddGeometry(boost::shared_ptr<CAnySdeGeometry> geometry, bool isSort = true);
		bool UpdateGeometry(boost::shared_ptr<CAnySdeGeometry> geometry, bool isSort = true);
		bool RemoveGeometry(boost::shared_ptr<CAnySdeGeometry> geometry, bool isSort = true);
		bool GetGeometrys(CAnyAccessor &accessor, std::vector<long> &geometryIdxs, std::vector<int> &relationships, int looptype, std::vector<boost::shared_ptr<CAnySdeGeometry> > &geometries, CAnySdeIndexGrid *curGrid = NULL, bool needinorder = true);
		bool GetGeometrys(CAnyAccessor &accessor, std::vector<long>::iterator &first, std::vector<long>::iterator &last, std::vector<boost::shared_ptr<CAnySdeGeometry> > &geometries, CAnySdeIndexGrid *curGrid = NULL);
		bool GetGeometrys_Peng1(CAnyAccessor &accessor, std::vector<long> &geometryIdxs, std::vector<int> &relationships, std::vector<boost::shared_ptr<CAnySdeGeometry> > &geometries, CAnySdeIndexGrid *curGrid = NULL);
		bool GetGeometrys_Peng2(LoadThreadParameter_Peng2 &parameter);
		void GetAllGeometryPts(std::vector<std::vector<CGeoPoint<double> > > &allpts);

		//
		// commit & version
		//
		void CommitConfigure();
		void Commit(bool istoUAD = false, bool istoVer = false, bool modifyfeature = false, bool ischeckidadd = true);
		void CommitMT(bool istoUAD = false, bool istoVer = false, bool modifyfeature = false, bool ischeckidadd = true);
		void LoadVersion();
		int NextVersion();
		void SwithToOtherVersion(int version);
		void SwithToOtherRecordVersion(int version);
		void SwithToOtherIndexVersion(int version);
		void SwithToOtherTableVersion(int version);
		void DeleteVersion(int version);
		void GetValidVersions(std::vector<int> &versions, std::vector<string> &versiondatas);
		void CreateNodataVersion();
		void BackUpCurrentVersion();
		int GetVersionType(int version);
		int GetParentVersion(int version);
		bool IsVersionHasData(int version);

		//
		// inherited functions as a hook
		//
		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect = false);
		bool MouseDown(const CGeoPoint<double> &scrPoint);
		bool MouseMove(const CGeoPoint<double> &scrPoint);
		bool MouseUp(const CGeoPoint<double> &scrPoint);
		bool DoubleClick(const CGeoPoint<double> &scrPoint);
		void SetHighLight(std::vector<unsigned long> &idxes);

		//
		// spatial analysis
		//
		/*!
		*
		**/
		bool Query(const CGeoPoint<double> &pt, std::vector<unsigned long> &idxes);
		bool Query(const CGeoRect<double> &rect, std::vector<unsigned long> &idxes, bool isCircle = false);
		bool Query(const std::vector<CGeoPoint<double> > &poly, std::vector<unsigned long> &idxes);

		//
		// spatial query
		//
		/*!
		*
		**/
		bool IsPolygon(const boost::shared_ptr<CAnySdeGeometry> geometry);
		bool IsPolygons(const boost::shared_ptr<CAnySdeGeometry> geometry);
		bool IsPolyline(const boost::shared_ptr<CAnySdeGeometry> geometry);
		bool IsPolylines(const boost::shared_ptr<CAnySdeGeometry> geometry);
		bool IsPoint(const boost::shared_ptr<CAnySdeGeometry> geometry);
		bool IsPoints(const boost::shared_ptr<CAnySdeGeometry> geometry);
		bool IsSkipped(const CGeoRect<double> &clipBox, double xMin, double yMin, double xMax, double yMax, CGeoRect<double> &bounding);
			
		//
		// feature operation
		//
		/*!
		*
		**/
		void CreateNewFeatureTable(string featuretablename, std::vector<DBFieldDesc> &fields);
		void SwitchFeatureTable(string featuretablename);
		void SetFeatureTables(std::vector<string> &featuretables);
		std::vector<string> GetFeatureTables();
		void SetGeometryPropertyTables(int geometryid, int elementid, std::vector<string> &propertytables);
		void GetGeometryPropertyTables(int geometryid, int &elementid, std::vector<string> &propertytables);
		void GetAllGeometryPropertyTables(CAnyAccessor &accessor, std::vector<int> &geometryids, std::vector<int> &elementids, std::vector<std::vector<string> > &propertytables);
		void RemoveAllFeatureTables(int idx = -1);
		void LoadFeatures(string featurename);	
		void LoadAllFeatures(string orderfieldname = "", bool isuporder = true);
		void LoadAllFeaturesDesc();
		void ClearAllFeaturesCache();
		void GetAllFeatures(std::vector<std::vector<string> > &allfeatures, std::vector<string> &allfeaturenames, int startpos, int endpos);
		int GetAllFeaturesCount();
		void GetAllFeaturesField(std::vector<DBFieldDesc> &allfeaturefields);
		bool QueryFeature(std::string &wheresentence, std::vector<int> &resultgeometryids);
		void LoadFeatureRangeColor(string &featurename, std::vector<string> &valueranges, std::vector<int> &colors,	std::vector<int> &minColors, std::vector<int> &maxColors);
		void SetFeatureRangeColor(const string &featurename, const std::vector<string> &valueranges, const std::vector<int> &colors, std::vector<int> &minColors, std::vector<int> &maxColors);
		void LoadFeaturePorperties(string &featurename, std::vector<string> &valueranges, std::vector<double> &symbolSizes, std::vector<int> &symbolStyles, std::vector<std::string> &textFields,\
			std::vector<double> &minSymbolSizes, std::vector<double> &maxSymbolSizes, std::vector<std::string> &symbolSizeFields);
		void SetFeaturePorperties(const string &featurename, const std::vector<string> &valueranges, const std::vector<double> &symbolSizes, const std::vector<int> &symbolStyles, const std::vector<std::string> &textFieldss,\
			const std::vector<double> &minSymbolSizes, const std::vector<double> &maxSymbolSizes, const std::vector<std::string> &symbolSizeFields);
		void LoadFeatureSymbolStyle(string &featurename, std::vector<string> &valueranges, std::vector<int> &symbolStyles);//20171227 load\set symbol style only
		void SetFeatureSymbolStyle(const string &featurename, const std::vector<string> &valueranges, const std::vector<int> &symbolStyles);
		void LoadFeatureSymbolSize(string &featurename, std::vector<string> &valueranges, std::vector<double> &symbolSizes, double &minSymbolSize, double &maxSymbolSize,	int &polygonsymbolstyle, int &polygonsymbolcolor);//20171227 load\set symbol size only
		void SetFeatureSymbolSize(const string &featurename, const std::vector<string> &valueranges, const std::vector<double> &symbolSizes, const double &minSymbolSize, const double &maxSymbolSize,	const int &polygonsymbolstyle,const int &polygonsymbolcolor);
		void LoadFeatureLabelStyle(string &featurename, std::vector<string> &valueranges, std::vector<AnyMap::LabelStyle> &labelstyles);
		void SetFeatureLabelStyle(const string &featurename, const std::vector<string> &valueranges, const std::vector<AnyMap::LabelStyle> &labelstyles);
		static int GetClassidBySource(string source);
		
		bool UpdateFeature(const PropertyVector &props);
		bool NewFeature(PropertyVector &props);//20170320
		bool MergeFeature(FeatureVector propsFrom, PropertyVector &props);//20170511 Create a new feature record from exist ones when merging
		bool CopyFeature(PropertyVector propsFrom, PropertyVector &props);//20170511 Create a new feature record from an exist one
		bool GetFeatureRecord(int idx, PropertyVector &props);//20170323
		static string PropertyTypeTrans(int fieldType, boost::any fieldVal);//20170503 transform boost::any to string
		void GetAllRecordsString(std::vector<std::vector<string> > &allfeatures, std::vector<string> &allfeaturenames);//20170503
		void GetRecordsForAttributeTable( std::vector<std::vector<string> > &allfeatures, std::vector<string> &allfeaturenames, std::vector<std::vector<double> > &geoidelementid);
		void AddField(int fieldType);//20170613 add a field in m_latestfeature
		void DeleteFields(std::vector<long> fieldNumbers);//20170613 delete fields in m_latestfeature
		static string GetLegalFieldName(const char* fileName);//20180110 field name cannot start with number,cannot contain '-' and '.'
		//
		// property
		//
		/*!
		*
		**/
		void GetShowChartFromDB(std::vector<int> &red, std::vector<int> &green, std::vector<int> &blue, std::vector<double> &height, std::vector<double> &width, std::vector<string> &whichfieldname);
		void GetShowChartFromDB(std::vector<int> &red, std::vector<int> &green, std::vector<int> &blue, std::vector<double> &height, std::vector<double> &width, std::vector<CGeoPoint<double> > &positions, std::vector<string> &datas);
		void SetShowChartToDB(std::vector<int> red, std::vector<int> green, std::vector<int> blue, std::vector<double> height, std::vector<double> width, std::vector<string> whichfieldname);


		//
		// geometry's edition
		//
		/*!
		*
		**/
		bool AdjustLines(std::vector<unsigned long> &idxes, const std::vector<CGeoPoint<double> > &poly, bool &isFirstUpdated, bool &isSecondUpdated, bool isOverHead = true);
		void AddIntoCopyGeometries(std::vector<unsigned long> &idxes);
		void GetGeometriesToPaste(std::vector<boost::shared_ptr<CAnySdeGeometry>> &geometries);
		void GetGeometriesInFeatureTable(std::vector<long> &ids);
		void SimplifyGeometries(std::vector<unsigned long> &idxes, int methodType, double para, CAnySdeGeometryEditor *editor);
		void DoGetGeometriesByIndexes(std::vector<unsigned long> &idxes, std::vector<boost::shared_ptr<CAnySdeGeometry>> &geometries);
		void CreateEnclosingPolygon(std::vector<unsigned long> &idxes, std::vector<CGeoPoint<double> > &outputpoints);
		void CheckConfilctGeometries(std::vector<int> &confilctids, std::vector<string> &confilcttypes);

		/*!
		*2015/10/28
		**/
		static void DoGrahamScanning(std::vector<CGeoPoint<double> > &inputpoints, std::vector<CGeoPoint<double> > &outputpoints);
		static inline unsigned int DoGetColor(double curValue, double minValue, double maxValue, int minColor, int midColor, int maxColor);

		/*!
		*
		**/
		static inline void SetLinePattern( LineStyle &style, int linePattern );
		static inline void DoRenderMarkedPoint(CAnyCanvas &canvas,const CGeoPoint<double> &scrPt, SymbolStyle &style, \
			int order = -1, bool isDefaultColor = false, int symbolStyle = -1, int color = 0, double symbolSize = -1., double lineWidth = -1., int lineStyle = 0, int lineColor = RGB(0,0,0));

		void Intersection(boost::shared_ptr<CAnySdeGeometry> geometry1,boost::shared_ptr<CAnySdeGeometry> geometry2, std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries, int outputgeometrytype);
		void Union(boost::shared_ptr<CAnySdeGeometry> geometry1,boost::shared_ptr<CAnySdeGeometry> geometry2, std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries);
		void Erase(boost::shared_ptr<CAnySdeGeometry> geometry1,boost::shared_ptr<CAnySdeGeometry> geometry2, std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries);
		void SymDifference(boost::shared_ptr<CAnySdeGeometry> geometry1,boost::shared_ptr<CAnySdeGeometry> geometry2, std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries);

		void DoRenderCustomSymbol(CAnyCanvas &canvas,const CGeoPoint<double> &scrPt, SymbolStyle &style, int symbolStyle = -1, int color = 0, double symbolSize = -1.);
		
		/*!
		*
		**/
		void DoSetBlankArea(const std::vector<CGeoPoint<double> > &trackMapPts);	
				
		/*!
		*
		**/
		void DoRenderBlankArea(CAnyCanvas &canvas);

		/*!
		*
		**/
		void ReleaseSymbolElements();

		void ImportFromPRJ(const string prjwkt, GisCoord &giscood, GisProj &gisproj);
		
	private:

		//2015/10/28: graham related
		static CGeoPoint<double> m_theleftpt;
		static bool CompareGraham(const CGeoPoint<double> &a, const CGeoPoint<double> &b);
		static double Cross(const CGeoPoint<double> &a, const CGeoPoint<double> &b, const CGeoPoint<double> &c);
		static bool Getdistance(const CGeoPoint<double> &a, const CGeoPoint<double> &b);
		
		/*!
		*
		**/
		static bool CompareGeometryIdx(const boost::shared_ptr<CAnySdeGeometry> first, const boost::shared_ptr<CAnySdeGeometry> second)
		{
			return first->m_idx < second->m_idx;
		}
			
		/*!
		*
		**/
		bool IsTooShort(CGeoPoint<double> &scrCoord, CGeoPoint<double> &prevCoord);
		bool IsRemoveByEdge(CGeoPoint<double> &scrCoord, CGeoPoint<double> &prevCoord, CGeoPoint<double> &nextCoord);
		bool IsRemoveByArea(CGeoPoint<double> &scrCoord, CGeoPoint<double> &prevCoord, CGeoPoint<double> &nextCoord);
		bool IsRemoveByDP(CGeoPoint<double> &scrCoord, CGeoPoint<double> &prevCoord, CGeoPoint<double> &nextCoord);
		bool IsSimplifyEdge2Point(CGeoPoint<double> &scrCoord, CGeoPoint<double> &prevCoord, CGeoPoint<double> &nextCoord,CGeoPoint<double> &next2Coord);
		CGeoPoint<double> SimplifyEdge2Point(CGeoPoint<double> &Coord1, CGeoPoint<double> &Coord2,CGeoPoint<double> &Coord3, CGeoPoint<double> &Coord4);


		/*!
		*2015/6/26
		**/
		void RenderGeometryPrimitives(const CGeoRect<double> &validExtent, CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, bool isRenderLabel = true, bool isForSelection = false,\
			const CGeoRect<double> &scrExtent = CGeoRect<double>(), const CGeoRect<double> &clipExtent = CGeoRect<double>());
		void MakeSimplification(std::vector<CGeoPoint<double> > &coords,const CGeoRect<double> &clipExtent, CAnyLightVector &clipPts,int &coordNumber, bool isLine = true);
	
		bool SimplifyLine(const boost::shared_ptr<CAnySdeGeometry> oneGeometry,const CGeoRect<double> &clipExtent, CAnyLightVector &clipPts,int &coordNumber, bool isOnlyGetCoords = false);
		void DrawLine(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, bool isForSelection = false, bool isRenderLabel = true);
		void DrawLineSelection(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, CAnyLightVector &clipPts);

		bool SimplifyLines(const boost::shared_ptr<CAnySdeGeometry> oneGeometry,int order, const CGeoRect<double> &clipExtent, CAnyLightVector &clipPts,  int &coordNumber);
		void DrawLines(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, bool isForSelection = false, bool isRenderLabel = true);
		void DrawLinesSelection(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding,CAnyLightVector &clipPts);

		bool SimplifyPoly(const boost::shared_ptr<CAnySdeGeometry> oneGeometry,const CGeoRect<double> &clipExtent, int ringnum, CAnyLightVector &clipPts,  int &coordNumber, bool isOnlyGetCoords = false);
		void DrawPoly(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, bool isForSelection = false, bool isRenderLabel = true);
		void DrawPolySelection(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, CAnyLightVector &clipPts);
		bool DrawPolygon(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &clipExtent,PolyStyle style);//20180524 render polygon with interior rings
		bool DrawMultiPolygon(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &clipExtent,PolyStyle style,int order);//20180524 render multipolygon

		bool SimplifyPolys(const boost::shared_ptr<CAnySdeGeometry> oneGeometry,int order, const CGeoRect<double> &clipExtent, int ringnum, CAnyLightVector &clipPts,  int &coordNumber, bool isOnlyGetCoords = false);
		void DrawPolys(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, bool isForSelection = false, bool isRenderLabel = true);
		void DrawPolysSelection(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, CAnyLightVector &clipPts);
		
		void DrawPoint(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, bool isForSelection = false, bool isRenderLabel = true);
		void DrawPointSelection(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, std::vector<CGeoPoint<double> > &coords, CGeoPoint<double> &mapCoord, CGeoPoint<double> &scrCoord);
		void DrawPoints(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, bool isForSelection = false, bool isRenderLabel = true);
		void DrawPointsSelection(CAnyCanvas &canvas, const boost::shared_ptr<CAnySdeGeometry> oneGeometry, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent, const CGeoRect<double> &bounding, CGeoPoint<double> &scrCoord);

		void FillPolygonByLitho(CAnyCanvas &canvas, CAnyView &curView, const boost::shared_ptr<CAnySdeGeometry> oneGeometry);
		/*!
		*2016/8/31: set symbol size by field
		**/
		void GetRenderSymbolSize(long geometryIdx, const std::string &field, double &symbolSize);

		void GetRenderLabel(long geometryIdx, std::string &label);
		void DoRenderLabel(CAnyCanvas &canvas, const CGeoPoint<double> &pos, const std::string &label, const LabelStyle &style, CGeoPoint<double> *alongPts = 0, int num = 0);
		void DoRenderSelectedGeometries(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent);
		void RenderRasterScanline(const CGeoRect<double> &validExtent, CAnyCanvas &canvas,const boost::shared_ptr<CAnySdeGeometry> oneGeometry);

		void DoRenderBorderLines(CAnyCanvas &canvas,const CGeoRect<double> mapExtent, int flag, int tickcount);

		bool IsIgnored(const CGeoRect<double> &geometryBounding);
		bool IsIgnored(const CGeoRect<double> &geometryBounding,const CGeoRect<double> &geometryboundingenlarged);

		/*!
		*
		**/
		void DoAddGeometryIntoCache(boost::shared_ptr<CAnySdeGeometry> geometry);
		void DoAddGeometryIntoCache(GeometryVector &geometries);
		void DoSortGeometryInCache();
		void DoRemoveGeometryFromCache(boost::shared_ptr<CAnySdeGeometry> geometry);
		void SetFeatureTables(const std::string &featureTable);

		void LoadRenderingGrids(std::vector<long> &gridIdxs, std::vector<CAnySdeIndexGrid *> &grids);
		void PaintOneGrid(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, CAnySdeIndexGrid *oneGrid, CGeoRect<double> &scrExtent, CGeoRect<double> &clipExtent, bool isRenderLabel = true);
		
		struct RenderThreadParameter
		{
			std::vector<boost::shared_ptr<CAnySdeGeometry> > m_geometries;
			const CGeoRect<double> &m_clipBox;
			const CGeoRect<double> &m_clipExtent;
			CAnyCanvas &m_canvas;
			bool m_isRenderLabel;

			RenderThreadParameter(const CGeoRect<double> &clipBox, const CGeoRect<double> &clipExtent, CAnyCanvas &canvas) : m_clipBox(clipBox), m_clipExtent(clipExtent), m_canvas(canvas),m_isRenderLabel(true)
			{
			}
		};
		void RenderThread(const RenderThreadParameter &parameter);
		void WaitPoolIdleWithNotification(CAnyCPUScheduler* scheduler);

		void DoRenderTopoErrorGeometries(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, const CGeoRect<double> &scrExtent, const CGeoRect<double> &clipExtent);

	public:
		// batches for DB performance or thread pool
		// below all are shared by grid cache
		// ...
		GeometryVector m_toReads;	// as cache, may load all rows | may not to load partial and LRU indicator to each geometry not grid
		GeometryVector m_toAdds;
		GeometryVector m_toDeletes;
		GeometryVector m_toUpdates;
	
		// the latest and cached feature definition
		std::map<int, string> m_features;
		FeatureVector m_latestfeatures;
		FeatureVector m_allfeatures;
		std::vector<DBFieldDesc> m_allfeaturesdesc;
		std::vector<string> m_featuretables;

		//2015/6/2: store current used feature table
		std::string m_curFeatureTable;

		// configure parameters
		int m_taskcount;
		int m_finishedtaskcount;

		bool m_ismultiline;
		bool m_isDirectInsertCache;
		int m_commitgeometries;	// commit geometries once
		double m_commitsecond;	// commit per seconds
		short m_commitfeatures;	// commit feature records once

		//
		std::vector<std::vector<unsigned long> > m_rastercache;
		bool m_isScanlineMode;
		double m_widthmappixelrate;
		double m_heightmappixelrate;
		std::map<int, std::vector<CGeoRect<double> > > m_scanlineextentscache;
		int m_scanlineextentscachelimit;

		//2015/6/23
		std::vector<unsigned long> m_copyGeometries;
		//2015/9/21, rectangle positions for geometry's label
		std::vector<CGeoRect <double>> m_labelRectPositions;

		double m_loadtime;//time when the layer is loaded
		bool m_isrenderthread;

		bool m_islayerpainted;
		bool m_islabelpainted;
		//20171020 draw border axis
		bool m_isdrawborder;
		int m_rowtickcount;
		int m_coltickcount;

		int m_labelpos;
		//point symbols
		std::map<int,std::vector<CAnyVectorSymbolPlot::VectorSymbolElement *>> m_symbolelements;
		//polygon filling lithos
		CAnyVectorSymbolPlot::VectorSymbolMap m_vectorSymbols;
		std::string m_curVectorSymbol;

		// map operation
		long m_operation;
		// blank areas for map output
		std::vector<std::vector<CGeoPoint<double>> > m_blanks;
		std::vector<std::vector<CGeoPoint<double> >> m_boderlines;

		//topo
		bool m_isdrawTopoErrors;
		std::vector<boost::shared_ptr<CAnySdeGeometry> > m_topoErrorGeometries;
	};
}
#endif