/*!
 * The AnyOGRE of PetroCOVERY Solution is a collection of native C++ classes that implement 
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
#ifndef __ANYOGRE_OGRE_RECT_LAYOUT_H__
#define __ANYOGRE_OGRE_RECT_LAYOUT_H__

//
#include "anyogre.h"
#include "any/base/anystl.h"

//
namespace AnyOGRE
{
	class ANYOGRE_CLASS CAnyOgreRectLayoutManager
	{
	public:
		enum MethodType 
		{
			PLACE_ABOVE = 0,		// the overlapping rectangles are placed above the non-overlapping ones
			PLACE_BELOW			// the overlapping rectangles are placed below the non-overlapping ones
		};
 
		class Rect
		{
		public:
			Rect(short left, short top, short right, short bottom)
				: mLeft(left)
				, mTop(top)
				, mRight(right)
				, mBottom(bottom)
				, dy(0)
			{
				if (mBottom <= mTop)
					throw std::exception("Condition Failure (top < bottom) in RectLayoutManager::Rect::Rect");
 
				if (mRight <= mLeft)
					throw std::exception("Condition Failure (left < right) in RectLayoutManager::Rect::Rect");
			}
 
			inline const short getTop() const {return mTop + dy;}
			inline const short getBottom() const {return mBottom + dy;}
			inline const short getLeft() const {return mLeft;}
			inline const short getRight() const {return mRight;}
 
			// STL needs this
			inline bool operator <(const CAnyOgreRectLayoutManager::Rect &R) const {return getBottom() < R.getBottom();}
 
			// displacement on Y axis
			short dy;
 
			// original rectangle coordinates
			short mBottom;
			short mTop;
			short mLeft;
			short mRight;
		};
		typedef std::list<CAnyOgreRectLayoutManager::Rect> RectList;

	public:
 		CAnyOgreRectLayoutManager(	unsigned short leftBound,
							unsigned short topBound,
							unsigned short rightBound,
							unsigned short bottomBound,
							MethodType method = PLACE_ABOVE)
		: mMethod(method)
		, mBoundTop(topBound)
		, mBoundLeft(leftBound)
		, mBoundBottom(bottomBound)
		, mBoundRight(rightBound)
		, mMinDistance(1)
		, mMaxRectHeight(0)
		, mDepth(0)
		{
			if (mBoundBottom <= mBoundTop)
				throw std::exception("Condition Failure (mBoundTop < mBoundBottom) in RectLayoutManager::RectLayoutManager");
 
			if (mBoundRight <= mBoundLeft)
				throw std::exception("Condition Failure (mBoundLeft < mBoundRight) in RectLayoutManager::RectLayoutManager");
		}
 
		~CAnyOgreRectLayoutManager(){clear();}
 
		const unsigned short getMinDistance() const {return mMinDistance;}
		const unsigned short getMaxRectHeight() const {return mMaxRectHeight;}
		const unsigned short getDepth() const {return mDepth;}
		void getBounds(	unsigned short &left,
						unsigned short &top,
						unsigned short &right,
						unsigned short &bottom)
		{
			left = mBoundLeft;
			top = mBoundTop;
			right = mBoundRight;
			bottom = mBoundBottom;
		}
 
		void setMinDistance(unsigned short minDistance){mMinDistance = minDistance;}
		void setDepth(unsigned short depth){mDepth = depth;}
 
		bool isOutOfBounds(CAnyOgreRectLayoutManager::Rect &r)
		{
			if (r.getTop() < mBoundTop ||
				r.getBottom() > mBoundBottom ||
				r.getLeft() < mBoundLeft ||
				r.getRight() > mBoundRight)
				return true;
			else
				return false;
		}
 
		RectList::iterator getListBegin(){return mList.begin();}
		RectList::iterator getListEnd(){return mList.end();}
 
		void clear(){mList.clear();}
 
		RectList::iterator addData(Rect &Data)
		{
			if (isOutOfBounds(Data))
				return mList.end(); // out of bounds, error
 
			switch (mMethod)
			{
			case PLACE_ABOVE:
				return addDataAbove(Data);
			case PLACE_BELOW:
				return addDataBelow(Data);
			default:
				return mList.end(); // incorrect method type, error
			}
		}
 
protected:
		// List of orderedd rectangles
		// All items in list are assumed ordered and within established Bounds
		RectList mList;
 
		// The overlapping rectangles are placed at a mMinDistance from the other ones
		unsigned short mMinDistance;
 
		// This gets calculated "on the fly"
		unsigned short mMaxRectHeight;
 
		// An overlapping rectangle is moved on Y axis (Above or Below) untill
		//  a place is found where it doesn't overlap any other rectangle.
		// mDepth is the number of times an overlapping rectangle will be moved
		//  in order to find a non-overlapping place.
		//
		// (mDepth = 0) - the search will go on untill a place is found.
		// (mDepth > 0) - the search will go on <mDepth> times
		unsigned short mDepth;	
 
		// Don't use these directly, use addData instead
		RectList::iterator addDataAbove(Rect &Data);
		RectList::iterator addDataBelow(Rect &Data);
 
		// Const variables can only be set in the constructor and certify the RectList integrity.
 
		// Method Type
		const MethodType mMethod;
 
		// Bounds
		const unsigned short mBoundTop;
		const unsigned short mBoundLeft;
		const unsigned short mBoundBottom;
		const unsigned short mBoundRight;
	};
}
#endif
