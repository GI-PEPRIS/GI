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
		 *	��2���ֽڣ��޷���������
		 **/
		bool ReadUnsignedShort(unsigned short &num);
				
		/*!
		*	������ȡ
		*/
		void skip();
				
		/*!
		*	��ȡVDC
		*/
		double ReadVdc();
				
		/*!
		*	��ȡType
		*/
		int ReadType();
				
		/*!
		*	��ȡString
		*/
		string ReadString(int len);
				
		/*!
		*	��ȡString
		*/
		string ReadString();
				
		/*!
		*	��ȡ����
		*/
		int ReadPrec();
				
		/*!
		*	��ȡ�㣬���ص���
		*/
		int ReadPoints(bool flags/*, double *& pPointsArray*/);

		/*!
		*	
		**/
		bool ExportToSHPFiles(string strGeoType);
		
		/*!
		 *	��ȡ�ֽ��, Class-0
		*/
		void ReadDelimiter(int elementID);

		/*!
		*	��ȡ����Ԫ��, Class-1
		*/
		void ReadMetaFileDiscription(int elementID);

		/*!
		*	��ȡͼƬ������Ԫ��, Class-2
		*/
		void ReadPictureDiscription(int elementID);

		/*!
		*	��ȡ����Ԫ��, Class-3
		*/
		void ReadControlElements(int elementID);
	
		/*!
		*	��ȡͼԪ, Class-4
		*/
		void ReadGraphicPrimitives(int elementID);
	
		/*!
		*	��ȡ����, Class-5
		*/
		void ReadAttributeElements(int elementID);
								
		/*!
		 *	��ȡEscapeԪ��, Class-6
		*/
		void ReadEscapeElements(int elementID);

		/*!
		*	��ȡ�ⲿԪ��, Class-7
		*/
		void ReadExternalElements(int elementID);
				
		/*!
		*	��ȡ�ֽ�
		*/
		BYTE ReadByte();

		/*!
		*	��ȡint
		*/
		int ReadInt(int prec);
				
		/*!
		*	��ȡint
		*/
		int ReadInt();
				
		/*!
		*	��ȡfloat
		*/
		double ReadFloat();
				
		/*!
		*	��ȡԪ��
		*/
		bool ReadElement();
				
		/*!
		 *	��ȡ��ɫ��R��G��Bֵ
		**/
		double ReadColorComp();
				
		/*!
		*	��ȡ��ɫ
		*/
		int ReadColor(int m_colorMode);
		
		/*!
		*	��ȡ��ɫ
		*/
		int ReadColor();

		/*!
		*	��ȡ��������
		*/
		int ReadParamLen();
	 		
	public:

		// �㼯
		//double *points; 
		std::vector<double> points;

		// ��������
		int m_paramLen;

		// SHP Writer
		CAnyShpWriter* shpWriter;

		
		// SHP�ļ�����Polyline�ͣ�
		anystring m_strPolylineFileName;
		
		// SHP�ļ�����Polygon�ͣ�
		anystring m_strPolygonFileName;
		
		// SHP�ļ�����Marker�ͣ�
		anystring m_strMarkerFileName;

		// �������
		double m_xMin;
		double m_yMin;
		double m_xMax;
		double m_yMax;

		//Polyline���
		int m_polylineParts;
		int* m_polylinePoints;
		int* m_polylinePartOffsets;
		int* m_polylineSize;
		double** m_polylineXCoords;
		double** m_polylineYCoords;

		//Polygon���
		int m_polygonParts;
		int* m_polygonPoints;
		int* m_polygonPartOffsets;
		int* m_polygonSize;
		double** m_polygonXCoords;
		double** m_polygonYCoords;

		//Marker���
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
		//�����Ƿ����
		bool b_paramContinued;
		static  int enumPrec ;

		//д�ļ�
		FILE * out;
		// ���ļ�
		FILE * in;

		// Color Table����
		map<int, string> m_mapColorTable;

		// ͼԪ����
		std::vector<string> m_vecPrimitive;

		// Polyline���
		std::vector<double> m_vecPolylineWidth;
		// Polyline��ɫ
		map<int, string> m_mapPolylineColor;
		//std::vector<string> m_vecPolylineColor;
		// Polyline����
		std::vector<string> m_vecPolylineType;

		// Polygon���
		std::vector<double> m_vecPolygonWidth;
		// Polygon�߿���ɫ
		map<int, string> m_mapPolygonEdgeColor;
		//std::vector<string> m_vecPolygonEdgeColor;
		// Polygon���ɫ
		map<int, string> m_mapPolygonFillColor;
		//std::vector<double> m_vecPolygonFillColor;

		// Marker���
		std::vector<double> m_vecMarkerWidth;
		// Marker��ɫ
		map<int, string> m_mapMarkerColor;
		//std::vector<string> m_vecMarkerColor;
		// Marker����
		std::vector<string> m_vecMarkerType;

		// �߿�
		double lineWidth;
		std::vector<double> lineWidthVector; //add by wrq
		// ����
		int lineType;
		std::vector<int> lineTypeVector;
		// ��ɫ
		int lineColor;
		std::vector<int> lineColorVector;
		// ������
		int MarkerType;
		std::vector<int> MarkerTypeVector;
		// ���С
		double MarkerSize;
		std::vector<double> MarkerSizeVector;
		// ����ɫ
		int markerColor;
		std::vector<int> markerColorVector;
		// �߿�
		double EdgeWidth;
		std::vector<double> EdgeWidthVector;
		// �߿���ɫ
		int EdgeColor;
		std::vector<int> EdgeColorVector;
		// ���ɫ
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

		// Text��ͼԪ����
		string strText;

		//add by wrq
		string LineWidthSpecificationMode;
		string MarkerSizeSpecificationMode;
		string EdgeWidthSpecificationMode;

private:
		/*!
		*	�ֽ���λ�Ե�
		*/
		void ExchangeByteOrder( void *, int len );

		float intBitsToFloat(double x); //add by wrq

		string double2string(double i_double);// add by wrq
	};


#endif