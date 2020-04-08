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
#ifndef __ANYINDEX_BINARYTREEBASE_H__
#define __ANYINDEX_BINARYTREEBASE_H__

// Refer to STL basics
#include "anybase\anystl.h"

// Spatial Index Package
namespace AnyIndex
{
	// Forward classes
	class CAnyInterval;
	class CAnyGeometry;

    /*!
    * \breif
	* Common behaviors belonging to root and other nodes of a binary tree
    **/
    class CAnyBinaryTreeBase
    {
    public:
        //
        //
        //
        /*!
        *
        **/
        CAnyBinaryTreeBase();

        /*!
        *
        **/
        virtual ~CAnyBinaryTreeBase();

	private:
		//
		//
		//
		/*!
		* Not permitted
		**/
		CAnyBinaryTreeBase(const CAnyBinaryTreeBase &other)
		{
		}

		/*!
		* Not permitted
		**/
		const CAnyBinaryTreeBase &operator = (const CAnyBinaryTreeBase &other)
		{
		}

    public:
        //
        //
        //
        /*!
        *
        **/
        virtual void Add(void* item);

		//
		// Characteristic methods
		//
        /*!
        * Items belonging to current node
        **/
        virtual const std::vector<void*> &GetCurrentItems() const;

        /*!
        *
        **/
        virtual void GetAllItems(std::vector<void*> &collect);

        /*!
        *
        **/
		virtual void GetAllItems(const CAnyInterval &interval, vector<void*> &collect);

        /*!
        * The number of descedent nodes
        **/
        virtual int Depth();

        /*!
        * Get the item number belonging to this node and its descedent nodes
        **/
        virtual int ItemSize();

        /*!
        *
        **/
        virtual int NodeSize();


    protected:
        //
        //
        //
        /*!
        *
        **/
        virtual bool IsSearchMatch(const CAnyInterval &interval) = 0;

		//
		// Common methods for its descedents
		//
        /*!
        *
        **/
        static int GetSubnodeIndex(const CAnyInterval &curInterval, double center);

    protected:
        // Tree container and not restrict its pointer types for future broad usages
        std::vector<void *> m_items;

        // Subnodes are numbered as follows:
        //  0 | 1
        CAnyBinaryTreeBase *m_subNodes[2];
    };
}
#endif