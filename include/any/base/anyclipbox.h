/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYBASE_CLIPBOX_H__
#define __ANYBASE_CLIPBOX_H__

// Refer to EXPORT & IMPORT macroes
#include "anybase.h"

// Refer to basic geometries
#include "anygeom.h"

// UeBase namespace
namespace AnyBase
{
	// Forward class
	class CAnyLightVector;

	/*!
	* To clip one polyline or polygon into given rectangle.
	*
	* To loop all vertices then decide which is out of border line, if does, calculate new coord. Here allocates one memory
	* block whose size is two times of given coords is divided into two parts, then one of two pointers temporarily points to
	* the first part while initially set by given coords' value, another of two pointers points to the second part while
	* reciving the clipped results when firstly cliping. Recusively, switch two pointers, namely, one is last clipped reults
	* another is prepared for reciving the following clipped results until finishing clip action.
	*
	* Note/TODO:
	* This class had better be taken as template class since we adopt CGeoPoin<> as its coords and to support
	* different data types' calculation. As far, this class mainly be used when getting screen coords, so it use
	* INT type.
	*/
	class ANYBASE_CLASS CAnyClipBox
	{
		// Disallow automatically or implicitly creation ...
		CAnyClipBox(const CAnyClipBox &other);
		void operator=(const CAnyClipBox &other);

	public:
		//
		// Constructors & deconstructor
		//
		/*!
		*
		**/
		CAnyClipBox();

		/*!
		*
		**/
		CAnyClipBox(const CAnyLightVector &pts);

		/*!
		*
		**/
		~CAnyClipBox();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool ClipPolyline(CAnyLightVector &pts, const CGeoRect<double> &scrExtent);

		/*!
		*
		**/
		bool ClipPolygon(CAnyLightVector &pts, const CGeoRect<double> &scrExtent);

		/*!
		*
		**/
		bool Prepare(const CAnyLightVector &pts);

	protected:
		//
		// Extra memory for running this plain and simple algorithm
		//
		/*!
		*
		**/
		void Release();

	private:
		//
		//
		//
		/*!
		* If (mbr.maxY > clip.maxY)
		**/
		bool PolygonClipTop(int clipY, CGeoPoint<double> *inVtxs, int inNum, CGeoPoint<double> *outVtxs, int &outNum);


		/*!
		* If (mbr.minY < clip.minY)
		**/
		bool PolygonClipBottom(int clipY, CGeoPoint<double> *inVtxs, int inNum, CGeoPoint<double> *outVtxs, int &outNum);

		/*!
		* If (mbr.maxX > clip.maxX)
		**/
		bool PolygonClipRight(int clipX, CGeoPoint<double> *inVtxs, int inNum, CGeoPoint<double> *outVtxs, int &outNum);


		/*!
		* If (mbr.minX < clip.minX)
		**/
		bool PolygonClipLeft(long clipX, CGeoPoint<double> *inVtxs, int inNum, CGeoPoint<double> *outVtxs, int &outNum);


		//
		//
		//
		/*!
		* if (mbr.maxY > clip.maxY)
		**/
		bool PolylineClipTop(int clipY, CGeoPoint<double> *inVtxs, int inNum, CGeoPoint<double> *outVtxs, int &outNum);

		/*!
		* if (mbr.minY < clip.minY)
		**/
		bool PolylineClipBottom(int clipY, CGeoPoint<double> *inVtxs, int inNum, CGeoPoint<double> *outVtxs, int &outNum);

		/*!
		* if (mbr.maxX > clip.maxX)
		**/
		bool PolylineClipRight(int clipX, CGeoPoint<double> *inVtxs, int inNum, CGeoPoint<double> *outVtxs, int &outNum);

		/*!
		* if (mbr.minX < clip.minX)
		**/
		bool PolylineClipLeft(int clipX, CGeoPoint<double> *inVtxs, int inNum, CGeoPoint<double> *outVtxs, int &outNum);

		//
		//
		//
		/*!
		*
		**/
		int XClipY(long clipY, const CGeoPoint<double> &firstPt, const CGeoPoint<double> &secondPt)
		{
			return (secondPt.m_x - firstPt.m_x) * (firstPt.m_y - clipY) / (firstPt.m_y - secondPt.m_y) + firstPt.m_x;
		}

		/*!
		*
		**/
		int XClipX(long clipX, const CGeoPoint<double> &firstPt, const CGeoPoint<double> &secondPt)
		{
			return (secondPt.m_y - firstPt.m_y) * (firstPt.m_x - clipX) / (firstPt.m_x - secondPt.m_x) + firstPt.m_y;
		}

	private:
		// Memory storing coords whose size is two times of given coords input
		CGeoPoint<double> *m_pts; 
		int m_ptsNum;

		// Recursivly take one of below points as input given coords, another to receive results
		//
		// First pointer or cursor pointing to the first part of above memory
		int m_firstNum;
		CGeoPoint<double> *m_firstPts;

		// Second pointer or cursor pointing to the second part of above memory
		int m_secondNum;
		CGeoPoint<double> *m_secondPts;
	};
}

#endif