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
#ifndef __ANYBASE_LOKI_THREADS_H__
#define __ANYBASE_LOKI_THREADS_H__

// Refer to CRITICAL_SECTION definition
#include <cassert>

// Modern C++: 
// Policies to for the threading model:
//
// - SingleThreaded
// - ObjectLevelLockable
// - ClassLevelLockable
//
//  To use a specific threading model define
//
//  - nothing, single-theading is default
//  - LOKI_OBJECT_LEVEL_THREADING for object-level-threading
//  - LOKI_CLASS_LEVEL_THREADING for class-level-threading

// Note:
// No recursive mutex support with pthread.
// This means: calling Lock() on a Loki::Mutex twice from the
// same thread before unlocking the mutex deadlocks the system.
//
namespace AnyBase
{
	// Compile macroes for strategies of thread-safe 
	#define LOKI_CLASS_LEVEL_THREADING
	#define LOKI_OBJECT_LEVEL_THREADING

	// Compiling various
	#if defined(LOKI_CLASS_LEVEL_THREADING) || defined(LOKI_OBJECT_LEVEL_THREADING)

		#define LOKI_DEFAULT_THREADING_NO_OBJ_LEVEL AnyBase::Loki::ClassLevelLockable

		#if defined(LOKI_CLASS_LEVEL_THREADING) && !defined(LOKI_OBJECT_LEVEL_THREADING)
			#define LOKI_DEFAULT_THREADING AnyBase::Loki::ClassLevelLockable
		#else
			#define LOKI_DEFAULT_THREADING AnyBase::Loki::ObjectLevelLockable
		#endif

		#if defined(_WIN32) || defined(_WIN64)
			#include <windows.h>
			#define LOKI_WINDOWS_H
		#else
			#include <pthread.h>
			#define LOKI_PTHREAD_H
		#endif

	#else
		// Without any thread-safe protect
		#define LOKI_DEFAULT_THREADING AnyBase::Loki::SingleThreaded
		#define LOKI_DEFAULT_THREADING_NO_OBJ_LEVEL AnyBase::Loki::SingleThreaded
	#endif

	#ifndef LOKI_DEFAULT_MUTEX
		#define LOKI_DEFAULT_MUTEX AnyBase::Loki::Mutex
	#endif

	// Subject to MS platform series
	#ifdef LOKI_WINDOWS_H

	#define LOKI_THREADS_MUTEX(x)           CRITICAL_SECTION (x);
	#define LOKI_THREADS_MUTEX_INIT(x)      InitializeCriticalSection (x)
	#define LOKI_THREADS_MUTEX_DELETE(x)    DeleteCriticalSection (x)
	#define LOKI_THREADS_MUTEX_LOCK(x)      EnterCriticalSection (x)
	#define LOKI_THREADS_MUTEX_UNLOCK(x)    LeaveCriticalSection (x)
	#define LOKI_THREADS_LONG               LONG
	#define LOKI_THREADS_MUTEX_CTOR(x)

	// Common thread-safe functions for class-level and object-level
	#define LOKI_THREADS_ATOMIC_FUNCTIONS																					\
		private:                                                         													\
			static CRITICAL_SECTION atomic_mutex_;                        													\
		public:																												\
			static IntType AtomicMultiply(volatile IntType &lval, const IntType val)										\
			{																												\
				EnterCriticalSection(&atomic_mutex_);																		\
				lval *= val;																								\
				LeaveCriticalSection(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicDivide(volatile IntType &lval, const IntType val)											\
			{																												\
				EnterCriticalSection(&atomic_mutex_);																		\
				lval /= val;																								\
				LeaveCriticalSection(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicIncrement(volatile IntType &lval)															\
			{																												\
				EnterCriticalSection(&atomic_mutex_);																		\
				++lval;																										\
				LeaveCriticalSection(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicDecrement(volatile IntType &lval)															\
			{																												\
				EnterCriticalSection(&atomic_mutex_);																		\
				--lval;																										\
				LeaveCriticalSection(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static void AtomicAssign(volatile IntType &lval, const IntType val)												\
			{																												\
				InterlockedExchange(&const_cast<IntType&>(lval), val);														\
			}																		    									\
																															\
			static void AtomicAssign(IntType &lval, volatile const IntType &val)											\
			{																												\
				InterlockedExchange(&lval, val);																			\
			}																												\
																															\
			static IntType AtomicIncrement(volatile IntType &lval, const IntType compare, bool &matches)    				\
			{																			                    				\
				EnterCriticalSection(&atomic_mutex_);																		\
				++lval;																										\
				matches = (lval == compare);																				\
				LeaveCriticalSection(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicDecrement(volatile IntType &lval, const IntType compare, bool &matches)    				\
			{																												\
				EnterCriticalSection(&atomic_mutex_);										                				\
				--lval;																										\
				matches = (lval == compare);											                    				\
				LeaveCriticalSection(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicAdd(volatile IntType &lval, const IntType val, const IntType compare, bool &matches )  	\
			{																												\
				EnterCriticalSection(&atomic_mutex_);													                	\
				lval += val;																								\
				matches = (lval == compare);																				\
				LeaveCriticalSection(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicSubtract(volatile IntType &lval, const IntType val, const IntType compare, bool &matches)	\
			{																												\
				EnterCriticalSection(&atomic_mutex_);																		\
				lval -= val;																								\
				matches = (lval == compare);																				\
				LeaveCriticalSection(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicMultiply(volatile IntType &lval, const IntType val, const IntType compare, bool &matches)  \
			{																												\
				EnterCriticalSection(&atomic_mutex_);													                    \
				lval *= val;																								\
				matches = (lval == compare);																				\
				LeaveCriticalSection(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicDivide(volatile IntType &lval, const IntType val, const IntType compare, bool &matches )   \
			{																												\
				EnterCriticalSection(&atomic_mutex_);													                    \
				lval /= val;																								\
				matches = (lval == compare);													                            \
				LeaveCriticalSection( &atomic_mutex_ );																	\
				return lval;																								\
			}

	#elif defined(LOKI_PTHREAD_H)


	#define LOKI_THREADS_MUTEX(x)           pthread_mutex_t (x);
	#define LOKI_THREADS_MUTEX_INIT(x)      ::pthread_mutex_init(x, 0)

	// define to 1 to enable recursive mutex support
	#if 0
	// experimental recursive mutex support
	#define LOKI_THREADS_MUTEX_CTOR(x)      : x(PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP)
	#else
	// no recursive mutex support
	#define LOKI_THREADS_MUTEX_CTOR(x)
	#endif

	#define LOKI_THREADS_MUTEX_DELETE(x)    ::pthread_mutex_destroy (x)
	#define LOKI_THREADS_MUTEX_LOCK(x)      ::pthread_mutex_lock (x)
	#define LOKI_THREADS_MUTEX_UNLOCK(x)    ::pthread_mutex_unlock (x)
	#define LOKI_THREADS_LONG               long

	#define LOKI_THREADS_ATOMIC(x)                                           												\
					pthread_mutex_lock(&atomic_mutex_);                      												\
					x;                                                       												\
					pthread_mutex_unlock(&atomic_mutex_)

	#define LOKI_THREADS_ATOMIC_FUNCTIONS                                													\
		private:                                                         													\
			static pthread_mutex_t atomic_mutex_;                        													\
		public:                                                          													\
			static IntType AtomicMultiply(volatile IntType &lval, const IntType val)										\
			{																												\
				::pthread_mutex_lock(&atomic_mutex_);																		\
				lval *= val;																								\
				::pthread_mutex_unlock(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicDivide(volatile IntType &lval, const IntType val)											\
			{                                                                												\
				::pthread_mutex_lock(&atomic_mutex_);                        												\
				lval /= val;                                                 												\
				::pthread_mutex_unlock(&atomic_mutex_);                      												\
				return lval;                                                 												\
			}                                                                												\
																			 												\
			static IntType AtomicIncrement(volatile IntType &lval)           												\
			{                                                                												\
				::pthread_mutex_lock(&atomic_mutex_);	                     												\
				++lval;                                                      												\
				:pthread_mutex_unlock(&atomic_mutex_);		                 												\
				return lval;                                                 												\
			}                                                                												\
																			 												\
			static IntType AtomicDecrement(volatile IntType &lval)           												\
			{                                                                												\
				::pthread_mutex_lock(&atomic_mutex_);                        												\
				--lval;                                                      												\
				::pthread_mutex_unlock(&atomic_mutex_);                      												\
				return lval;                                                 												\
			}                                                                												\
																			 												\
			static void AtomicAssign(volatile IntType &lval, const IntType val)												\
			{																												\
				::pthread_mutex_lock(&atomic_mutex_);																		\
				lval = val;																									\
				::pthread_mutex_unlock( &atomic_mutex_ );																	\
				return lval;																								\
			}																												\
																															\
			static void AtomicAssign(IntType &lval, volatile const IntType &val)											\
			{																												\
				::pthread_mutex_lock(&atomic_mutex_);																		\
				lval = val;																									\
				::pthread_mutex_unlock(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicIncrement(volatile IntType &lval, const IntType compare, bool &matches)					\
			{																												\
				::pthread_mutex_lock(&atomic_mutex_);																		\
				++lval;																										\
				matches = (compare == lval);																				\
				::pthread_mutex_unlock(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicDecrement(volatile IntType &lval, const IntType compare, bool &matches)					\
			{																												\
				::pthread_mutex_lock(&atomic_mutex_);																		\
				--lval;																										\
				matches = (compare == lval);																				\
				::pthread_mutex_unlock(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicMultiply(volatile IntType &lval, const IntType val, const IntType compare, bool &matches)  \
			{																												\
				::pthread_mutex_lock(&atomic_mutex_);													                    \
				lval *= val;																								\
				matches = (lval == compare);																				\
				::pthread_mutex_unlock(&atomic_mutex_);																		\
				return lval;																								\
			}																												\
																															\
			static IntType AtomicDivide(volatile IntType &lval, const IntType val, const IntType compare, bool &matches)	\
			{																												\
				::pthread_mutex_lock(&atomic_mutex_);																		\
				lval /= val;																								\
				matches = (lval == compare);																				\
				::pthread_mutex_unlock(&atomic_mutex_);																		\
				return lval;																								\
			}

	#else // single threaded

	#define LOKI_THREADS_MUTEX(x)
	#define LOKI_THREADS_MUTEX_INIT(x)
	#define LOKI_THREADS_MUTEX_DELETE(x)
	#define LOKI_THREADS_MUTEX_LOCK(x)
	#define LOKI_THREADS_MUTEX_UNLOCK(x)
	#define LOKI_THREADS_LONG
	#define LOKI_THREADS_MUTEX_CTOR(x)

#endif

	// Note:
	// This includes file which is benefited from the ideas of "Modern C++" written 
	// by Andrei Alexandrescu
	namespace Loki
	{
		/*!
		* \class Mutex
		*
		*  A simple and portable Mutex.  A default policy class for locking objects.
		**/
		class Mutex
		{
		public:
			/*!
			*
			**/
			Mutex() LOKI_THREADS_MUTEX_CTOR(m_mtx)
			{
				LOKI_THREADS_MUTEX_INIT(&m_mtx);
			}

			/*!
			*
			**/
			~Mutex()
			{
				LOKI_THREADS_MUTEX_DELETE(&m_mtx);
			}

		public:
			//
			//
			//
			/*!
			*
			**/
			void Lock()
			{
				// EnterCriticalSection for Windows
				LOKI_THREADS_MUTEX_LOCK(&m_mtx);
			}

			/*!
			*
			**/
			void Unlock()
			{
				// LeaveCriticalSection for Windows
				LOKI_THREADS_MUTEX_UNLOCK(&m_mtx);
			}

		private:
			//
			// Copy-constructor and Copy-assignement operator not implemented
			//
			/*!
			*
			**/
			Mutex(const Mutex&);

			/*!
			*
			**/
			Mutex &operator = (const Mutex&);

		private:
			// mutex variable
			// For Window versions, that means CRITICAL_SECTION
			LOKI_THREADS_MUTEX(m_mtx)
		};

		/*!
		* \brief
		*
		* Implements a single-threaded model with no synchronization
		**/
		template <class Host>
		class SingleThreaded
		{
		public:
            /*!
			* \brief
			*
			* Inner class for dummy usage
			**/
			struct Lock
			{
				/*!
				* 
				**/
				Lock() 
				{
					// Do nothing
				}

				/*!
				*
				**/
				explicit Lock(const SingleThreaded&) 
				{
					// Do nothing
				}

				/*!
				*
				**/
				explicit Lock(const SingleThreaded*) 
				{
					// Do nothing
				}
			};

			//
			// Atomic operations are subject to non-threaded environment
			//
			/*!
			* Alias names
			**/
			typedef Host VolatileType;
			typedef int IntType; 

			/*!
			*
			**/
			static IntType AtomicAdd(volatile IntType &lval, IntType val)
			{ 
				return lval += val; 
			}
		    
			/*!
			*
			**/
			static IntType AtomicSubtract(volatile IntType &lval, IntType val)
			{ 
				return lval -= val; 
			}

			/*!
			*
			**/
			static IntType AtomicMultiply(volatile IntType &lval, IntType val)
			{ 
				return lval *= val; 
			}
		    
			/*!
			*
			**/
			static IntType AtomicDivide(volatile IntType &lval, IntType val)
			{ 
				return lval /= val; 
			}

			/*!
			*
			**/
			static IntType AtomicIncrement(volatile IntType &lval)
			{ 
				return ++lval; 
			}
		    
			/*!
			*
			**/
			static IntType AtomicDecrement(volatile IntType &lval)
			{ 
				return --lval; 
			}
		    
			/*!
			*
			**/
			static void AtomicAssign(volatile IntType &lval, IntType val)
			{ 
				lval = val; 
			}
		    
			/*!
			*
			**/
			static void AtomicAssign(IntType &lval, volatile IntType &val)
			{ 
				lval = val; 
			}

			//
			// New versions
			//
			/*!
			*
			**/
			static IntType AtomicAdd(volatile IntType &lval, const IntType val, const IntType compare, bool &matches)
			{
				lval += val;
				matches = (lval == compare);
				return lval;
			}

			/*!
			*
			**/
			static IntType AtomicSubtract(volatile IntType &lval, const IntType val, const IntType compare, bool &matches)
			{
				lval -= val;
				matches = (lval == compare);
				return lval;
			}

			/*!
			*
			**/
			static IntType AtomicMultiply(volatile IntType &lval, const IntType val, const IntType compare, bool &matches)
			{
				lval *= val;
				matches = (lval == compare);
				return lval;
			}

			/*!
			*
			**/
			static IntType AtomicDivide(volatile IntType &lval, const IntType val, const IntType compare, bool &matches)
			{
				lval /= val;
				matches = (lval == compare);
				return lval;
			}

			/*!
			*
			**/
			static IntType AtomicIncrement(volatile IntType& lval, const IntType compare, bool & matches)
			{
				++lval;
				matches = (lval == compare);
				return lval;
			}

			/*!
			*
			**/
			static IntType AtomicDecrement(volatile IntType& lval, const IntType compare, bool & matches )
			{
				--lval;
				matches = (lval == compare);
				return lval;
			}
		};
		#define DEFAULT_THREADING SingleThreaded


		#if defined(LOKI_WINDOWS_H) || defined(LOKI_PTHREAD_H)
		/*!
		* \brief
		*
		* Implements a object-level locking scheme
		**/
		template <class Host, class MutexPolicy = LOKI_DEFAULT_MUTEX>
		class ObjectLevelLockable
		{
			// For windows it means critical section
			mutable MutexPolicy m_mtx;

		public:
			/*!
			*
			**/
			ObjectLevelLockable() : m_mtx() 
			{
				LOKI_THREADS_MUTEX_INIT(&atomic_mutex_);
			}

			/*!
			*
			**/
			ObjectLevelLockable(const ObjectLevelLockable&) : m_mtx() 
			{
				LOKI_THREADS_MUTEX_INIT(&atomic_mutex_);
			}

			/*!
			*
			**/
			~ObjectLevelLockable() 
			{
			}

			// Forward declarations
			class Lock;
			friend class Lock;

			//  Lock class to lock on object level
			class Lock
			{
			public:
				/*!
				* Lock object
				**/
				explicit Lock(const ObjectLevelLockable &host) : m_host(host)
				{
					m_host.m_mtx.Lock();
				}

				/*!
				* Lock object
				**/
				explicit Lock(const ObjectLevelLockable *host) : m_host(*host)
				{
					m_host.m_mtx.Lock();
				}

				/*!
				* Unlock object
				**/
				~Lock()
				{
					m_host.m_mtx.Unlock();
				}

			private:
				//
				// private by design of the object level threading
				//
				Lock();
				Lock(const Lock&);
				Lock& operator=(const Lock&);

			private:
				const ObjectLevelLockable &m_host;
			};

			typedef volatile Host VolatileType;
			typedef LOKI_THREADS_LONG IntType;

			// Macro functions
			LOKI_THREADS_ATOMIC_FUNCTIONS
		};

		#ifdef LOKI_PTHREAD_H
			template <class Host, class MutexPolicy>
			pthread_mutex_t ObjectLevelLockable<Host, MutexPolicy>::atomic_mutex_ = PTHREAD_MUTEX_INITIALIZER;
		#endif

		#ifdef LOKI_WINDOWS_H
			template <class Host, class MutexPolicy>
			CRITICAL_SECTION ObjectLevelLockable<Host, MutexPolicy>::atomic_mutex_;
		#endif

		/*!
		*  Implements a class-level locking scheme
		**/
		template <class Host, class MutexPolicy = LOKI_DEFAULT_MUTEX>
		class ClassLevelLockable
		{
			/*!
			*
			**/
			struct Initializer
			{
				bool m_init;
				MutexPolicy m_mtx;

				Initializer() : m_init(false), m_mtx()
				{
					m_init = true;
				}

				~Initializer()
				{
					assert(m_init);
				}
			};

			// For entries protect of all class-objects
			static Initializer m_initializer;

		public:
			/*!
			*
			**/
			ClassLevelLockable()
			{
				LOKI_THREADS_MUTEX_INIT(&atomic_mutex_);
			}

			// Forward declaration
			class Lock;
			friend class Lock;

			/*!
			* Lock class to lock on class level
			**/
			class Lock
			{
			public:
				/*!
				* Lock class
				**/
				Lock()
				{
					assert(m_initializer.m_init);
					m_initializer.m_mtx.Lock();
				}

				/*!
				* Lock class
				**/
				explicit Lock(const ClassLevelLockable&)
				{
					assert(m_initializer.m_init);
					m_initializer.m_mtx.Lock();
				}

				/*!
				* Lock class
				**/
				explicit Lock(const ClassLevelLockable*)
				{
					assert(m_initializer.m_init);
					m_initializer.m_mtx.Lock();
				}

				/*!
				* Unlock class
				**/
				~Lock()
				{
					assert(m_initializer.m_init);
					m_initializer.m_mtx.Unlock();
				}

			private:
				// Not permitted
				Lock(const Lock&);
				Lock& operator=(const Lock&);
			};

			typedef volatile Host VolatileType;
			typedef LOKI_THREADS_LONG IntType;

			// Function macroes
			LOKI_THREADS_ATOMIC_FUNCTIONS
		};

		#ifdef LOKI_PTHREAD_H
			template <class Host, class MutexPolicy>
			pthread_mutex_t ClassLevelLockable<Host, MutexPolicy>::atomic_mutex_ = PTHREAD_MUTEX_INITIALIZER;
		#endif

		#ifdef LOKI_WINDOWS_H
			template <class Host, class MutexPolicy>
			CRITICAL_SECTION ClassLevelLockable<Host, MutexPolicy>::atomic_mutex_;
		#endif

		template <class Host, class MutexPolicy>
		typename ClassLevelLockable<Host, MutexPolicy>::Initializer
		ClassLevelLockable<Host, MutexPolicy>::m_initializer;

		#endif // End of window_h and pthread_h
	}
}
#endif