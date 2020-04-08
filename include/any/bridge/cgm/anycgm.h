// anycgm.h: interface for the CCGM class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __ANYBRIDGE_CGM_H__
#define __ANYBRIDGE_CGM_H__

#include <string>
using namespace std; 

// Refer to EXPORT & IMPORT
#include "..\anybridge.h"

typedef int Color;

	/*!
	*
	*/
	class CCGM  
	{
		public:
			void VdcExt(double x1,double y1,double x2,double y2);

			CCGM();
	 
			virtual ~CCGM();

		public:
			string name;
			double  width;
			double  height;
			double  ax, bx, ay, by;
			int  EdgeWidthMode;
			int  LineWidthMode;
			int MarkerSizeMode;
			bool EdgesVisible;
			int EdgeType;
			// �߿�
			double lineWidth;
		// ����
			int lineType;
			// ��ɫ
			Color lineColor;
			// ������, Class-5, ElementID-6
			int MarkerType;
			string strMarkerType;
			// ���С
			double MarkerSize;
			// ����ɫ
			Color markerColor;
			// �߿�
			double EdgeWidth;
			// �߿���ɫ
			Color EdgeColor;
			// ���ɫ
			Color m_fillColor;

			int  InteriorStyle;
			int  HatchIndex;
			Color   backColor;
			Color   textColor;
			double  characterHeight;
			double  characterExpansion;
			double  characterSpacing;
			int  	  textPath;
			double  charOri;
			double  charSlant;
			int     fontIndex;
			int     textAlignVert;
			int	  textAlignHor;
			bool m_finishedLoading;
	};

#endif 
