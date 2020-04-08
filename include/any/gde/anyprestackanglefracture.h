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
#ifndef __ANYGDE_PRESTACK_ANGLE_FRACTURE_H__
#define __ANYGDE_PRESTACK_ANGLE_FRACTURE_H__

// refer to export/import macro
#include "anygde.h"

// refer to parent
#include "anygdedatahandler.h"
#include "anygdedataset.h"

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CAnyPrestackAngleFracture : public CAnyGdeDataHandler
	{
	public:
		
		struct TraceHeadoffset
		{
			CGeoPoint<double> m_shotpt;
			CGeoPoint<double> m_detectionpt;
			int m_offset;
			/*!
			*
			**/
			TraceHeadoffset() : m_offset(0)
			{
			}

			/*!
			*
			**/
			const TraceHeadoffset &operator=(const TraceHeadoffset &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_shotpt = other.m_shotpt;
				m_detectionpt = other.m_detectionpt;
				m_offset = other.m_offset;
				return *this;
			}
			static bool CompareDistance(const TraceHeadoffset &a, const TraceHeadoffset &b)
			{
				double distancea = sqrt((a.m_shotpt.m_x - a.m_detectionpt.m_x) * (a.m_shotpt.m_x - a.m_detectionpt.m_x) + (a.m_shotpt.m_y - a.m_detectionpt.m_y) * (a.m_shotpt.m_y - a.m_detectionpt.m_y));
				double distanceb = sqrt((b.m_shotpt.m_x - b.m_detectionpt.m_x) * (b.m_shotpt.m_x - b.m_detectionpt.m_x) + (b.m_shotpt.m_y - b.m_detectionpt.m_y) * (b.m_shotpt.m_y - b.m_detectionpt.m_y));
				if(::abs(distancea) < ::abs(distanceb))
					return true;
				return false;
			}
			static bool CompareAngle(const TraceHeadoffset &a, const TraceHeadoffset &b)
			{
				double distancea = sqrt((a.m_shotpt.m_x - a.m_detectionpt.m_x) * (a.m_shotpt.m_x - a.m_detectionpt.m_x) + (a.m_shotpt.m_y - a.m_detectionpt.m_y) * (a.m_shotpt.m_y - a.m_detectionpt.m_y));
				double distanceb = sqrt((b.m_shotpt.m_x - b.m_detectionpt.m_x) * (b.m_shotpt.m_x - b.m_detectionpt.m_x) + (b.m_shotpt.m_y - b.m_detectionpt.m_y) * (b.m_shotpt.m_y - b.m_detectionpt.m_y));
				double anglea = acos((a.m_detectionpt.m_x - a.m_shotpt.m_x) / distancea);
				double angleb = acos((b.m_detectionpt.m_x - b.m_shotpt.m_x) / distanceb);
				if(a.m_detectionpt.m_y < a.m_shotpt.m_y)
					anglea = 2 * PI - anglea;
				anglea = 2.5 * PI - anglea;
				if(anglea >= 2 * PI)
					anglea -= 2 * PI;
				if(b.m_detectionpt.m_y < b.m_shotpt.m_y)
					angleb = 2 * PI - angleb;
				angleb = 2.5 * PI - angleb;
				if(angleb >= 2 * PI)
					angleb -= 2 * PI;
				if(anglea < angleb)
					return true;
				return false;
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyPrestackAngleFracture();

		/*!
		*
		**/
		~CAnyPrestackAngleFracture();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoHandle(CAnyGdeDataHandler::HandlerStruct &handlerstruct);
		void DoHandle360(CAnyGdeDataHandler::HandlerStruct &handlerstruct);

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
		void RayTracing(std::vector<double> &distances, std::vector<double> &times, std::vector<double> &vrms, std::vector<double> &vint, std::vector<std::vector<double> > &seta);
								
		/*!
		*
		**/
		void ConvertCAG_weight(std::vector<std::vector<double> > &cmps, std::vector<double> &distances, std::vector<double> &times, std::vector<double> &vrms, std::vector<double> &vint, \
			std::vector<double> &angles, std::vector<std::vector<double> > &cag);
									
		/*!
		*
		**/
		void ConvertCAG_interpolation(std::vector<std::vector<double> > &cmps, std::vector<double> &distances, std::vector<double> &times, std::vector<double> &vrms, std::vector<double> &vint, \
			std::vector<double> &angles, std::vector<std::vector<double> > &cag);
		
		/*!
		*
		**/
		bool DoEllipse(std::vector<double> &azimuths, std::vector<double> &amps, double &A, double &B, double &C, double &D, double &E, double &F, double &a, double &b, double &seta, double &xc, double &yc, double &e);
		bool DoEllipse_old(std::vector<double> &azimuths, std::vector<double> &amps, double &A, double &B, double &C, double &D, double &E, double &F, double &a, double &b, double &seta, double &xc, double &yc, double &e);
		bool GeneralizedEIG(std::vector<std::vector<double> > A, std::vector<std::vector<double> > B, std::vector<std::vector<double> > &miu, std::vector<std::vector<double> > &lamda);
		bool Cholesky(std::vector<std::vector<double> > &input, int n, std::vector<std::vector<double> > &output);
		bool GaussJordan(std::vector<std::vector<double> > &input, int n, std::vector<std::vector<double> > &output);
		bool Eejcb(std::vector<std::vector<double> > &input, int n, double eps, int jtmin, int jtmax, std::vector<std::vector<double> > &output1, std::vector<std::vector<double> > &output2);
		void InitMatrix(std::vector<std::vector<double> > &matrixtoinit, int m, int n);
		void PolarToOrt(double fai, double offset, double &x, double &y);
		bool StandardToPara(double A, double B, double C, double D, double E, double F, double tmp_k, double &a, double &b, double &seta, double &xc, double &yc, double &e);
		bool StandardToPara_old(double A, double B, double C, double D, double E, double F, double &a, double &b, double &seta, double &xc, double &yc, double &e);
		bool DoEllipse_Xiaoye(std::vector<double> &azimuths, std::vector<double> &amps, double &a, double &b, double &seta, double &xc, double &yc, bool isforcetorigin = false);
		bool DorsEllipseFit(std::vector<double> &azimuths, std::vector<double> &amps, double &a, double &b, double &seta, double &xc, double &yc);
		void RSEig(double *A, double *B, double *V, double *D, int n);
	public:
		std::vector<double> m_angles;//入射角设置
		CAnyGdeDataSet *m_vrmsdataset;
		CAnyGdeDataSet *m_vintdataset;
		bool m_isvrmsgde;
		bool m_isvintgde;
		int m_converttype;
		//方位角分组设置
		double m_azimuthlow;
		double m_azimuthhigh;
		int m_azimuthgroup;
		double m_timeinterval;//计算振幅的时窗
		double m_toptime;
		double m_bottime;
	};
}
#endif