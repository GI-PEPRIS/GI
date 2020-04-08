/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYGEOP_SEGYFILE_H__
#define __ANYGEOP_SEGYFILE_H__

// refer to export/import macro
#include "anygeop.h"

// refer to STL
#include "any/base/anystl.h"
#include "any/base/anyfilebasic.h"
#include "any/base/anygeom.h"
using namespace AnyBase;

// namespace, geophysics
namespace AnyGeoP
{
	// forward class
	class CAnySegyLayer;

	/*!
	*
	**/
	class ANYGEOP_CLASS CAnySegyFile
	{
		// relatives
		friend class CAnySegyLayer;

	public:
		/*!
		* ���������������
		**/
		const static short	SEGY_SHORT = 3;
		const static short	SEGY_INT = 2;
		const static short	SEGY_IEEE = 5;
		const static short	SEGY_IBM = 1;

		/*!
		*
		**/
		struct HeadInfo
		{
			// head info
			long m_nTraceNum; // total trace number
			int m_nTraceLen; // trace lenth in bytes
			short m_nType; // segy type
			short m_nTracePt;		// sample number per trace
			long m_nInterval; // sample interval
			int m_lineNumber;	// in-line number
			int m_reelNumber; // CDP number

			/*!
			*
			**/
			HeadInfo() : m_nType(SEGY_IBM), m_nTraceLen(240), m_nTracePt(0), m_nTraceNum(1), m_nInterval(0), m_lineNumber(0), m_reelNumber(0)
			{
			}

			/*!
			*
			**/
			const HeadInfo &operator=(const HeadInfo &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_nTraceNum = other.m_nTraceNum; // total trace number
				m_nTraceLen = other.m_nTraceLen; // trace lenth in bytes
				m_nType = other.m_nType; // segy type
				m_nTracePt = other.m_nTracePt;		// sample number per trace
				m_nInterval = other.m_nInterval; // sample interval
				m_lineNumber = other.m_lineNumber;	// in-line number
				m_reelNumber = other.m_reelNumber; // CDP number

				return *this;
			}
		};

		/*!
		* ��������ͷ�ṹ
		**/
		struct TraceHead
		{
			int m_nOrder;						//�����
			short m_nPts;						//ÿ����������
			short m_nInterval;					//�������
			int m_nLineNo;						//�ߺ�
			int m_nCDPNo;						//����
			int m_nSourceCrdX;				//�������(source)
			int m_nSourceCrdY;				//�������(source)
			int m_nCrdType;					// ����ϵͳ����
			short m_nStartTime;				//������ʼʱ��
			short m_nEndTime;				//������ֹʱ��

			/*!
			*
			*/
			TraceHead() : m_nOrder(0), m_nPts(0), m_nInterval(0), m_nLineNo(0), m_nCDPNo(0), m_nSourceCrdX(0), m_nCrdType(1), \
				m_nSourceCrdY(0), m_nStartTime(0), m_nEndTime(0)
			{
			}

			/*!
			*
			**/
			const TraceHead &operator=(const TraceHead &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_nOrder = other.m_nOrder;				//�����
				m_nPts = other.m_nPts;						//ÿ����������
				m_nInterval = other.m_nInterval;		//�������
				m_nLineNo = other.m_nLineNo;			//�ߺ�
				m_nCDPNo = other.m_nCDPNo;			//����
				m_nSourceCrdX = other.m_nSourceCrdX;				//�������
				m_nSourceCrdY = other.m_nSourceCrdY;				//�������
				m_nCrdType = other.m_nCrdType;
				m_nStartTime = other.m_nStartTime;	//������ʼʱ��
				m_nEndTime = other.m_nEndTime;    // ��������ʱ��

				return *this;
			}
		};

		/*!
		*
		**/
		struct ProfileInfo
		{
			// default time/depth extent
			int m_defaultStart;
			int m_defaultEnd;

			// user's interesting extent
			int m_userStart;
			int m_userEnd;

			/*!
			*
			**/
			ProfileInfo() : m_defaultStart(0), m_defaultEnd(0), m_userStart(0), m_userEnd(0)
			{
			}

			/*!
			*
			**/
			const ProfileInfo &operator=(const ProfileInfo &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_defaultStart = other.m_defaultStart;
				m_defaultEnd = other.m_defaultEnd;
				m_userStart = other.m_userStart;
				m_userEnd = other.m_userEnd;

				return *this;
			}

			/*!
			*
			**/
			bool IsValidExtent()
			{
				return !(m_userStart < m_defaultStart || m_userStart > m_defaultEnd ||
					m_userEnd < m_userStart || m_userEnd > m_defaultEnd);
			}
		};

		/*!
		*
		**/
		struct SurveyInfo
		{
			int m_nLineNum;								// In Line��Ŀ
			int m_nCDPNum;								//Cross Line��Ŀ
			int m_nStartLine;								//In Line��ʼ���
			int m_nStartCDP;								//Cross Line��ʼ���
			short m_nLineIncrement;					//In Line��ż��	
			short m_nCDPIncrement;					//Cross Line��ż��
			float m_fOrientation;							//In Line��λ��
			float m_fDirection;								//Cross Line�����In Line�ķ�λ��
			float m_fOrgX;									//�����ʼ����
			float m_fOrgY;									//�����ʼ����
			float m_fLineSpace;							//In Line��ؼ��	
			float m_fCDPSpace;							//Cross Line��ؼ��
			short m_crdType;								//������굥λ����
			CGeoRect<double> m_extent;				// geographic extent

			/*!
			*
			**/
			SurveyInfo() : m_nLineNum(0), m_nCDPNum(0), m_nStartLine(0), m_nStartCDP(0), m_nLineIncrement(0), m_nCDPIncrement(0), \
				m_fOrientation(0.), m_fDirection(0.), m_fOrgX(0.), m_fOrgY(0.), m_fLineSpace(0.), m_fCDPSpace(0.), m_crdType(1)
			{
			}

			/*!
			*
			**/
			const SurveyInfo &operator=(const SurveyInfo &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_nLineNum = other.m_nLineNum;					// In Line��Ŀ
				m_nCDPNum = other.m_nCDPNum;					//Cross Line��Ŀ
				m_nStartLine = other.m_nStartLine;				//In Line��ʼ���
				m_nStartCDP = other.m_nStartCDP;				//Cross Line��ʼ���
				m_nLineIncrement = other.m_nLineIncrement;	//In Line��ż��	
				m_nCDPIncrement = other.m_nCDPIncrement;	//Cross Line��ż��
				m_fOrientation = other.m_fOrientation;			//In Line��λ��
				m_fDirection = other.m_fDirection;					//Cross Line�����In Line�ķ�λ��
				m_fOrgX = other.m_fOrgX;								//�����ʼ����
				m_fOrgY = other.m_fOrgY;								//�����ʼ����
				m_fLineSpace = other.m_fLineSpace;				//In Line��ؼ��	
				m_fCDPSpace = other.m_fCDPSpace;				//Cross Line��ؼ��
				m_crdType = other.m_crdType;						//������굥λ��ʶ
				m_extent = other.m_extent;

				return *this;
			}

			/*!
			*
			**/
			bool Is3D() const
			{
				if(m_nLineNum <= 1 || m_nCDPNum <= 1)
				{
					return false;
				}

				return true;
			}

			/*!
			*
			**/
			bool IsEastDirection()
			{
				return m_fOrientation == 0.;
			}

			/*!
			*
			**/
			long GetLineOrder(long sequenceOrder) const
			{
				return ::floor(sequenceOrder * 1./m_nCDPNum);
			}

			/*!
			*
			**/
			long GetCDPOrder(long sequenceOrder) const
			{
				return sequenceOrder % m_nCDPNum;
			}

			/*!
			*
			**/
			bool IsValid()
			{
				if(m_nLineNum <= 0 || m_nCDPNum <= 0 || (m_fLineSpace <= 0. && m_fCDPSpace <= 0.) || 
					(m_extent.Width() <= 0. && m_extent.Height() <= 0.))
				{
					return false;
				}

				return true;
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySegyFile(const wstring &strFileName, CAnySegyLayer *parent);
		
		/*!
		*
		**/
		~CAnySegyFile();

	public:
		//
		// reader, ��ȡ�������ݽӿ� 
		//
		/*!
		*
		**/
		bool IsSEGYFile();

		/*!
		*
		**/
		wstring GetFileName() const;

		/*!
		*
		**/
		const SurveyInfo &GetSurveyInfo();

		/*!
		*
		**/
		void UpdateSurveyInfo(const SurveyInfo& info);

		/*!
		*
		**/
		const ProfileInfo &GetProfileInfo();

		/*!
		*
		**/
		void UpdateProfileInfo(const ProfileInfo &info);

		/*!
		*
		**/
		int GetTraceNum() const;

		/*!
		*
		**/
		int GetTracePoint() const;

		/*!
		*
		**/
		int GetType() const;

		/*!
		*
		**/
		float *ReadTraceData(int nOrder, TraceHead& traceHead);

		/*!
		*
		**/
		double GetSampleInterval()
		{
			return m_headInfo.m_nInterval;
		}

		//
		// writer
		//
		/*!
		* 
		**/
		void SetFileName(wstring &strFileName);

		/*!
		* �����µ�SEGY�ļ�
		**/
		bool CreateFile();

		/*!
		*
		**/
		void SetTraceNum(int nTraceNum);
		
		/*!
		*
		**/
		void SetTracePoint(int nPts);
		
		/*!
		*
		**/
		void SetType(int nType);

		/*!
		*
		**/
		bool WriteTraceData(float *pData, const TraceHead &traceHead, int nOrder);

		//
		// utility
		//
		/*!
		*
		**/
		int Time2Index(double time, double startTime, float interval);
				
        /*!
        *
        */
        void SaveToDB(int datasetid);
				
        /*!
        *
        */
        void LoadFromDB(int gateid);

		/*!
        *
        */
        void LoadTraceHeadFromDB(int gateid, int order, TraceHead& traceHead);

		/*!
        *
        */
        float *LoadTraceDataFromDB(int gateid, int order, TraceHead& traceHead);

	private:
		//
		//	��ȡ�����ͷ����
		//
		/*!
		*
		**/
		void GetTraceHead(char* pBuf, TraceHead& traceHead);
		
		/*!
		*
		**/
		void PutTraceHead(char* pBuf, const TraceHead& traceHead);

		//
		//	�����ļ�ʱ��
		//
		/*!
		*
		**/
		bool InitTraceHead();

		/*!
		*
		**/
		bool InitTraceData();

		//
		//��������ת��
		//
		/*!
		*
		**/
		void IBMtoIEEE(char *bytes);

		/*!
		*
		**/
		void IEEEtoIBM(char *bytes);
		
		/*!
		*
		**/
		void ReverseBytes(char *bytes, short nSize);

		/*!
		*
		**/
		void DoGetSurveyInfo();

	public:
		// survey info
		SurveyInfo m_surveyInfo;
		// for AnySeismic3DGeometry
		CGeoPoint<double> m_pos[4];
		// segy file
		wstring m_strFileName;
		void *m_fileHandle;
		const CAnyFileBasic &m_fileBasic;

		// head info
		HeadInfo m_headInfo;
		
		// profile info
		ProfileInfo m_profileInfo;

		// parent
		CAnySegyLayer *m_parent;

		// source is database
		bool m_isfromDB;

		// id of this gate
		int m_gateid;
	};
}
#endif




