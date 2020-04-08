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
#ifndef __ANYINDEX_GEO_INDEX_H__
#define __ANYINDEX_GEO_INDEX_H__

// Refer to EXPORT & IMPORT
#include "anyindex.h"

// Refer to index basic definitions
#include "anyindexbasic.h"

// Refer to own-vector definition
#include "any/base/anylightvector.h"

// Refer to its parent CObserver
#include "any/base/anystl.h"
#include "any/base/anymediator.h"
using namespace AnyBase;

// Refer to singleton object
#include "any/base/loki/singleton.h"
using namespace AnyBase::Loki;

//
#pragma warning( push )
#pragma warning( disable: 4251 )  // needs to have dll-interface to be used

//
namespace AnyIndex
{
	// Forward classes
	class CAnyGeoIndexImpl;

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
    class ANYINDEX_CLASS CAnyGeoIndex
    {
		// sinleton
		typedef SingletonHolder<CAnyGeoIndex, CreateUsingNew> Singleton;

	public:
		// Index mechanism set
		typedef std::map<string, CAnyGeoIndexImpl *> IndexMap;
		typedef IndexMap::iterator idx_itr;
		typedef IndexMap::const_iterator idx_citr;

	public:
		//
        // Constructors & deconstructor
        //
		/*!
		*
		**/
		CAnyGeoIndex();

	public:
        /*!
        *
        */
        virtual ~CAnyGeoIndex();

    public:
		//
		// Singleton functions
		//
		/*!
		*
		**/
		static CAnyGeoIndex &GetSingleton();

		//
		// Construct index layer which maybe correspond to which scale level
		//
		/*!
		*
		**/
		CAnyGeoIndexImpl *SetLayerIndex(short indexType, const string &name, const GeoLayer &layer);

		/*!
		*
		**/
		CAnyGeoIndexImpl *GetLayerIndex(const string &name);

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
        unsigned long GetGateID(unsigned short layerIdx, unsigned short tileIdx) const;

        /*!
        * Using one index implementation mechansim to spatially position which tile id is being used.
		*
		* param layerIdx The identifier of one data layer specified by <code> ParcelType </code>
		* param location The spatial position is used to calculate the identifer of which tile
		* return The identifier of one data source corresponding to one tile in a specified layer
        */
        unsigned long GetGateID(unsigned short layerIdx, const CGeoPoint<double> &location) const;

        /*!
        * Get identifer of above layer according to current layer's identifer.
		*
		* param gateIdx The identifer of current data layer
		* return The identifer of one data source corresponding to one tile in above layer
        */
        unsigned long GetUpGateID(unsigned long gataIdx) const;

        /*!
        * Get identifer of down layer according to current layer's identifer.
		* 
		* param gateIdx The identifer of current data layer.
		* return The identifer of one data source corresponding to one tile in down layer
        */
        unsigned long GetDownGateID(unsigned long gateIdx) const;

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
        unsigned short GetLayerID(unsigned long gateIdx) const;

        /*!
        * Conversion between identifers of one data layer and one data source since gate idx is created by identifers
		* of one data layer and one tile.
		*
		* param gateIdx The identifer of current data source
		* return The identifer for one tile in current data layer
        */
        unsigned short GetTileID(unsigned long gateIdx) const;

        /*!
        *
        */
        unsigned short GetTileID(unsigned short layerIdx, const CGeoPoint<double> &location) const;


        /*!
        *
        */
        void GetTileID(unsigned short layerIdx, const CGeoRect<double> &mbr, double tolerance, CAnyLightVector &indice) const;

        /*!
        * Directly get identifer for one parcel belonging to one tile in a data layer.
		*
		* param gateIdx The identifer of one data source corresponding to one tile in a data layer.
		* param location The position on which parcel it is standing
		* return The identifer of one parcel belong to one tile
        */
        unsigned long GetParcelID(unsigned long gateIdx, const CGeoPoint<double> &location);

        /*!
        * Directly get identifers for those parcels interected by a specified rectangle and 
		* they belong to one tile in a data layer.
		*
		* param gateIdx The identifer of one data source corresponding to one tile in a data layer.
		* param mbr The spatial rectangle to overlay current tile.
		* param tolerance The inflated or deflated variable for above specified rectangle.
		* return The set of identifers of those parcels intersected by this specified rectangle
        */
       void GetParcelID(unsigned long gateIdx, const CGeoRect<double> &mbr, double tolerance, CAnyLightVector &indice);

        /*!
        * Get the total number of parcels belonging to one tile in a data layer.
		*
		* param gateIdx The identifer for one tile
		* return the number of all parcels belonging to current tile in a specified data layer
        */
        long GetParcelCount(unsigned long gateIdx);

		//
		//
		//
		/*!
		*
		**/
		bool GetParcelExtent(unsigned long gateIdx, unsigned long parcelIdx, CGeoRect<double> &extent);

		/*!
		*
		**/
		bool GetLayerExtent(unsigned long gateIdx, CGeoRect<double> &extent);

		//
		// Validity check
		//
		/*!
		*
		*/
		bool IsValidLayer(unsigned short layerIdx) const;

		/*!
		*
		*/
		bool IsValidTile(unsigned short tileIdx) const;

		/*!
		*
		*/
		bool IsValidGate(unsigned long gateIdx) const;

	protected:
        // "Layer-Tile" structure
		// Note:
		// Here subscript of this vector MUST follow the definition of <code> ParcelType </code>
		// So, it had better use map container for flexible definition of <code> ParcelType </code>
        LayerMap m_layers;

		// Briged implementation
		IndexMap m_indexes;

		// Current index mechansim
		CAnyGeoIndexImpl *m_curIndex;

        // Index as singletion
        static CAnyGeoIndex *m_geoIndex;
	};
}
#endif