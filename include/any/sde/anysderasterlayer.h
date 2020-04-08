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
#ifndef __ANYSDE_SDE_RASTER_LAYER_H__
#define __ANYSDE_SDE_RASTER_LAYER_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// adaption
#include "anysdelayer.h"
#include "anysnesim.h"
// BMP
#include "any/base/anybmpbasic.h"
using namespace AnyBase;
// visitor pattern
#include "any/base/loki/visitor.h"
using namespace AnyBase::Loki;
//
namespace AnySDE
{
	/*!
	*
	**/
	class ANYSDE_CLASS CAnySdeRasterLayer : public CAnySdeLayer
	{
	public:
		//
		LOKI_DEFINE_VISITABLE()
		// Not permit copy & assign operations
		CAnySdeRasterLayer(const CAnySdeRasterLayer &other);
		const CAnySdeRasterLayer &operator=(const CAnySdeRasterLayer &other);
	public:
		class ReadFileTestTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			ReadFileTestTask(int taskcount, int index, string filepath, int filelength, char* datareaded, CAnyCPUScheduler *scheduler);
			~ReadFileTestTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			string m_filepath;
			int m_filelength;
			char* m_datareaded;
			CAnyCPUScheduler *m_scheduler;
		};

		class WriteFileTestTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			WriteFileTestTask(int taskcount, int index, string filepath, int filelength, char* datatowrite, CAnyCPUScheduler *scheduler);
			~WriteFileTestTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			string m_filepath;
			int m_filelength;
			char* m_datatowrite;
			CAnyCPUScheduler *m_scheduler;
		};

		class SaveBigPictureTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			SaveBigPictureTask(int taskcount, int index, CAnySdeRasterLayer* layer, int elementid, int classid, string username, string filepath, int maxversion, \
				double timestamp, int picturetype, bool iscreatefile, int xpixel, int ypixel, bool ismedianfilter, int endlevelMT, int &uploadedfile, std::vector<int> &uploadfailedtileids, CAnyCPUScheduler *scheduler);
			~SaveBigPictureTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnySdeRasterLayer *m_layer;
			int m_elementid;
			int m_classid;
			string m_username;
			string m_filepath;
			int m_maxversion;
			double m_timestamp;
			int m_picturetype;
			bool m_iscreatefile;
			int m_xpixel;
			int m_ypixel;
			bool m_ismedianfilter;
			int m_endlevelMT;
			int &m_uploadedfile;
			std::vector<int> &m_uploadfailedtileids;
			CAnyCPUScheduler *m_scheduler;
			int m_bandcount;//raster band count of image
			int panBandMap[3];
		};

		class SaveBigPictureTask3D : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			SaveBigPictureTask3D(int taskcount, int index, CAnySdeRasterLayer* layer, int elementid, int classid, string username, string filepath, int maxversion, \
				double timestamp, int picturetype, bool iscreatefile, int xpixel, int ypixel, int zpixel, int endlevelMT, int &uploadedfile, std::vector<int> &uploadfailedtileids, CAnyCPUScheduler *scheduler);
			~SaveBigPictureTask3D();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnySdeRasterLayer *m_layer;
			int m_elementid;
			int m_classid;
			string m_username;
			string m_filepath;
			int m_maxversion;
			double m_timestamp;
			int m_picturetype;
			bool m_iscreatefile;
			int m_xpixel;
			int m_ypixel;
			int m_zpixel;
			int m_endlevelMT;
			int &m_uploadedfile;
			std::vector<int> &m_uploadfailedtileids;
			CAnyCPUScheduler *m_scheduler;
			int m_bandcount;//raster band count of image
			int panBandMap[3];
		};

		class LoadPictureData3DTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			LoadPictureData3DTask(int taskcount, int index, CAnySdeRasterLayer *parent, std::vector<CGeoPoint<double> > &pts, double widthmappixelrate, double heightmappixelrate, double depthmappixelrate, CAnyCPUScheduler *scheduler);
			~LoadPictureData3DTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnySdeRasterLayer *m_parent;
			std::vector<CGeoPoint<double> > m_pts;
			double m_widthmappixelrate;
			double m_heightmappixelrate;
			double m_depthmappixelrate;
			CAnyCPUScheduler *m_scheduler;
		};
	public:
		/*!
		* record of "info_assessment_element_raster"
		**/
		struct RasterRecord
		{
			long m_elementIdx;
			long m_layerIdx;
			CGeoRect<double> m_extent;
			void *m_image;
			double m_timestamp;
			int m_imgwidth;
			int m_imgheight;
			int m_imgfilelength;

			/*!
			*
			**/
			RasterRecord() : m_elementIdx(-1), m_layerIdx(-1), m_image(0), m_imgwidth(0), m_imgheight(0), m_imgfilelength(0)
			{
			}
		};

		struct PictureData
		{
			long m_tileid;
			int m_hit;
			int m_bitcount;
			CGeoRect<int> m_extent; // the position against the whole image
			int m_zmin; // the position against the whole image
			int m_zmax; // the position against the whole image
			CGeoRect<double> m_layerextent;
			double m_layerzmin;
			double m_layerzmax;
			char* m_parameter;
			int m_parameterlength;

			PictureData() : m_tileid(-1), m_hit(0), m_bitcount(0), m_zmin(0), m_zmax(0), m_layerzmin(0), m_layerzmax(0), m_parameter(0), m_parameterlength(0)
			{
			}
			~PictureData()
			{
				if(m_parameter)
				{
					delete m_parameter;
					m_parameter = NULL;
				}
			}
		};
		//for tiff 
		typedef struct tagIMAGEFILEHEADER
		{
			WORD byteOrder;
			WORD version;
			DWORD offsetToIFD;
		}IFH;
		//for tiff 
		typedef struct tagDIRECTORYENTRY
		{
			WORD tag;
			WORD type;
			DWORD length;
			DWORD valueOffset;
		}DE;
	public:
		//
		//
		//
		/*!
		* the feature table "info_assessment_element_raster"
		**/
		CAnySdeRasterLayer(long layerIdx, CAnyView &view, const string &file, const string &featureTable, \
			const string &rasterTable, const string &indexTable, const string &configureTable, const string &versiontreeTable, long elementIdx = 0);

		/*!
		*
		**/
		~CAnySdeRasterLayer();

	public:
		//
		// DB\exporting interface
		//
		/*!
		*
		**/
		void Release();

		/*!
		*
		**/
		void Load(const CGeoRect<double> &extent, short indexType = IT_RegularGrid);
		
		/*!
		*
		**/
		void Commit(bool istoUAD = false, bool istoVer = false, bool modifyfeature = false, bool ischeckidadd = true);
				
		/*!
		*
		**/
		bool InitGFSClient(string gfspara, string gfsname);
						
		/*!
		*
		**/
		bool InitJobClient(string gfspara);

		//
		// importing interface
		//
		/*!
		* timestamp != 0 means USER to specifiy, timestamp = 0, means SYSTEM to generate
		**/
		bool AddRaster(const string &fileName, double timestamp = 0);

		/*!
		*
		**/
		bool AddRaster(void *image, double timestamp = 0, int imgwidth = 0, int imgheight = 0, int imgfilelength = 0);

		/*!
		*
		**/
		bool RemoveRaster(double timestamp);

		//
		// inherited functions
		//
		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect = false);

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
		bool Query(const CGeoPoint<double> &pt, std::vector<unsigned long> &idxes);
		
		/*!
		*
		**/
		bool Query(const CGeoRect<double> &rect, std::vector<unsigned long> &idxes, bool isCircle = false);

		/*!
		*
		**/
		void SetRecordExtent(const CGeoRect<double> &extent, int i);

		/*!
		*
		**/
		bool DoGetTableRecord(RasterRecord &record);

		/*!
		*
		**/
		double DoGetTimestamp();
		
		/*!
		*
		**/
		void SaveBigPicture(int elementid, int classid, string filepath, string username, CAnyFunctor *progress, bool isMT, int picturetype, bool iscreatefile, int xpixel, int ypixel, bool ismedianfilter, string gfspara = "", string gfsdir = "");
		void SaveBigPicture3D(int elementid, int classid, string filepath, string username, CAnyFunctor *progress, bool isMT, int picturetype, bool iscreatefile, int xpixel, int ypixel, int zpixel, string gfspara = "", string gfsdir = "");

		/*!
		*
		**/		
		void MedianFileter_Raw(char* imagedata, int width, int height);

		/*!
		*
		**/
		void MergeFourPicture(int leveloffset, int elementid, int classid, string username, CAnyAccessor &accessor, int maxversion, double timestamp, string filename_nodot, string filedir, \
			const CAnyFileBasic &fileBasic, const CAnyDirBasic &dirBasic, tagBITMAPFILEHEADER *strHead, RGBQUAD *strPla, BITMAPINFOHEADER *strInfo, WORD biBitCount, int dataoffset, \
			std::vector<std::vector<char*> > &imagedatas, std::vector<std::vector<CGeoRect<double> > > &imageextents, std::vector<std::vector<long> > &imagewidths, std::vector<std::vector<long> > &imageheights, \
			std::vector<std::vector<long> > &imagesublinebytes, std::vector<std::vector<std::vector<int> > > &imagemortons, std::vector<std::vector<bool> > &imagehasdatas, bool iscreatefile, bool ismedianfilter, \
			int &uploadedfile, std::vector<int> &uploadfailedtileids);
		void MergeEightPicture(int leveloffset, int elementid, int classid, string username, CAnyAccessor &accessor, int maxversion, double timestamp, string filename_nodot, string filedir, \
			const CAnyFileBasic &fileBasic, const CAnyDirBasic &dirBasic, tagBITMAPFILEHEADER *strHead, RGBQUAD *strPla, BITMAPINFOHEADER *strInfo, WORD biBitCount, int dataoffset, \
			std::vector<std::vector<char*> > &imagedatas, std::vector<std::vector<CGeoRect<double> > > &imageextents, std::vector<std::vector<double> > &imagezmins, std::vector<std::vector<double> > &imagezmaxs, std::vector<std::vector<long> > &imagewidths, std::vector<std::vector<long> > &imageheights, std::vector<std::vector<long> > &imagedepths, \
			std::vector<std::vector<long> > &imagesublinebytes, std::vector<std::vector<std::vector<int> > > &imagemortons, std::vector<std::vector<bool> > &imagehasdatas, bool iscreatefile, \
			int &uploadedfile, std::vector<int> &uploadfailedtileids);
				
		/*!
		*
		**/
		PictureData* LoadOnePictureData(int tileid);
		PictureData* LoadOnePictureData3D(int tileid);
		bool LoadPictureData3D(std::vector<CGeoPoint<double> > &pts, std::vector<PictureData*> &picturedatas, std::vector<int> &picturedataoffsets, CAnyFunctor *progress);
		bool LoadPictureData3D_MR(std::vector<CGeoPoint<double> > &pts, std::vector<unsigned int> &colors, CAnyFunctor *progress);
		void CommitPictureData(PictureData* picdata);
		void DemToColor(PictureData* picturedata);
		void ChangeChanelAndColor(PictureData* picturedata);
		void SetColorCodeToDB(int classid, std::vector<int> &channelorder, std::vector<double> &demcolorcodevals, std::vector<int> &demcolorcodecolors, bool demisdiscrete);
		void GetColorCodeFromDB(int classid, std::vector<int> &channelorder, std::vector<double> &demcolorcodevals, std::vector<int> &demcolorcodecolors, bool &demisdiscrete);
		void GetAllDemData(std::vector<std::vector<double> > &alldatas,int &height, int &width);
		void GetPictureData(int x, int y, double &datavalue, int &red, int &green, int &blue);
		/*!
		*
		**/
		bool PositionToPostile(CGeoPoint<int> Position, int fetchlevel, CGeoPoint<int> &postile);
		bool PostileToPosition(CGeoPoint<int> postile, int fetchlevel, CGeoPoint<int> &Position1, CGeoPoint<int> &Position2);
		bool Postile2Morton(CGeoPoint<int> postile, int fetchlevel, std::vector<int> &morton);
		bool Morton2Postile(std::vector<int> morton, CGeoPoint<int> &postile, int &fetchlevel);
		bool Morton2Tileid(std::vector<int> morton, int &tileid);
		bool Tileid2Morton(int tileid, std::vector<int> &morton);
		bool Morton2Tileid_OneLevel(std::vector<int> morton, int &tileid);
		bool Tileid2Morton_OneLevel(int tileid, int fetchlevel, std::vector<int> &morton);
		bool PositionToPostile3D(CGeoPoint<int> Position, int fetchlevel, CGeoPoint<int> &postile);
		bool PostileToPosition3D(CGeoPoint<int> postile, int fetchlevel, CGeoPoint<int> &Position1, CGeoPoint<int> &Position2);
		bool Postile2Morton3D(CGeoPoint<int> postile, int fetchlevel, std::vector<int> &morton);
		bool Morton2Postile3D(std::vector<int> morton, CGeoPoint<int> &postile, int &fetchlevel);
		bool Morton2Tileid3D(std::vector<int> morton, int &tileid);
		bool Tileid2Morton3D(int tileid, std::vector<int> &morton);
		bool Morton2Tileid_OneLevel3D(std::vector<int> morton, int &tileid);
		bool Tileid2Morton_OneLevel3D(int tileid, int fetchlevel, std::vector<int> &morton);
		
		/*!
		*
		**/
		void TrainAndPredict(int traintype, int randcount, double dropdatarate, bool addtotrain, int shapetype, int shapesize);
		void TrainPictureData(CAnySnesim &snesim, PictureData* picdata, int traintype, int shapetype, int shapesize);
		void PredictPictureData(CAnySnesim &snesim, PictureData* picdata, int traintype, int randcount, double dropdatarate, bool addtotrain, int shapetype, int shapesize);

		/*!
		*
		**/
		static bool ComparePictureTileid(const PictureData *first, const PictureData *second)
		{
			return first->m_tileid < second->m_tileid;
		}
		
		/*!
		*
		**/
		static bool ComparePictureHit(const PictureData *first, const PictureData *second)
		{
			return first->m_hit > second->m_hit;
		}
	public:
		// Utility IO and rendering functions given BITMAP structure
		std::vector<CAnyBmpBasic*> m_bmpUtils;
		// Persistence record
		std::vector<RasterRecord> m_records;
		// 是否透明有效
		bool m_isblend;

		int m_horlinenum;
		int m_verlinenum;
		bool m_ispaintline;
		int m_displaymode;
		bool m_ispaintadjustpoint;//是否绘制校验点
		std::vector<CGeoPoint<double> > m_adjustpoints;//校验点
		bool m_ispaintdigitizerpoint;//是否绘制矢量化点
		std::vector<CGeoPoint<double> > m_digitizerpoints;//矢量化点
		bool m_ispickingpoint;//是否正在拾取点
		bool m_iserasing;//是否正在擦除点
		bool m_iserasingstart;//
		CGeoPoint<double> m_curMouseScrPt;//mouse move

		int m_pictype;//0:栅格图片，1:大图片
		int m_quadtreeLevel;
		int m_tileSizex;
		int m_tileSizey;
		int m_tileSizez;
		int m_pixelx;
		int m_pixely;
		int m_pixelz;
		int m_showz;
		int m_nextkey;
		int m_classid;
		std::vector<PictureData*> m_picturedatas;
		int m_picturedatalimit;
		std::vector<PictureData*> m_picturedatasforMT;
		std::vector<int> m_picturedataoffsetsforMT;
		//切图片多线程所需变量
		std::vector<char*> m_imagedataforMT;
		std::vector<CGeoRect<double> > m_imageextentforMT;
		std::vector<double> m_imagezminforMT;
		std::vector<double> m_imagezmaxforMT;
		std::vector<long> m_imagewidthforMT;
		std::vector<long> m_imageheightforMT;
		std::vector<long> m_imagedepthforMT;
		std::vector<long> m_imagesublinebyteforMT;
		std::vector<std::vector<int> > m_imagemortonforMT;
		std::vector<bool> m_imagehasdataforMT;
		std::vector<std::vector<CGeoPoint<double> > > m_delunarylines; // 三角剖分的边,像素坐标
		std::vector<std::vector<CGeoPoint<double> > > m_queryscanlines; // 查询一个点对应的连通区域

		void* m_gfsclient;
		void* m_jobclient;
		wstring m_indexfileName;

		int m_bandcount;//raster band count of image
		double m_demmin;
		double m_demmax;
		int panBandMap[3];

		std::vector<int> m_channelorder;//换RGB顺序
		std::vector<double> m_demcolorcodevals;//dem数据色标
		std::vector<int> m_demcolorcodecolors;//dem数据色标
		bool m_demisdiscrete;//dem数据连续或离散
		
		bool m_islayerpainted;//shown by scale
	};
}
#endif