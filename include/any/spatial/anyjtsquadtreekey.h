/*!
 * The AnyIndex of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages, especially for those quick
 * spatial algorithms.
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
#ifndef __ANYINDEX_JTS_QUADTREEKEY_H__
#define __ANYINDEX_JTS_QUADTREEKEY_H__

// Refer to spatial extent of this key
// Refer to basic geometry definitions
#include "anygeom\anycoordinate.h"
#include "anygeom\anyenvelope.h"
using namespace AnyGeometry;

// Spatial index package
namespace AnyIndex
{
	/*!
	 * \brief
	 * A Key is a unique identifier for a node in a quadtree.
	 *
	 * It contains a lower-left point and a level number. The level number
	 * is the power of two for the size of the node envelope
	 */
	class CAnyJTSQuadTreeKey 
	{
	public:
		//
		//
		//
		/**
		*
		**/
		CAnyJTSQuadTreeKey(const CAnyEnvelope &quadEnvelope);

		/**
		*
		**/
		virtual ~CAnyJTSQuadTreeKey();

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
		/*!
		*
		**/
		static int ComputeQuadLevel(const CAnyEnvelope &envelope);

	private:
		//
		//
		//
		/*!
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