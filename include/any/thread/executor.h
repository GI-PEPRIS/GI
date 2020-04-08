#ifndef __ANYTHREAD_EXECUTOR_H__
#define __ANYTHREAD_EXECUTOR_H__

// refer to EXPORT & IMPORT
#include "anythread.h"

// parallel task
#include "task.h"

/*!
*
**/
template<typename Children>
class ParallelExecutor 
{
	/*!
	* parallel task
	**/
	template<typename Executor, typename Signature = void()>
	class CAnyParallelTask : public CAnySignalTask<Signature>
	{
	public:
		CAnyParallelTask(Executor *executor, long start, long end) : CAnySignalTask(), m_executor(executor), m_start(start), m_end(end)
		{
		}

		~CAnyParallelTask()
		{
		}

	public:
		/*!
		*
		**/
		void DoExecuteTask()
		{
			m_executor->DoWork(m_start, m_end);
		}

	private:
		// seqential\parallel\group etc executor
		Executor *m_executor;
		//
		long m_start;
		//
		long m_end;
	};

	typedef CAnyParallelTask<ParallelExecutor, void()> Task;
	typedef CAnySignalTask<void()>::slot_t slot_t;

public:
	/*!
	*
	**/
	ParallelExecutor() : m_iterations(ANY_NAN), m_batches(ANY_NAN)
	{
	}

	/*!
	*
	**/
	~ParallelExecutor()
	{
	}

public:
	//
	//
	//
	/*!
	*
	**/
	void DoPrepare()
	{
		static_cast<Children *>(this)->DoPrepare();
	}

	/*!
	*
	**/
	void DoWork(long start, long end)
	{
		static_cast<Children *>(this)->DoWork(start, end);
	}

	/*!
	*
	**/
	void DoFinish()
	{
		static_cast<Children *>(this)->DoFinish();
	}

	/*!
	*
	**/
	void Execute(slot_t s)
	{	
		// prepare
		DoPrepare();

		// work
		CAnyCPUScheduler* scheduler =CAnyCPUScheduler::GetInstance();
		Task **tasks=new Task*[m_batches];
		int start = 0;
		int stop = 0;
		int i = 0;
		for(; i < m_batches; i++)
		{
			DoAllocateTaskExtent(start, stop, i, m_batches);
			tasks[i] = new Task(this, start, stop);
			tasks[i]->Connect(1, s);
			scheduler->AddTask(tasks[i]);
		}
		delete[] tasks;

		// finish
		DoFinish();
	}

private:
	/*!
	*
	**/
	void DoAllocateTaskExtent(int& start, int &stop, int id, int taskCount)
	{
		int size = m_iterations/taskCount;
		start=id*size;
		stop=(id+1)*size;
		if(stop>m_iterations)
		{
			stop=m_iterations;
		}
	}

protected:
	// iterations
	long m_iterations;
	// batches
	short m_batches;
};

#endif

