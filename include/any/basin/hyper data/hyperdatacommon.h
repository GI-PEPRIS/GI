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
#ifndef __ANYBASIN_HUGE_DATA_COMMON_H__
#define __ANYBASIN_HUGE_DATA_COMMON_H__

#include "anybase/anystl.h"

//
namespace AnyBasin
{
	/*!
	 * \brief Split a string by delimiter
	 * \param s String to be splitted.
	 * \param delim The delimiter.
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

	// simple routine to convert any data to string
	template<typename T>
	inline std::string ToString(const T& data) 
	{
		std::ostringstream os;
		os << data;
		return os.str();
	}

}
#endif