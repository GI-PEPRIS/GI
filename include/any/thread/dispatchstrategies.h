
#ifndef JTC_DISPATCHSTRATEGY_H
#define JTC_DISPATCHSTRATEGY_H

#include "threadpool.h"

/*!
* CRTP pattern
**/
template<class Derived>
class ANYTHREAD_CLASS CAnyThreadScheduler : public CAnyThreadPool
{
public:
	CAnyThreadScheduler(int worker_num) : CAnyThreadPool(worker_num)
	{
	}

	~CAnyThreadScheduler()
	{
	}

	/*!
	* main thread's run method invoked by start()
	**/
	void run()
	{
		JTCSyncT<JTCRecursiveMutex> guard(m_internal);
		while(true)
		{
			//wait for task arrive wait will release lock
			m_task_or_terminate_workers_event.wait(m_internal);
		
			//exit leader thread when destroy pool
			if(m_terminate_all_workers)
			{
				break;
			}

			//simple strategy: when there are fewer worker thread than the count of tasks and the count of threads doesn't reach the max, then increase it.
			static_cast<Derived*>(this)->DispatchStrategy();
		
			m_executetask_event.signal();
		
			//for more complex strategy,write new class inherit from thread pool.
		}		
	}

	/*!
	* dispatch strategy virtual
	**/
	virtual void DispatchStrategy()
	{
		if(m_active_worker_count==m_worker_count)
		{
			m_leaderaccept_event.broadcast();
		}
	}
};

/*!
*
**/
class ANYTHREAD_CLASS CAnyCPUScheduler : public CAnyThreadScheduler<CAnyCPUScheduler>
{
public:
	enum PoolState
	{
		Normal,
		CPUBusy,
		MemoryBusy,
	};

public:
	CAnyCPUScheduler(int worker_num) : CAnyThreadScheduler<CAnyCPUScheduler>(worker_num)
	{
	}

	~CAnyCPUScheduler()
	{
	}

	static CAnyCPUScheduler* GetInstance()
	{
		static CAnyCPUScheduler *s_cpuScheduler = 0;

		if(s_cpuScheduler==0)
		{
			s_cpuScheduler=new CAnyCPUScheduler(10);
			s_cpuScheduler->start();
		}

		return s_cpuScheduler;
	}

	static bool ReleaseInstance()
	{
		if(GetInstance()!=0)
		{
			GetInstance()->DestroyPool();
		}
		return true;
	}

	/*!
	*
	**/
	void DispatchStrategy()
	{
		//check whether cpubusy task is finished
		if(m_poolstate==CPUBusy)
		{
			bool IsStillBusy=false;
			std::map<JTCThreadId,int>::iterator it = m_currentThreadToTaskMap.begin();
			for(; it != m_currentThreadToTaskMap.end(); it++)
			{
				int id=it->second;
				if(m_taskMap[id]->m_type==CAnyTask::CPU_Cost)
				{
					//m_poolstate=CPUBusy;
					IsStillBusy=true;
					break;
				}
			}

			if(!IsStillBusy)
			{
				m_poolstate=Normal;
				for(int i=0;i<m_cpuCostTaskVec.size();i++)
				{
					m_queue.push(m_cpuCostTaskVec[i]);
				}
				m_cpuCostTaskVec.clear();
			}
		}

		if(m_active_worker_count==m_worker_count)
		{
			m_leaderaccept_event.broadcast();
			return;
		}

		CAnyTask*  task;	
		int c=0;
		switch(m_poolstate)
		{
		case Normal:
			if(m_queue.size()==0)
			{
				m_leaderaccept_event.signal();
				break;
			}

			task=m_queue.top();
			if(task->m_type==CAnyTask::CPU_Cost)
			{
				m_poolstate=CPUBusy;
			}
			break;
		case CPUBusy:
			if(m_queue.size()==0)
			{
				m_leaderaccept_event.signal();
				break;
			}

			task=m_queue.top();
			while(task->m_type==CAnyTask::CPU_Cost)
			{
				m_cpuCostTaskVec.push_back(task);
				m_queue.pop();

				if(m_queue.size()==0)
				{
					m_leaderaccept_event.signal();
					break;
				}
				task=m_queue.top();
			}
			break;
		default:
			break;
		}	
	}

private:
	PoolState m_poolstate;
	std::vector<CAnyTask*> m_cpuCostTaskVec;
};
#endif