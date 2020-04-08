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
#ifndef __ANYBASE_OUTPUTTER_H__
#define __ANYBASE_OUTPUTTER_H__

// refer to export etc macroes
#include "anybase.h"

// namespace
namespace AnyBase
{
	/*! 
	*\brief Abstract outputter to print test result summary.
	* \ingroup WritingTestResult
	*/
	class ANYBASE_CLASS CAnyOutputter
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		virtual ~CAnyOutputter() 
		{
		}

	public:
		/*!
		*
		**/
		virtual void Write(const char *content = 0) = 0;
	};
}

#endif
