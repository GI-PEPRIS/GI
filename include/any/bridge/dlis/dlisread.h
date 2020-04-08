/*!
 * The AnyBridge of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * rendering pipeline and key display implementatios etc.
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
#ifndef __ANYBRIDGE_DLISREAD_H__
#define __ANYBRIDGE_DLISREAD_H__

// refer to EXPORT and IMPORT
#include "..\anybridge.h"

#include "any/base/anystl.h"
#include "any/base/anyfilebasic.h"
#include "any/base/anydirbasic.h"
#include "any/base/anystringbasic.h"
using namespace AnyBase;
//
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CDlisRead
	{
	public:
		// ͨ����
		struct Channel
		{
			string m_Name;// ����
			string m_LongName;// ����
			string m_Properties;// ����
			int m_Code;// ������
			string m_Units;// ��λ
			int m_Dimension;// ά��
			int m_NumOfAxis;// ��ĸ���
			std::vector<string> m_Axis;// �������
			std::vector<int> m_Element;// Ԫ�ص�����
			string m_Source;// ��Դ����
			Channel() : m_NumOfAxis(0)
			{
				m_Axis.resize(4);
				m_Element.resize(4);
			}
			const Channel &operator=(const Channel &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_Name = other.m_Name;
				m_LongName = other.m_LongName;
				m_Properties = other.m_Properties;
				m_Code = other.m_Code;
				m_Units = other.m_Units;
				m_Dimension = other.m_Dimension;
				m_NumOfAxis = other.m_NumOfAxis;
				m_Axis = other.m_Axis;
				m_Element = other.m_Element;
				m_Source = other.m_Source;
				return *this;								
			}
		};
		// �����
		struct Frame
		{
			string m_Name;// ����
			string m_Desc;// ����
			std::vector<string> m_Channels;// ͨ������
			int m_NumOfChannels;// ͨ������
			string m_IndexType;// ��������
			string m_Direction;// ��������
			double m_IndexMin;// ������Сֵ
			double m_IndexMax;// �������ֵ
			double m_IndexSpacing;// �������
			string m_IndexUnit;// ������λ
			int m_Encrypted;// �Ƿ����
			std::vector<int> m_ChannelNo;// ͨ�����
			std::vector<int> m_IsChannel;// �Ƿ��������
			Frame()
			{
				m_Channels.resize(3000);
				m_ChannelNo.resize(3000);
				m_IsChannel.resize(3000);
			}
			const Frame &operator=(const Frame &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_Name = other.m_Name;
				m_Desc = other.m_Desc;
				m_Channels = other.m_Channels;
				m_NumOfChannels = other.m_NumOfChannels;
				m_IndexType = other.m_IndexType;
				m_Direction = other.m_Direction;
				m_IndexMin = other.m_IndexMin;
				m_IndexMax = other.m_IndexMax;
				m_IndexSpacing = other.m_IndexSpacing;
				m_IndexUnit = other.m_IndexUnit;
				m_Encrypted = other.m_Encrypted;
				m_ChannelNo = other.m_ChannelNo;
				m_IsChannel = other.m_IsChannel;
				return *this;								
			}
		};
		// ������
		struct Parameter
		{
			string m_Name;// ����
			string m_LongName;// ����
			int m_NumOfDimEle;// ά�ĸ���
			int m_NumOfAxis;// ��ĸ���
			std::vector<string> m_Axis;// ��
			string m_Zones;// ��Χ
			string m_Values;  // ֵ//ת�����ַ��ͣ��Կո�ֿ�;
			string m_Unit;// ��λ
			int m_Code;// ������
			string m_SetName;// ������
			Parameter() : m_NumOfAxis(0)
			{
				m_Axis.resize(4);
			}
			const Parameter &operator=(const Parameter &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_Name = other.m_Name;
				m_LongName = other.m_LongName;
				m_NumOfDimEle = other.m_NumOfDimEle;
				m_NumOfAxis = other.m_NumOfAxis;
				m_Axis = other.m_Axis;
				m_Zones = other.m_Zones;
				m_Values = other.m_Values;
				m_Unit = other.m_Unit;
				m_Code = other.m_Code;
				m_SetName = other.m_SetName;
				return *this;								
			}
		};
		// ����
		struct Axis
		{
			string m_Name;// ����
			string m_AxisId;// ������
			string m_Coordinates;// ����ʼ����
			string m_SpacingValue;// ���
			int m_SpacingCode;// ����ı�����
			string m_SpacingUnit;// ����ĵ�λ
			Axis()
			{
			}
			const Axis &operator=(const Axis &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_Name = other.m_Name;
				m_AxisId = other.m_AxisId;
				m_Coordinates = other.m_Coordinates;
				m_SpacingValue = other.m_SpacingValue;
				m_SpacingCode = other.m_SpacingCode;
				m_SpacingUnit = other.m_SpacingUnit;
				return *this;								
			}
		};
		// ���ͨ��
		struct DlisDecodeChannel
		{
			string m_Name;// ����
			double m_IndexMin;// ������Сֵ
			double m_IndexMax;// �������ֵ
			double m_IndexSpacing;// �������
			string m_IndexUnit;// ������λ
			int m_IndexDir;// ��������
			int m_NumLev;// ����������
			int m_Code;// ������
			string m_Units;// ��λ
			int m_Dimension;// ά��
			int m_NumOfAxis;// ��ĸ���
			std::vector<string> m_Axis;// ����б�
			std::vector<int> m_Element;// Ԫ��
			string m_FrameName;// �������
			int m_FrameNo;// ��ܱ��
			int m_ChannelNo;// ͨ�����
			int m_Samples;// ÿ������������ݸ���
			int m_CodeSize;// ���������ռ���ֽ���
			int m_SamplesSize;// ÿ�����������ݵ��ֽ���
			int m_OffsetAddrOfData;// �����ݼ�¼�еĿ�ʼ���ֽ�ƫ����
			DlisDecodeChannel() : m_NumOfAxis(0)
			{
				m_Axis.resize(4);
				m_Element.resize(4);
			}
			const DlisDecodeChannel &operator=(const DlisDecodeChannel &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_Name = other.m_Name;
				m_IndexMin = other.m_IndexMin;
				m_IndexMax = other.m_IndexMax;
				m_IndexSpacing = other.m_IndexSpacing;
				m_IndexUnit = other.m_IndexUnit;
				m_IndexDir = other.m_IndexDir;
				m_NumLev = other.m_NumLev;
				m_Code = other.m_Code;
				m_Units = other.m_Units;
				m_Dimension = other.m_Dimension;
				m_NumOfAxis = other.m_NumOfAxis;
				m_Axis = other.m_Axis;
				m_Element = other.m_Element;
				m_FrameName = other.m_FrameName;
				m_FrameNo = other.m_FrameNo;
				m_ChannelNo = other.m_ChannelNo;
				m_Samples = other.m_Samples; 
				m_CodeSize = other.m_CodeSize;
				m_SamplesSize = other.m_SamplesSize;
				m_OffsetAddrOfData = other.m_OffsetAddrOfData;
				return *this;								
			}
		};
		// ������
		struct DlisDecodePar
		{
			string m_Name;// ����
			string m_Values;// ֵ
			string m_Unit;// ��λ
			DlisDecodePar() : m_Name(""), m_Values(""), m_Unit("")
			{
			}
			const DlisDecodePar &operator=(const DlisDecodePar &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_Name = other.m_Name;
				m_Values = other.m_Values;
				m_Unit = other.m_Unit;
				return *this;								
			}
		};
		// ���������
		struct DlisDecodeFrameData
		{
			int m_IndexNoNow;// ��ǰ���������
			double m_IndexNow;// ��ǰ������
			int m_IndexDir;// ��������
			double m_IndexMin;// ������Сֵ
			double m_IndexMax;// �������ֵ
			double m_IndexSpacing;// �������
			string m_IndexUnit;// ������λ
			int m_Numlev;// ������
			int m_NumofChannel;// ͨ���ĸ���
			std::vector<string> m_Channels;// ͨ��������
			std::vector<string> m_Unit;// ��λ
			std::vector<int> m_ChannelNo;// ͨ�����
			std::vector<int> m_Samples;// ÿ������������ݸ���
			std::vector<int> m_Code;// ������
			std::vector<string> m_DataType;// ��������
			std::vector<int> m_OffsetSample;// ƫ�Ƹ���
			std::vector<int> m_OffsetEntryAddr;// ƫ�Ƶ��ֽ�
			std::vector<int> m_Dimension;// ά��
			std::vector<std::vector<int> > m_Element;// Ԫ��
			int m_AllSamples;// �ý���ܵ������ܸ���
			std::vector<double> m_AllValue;// ֵ
			DlisDecodeFrameData() : m_IndexNoNow(1), m_NumofChannel(0), m_AllSamples(0)
			{
			}
			const DlisDecodeFrameData &operator=(const DlisDecodeFrameData &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_IndexNoNow = other.m_IndexNoNow;
				m_IndexNow = other.m_IndexNow;
				m_IndexDir = other.m_IndexDir;
				m_IndexMin = other.m_IndexMin;
				m_IndexMax = other.m_IndexMax;
				m_IndexSpacing = other.m_IndexSpacing;
				m_IndexUnit = other.m_IndexUnit;
				m_Numlev = other.m_Numlev;
				m_NumofChannel = other.m_NumofChannel;
				m_Channels = other.m_Channels;
				m_Unit = other.m_Unit;
				m_ChannelNo = other.m_ChannelNo;
				m_Samples = other.m_Samples;
				m_Code = other.m_Code;
				m_DataType = other.m_DataType; 
				m_OffsetSample = other.m_OffsetSample;
				m_OffsetEntryAddr = other.m_OffsetEntryAddr;
				m_Dimension = other.m_Dimension; 
				m_Element = other.m_Element;	 
				m_AllSamples = other.m_AllSamples;
				m_AllValue = other.m_AllValue;	
				return *this;								
			}
		};														
	public:
		//
		//
		//
		/*!
		*
		**/
		CDlisRead();

		/*!
		*
		**/
		~CDlisRead();
	public:
		
		/*!
		*
		**/
		bool OpenFile(string filename);
		void DlisWorkInit(string filename);
		int DetectGap();
		void DlisLogicalRecordSegmentLocation();
		void GetLRInf();
		void LogicalFileScan();
		void ReadFileStreamToBytes();
		void DlisWellSiteInfScan();
		void EFLRScan(int NoLR);
		void SetEFLRProcessFlag();
		void EFLRProcess(int NoLR);
		int GetEFLRSetTypeAndName(int IpComponent);
		int GetEFLRTemplateAttr(int IpComponent);
		int GetEFLRObjectValue(int IpComponent, int NoTemplate);
		void GetChannelAttributies(int NoTemplate);
		void GetFrameAttributies(int NoFrame, int NoTemplate);
		void GetParameterAttributies(int NoTemplate);
		void GetCommentAttributies(int NoTemplate);
		void GetAxisAttributies(int NoTemplate);
		void GetFrameChannelNoInChannelSet();
		void DlisDataDecodeInit();
		void GetDlisDecodeChannelAttr();
		void GetDlisDecodeFrameDataAttr();
		static string TypeOfDlisCode(int Code);
		void GetDlisFrameAllValueByDataLRNo(int LRNoNow);
		void GetDlisFrameAllValueByFrameIndexNo(int FrameNoNow, int IndexNoNow);
		void DlisWorkOver();
		void CloseFile();
		void GetLRSAttrBit(int AttrWord);
		void GetLRBody(int NoLRSeg, int &NumOfLRSeg);
		void GetLRBodyNew(int NoLRNow);
		void GetComponentRoleAndBit(int IpComponent);
		void GetComponentValue(int IpComponent, int Count, int RepCode, int &BytesValue);
		void GetDlisFrameChannelDataValue(int DecodeChannelNo, float* Values, int &NumOfValues);
		void GetDlisFrameChannelDataZoneValue(int DecodeChannelNo, int StartIndexNo, int NumOfIndex, float* Values, int &NumOfValues);
		void GetChannelDataBody(int DataNo, int NoLRNow, int DecodeChannelNo);
		void GetDlisFrameChannelDataValueOld(int NoDlisDecodeChannel, float* Values, int &NumOfValues);
		void GetDlisFrameChannelDataZoneValueOld(int NoDlisDecodeChannel, int StartIndexNo, int NumOfIndex, float* Values, int &NumOfValues);
		int GetIsSUL();
		int GetChannelLRSegNo();
		int GetFrameLRSegNo();
		void SetCurveAndParamsSelectFlagByDefaultFile(string CurveFileName);
		void SetDlisDecodeChannelByCurveName(string ChannelName);
		void SetDlisDecodeParaByName(string ParaName);

	public:
		string IntToString(int val);
		string FloatToString(float val);
		string DoubleToString(double val);
		int ReadInt32(long long IPoffset);
		unsigned char ReadChar(long long IPoffset);
		unsigned char* ReadBytes(long long IPoffset, int LengthBlockReadStream);

	public:
		int m_dataversion;//�汾��1,2
		string m_filePath;
		const CAnyFileBasic &m_fileBasic;
		void *m_fileHandle;
		long long m_filelength;

		//�Ŵ�ͷ����Ϣ
		int m_IsGap;// �Ƿ��м�϶
		int m_MachineGap;// ������
		int m_LenGap;// ��϶����
		int m_TitilOffset;// �ļ���ʼƫ����
		int m_IsSUL; // �Ƿ���ڴ洢��Ԫ��ǩ
		int m_LengthBlockReadStream;// �������Ŀ鳤��
		int m_LengthBlockNow;// ��ǰ��ĳ���
		int m_LengthBlockNowGap;// ��ǰ��϶�ĳ���

		//�߼���¼�γ�Ա����
		int m_NumOfSeg;// �߼���¼�εĸ���
		std::vector<int> m_SegEntryAddr;// �߼���¼�εĿ�ʼλ��	
		std::vector<int> m_SegLength;// �߼���¼�εĳ���	
		std::vector<int> m_SegAttr;// �߼���¼�ε�����
		std::vector<int> m_SegType;// �߼���¼�ε�����
		std::vector<int> m_SegHeaderLen;// �߼���¼��ͷ�ĳ���	
		std::vector<int> m_SegBodyLen;// �߼���¼����ĳ���	
		std::vector<int> m_SegAttrBit;// �߼���¼������λ

		//�߼���¼����Ϣ
		int m_NumOfLR;// �߼���¼�ĸ���
		std::vector<int> m_LREntrySegNo;// ÿ���߼���¼����ڶα��	
		std::vector<int> m_LRSegNum;// ÿ���߼���¼�Ľ����α��
		std::vector<int> m_LRFormat;// �߼���¼�Ľṹ���Ը�ʽ������ʽ	
		std::vector<int> m_LRType;// �߼���¼���ͣ�=�߼���¼�����ͣ�

		//�߼��ļ�����Ϣ
		int m_numOfLogicalFile;// �߼��ļ��ĸ���
		int m_noLogicalFileNow;// ��ǰ�߼��ļ����
		std::vector<int> m_StartLRNoOfLogicalFile;// �߼��ļ�������߼���¼���
		std::vector<int> m_EndLRNoOfLogicalFile;// �߼��ļ��Ľ����߼���¼���
		std::vector<int> m_DataStartLRNoOfLogicalFile;// �߼��ļ������ݶο�ʼ���߼���¼���

		//������Ϣ	
		int m_isAllFrameData;// �ǹ����տ��һ��һ�����	
		int m_isIndexUnit;// �Ƿ���������λ	
		int m_isIndexDir;// �Ƿ�����������

		//���ݼ�¼����Ϣ
		int m_numOfDataLR;// �����߼���¼�ĸ���
		std::vector<int> m_DataEntryLRNo;// ������ڵ��߼���¼���
		std::vector<int> m_DataLRFrameNo;// �����߼���¼�Ŀ�ܱ��
		std::vector<int> m_DataLRHeadLen;// �����߼���¼��ͷ�ĳ���
		std::vector<int> m_DataLRFrameIndexNo;// �����߼���¼����������
		int m_nowDataLRFrameNo;// ��ǰ�����߼���¼�Ŀ�ܱ��
		std::vector<DlisDecodeFrameData> m_frameDataList;// ����������б�

		//�Ը�ʽ�߼���¼
		int m_NumOfEFLR;// �Ը�ʽ�߼���¼�ĸ���
		std::vector<int> m_LRNoOfEFLR;// �Ը�ʽ�߼���¼�ı��
		std::vector<string> m_SetTypeOfEFLR;// �Ը�ʽ�߼���¼��������
		std::vector<string> m_SetNameOfEFLR;// �Ը�ʽ�߼���¼��������
		std::vector<int> m_IsEFLR;// �Ƿ����Ը�ʽ���߼���¼

		//�洢�ֽڵı���
		long long m_IPoffset;// �ֽ�ƫ����
		unsigned char* m_BytesBlock;// �ֽڿ�
		unsigned char* m_BytesLRBody;// �߼���¼����ֽ���	
		int m_LenLRBody;// �߼���¼����ֽڳ���

		//�����ı���
		std::vector<int> m_ComponentBit;// ������8λ
		int m_ComponentRole;// ������ǰ3λ��ֵ���жϹ����Ľ�ɫ

		//������ͺ�����
		string m_EFLRSetType;// �Ը�ʽ�߼���¼�������
		string m_EFLRSetName;// �Ը�ʽ�߼���¼�������

		//ģ��ı���
		int m_NumOfTemplate;// ģ��ĸ���
		std::vector<string> m_TemplateLabel;// ģ��ı�ǩ
		std::vector<int> m_TemplateCount;// ģ��ļ���
		std::vector<int> m_TemplateCode;// ģ��ı�����
		std::vector<string> m_TemplateUnit;// ģ��ĵ�λ

		//����������ı���
		std::vector<int> m_EleOfComponentValue;// �������Ԫ�صĸ�����FSING1--> 2 *FSING [V-A,V+A],V,A
		std::vector<string> m_StringOfComponentValue;// ������������ַ�����ֵ
		std::vector<double> m_ValueOfComponentValue;// �������������ֵ�͵�ֵ

		//����ı���
		string m_EFLRObjectName;// �Ը�ʽ�߼���¼�Ķ��������
		int m_NumOfObject;// ����ĸ���
		string m_ObjectLabel;// ����ı�ǩ
		int m_ObjectCount;// ����ļ���
		int m_ObjectCode;// ����ı�����
		string m_ObjectUnit;// ����ĵ�λ

		//����¼���ַ�����ʾ
		string m_OriginInfShow;// ��������Ϣ��ʾ

		//�ı��߼���¼
		int m_isComment;// �Ƿ�����ļ���¼	
		int m_numOfComment;// �ı��ĸ���
		std::vector<string> m_CommentSetName;// �ı���������
		std::vector<string> m_CommentObjName;// �ı��Ķ��������
		std::vector<string> m_CommentText;// �ı����ַ�

		//���߼���¼
		int m_isAxis;// �Ƿ�������߼���¼
		int m_numOfAxis;// ��ĸ���
		Axis m_axis;// �����
		std::vector<Axis> m_axisList;// ���б�

		//�����߼���¼
		int m_isParameter;// �ǹ��ǲ����߼���¼
		int m_numOfParameter;// �����ĸ���
		Parameter m_parameter;// ��������
		std::vector<Parameter> m_parameterList;// �����б�

		//ͨ���߼���¼
		int m_numOfChannel;// ͨ���ĸ���
		Channel m_channel;// ͨ������
		std::vector<Channel> m_channelList;// ͨ���б�

		//����߼���¼
		int m_numOfFrame;// ��ܵĸ���
		std::vector<Frame> m_frameList;// ����б�

		//���ͨ��
		int m_numOfDlisDecodeChannel;// ���ͨ���ĸ���
		std::vector<DlisDecodeChannel> m_decodeChannelList;// ���ͨ���б�
		int m_numOfDlisDecodePar;// ͨ�������ĸ���
		std::vector<DlisDecodePar> m_decodeParaList;// ͨ���б�
		string m_CMRParaStr;// �����ַ���
	};
}

#endif
