 /* The AnyCGAL of PetroCOVERY solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy management 
 * and rendering of geometries being a leading one.
 *
 * Copyright (C) 2015 Xiujie Sheng
 *
 * This library isn't a free software, so you cann't take the sourcecode without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
 * if you illegally got it. 
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
#ifndef __ANYCGAL_GEOFRACTURE_VECTOR_DO_H__
#define __ANYCGAL_GEOFRACTURE_VECTOR_DO_H__

// macro
#include "anycgal.h"

#include <string>
#include <vector>
#include <algorithm>//sort
using namespace std;

// refer to smart pointer
#include "boost/smart_ptr.hpp"
using namespace boost;

namespace AnyCGAL
{
	/*!
	* Vector.cs
	**/
	class ANYCGAL_CLASS CGeoVectorDo
	{
	friend class CGeoSurfaceFit;

	public:
		//
		typedef std::vector<CGeoVectorDo* > GeoPointVector;
		typedef std::vector<int> GeoIndexVector;

		enum VectorAttributesNames
		{
			//E, // 岩石弹性模量, MPa, 石英砂岩
			//u, // 岩石泊松比,?, 石英砂岩
			MaxCurvature = 0,
			MinCurvature,
			MaxStress,
			MinStress,
			Azimuth,
			FractureDensity,
			FractureDensityX,
			FractureDensityY,
			FractureWidth,
			FractureLength,
			FractureLengthX,
			FractureLengthY,
			FractureHeight
		};

	public:
		CGeoVectorDo(double x, double y, double z);
		CGeoVectorDo(const CGeoVectorDo &other);
		~CGeoVectorDo();
	
	public:
		//
		//common methods
		//
		static double GetMax(double val1, double val2);
		static double GetMin(double val1, double val2);
		
		//
		//attributes
		//
		double GetVectorAttribute(int type);
		
		// 最大主应力方向
		void SetAzimuth(double val);
		double GetAzimuthX();
		double GetAzimuthY();
		
		// 张破裂面方向
		void SetTensileAzimuth(double val);

		// 张破裂率
		void SetTensileI(double val);
		
		// 张裂缝密度
		void SetTensileFractureDensity(double val);
		double GetTensileFractureDensityX();
		double GetTensileFractureDensityY();

		// 张裂缝长度
		void SetTensileFractureLength(double val);
		double GetTensileFractureLengthX();
		double GetTensileFractureLengthY();

		// 张裂缝宽度
		double GetTensileFractureWidth();
		
		// 张裂缝高度
		void SetTensileFractureHeight(double val);
		
		// 剪破裂面方向
		void SetShearingAzimuth(double val);
				
		// 剪破裂率
		void SetShearingI(double val);

		// 剪裂缝密度
		void SetShearingFractureDensity(double val);
		double GetShearingFractureDensityX();
		double GetShearingFractureDensityY();

		// 剪裂缝长度
		void SetShearingFractureLength(double val);
		double GetShearingFractureLengthX();
		double GetShearingFractureLengthY();

		// 剪裂缝宽度
		double GetShearingFractureWidth();
		
		// 剪裂缝高度
		void SetShearingFractureHeight(double val);
		
		//
		//method
		//
		double Distance(CGeoVectorDo &other);
		void Translate(double x, double y, double z);
		void Reset();
		void ResetCurvature();
		void ResetAll();

		//save
		static void Save(const std::string &filename, const std::vector<CGeoVectorDo*> &vectors);
		
		//average
		static CGeoVectorDo *Average(const std::vector<CGeoVectorDo*> &vectors);  
		
		//
		//operators
		//
		CGeoVectorDo* operator+(CGeoVectorDo *other);
		CGeoVectorDo* operator+(double d);

		CGeoVectorDo* operator-(CGeoVectorDo *other);
		CGeoVectorDo* operator-(double d);

		CGeoVectorDo* operator*(double d);
		CGeoVectorDo* operator/(double d);

		//
		//interpolate
		//
		//equal
		bool EqualXY(CGeoVectorDo &other);

		// t有可能是除Z之外的其他值得参数
		// 通过t得到真正的Z，再通过Z得到t，然后再根据Z的t对其他数进行插值
		static CGeoVectorDo *Interpolate(CGeoVectorDo *v1, CGeoVectorDo *v2, double t);
		static CGeoVectorDo *Interpolate(CGeoVectorDo *v1, CGeoVectorDo *v2, CGeoVectorDo *v);

		static CGeoVectorDo *InterpolateByName( CGeoVectorDo * v1,  CGeoVectorDo * v2, int type, double value);
		static CGeoVectorDo *InterpolateByX(CGeoVectorDo * v1,  CGeoVectorDo * v2, double value);
		static CGeoVectorDo *InterpolateByY(CGeoVectorDo * v1,  CGeoVectorDo * v2, double value);
		static CGeoVectorDo *InterpolateByZ(CGeoVectorDo * v1,  CGeoVectorDo * v2, double value);
		static CGeoVectorDo *InterpolateByValue(CGeoVectorDo * v1,  CGeoVectorDo * v2, double value);
		
		//clone
		CGeoVectorDo* Clone();
		
		//dot
		double Dot2(CGeoVectorDo &other);
		double Dot(CGeoVectorDo &other);

		//
		//cross
		//
		double Cross2(CGeoVectorDo &other);
		// 右手法则
		// 向量c=向量a×向量b= 
		// |i  j  k | 
		// |a1 a2 a3| 
		// |b1 b2 b3| 
		// =(a2b3-a3b2,a3b1-a1b3,a1b2-a2b1) ,
		CGeoVectorDo *Cross(CGeoVectorDo &other);

		//length
		double Length();

		//Normalize
		void Normalize();
		
		//check
		static void Validate(const std::vector<CGeoVectorDo*> &vectors);
		
		//IsZero
		bool IsZero();
		
		//sort
		static std::vector<CGeoVectorDo*> Unique(std::vector<CGeoVectorDo*> &vectors);
		static bool CompareCGeoVectorDoX(CGeoVectorDo *v1, CGeoVectorDo *v2);
		static bool CompareCGeoVectorDoY(CGeoVectorDo *v1, CGeoVectorDo *v2);

		//ToRectangle
		static std::vector<CGeoVectorDo*> ToRectangle(const std::vector<CGeoVectorDo*> &vectors);
		static std::vector<CGeoVectorDo*> ToRectangle(CGeoVectorDo *v1, CGeoVectorDo *v2);
	
		//ToString
		std::string ToString();

		//ValueHelper
		static bool EQ(double v1, double v2);
		static bool EQ(CGeoVectorDo *v1, CGeoVectorDo *v2);
		static bool GZ(double v);
	private:

		//check
		static double _Validate(double value);

		//
		//interpolate
		//
		static double _Interpolate(double start, double end, double t);
		static double _Proportion(double start, double end, double value);

	public:
		//
		//properties
		//
		double _X;
		double _Y;
		double _Z;
		bool _IsBoundary;

		// extent of adjacent points
		double m_radius;
		int m_sample_suffix;	// the suffix of current samples

		// For contour computation
		double _Value;
		bool _Flag;

		//
		//attributes
		//
		double _MaxCurvature;
		double _MinCurvature;
		double _MaxStress;
		double _MinStress;

		// 最大主应力方向
		double _Azimuth;
		double _AzimuthSin;
		double _AzimuthCos;

		// 张应力
		double _TensileStress;

		// 张破裂面方向
		double _TensileAzimuth;
		double _TensileAzimuthSin;
		double _TensileAzimuthCos;

		// 张破裂率
		double _TensileI;

		 // 张裂缝密度
		double _TensileFractureDensity;

		// 张裂缝长度
		double _TensileFractureLength;
		double _TensileFractureWidth;

		// 张裂缝高度
		double _TensileFractureHeight;

		// 剪应力
		double _ShearingStress;

		// 剪破裂面方向
		double _ShearingAzimuth;
		double _ShearingAzimuthSin;
		double _ShearingAzimuthCos;

		// 剪破裂率
		double _ShearingI;

		// 剪裂缝密度
		double _ShearingFractureDensity;

		// 剪裂缝长度
		double _ShearingFractureLength;

		// 剪裂缝高度
		double _ShearingFractureHeight;
		double _ShearingFractureWidth;

		//
		static double _MaxDifference;
	};
}
#endif