// anycgmpicture.h: interface for the CCGMPicture class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __ANYBRIDGE__CGM_PICTURE_H_
#define __ANYBRIDGE__CGM_PICTURE_H_

#include <string>
#include <vector>
using namespace std;

#include "anycgm.h"

class CCGMContext;
class CCGMPrimitive;
class CCGMPrimList;
class CFont;
class CCGMText;
class CCGMPrimitivePoly;
class CImage;

// 椭圆弧专用
#define  E_SEGM   45 
// 贝塞尔曲线专用
#define  B_SEGM1  8 
#define  B_SEGM2  4 
//////////////////////////////////////////////////////////////////////
// CCGMPicture
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class  CCGMPicture  : public CCGM
	{
	public:

		/*!
		 *	
		**/
		CCGMPicture( CCGMContext & mf, string & name );	 

		/*!
		 *	
		**/
		~CCGMPicture();

	public:

		/*!
		 *	输出日志到txt（顺序：CGMContext--CGMPicture--CGMPrimList--CGMPrimitive）
		**/
		void WriteDataToASCIIFile(FILE *out);

		/*!
		 *	设置线属性（颜色、宽度、线形）
		 * @Target  某图元
		**/
		void SetLineAttributes(CCGMPrimitive & Target);

		/*!
		*	创建文本
		* @isAppend  是否为AppendText图元
		* @deltaWeight  delta宽度
		* @deltaHeight   delta高度
		* @posX	x坐标
		* @posY	y坐标
		* @isFinal	 是否结束
		* @strText  文本内容
		**/
		void Text(bool isAppend, double deltaWeight, double deltaHeight, double posX, double posY, bool isFinal, string &strText);

		/*!
		 *	设置图元的填充和线形
		**/
		void SetFillAndLine ( CCGMPrimitive &Target);

		/*!
		*	创建矩形
		* @x1  第1点的x坐标
		* @y1  第1点的y坐标
		* @x2	第4点的x坐标
		* @y2	第4点的y坐标
		**/
		void Rectangle(double x1,double y1,double x2,double y2);

		/*!
		*	创建折线
		* @points  点集合
		* @pointNum  点数量
		**/
		void Polyline(/*double **/std::vector<double> & points, int pointNum);

		/*!
		*	创建多边形
		* @points  点集合
		* @pointNum  点数量
		**/
		void Polygon(/*double **/std::vector<double> points, int pointNum);

		/*!
		*	创建标记
		* @points  点集合
		* @pointNum  点数量
		**/
		void marker(/*double **/std::vector<double> points, int pointNum );

		/*!
		*	创建椭圆
		* @cx  圆心的x坐标
		* @cy  圆心的y坐标
		* @x1  第1条共轭直径的x坐标
		* @y1  第1条共轭直径的y坐标
		* @x2	第2条共轭直径的x坐标
		* @y2	第2条共轭直径的y坐标
		**/
		void Ellipse(double cx,double cy,double x1,double y1,double x2,double y2);

		/*!
		*	创建椭圆弧
		* @cx  圆心的x坐标
		* @cy  圆心的y坐标
		* @x1  第1条共轭直径的x坐标
		* @y1  第1条共轭直径的y坐标
		* @x2	第2条共轭直径的x坐标
		* @y2	第2条共轭直径的y坐标
		* @sx  起始向量的deltaX
		* @sy  起始向量的deltaY
		* @ex	结束向量的deltaX
		* @ey	结束向量的deltaY
		* @closed  是否闭合
		**/
		void elliparc(double cx,double cy,double x1,double y1,double x2,double y2,double sx,double sy,double ex,double ey, int closed);

		/*!
		*	创建不相连折线
		* @points  点集合
		* @pointNum  点数量
		**/
		void DisjtLine(/*double **/std::vector<double>points, int pointNum );

		/*!
		*	创建圆弧（3点）
		* @x1  起始点的x坐标
		* @y1  起始点的y坐标
		* @x2	中间点的x坐标
		* @y2	中间点的y坐标
		* @x3	结束点的x坐标
		* @y3	结束点的y坐标
		* @closed	是否闭合
		**/
		void Circarc(double x1,double y1,double x2,double y2,double x3,double y3,int closed);

		/*!
		*	创建圆弧（中心）
		* @cx  圆心的x坐标
		* @cy  圆心的y坐标
		* @sx	起始向量的x坐标
		* @sy	起始向量的y坐标
		* @ex	结束向量的x坐标
		* @ey	结束向量的y坐标
		* @r  	半径
		* @closed	是否闭合
		**/
		void Circarc(double cx,double cy,double sx,double sy,double ex,double ey,double r,int closed);

		/*!
		*	创建单元阵列
		* @x1  拐点P的x坐标
		* @y1  拐点P的y坐标
		* @x2	拐点Q的x坐标
		* @y2	拐点Q的y坐标
		* @x3	拐点R的x坐标
		* @y3	拐点R的y坐标
		* @c	    颜色数组
		* @C_number	单元格数=行数*列数
		* @iw  	列数
		* @ih	行数
		**/
		void CellArray(double x1,double y1,double x2 ,double y2, double x3 ,double y3, int* c, int C_number, int iw, int ih);

		/*!
		*	创建Bezier曲线
		* @t  是否连续
		* @points  点集合
		* @pointNum  点数量
		**/
		void Bezier(int t, /*double **/std::vector<double>points,int pointNum );

		/*!
		*	将Poly类型的图元加载进PrimList
		* @target  Poly图元
		* @points  点集合
		* @pointNum  点数量
		**/
		void AnyPoly(CCGMPrimitivePoly & target, /*double **/std::vector<double> points, int pointNum);
	
	public:

		// 图元列表
		CCGMPrimList * primList;

		// 上下文
		CCGMContext *m_cgm;

		// 字体
		CFont *defaultFont; // = new Font("Courier",Font.PLAIN,12);

		// 上一文本（AppendText图元专用）
		CCGMText *previousText;
	};


#endif 