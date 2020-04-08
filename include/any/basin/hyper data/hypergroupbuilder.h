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
#ifndef __ANYBASIN_HYPER_DATA_GROUP_BUILDER_H__
#define __ANYBASIN_HYPER_DATA_GROUP_BUILDER_H__

namespace AnyBasin
{
	/*!
	 * \brief multi-thread version of group builder
	 * \tparam ValueType type of entries in the sparse matrix
	 * \tparam SizeType type of the index range holder
	 */
	template<typename ValueType, typename SizeType = unsigned long>
	struct HyperParallelGroupBuilder 
	{
	 public:
	  // parallel group builder of data
	  HyperParallelGroupBuilder(std::vector<SizeType> *p_rptr,
						   std::vector<ValueType> *p_data)
		  : rptr(*p_rptr), data(*p_data), thread_rptr(tmp_thread_rptr) {
	  }
	  HyperParallelGroupBuilder(std::vector<SizeType> *p_rptr,
						   std::vector<ValueType> *p_data,
						   std::vector< std::vector<SizeType> > *p_thread_rptr)
		  : rptr(*p_rptr), data(*p_data), thread_rptr(*p_thread_rptr) {
	  }

	 public:
	  /*!
	   * \brief step 1: initialize the helper, with hint of number keys
	   *                and thread used in the construction
	   * \param nkeys number of keys in the matrix, can be smaller than expected
	   * \param nthread number of thread that will be used in construction
	   */
	  inline void InitBudget(size_t nkeys, int nthread) {
		thread_rptr.resize(nthread);
		for (size_t i = 0;  i < thread_rptr.size(); ++i) {
		  thread_rptr[i].resize(nkeys);
		  std::fill(thread_rptr[i].begin(), thread_rptr[i].end(), 0);
		}
	  }
	  /*!
	   * \brief step 2: add budget to each key
	   * \param key the key
	   * \param threadid the id of thread that calls this function
	   * \param nelem number of element budget add to this row
	   */
	  inline void AddBudget(size_t key, int threadid, SizeType nelem = 1) {
		std::vector<SizeType> &trptr = thread_rptr[threadid];
		if (trptr.size() < key + 1) {
		  trptr.resize(key + 1, 0);
		}
		trptr[key] += nelem;
	  }
	  /*! \brief step 3: initialize the necessary storage */
	  inline void InitStorage(void) {
		// set rptr to correct size
		for (size_t tid = 0; tid < thread_rptr.size(); ++tid) {
		  if (rptr.size() <= thread_rptr[tid].size()) {
			rptr.resize(thread_rptr[tid].size() + 1);
		  }
		}
		// initialize rptr to be beginning of each segment
		size_t start = 0;
		for (size_t i = 0; i + 1 < rptr.size(); ++i) {
		  for (size_t tid = 0; tid < thread_rptr.size(); ++tid) {
			std::vector<SizeType> &trptr = thread_rptr[tid];
			if (i < trptr.size()) {
			  size_t ncnt = trptr[i];
			  trptr[i] = start;
			  start += ncnt;
			}
		  }
		  rptr[i + 1] = start;
		}
		data.resize(start);
	  }
	  /*!
	   * \brief step 4: add data to the allocated space,
	   *   the calls to this function should be exactly match previous call to AddBudget
	   *
	   * \param key the key of group.
	   * \param value The value to be pushed to the group.
	   * \param threadid the id of thread that calls this function
	   */
	  inline void Push(size_t key, ValueType value, int threadid) {
		SizeType &rp = thread_rptr[threadid][key];
		data[rp++] = value;
	  }

	 private:
	  /*! \brief pointer to the beginning and end of each continuous key */
	  std::vector<SizeType> &rptr;
	  /*! \brief index of nonzero entries in each row */
	  std::vector<ValueType> &data;
	  /*! \brief thread local data structure */
	  std::vector<std::vector<SizeType> > &thread_rptr;
	  /*! \brief local temp thread ptr, use this if not specified by the constructor */
	  std::vector<std::vector<SizeType> > tmp_thread_rptr;
	};
}
#endif