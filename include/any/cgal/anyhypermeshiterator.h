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
#ifndef __ANYCGAL_HYPER_MESH_ITERATOR_H__
#define __ANYCGAL_HYPER_MESH_ITERATOR_H__

// Refer to EXPORT & IMPORT macroes
#include "anycgal.h"

#include "anyhypermeshbasic.h"

//
namespace AnyCGAL
{
	/*!
	*
	**/
	template<typename BatchType>
	class ANYCGAL_CLASS CAnyHyperDataIterator
	{
	public:
		//
		typedef typename std::vector<BatchType> BatchContainer;
		typedef typename BatchContainer::iterator BatchItr;

	public:
		//
		//
		//
		CAnyHyperDataIterator(){}
		virtual ~CAnyHyperDataIterator(){}

	public:
		//
		bool First()
		{
			if(!m_batches.size())
			{
				return false;
			}
			m_cursor = m_batches.begin();
			return true;
		}
		bool Next()
		{
			if(!m_batches.size())
			{
				return false;
			}
			m_cursor++;
			if(m_cursor == m_batches.end())
			{
				return false;
			}
			return true;
		}
		BatchType &Value()
		{
			return *m_cursor;
		}
		
	public:
		//
		BatchContainer m_batches;
		BatchItr m_cursor;
	};

	//
	typedef CAnyHyperDataIterator<IsoMeshBatch> IsoMeshIterator;
	typedef CAnyHyperDataIterator<IsoVertexBatch> IsoVertexIterator;

	typedef CAnyHyperDataIterator<SliceMeshBatch> SliceMeshIterator;
	typedef CAnyHyperDataIterator<SliceVertexBatch> SliceVertexIterator;

	typedef CAnyHyperDataIterator<DirectionMeshBatch> DirectionMeshIterator;
	typedef CAnyHyperDataIterator<DirectionVertexBatch> DirectionVertexIterator;

	typedef CAnyHyperDataIterator<OctreeMeshBatch> OctreeMeshIterator;
	typedef CAnyHyperDataIterator<OctreeVertexBatch> OctreeVertexIterator;

	//
	template class ANYCGAL_CLASS CAnyHyperDataIterator<IsoMeshBatch>;
	template class ANYCGAL_CLASS CAnyHyperDataIterator<IsoVertexBatch>;

	template class ANYCGAL_CLASS CAnyHyperDataIterator<SliceMeshBatch>;
	template class ANYCGAL_CLASS CAnyHyperDataIterator<SliceVertexBatch>;

	template class ANYCGAL_CLASS CAnyHyperDataIterator<DirectionMeshBatch>;
	template class ANYCGAL_CLASS CAnyHyperDataIterator<DirectionVertexBatch>;

	template class ANYCGAL_CLASS CAnyHyperDataIterator<OctreeMeshBatch>;
	template class ANYCGAL_CLASS CAnyHyperDataIterator<OctreeVertexBatch>;

}


#endif