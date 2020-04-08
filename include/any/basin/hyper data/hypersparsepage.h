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
#ifndef __ANYBASIN_HYPER_DATA_SPARSE_PAGE_H__
#define __ANYBASIN_HYPER_DATA_SPARSE_PAGE_H__

//
#include "hyperdata.h"
#include "hyperconcurrency.h"

//
namespace AnyBasin
{
	/*!
	 * \brief in-memory storage unit of sparse batch
	 */
	class HyperSparsePage 
	{
	public:
		/*! \brief Format of the sparse page. */
		class Format;
		/*! \brief Writer to write the sparse page to files. */
		class Writer;

		/*! \brief minimum index of all index, used as hint for compression. */
		unsigned int m_min_index;
		/*! \brief offset of the segments */
		std::vector<unsigned long> m_offset;
		/*! \brief the data of the segments */
		std::vector<HyperSparseBatch::Entry> m_data;

		/*! \brief constructor */
		HyperSparsePage() 
		{
			this->Clear();
		}
		/*! \return number of instance in the page */
		inline size_t Size() const 
		{
			return m_offset.size() - 1;
		}
		/*! \return estimation of memory cost of this page */
		inline size_t MemCostBytes(void) const 
		{
			return m_offset.size() * sizeof(size_t) + m_data.size() * sizeof(HyperSparseBatch::Entry);
		}
		/*! \brief clear the page */
		inline void Clear(void) 
		{
			m_min_index = 0;
			m_offset.clear();
			m_offset.push_back(0);
			m_data.clear();
		}

		/*!
		* \brief Push row batch into the page
		* \param batch the row batch
		*/
		inline void Push(const HyperRowBatch &batch) 
		{
			m_data.resize(m_offset.back() + batch.m_ind_ptr[batch.m_size]);
			std::memcpy(&m_data[0] + m_offset.back(),
						batch.m_data_ptr + batch.m_ind_ptr[0],
						sizeof(HyperSparseBatch::Entry) * batch.m_ind_ptr[batch.m_size]);
			size_t top = m_offset.back();
			size_t begin = m_offset.size();
			m_offset.resize(m_offset.size() + batch.m_size);
			for (size_t i = 0; i < batch.m_size; ++i) 
			{
				m_offset[i + begin] = top + batch.m_ind_ptr[i + 1] - batch.m_ind_ptr[0];
			}
		}
		/*!
		* \brief Push row block into the page.
		* \param batch the row batch.
		*/
		inline void Push(const HyperRowBlock<unsigned int>& batch) 
		{
			m_data.reserve(m_data.size() + batch.m_offset[batch.m_size] - batch.m_offset[0]);
			m_offset.reserve(m_offset.size() + batch.m_size);
			assert(batch.m_index != nullptr);
			for (size_t i = 0; i < batch.m_size; ++i) 
			{
				m_offset.push_back(m_offset.back() + batch.m_offset[i + 1] - batch.m_offset[i]);
			}
			for (size_t i = batch.m_offset[0]; i < batch.m_offset[batch.m_size]; ++i) 
			{
				unsigned int index = batch.m_index[i];
				double fvalue = batch.m_value == nullptr ? 1.0f : batch.m_value[i];
				m_data.push_back(HyperSparseBatch::Entry(index, fvalue));
			}
			assert(m_offset.back() == m_data.size());
		}
		/*!
		* \brief Push a sparse page
		* \param batch the row page
		*/
		inline void Push(const HyperSparsePage &batch) 
		{
			size_t top = m_offset.back();
			m_data.resize(top + batch.m_data.size());
			std::memcpy(&m_data[0] + top,
						&batch.m_data[0],
						sizeof(HyperSparseBatch::Entry) * batch.m_data.size());
			size_t begin = m_offset.size();
			m_offset.resize(begin + batch.Size());
			for (size_t i = 0; i < batch.Size(); ++i) 
			{
				m_offset[i + begin] = top + batch.m_offset[i + 1];
			}
		}
		/*!
		* \brief Push one instance into page
		*  \param row an instance row
		*/
		inline void Push(const HyperSparseBatch::Inst &inst) 
		{
			m_offset.push_back(m_offset.back() + inst.m_length);
			size_t begin = m_data.size();
			m_data.resize(begin + inst.m_length);
			if (inst.m_length != 0) 
			{
				std::memcpy(&m_data[0] + begin, inst.m_data,
							sizeof(HyperSparseBatch::Entry) * inst.m_length);
			}
		}
		/*!
		* \param base_rowid base_rowid of the data
		* \return row batch representation of the page
		*/
		inline HyperRowBatch GetRowBatch(size_t base_rowid) const 
		{
			HyperRowBatch out;
			out.m_base_rowid  = base_rowid;
			out.m_ind_ptr = m_offset.size() ? &m_offset[0] : 0;//dmlc::BeginPtr(offset);
			out.m_data_ptr = m_data.size() ? &m_data[0] : 0; //dmlc::BeginPtr(data);
			out.m_size = m_offset.size() - 1;
			return out;
		}
	};

	/*!
	 * \brief Format specification of SparsePage.
	 */
	class HyperSparsePage::Format 
	{
	 public:
	  /*! \brief virtual destructor */
	  virtual ~Format() {}
	  /*!
	   * \brief Load all the segments into page, advance fi to end of the block.
	   * \param page The data to read page into.
	   * \param fi the input stream of the file
	   * \return true of the loading as successful, false if end of file was reached
	   */
	  virtual bool Read(HyperSparsePage* page, HyperSeekStream* fi) = 0;
	  /*!
	   * \brief read only the segments we are interested in, advance fi to end of the block.
	   * \param page The page to load the data into.
	   * \param fi the input stream of the file
	   * \param sorted_index_set sorted index of segments we are interested in
	   * \return true of the loading as successful, false if end of file was reached
	   */
	  virtual bool Read(HyperSparsePage* page,
	 					HyperSeekStream* fi,
	 					const std::vector<unsigned int>& sorted_index_set) = 0;

	  /*!
	   * \brief save the data to fo, when a page was written.
	   * \param fo output stream
	   */
	  virtual void Write(const HyperSparsePage& page, HyperStream* fo) = 0;
	  /*!
	   * \brief Create sparse page of format.
	   * \return The created format functors.
	   */
	  static Format* Create(const std::string& name){return 0;}
	  /*!
	   * \brief decide the format from cache prefix.
	   * \return pair of row format, column format type of the cache prefix.
	   */
	  static std::pair<std::string, std::string> DecideFormat(const std::string& cache_prefix){std::pair<std::string, std::string> tmp; return tmp;};
	};

	//#if DMLC_ENABLE_STD_THREAD
	/*!
	 * \brief A threaded writer to write sparse batch page to sharded files.
	 */
	class HyperSparsePage::Writer 
	{
	 public:
	  /*!
	   * \brief constructor
	   * \param name_shards name of shard files.
	   * \param format_shards format of each shard.
	   * \param extra_buffer_capacity Extra buffer capacity before block.
	   */
		 explicit Writer(
			 const std::vector<std::string>& name_shards,
			 const std::vector<std::string>& format_shards,
			 size_t extra_buffer_capacity)
			 : num_free_buffer_(extra_buffer_capacity + name_shards.size()),
			 clock_ptr_(0),
			 workers_(name_shards.size()),
			 qworkers_(name_shards.size()) {
				 assert(name_shards.size() == format_shards.size());
				 // start writer threads
				 for (size_t i = 0; i < name_shards.size(); ++i) {
					 std::string name_shard = name_shards[i];
					 std::string format_shard = format_shards[i];
					 auto* wqueue = &qworkers_[i];
#ifdef USE_CXX11_FEATURE
					 workers_[i].reset(new std::thread(
						 [this, name_shard, format_shard, wqueue] () {
							 std::unique_ptr<HyperStream> fo(
								 HyperStream::Create(name_shard.c_str(), "w"));
							 std::unique_ptr<HyperSparsePage::Format> fmt(
								 HyperSparsePage::Format::Create(format_shard));
							 fo->Write(format_shard);
							 std::shared_ptr<HyperSparsePage> page;
							 while (wqueue->Pop(&page)) {
								 if (page.get() == nullptr) break;
								 fmt->Write(*page, fo.get());
								 qrecycle_.Push(std::move(page));
							 }
							 fo.reset(nullptr);
							 //LOG(CONSOLE) << "SparsePage::Writer Finished writing to " << name_shard;
					 }));
#endif
				 }
		 }
	  /*! \brief destructor, will close the files automatically */
	  ~Writer()
	  {
#ifdef USE_CXX11_FEATURE
		  for (auto& queue : qworkers_) 
		  {
			  // use nullptr to signal termination.
			  std::shared_ptr<HyperSparsePage> sig(nullptr);
			  queue.Push(std::move(sig));
		  }
		  for (auto& thread : workers_) 
		  {
			  thread->join();
		  }
#endif
	  }
	  /*!
	   * \brief Push a write job to the writer.
	   * This function won't block,
	   * writing is done by another thread inside writer.
	   * \param page The page to be written
	   */
	  void PushWrite(std::shared_ptr<HyperSparsePage>&& page)
	  {
		  qworkers_[clock_ptr_].Push(std::move(page));
		  clock_ptr_ = (clock_ptr_ + 1) % workers_.size();
	  }

	  /*!
	   * \brief Allocate a page to store results.
	   *  This function can block when the writer is too slow and buffer pages
	   *  have not yet been recycled.
	   * \param out_page Used to store the allocated pages.
	   */
	  void Alloc(std::shared_ptr<HyperSparsePage>* out_page)
	  {
		  assert(out_page->get() == nullptr);
		  if (num_free_buffer_ != 0) 
		  {
			  out_page->reset(new HyperSparsePage());
			  --num_free_buffer_;
		  } 
		  else
		  {
			  /*CHECK*/(qrecycle_.Pop(out_page));
		  }
	  }

	 private:
	  /*! \brief number of allocated pages */
	  size_t num_free_buffer_;
	  /*! \brief clock_pointer */
	  size_t clock_ptr_;
	  /*! \brief writer threads */
#ifdef USE_CXX11_FEATURE
	  std::vector<std::unique_ptr<std::thread> > workers_;
#else
	  std::vector<std::unique_ptr<JTCThread> > workers_;
#endif
	  /*! \brief recycler queue */
	  HyperConcurrentBlockingQueue<std::shared_ptr<HyperSparsePage> > qrecycle_;
	  /*! \brief worker threads */
	  std::vector<HyperConcurrentBlockingQueue<std::shared_ptr<HyperSparsePage> > > qworkers_;
	};
	//#endif  // DMLC_ENABLE_STD_THREAD

}
#endif