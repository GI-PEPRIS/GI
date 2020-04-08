// anycgmprimitive.h: interface for the CCGMPrimitive class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __ANYBRIDGE__CGMPRIMITIVE_H_
#define __ANYBRIDGE__CGMPRIMITIVE_H_

#include <string>
using namespace std;

#define    H5  0.5d 
#define    H6  0.6d 

#include <vector>
using namespace std;

#include "any/base/anystl.h" //vs2015, herman

//////////////////////////////////////////////////////////////////////
// CCGMPrimitive��ͼԪ
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class   CCGMPrimitive  
	{
	public:

		/*!
		*	
		**/
		CCGMPrimitive();

		/*!
		*	
		**/
		~CCGMPrimitive()
		{
		}

	public:

		/*!
		*	�����־��txt��˳��CGMContext--CGMPicture--CGMPrimList--CGMPrimitive��
		**/
		virtual void WriteDataToASCIIFile( FILE *out);

		/*!
		*	���ñպ�
		**/
		void SetClosed() 
		{
			closed = true;
		}
		int points;
		//double * pointSet;
		std::vector<double>pointSet;
		double x ;
		double y ;
		double width ;
		double height ;
		//	double Angle=0;

		// ��ɫ
 		int lineColor ;
		// �߿�
		double lineWidth ;
		// ����
		int lineType ;
		// ������
		int MarkerType;
		string strMarkerType;
		// ���С
		double MarkerSize;
		// ����ɫ
		int markerColor;
		// �߿�
		double EdgeWidth;
		// �߿���ɫ
		int EdgeColor;
		// ���ɫ
		int m_fillColor ; 

		// �ڲ����
		int IntStyle ;
		// TextͼԪר��
		bool noclip ;
		// �Ƿ�պ�
		bool closed ;
		// ͼԪID
		int m_elementID;
	};

//////////////////////////////////////////////////////////////////////
// CFont
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class   CFont  
	{
	public:

		/*!
		*	
		**/
		CFont()
		{
			this->lfBold = 0;
			this->lfItalic = 0;
			this->lfStrikeOut = 0;
			this->lfUnderline = 0;
		}

		/*!
		*	
		**/
		~CFont()
		{

		}

		// ��������
		string name;
		// б��
		unsigned char lfItalic; 
		// �»���
		unsigned char lfUnderline; 
		// ɾ����
		unsigned char lfStrikeOut; 
		// ����
		unsigned char lfBold;
		// �����С
		int size;
	};

//////////////////////////////////////////////////////////////////////
// CCGMRectangle���̳���CCGMPrimitive
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class    CCGMRectangle : public CCGMPrimitive  
	{
	public:

		/*!
		*	
		**/
		CCGMRectangle()
		{
			m_elementID = 6;
		}

		/*!
		*	
		**/
		CCGMRectangle(double x1,double y1,double x2,double y2)
		{
			x =  min(x1,x2);
			y =  min(y1,y2);
			height =  abs(y2-y1);
			width =  abs(x2-x1);
			m_elementID = 6;
		}

		/*!
		*	
		**/
		~CCGMRectangle()
		{

		}
	};


//////////////////////////////////////////////////////////////////////
// CCGMOval���̳���CCGMPrimitive
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class   CCGMOval : public CCGMPrimitive  
	{
	public:

		/*!
		*	
		**/
		virtual void WriteDataToASCIIFile( FILE *out);

		/*!
		*	
		**/
		CCGMOval(double cx,double cy,double r,double r2)
		{
			x = cx;
			y = cy;
			width = fabs(r);
			height = fabs(r2);
			m_elementID = 3;
		}

		/*!
		*	
		**/
		~CCGMOval()
		{

		}
	};


//////////////////////////////////////////////////////////////////////
// CCGMText���̳���CCGMPrimitive
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class   CCGMText : public CCGMPrimitive  
	{
	public:

		/*!
		*	
		**/
		CCGMText(double ex, double ey, double cx, double cy,double h,double a, double s, double spacing,string &str,int horA, int vertA, int path);

		/*!
		*	
		**/
		~CCGMText()
		{

		}

	public:

		/*!
		*	�����־��txt��˳��CGMContext--CGMPicture--CGMPrimList--CGMPrimitive��
		**/
		virtual void WriteDataToASCIIFile( FILE *out);

		/*!
		*	��������
		**/
		void SetFont(CFont &f);

		// �ı�����
		string Content;
		// ˮƽ����
		int textAlignHor;
		// �ַ�����ϵ��
		double characterExpansion;
		// �ַ����
		double characterSpacing;
		// �ַ��߶�
		double characterHeight;
		double as ,ac ,aa ;
		double extW ,extH ;
		int textPath;
		// �ַ�����
		double charOri;
		// �ַ�б��
		double charSlant;
		// �Ƿ����»���
		bool underlined;
		// �Ƿ�ѡ��
		bool selected;
		// ��������
		string fontname;
		// б��
		unsigned char lfItalic; 
		// �»���
		unsigned char lfUnderline; 
		// ɾ����
		unsigned char lfStrikeOut; 
		// ����
		unsigned char lfBold;
		// �����С
		int FontSize;
		int xe  ;
		int ye  ;
		// ��һ�ı�
		CCGMText *Previous;
	};


#endif 