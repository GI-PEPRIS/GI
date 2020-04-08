// anycgmprimitivepoly.h: interface for the CCGMPrimitivePoly class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __ANYBRIDGE_CGMPRIMITIVEPOLY_H__
#define __ANYBRIDGE_CGMPRIMITIVEPOLY_H__

#include "anycgmprimitive.h"

//////////////////////////////////////////////////////////////////////
// CCGMPrimitivePoly£¬¼Ì³Ð×ÔCCGMPrimitive
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class   CCGMPrimitivePoly : public CCGMPrimitive  
	{
	public:
		CCGMPrimitivePoly();
		virtual ~CCGMPrimitivePoly();

	public:
		virtual void WriteDataToASCIIFile( FILE *out);
		
		double * xpoints;
		double * ypoints;
		int  * xpoints1;
		int  * ypoints1;
		
		int lw; //=1;
		double previousW; //=0;
		double previousH; //=0;
	};


//////////////////////////////////////////////////////////////////////
// CCGMMarker£¬¼Ì³Ð×ÔCCGMPrimitivePoly
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class   CCGMMarker : public CCGMPrimitivePoly  
	{
	public:
		CCGMMarker()
		{
			m_elementID = 2;
		}

		CCGMMarker(int pnts ) 
		{
			xpoints = new double[pnts];
			ypoints = new double[pnts];
			//pointSet = new double[pnts];
			pointSet.clear();
			points=pnts;
			m_elementID = 2;
		}
		~CCGMMarker()
		{

		}
	};


//////////////////////////////////////////////////////////////////////
// CCGMPolygon£¬¼Ì³Ð×ÔCCGMPrimitivePoly
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class CCGMPolygon : public CCGMPrimitivePoly  
	{
	public:
		CCGMPolygon();
		CCGMPolygon(int pnts)
		{
			//int p1 = pnts+1;
			//xpoints=new double[pnts];
			//ypoints=new double[pnts];
			//xpoints1=new int[p1];
			//ypoints1=new int[p1];
			//points  =pnts;
			//p = (closed = c) ? p1 : pnts;
			
			//pointSet = new double[pnts];
			pointSet.clear();
			points = pnts;
			m_elementID = 4;
		}
		 ~CCGMPolygon()
		 {

		 }

		void SetClosed() 
		{
			if (!closed) 
				p++;
			closed = true;
		}

	public:
		int p;
		static   double HATCHWIDTH;
		static  int LINE_HATCH_SIZE;
		static  int LINE_POINT_SIZE;
		static   int LINE_GAP_SIZE;

	};


//////////////////////////////////////////////////////////////////////
// CCGMPolyline£¬¼Ì³Ð×ÔCCGMPrimitivePoly
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class   CCGMPolyline : public CCGMPrimitivePoly  
	{
		public:
			CCGMPolyline();
			CCGMPolyline(int pnts)
			{
				//pointSet = new double[pnts];
				pointSet.clear();
				points = pnts;
				m_elementID = 30;
			}
			~CCGMPolyline()
			{
			}

		public:
	
	};


//////////////////////////////////////////////////////////////////////
// CCGMDisjtLine£¬¼Ì³Ð×ÔCCGMPrimitivePoly
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class   CCGMDisjtLine  : public CCGMPrimitivePoly
	{
	public:
		CCGMDisjtLine();
		CCGMDisjtLine( int pnts )
		{
			xpoints = new double[pnts];
			ypoints = new double[pnts];
			xpoints1 = new int[pnts];
			ypoints1 = new int[pnts];
			points = pnts;
			m_elementID = 1;
		}
		 ~CCGMDisjtLine()
		 {

		 }
	};


#endif 