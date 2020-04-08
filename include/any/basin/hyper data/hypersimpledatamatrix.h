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
#ifndef __ANYBASIN_HYPER_DATA_SIMPLE_DATA_MATRIX_H__
#define __ANYBASIN_HYPER_DATA_SIMPLE_DATA_MATRIX_H__

// import omp
#include "anybasin.h"

//
#include "Hyperdata.h"
#include "Hypersparsepage.h"

//
#include "any/base/anystl.h"

// shared by XGBoost 
namespace AnyBasin
{
	/*!
	*
	**/
	class HyperSimpleDataMatrix : public HyperDataMatrix
	{
		// in-memory column batch iterator.
		struct ColBatchIter: HyperDataIter<HyperColBatch> {
		public:
			ColBatchIter() : data_ptr_(0) {}
			void BeforeFirst() override {
				data_ptr_ = 0;
			}
			const HyperColBatch &Value() const override {
				return batch_;
			}
			bool Next() override;
			void Clear() override {}
		private:
			// allow SimpleDMatrix to access it.
			friend class HyperSimpleDataMatrix;
			// data content
			std::vector<unsigned int> col_index_;
			// column content
			std::vector<HyperColBatch::Inst> col_data_;
			// column sparse pages
			std::vector<std::unique_ptr<HyperSparsePage> > cpages_;
			// data pointer
			unsigned int data_ptr_;
			// temporal space for batch
			HyperColBatch batch_;
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		HyperSimpleDataMatrix(std::unique_ptr<HyperDataSource>&& source) : source_(std::move(source)) {}
		~HyperSimpleDataMatrix();

	public:
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

		bool HaveColAccess() const override {
			return col_size_.size() != 0;
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

		HyperDataIter<HyperColBatch>* ColIterator();

		HyperDataIter<HyperColBatch>* ColIterator(const std::vector<unsigned int>& fset);

		void InitColAccess(const std::vector<bool>& enabled,
			float subsample,
			unsigned int max_row_perbatch);

		bool SingleColBlock() const;

		// herman
		// directly to create col iterator
		void InitColAccess(unsigned int max_row_perbatch = unsigned long(-1));

	private:
		// internal function to make one batch from row iter.
		void MakeOneBatch(const std::vector<bool>& enabled,
			float pkeep,
			HyperSparsePage *pcol);

		// herman
		// directly to create col iterator
		void MakeOneBatch(HyperSparsePage *pcol);

		void MakeManyBatch(const std::vector<bool>& enabled,
			float pkeep,
			size_t max_row_perbatch);

		void MakeColPage(const HyperRowBatch& batch,
			size_t buffer_begin,
			const std::vector<bool>& enabled,
			HyperSparsePage* pcol);

	private:
		// source data pointer.
		std::unique_ptr<HyperDataSource> source_;
		// column iterator
		ColBatchIter col_iter_;
		// list of row index that are buffered.
		HyperRowSet buffered_rowset_;
		/*! \brief sizeof column data */
		std::vector<unsigned int> col_size_;
	};
}
#endif