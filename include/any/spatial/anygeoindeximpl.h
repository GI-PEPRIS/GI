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
#ifndef __ANYINDEX_GEO_INDEXIMPL_H__
#define __ANYINDEX_GEO_INDEXIMPL_H__

// Refer to EXPORT & IMPORT
#include "anyindex.h"

// Refer to index basic definitions
#include "anyindexbasic.h"

// Refer to portable type definitions like string etc
#include "any/base/anyport.h"

// Refer to geometry basic definitions like point etc
#include "any/base/anygeom.h"

// Refer to own-specified array
#include "any/base/anylightvector.h"
using namespace AnyBase;

// UeIndex namespace
namespace AnyIndex
{
   /*!
	* Road network follows the basic idea about "LAYER-TILE" structure. That is, those different types of network including
	* one real data layer and other index layers are taken as different data layers. Data content in one layer can be 
	* put into different TILEs which may correspond to one special geographical or administrative area for smart data 
	* update. Each tile is accessed by those parcels or meshes indexed by normal, quad-tree and random etc grids etc forms.
	*
	* Note:
	* Currently the maximum number of parcel Idx is 65535, namely two bytes, and tileIdx is also two bytes.
	*
	* TODO:
	* 1) If we take each data file or one table in SQL db corresponding to one tile in a specified layer, here still
	* lacks an efficent mechansim to support once route plan stepping over different tiles. In addition, we need set 
	* direct relationship between one kind of below indexes and network data for smart update data according to 
	* those specified parcels.
	*
	* 2) Of course, we can take TILE definition as an index mechansim for one layer and the whole content of one layer would 
	* correspond to one plain file or a SQL table.
	*/
    class ANYINDEX_CLASS CAnyGeoIndexImpl
    {
		//
		const static int MAXLAYERCOUNT = 128;

	public:
		//
        // Constructors & deconstructor
        //
       /*!
        * 
        */
        CAnyGeoIndexImpl(const string &indexFile, GeoLayer &curLayer, bool isTiled = false);

		/*!
		*
		**/
		CAnyGeoIndexImpl();

	public:
       /*!
        *
        */
        virtual ~CAnyGeoIndexImpl();

    public:
        //
        // Identifers for different data source
        //
       /*!
        * Get indentifer for one data source, namely one plain file or one SQL table, corresponding to 
		* one tile in a specified layer.
		*
		* param layerIdx The identfier of one layer specified by <code> ParcelType </code>
		* param tileIdx The identifer of one tile in a specified layer, it can be numbered by "SCAN LINE" idea
		* return The identifer for one data source corresponding to one tile in a specified layer
        */
        virtual unsigned long GetGateID(unsigned short layerIdx, unsigned short tileIdx) const;

       /*!
        * Using one index implementation mechansim to spatially position which tile id is being used.
		*
		* param layerIdx The identifier of one data layer specified by <code> ParcelType </code>
		* param location The spatial position is used to calculate the identifer of which tile
		* return The identifier of one data source corresponding to one tile in a specified layer
        */
        virtual unsigned long GetGateID(unsigned short layerIdx, const CGeoPoint<double> &location) const;

       /*!
        * Get identifer of above layer according to current layer's identifer.
		*
		* param gateIdx The identifer of current data layer
		* return The identifer of one data source corresponding to one tile in above layer
        */
        virtual unsigned long GetUpGateID(unsigned long gataIdx) const;

       /*!
        * Get identifer of down layer according to current layer's identifer.
		* 
		* param gateIdx The identifer of current data layer.
		* return The identifer of one data source corresponding to one tile in down layer
        */
        virtual unsigned long GetDownGateID(unsigned long gateIdx) const;

		//
		// Methods about LAYER-TILE structure
		//
       /*!
        * Conversion between identifers of one data layer and one data source since gate idx is created by identifers
		* of one data layer and one tile.
		*
		* param gateIdx The identifer of current data source
		* return The identifer for current data layer
        */
        virtual unsigned short GetLayerID(unsigned long gateIdx) const;

       /*!
        * Conversion between identifers of one data layer and one data source since gate idx is created by identifers
		* of one data layer and one tile.
		*
		* param gateIdx The identifer of current data source
		* return The identifer for one tile in current data layer
        */
        virtual unsigned short GetTileID(unsigned long gateIdx) const;

       /*!
        *
        */
        virtual unsigned short GetTileID(unsigned short layerIdx, const CGeoPoint<double> &location) const;


       /*!
        *
        */
        virtual void GetTileID(unsigned short layerIdx, const CGeoRect<double> &mbr, double tolerance, CAnyLightVector &indice) const;

       /*!
        * Directly get identifer for one parcel belonging to one tile in a data layer.
		*
		* param gateIdx The identifer of one data source corresponding to one tile in a data layer.
		* param location The position on which parcel it is standing
		* return The identifer of one parcel belong to one tile
        */
        virtual unsigned long GetParcelID(unsigned long gateIdx, const CGeoPoint<double> &location) = 0;

       /*!
        * Directly get identifers for those parcels interected by a specified rectangle and 
		* they belong to one tile in a data layer.
		*
		* param gateIdx The identifer of one data source corresponding to one tile in a data layer.
		* param mbr The spatial rectangle to overlay current tile.
		* param tolerance The inflated or deflated variable for above specified rectangle.
		* return The set of identifers of those parcels intersected by this specified rectangle
        */
       virtual void GetParcelID(unsigned long gateIdx, const CGeoRect<double> &mbr, double tolerance, CAnyLightVector &indice) = 0;

	  /*!
	   *
	   **/
       virtual void GetParcelID(unsigned long gateIdx, const CGeoRect<int> &directions, CAnyLightVector &indice);

       /*!
        * Get the total number of parcels belonging to one tile in a data layer.
		*
		* param gateIdx The identifer for one tile
		* return the number of all parcels belonging to current tile in a specified data layer
        */
        virtual long GetParcelCount(unsigned long gateIdx) = 0;

		/*!
		*
		**/
		virtual bool GetParcelExtent(unsigned long gateIdx, unsigned long parcelIdx, CGeoRect<double> &extent);

		/*!
		*
		**/
		virtual bool GetLayerExtent(unsigned long gateIdx, CGeoRect<double> &extent);

		/*!
		*
		**/
		virtual void GetParcelDirections(unsigned long gateIdx, unsigned long parcelIdx, CGeoRect<int> &directions);

		/*!
		*
		**/
		virtual void GetTileDirections(unsigned long gateIdx, CGeoRect<int> &directions);

		//
		// Validity check
		//
		/*!
		*
		*/
		bool IsValidLayer(unsigned short layerIdx) const
		{
			return m_layer.m_idx == layerIdx;
		}

		/*!
		*
		*/
		virtual bool IsValidTile(unsigned short tileIdx) const
		{
			return tileIdx >= 0 && tileIdx <= (1 << (32 - m_shift));
		}

		/*!
		*
		*/
		virtual bool IsValidGate(unsigned long gateIdx) const
		{
			unsigned short layerIdx = GetLayerID(gateIdx);
			unsigned short tileIdx = GetTileID(gateIdx);

			return /*IsValidLayer(layerIdx) &&*/ IsValidTile(tileIdx);
		}

	protected:
		// layer name
		string m_name;

		// Indicate TILE play which role
		// One is to use an identifer of one tile and an identifer of one layer to merge an identifer indicating which
		// data source, another is only to take TILEs as index mechansim for a specified layer
		// TRUE means as an identifer for one plain file and FALSE means as an index mechansim, for example, quad-tree
		bool m_isTiled;		
		
		// For which layer
		GeoLayer &m_layer;

		// Bit shift for merging two kinds of identifiers: one data layer and one tile
		// Formula as below:
		// tile Idx << m_shift | layer Idx
		short m_shift;
		unsigned long m_mask;
    };
}

#endif