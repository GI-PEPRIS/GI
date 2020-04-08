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
#ifndef __ANYINDEX_BINARYTREEKEY_H__
#define __ANYINDEX_BINARYTREEKEY_H__

// Refer to its interval definition
#include "anyinterval.h"

//
namespace AnyIndex
{
    /*!
	* \brief
	* A Key is a unique identifier for a node in a binary tree.
	* It contains a lower-left point and a level number. The level number
	* is the power of two for the size of the node envelope/interval
     **/
    class CAnyBinaryTreeKey
    {
    public:
        //
        //
        //
        /*!
        *
        **/
        CAnyBinaryTreeKey(const CAnyInterval &interval);

        /*!
        *
        **/
        ~CAnyBinaryTreeKey();

    public:
        //
        //
        //
        /*!
        *
        **/
	    double GetPoint() const;

        /*!
        *
        **/
	    int GetLevel() const;

        /*!
        *
        **/
	    const CAnyInterval &GetInterval() const;

	private:
		//
		//
		//
        /*!
        * \brief
		* To get the level and interval definition of current binary tree node
        **/
	    void ComputeKey(const CAnyInterval &curInterval);

        /*!
        *
        **/
    	int DoComputeLevel(const CAnyInterval &curInterval);

        /*!
        *
        **/
	    void DoComputeInterval(int level, const CAnyInterval &curInterval);

    private:
	    // The fields making up the current key
		// ...

	    // its start position along one dimension
		double m_start;	 
		// its recursively level of splitting
		int m_level; 

	    // Auxiliary data which is derived from the key for use in computation
	    CAnyInterval m_interval;
    };
}

#endif