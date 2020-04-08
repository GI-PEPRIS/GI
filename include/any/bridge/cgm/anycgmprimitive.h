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
// CCGMPrimitive，图元
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
		*	输出日志到txt（顺序：CGMContext--CGMPicture--CGMPrimList--CGMPrimitive）
		**/
		virtual void WriteDataToASCIIFile( FILE *out);

		/*!
		*	设置闭合
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

		// 线色
 		int lineColor ;
		// 线宽
		double lineWidth ;
		// 线型
		int lineType ;
		// 点类型
		int MarkerType;
		string strMarkerType;
		// 点大小
		double MarkerSize;
		// 点颜色
		int markerColor;
		// 边宽
		double EdgeWidth;
		// 边框颜色
		int EdgeColor;
		// 填充色
		int m_fillColor ; 

		// 内部风格
		int IntStyle ;
		// Text图元专用
		bool noclip ;
		// 是否闭合
		bool closed ;
		// 图元ID
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

		// 字体名称
		string name;
		// 斜体
		unsigned char lfItalic; 
		// 下划线
		unsigned char lfUnderline; 
		// 删除线
		unsigned char lfStrikeOut; 
		// 粗体
		unsigned char lfBold;
		// 字体大小
		int size;
	};

//////////////////////////////////////////////////////////////////////
// CCGMRectangle，继承自CCGMPrimitive
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
// CCGMOval，继承自CCGMPrimitive
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
// CCGMText，继承自CCGMPrimitive
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
		*	输出日志到txt（顺序：CGMContext--CGMPicture--CGMPrimList--CGMPrimitive）
		**/
		virtual void WriteDataToASCIIFile( FILE *out);

		/*!
		*	设置字体
		**/
		void SetFont(CFont &f);

		// 文本内容
		string Content;
		// 水平居中
		int textAlignHor;
		// 字符缩放系数
		double characterExpansion;
		// 字符间距
		double characterSpacing;
		// 字符高度
		double characterHeight;
		double as ,ac ,aa ;
		double extW ,extH ;
		int textPath;
		// 字符方向
		double charOri;
		// 字符斜率
		double charSlant;
		// 是否有下划线
		bool underlined;
		// 是否选中
		bool selected;
		// 字体名称
		string fontname;
		// 斜体
		unsigned char lfItalic; 
		// 下划线
		unsigned char lfUnderline; 
		// 删除线
		unsigned char lfStrikeOut; 
		// 粗体
		unsigned char lfBold;
		// 字体大小
		int FontSize;
		int xe  ;
		int ye  ;
		// 上一文本
		CCGMText *Previous;
	};


#endif 