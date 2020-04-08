/*!
 * The AnySDB of PetroCOVERY solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy management 
 * and rendering of geometries being a leading one.
 *
 * Copyright (C) 2015 Xiujie Sheng
 *
 * This library isn't a free software, so you cann't take the sourcecode without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
 * if you illegally got it. 
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
#ifndef __ANYDEEPLEARNING_DYNAMIC_DATACUBE_H__
#define __ANYDEEPLEARNING_DYNAMIC_DATACUBE_H__

#include "anylearning.h"

#include "any/base/anystl.h"
using namespace std;

namespace AnyLearning
{
	/*!
	* data cube in memory, as part of distributed data cube in future
	**/
	class ANYLEARNING_CLASS CAnyDynamicDataCube
	{
	public:
		enum DBFieldType
		{
			DBF_Unknown = 0,
			DBF_Binary,
			DBF_Bool,
			DBF_Float,
			DBF_Int,
			DBF_Text,
			DBF_LongText,
			DBF_LongBinary,
			DBF_Date
		};
		
		//
		struct CubeMeasure
		{
			string m_name;
			int m_type;
		};
		typedef std::vector<CubeMeasure> CubeMeasureVector;

		//
		struct CubeAttribute
		{
			string m_name;
			int m_type;
			std::vector<string> m_enumvalues;
		};
		typedef std::vector<CubeAttribute> CubeAttributeVector;

		//
		struct CubeDimension : CubeAttributeVector
		{
			string m_name;
		};
		typedef std::vector<CubeDimension> CubeDimensionVector;

		// fact record
		struct CubeCell
		{
			// cell id
			long m_cellidx;  // element idx
			// measures
			std::vector<string> m_measuredatas;
			// dimensions
			std::vector<string> m_attributedatas;
		};

		// data cube or fact table
		typedef std::list<CubeCell> DataCube;
		typedef DataCube::iterator cub_iterator;

		// index cache or dynamic tree
		struct CubeIndex
		{
			CubeAttributeVector m_attributes;
			std::vector<cub_iterator> m_indice;
		};
		typedef std::vector<CubeIndex*> CubeIndexVector;

	public:
		//
		//
		//
		CAnyDynamicDataCube();
		CAnyDynamicDataCube(CubeMeasureVector &measures, CubeAttributeVector &attributes);
		~CAnyDynamicDataCube();

	public:
		//
		// meta data of current cube
		//
		void AddMeasure(CubeMeasure &measure);
		void RemoveMeasure(string &name);
		void AddDimension(string &name);
		void RemoveDimension(string &name);
		void AddAttribute(CubeAttribute &attr);
		void RemoveAttribute(string &name);
		void Clear();

		/*!
		*2016/12/21: add enum values
		**/
		void AddAttributeEnumValue(const std::string &name, const std::string &enumVal);

		//
		// ETL
		//
		void ClearFactTable();
		void AddFactRecord(CubeCell &cell);

		//
		// Query and main dynamic tree index hidden
		//
		void Query(CubeAttributeVector &enumattributes, std::vector<std::vector<string> > &enumvalues, \
			CubeAttributeVector &rangeattributes, std::vector<std::vector<string> > &rangemins, std::vector<std::vector<string> > &rangemaxs, std::vector<cub_iterator> &results);
		bool IsFactMatch(cub_iterator &iter, std::vector<int> &enumattributeoffsets, std::vector<std::vector<string> > &enumvalues, \
			std::vector<int> &rangeattributeoffsets, std::vector<std::vector<string> > &rangemins, std::vector<std::vector<string> > &rangemaxs);

		//
		// index related functions
		//
		void AddIndex(CubeAttributeVector &attributes);
		void RemoveOneIndex();
		bool IsIndexCover(CubeAttributeVector &indexattributes, CubeAttributeVector &queryenumattributes, CubeAttributeVector &queryreangeattributes);
		bool IsIndexCover(CubeAttributeVector &indexattributesA, CubeAttributeVector &indexattributesB);
		void QuickSort(std::vector<cub_iterator> &indice, int zz, int yy, std::vector<int> &attributetypes, std::vector<int> &attributeoffsets, std::vector<int> &upordownorders);
		int CompareContent(cub_iterator &a, cub_iterator &b, std::vector<int> &attributetypes, std::vector<int> &attributeoffsets, std::vector<int> &upordownorders);
	public:
		// meta data of data cube
		CubeMeasureVector m_measures;
		CubeAttributeVector m_attributes;

		// fact table
		DataCube m_datacube;

		// index tree
		CubeIndexVector m_indices;

		int m_indexlimits; 
	};
}


#endif