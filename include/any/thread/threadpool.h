#ifndef JTC_THREADPOOL_H
#define JTC_THREADPOOL_H

#include "anythread.h"

#include "thread.h"
#include "threadGroup.h"
#include "sync.h"
#include "synct.h"
#include "runnable.h"
#include "tss.h"
#include "rwmutex.h"

#include "handlei.h"
#include "monitori.h"

#include "task.h"

#include "any/base/anystl.h"
#include "boost/bind.hpp"
#include "boost/function.hpp"

class CAnyWorkerThread;

class ANYTHREAD_CLASS CAnyThreadPool : public JTCThread
{
public:
	/*!
	*
	**/
	enum Priority
	{
		Prior_Lowest=0,
		Prior_Low,
		Prior_Middle,
		Prior_High,
		Prior_Highest,
	};

	/*!
	*
	**/
	enum MutexType
	{
		ReadWriteLock=0,// correspond to JTCRWMutex
		NormalLock, // correspond to JTCMutex 
		TimedLock,
	};

public:
	/*!
	* constructor
	**/
	CAnyThreadPool(int worker_num);

	/*!
	*
	**/
	virtual ~CAnyThreadPool();

public:
	//
	// inherited from JTCThread
	//
	/*!
	* main thread's run method invoked by start()
	**/
	virtual void run(){}

	//
	//
	//
	/*!
	*add a task to thread pool 
	*@prior set the priority of the task
	*return the taskid for task operation in future
	**/
	int AddTask(CAnyTask* t,Priority prior=Prior_Low,int groupid=0,int mutextype=ReadWriteLock);

	/*!
	* get the task state   
	**/
	int GetTaskState(int taskId);

	/*!
	* remove task from waiting queue    
	**/
	bool RemoveTaskInQueue(int taskId);

	/*!
	* end and remove task even if the task is running by thread
	**/
	bool EndTask(int taskId);

	/*!
	* suspend task and thread if the task is running by thread 
	**/
	bool SuspendTask(int taskId);

	/*!
	* suspend task and thread if the task is running by thread  
	**/
	bool ResumeTask(int taskId);

	/*!
	* join task  and thread if the task is running by thread   
	**/
	bool JoinTask(int taskId, long timeout=0);

	/*!
	* set the priority of the task. It often adjust the task order in waiting queue,
	* but will create a new thread to execute the task immediately when set to Highest
	**/
	bool SetTaskPriority(int taskId,Priority prior);
	
	/*!
	* execute the task in the waiting queue, with wait-notify framework
	* this function is called by worker thread repeatedly. 
	**/
	bool ExecuteTask(JTCThreadId threadId);

	//
	//
	//
	/*!
	* suspend the target thread    
	**/
	bool SuspendThread(JTCThreadId threadId);

	/*!
	* suspend the target thread      
	**/
	bool ResumeThread(JTCThreadId threadId);

	/*!
	* join the target thread 
	**/
	bool JoinThread(JTCThreadId threadId);

	/*!
	* get the state of target thread 
	**/
	int GetThreadState(JTCThreadId threadId);

	/*!
	* waiting for all the threads in pool complete, this means pool is destroyed
	* Join a pool seems make no sense. if you want pool finish all the job, 
	* just use WaitPoolIdle()
	**/
	bool JoinPool();

	/*!
	* waiting for all the threads in pool are active(no task is running)
	**/
	bool WaitPoolIdle(int groupid);	// -1 means all or queue empty
	bool WaitPoolIdle();

	/*!
	* suspend the pool 
	**/
	bool SuspendPool();

	/*!
	* suspend the pool with timeout milliseconds 
	**/
	bool SleepPool(long timeout);

	/*!
	* suspend the pool with timeout milliseconds  
	**/
	bool ResumePool();

	/*!
	* destroy the pool when the current tasks are finished  
	**/
	bool DestroyPool();
	bool StopPool();

	/*!
	* destroy the pool now     
	**/
	bool DestroyPoolNow();

	/*!
	* worker destructed   
	**/
	bool WorkerThreadDestructed(CAnyWorkerThread* worker);

	/*!
	* worker die unexpectedly     
	**/
	bool WorkerDieUnexpectedly(CAnyWorkerThread* worker);

	/*!
	* resize the pool  
	**/
	bool Resize(int num);

	/*!
	* clear the waiting queue 
	**/
	bool ClearQueue();

	/*!
	* the number of active thread 
	**/
	int GetActiveThreadCount();

	/*!
	* the number of thread in pool   
	**/
	int GetThreadCount();

	/*!
	* the number of tasks in waiting queue
	**/
	int GetTaskInQueueCount();
	
	/*!
	*get task by id     
	**/
	CAnyTask* GetTask(int taskID);

public:
	struct cmp
	{
		bool operator()(CAnyTask* a,CAnyTask* b)
		{
			if(a->m_prior == b->m_prior)
			{
				return a->m_taskid > b->m_taskid;
			}
			else
			{
				return a->m_prior < b->m_prior;
			}
		}
	};
	
public:
	std::priority_queue<CAnyTask*,std::vector<CAnyTask*>,cmp> m_queue; //waiting queue
	
	std::map<JTCThreadId,int> m_currentThreadToTaskMap; //this map contain mapping of thread and its current task to be excuted. 
	std::map<int,CAnyTask*> m_taskMap;     //this map contain task and its key id. you can use id to search for a specified task
	std::map<JTCThreadId,CAnyWorkerThread*> m_workerThreadMap;  // this map contains worker threads and modified by Resize method 
	std::map<int,JTCRWMutex*> m_rwmutexMap;// task's read write lock
	std::map<int,JTCRecursiveMutex*> m_normalmutexMap; // task's normal lock
	std::map<int,JTCTimedMutex*> m_timedmutexMap; // task's normal lock
	
	//std::set<int> m_executedTaskIdSet; //record the excuted taskid to avoid repeatedly execution of task. Becasue priority_queue doesn't support delete of non-top element
	//std::vector<CAnyWorkerThread*> m_terminated_workers;

	JTCRecursiveMutex m_internal;//for internal synchronize 
	JTCRecursiveMutex m_taskidsetMutex;//for internal synchronize 
	
	//CV(Conditional Variable) Order: client's AddTask() signal mainthread's run()--- main thread's run() signal worker thread's ExcuteTask() 
	//or client's AddTask() when queue is empty  ----worker thread's ExcuteTask() signal  client's AddTask().
	JTCCond m_task_or_terminate_workers_event; //signal when task arrives or terminate pool. and pool's main thread wait for this cv in run()
	JTCCond m_workeridle_or_terminated_event; //signal when worker thread is idle or is to be terminated. and it will wait for all worker thread idle when calling DestroyPool()
	JTCCond m_taskfinish_event;   // signal when task is successfully executed by a worker thread and it's used by join task to wait for this cv within a timeout.
	JTCCond m_leaderaccept_event; //signal when a worker thread adopt this task or m_queue is empty or other stategy.
	JTCCond m_executetask_event;  //signal when passed the run's dispatch strategy and worker thread is waiting for this cv in ExecuteTask method.
	
	volatile int m_taskidkey; // global task id key.
	volatile int m_worker_count; //current worker count
	volatile int m_target_worker_count;//the target count set by resize() method
	volatile int m_max_worker_count;//the max count set by resize() method       No Use Now
	volatile int m_active_worker_count;  // busy worker count
	volatile bool m_terminate_all_workers;
};
#endif