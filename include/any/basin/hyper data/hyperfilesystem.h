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
#ifndef __ANYBASIN_HYPER_DATA_FILESYSTEM_H__
#define __ANYBASIN_HYPER_DATA_FILESYSTEM_H__

#include "hyperstream.h"
#include "anybase\anystl.h"

namespace AnyBasin
{
	/*!
	 * \brief Split a string by delimiter
	 * \param s String to be splitted.
	 * \param delim The delimiter.
	 * \return a splitted vector of strings.
	 */
	inline std::vector<std::string> Split(const std::string& s, char delim)
	{
		std::string item;
		std::istringstream is(s);
		std::vector<std::string> ret;
		while (std::getline(is, item, delim)) 
		{
			ret.push_back(item);
		}
		return ret;
	}

	/*!
	 * \brief some super set of URI
	 *  that allows sugars to be passed around
	 *  Example:
	 *
	 *  hdfs:///mylibsvm/?format=libsvm&clabel=0#mycache-file.
	 */
	class URISpec 
	{
	 public:
		/*! \brief the real URI */
		std::string uri;
		/*! \brief arguments in the URL */
		std::map<std::string, std::string> args;
		/*! \brief the path to cache file */
		std::string cache_file;
		/*!
		* \brief constructor.
		* \param uri The raw uri string.
		* \param part_index The parition index of the part.
		* \param num_parts total number of parts.
		*/
		explicit URISpec(const std::string& uri,
						unsigned part_index,
						unsigned num_parts) {
		std::vector<std::string> name_cache = Split(uri, '#');

		if (name_cache.size() == 2) {
			std::ostringstream os;
			os << name_cache[1];
			if (num_parts != 1) {
			os << ".split" << num_parts << ".part" << part_index;
			}
			this->cache_file = os.str();
		} else {
			//CHECK_EQ(name_cache.size(), 1U)
			//	<< "only one `#` is allowed in file path for cachefile specification";
		}
		std::vector<std::string> name_args = Split(name_cache[0], '?');
		if (name_args.size() == 2) {
			std::vector<std::string> arg_list = Split(name_args[1], '&');
			for (size_t i = 0; i < arg_list.size(); ++i) {
			std::istringstream is(arg_list[i]);
			std::pair<std::string, std::string> kv;
			//CHECK(std::getline(is, kv.first, '=')) << "Invalid uri argument format"
			//	<< " for key in arg " << i + 1;
			//CHECK(std::getline(is, kv.second)) << "Invalid uri argument format"
			//	<< " for value in arg " << i + 1;
			this->args.insert(kv);
			}
		} else {
			//CHECK_EQ(name_args.size(), 1U)
			//	<< "only one `#` is allowed in file path for cachefile specification";
		}
		this->uri = name_args[0];
		}
	};

	/*! \brief common data structure for URI */
	struct URI 
	{
		/*! \brief protocol */
		std::string protocol;
		/*!
		* \brief host name, namenode for HDFS, bucket name for s3
		*/
		std::string host;
		/*! \brief name of the path */
		std::string name;
		/*! \brief enable default constructor */
		URI(void) {}
		/*!
		* \brief construct from URI string
		*/
		explicit URI(const char *uri) 
		{
		const char *p = std::strstr(uri, "://");
		if (p == NULL) {
			name = uri;
		} else {
			protocol = std::string(uri, p - uri + 3);
			uri = p + 3;
			p = std::strchr(uri, '/');
			if (p == NULL) {
			host = uri; name = '/';
			} else {
			host = std::string(uri, p - uri);
			name = p;
			}
		}
		}
		/*! \brief string representation */
		inline std::string str(void) const {
		return protocol + host + name;
		}
	};

	/*! \brief type of file */
	enum FileType 
	{
		/*! \brief the file is file */
		kFile,
		/*! \brief the file is directory */
		kDirectory
	};

	/*! \brief use to store file information */
	struct FileInfo 
	{
		/*! \brief full path to the file */
		URI path;
		/*! \brief the size of the file */
		size_t size;
		/*! \brief the type of the file */
		FileType type;
		/*! \brief default constructor */
		FileInfo() : size(0), type(kFile) {}
	};

	/*! \brief file system system interface */
	class HyperFileSystem 
	{
	 public:
		  /*!
		   * \brief get singleton of filesystem instance according to URI
		   * \param path can be s3://..., hdfs://..., file://...,
		   *            empty string(will return local)
		   * \return a corresponding filesystem, report error if
		   *         we cannot find a matching system
		   */
		  static HyperFileSystem *GetInstance(const URI &path);
		  /*! \brief virtual destructor */
		  virtual ~HyperFileSystem() {}
		  /*!
		   * \brief get information about a path
		   * \param path the path to the file
		   * \return the information about the file
		   */
		  virtual FileInfo GetPathInfo(const URI &path) = 0;
		  /*!
		   * \brief list files in a directory
		   * \param path to the file
		   * \param out_list the output information about the files
		   */
		  virtual void ListDirectory(const URI &path, std::vector<FileInfo> *out_list) = 0;
		  /*!
		   * \brief open a stream
		   * \param path path to file
		   * \param uri the uri of the input, can contain hdfs prefix
		   * \param flag can be "w", "r", "a
		   * \param allow_null whether NULL can be returned, or directly report error
		   * \return the created stream, can be NULL when allow_null == true and file do not exist
		   */
		  virtual HyperStream *Open(const URI &path,
							   const char* const flag,
							   bool allow_null = false) = 0;
		  /*!
		   * \brief open a seekable stream for read
		   * \param path the path to the file
		   * \param allow_null whether NULL can be returned, or directly report error
		   * \return the created stream, can be NULL when allow_null == true and file do not exist
		   */
		  virtual HyperSeekStream *OpenForRead(const URI &path,
										  bool allow_null = false) = 0;
	};

}

#endif