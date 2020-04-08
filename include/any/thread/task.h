
#ifndef JTC_TASK_H
#define JTC_TASK_H

//
#include "any/base/anystl.h"

//
#include "thread.h"
#include "threadGroup.h"
#include "sync.h"
#include "synct.h"
#include "runnable.h"
#include "tss.h"
#include "rwmutex.h"
#include "lockstrategies.h"

// boost
#include "boost/signals2.hpp"
#include "boost/type_traits/function_traits.hpp"
using namespace boost::signals2;

// forward class
class CAnyThreadPool;

/*!
* need to overide the run function inherited form JTCRunnable
**/
class ANYTHREAD_CLASS CAnyTask : public JTCRunnable
{	
public:
	/*!
	*
	**/
	enum TaskState
	{
		Task_Waiting=0,
		Task_Executing,
		Task_Ending,
	};

	/*!
	*
	**/
	enum TaskType
	{
		Normal=0,
		CPU_Cost,
		Memory_Cost,
	};

public:
	//
	//
	//
	/*!
	*
	**/
	CAnyTask(TaskType type=Normal)
	{
		m_prior=0;
		m_taskid=0;
		m_state=Task_Waiting;
		m_threadId=0;
		m_pool=0;
		m_taskgroup=0;
		m_type=type;
	}

	/*!
	*
	**/
	~CAnyTask()
	{
	}
	
public:
	//
	// task property
	//
	/*!
	*
	**/
	void SetPriority(int prior)
	{
		m_prior=prior;
	}

	/*!
	*
	**/
	void SetId(int id)
	{
		m_taskid=id;
	}

	/*!
	*
	**/
	void SetType(TaskType type)
	{
		m_type = type;
	}

	/*!
	*
	**/
	void SetState(TaskState ts)
	{
		m_state  = ts;
	}

	/*!
	*
	**/
	void SetGroup(int groupid)
	{
		m_taskgroup=groupid;
	}

	/*!
	*
	**/
	void SetRWMutex(JTCRWMutex* mutex)
	{
		m_rwmutex=mutex;
	}

	/*!
	*
	**/
	void SetNormalMutex(JTCRecursiveMutex* mutex)
	{
		m_normalmutex=mutex;
	}

	/*!
	*
	**/
	void SetTimedMutex(JTCTimedMutex* mutex)
	{
		m_timedmutex=mutex;
	}
	
	//
	// thread-specific
	//
	/*!
	*
	**/
	void AttachToThread(JTCThreadId threadid)
	{
		m_threadId=threadid;
	}
	
	/*!
	*
	**/
	void AttachToPool(CAnyThreadPool* pool)
	{
		m_pool=pool;
	}
	
	/*!
	*
	**/
	virtual void DoExecuteTask() = 0;

public:
	//
	int m_prior;
	int m_taskid;
	TaskState m_state;
	TaskType m_type;
	JTCThreadId m_threadId;
	CAnyThreadPool* m_pool;

	int m_taskgroup;
	JTCRWMutex* m_rwmutex;//for internal synchronize 
	JTCRecursiveMutex* m_normalmutex;//for internal synchronize 
	JTCTimedMutex* m_timedmutex;//for internal synchronize 
};

/*!
*
**/
template<typename Signature, typename Lockable = CAnyReadWriteLockable>
class CAnySimpleTask : public CAnyTask
{
	typedef boost::function<Signature> ThreadFunction;
	typedef typename boost::function_traits<Signature>::arg1_type ParameterType;

public:
	/*!
	*
	**/
	CAnySimpleTask() : CAnyTask(), m_timeout(1000)
	{
	}
	CAnySimpleTask(ParameterType parameter) : CAnyTask(), m_timeout(1000), m_parameter(parameter)
	{
	}
public:
	/*!
	*
	**/
	void run()
	{
		void *mutex = 0;
		if(LockableStrategy<Lockable>::value == RWREAD_LOCK ||
			LockableStrategy<Lockable>::value == RWWRITE_LOCK)
		{
			mutex = m_rwmutex;
		}
		else if(LockableStrategy<Lockable>::value == NORMAL_LOCK)
		{
			mutex = m_normalmutex;
		}
		else if(LockableStrategy<Lockable>::value == TIMED_LOCK)
		{
			mutex = m_timedmutex;
		}

		CAnyScopeGuard<Lockable> guard(mutex,m_timeout);
		DoExecuteTask();
	}
	virtual void DoExecuteTask()
	{
		m_function(m_parameter);
	}

public:
	ThreadFunction m_function;
	long m_timeout; //used by timedlock; milisecond
	ParameterType m_parameter;
};

/*!
* task(signal) -> slot <- task(signal)
* 1 : n : 1
**/
template<typename Signature, typename Lockable = CAnyReadWriteLockable, typename Combiner = optional_last_value<typename boost::function_traits<Signature>::result_type> >
class CAnySignalTask : public CAnyTask
{
public:
	//functor should return void and with no parameters
	typedef typename signal<Signature, Combiner> signal_t; 
	typedef typename signal_t::slot_type slot_t;
	typedef typename signal_t::group_type group_t;

public:
	/*!
	*
	**/
	CAnySignalTask() : CAnyTask(),m_guard(0),m_timeout(1000)
	{
	}

	//
	// template run function
	//
	/*!
	* template function
	**/
	void run()
	{
		void *mutex = 0;
		if(LockableStrategy<Lockable>::value == RWREAD_LOCK ||
			LockableStrategy<Lockable>::value == RWWRITE_LOCK)
		{
			mutex = m_rwmutex;
		}
		else if(LockableStrategy<Lockable>::value == NORMAL_LOCK)
		{
			mutex = m_normalmutex;
		}
		else if(LockableStrategy<Lockable>::value == TIMED_LOCK)
		{
			mutex = m_timedmutex;
		}

		CAnyScopeGuard<Lockable> guard(mutex,m_timeout);
		DoExecuteTask();
		m_sig();

	}

	//
	// observable-observer
	//
	/*!
	* boost signal2's interface to register slot(functor)
	*/
	connection Connect(const slot_t& s/*,connect_position p=at_back*/)
	{
		return m_sig.connect(s);
	}

	/*!
	* boost signal2's interface to register slot(functor) with group
	*/
	connection Connect(const group_t& g,const slot_t& s/*,connect_position p=at_back*/)
	{
		return m_sig.connect(g,s);
	}

	/*!
	*
	**/
	void SetTimeout(long timeout)
	{
		m_timeout=timeout;
	}

protected:
	//boost signal2 interface
	signal_t m_sig; 
	//LOCK_STRATEGY_TYPE m_lockstrategy;
	JTCSynchronized* m_guard;

	long m_timeout; //used by timedlock; milisecond
};

#endif