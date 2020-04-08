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
#ifndef __ANBASIN_HYPER_DATA_THREAD_LOCAL_H__
#define __ANBASIN_HYPER_DATA_THREAD_LOCAL_H__

// macro hanlding for threadlocal variables
#ifdef __GNUC__
  #define MX_TREAD_LOCAL __thread
#elif __STDC_VERSION__ >= 201112L
  #define  MX_TREAD_LOCAL _Thread_local
#elif defined(_MSC_VER)
  #define MX_TREAD_LOCAL __declspec(thread)
#endif

#ifndef MX_TREAD_LOCAL
#message("Warning: Threadlocal is not enabled");
#endif

//
namespace AnyBasin
{
	/*!
	 * \brief A threadlocal store to store threadlocal variables.
	 *  Will return a thread local singleton of type T
	 * \tparam T the type we like to store
	 */
	template<typename T>
	class HyperThreadLocalStore {
	 public:
	  /*! \return get a thread local singleton */
	  static T* Get() {
		static MX_TREAD_LOCAL T* ptr = nullptr;
		if (ptr == nullptr) {
		  ptr = new T();
		  Singleton()->RegisterDelete(ptr);
		}
		return ptr;
	  }

	 private:
	  /*! \brief constructor */
	  HyperThreadLocalStore() {}
	  /*! \brief destructor */
	  ~HyperThreadLocalStore() {
		for (size_t i = 0; i < data_.size(); ++i) {
		  delete data_[i];
		}
	  }
	  /*! \return singleton of the store */
	  static HyperThreadLocalStore<T> *Singleton() {
		static HyperThreadLocalStore<T> inst;
		return &inst;
	  }
	  /*!
	   * \brief register str for internal deletion
	   * \param str the string pointer
	   */
	  void RegisterDelete(T *str) {
	#if DMLC_ENABLE_STD_THREAD
		std::unique_lock<std::mutex> lock(mutex_);
		data_.push_back(str);
		lock.unlock();
	#else
		data_.push_back(str);
	#endif
	  }

	#if DMLC_ENABLE_STD_THREAD
	  /*! \brief internal mutex */
	  std::mutex mutex_;
	#endif
	  /*!\brief internal data */
	  std::vector<T*> data_;
	};
}

#endif