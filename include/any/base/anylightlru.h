/*!
 * The AnyBase package of PetroCOVERY Solution is a collection of native C++ classes that 
 * implement the fundamental algorithms & operations required to 
 * satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYBASE_LIGHT_LRU_H__
#define __ANYBASE_LIGHT_LRU_H__

// Note: template class no need below macroes

// Refer STL container: deque
#include "anyport.h"

// Erase compiling warning condition
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z

// UeBase
namespace AnyBase
{
    // Cache unit 
    template<typename T>
    struct CacheUnit
    {
        int m_id;  // Merged by gate id and parcel id
        T *m_unit;   // Basic cache unit

        //
        // Useful default copy, assignment function implementation
        //
        /*!
        *
        */
        CacheUnit() : m_id(-1), m_unit(0)
        {
        }

        /*!
        *
        */
        CacheUnit(const CacheUnit& other)
        {
            m_id = other.m_id;
            m_unit = other.m_unit;
        }

        /*!
        *
        */
        const CacheUnit & operator = (const CacheUnit &other)
        {
            if(this == &other)
            {
                return *this;
            }

            m_id = other.m_id;
            m_unit = other.m_unit;

            return *this;
        }
    };

	/*!
	* Even if it share one general memory cache strategy here, but there still exist one fatal problem:
	* when insering a new memort chache unit and it need to delete the last one memory chache unit, how about if
	* the last one is still being used? One clumsy way is to enlarge the cache size and another root way is to use
	* smart pointer which indicates whether it is also being used.
	*
	*/
    template<typename T>
    class CAnyLightLru
    {
        // Cache continer
        typedef std::deque< CacheUnit<T> > SimpleCache;

    public:
        //
        //
        //
        /*!
        *
        */
        CAnyLightLru()
        {
            // Default size of cache
			// Note: this number can be decided by the size of one parcel, for example, this software
			// generally is used in the extent of parcels
            m_unitNumber = 10000;
        }

        /*!
        *
        */
        virtual ~CAnyLightLru()
        {
            EraseLRU();
        }

    public:
        //
        //
        //
        /*!
        *
        */
        void SetSize(short size);

		/*!
		*
		**/
		short GetSize();

        /*!
        *
        */
        T *GetUnit(int order);

        /*!
        *
        */
        T *GetUnit(short firstID, long secondID);

		/*!
		*
		**/
		bool IsExist(short firstID, long secondID);

        /*!
        *
        */
        void AddUnit(short firstID, long secondID, T *oneUnit);

        /*!
        *
        */
        void AddUnit(int unitID, T *oneUnit);

        /*!
        *
        */
        void EraseLRU(int tails = 0);

        /*!
        *
        */
        void EraseLRU(short firstID);

        /*!
        *
        */
        void EraseLRU(short firstID, long secondID);

		/*!
		*
		**/
		void MakeXOR(std::vector<int> &ids);

    protected:
        /*!
        *
        */
        T *MoveFirst(int order);

    public:
        // The continer of cache
        SimpleCache m_cache;
        // Maximum number of cache unit and this cache mechansim need the minmum number
        int m_unitNumber;    // The number can be evaluated by how much those parcels take on earth main memory
    };

	/*!
	*
	*/
	template<typename T>
	inline void CAnyLightLru<T>::SetSize(short size)
	{
		// Free unneccessary memory
		int count = static_cast<int>(m_cache.size());
		if(count > size)
		{
			int tails = count - size;
			EraseLRU(tails);
		}

		//
		m_unitNumber = size;
	}

	/*!
	*
	*/
	template<typename T>
	inline short CAnyLightLru<T>::GetSize()
	{
		int size = static_cast<int>(m_cache.size());
		return (size < m_unitNumber) ? size : m_unitNumber;
	}

	/*!
	*
	*/
	template<typename T>
	inline T *CAnyLightLru<T>::GetUnit(int order)
	{
		assert(order >= 0 && order < GetSize());
		return m_cache[order].m_unit;
	}

	/*!
	*
	*/
	template<typename T>
	inline T *CAnyLightLru<T>::GetUnit(short firstID, long secondID)
	{
		//int unitID = secondID << 8 | firstID;
		int unitID = firstID << 24 | secondID;

		// Note: the performance of finding one cache unit is limited to the number of cache
		int  i = 0;
		int count = static_cast<int>(m_cache.size());
		for(; i < count; i++)
		{
			if(unitID == m_cache[i].m_id)
			{
				return MoveFirst(i);
			}
		}

		return 0;
	}

	/*!
	*
	**/
	template<typename T>
	inline bool CAnyLightLru<T>::IsExist(short firstID, long secondID)
	{
		//int unitID = secondID << 8 | firstID;
		int unitID = firstID << 24 | secondID;

		// Note: the performance of finding one cache unit is limited to the number of cache
		int  i = 0;
		int count = static_cast<int>(m_cache.size());
		for(; i < count; i++)
		{
			if(unitID == m_cache[i].m_id)
			{
				return true;
			}
		}

		return false;
	}


	/*!
	*
	*/
	template<typename T>
	inline void CAnyLightLru<T>::AddUnit(int unitID, T *oneUnit)
	{
		assert(oneUnit);
		if(m_unitNumber == 0)
		{
			return;
		}

		// Firstly check whether already exist then move it
		// TODO: Get another quick way to find one element
		CacheUnit<T> oneCache;
		oneCache.m_id = unitID;
		oneCache.m_unit = oneUnit;

		//
		int i = 0;
		int count = static_cast<int>(m_cache.size());
		for(; i < count; i++)
		{
			if(oneCache.m_id == m_cache[i].m_id)
			{
				MoveFirst(i);
				return;
			}
		}

		// Secondly check whether it is already full
		if(count == m_unitNumber)
		{
			m_cache[m_unitNumber-1].m_unit->Delete();
			m_cache.erase(m_cache.begin() + m_unitNumber - 1);
		}

		// Lastly
		m_cache.push_front(oneCache);
	}

	/*!
	*
	*/
	template<typename T>
	inline void CAnyLightLru<T>::AddUnit(short firstID, long secondID, T *oneUnit)
	{
		//AddUnit(secondID << 8 | firstID, oneUnit);
		AddUnit(firstID << 24 | secondID, oneUnit);
	}

	/*!
	*
	*/
	template<typename T>
	inline void CAnyLightLru<T>::EraseLRU(int tails)
	{
		int count = static_cast<int>(m_cache.size());
		assert(count >= tails);

		if(tails > 0)
		{
			int i = tails;
			for(; i > 0; i--)
			{
				m_cache[count - i].m_unit->Delete();
			}
			m_cache.erase(m_cache.end() - tails, m_cache.end());
		}
		else
		{
			int i = 0;
			for(; i < count; i++)
			{
				m_cache[i].m_unit->Delete();
			}
			m_cache.erase(m_cache.begin(), m_cache.end());
		}
	}

	/*!
	*
	*/
	template<typename T>
	inline void CAnyLightLru<T>::EraseLRU(short firstID)
	{
		SimpleCache::iterator itrCacheUnit = m_cache.begin();
		while(itrCacheUnit != m_cache.end())
		{
			//if((((*itrCacheUnit).m_id & 0xFF000000) >> 8) == firstID)
			if((((*itrCacheUnit).m_id & 0xFF000000) >> 24) == firstID)
			{
				(*itrCacheUnit).m_unit->Delete();
				itrCacheUnit = m_cache.erase(itrCacheUnit);

				continue;
			}

			itrCacheUnit++;
		}
	}

	/*!
	*
	*/
	template<typename T>
	inline void CAnyLightLru<T>::EraseLRU(short firstID, long secondID)
	{
		//int id = secondID << 8 | firstID;
		int id = firstID << 24 | secondID;

		int count = static_cast<int>(m_cache.size());
		int i = 0;
		for(; i < count; i++)
		{
			if(m_cache[i].m_id == id)
			{
				m_cache[i].m_unit->Delete();
				m_cache.erase(m_cache.begin() + i);

				return;
			}
		}
	}

	/*!
	*
	*/
	inline static bool BinaryFunc(const int &first, const int &second)
	{
		return first < second;
	}

	/*!
	*
	*/
	template<typename T>
	inline void CAnyLightLru<T>::MakeXOR(std::vector<int> &ids)
	{
		//
		int i = 0;
		int size = static_cast<int>(m_cache.size());
		std::sort(ids.begin(), ids.end(), BinaryFunc);

		//
		SimpleCache::iterator first = m_cache.begin();
		SimpleCache::iterator end = m_cache.end();
		for(; first != m_cache.end(); /*first++*/)
		{
			//
			if(!std::binary_search(ids.begin(), ids.end(), (*first).m_id, BinaryFunc))
			{
				(*first).m_unit->Delete();
				first = m_cache.erase(first);
			}
			else
			{
				first++;
			}
		}
	}

	/*!
	*
	*/
	template<typename T>
	inline T *CAnyLightLru<T>::MoveFirst(int order)
	{
		assert(order < m_unitNumber);
		if(order)
		{
			CacheUnit<T> tmp = m_cache[order];

			int i = order;
			for(; i > 0; i--)
			{
			    m_cache[i] = m_cache[i-1];
			}

			m_cache[0] = tmp;

			// Below code exist one fatal bug: if find order = m_unitNumber is suddenly to be moved to the first one
			// but the first one is being used, OOPS!
			// 
			//CacheUnit<T> tmp = m_cache[order];
			//m_cache[order] = m_cache[0];
			//m_cache[0] = tmp;
		}

		return m_cache[0].m_unit;
	}
}

#endif
