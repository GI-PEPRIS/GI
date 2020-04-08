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
#ifndef __ANYBASIN_HYPER_DATA_BASIC_H__
#define __ANYBASIN_HYPER_DATA_BASIC_H__

//
#include "hyperstream.h"

//
#include "any/base/anystl.h"

// shared by XGBoost 
namespace AnyBasin
{
	/*!
	 * \brief data iterator interface
	 *  this is not a C++ style iterator, but nice for data pulling:)
	 *  This interface is used to pull in the data
	 *  The system can do some useful tricks for you like pre-fetching
	 *  from disk and pre-computation.
	 *
	 * Usage example:
	 * \code
	 *
	 *   itr->BeforeFirst();
	 *   while (itr->Next()) {
	 *      const DType &batch = itr->Value();
	 *      // some computations
	 *   }
	 * \endcode
	 * \tparam DType the data type
	 */
	template<typename DType>
	class HyperDataIter 
	{
	 public:
	  /*! \brief destructor */
	  virtual ~HyperDataIter(void) {}
	  /*! \brief set before first of the item */
	  virtual void BeforeFirst(void) = 0;
	  /*! \brief move to next item */
	  virtual bool Next(void) = 0;
	  /*! \brief get current data */
	  virtual const DType &Value(void) const = 0;
	  /*! \brief clear the data structure  */
	  virtual void Clear(void) = 0;
	};

	// data type accepted by simulation process
	enum HyperDataType 
	{
		HDT_Float32 = 1,
		HDT_Double  = 2,
		HDT_UInt32  = 3,
		HDT_UInt64  = 4
	};

	/*!
	* which step and its meta info about data or matrix content
	**/
	struct HyperMetaInfo 
	{
		void Clear(){}
		void LoadBinary(HyperStream* fi){}
		void SaveBinary(HyperStream* fi){}

		int m_num_col;
		int m_num_row;
	};

	// read-only sparse instance batch in CSR format
	struct HyperSparseBatch 
	{
		// an entry of sparse vector
		struct Entry 
		{
			/*! \brief feature index */
			unsigned int m_index;
			/*! \brief feature value */
			double m_fvalue;
			/*! \brief default constructor */
			Entry() {}
			/*!
				* \brief constructor with index and value
				* \param index The feature or row index.
				* \param fvalue THe feature value.
				*/
			Entry(unsigned int index, double fvalue) : m_index(index), m_fvalue(fvalue) {}
			Entry(const Entry &other)
			{
				*this = other;
			}
			const Entry &operator=(const Entry &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_index = other.m_index;
				m_fvalue = other.m_fvalue;
				return *this;
			}
			/*! \brief reversely compare feature values */
			inline static bool CmpValue(const Entry& a, const Entry& b) {
				return a.m_fvalue < b.m_fvalue;
			}
			inline static bool CmpIndex(const Entry& a, const Entry& b) {
				return a.m_index < b.m_index;
			}
		};

		// an instance of sparse vector in the batch
		struct Inst 
		{
			/*! \brief pointer to the elements*/
			const Entry *m_data;
			/*! \brief length of the instance */
			unsigned int m_length;
			/*! \brief constructor */
			Inst() : m_data(0), m_length(0) {}
			Inst(const Entry *data, unsigned int length) : m_data(data), m_length(length) {}
			/*! \brief get i-th pair in the sparse vector*/
			inline const Entry& operator[](unsigned int i) const
			{
				return m_data[i];
			}
			Inst(const Inst &other)
			{
				*this = other;
			}
			const Inst &operator=(const Inst &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_data = other.m_data;
				m_length = other.m_length;
				return *this;
			}
		};

		// batch size
		unsigned int m_size;
	};

	// read-only row batch, used to access row continuously
	struct HyperRowBatch : public HyperSparseBatch 
	{
		/*! \brief the offset of rowid of this batch */
		unsigned long m_base_rowid;
		/*! \brief array[size+1], row pointer of each of the elements */
		const unsigned long *m_ind_ptr;
		/*! \brief array[ind_ptr.back()], content of the sparse element */
		const Entry *m_data_ptr;
		/*! \brief get i-th row from the batch */
		inline Inst operator[](unsigned int i) const
		{
			return Inst(m_data_ptr + m_ind_ptr[i], static_cast<__int32>(m_ind_ptr[i + 1] - m_ind_ptr[i]));
		}
	};

	/*!
	 * \brief read-only column batch, used to access columns,
	 * the columns are not required to be continuous
	 */
	struct HyperColBatch : public HyperSparseBatch 
	{
		/*! \brief column index of each columns in the data */
		const unsigned int *m_col_index;
		/*! \brief pointer to the column data */
		const Inst *m_col_data;
		/*! \brief get i-th column from the batch */
		inline Inst operator[](unsigned int i) const 
		{
			return m_col_data[i];
		}
	};

	/*!
	 * \brief This is data structure that user can pass to DMatrix::Create
	 *  to create a DMatrix for training, user can create this data structure
	 *  for customized Data Loading on single machine.
	 *
	 *  On distributed setting, usually an customized dmlc::Parser is needed instead.
	 */
	class HyperDataSource : public HyperDataIter<HyperRowBatch> 
	{
	 public:
		/*!
		* \brief Meta information about the dataset
		* The subclass need to be able to load this correctly from data.
		*/
		HyperMetaInfo m_info;
	};

	/*!
	 * \brief A vector-like structure to represent set of rows.
	 * But saves the memory when all rows are in the set (common case in xgb)
	 */
	struct HyperRowSet 
	{
	 public:
		/*! \return i-th row index */
		inline unsigned int operator[](unsigned int i) const;
		/*! \return the size of the set. */
		inline unsigned int size() const;
		/*! \brief push the index back to the set */
		inline void push_back(unsigned int i);
		/*! \brief clear the set */
		inline void clear();
		/*!
		* \brief save rowset to file.
		* \param fo The file to be saved.
		*/
		inline void Save(HyperStream* fo) const;
		/*!
		* \brief Load rowset from file.
		* \param fi The file to be loaded.
		* \return if read is successful.
		*/
		inline bool Load(HyperStream* fi);
		/*! \brief constructor */
		HyperRowSet() : m_size(0) {}

		private:
		/*! \brief The internal data structure of size */
		unsigned long m_size;
		/*! \brief The internal data structure of row set if not all*/
		std::vector<unsigned int> m_rows;
	};

	// implementation of inline functions
	inline unsigned int HyperRowSet::operator[](unsigned int i) const 
	{
		return m_rows.size() == 0 ? i : m_rows[i];
	}

	inline unsigned int HyperRowSet::size() const 
	{
		return m_size;
	}

	inline void HyperRowSet::clear() 
	{
		m_rows.clear(); m_size = 0;
	}

	inline void HyperRowSet::push_back(unsigned int i) 
	{
		if (m_rows.size() == 0) 
		{
			if (i == m_size) 
			{
				++m_size; return;
			}
			else
			{
				m_rows.resize(m_size);
				for (unsigned int i = 0; i < m_size; ++i) 
				{
					m_rows[i] = static_cast<unsigned int>(i);
				}
			}
		}
		m_rows.push_back(i);
		++m_size;
	}

	inline void HyperRowSet::Save(HyperStream* fo) const 
	{
		fo->Write(m_rows);
		fo->Write(&m_size, sizeof(m_size));
	}

	inline bool HyperRowSet::Load(HyperStream* fi) 
	{
		if (!fi->Read(&m_rows)) return false;
		if (m_rows.size() != 0) return true;
		return fi->Read(&m_size, sizeof(m_size)) == sizeof(m_size);
	}

	/*!
	 * \brief one row of training instance
	 * \tparam IndexType type of index
	 */
	template<typename IndexType>
	class HyperRow {
	 public:
	  /*! \brief label of the instance */
	  double m_label;
	  /*! \brief weight of the instance */
	  double m_weight;
	  /*! \brief length of the sparse vector */
	  size_t m_length;
	  /*!
	   * \brief field of each instance
	   */
	  const IndexType *m_field;
	  /*!
	   * \brief index of each instance
	   */
	  const IndexType *m_index;
	  /*!
	   * \brief array value of each instance, this can be NULL
	   *  indicating every value is set to be 1
	   */
	  const double *m_value;
	  /*!
	   * \param i the input index
	   * \return field for i-th feature
	   */
	  inline IndexType get_field(size_t i) const 
	  {
		return m_field[i];
	  }
	  /*!
	   * \param i the input index
	   * \return i-th feature
	   */
	  inline IndexType get_index(size_t i) const 
	  {
		return m_index[i];
	  }
	  /*!
	   * \param i the input index
	   * \return i-th feature value, this function is always
	   *  safe even when value == NULL
	   */
	  inline double get_value(size_t i) const 
	  {
		return m_value == NULL ? 1.0f : m_value[i];
	  }
	  /*!
	   * \brief helper function to compute dot product of current
	   * \param weight the dense array of weight we want to product
	   * \param size the size of the weight vector
	   * \tparam V type of the weight vector
	   * \return the result of dot product
	   */
	  template<typename V>
	  inline V SDot(const V *weight, size_t size) const 
	  {
		V sum = static_cast<V>(0);
		if (m_value == NULL)
		{
		  for (size_t i = 0; i < length; ++i) 
		  {
			assert(m_index[i] < size);// << "feature index exceed bound";
			sum += m_weight[index[i]];
		  }
		}
		else
		{
		  for (size_t i = 0; i < length; ++i) 
		  {
			assert(m_index[i] < size);// << "feature index exceed bound";
			sum += m_weight[index[i]] * m_value[i];
		  }
		}
		return sum;
	  }
	};


	/*!
	 * \brief a block of data, containing several rows in sparse matrix
	 *  This is useful for (streaming-sxtyle) algorithms that scans through rows of data
	 *  examples include: SGD, GD, L-BFGS, kmeans
	 *
	 *  The size of batch is usually large enough so that parallelizing over the rows
	 *  can give significant speedup
	 * \tparam IndexType type to store the index used in row batch
	 */
	template<typename IndexType>
	struct HyperRowBlock 
	{
	  /*! \brief batch size */
	  size_t m_size;
	  /*! \brief array[size+1], row pointer to beginning of each rows */
	  const size_t *m_offset;
	  /*! \brief array[size] label of each instance */
	  const double *m_label;
	  /*! \brief With weight: array[size] label of each instance, otherwise nullptr */
	  const double *m_weight;
	  /*! \brief field id*/
	  const IndexType *m_field;
	  /*! \brief feature index */
	  const IndexType *m_index;
	  /*! \brief feature value, can be NULL, indicating all values are 1 */
	  const double *m_value;
	  /*!
	   * \brief get specific rows in the batch
	   * \param rowid the rowid in that row
	   * \return the instance corresponding to the row
	   */
	  inline HyperRow<IndexType> operator[](size_t rowid) const;
	  /*! \return memory cost of the block in bytes */
	  inline size_t MemCostBytes(void) const {
		size_t cost = m_size * (sizeof(size_t) + sizeof(double));
		if (weight != NULL) cost += m_size * sizeof(double);
		size_t ndata = m_offset[m_size] - m_offset[0];
		if (field != NULL) cost += ndata * sizeof(IndexType);
		if (index != NULL) cost += ndata * sizeof(IndexType);
		if (value != NULL) cost += ndata * sizeof(double);
		return cost;
	  }
	  /*!
	   * \brief slice a RowBlock to get rows in [begin, end)
	   * \param begin the begin row index
	   * \param end the end row index
	   * \return the sliced RowBlock
	   */
	  inline HyperRowBlock Slice(size_t begin, size_t end) const 
	  {
		  assert(begin <= end && end <= size);
		  HyperRowBlock ret;
		  ret.m_size = end - begin;
		  ret.label = label + begin;
		  if (weight != NULL) 
		  {
			  ret.m_weight = m_weight + begin;
		  }
		  else
		  {
			  ret.m_weight = NULL;
		  }
		  ret.m_offset = m_offset + begin;
		  ret.m_field = m_field;
		  ret.m_index = m_index;
		  ret.m_value = m_value;
		  return ret;
	  }
	};

	/*!
	 * \brief Data structure that holds the data
	 * Row block iterator interface that gets RowBlocks
	 * Difference between RowBlockIter and Parser:
	 *     RowBlockIter caches the data internally that can be used
	 *     to iterate the dataset multiple times,
	 *     Parser holds very limited internal state and was usually
	 *     used to read data only once
	 *
	 * \sa Parser
	 * \tparam IndexType type of index in RowBlock
	 *  Create function was only implemented for IndexType uint64_t and uint32_t
	 */
	template<typename IndexType>
	class HyperRowBlockIter : public HyperDataIter<HyperRowBlock<IndexType> > 
	{
	 public:
	  /*!
	   * \brief create a new instance of iterator that returns rowbatch
	   *  by default, a in-memory based iterator will be returned
	   *
	   * \param uri the uri of the input, can contain hdfs prefix
	   * \param part_index the part id of current input
	   * \param num_parts total number of splits
	   * \param type type of dataset can be: "libsvm", ...
	   *
	   * \return the created data iterator
	   */
	  static HyperRowBlockIter<IndexType> *
	  Create(const char *uri,
			 unsigned part_index,
			 unsigned num_parts,
			 const char *type);
	  /*! \return maximum feature dimension in the dataset */
	  virtual size_t NumCol() const = 0;
	};

	/*!
	 * \brief Internal data structured used by XGBoost during training.
	 *  There are two ways to create a customized DMatrix that reads in user defined-format.
	 *
	 *  - Provide a dmlc::Parser and pass into the DMatrix::Create
	 *  - Alternatively, if data can be represented by an URL, define a new dmlc::Parser and register by DMLC_REGISTER_DATA_PARSER;
	 *      - This works best for user defined data input source, such as data-base, filesystem.
	 *  - Provide a DataSource, that can be passed to DMatrix::Create
	 *      This can be used to re-use inmemory data structure into DMatrix.
	 */
	class HyperDataMatrix 
	{
	 public:
		  /*! \brief default constructor */
		  HyperDataMatrix() {}
		  /*! \brief meta information of the dataset */
		  virtual HyperMetaInfo& info() = 0;
		  /*! \brief meta information of the dataset */
		  virtual const HyperMetaInfo& info() const = 0;
		  /*!
		   * \brief get the row iterator, reset to beginning position
		   * \note Only either RowIterator or  column Iterator can be active.
		   */
		  virtual HyperDataIter<HyperRowBatch>* RowIterator() = 0;
		  /*!\brief get column iterator, reset to the beginning position */
		  virtual HyperDataIter<HyperColBatch>* ColIterator() = 0;
		  /*!
		   * \brief get the column iterator associated with subset of column features.
		   * \param fset is the list of column index set that must be contained in the returning Column iterator
		   * \return the column iterator, initialized so that it reads the elements in fset
		   */
		  virtual HyperDataIter<HyperColBatch>* ColIterator(const std::vector<unsigned int>& fset) = 0;
		  /*!
		   * \brief check if column access is supported, if not, initialize column access.
		   * \param enabled whether certain feature should be included in column access.
		   * \param subsample subsample ratio when generating column access.
		   * \param max_row_perbatch auxiliary information, maximum row used in each column batch.
		   *         this is a hint information that can be ignored by the implementation.
		   * \return Number of column blocks in the column access.
		   */
		  virtual void InitColAccess(const std::vector<bool>& enabled,
									 float subsample,
									 unsigned int max_row_perbatch) = 0;
		  // the following are column meta data, should be able to answer them fast.
		  /*! \return whether column access is enabled */
		  virtual bool HaveColAccess() const = 0;
		  /*! \return Whether the data columns single column block. */
		  virtual bool SingleColBlock() const = 0;
		  /*! \brief get number of non-missing entries in column */
		  virtual unsigned int GetColSize(unsigned int cidx) const = 0;
		  /*! \brief get column density */
		  virtual float GetColDensity(unsigned int cidx) const = 0;
		  /*! \return reference of buffered rowset, in column access */
		  virtual const HyperRowSet& buffered_rowset() const = 0;
		  /*! \brief virtual destructor */
		  virtual ~HyperDataMatrix() {}
		  /*!
		   * \brief Save DMatrix to local file.
		   *  The saved file only works for non-sharded dataset(single machine training).
		   *  This API is deprecated and dis-encouraged to use.
		   * \param fname The file name to be saved.
		   * \return The created DMatrix.
		   */
		  virtual void SaveToLocalFile(const std::string& fname);
		  /*!
		   * \brief Load DMatrix from URI.
		   * \param uri The URI of input.
		   * \param silent Whether print information during loading.
		   * \param load_row_split Flag to read in part of rows, divided among the workers in distributed mode.
		   * \param file_format The format type of the file, used for dmlc::Parser::Create.
		   *   By default "auto" will be able to load in both local binary file.
		   * \return The created DMatrix.
		   */
		  //static DMatrix* Load(const std::string& uri,
				//			   bool silent,
				//			   bool load_row_split,
				//			   const std::string& file_format = "auto");
		  /*!
		   * \brief create a new DMatrix, by wrapping a row_iterator, and meta info.
		   * \param source The source iterator of the data, the create function takes ownership of the source.
		   * \param cache_prefix The path to prefix of temporary cache file of the DMatrix when used in external memory mode.
		   *     This can be nullptr for common cases, and in-memory mode will be used.
		   * \return a Created DMatrix.
		   */
		  static HyperDataMatrix* Create(std::unique_ptr<HyperDataSource>&& source,
								 const std::string& cache_prefix = "");
		  /*!
		   * \brief Create a DMatrix by loading data from parser.
		   *  Parser can later be deleted after the DMatrix i created.
		   * \param parser The input data parser
		   * \param cache_prefix The path to prefix of temporary cache file of the DMatrix when used in external memory mode.
		   *     This can be nullptr for common cases, and in-memory mode will be used.
		   * \sa dmlc::Parser
		   * \note dmlc-core provides efficient distributed data parser for libsvm format.
		   *  User can create and register customized parser to load their own format using DMLC_REGISTER_DATA_PARSER.
		   *  See "dmlc-core/include/dmlc/data.h" for detail.
		   * \return A created DMatrix.
		   */
		  //static DMatrix* Create(dmlc::Parser<uint32_t>* parser,
				//				 const std::string& cache_prefix = "");
	};

	/*!
	 * \brief parser interface that parses input data
	 * used to load dmlc data format into your own data format
	 * Difference between RowBlockIter and Parser:
	 *     RowBlockIter caches the data internally that can be used
	 *     to iterate the dataset multiple times,
	 *     Parser holds very limited internal state and was usually
	 *     used to read data only once
	 *
	 *
	 * \sa RowBlockIter
	 * \tparam IndexType type of index in RowBlock
	 *  Create function was only implemented for IndexType uint64_t and uint32_t
	 */
	template <typename IndexType>
	class HyperParser : public HyperDataIter<HyperRowBlock<IndexType> > 
	{
	 public:
	  /*!
	  * \brief create a new instance of parser based on the "type"
	  *
	  * \param uri_ the uri of the input, can contain hdfs prefix
	  * \param part_index the part id of current input
	  * \param num_parts total number of splits
	  * \param type type of dataset can be: "libsvm", "auto", ...
	  *
	  * When "auto" is passed, the type is decided by format argument string in URI.
	  *
	  * \return the created parser
	  */
	  static HyperParser<IndexType> *
	  Create(const char *uri_,
			 unsigned part_index,
			 unsigned num_parts,
			 const char *type);
	  /*! \return size of bytes read so far */
	  virtual size_t BytesRead(void) const = 0;
	  /*! \brief Factory type of the parser*/
	  typedef HyperParser<IndexType>* (*Factory)
		  (const std::string& path,
		   const std::map<std::string, std::string>& args,
		   unsigned part_index,
		   unsigned num_parts);
	};

}

#endif