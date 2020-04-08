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
#ifndef __ANYINDEX_BINARYTREEINDEX_H__
#define __ANYINDEX_BINARYTREEINDEX_H__

// Refer to STL relatives
#include "..\anybase\anystl.h"

// Refer to the definition of geometry item & its boundable
#include "..\anygeom\anygeometry.h"
using namespace AnyGeometry;

// Namespace
namespace AnyIndex
{
	// Forward class
	class CAnyBinaryTreeIndexImpl;
	class CAnyInterval;

	/*!
	*
	**/
	class CAnyBinaryTreeIndex
	{
	public:
        // Container definition for geometry items
        typedef std::vector<CAnyGeometry *> ItemVector;
        typedef ItemVector::iterator item_itr;
        typedef ItemVector::const_iterator item_citr;

	protected:
		//
		//
		//
		/*!
		*
		**/
		CAnyBinaryTreeIndex(CAnyBinaryTreeIndexImpl *impl);

		/*!
		*
		**/
		~CAnyBinaryTreeIndex();

	private:
		/*!
		*
		**/
		CAnyBinaryTreeIndex(const CAnyBinaryTreeIndex &other);

		/*!
		*
		**/
		const CAnyBinaryTreeIndex operator=(const CAnyBinaryTreeIndex &other);

	public:
        //
        // Characteristic methods as a classical tree
        //
        /*!
        *
        **/
        int GetDepth();
        
        /*!
        *
        **/
        int GetItemSize();
        
        /*!
        *
        **/
        int GetNodeSize();

		//
		// Classical spatial functions
		//
        /*!
        *
        **/
        void Insert(CAnyGeometry *item, const CAnyInterval &itemInterval);

        /*!
        *
        **/
        void Query(double x, ItemVector &collect);

        /*!
        *
        **/
        void Query(const CAnyInterval &interval, ItemVector &collect);

    protected:
        //
        // Singleton declaration
        //
        /*!
        *
        **/
        static CAnyBinaryTreeIndex *GetIndex(short type);

        /*!
        *
        **/
        static void DeleteIndex();

	private:
		// Delegated to kinds of implementations
		CAnyBinaryTreeIndexImpl *m_impl;

		// Singleton
		static CAnyBinaryTreeIndex *m_singleton;
	};
}
#endif