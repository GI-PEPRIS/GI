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
#ifndef __ANYBASIN_HYPER_BASIN_SIMULATOR_HORIZON_BATCH_DISTRIBUTED_H__
#define __ANYBASIN_HYPER_BASIN_SIMULATOR_HORIZON_BATCH_DISTRIBUTED_H__

//
#include "anybasin.h"

//
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
using namespace AnyBase;
#include "any/thread/task.h"
#include "any/thread/monitor.h"
#include "any/thread/dispatchstrategies.h"

//
namespace AnyBasin
{
	// forward class
	class CHorizonBatchSimulated;

	/*!
	*
	**/
	class CHorizonBatchDistributed
	{
		//
		friend class CAnyHyperBasinSimulator;

	protected:

		// Batch index
		typedef std::vector<CHorizonBatchSimulated *> BatchCacheVector; // as memory cache

		//
		struct PageSimulated
		{
			int m_from_order;
			int m_to_order;

		};

	public:
		//
		//
		CHorizonBatchDistributed();
		~CHorizonBatchDistributed();

	public:
		//
		//
		//
		void ReleaseBatchCache();
		void InitBatchCache(int totalstepssimulated, std::vector<CGeoPoint<int> > &ijk);
		CHorizonBatchSimulated* GetBatchSimulated(int whichlayer, int whichhorizon, int whichstep);
		CHorizonBatchSimulated* GetHorizonSimulated(int whichsimulationstep, int whichhorizon);
	public:
		bool SaveToFile(int whichlayer, int whichhorizon, int whichstep, bool ismini = false);
		bool DoSaveToFile(int whichlayer, int whichhorizon, int whichstep, bool ismini);
		bool DoSaveToMem(int whichlayer, int whichhorizon, int whichstep, bool ismini);
		bool SaveToMultiFile(int whichlayer, int whichhorizon, int bachespercurrentstep);
		bool DoSaveToMultiFile(int whichlayer, int whichhorizon, int bachespercurrentstep);
		bool DoSaveToMultiMem(int whichlayer, int whichhorizon, int bachespercurrentstep);
		bool LoadFromFile(int whichlayer, int whichhorizon, int whichstep, bool ismini = false, bool reusemem = false);
		bool DoLoadFromFile(int whichlayer, int whichhorizon, int whichstep, bool ismini, bool reusemem);
		bool DoLoadFromMem(int whichlayer, int whichhorizon, int whichstep, bool ismini, bool reusemem);
		bool ClearMemory(int whichlayer, int whichhorizon, int whichstep, bool reusemem = false);
	public:
		//
		BatchCacheVector m_batches_cached;
		std::vector<CGeoPoint<int> > m_ijk;	// the same size as above cache and as index
		string m_diskfiledir;
		int m_diskfilemode;//0:内存,1:文件,2:内存+文件,3:已有文件,4:已有文件+内存,5:断点续传
		std::vector<void*> m_vertexreusemem;// vertex reuse memory
		std::vector<void*> m_meshreusemem;// mesh reuse memory
	};
}

#endif
