#ifndef __ANYMATH_KRIGING_H__
#define __ANYMATH_KRIGING_H__

// refer to EXPORT & IMPORT macroes
#include "anymath.h"

// refer to STL
#include "any/base/anystl.h"

// refer to CGeoPoint
#include "any/base/anygeom.h"
using namespace AnyBase;

// namespace
namespace AnyMath
{
	#define MATHPI 3.14159265358979323846
	
	template<class T>
	struct DataWithIndex
	{
		DataWithIndex()
		{
		}

		~DataWithIndex()
		{
		}

		DataWithIndex(const DataWithIndex& other)
		{
			*this = other;
		}

		const DataWithIndex& operator=(const DataWithIndex& other)
		{
			if(this == &other)
			{
				return *this;
			}
			data=other.data;
			index=other.index;
			return *this;
		}

		//
		T data;
		int index;
	};

	class ANYMATH_CLASS CAnyKriging
	{
	private:
		//
		int m_taskcount;
		void *m_scheduler;

		// thread parameter
		struct CalculateVarianceThreadParameter
		{
			int m_from;
			int m_to;
			int m_sampleNumber;

			double **m_distance;
			double **m_variance;
			CalculateVarianceThreadParameter() : m_from(0), m_to(0), m_sampleNumber(0), m_distance(0), m_variance(0)
			{
			}
		};
		void CalculateDistanceThreadFunc(const CalculateVarianceThreadParameter &parameter);
		void CalculateVarianceThreadFunc(const CalculateVarianceThreadParameter &parameter);

		struct CalculateTargetThreadParameter
		{
			int m_from;
			int m_to;
			int m_sampleNumber;
			int m_targetNumber;

			double **m_invvariogram;
			CGeoPoint<double> *m_targets;
			CGeoPoint<double> *m_samples;
			double *m_r;
			double *m_weight;
			CalculateTargetThreadParameter() : m_from(0), m_to(0), m_sampleNumber(0), m_targetNumber(0), m_invvariogram(0), \
				m_samples(0), m_targets(0), m_r(0),m_weight(0)
			{
			}
		};
		void CalculateTargetThreadFunc(const CalculateTargetThreadParameter &parameter);

	public:
		// a 2-D point;
		struct KrigingPoint
		{
			KrigingPoint():m_x(0.),m_y(0.)
			{

			}
			KrigingPoint(const KrigingPoint &other)
			{

				m_x = other.m_x;
				m_y = other.m_y;
			}
			const KrigingPoint &operator=(const KrigingPoint &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_x = other.m_x;
				m_y = other.m_y;

				return *this;
			}

			/*!
			*
			**/
			bool operator<(const KrigingPoint &right) const
			{
				if(m_x<right.m_x)
				{
					return true;
				}
				else if(m_x==right.m_x)
				{
					if(m_y<right.m_y)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
					{
						return false;
					}
			}

			double m_x;
			double m_y;
		};
		// variogram fitting
		enum KernelType
		{
			SPHERICAL=0,
			EXPONETIAL,
			GUASSIAN,
			LINEAR,
		};

		//
		enum KrigingType
		{
			KOrdinaryKriging=0,
			KUniversalKriging,
			KCoKriging,
		};
		
		//
		enum UniversalType
		{
			ULINEAR=0,
			UQUADRATIC,
		};

		//
		enum CoKrigingType
		{
			TYPEA=0,
			TYPEB,
			TYPEAB,
		};

		CAnyKriging();
		CAnyKriging(int m_neighborNum,bool m_isNeighborMode=false,double m_nugget=0,double m_range=0,double m_sill=0,int m_kernelType=SPHERICAL,int m_krigingType=KOrdinaryKriging,int m_universalType=ULINEAR,bool m_isAnisotropyMode=false);
		~CAnyKriging();

		CAnyKriging(const CAnyKriging& other){
			m_samples=other.m_samples;
			m_sampleNumber=other.m_sampleNumber;

			m_targets=other.m_targets;
			m_targetNumber=other.m_targetNumber;

			m_isAutoEstiamteParameter=other.m_isAutoEstiamteParameter;
			m_nugget=other.m_nugget;
			m_range=other.m_range;
			m_sill=other.m_sill;

			m_anisotropyR=other.m_anisotropyR;
			m_anisotropyTheta=other.m_anisotropyTheta;

			m_neighborNum=other.m_neighborNum;
			m_isNeighborMode=other.m_isNeighborMode;
			m_isAnisotropyMode=other.m_isAnisotropyMode;
			m_kernelType=other.m_kernelType;
			m_krigingType=other.m_krigingType;
			m_universalType=other.m_universalType;

			m_maxdist=other.m_maxdist;
			m_mindist=other.m_mindist;

			/*m_lags=other.m_lags;
			if(other.m_gammar)
			{
				m_gammar=(double* )malloc(m_lags);
				for(int i=0;i<m_lags;i++){
					m_gammar[i]=other.m_gammar[i];
				}
			}
			else
			{
				m_gammar=NULL;
			}
			if(other.m_h)
			{
				m_h=(double* )malloc(m_lags);
				for(int i=0;i<m_lags;i++){
					m_h[i]=other.m_h[i];
				}
			}
			else
			{
				m_h=NULL;
			}*/
		}

		/*const CAnyKriging &operator=(const CAnyKriging &other)
		{
		if(this == &other)
		{
		return *this;
		}
		m_samples=other.m_samples;
		m_sampleNumber=other.m_sampleNumber;

		m_targets=other.m_targets;
		m_targetNumber=other.m_targetNumber;

		m_isAutoEstiamteParameter=other.m_isAutoEstiamteParameter;
		m_nugget=other.m_nugget;
		m_range=other.m_range;
		m_sill=other.m_sill;

		m_anisotropyR=other.m_anisotropyR;
		m_anisotropyTheta=other.m_anisotropyTheta;

		m_neighborNum=other.m_neighborNum;
		m_isNeighborMode=other.m_isNeighborMode;
		m_isAnisotropyMode=other.m_isAnisotropyMode;
		m_kernelType=other.m_kernelType;
		m_krigingType=other.m_krigingType;
		m_universalType=other.m_universalType;

		m_maxdist=other.m_maxdist;
		m_mindist=other.m_mindist;

		m_lags=other.m_lags;
		if(other.m_gammar)
		{
		m_gammar=(double* )malloc(m_lags);
		for(int i=0;i<m_lags;i++){
		m_gammar[i]=other.m_gammar[i];
		}
		}
		else
		{
		m_gammar=NULL;
		}
		if(other.m_h)
		{
		m_h=(double* )malloc(m_lags);
		for(int i=0;i<m_lags;i++){
		m_h[i]=other.m_h[i];
		}
		}
		else
		{
		m_h=NULL;
		}
		return *this;
		}*/

	public:
		
		void SetSampleData(double* x,double* y,double* z,int num );
		void SetSampleDataB(double* x,double* y,double* z,int num );
		void SetTargetData(double* x,double* y,int num );

		void SetSampleData(const std::vector<CGeoPoint<double> > &samples);
		void SetSampleDataB(const std::vector<CGeoPoint<double> > &samples);
		void SetTargetData(const std::vector<CGeoPoint<double> > &targets);
		void GetTargetData(std::vector<CGeoPoint<double> > &targets)
		{
			targets.clear();
			targets.assign(m_targets.begin(), m_targets.end());
		}

		void SetNugget(double nugget);
		void SetRange(double range);
		void SetSill(double sill);
		void SetIsAutoEstimatePara(bool isAutoEstimatePara);

		void SetNeighborNum(double neighborNum);
		void SetIsNeighborMode(bool isNeighborMode);
		
		void SetKernelType(int kernelType);
		void SetKrigingType(int krigingType);
		void SetUniversalType(int universalType);
		
		void SetIsAnisotropyMode(bool isAnisotropyMode);
		bool SetAnisotropyRTheta(double R,double theta);

		void SetLagNum(int lagnum);
	
		//主函数
		bool KrigingPred();

		//
		//
		//
		//int MatrixInversionGS(double **rhs, double **m, int stRank);
		//void MatrixProduct(double **rhs, double **m, int nRow, int nR, int nCol, double **R);
		//void MatrixProductVector(double **rhs, double *m, int nRow, int nCol, double *R);

		double KernelModel(double h,double nugget,double range,double sill);
		double KernelFi(double h,double range);

		double getDist(double x1,double y1,double x2,double y2);
		void FindNeighbor(double targetx,double targety,std::vector<int>& neighborIndexVec);
		int GetLagsNum();
		double CalculateMSE(double* gamma,int lags,double *h,double nugget,double range,double sill);
		bool CalculateGamma(double* gamma,int *neiborNum,double* lagh,int lags,int type=0);
		bool GetEstimateSillNugget(double* gamma,int lags,double *h,double range,double& nugget,double& sill,double maxresponce);
	
		void EstimateParameter();

		//具体kriging
		bool OrdinaryKriging();
		bool OrdinaryKrigingNeighbor();
		bool UniversalKriging();
		bool UniversalKrigingNeighbor();

		/*!
		*	CoKriging
		**/
		void EstimateParameterCoKriging(int type);
		bool CoKriging();


		bool CalculateGammaWithAngle(double* gamma,int *neiborNum,double *h,int lags,double angle,double angleTolerance);
		double getAngle(double x1,double y1,double x2,double y2);
		//
		//
		//
		template<class T>
		int Partition(DataWithIndex<T>*vec,int left,int right )
		{
			DataWithIndex<T> prior=vec[left];
			int i=left;
			int j;
			for(j=left+1;j<=right;j++)
			{
				if(vec[j].data<prior.data)
				{
					i++;
					if(i!=j)
					{
						DataWithIndex<T> tmp=vec[i];
						vec[i]=vec[j];
						vec[j]=tmp;
					}
				}

			}
			DataWithIndex<T> tmp=vec[i];
			vec[i]=vec[left];
			vec[left]=tmp;
			return i;
		}

		template<class T>
		void QuickSortWithIndex( DataWithIndex<T>* vec,int left,int right )
		{
			if(left<right)
			{
				int pivot=Partition(vec,left,right);
				QuickSortWithIndex(vec,left,pivot-1);
				QuickSortWithIndex(vec,pivot+1,right);
			}
		}

		//
		//
		//
		/*!
		*
		**/
		static void DoInverseDistanceWeighting(CGeoPoint<double> *cells, int rows, int cols, const CGeoPoint<double> *samples, int number, const CGeoRect<double> &extent);

	public:
		std::vector<CGeoPoint<double> > m_samples;
		int m_sampleNumber;

		std::vector<CGeoPoint<double> > m_targets;
		int m_targetNumber;

		bool m_isAutoEstiamteParameter;
		double m_nugget;
		double m_range;
		double m_sill;

		double m_anisotropyR;
		double m_anisotropyTheta;

		int m_neighborNum;
		bool m_isNeighborMode;
		bool m_isAnisotropyMode;
		int m_kernelType;
		int m_krigingType;
		int m_universalType;

		double m_maxdist;
		double m_mindist;
		int m_lagnum;
		// for cokriging
	public:
		double m_nuggetA;
		double m_rangeA;
		double m_sillA;
		double m_nuggetB;
		double m_rangeB;
		double m_sillB;
		double m_nuggetAB;
		double m_rangeAB;
		double m_sillAB;

		std::vector<CGeoPoint<double> > m_samplesB;
		int m_sampleNumberB;

		//
		bool m_isthreaded;
	};
}
#endif