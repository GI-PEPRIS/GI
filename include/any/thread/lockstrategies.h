
#ifndef JTC_LOCKSTRATEGY_H
#define JTC_LOCKSTRATEGY_H
#include "sync.h"
#include "rwmutex.h"
#include "boost\mpl\int.hpp"

/*!
*
**/
enum LOCK_STRATEGY_TYPE
{
	RWREAD_LOCK	=	0,
	RWWRITE_LOCK,
	NORMAL_LOCK,
	TIMED_LOCK,
	NULL_LOCK
};

/*!
*
**/
class CAnyLockable
{
protected:
	//
	//
	//
	/*!
	*
	**/
	CAnyLockable() : m_guard(0)
	{
	}

public:
	/*!
	*
	**/
	virtual int Aquire(void *mutex,long timeout) = 0;

	/*!
	*
	**/
	virtual int Release() = 0;

protected:
	JTCSynchronized* m_guard;
};

/*!
*
**/
class CAnyReadWriteLockable : public CAnyLockable
{
public:
	//
	//
	//
	/*!
	*
	**/
	int Aquire(void *mutex,long timeout)
	{
		assert(mutex);
		if(mutex)
		{
			m_guard=new JTCSynchronized(*(JTCRWMutex *)(mutex), JTCSynchronized::read_lock);
			return 1;
		}
		return 0;
	}

	/*!
	*
	**/
	int Release()
	{
		if(m_guard)
		{
			delete m_guard;
		}
		return 1;
	}
};

/*!
*
**/
class CAnyWriteLockable : public CAnyLockable
{
public:
	/*!
	*
	**/
	int Aquire(void *mutex,long timeout)
	{
		assert(mutex);
		if(mutex)
		{
			m_guard= new JTCSynchronized(*((JTCRWMutex *)(mutex)), JTCSynchronized::write_lock);
			return 1;
		}
		return 0;
	}

	/*!
	*
	**/
	int Release()
	{
		if(m_guard)
		{
			delete m_guard;
		}
		return 1;
	}
};

/*!
*
**/
class CAnyNormalLockable : public CAnyLockable
{
public:
	/*!
	*
	**/
	int Aquire(void *mutex,long timeout)
	{
		assert(mutex);
		if(mutex)
		{
			m_guard=new JTCSynchronized(*(JTCRecursiveMutex *)(mutex));
			return 1;
		}
		return 0;
	}

	/*!
	*
	**/
	int Release()
	{
		if(m_guard)
		{
			delete m_guard;
		}
		return 1;
	}
};

/*!
*
**/
class CAnyTimedLockable : public CAnyLockable
{
public:
	/*!
	*
	**/
	int Aquire(void *mutex,long timeout)
	{
		assert(mutex);
		if(mutex)
		{
			m_guard=new JTCSynchronized(*(JTCTimedMutex *)(mutex),timeout);
			return 1;
		}
		return 0;
	}

	/*!
	*
	**/
	int Release()
	{
		if(m_guard)
		{
			delete m_guard;
		}
		return 0;
	}
};

/*!
*
**/
class CAnyNullLockable : public CAnyLockable
{
	/*!
	*
	**/
	int Aquire(void *mutex,long timeout)
	{
		return 0;
	}

	/*!
	*
	**/
	int Release()
	{
		return 0;
	}
};

/*!
*
**/
template<class Lockable>
class CAnyScopeGuard
{
public:
	/*!
	*
	**/
	CAnyScopeGuard(void *mutex,long timeout=1000)
	{
		m_lock.Aquire(mutex,timeout);
	}

	/*!
	*
	**/
	~CAnyScopeGuard()
	{
		m_lock.Release();
	}

private:
	//
	Lockable m_lock;
	long m_timeout; //used by timedlock; milisecond
};

//
// lockable traits
//
/*!
*
**/
template<class Lockable>
struct LockableStrategy
{
};

template<>
struct  LockableStrategy<CAnyReadWriteLockable > : boost::mpl::int_<RWREAD_LOCK>
{
};

template<>
struct  LockableStrategy<CAnyWriteLockable > : boost::mpl::int_<RWWRITE_LOCK>
{
};

template<>
struct  LockableStrategy<CAnyNormalLockable > : boost::mpl::int_<NORMAL_LOCK>
{
};

template<>
struct  LockableStrategy<CAnyTimedLockable > : boost::mpl::int_<TIMED_LOCK>
{
};

template<>
struct  LockableStrategy<CAnyNullLockable > : boost::mpl::int_<NULL_LOCK>
{
};

#endif