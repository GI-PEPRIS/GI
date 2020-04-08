#ifndef __ANYBASE_LOKI_SINGLETON_H__
#define __ANYBASE_LOKI_SINGLETON_H__

// Refer to STL defintions
#include "any/base/anystl.h"

// Refer to thread-related definitions
#include "threads.h"

/*!
* The most important issues associated with designing and implementing various Singleton variants in C++:
* 1) The features that set apart a singleton from a simple global object
* 2) The basic C++ idioms supporting singletons
* 3) Better enforcement of a singleton's uniqueness
* 4) Destroying the singleton and detecting postdestruction access
* 5) Implementing solutions for advanced lifetime management of the Singleton object
* 6) Multithreading issues
**/
namespace AnyBase
{
	/*!
	* Note:
	* This include file is benefited from the ideas of "Modern C++" written by  by Andrei Alexandrescu
	*/
	namespace Loki
	{
		// C lib standard function prototype for exit of current application
		#define C_CALLING_CONVENTION_QUALIFIER __cdecl 
		typedef void (C_CALLING_CONVENTION_QUALIFIER *atexit_pfn_t)();

		// Global function for calling back to above function prototype
		void C_CALLING_CONVENTION_QUALIFIER AtExitFn();

		/*!
		* Helper class for SetLongevity
		*/
		class LifetimeTracker
		{
		public:
			/*!
			*
			**/
			LifetimeTracker(unsigned int x) : m_longevity(x) 
			{}

			/*!
			*
			**/
			virtual ~LifetimeTracker()
			{
			}
		    
		public:
			/*!
			*
			**/
			static bool Compare(const LifetimeTracker *lhs, const LifetimeTracker *rhs)
			{
				return lhs->m_longevity > rhs->m_longevity;
			}
		    
		private:
			// Life time indicator of an object and using it to define 
			// which is firstly to be deleted and which is the last one
			unsigned int m_longevity;
		};

		// Helper data
		typedef LifetimeTracker **TrackerArray;
		extern TrackerArray pTrackerArray;
		extern unsigned int elements;

		/*!
		* Helper destroyer function
		**/
		template <typename T>
		struct Deleter
		{
			static void Delete(T* pObj)
			{ delete pObj; }
		};

		/*!
		* Concrete lifetime tracker for objects of type T
		**/
        template <typename T, typename Destroyer>
        class ConcreteLifetimeTracker : public LifetimeTracker
        {
        public:
            ConcreteLifetimeTracker(T* p,unsigned int longevity, Destroyer d)
                : LifetimeTracker(longevity)
                , m_tracked(p)
                , m_destroyer(d)
            {}
            
            ~ConcreteLifetimeTracker()
            { m_destroyer(m_tracked); }
            
        private:
            T *m_racked;
            Destroyer m_destroyer;
        };

		/*!
		* Assigns an object a longevity; ensures ordered destructions of objects registered 
		* thusly during the exit sequence of the application
		**/
		template <typename T, typename Destroyer>
		void SetLongevity(T *pDynObject, unsigned int longevity, Destroyer d = Deleter<T>::Delete)
		{
			TrackerArray pNewArray = static_cast<TrackerArray>(std::realloc(pTrackerArray, sizeof(*pTrackerArray) * (elements + 1)));
			if(!pNewArray) 
			{
				throw std::bad_alloc();
			}
		    
			// Delayed assignment for exception safety
			pTrackerArray = pNewArray;
			LifetimeTracker *p = new ConcreteLifetimeTracker<T, Destroyer>(pDynObject, longevity, d);
		            
			// Insert a pointer to the object into the queue
			TrackerArray pos = std::upper_bound(
				pTrackerArray, 
				pTrackerArray + elements, 
				p, 
				LifetimeTracker::Compare);
			std::copy_backward(
				pos, 
				pTrackerArray + elements,
				pTrackerArray + elements + 1);
			*pos = p;
			++elements;
		    
			// Register a call to AtExitFn
			std::atexit(AtExitFn);
		}

		/**
		* Implementation of the CreationPolicy used by SingletonHolder 
		* Creates objects using a straight call to the new operator 
		**/
		template <class T> struct CreateUsingNew
		{
			static T *Create()
			{ return new T; }
		    
			static void Destroy(T* p)
			{ delete p; }
		};
    
		/**
		* Implementation of the CreationPolicy used by SingletonHolder
		* Creates objects using a call to std::malloc, followed by a call to the placement new operator
		**/
		template <class T> struct CreateUsingMalloc
		{
			static T *Create()
			{
				void *p = std::malloc(sizeof(T));
				if(!p)
				{
					return 0;
				}
				return new(p) T;
			}
		    
			static void Destroy(T* p)
			{
				p->~T();
				std::free(p);
			}
		};

		/*!
		* Implementation of the CreationPolicy used by SingletonHolder
		* Creates an object in static memory
		* Implementation is slightly nonportable because it uses the MaxAlign trick  (an union of all types to ensure proper memory alignment). 
		* This trick is nonportable in theory but highly portable in practice.
		**/
		template <class T> struct CreateStatic
		{        
		#ifdef _MSC_VER
		#pragma warning( push ) 
		// alignment of a member was sensitive to packing
		#pragma warning( disable : 4121 )
		#endif // _MSC_VER
			union MaxAlign
			{
				char t_[sizeof(T)];
				short int shortInt_;
				int int_;
				long int longInt_;
				float float_;
				double double_;
				long double longDouble_;
				struct Test;
				int Test::* pMember_;
				int (Test::*pMemberFn_)(int);
			};
		#ifdef _MSC_VER
		#pragma warning( pop )
		#endif // _MSC_VER
		    
			static T *Create()
			{
				static MaxAlign staticMemory_;
				return new(&staticMemory_) T;
			}
		    
			static void Destroy(T* p)
			{
				p->~T();
			}
		};

		/*!
		* Implementation of the LifetimePolicy used by SingletonHolder
		* Schedules an object's destruction as per C++ rules
		* Forwards to std::atexit
		**/
		template <class T>
		struct DefaultLifetime
		{
			static void ScheduleDestruction(T*, atexit_pfn_t pFun)
			{ std::atexit(pFun); }

			static void OnDeadReference()
			{ throw std::logic_error("Dead Reference Detected"); }
		};

		/**
		* Implementation of the LifetimePolicy used by SingletonHolder
		* Schedules an object's destruction as per C++ rules, and it allows object  recreation by not throwing 
		* an exception from OnDeadReference
		**/
		template <class T>
		class PhoenixSingleton
		{
		public:
			static void ScheduleDestruction(T*, atexit_pfn_t pFun)
			{
		#ifndef ATEXIT_FIXED
				if (!m_isDestroyedOnce)
		#endif
					std::atexit(pFun);
			}
		    
			static void OnDeadReference()
			{
		#ifndef ATEXIT_FIXED
				m_isDestroyedOnce = true;
		#endif
			}
		    
		private:
		#ifndef ATEXIT_FIXED
			static bool m_isDestroyedOnce;
		#endif
		};

		#ifndef ATEXIT_FIXED
		template <class T> bool PhoenixSingleton<T>::m_isDestroyedOnce = false;
		#endif
        

		/*!
		* Implementation of the LifetimePolicy used by SingletonHolder
		* Schedules an object's destruction in order of their longevities
		* Assumes a visible function GetLongevity(T*) that returns the longevity of the object
		**/
		template <class T>
		class SingletonWithLongevity
		{
			/*!
			* Helper for SingletonWithLongevity below
			**/
			template <class T>
			struct Adapter
			{
				void operator()(T*) { return m_fun(); }
				atexit_pfn_t m_fun;
			};

		public:
			static void ScheduleDestruction(T *pObj, atexit_pfn_t pFun)
			{
				Adapter<T> adapter = { pFun };
				SetLongevity(pObj, GetLongevity(pObj), adapter);
			}
		    
			static void OnDeadReference()
			{ throw std::logic_error("Dead Reference Detected"); }
		};

		/*!
		* Implementation of the LifetimePolicy used by SingletonHolder
		* Never destroys the object
		**/
		template <class T>
		struct NoDestroy
		{
			static void ScheduleDestruction(T*, atexit_pfn_t)
			{}
		    
			static void OnDeadReference()
			{}
		};

		/*!
		* Provides Singleton amenities for a type T
		* To protect that type from spurious instantiations, you have to protect it yourself.
		**/
		template
		<
			class ClientType,
			class ThreadingModelType,
			class PtrInstanceType
		>
		class SingletonHolderStaticData
		{
			friend ClientType; // illegal (11.4/2) but works with VC

			static PtrInstanceType    s_pInstance;
			static bool               s_destroyed;
		};

		template<class C, class M, class P>
		P SingletonHolderStaticData<C, M, P>::s_pInstance;

		template<class C, class M, class P>
		bool SingletonHolderStaticData<C, M, P>::s_destroyed;

		template
		<
			typename T,
			template <class> class CreationPolicy = CreateUsingNew,
			template <class> class LifetimePolicy = DefaultLifetime,
			template <class> class ThreadingModel = SingleThreaded
		>
		class SingletonHolder
		{
			typedef typename ThreadingModel<T*>::VolatileType PtrInstanceType;
			typedef SingletonHolderStaticData
			<
				SingletonHolder,
				ThreadingModel<T>,
				PtrInstanceType
			>
			MySingletonHolderStaticData;

		public:
			static T &Instance()
			{
				if (!pInstance_())
				{
					MakeInstance();
				}
				return *pInstance_();
			}
		    
		private:
			// Helpers
			static void MakeInstance()
			{
				typename ThreadingModel<SingletonHolder>::Lock guard;
				(void)guard;

				if (!pInstance_())
				{
					if(destroyed_())
					{
						LifetimePolicy<T>::OnDeadReference();
						destroyed_() = false;
					}

					pInstance_() = CreationPolicy<T>::Create();

					LifetimePolicy<T>::ScheduleDestruction
					(
						pInstance_(), 
						&DestroySingleton
					);
				}
			}

			static void C_CALLING_CONVENTION_QUALIFIER DestroySingleton()
			{
				assert(!destroyed_());
				CreationPolicy<T>::Destroy(pInstance_());
				pInstance_() = 0;
				destroyed_() = true;
			}
		    
			// Protection
			SingletonHolder();
		    
			// Data
			static PtrInstanceType &pInstance_()
			{
				return MySingletonHolderStaticData::s_pInstance;
			}

			static bool &destroyed_()
			{
				return MySingletonHolderStaticData::s_destroyed;
			}
		};
	}
}

#endif