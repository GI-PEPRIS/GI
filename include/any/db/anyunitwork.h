/*!
 * The AnyDB of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the persistence-related architectural patterns such as MAPPER etc.
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
#ifndef __ANYDB_UNITWORK_H__
#define __ANYDB_UNITWORK_H__

// Refer to EXPORT etc
#include "anydb.h"

// Import STL definitions
#include "any/base/anystl.h"

// refer to thread issues
#include "any/thread/jtc.h"

// refer to anyobject
#include "any/base/anyobject.h"
using namespace AnyBase;

// refer to smart pointer
#include "boost\smart_ptr.hpp"
using namespace boost;

// X needs to have dll-interface to be used by clients of class Z
#pragma warning(push)
#pragma warning(disable: 4251)

// SoftCOVERY package -> MemBASE package
namespace AnyDB
{
	/*!
	* Under the help of the idea of the double bufferes on graphic rendering, this class knows 
	* the least recently used objects in memory. In theory there should be an alone thread monitoring 
	* the changes of memory cache. 
	* That is,this alone thread will use this class to decide which object should stay continuely in memory 
	* and which  not.
	* (TODO: Add thread-safe mechannism to this class).This class provides monitoring thread with 
	* useful infomation. 
	* If monitoring thread decide to move one a object from memory, it will firstly select the leatest recently 
	* used object. 
	**/
	class ANYDB_CLASS CAnyUnitWork : public JTCMonitor
    {
		// relatives
		friend class CAnyAccessor;

		/*!
		* Cache unit
		**/
		struct CacheUnit
		{
			long m_idx;
			boost::shared_ptr<CAnyObject> m_obj;

			/*!
			*
			**/
			CacheUnit() : m_obj(boost::shared_ptr<CAnyObject>()), m_idx(-1)
			{
			}

			/*!
			*
			**/
			const CacheUnit &operator=(const CacheUnit &other)
			{
				m_idx = other.m_idx;
				m_obj = other.m_obj;
			}
		};

		// The status of object maintained in memory indicating whether it is used: 
		// eAdd means object just be used, may be just inserted, may be updated,etc.
		// eRemove means object is just be removed from memory.
		enum OperationType{eAdd, eRemove};

		// The content of flag of this object recording all recently used objects 
		// whose frequences will be maintined in the below map; 
		// That is, the iterators of this list are in below map.
		typedef std::list<long> list_t;
		typedef std::map<long, list_t::iterator> map_t;		
		typedef std::map<long, OperationType> map_c;

		// object cache
		typedef std::list<CacheUnit> list_cache;
		typedef list_cache::iterator cache_itr;
		typedef list_cache::const_iterator cache_citr;

		// Singleton
		//typedef SingletonHolder<CAnyUnitWork, CreateUsingNew> Singleton;

	public:
		//
		// Constructors and deconstructor
		//
		/*!
		* Default constructor
		*/
		CAnyUnitWork();

		/*!
		* Deconstructor
		*/
		~CAnyUnitWork();

    public:
		//
		// Basic methods for updating both buffers
		//
		/*!
		* Record this object ID means this object is just used and should be in the top of list,
		* especially when getting a object from memory or persisted medium
		*/
		void RegisterAdded(CAnyObject *obj);

		/*!
		* Record this object ID means this object is just deleted and never be used
		*/
		void RegisterRemoved(long objectID);

		/*!
		* The least recently used frequence object always at the tail of this list and get its
		* reference and don't remove it
		* 
		* @Return: the object is the least used frequence
		*/
		CAnyObject *GetRegistered(long objectID);

		/*!
		* Get the latest statistics of used status of objects with both buffers
		*/
		void Commit();

		/*!
		* Clear all contents maintained in a list and map
		*/
		void Clear(bool isAll = true);

		/*!
		*
		**/
		cache_itr FindObject(long objectID);

    protected:
		//
		// Basic methods for operating that unique ID list and position map
		//
		/*!
		* Always keep the just used object in the top positions
		*
		* @Param1: the unique object ID of one object that is just be used
		*/
		void AddTo(long objectID);

		/*
		* Since this object is no need to stay in memory, so we remove the recorded information
		* about it
		*
		* @Param1: the unique ID of one object that is never be used
		*/
		void RemoveFrom(long objectID);
		
		/*!
		*
		**/
		void DoCommit(long objectID, bool isDelete = false);

		/*!
		*
		**/
		static bool CompareIdx(const CacheUnit &first, const CacheUnit &second)
		{
			return first.m_idx < second.m_idx;
		}

    protected:
		// Double buffer ideas:
		// A monitoring thread will poll the used frequence from this object in nealy the same time, 
		// two changes map should have little difference in order to efficiently get the used/changed frequence of 
		// objects.
		// The object in top position of changes list should be used often, object located tail may be removed 
		// from memory.

		// TODO: 
		// Here simply use one integer valuse as an unique flag. and it should be replaced by 
		// other style of the unique flag of persisted object
		// Current changes list is the result from comparison with both
		map_c m_fChanges;
		map_c m_sChanges;
		map_c *m_changes;

		// ids in memory whose order reflect the fresh of usage
		list_t m_idxes;
		// Quickly seek the object idx
		map_t m_positions;
		// objects' cache
		list_cache m_cache;
    };
}
#pragma warning(pop)

#endif