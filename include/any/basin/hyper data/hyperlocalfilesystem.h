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
#ifndef __ANYBASIN_HYPER_DATA_LOCAL_FILESYSTEM_H__
#define __ANYBASIN_HYPER_DATA_LOCAL_FILESYSTEM_H__

#include "hyperfilesystem.h"

//
namespace AnyBasin
{
	/*! \brief local file system */
	class HyperLocalFileSystem : public HyperFileSystem 
	{
	 public:
	  /*! \brief destructor */
	  virtual ~HyperLocalFileSystem() {}
	  /*!
	   * \brief get information about a path
	   * \param path the path to the file
	   * \return the information about the file
	   */
	  virtual FileInfo GetPathInfo(const URI &path);
	  /*!
	   * \brief list files in a directory
	   * \param path to the file
	   * \param out_list the output information about the files
	   */
	  virtual void ListDirectory(const URI &path, std::vector<FileInfo> *out_list);
	  /*!
	   * \brief open a stream, will report error and exit if bad thing happens
	   * NOTE: the IStream can continue to work even when filesystem was destructed
	   * \param path path to file
	   * \param uri the uri of the input
	   * \param allow_null whether NULL can be returned, or directly report error
	   * \return the created stream, can be NULL when allow_null == true and file do not exist
	   */
	  virtual HyperSeekStream *Open(const URI &path,
							   const char* const flag,
							   bool allow_null);
	  /*!
	   * \brief open a seekable stream for read
	   * \param path the path to the file
	   * \param allow_null whether NULL can be returned, or directly report error
	   * \return the created stream, can be NULL when allow_null == true and file do not exist
	   */
	  virtual HyperSeekStream *OpenForRead(const URI &path, bool allow_null);
	  /*!
	   * \brief get a singleton of LocalFileSystem when needed
	   * \return a singleton instance
	   */
	  inline static HyperLocalFileSystem *GetInstance(void) {
		static HyperLocalFileSystem instance;
		return &instance;
	  }

	 private:
	  HyperLocalFileSystem() {}
	};
}


#endif
