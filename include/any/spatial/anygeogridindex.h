/*!
 * The AnyNet of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON NETWORK PROGRAMMING DEMANDS of other packages.
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
#ifndef __ANYINDEX_GEO_GRIDINDEX_H__
#define __ANYINDEX_GEO_GRIDINDEX_H__

// Refer to EXPORT & IMPORT macroes
#include "anyindex.h"

// Refer to index basic definitions
#include "anyindexbasic.h"

// Refer to its parent
#include "anygeoindeximpl.h"

// refer to light vector
#include "any/base/anylightvector.h"

//
namespace AnyIndex
{
    /*!
	* Define index mechansim for "layer-tiler" structure using grids in different sizes. Namely, those grids can be
	* organized by different rows & cols. For each row those grids have the same height but can have different widths. For
	* each coloumn, those grids have the same width but they may have different heights. The general defintion for this
	* index is those grids have the same width and height and they can be ordered or identified by basic "SCAN LINE" ideas,
	* namely, gridIdx = the ?th column * rows number + current row number.
	*/
	class ANYINDEX_CLASS CAnyGeoGridIndex : public CAnyGeoIndexImpl
    {
		// Disallow implicitly creation etc
		CAnyGeoGridIndex(const CAnyGeoGridIndex &other);
		const CAnyGeoGridIndex &operator=(const CAnyGeoGridIndex &other);

    public:
        //
        //
        //
		/*!
		* Both tiles & parcels in regular way, namely, they have the same width & height
		**/
		CAnyGeoGridIndex(const CGeoRect<double> &extent, unsigned long xCount, unsigned long yCount, GeoLayer &curLayer, bool isTiled = false);

        /*!
        *
        */
        virtual ~CAnyGeoGridIndex();

    public:
		///
		/// Special parcel index mechansim
		///
        /*!
        *
        */
        virtual unsigned long GetParcelID(unsigned long gateIdx, const CGeoPoint<double> &location);

        /*
        *
        */
        virtual void GetParcelID(unsigned long gateIdx, const CGeoRect<double> &mbr, double tolerance, CAnyLightVector &indice);

        /*!
        *
        */
        virtual long GetParcelCount(unsigned long gateIdx);

		/*!
		*
		**/
		virtual bool GetParcelExtent(unsigned long gateIdx, unsigned long parcelIdx, CGeoRect<double> &extent);

		/*!
		*
		**/
		virtual void GetParcelID(unsigned long gateIdx, const CGeoRect<int> &directions, CAnyLightVector &indice);

		/*!
		*
		**/
		virtual  void GetParcelDirections(unsigned long gateIdx, unsigned long parcelIdx, CGeoRect<int> &directions);

		/*!
		*
		**/
		virtual  void GetTileDirections(unsigned long gateIdx, CGeoRect<int> &directions);

	private:
		//
		// Tiles & Parcels are laid from left to right and from bottom to up
		//
		/*!
		*
		**/
		void CreateIndex(const CGeoRect<double> &extent, unsigned long xCount, unsigned long yCount);

        /*!
        *
        */
        unsigned long GetParcelID(const GeoTile &oneTile, const CGeoPoint<double> &location) const;

        /*!
        *
        */
        void GetParcelID(const GeoTile &oneTile, const CGeoRect<double> &mbr, double tolerance, CAnyLightVector &indice) const;
    };
}

#endif