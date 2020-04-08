
#ifndef JTC_WORKTHREAD_H
#define JTC_WORKTHREAD_H

#include "thread.h"
#include "threadGroup.h"
#include "sync.h"
#include "synct.h"
#include "runnable.h"
#include "tss.h"
#include "rwmutex.h"

#include "handlei.h"
#include "monitori.h"
#include "any/base/anystl.h"

#include "task.h"
#include "threadpool.h"

// forward class
class CAnyThreadPool;

/*!
*  a sub class of JTCThread
* suspend and stop method will be implemented in thread.cpp
*/
class CAnyWorkerThread : public JTCThread 
{
public:
	//
	//
	//
	/*!
	*
	**/
	CAnyWorkerThread(CAnyThreadPool* pool);
	
	/*!
	*
	**/
	virtual ~CAnyWorkerThread();
	
public:
	/*!
	* thread run run ExecuteTask() method of JTCThreadPool repeatedly
	*/
	virtual void run();

	/*!
	* run died unexpectedly   
	*/
	void died_unexpectedly();

	/*!
	* factory of worker thread call start method of thread
	*/
	static CAnyWorkerThread* CreateAndAttachThread(CAnyThreadPool* pool);

private:
	int m_id;
	CAnyThreadPool* m_pool;
};
#endif