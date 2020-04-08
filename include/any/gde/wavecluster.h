/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYGDE_WAVECLUSTER_H__
#define __ANYGDE_WAVECLUSTER_H__

// refer to export/import macro
#include <stdlib.h>
#include <time.h>
#include "any/base/anygeom.h"
#include "anygde.h"
#include "anygdedatahandler.h"
#include "anygdedataset.h"

#define   EPSILON_CLUSTER             1.0E-6

#define RandCoef2053 2053	
#define RandCoef13849 13849
#define MODUL65536 65536

#define RS_CLUSTER_INFO_FLAG		"ClusterInfo"
#define RS_CLUSTER_FILE_VER_200		200

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CWaveCluster : public CAnyGdeDataHandler
	{
	public:
		enum clustermode
		{
			COMPARE_MODE_UP = 1,
			COMPARE_MODE_DOWN = 2,
			COMPARE_MODE_MIDDLE = 3,
		};
		enum icomparemode
		{
			CLUSTERMETHORD_FUZZY = 1,
			CLUSTERMETHORD_NETWORK = 2,
			CLUSTERMETHORD_FUZZY_STEP = 500,
			CLUSTERMETHORD_NETWORK_STEP = 30,
		};
	public:
		typedef struct struct_RealSlice_Point
		{
			float	fTime;	//us
			float	fValue;
			int		uReserved;
		} REALSLICE_POINT;

		struct CLUSTER_INFO
		{
			int		nValue;				//聚类值
			int		nSequence;			//在对话框中的序号
			int		r,g,b;
			float	fRatio;				//所占比例
			int		nInterval,nPoint;	//Sample interval:us		 
			int		uLine,uCDP;
			int		uWellID;
			int		uCurveID[2];
			bool	bShowTops;
			int		Reserved[4];

		public:
			CLUSTER_INFO()
			{
				fRatio = 0.f;
				nPoint = 0;
				uLine = uCDP = -1;
				uWellID = -1;
				uCurveID[0] = uCurveID[1] = -1;
				bShowTops = true;
			};

			void operator = (CLUSTER_INFO &info)
			{
				this->nValue		= info.nValue;
				this->nSequence		= info.nSequence;
				this->r				= info.r;
				this->g				= info.g;
				this->b				= info.b;
				this->fRatio		= info.fRatio;
				this->nInterval		= info.nInterval;
				this->nPoint		= info.nPoint;
				this->uLine			= info.uLine;
				this->uCDP			= info.uCDP;
				this->uWellID		= info.uWellID;
				this->uCurveID[0]	= info.uCurveID[0];
				this->uCurveID[1]	= info.uCurveID[1];
				this->bShowTops		= info.bShowTops;
			};
		}; 

		struct CLUSTER_HEAD
		{
			char	cFlag[12];			//聚类标志："ClusterInfo"
			int		nVersion;			//版本号*100，如2.1版表示为210
			int		nCubeID,nWell;
			int		nCluster,nMaxPoint;
			float	fSeisMinWin,fSeisMaxWin;
			float	fWellMaxWin;
			int		nCompare;			//要比较的聚类中心的序号
			int		Reserved[4];		//保留
		}; 

		struct WELL_INFO
		{
			int		uWellID;
			int		uLine,uCDP;
			float	fTimeFrom,fTimeTo;	//ms
			float	fDeptFrom,fDeptTo;

			WELL_INFO()
			{
				uWellID = -1;
				uLine = uCDP = -1;
				fTimeFrom = fTimeTo = -1.f;
				fDeptFrom = fDeptTo = -1.f;
			}
		}; 

	public:
		//
		//
		//
		/*!
		*
		**/
		CWaveCluster();
		~CWaveCluster();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoHandle(HandlerStruct &handlerstruct);

		/*!
		*
		**/
		void DoGetTraceSample(std::vector<double> &results, int &cmpcount);

		/*!
		*
		**/
		void DoGetTraceHead(std::vector<double> &results);
		
		/*!
		*
		**/
		void freeAllBuffer();
		bool getSliceTime();
		bool loadData();
		bool compute();
		bool fillSlice();
		bool getValidDataRange();
		void createSlice();
		void smooth();
		
		/*!
		*
		**/
		bool kmeans(int* iIndexCluster, float** x, int numData,int maxAttribNum, int *colNum, int numCenters, int niter,
			int *centerPos,int *centersAttribNum, double **centers, double &deviation, double &error);
		bool SOMNetWork(int* iIndexCluster, float** x, int numData,int maxAttribNum, int *colNum, int numCenters, int niter,
			int *centerPos,int *centersAttribNum, double **centers, double &deviation, double &error);
				
		/*!
		*
		**/
		double *alloc1d(int);	
		double **alloc2d(int, int); 
		float **alloc2df(int,int);
		double **alloc2d(int, int*); 
		int **alloc2d_int(int, int);

		double ***alloc3d(int, int *); 
		double ***alloc3d(int l , int m , int n);
		float ***alloc3d_float(int l, int m, int n);
		void free1d(double *);
		void free2d(double **, int); 
		void free2d(int **, int); 
		void free2d(float **, int); 

		void free3d(double ***, int, int*); 
		void free3d(double ***, int, int);	
		void free3d_float(float ***, int, int);	
		void randperm(int*, int, unsigned int seed);  
		void convert(double**, double*, int, int);
		double** convert(double*, int, int);
		double** convertAll(double**, int, int, int);
		int rand2(int n);
		double randn(double mu, double ro, double& seed);
		void normalizeData(double* x, int num, double& p1,double& p2, int method = 1, bool change=false) ;

		void randWeights(double **w, int m, int n, double& seed, bool etaflag = false);
		void randWeights3d(double ***w, int l, int* m, double &seed, bool etaflag = false);
	public:
		CAnyGdeDataSet *m_dataset;
		bool m_isgde;
		REALSLICE_POINT *m_outputs;

		int m_iVariableLength;
		int m_nMaxLength;
		int m_iCompareMode;
		int m_nPoints;
		float m_lTimeWindow;
		int m_nCluster;
		int m_nClusterMode;
		bool m_issmooth;
		int m_smoothradius;

		float **m_ppSeisData;
		double **m_ppCenter; 
		int *m_pLength;
		int *m_pBegin;
		int *m_pEnd;
		int *m_pCenterPos;
		int *m_pCenterNum;
		int *m_pFaceData;
		CGeoPoint<double> *m_pPointData;
		int m_nDataNumber;
		int m_nCubeStartTime;
		bool m_bUseGradient, m_bNormalize;
		int m_nInlineFrom, m_nInlineTo, m_nXlineFrom, m_nXlineTo;

		int m_pCluster_nCubeID, m_pCluster_nWell;
		int m_pCluster_nCluster,m_pCluster_nMaxPoint;
		float m_pCluster_fSeisMinWin, m_pCluster_fSeisMaxWin;
		float m_pCluster_fWellMaxWin;
		int m_pCluster_nCompare;
		float *m_pCluster_pCenter;
		CLUSTER_INFO *m_pCluster_pInfo;
		WELL_INFO *m_pCluster_pWells;

		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;
	};
}
#endif
