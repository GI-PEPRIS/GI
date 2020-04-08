// anycgmreader.h: interface for the CCGMReader class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __ANYBRIDGE__CGMREADER_H_
#define __ANYBRIDGE__CGMREADER_H_

class  CCGM;
class  CCGMContext;

#include "../gis/anyshpbasic.h"
#include "../gis/anyshpwriter.h"
using namespace AnyBridge;

#include <vector>
#include <map>
using namespace std;

#define COLOR_SELECTION_MODE_DIRECT 0 
#define COLOR_SELECTION_MODE_DIRECT_ALPHA 1 
#define COLOR_SELECTION_MODE_INDEXED 2 

union int_float_bits
{
	int int_bits;
	//int32_t int_bits;
	float float_bits;
};

	/*!
	*
	*/
	class   ANYBRIDGE_CLASS CCGMReader  
	{
	public:
		
		/*!
		*	
		*/
		CCGMReader();
		
		/*!
		*	
		*/
		CCGMReader(FILE* in, CCGMContext *m_cgm);
				
		/*!
		*	
		*/
		~CCGMReader();

	public:
				
		 /*!
		 *	读2个字节（无符号整数）
		 **/
		bool ReadUnsignedShort(unsigned short &num);
				
		/*!
		*	跳过读取
		*/
		void skip();
				
		/*!
		*	读取VDC
		*/
		double ReadVdc();
				
		/*!
		*	读取Type
		*/
		int ReadType();
				
		/*!
		*	读取String
		*/
		string ReadString(int len);
				
		/*!
		*	读取String
		*/
		string ReadString();
				
		/*!
		*	读取精度
		*/
		int ReadPrec();
				
		/*!
		*	读取点，返回点数
		*/
		int ReadPoints(bool flags/*, double *& pPointsArray*/);

		/*!
		*	
		**/
		bool ExportToSHPFiles(string strGeoType);
		
		/*!
		 *	读取分界符, Class-0
		*/
		void ReadDelimiter(int elementID);

		/*!
		*	读取属性元素, Class-1
		*/
		void ReadMetaFileDiscription(int elementID);

		/*!
		*	读取图片描述符元素, Class-2
		*/
		void ReadPictureDiscription(int elementID);

		/*!
		*	读取控制元素, Class-3
		*/
		void ReadControlElements(int elementID);
	
		/*!
		*	读取图元, Class-4
		*/
		void ReadGraphicPrimitives(int elementID);
	
		/*!
		*	读取属性, Class-5
		*/
		void ReadAttributeElements(int elementID);
								
		/*!
		 *	读取Escape元素, Class-6
		*/
		void ReadEscapeElements(int elementID);

		/*!
		*	读取外部元素, Class-7
		*/
		void ReadExternalElements(int elementID);
				
		/*!
		*	读取字节
		*/
		BYTE ReadByte();

		/*!
		*	读取int
		*/
		int ReadInt(int prec);
				
		/*!
		*	读取int
		*/
		int ReadInt();
				
		/*!
		*	读取float
		*/
		double ReadFloat();
				
		/*!
		*	读取元素
		*/
		bool ReadElement();
				
		/*!
		 *	读取颜色的R、G、B值
		**/
		double ReadColorComp();
				
		/*!
		*	读取颜色
		*/
		int ReadColor(int m_colorMode);
		
		/*!
		*	读取颜色
		*/
		int ReadColor();

		/*!
		*	读取参数长度
		*/
		int ReadParamLen();
	 		
	public:

		// 点集
		//double *points; 
		std::vector<double> points;

		// 参数长度
		int m_paramLen;

		// SHP Writer
		CAnyShpWriter* shpWriter;

		
		// SHP文件名（Polyline型）
		anystring m_strPolylineFileName;
		
		// SHP文件名（Polygon型）
		anystring m_strPolygonFileName;
		
		// SHP文件名（Marker型）
		anystring m_strMarkerFileName;

		// 坐标相关
		double m_xMin;
		double m_yMin;
		double m_xMax;
		double m_yMax;

		//Polyline相关
		int m_polylineParts;
		int* m_polylinePoints;
		int* m_polylinePartOffsets;
		int* m_polylineSize;
		double** m_polylineXCoords;
		double** m_polylineYCoords;

		//Polygon相关
		int m_polygonParts;
		int* m_polygonPoints;
		int* m_polygonPartOffsets;
		int* m_polygonSize;
		double** m_polygonXCoords;
		double** m_polygonYCoords;

		//Marker相关
		int m_markerParts;
		int* m_markerPoints;
		int* m_markerPartOffsets;
		int* m_markerSize;
		double** m_markerXCoords;
		double** m_markerYCoords;

		// Begin MetaFile, Class-0, ElementID-1
		string m_beginMetafile;
		// Begin Picture, Class-0, ElementID-3
		string m_strBeginPicture;
		// Metafile Version, Class-1, ElementID-1
		int m_metafileVersion;
		// Metafile Description, Class-1, ElementID-2
		string m_metafileDescription;
		// VDC Type, Class-1, ElementID-3
		bool b_vdcIsInt ;
		// Integer Precision, Class-1, ElementID-4
		int intPrec ;
		// Real Precision, Class-1, ElementID-5
		int m_realPrec_P1;
		int m_realPrec_P2;
		int m_realPrec_P3;
		string m_strRealPrec;
		// Index Precision, Class-1, ElementID-6
		int indexPrec ;
		// Color Precision, Class-1, ElementID-7
		int colorPrec ;
		// Color index precision, Class-1, ElementID-8
		int colorIndexPrec ;
		// Maximum Color Index, Class-1, ElementID-9
		int maxColorIndex;
		// Metafile Element List, Class-1, ElementID-11
		int elementNum;
		int index_1;
		int index_2;
		// Character Set List, Class-1, ElementID-14
		int m_characterSetList;
		string m_strCharacterSetList1;
		string m_strCharacterSetList2;
		// Character Coding Announcer, Class-1, ElementID-15
		int m_characterCodingAnnouncer;
		string m_strCharacterCodingAnnouncer;
		// Colour Selection Mode, Class-2, ElementID-2
		string m_strColourSelectionMode;
		// VDC integer precision, Class-3, ElementID-1
		int vdcIntPrec ;
		// VDC Real precision, Class-3, ElementID-2
		int vdcRealPrec ;
		int vdcRealType ;
		// Color Table, Class-5, ElementID-34
		double m_r, m_g, m_b;
		//参数是否结束
		bool b_paramContinued;
		static  int enumPrec ;

		//写文件
		FILE * out;
		// 读文件
		FILE * in;

		// Color Table数组
		map<int, string> m_mapColorTable;

		// 图元数组
		std::vector<string> m_vecPrimitive;

		// Polyline宽度
		std::vector<double> m_vecPolylineWidth;
		// Polyline颜色
		map<int, string> m_mapPolylineColor;
		//std::vector<string> m_vecPolylineColor;
		// Polyline类型
		std::vector<string> m_vecPolylineType;

		// Polygon宽度
		std::vector<double> m_vecPolygonWidth;
		// Polygon边框颜色
		map<int, string> m_mapPolygonEdgeColor;
		//std::vector<string> m_vecPolygonEdgeColor;
		// Polygon填充色
		map<int, string> m_mapPolygonFillColor;
		//std::vector<double> m_vecPolygonFillColor;

		// Marker宽度
		std::vector<double> m_vecMarkerWidth;
		// Marker颜色
		map<int, string> m_mapMarkerColor;
		//std::vector<string> m_vecMarkerColor;
		// Marker类型
		std::vector<string> m_vecMarkerType;

		// 线宽
		double lineWidth;
		std::vector<double> lineWidthVector; //add by wrq
		// 线型
		int lineType;
		std::vector<int> lineTypeVector;
		// 线色
		int lineColor;
		std::vector<int> lineColorVector;
		// 点类型
		int MarkerType;
		std::vector<int> MarkerTypeVector;
		// 点大小
		double MarkerSize;
		std::vector<double> MarkerSizeVector;
		// 点颜色
		int markerColor;
		std::vector<int> markerColorVector;
		// 边宽
		double EdgeWidth;
		std::vector<double> EdgeWidthVector;
		// 边框颜色
		int EdgeColor;
		std::vector<int> EdgeColorVector;
		// 填充色
		int m_fillColor;
		std::vector<int> m_fillColorVector;

		CCGM  *ContextOrPicture;
		int m_colorTable[258]; 
		CCGMContext *m_cgm;

		int m_colorMode ;

		int  m_colorRed1;
		int  m_colorGreen1;
		int  m_colorBlue1;
		int  m_colorRed2;
		int  m_colorGreen2;
		int  m_colorBlue2;

		// Text等图元内容
		string strText;

		//add by wrq
		string LineWidthSpecificationMode;
		string MarkerSizeSpecificationMode;
		string EdgeWidthSpecificationMode;

private:
		/*!
		*	字节逐位对调
		*/
		void ExchangeByteOrder( void *, int len );

		float intBitsToFloat(double x); //add by wrq

		string double2string(double i_double);// add by wrq
	};


#endif