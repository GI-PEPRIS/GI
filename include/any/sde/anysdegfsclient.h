/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYSDE_RCF_GFS_CLIENT_H__
#define __ANYSDE_RCF_GFS_CLIENT_H__

// refer to EXPORT & IMPORT
#include "anysde.h"

#include "any/gfs/anygfschunkrunner.h"
using namespace AnyRCF;

//
namespace AnySDE
{
	/*!
	* issues control (metadata) requests to master server
	* issues data requests directly to chunk servers
	* whether or not cache metadata
	**/
	class ANYSDE_CLASS CAnySdeGFSClient : public CAnyGFSChunkRunner
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySdeGFSClient();
		~CAnySdeGFSClient();

	public:

	};
}
#endif
