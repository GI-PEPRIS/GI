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
#ifndef __ANYBASIN_HYPER_DATA_SIMPLE_CSR_SOURCE_H__
#define __ANYBASIN_HYPER_DATA_SIMPLE_CSR_SOURCE_H__

#include "hyperdata.h"

// shared by XGBoost 
namespace AnyBasin
{
	/*!
	*
	**/
	class HyperSimpleCSRSource : public HyperDataSource
	{
	public:
		//
		//
		//
		HyperSimpleCSRSource();
		virtual ~HyperSimpleCSRSource();

	public:
	  // implement Clear
	  void Clear() override;
	  /*!
	   * \brief copy content of data from src
	   * \param src source data iter.
	   */
	  void CopyFrom(HyperDataMatrix* src);
	  /*!
	   * \brief copy content of data from parser, also set the additional information.
	   * \param src source data iter.
	   * \param info The additional information reflected in the parser.
	   */
	  //void CopyFrom(dmlc::Parser<uint32_t>* src);
	  /*!
	   * \brief Load data from binary stream.
	   * \param fi the pointer to load data from.
	   */
	  void LoadBinary(HyperStream* fi);
	  /*!
	   * \brief Save data into binary stream
	   * \param fo The output stream.
	   */
	  void SaveBinary(HyperStream* fo);
	  // implement Next
	  bool Next() override;
	  // implement BeforeFirst
	  void BeforeFirst() override;
	  // implement Value
	  const HyperRowBatch &Value() const override;
	  /*! \brief magic number used to identify SimpleCSRSource */
	  static const int kMagic = 0xffffab01;

	public:
		// public data members
		// MetaInfo info;  // inheritated from DataSource
		/*! \brief row pointer of CSR sparse storage */
		std::vector<unsigned long> m_row_ptr;
		/*! \brief data in the CSR sparse storage */
		std::vector<HyperSparseBatch::Entry> m_row_data;

	private:
		/*! \brief internal variable, used to support iterator interface */
		bool m_at_first;
		/*! \brief */
		HyperRowBatch m_batch;
	};
}
#endif