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

// ��Բ��ר��
#define  E_SEGM   45 
// ����������ר��
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
		 *	�����־��txt��˳��CGMContext--CGMPicture--CGMPrimList--CGMPrimitive��
		**/
		void WriteDataToASCIIFile(FILE *out);

		/*!
		 *	���������ԣ���ɫ����ȡ����Σ�
		 * @Target  ĳͼԪ
		**/
		void SetLineAttributes(CCGMPrimitive & Target);

		/*!
		*	�����ı�
		* @isAppend  �Ƿ�ΪAppendTextͼԪ
		* @deltaWeight  delta���
		* @deltaHeight   delta�߶�
		* @posX	x����
		* @posY	y����
		* @isFinal	 �Ƿ����
		* @strText  �ı�����
		**/
		void Text(bool isAppend, double deltaWeight, double deltaHeight, double posX, double posY, bool isFinal, string &strText);

		/*!
		 *	����ͼԪ����������
		**/
		void SetFillAndLine ( CCGMPrimitive &Target);

		/*!
		*	��������
		* @x1  ��1���x����
		* @y1  ��1���y����
		* @x2	��4���x����
		* @y2	��4���y����
		**/
		void Rectangle(double x1,double y1,double x2,double y2);

		/*!
		*	��������
		* @points  �㼯��
		* @pointNum  ������
		**/
		void Polyline(/*double **/std::vector<double> & points, int pointNum);

		/*!
		*	���������
		* @points  �㼯��
		* @pointNum  ������
		**/
		void Polygon(/*double **/std::vector<double> points, int pointNum);

		/*!
		*	�������
		* @points  �㼯��
		* @pointNum  ������
		**/
		void marker(/*double **/std::vector<double> points, int pointNum );

		/*!
		*	������Բ
		* @cx  Բ�ĵ�x����
		* @cy  Բ�ĵ�y����
		* @x1  ��1������ֱ����x����
		* @y1  ��1������ֱ����y����
		* @x2	��2������ֱ����x����
		* @y2	��2������ֱ����y����
		**/
		void Ellipse(double cx,double cy,double x1,double y1,double x2,double y2);

		/*!
		*	������Բ��
		* @cx  Բ�ĵ�x����
		* @cy  Բ�ĵ�y����
		* @x1  ��1������ֱ����x����
		* @y1  ��1������ֱ����y����
		* @x2	��2������ֱ����x����
		* @y2	��2������ֱ����y����
		* @sx  ��ʼ������deltaX
		* @sy  ��ʼ������deltaY
		* @ex	����������deltaX
		* @ey	����������deltaY
		* @closed  �Ƿ�պ�
		**/
		void elliparc(double cx,double cy,double x1,double y1,double x2,double y2,double sx,double sy,double ex,double ey, int closed);

		/*!
		*	��������������
		* @points  �㼯��
		* @pointNum  ������
		**/
		void DisjtLine(/*double **/std::vector<double>points, int pointNum );

		/*!
		*	����Բ����3�㣩
		* @x1  ��ʼ���x����
		* @y1  ��ʼ���y����
		* @x2	�м���x����
		* @y2	�м���y����
		* @x3	�������x����
		* @y3	�������y����
		* @closed	�Ƿ�պ�
		**/
		void Circarc(double x1,double y1,double x2,double y2,double x3,double y3,int closed);

		/*!
		*	����Բ�������ģ�
		* @cx  Բ�ĵ�x����
		* @cy  Բ�ĵ�y����
		* @sx	��ʼ������x����
		* @sy	��ʼ������y����
		* @ex	����������x����
		* @ey	����������y����
		* @r  	�뾶
		* @closed	�Ƿ�պ�
		**/
		void Circarc(double cx,double cy,double sx,double sy,double ex,double ey,double r,int closed);

		/*!
		*	������Ԫ����
		* @x1  �յ�P��x����
		* @y1  �յ�P��y����
		* @x2	�յ�Q��x����
		* @y2	�յ�Q��y����
		* @x3	�յ�R��x����
		* @y3	�յ�R��y����
		* @c	    ��ɫ����
		* @C_number	��Ԫ����=����*����
		* @iw  	����
		* @ih	����
		**/
		void CellArray(double x1,double y1,double x2 ,double y2, double x3 ,double y3, int* c, int C_number, int iw, int ih);

		/*!
		*	����Bezier����
		* @t  �Ƿ�����
		* @points  �㼯��
		* @pointNum  ������
		**/
		void Bezier(int t, /*double **/std::vector<double>points,int pointNum );

		/*!
		*	��Poly���͵�ͼԪ���ؽ�PrimList
		* @target  PolyͼԪ
		* @points  �㼯��
		* @pointNum  ������
		**/
		void AnyPoly(CCGMPrimitivePoly & target, /*double **/std::vector<double> points, int pointNum);
	
	public:

		// ͼԪ�б�
		CCGMPrimList * primList;

		// ������
		CCGMContext *m_cgm;

		// ����
		CFont *defaultFont; // = new Font("Courier",Font.PLAIN,12);

		// ��һ�ı���AppendTextͼԪר�ã�
		CCGMText *previousText;
	};


#endif 