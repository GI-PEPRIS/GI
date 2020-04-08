/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYBASIN_HYPER_DATA_CONCURRENT_BLOCKING_QUEUE_H__
#define __ANYBASIN_HYPER_DATA_CONCURRENT_BLOCKING_QUEUE_H__

//
#include "any/base/anystl.h"

//
#ifdef USE_CXX11_FEATURE
#else
#include "any/thread/jtc.h"
#endif

//
namespace AnyBasin
{
	/*! \brief type of concurrent queue */
	enum ConcurrentQueueType 
	{
		/*! \brief FIFO queue */
		kFIFO,
		/*! \brief queue with priority */
		kPriority
	};

	/*!
	 * \brief Cocurrent blocking queue.
	 */
	template <typename T, ConcurrentQueueType type = ConcurrentQueueType::kFIFO>
	class HyperConcurrentBlockingQueue
	{
	 public:
	  HyperConcurrentBlockingQueue();
#ifdef USE_CXX11_FEATURE
	  ~HyperConcurrentBlockingQueue() = default;
#else
	  ~HyperConcurrentBlockingQueue(){}
#endif
	  /*!
	   * \brief Push element into the queue.
	   * \param e Element to push into.
	   * \param priority the priority of the element, only used for priority queue.
	   *            The higher the priority is, the better.
	   * \tparam E the element type
	   *
	   * It will copy or move the element into the queue, depending on the type of
	   * the parameter.
	   */
	  template <typename E>
	  void Push(E&& e, int priority = 0);
	  /*!
	   * \brief Pop element from the queue.
	   * \param rv Element popped.
	   * \return On false, the queue is exiting.
	   *
	   * The element will be copied or moved into the object passed in.
	   */
	  bool Pop(T* rv);
	  /*!
	   * \brief Signal the queue for destruction.
	   *
	   * After calling this method, all blocking pop call to the queue will return
	   * false.
	   */
	  void SignalForKill();
	  /*!
	   * \brief Get the size of the queue.
	   * \return The size of the queue.
	   */
	  size_t Size();

	 private:
	  struct Entry {
		T data;
		int priority;
		inline bool operator<(const Entry &b) const {
		  return priority < b.priority;
		}
	  };

#ifdef USE_CXX11_FEATURE
	  std::mutex mutex_;
	  std::condition_variable cv_;
	  std::atomic<bool> exit_now_;
#else
	  JTCMutex mutex_;
	  JTCCond cv_;
	  volatile bool exit_now_;
#endif


	  int nwait_consumer_;
	  // a priority queue
	  std::vector<Entry> priority_queue_;
	  // a FIFO queue
	  std::queue<T> fifo_queue_;
	};

	template <typename T, ConcurrentQueueType type>
	HyperConcurrentBlockingQueue<T, type>::HyperConcurrentBlockingQueue():exit_now_(false),nwait_consumer_(0) {}

	template <typename T, ConcurrentQueueType type>
	template <typename E>
	void HyperConcurrentBlockingQueue<T, type>::Push(E&& e, int priority) {
		static_assert(std::is_same<typename std::remove_cv<
			typename std::remove_reference<E>::type>::type,
			T>::value,
			"Types must match.");
		bool notify;
		{
#ifdef USE_CXX11_FEATURE
			std::lock_guard<std::mutex> lock{mutex_};
#else
			JTCSyncT<JTCMutex> lock(mutex_);
#endif
			if (type == ConcurrentQueueType::kFIFO) {
				fifo_queue_.emplace(std::forward<E>(e));
				notify = nwait_consumer_ != 0;
			} else {
				Entry entry;
				entry.data = std::move(e);
				entry.priority = priority;
				priority_queue_.push_back(std::move(entry));
				std::push_heap(priority_queue_.begin(), priority_queue_.end());
				notify = nwait_consumer_ != 0;
			}
		}

#ifdef USE_CXX11_FEATURE
		if (notify) cv_.notify_one();
#else
		if (notify) cv_.signal();
#endif
	}

template <typename T, ConcurrentQueueType type>
bool HyperConcurrentBlockingQueue<T, type>::Pop(T* rv) 
{
#ifdef USE_CXX11_FEATURE
	std::unique_lock<std::mutex> lock{mutex_};
#else
	JTCSyncT<JTCMutex> lock(mutex_);
#endif

	if (type == ConcurrentQueueType::kFIFO) {
		++nwait_consumer_;

#ifdef USE_CXX11_FEATURE
		cv_.wait(lock, [this] {
			return !fifo_queue_.empty() || exit_now_.load();
		});
#else
#endif
		--nwait_consumer_;

#ifdef USE_CXX11_FEATURE
		if (!exit_now_.load()) {
#else
		if (!exit_now_) {
#endif
			*rv = std::move(fifo_queue_.front());
			fifo_queue_.pop();
			return true;
		} else {
			return false;
		}
	} else {
		++nwait_consumer_;

#ifdef USE_CXX11_FEATURE
		cv_.wait(lock, [this] {
			return !priority_queue_.empty() || exit_now_.load();
		});
#else
#endif

		--nwait_consumer_;
#ifdef USE_CXX11_FEATURE
		if (!exit_now_.load()) {
#else
		if (!exit_now_) {
#endif
			std::pop_heap(priority_queue_.begin(), priority_queue_.end());
			*rv = std::move(priority_queue_.back().data);
			priority_queue_.pop_back();
			return true;
		} else {
			return false;
		}
	}
}

template <typename T, ConcurrentQueueType type>
void HyperConcurrentBlockingQueue<T, type>::SignalForKill() 
{
#ifdef USE_CXX11_FEATURE
	{
		std::lock_guard<std::mutex> lock{mutex_};
		exit_now_.store(true);
	}
	cv_.notify_all();
#else
	{
		JTCSyncT<JTCMutex> lock(mutex_);
		exit_now_.store(true);
	}
	cv_.broadcast();
#endif
}

template <typename T, ConcurrentQueueType type>
size_t HyperConcurrentBlockingQueue<T, type>::Size() 
{
#ifdef USE_CXX11_FEATURE
	std::lock_guard<std::mutex> lock{mutex_};
#else
	JTCSyncT<JTCMutex> lock(mutex_);
#endif

	if (type == ConcurrentQueueType::kFIFO) {
		return fifo_queue_.size();
	} else {
		return priority_queue_.size();
	}
}
}
#endif