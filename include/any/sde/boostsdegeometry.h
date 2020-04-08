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
#ifndef __ANYSDE_SDE_BOOST_GEOMETRY_H__
#define __ANYSDE_SDE_BOOST_GEOMETRY_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// refer to its parent
#include "anysdegeometry.h"

// refer to BOOST geometries
#include "boost\geometry\geometry.hpp"
#include "boost\geometry\geometries\geometries.hpp"
#include "boost\geometry\multi\geometries\multi_geometries.hpp"
using namespace boost::geometry;

//#include "anybridge\gis\anyshpbasic.h"
//using namespace AnyBridge;
//#include "anydb\anyaccessor.h"
//using namespace AnyDB;

// namespace
namespace AnySDE
{
	/*!
	* 
	**/
	template<typename Geometry>
	class ANYSDE_CLASS CBoostSdeGeometry : public CAnySdeGeometry
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CBoostSdeGeometry()
		{
		}

		/*!
		*
		**/
		CBoostSdeGeometry(long geometryIdx, short type) : CAnySdeGeometry(geometryIdx, type)
		{
		}

		/*!
		*
		**/
		~CBoostSdeGeometry()
		{
			if(m_geometry)
			{
				delete m_geometry;
			}
			m_geometry = 0;
			::free(m_data);
			m_data = NULL;
			m_data_end = NULL;
		}

	public:
		//
		//
		//
		/*!
		*
		**/
		void CreateFromBoost(Geometry *geometry);

		/*!
		* when loading from DB
		**/
		bool CreateFromWKT(const string &wkt);

		/*!
		* when loading from DB
		**/
		bool CreateFromWKB(const std::vector<unsigned char> &bytes);

		/*!
		*
		**/
		void CreateFromSHP(boost::shared_ptr<ShpGeometry> geometry);
		
		/*!
		*
		**/
		void CreateFromPoints(std::vector<CGeoPoint<double> > &points);

		/*!
		*
		**/
		void CreateFromDB(CAnyAccessor &accessor);
		
		//
		//
		//
		/*!
		*
		**/
		unsigned short RelationTo(const CGeoPoint<double> &pt);

		/*!
		* to decide the spatial relationship given extent compared to this geometry
		**/
		unsigned short RelationTo(const CGeoRect<double> &extent);
				
		/*!
		*
		**/
		unsigned short RelationTo(const std::vector<CGeoPoint<double> > &poly);
		
		/*!
		*
		**/
		void ConvertToSHP(int geometryid, CAnyShpWriter* shpWriter);

		//
		// editting interface
		//
		/*!
		*
		**/
		CAnySdeGeometry *Clone();

		/*!
		*
		**/
		void MoveTo(const CGeoPoint<double> &pos);
		
		/*!
		*
		**/
		void Move(const CGeoPoint<double> &offset);
		
		/*!
		*2015/7/20: change parameter CGeoPoint<double> to CGeoRect<double>
		**/
		CGeoPoint<double> FindPtInGeometry(const CGeoRect<double> &rect);
		
		/*!
		*
		**/
		void AddPtInGeometry(const CGeoPoint<double> &pt,const CGeoPoint<double> &pt_new);
		/*!
		*
		**/
		void DeletePtInGeometry(const CGeoPoint<double> &pt);
				
		/*!
		*20170301
		**/
		void DeletePtInGeometryByExtent(const CGeoRect<double> &rect);

		/*!
		*
		**/
		void UpdateLastPtInGeometry(const CGeoPoint<double> &pt);
		/*!
		*
		**/
		void UpdateLastPtXYInGeometry(const CGeoPoint<double> &pt, bool updateX=true, bool updateY=true);
		/*!
		*
		**/
		void UpdatePtInGeometry(const CGeoPoint<double> &pt,const CGeoPoint<double> &pt_new);

	protected:
		//
		//
		//
		/*!
		*
		**/
		template <typename OutputIterator>
		bool hex2wkb(std::string const& hex, OutputIterator bytes)
		{
			// Bytes can be only written to output iterator.
			BOOST_STATIC_ASSERT((boost::is_convertible<
				typename std::iterator_traits<OutputIterator>::iterator_category,
				const std::output_iterator_tag&>::value));

			std::string::size_type const byte_size = 2;
			if (0 != hex.size() % byte_size)
			{
				return false;
			}

			std::string::size_type const size = hex.size() / byte_size;
			for (std::string::size_type i = 0; i < size; ++i)
			{
				// TODO: This is confirmed performance killer - to be replaced with static char-to-byte map --mloskot
				std::istringstream iss(hex.substr(i * byte_size, byte_size));
				unsigned int byte(0);
				if (!(iss >> std::hex >> byte))
				{
					return false;
				}
				*bytes = static_cast<boost::uint8_t>(byte);
				++bytes;
			}

			return true;
		}

		/*!
		*
		**/
		template <typename Iterator>
		bool wkb2hex(Iterator begin, Iterator end, std::string& hex)
		{
			// Stream of bytes can only be passed using random access iterator.
			BOOST_STATIC_ASSERT((boost::is_convertible<
				typename std::iterator_traits<Iterator>::iterator_category,
				const std::random_access_iterator_tag&>::value));

			const char hexalpha[] = "0123456789ABCDEF";
			char hexbyte[3] = { 0 };
			std::ostringstream oss;

			Iterator it = begin;
			while (it != end)
			{
				boost::uint8_t byte = static_cast<boost::uint8_t>(*it);
				hexbyte[0] = hexalpha[(byte >> 4) & 0xf];
				hexbyte[1] = hexalpha[byte & 0xf];
				hexbyte[2] = '\0';
				oss << std::setw(2) << hexbyte;
				++it;
			}

			// TODO: Binary streams can be big.
			// Does it make sense to request stream buffer of proper (large) size or
			// use incremental appends within while-loop?
			hex = oss.str();

			// Poor-man validation, no performance penalty expected
			// because begin/end always are random access iterators.
			return hex.size() == (2 * std::distance(begin, end));
		}

	public:
		// kinds of boost geometry
		Geometry *m_geometry;
	};

	//
	typedef boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian> BoostPoint;
	typedef boost::geometry::model::linestring<BoostPoint> BoostLine;
	typedef boost::geometry::model::polygon<BoostPoint> BoostPolygon;
	typedef boost::geometry::model::multi_point<BoostPoint> BoostMultiPoint;
	typedef boost::geometry::model::multi_linestring<BoostLine> BoostMultiLine;
	typedef boost::geometry::model::multi_polygon<BoostPolygon> BoostMultiPolygon;
	typedef boost::geometry::model::box<BoostPoint> BoostBox;

	//
	typedef CBoostSdeGeometry<BoostPoint> CAnySdePoint;
	typedef CBoostSdeGeometry<BoostLine> CAnySdeLine;
	typedef CBoostSdeGeometry<BoostPolygon> CAnySdePolygon;
	typedef CBoostSdeGeometry<BoostMultiPoint> CAnySdeMultiPoint;
	typedef CBoostSdeGeometry<BoostMultiLine> CAnySdeMultiLine;
	typedef CBoostSdeGeometry<BoostMultiPolygon> CAnySdeMultiPolygon;

	//
	template class ANYSDE_CLASS CBoostSdeGeometry<BoostPoint>;
	template class ANYSDE_CLASS CBoostSdeGeometry<BoostLine>;
	template class ANYSDE_CLASS CBoostSdeGeometry<BoostPolygon>;
	template class ANYSDE_CLASS CBoostSdeGeometry<BoostMultiPoint>;
	template class ANYSDE_CLASS CBoostSdeGeometry<BoostMultiLine>;
	template class ANYSDE_CLASS CBoostSdeGeometry<BoostMultiPolygon>;
}

#endif
