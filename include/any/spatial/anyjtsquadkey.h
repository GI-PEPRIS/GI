/**
 * The AnySDB of PetroCOVERY solution is a collection of packages based on native C++ classes
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
 * smartpoint@sohu.com
 */
 #ifndef __ANYSPATIALINDEX_JTSQUADKEY_H__
#define __ANYSPATIALINDEX_JTSQUADKEY_H__

// Refer to basic geometry definitions
#include "any/geom/anycoordinate.h"
#include "any/geom/anyenvelope.h"
using namespace AnyGeometry;

// Spatial index package
namespace AnySpatialIndex
{
	/*!
	 * \brief
	 * A Key is a unique identifier for a node in a quadtree.
	 *
	 * It contains a lower-left point and a level number. The level number
	 * is the power of two for the size of the node envelope
	 */
	class CAnyJtsQuadKey 
	{
	public:
		//
		//
		//
		/**
		*
		**/
		CAnyJtsQuadKey(const CAnyEnvelope &quadEnvelope);

		/**
		*
		**/
		virtual ~CAnyJtsQuadKey();

	public:
		//
		// Access functions
		//
		/*!
		*
		**/
		const CAnyCoordinate &GetPoint() const;

		/*!
		*
		**/
		int GetLevel() const;

		/*!
		*
		**/
		const CAnyEnvelope &GetEnvelope() const;

		/*!
		*
		**/
		CAnyCoordinate GetCenter() const;

        //
        //
        //
		/*!
		*
		**/
		void ComputeKey(const CAnyEnvelope &itemEnv);

		//
		// Utility functions
		//
		/**
		*
		**/
		static int ComputeQuadLevel(const CAnyEnvelope &envelope);

	private:
		//
		//
		//
		/**
		*
		**/
		void ComputeKey(int level, const CAnyEnvelope &itemEnv);

	private:	
		// The fields which make up the key
		CAnyCoordinate m_pt;
		int m_level;
		// Auxiliary data which is derived from the key for use in computation
		CAnyEnvelope m_envelope;
	};
}
#endif