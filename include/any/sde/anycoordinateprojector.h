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
#ifndef __ANYSDE_SDE_COORD_PROJECTION_H__
#define __ANYSDE_SDE_COORD_PROJECTION_H__

// refer to EXPORT & IMPORT macros
#include "anysde.h"
#include "anysdegeometrylayer.h"
#include "proj4\projects.h"

//forward
struct PJ_DATUMS;
struct PJ_LIST;
struct PJ_ELLPS; 
struct PJ_UNITS;
struct PJ_PRIME_MERIDIANS;

//
namespace AnySDE
{
	

	/*!
	*
	**/
	class ANYSDE_CLASS CAnyCoordinateProjector
	{
	public:
		CAnyCoordinateProjector();
		~CAnyCoordinateProjector();
	
	public:
		/*!
		*
		**/
		bool GaussProjTransform(std::vector<CGeoPoint<double>> &pts,const char * ellpsFrom,const char * lon0From,const char * lat0From,const char * xTranslationFrom,const char * yTranslationFrom,const char * k0From,int zonetypeFrom,const char * ellpsTo,const char * lon0TO,const char * lat0TO,const char * xTranslationTO,const char * yTranslationTO,const char * k0TO,int zonetypeTO);
		bool GaussProjTransformSDE(const char * ellpsFrom,const char * lon0From,const char * lat0From,const char * xTranslationFrom,const char * yTranslationFrom,const char * k0From,int zonetypeFrom,const char * ellpsTo,const char * lon0TO,const char * lat0TO,const char * xTranslationTO,const char * yTranslationTO,const char * k0TO,int zonetypeTO);

		/*!
		*projPJ projFrom including projection type and params
		**/
		bool CoordinateTransform(const char* projFromstr,const char * projFrom, const char * ellpsFrom, const char * towgs84From,const char* projTostr,const char * projTo,const char * ellpsTo, const char * towgs84To,std::vector<CGeoPoint<double>> &pts);
	
		/*!
		*
		**/
		bool Transform(const char* projFromstr,const char * projFrom,const char * ellpsFrom, const char * towgs84From,const char* projTostr,const char * projTo,const char * ellpsTo, const char * towgs84To);

		/*!
		*
		**/
		void GetDatums(std::vector<PJ_DATUMS> &datums);

		/*!
		*
		**/
		void GetProjections(std::vector<PJ_LIST> &projections);

		/*!
		*
		**/
		void GetEllps(std::vector<PJ_ELLPS> &ellpses);
	private:
		
		/*!
		*
		**/
		//void GaussProjInv(projPJ &pj, double x, double y, double &longitude, double &latitude);

		/*!
		*
		**/
		//void GaussProjFwd(projPJ &pj, double longitude, double latitude, double &x, double &y);
	public:
		CAnySdeGeometryLayer *m_from;
		std::vector<std::vector<CGeoPoint<double>>> m_destPts;
	};
}
#endif