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
#ifndef __ANYSDE_SDE_GEOMETRY_INTERFACE_H__
#define __ANYSDE_SDE_GEOMETRY_INTERFACE_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// refer to stl
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
using namespace AnyBase;
#include "any/db/anyaccessor.h"
using namespace AnyDB;
#include "any/bridge/gis/anyshpbasic.h"
#include "any/bridge/gis/anyshpwriter.h"
using namespace AnyBridge;

// namespace
namespace AnySDE
{
	// forward class
	class CAnySdeLayer;

	/*!
	*
	**/
	class ANYSDE_CLASS CAnySdeGeometry
	{
	public:
		// macroes
		static const unsigned int SRID_SIZE = 4;
		static const unsigned int SIZEOF_STORED_DOUBLE = 8;
		static const unsigned int POINT_DATA_SIZE = SIZEOF_STORED_DOUBLE * 2; 
		static const unsigned int WKB_HEADER_SIZE = 1 + 4;
		static const unsigned int BYTE_ORDER_SIZE = 1;
	
		/*!
		* cell against geometry object
		**/
		enum SpatialRelationType
		{
			SRT_Outside			= 1,				// disjoint
			SRT_Touch			= 1 << 1,		//
			SRT_Overlap			= 1 << 2,		// intersect
			SRT_Interior			= 1 << 3,		// within
			SRT_Cover			= 1 << 4,
		};

		/*!
		*
		**/
		enum wkbType
		{
			wkb_point= 1,
			wkb_linestring= 2,
			wkb_polygon= 3,
			wkb_multipoint= 4,
			wkb_multilinestring= 5,
			wkb_multipolygon= 6,
			wkb_geometrycollection= 7,
			wkb_end=7
		};
		
		/*!
		*
		**/
		enum wkbByteOrder
		{
			wkb_xdr= 0,    /* Big Endian */
			wkb_ndr= 1     /* Little Endian */
		};    

		/*!
		*
		**/
		enum DBOperationType
		{
			// load but not changed
			eNothing			= 0,
			// just added
			eAdd				= 1,
			// just removed
			eRemove				= 1 << 1,
			// just updated
			eDirty				= 1 << 2,
		};

	protected:
		/*!
		*
		**/
		struct st_point_2d
		{
		  double x;
		  double y;
		};

		/*!
		*
		**/
		struct st_linear_ring
		{
		  unsigned long n_points;
		  st_point_2d points;
		};

		/*!
		  It's ok that a lot of the functions are inline as these are only used once
		  in MySQL
		*/
		struct MBR
		{
		  double xmin, ymin, xmax, ymax;

		  MBR()
		  {
			xmin= ymin= DBL_MAX;
			xmax= ymax= -DBL_MAX;
		  }

		  MBR(const double xmin_arg, const double ymin_arg,
			  const double xmax_arg, const double ymax_arg)
			:xmin(xmin_arg), ymin(ymin_arg), xmax(xmax_arg), ymax(ymax_arg)
		  {}

		  MBR(const st_point_2d &min, const st_point_2d &max)
			:xmin(min.x), ymin(min.y), xmax(max.x), ymax(max.y)
		  {}
 
		  inline void add_xy(double x, double y)
		  {
			/* Not using "else" for proper one point MBR calculation */
			if (x < xmin)
				xmin= x;
			if (x > xmax)
				xmax= x;
			if (y < ymin)
				ymin= y;
			if (y > ymax)
				ymax= y;
		  }
		  void add_xy(const char *px, const char *py)
		  {
			double x, y;
			float8get(x, px);
			float8get(y, py);
			add_xy(x,y);
		  }
		  void add_mbr(const MBR *mbr)
		  {
			if (mbr->xmin < xmin)
				xmin= mbr->xmin;
			if (mbr->xmax > xmax)
				xmax= mbr->xmax;
			if (mbr->ymin < ymin)
				ymin= mbr->ymin;
			if (mbr->ymax > ymax)
				ymax= mbr->ymax;
		  }

		  int equals(const MBR *mbr)
		  {
			/* The following should be safe, even if we compare doubles */
			return ((mbr->xmin == xmin) && (mbr->ymin == ymin) &&
				(mbr->xmax == xmax) && (mbr->ymax == ymax));
		  }

		  int disjoint(const MBR *mbr)
		  {
			/* The following should be safe, even if we compare doubles */
			return ((mbr->xmin > xmax) || (mbr->ymin > ymax) ||
				(mbr->xmax < xmin) || (mbr->ymax < ymin));
		  }

		  int intersects(const MBR *mbr)
		  {
			return !disjoint(mbr);
		  }

		  int touches(const MBR *mbr)
		  {
			/* The following should be safe, even if we compare doubles */
			return ((((mbr->xmin == xmax) || (mbr->xmax == xmin)) && 
				 ((mbr->ymin >= ymin) && (mbr->ymin <= ymax) || 
				  (mbr->ymax >= ymin) && (mbr->ymax <= ymax))) ||
				(((mbr->ymin == ymax) || (mbr->ymax == ymin)) &&
				 ((mbr->xmin >= xmin) && (mbr->xmin <= xmax) ||
				  (mbr->xmax >= xmin) && (mbr->xmax <= xmax))));
		  }

		  int within(const MBR *mbr)
		  {
			/* The following should be safe, even if we compare doubles */
			return ((mbr->xmin <= xmin) && (mbr->ymin <= ymin) &&
				(mbr->xmax >= xmax) && (mbr->ymax >= ymax));
		  }

		  int contains(const MBR *mbr)
		  {
			/* The following should be safe, even if we compare doubles */
			return ((mbr->xmin >= xmin) && (mbr->ymin >= ymin) &&
				(mbr->xmax <= xmax) && (mbr->ymax <= ymax));
		  }

		  bool inner_point(double x, double y) const
		  {
			/* The following should be safe, even if we compare doubles */
			return (xmin<x) && (xmax>x) && (ymin<y) && (ymax>y);
		  }

		  int overlaps(const MBR *mbr)
		  {
			int lb= mbr->inner_point(xmin, ymin);
			int rb= mbr->inner_point(xmax, ymin);
			int rt= mbr->inner_point(xmax, ymax);
			int lt= mbr->inner_point(xmin, ymax);

			int a = lb+rb+rt+lt;
			return (a>0) && (a<4) && (!within(mbr));
		  }
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySdeGeometry() : m_idx(-1), m_wkType(wkb_xdr), m_opType(eNothing), m_layer(0), m_data(0), m_data_end(0), m_version(0)
		{
		}

		/*!
		*
		**/
		CAnySdeGeometry(long geometryIdx, short type) : m_idx(geometryIdx), m_wkType(type), m_data(0), m_data_end(0), m_layer(0), m_version(0)
		{
		}

		/*!
		*
		**/
	    virtual ~CAnySdeGeometry()
		{
		}

	public:
		//
		//
		//
		/*!
		* when loading from DB
		**/
		virtual bool CreateFromWKB(const std::vector<unsigned char> &bytes) = 0;

		/*!
		* when loading from DB
		**/
		virtual bool CreateFromWKT(const string &wkt) = 0;

		/*!
		*2015/7/20
		**/
		virtual void CreateFromPoints(std::vector<CGeoPoint<double> > &points) = 0;

		/*!
		*
		**/
		virtual bool Commit(CAnyAccessor &accessor, CAnyAccessor &accessorver, bool istoUAD = false, bool istoVer = false);
		
		/*!
		*
		**/
		virtual bool CommitFeature(CAnyAccessor &accessor, CAnyAccessor &accessorver, bool istoUAD = false, bool istoVer = false, bool modifyfeature = false);
				
		/*!
		*
		**/
		void CommitConflict(CAnyAccessor &accessor, double curtime);

		//
		// SFS interface
		// 
		/*!
		*
		**/
		virtual int GetDimension();

		/*!
		*
		**/
		virtual long GetCoordCount();

		/*!
		*
		**/
		virtual CGeoPoint<double> GetCoord(int order = 0);

		/*!
		*
		**/
		void GetEnvelope(CGeoRect<double> &envelope);

		/*!
		*
		**/
		virtual double GetLength();
				
		/*!
		*
		**/
		virtual double GetPerimeter();

		/*!
		*
		**/
		virtual double GetArea();

		/*!
		*
		**/
		virtual bool GetCentroid(CGeoPoint<double> &coord);

		/*!
		*
		**/
		virtual bool IsClosed();

		/*!
		*
		**/
		virtual bool GetExeriorRing(std::vector<CGeoPoint<double> > &coords);

		/*!
		*
		**/
		virtual bool GetExeriorRing(int order, std::vector<CGeoPoint<double> > &coords);

		/*!
		*
		**/
		virtual int GetInteriorRingCount();
				
		/*!
		*
		**/
		virtual int GetInteriorRingCount(int order);

		/*!
		*
		**/
		virtual int GetRingCount(int order = 0);

		/*!
		*
		**/
		virtual void GetInteriorRing(int ringnum, std::vector<CGeoPoint<double> > &coords);
				
		/*!
		*
		**/
		virtual void GetInteriorRing(int order, int ringnum, std::vector<CGeoPoint<double> > &coords);

		/*!
		*
		**/
		virtual int GetGeometryCount();

		/*!
		* WKB style
		**/
		virtual const char *GetGeometry(int order);

		//
		//
		//			
		/*!
		*
		**/
		virtual unsigned short RelationTo(const CGeoPoint<double> &pt) = 0;

		/*!
		* to decide the spatial relationship given extent compared to this geometry
		**/
		virtual unsigned short RelationTo(const CGeoRect<double> &extent) = 0;
				
		/*!
		*
		**/
		virtual unsigned short RelationTo(const std::vector<CGeoPoint<double> > &poly) = 0;

		/*!
		*
		**/
		virtual bool GetCoords(std::vector<CGeoPoint<double> > &coords, int order = 0, int ringnum = 0);
						
		/*!
		*
		**/
		bool IsIntersect(CGeoPoint<double> p1, CGeoPoint<double> p2, CGeoPoint<double> p3, CGeoPoint<double> p4);
		
		/*!
		*
		**/
		double CrossProduct(CGeoPoint<double> pi, CGeoPoint<double> pj, CGeoPoint<double> pk);
		
		/*!
		*
		**/
		virtual void ConvertToSHP(int geometryid, CAnyShpWriter* shpWriter) = 0;

		//
		// editting interface
		//
		/*!
		*
		**/
		virtual CAnySdeGeometry *Clone() = 0;

		/*!
		*
		**/
		virtual void MoveTo(const CGeoPoint<double> &pos) = 0;
		/*!
		*
		**/
		virtual void Move(const CGeoPoint<double> &offset)= 0;

		/*!
		*2015/7/20: change parameter CGeoPoint<double> to CGeoRect<double>
		**/
		virtual CGeoPoint<double> FindPtInGeometry(const CGeoRect<double> &rect) = 0;

		/*!
		*
		**/
		virtual void AddPtInGeometry(const CGeoPoint<double> &pt,const CGeoPoint<double> &pt_new)= 0;
		/*!
		*
		**/
		virtual void DeletePtInGeometry(const CGeoPoint<double> &pt)= 0;
		/*!
		*20170301
		**/
		virtual void DeletePtInGeometryByExtent(const CGeoRect<double> &rect)= 0;
		/*!
		*
		**/
		virtual void UpdateLastPtInGeometry(const CGeoPoint<double> &pt)= 0;
		/*!
		*
		**/
		virtual void UpdateLastPtXYInGeometry(const CGeoPoint<double> &pt, bool updateX, bool updateY)= 0;
		/*!
		*
		**/
		virtual void UpdatePtInGeometry(const CGeoPoint<double> &pt,const CGeoPoint<double> &pt_new)= 0;
	private:
		//
		// MySQL functions
		//
		/*!
		*
		**/
		inline bool no_data(const char *cur_data, unsigned long data_amount) const;

		/*!
		*
		**/
		static void get_point(double *x, double *y, const char *data);

		/*!
		*
		**/
		static void get_points(const char *data, int points_size, std::vector<CGeoPoint<double> > &coords);

		/*!
		*
		**/
		bool is_line_closed(const char *data);

		/*!
		  Get most bounding rectangle (mbr) for X points

		  SYNOPSIS
			get_mbr_for_points()
			mbr			MBR (store rectangle here)
			points		Number of points
			data		Packed data
			offset		Offset between points

		  RETURN
			0	Wrong data
			#	end of data
		*/
		const char *get_mbr_for_points(MBR *mbr, const char *data, unsigned int offset) const;

		/*!
		*
		**/
		double get_line_length(char *&data);
				
		/*!
		*
		**/
		double get_poly_perimeter(char *&data);

		/*!
		*
		**/
		double get_poly_area(char *&data);

	public:
		// unqiue idx, corresponding to Geometry Table
		long m_idx;
		// WKB type
		unsigned int m_wkType;
		// operation
		unsigned short m_opType;
		// host layer
		CAnySdeLayer *m_layer;
		// geometry version
		int m_version;
	protected:
		// WKB encoding
		char *m_data;
		char *m_data_end;
	};
}

#endif
