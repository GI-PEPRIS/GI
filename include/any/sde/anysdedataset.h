/*!
 * The AnyPetro of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the domain data model etc.
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
#ifndef __ANYSDE_SDE_DATASET_H__
#define __ANYSDE_SDE_DATASET_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// refer to "PORT" definitions
#include "any/base/anyport.h"

// Refer to "test object"
#include "any/base/loki/singleton.h"
using namespace AnyBase::Loki;

// refer to REFLECTION mechanism

//
namespace AnySDE
{
	// forward class
	class CAnySdeLayer;

	/*!
	* as singleton
	**/
	class ANYSDE_CLASS CAnySdeDataset
	{
		// Not permit copy & assign operations
		CAnySdeDataset(const CAnySdeDataset &other);
		const CAnySdeDataset &operator=(const CAnySdeDataset &other);
		
		// sinleton
		typedef SingletonHolder<CAnySdeDataset, CreateUsingNew> Singleton;

	public:
		/*!
		* hierarchical space decomposition
		**/
		struct DatasetRecord
		{
			// encoded by layerIdx and tileIdx
			long m_gateIdx;
			// foreign key from kida_class table
			long m_layerIdx;
			// tile idx
			long m_tileIdx;
			// grid cardinality for parcels
			long m_xLayerCount;
			long m_yLayerCount;
			// for DB\QUERY indexer
			long m_shift;
			// the tile size, by defualt 1
			long m_xTileCount;
			long m_yTileCount;
			// the whole dataset extent
			double m_minX;
			double m_maxX;
			double m_minY;
			double m_maxY;

			/*!
			*
			**/
			DatasetRecord() : m_gateIdx(ANY_NAN), m_layerIdx(ANY_NAN), m_tileIdx(ANY_NAN), m_xLayerCount(0), m_yLayerCount(0), m_xTileCount(1), m_yTileCount(1), \
				m_minX(ANY_NAN), m_maxX(ANY_NAN), m_minY(ANY_NAN), m_maxY(ANY_NAN)
			{
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySdeDataset();

		/*!
		*
		**/
		~CAnySdeDataset();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool RegisterLayer(const CAnySdeLayer *layer);

		/*!
		*
		**/
		void Load();

		/*!
		*
		**/
		void Commit();

		//
		//
		//
		/*!
		*
		**/
		static CAnySdeDataset &GetSingleton();

		/*!
		*
		**/
		bool ComplareLayerGateIdx(const DatasetRecord &first, const DatasetRecord &second);

	private:
		// grid index infomation
		std::vector<DatasetRecord> m_layers;

		// index meta table
		string m_datasetTable;
	};
}

#endif
