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
#ifndef __ANYBASIN_HYPER_DATA_SPARSE_PAGE_DATA_MATRIX_H__
#define __ANYBASIN_HYPER_DATA_SPARSE_PAGE_DATA_MATRIX_H__

//
#include "anybasin.h"

//
#include "Hyperdata.h"
#include "Hypersparsepage.h"
#include "Hyperthreadediter.h"

//
namespace AnyBasin
{
	/*!
	*
	**/
	class HyperSparsePageDataMatrix : public HyperDataMatrix 
	{
	public:
		explicit HyperSparsePageDataMatrix(std::unique_ptr<HyperDataSource>&& source,
									const std::string& cache_info)
			: source_(std::move(source)), cache_info_(cache_info) {
		}

		HyperMetaInfo& info() {
		return source_->m_info;
		}

		const HyperMetaInfo& info() const {
		return source_->m_info;
		}

		HyperDataIter<HyperRowBatch>* RowIterator() {
		HyperDataIter<HyperRowBatch>* iter = source_.get();
		iter->BeforeFirst();
		return iter;
		}

		bool HaveColAccess() const {
		return col_iter_.get() != nullptr;
		}

		const HyperRowSet& buffered_rowset() const {
		return buffered_rowset_;
		}

		unsigned int GetColSize(unsigned int cidx) const {
		return col_size_[cidx];
		}

		float GetColDensity(unsigned int cidx) const {
		unsigned int nmiss = buffered_rowset_.size() - col_size_[cidx];
		return 1.0f - (static_cast<float>(nmiss)) / buffered_rowset_.size();
		}

		bool SingleColBlock() const {
		return false;
		}

		HyperDataIter<HyperColBatch>* ColIterator();

		HyperDataIter<HyperColBatch>* ColIterator(const std::vector<unsigned int>& fset) override;

		void InitColAccess(const std::vector<bool>& enabled,
							float subsample,
							unsigned int max_row_perbatch) override;

		/*! \brief page size 256 MB */
		static const unsigned int kPageSize = 256UL << 20UL;
		/*! \brief Maximum number of rows per batch. */
		static const unsigned int kMaxRowPerBatch = 64UL << 10UL;

	private:
		// declare the column batch iter.
		class ColPageIter : public HyperDataIter<HyperColBatch> {
		public:
		explicit ColPageIter(std::vector<std::unique_ptr<HyperSeekStream> >&& files);
		virtual ~ColPageIter();
		void BeforeFirst() override;
		const HyperColBatch &Value() const override {
			return out_;
		}
		bool Next() override;
		// initialize the column iterator with the specified index set.
		void Init(const std::vector<unsigned int>& index_set, bool load_all);

		private:
			// the temp page.
			HyperSparsePage* page_;
			// internal clock ptr.
			unsigned int clock_ptr_;
			// data file pointer.
			std::vector<std::unique_ptr<HyperSeekStream> > files_;
			// page format.
			std::vector<std::unique_ptr<HyperSparsePage::Format> > formats_;
			/*! \brief internal prefetcher. */
			std::vector<std::unique_ptr<HyperThreadedIter<HyperSparsePage> > > prefetchers_;
			// The index set to be loaded.
			std::vector<unsigned int> index_set_;
			// The index set by the outsiders
			std::vector<unsigned int> set_index_set_;
			// whether to load data dataset.
			bool set_load_all_, load_all_;
			// temporal space for batch
			HyperColBatch out_;
			// the pointer data.
			std::vector<HyperSparseBatch::Inst> col_data_;
		};
		/*!
		* \brief Try to initialize column data.
		* \return true if data already exists, false if they do not.
		*/
		bool TryInitColData();
		// source data pointer.
		std::unique_ptr<HyperDataSource> source_;
		// the cache prefix
		std::string cache_info_;
		/*! \brief list of row index that are buffered */
		HyperRowSet buffered_rowset_;
		// count for column data
		std::vector<unsigned int> col_size_;
		// internal column iter.
		std::unique_ptr<ColPageIter> col_iter_;
	};
}
#endif