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
		// 通道类
		struct Channel
		{
			string m_Name;// 名称
			string m_LongName;// 长名
			string m_Properties;// 属性
			int m_Code;// 表征码
			string m_Units;// 单位
			int m_Dimension;// 维数
			int m_NumOfAxis;// 轴的个数
			std::vector<string> m_Axis;// 轴的名称
			std::vector<int> m_Element;// 元素的限制
			string m_Source;// 资源属性
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
		// 框架类
		struct Frame
		{
			string m_Name;// 名称
			string m_Desc;// 描述
			std::vector<string> m_Channels;// 通道名称
			int m_NumOfChannels;// 通道个数
			string m_IndexType;// 索引类型
			string m_Direction;// 索引方向
			double m_IndexMin;// 索引最小值
			double m_IndexMax;// 索引最大值
			double m_IndexSpacing;// 索引间隔
			string m_IndexUnit;// 索引单位
			int m_Encrypted;// 是否加密
			std::vector<int> m_ChannelNo;// 通道编号
			std::vector<int> m_IsChannel;// 是否解编该曲线
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
		// 参数类
		struct Parameter
		{
			string m_Name;// 名称
			string m_LongName;// 长名
			int m_NumOfDimEle;// 维的个数
			int m_NumOfAxis;// 轴的个数
			std::vector<string> m_Axis;// 轴
			string m_Zones;// 范围
			string m_Values;  // 值//转化成字符型，以空格分开;
			string m_Unit;// 单位
			int m_Code;// 表征码
			string m_SetName;// 组名称
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
		// 轴类
		struct Axis
		{
			string m_Name;// 名称
			string m_AxisId;// 轴类型
			string m_Coordinates;// 轴起始坐标
			string m_SpacingValue;// 间隔
			int m_SpacingCode;// 间隔的表征码
			string m_SpacingUnit;// 间隔的单位
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
		// 解编通道
		struct DlisDecodeChannel
		{
			string m_Name;// 名称
			double m_IndexMin;// 索引最小值
			double m_IndexMax;// 索引最大值
			double m_IndexSpacing;// 索引间隔
			string m_IndexUnit;// 索引单位
			int m_IndexDir;// 索引方向
			int m_NumLev;// 索引采样数
			int m_Code;// 表征码
			string m_Units;// 单位
			int m_Dimension;// 维数
			int m_NumOfAxis;// 轴的个数
			std::vector<string> m_Axis;// 轴的列表
			std::vector<int> m_Element;// 元素
			string m_FrameName;// 框架名称
			int m_FrameNo;// 框架编号
			int m_ChannelNo;// 通道编号
			int m_Samples;// 每个索引点的数据个数
			int m_CodeSize;// 表征码的所占的字节数
			int m_SamplesSize;// 每个索引点数据的字节数
			int m_OffsetAddrOfData;// 在数据记录中的开始的字节偏移量
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
		// 解编参数
		struct DlisDecodePar
		{
			string m_Name;// 名称
			string m_Values;// 值
			string m_Unit;// 单位
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
		// 解编框架数据
		struct DlisDecodeFrameData
		{
			int m_IndexNoNow;// 当前的索引编号
			double m_IndexNow;// 当前的索引
			int m_IndexDir;// 索引方向
			double m_IndexMin;// 索引最小值
			double m_IndexMax;// 索引最大值
			double m_IndexSpacing;// 索引间隔
			string m_IndexUnit;// 索引单位
			int m_Numlev;// 采样数
			int m_NumofChannel;// 通道的个数
			std::vector<string> m_Channels;// 通道的名称
			std::vector<string> m_Unit;// 单位
			std::vector<int> m_ChannelNo;// 通道编号
			std::vector<int> m_Samples;// 每个索引点的数据个数
			std::vector<int> m_Code;// 表征码
			std::vector<string> m_DataType;// 数据类型
			std::vector<int> m_OffsetSample;// 偏移个数
			std::vector<int> m_OffsetEntryAddr;// 偏移的字节
			std::vector<int> m_Dimension;// 维数
			std::vector<std::vector<int> > m_Element;// 元素
			int m_AllSamples;// 该解编框架的数据总个数
			std::vector<double> m_AllValue;// 值
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
		int m_dataversion;//版本：1,2
		string m_filePath;
		const CAnyFileBasic &m_fileBasic;
		void *m_fileHandle;
		long long m_filelength;

		//磁带头的信息
		int m_IsGap;// 是否有间隙
		int m_MachineGap;// 机器码
		int m_LenGap;// 间隙长度
		int m_TitilOffset;// 文件开始偏移量
		int m_IsSUL; // 是否存在存储单元标签
		int m_LengthBlockReadStream;// 读入流的块长度
		int m_LengthBlockNow;// 当前块的长度
		int m_LengthBlockNowGap;// 当前间隙的长度

		//逻辑记录段成员变量
		int m_NumOfSeg;// 逻辑记录段的个数
		std::vector<int> m_SegEntryAddr;// 逻辑记录段的开始位置	
		std::vector<int> m_SegLength;// 逻辑记录段的长度	
		std::vector<int> m_SegAttr;// 逻辑记录段的属性
		std::vector<int> m_SegType;// 逻辑记录段的类型
		std::vector<int> m_SegHeaderLen;// 逻辑记录段头的长度	
		std::vector<int> m_SegBodyLen;// 逻辑记录段体的长度	
		std::vector<int> m_SegAttrBit;// 逻辑记录段属性位

		//逻辑记录的信息
		int m_NumOfLR;// 逻辑记录的个数
		std::vector<int> m_LREntrySegNo;// 每个逻辑记录的入口段编号	
		std::vector<int> m_LRSegNum;// 每个逻辑记录的结束段编号
		std::vector<int> m_LRFormat;// 逻辑记录的结构：显格式和隐格式	
		std::vector<int> m_LRType;// 逻辑记录类型（=逻辑记录段类型）

		//逻辑文件的信息
		int m_numOfLogicalFile;// 逻辑文件的个数
		int m_noLogicalFileNow;// 当前逻辑文件编号
		std::vector<int> m_StartLRNoOfLogicalFile;// 逻辑文件的入口逻辑记录编号
		std::vector<int> m_EndLRNoOfLogicalFile;// 逻辑文件的结束逻辑记录编号
		std::vector<int> m_DataStartLRNoOfLogicalFile;// 逻辑文件的数据段开始的逻辑记录编号

		//索引信息	
		int m_isAllFrameData;// 是够按照框架一个一个解编	
		int m_isIndexUnit;// 是否是索引单位	
		int m_isIndexDir;// 是否是索引方向

		//数据记录的信息
		int m_numOfDataLR;// 数据逻辑记录的个数
		std::vector<int> m_DataEntryLRNo;// 数据入口的逻辑记录编号
		std::vector<int> m_DataLRFrameNo;// 数据逻辑记录的框架编号
		std::vector<int> m_DataLRHeadLen;// 数据逻辑记录的头的长度
		std::vector<int> m_DataLRFrameIndexNo;// 数据逻辑记录框架索引编号
		int m_nowDataLRFrameNo;// 当前数据逻辑记录的框架编号
		std::vector<DlisDecodeFrameData> m_frameDataList;// 解编框架数据列表

		//显格式逻辑记录
		int m_NumOfEFLR;// 显格式逻辑记录的个数
		std::vector<int> m_LRNoOfEFLR;// 显格式逻辑记录的编号
		std::vector<string> m_SetTypeOfEFLR;// 显格式逻辑记录的组类型
		std::vector<string> m_SetNameOfEFLR;// 显格式逻辑记录的组名称
		std::vector<int> m_IsEFLR;// 是否是显格式的逻辑记录

		//存储字节的变量
		long long m_IPoffset;// 字节偏移量
		unsigned char* m_BytesBlock;// 字节块
		unsigned char* m_BytesLRBody;// 逻辑记录体的字节组	
		int m_LenLRBody;// 逻辑记录体的字节长度

		//构件的变量
		std::vector<int> m_ComponentBit;// 构件的8位
		int m_ComponentRole;// 构件的前3位的值，判断构件的角色

		//组的类型和名称
		string m_EFLRSetType;// 显格式逻辑记录组的类型
		string m_EFLRSetName;// 显格式逻辑记录组的名称

		//模板的变量
		int m_NumOfTemplate;// 模板的个数
		std::vector<string> m_TemplateLabel;// 模板的标签
		std::vector<int> m_TemplateCount;// 模板的计数
		std::vector<int> m_TemplateCode;// 模板的表征码
		std::vector<string> m_TemplateUnit;// 模板的单位

		//解析表征码的变量
		std::vector<int> m_EleOfComponentValue;// 表征码的元素的个数，FSING1--> 2 *FSING [V-A,V+A],V,A
		std::vector<string> m_StringOfComponentValue;// 解析表征码的字符串的值
		std::vector<double> m_ValueOfComponentValue;// 解析表征码的数值型的值

		//对象的变量
		string m_EFLRObjectName;// 显格式逻辑记录的对象的名称
		int m_NumOfObject;// 对象的个数
		string m_ObjectLabel;// 对象的标签
		int m_ObjectCount;// 对象的计数
		int m_ObjectCode;// 对象的表征码
		string m_ObjectUnit;// 对象的单位

		//历记录的字符串显示
		string m_OriginInfShow;// 来历的信息显示

		//文本逻辑记录
		int m_isComment;// 是否存在文件记录	
		int m_numOfComment;// 文本的个数
		std::vector<string> m_CommentSetName;// 文本的组名称
		std::vector<string> m_CommentObjName;// 文本的对象的名称
		std::vector<string> m_CommentText;// 文本的字符

		//轴逻辑记录
		int m_isAxis;// 是否存在轴逻辑记录
		int m_numOfAxis;// 轴的个数
		Axis m_axis;// 轴对象
		std::vector<Axis> m_axisList;// 轴列表

		//参数逻辑记录
		int m_isParameter;// 是够是参数逻辑记录
		int m_numOfParameter;// 参数的个数
		Parameter m_parameter;// 参数对象
		std::vector<Parameter> m_parameterList;// 参数列表

		//通道逻辑记录
		int m_numOfChannel;// 通道的个数
		Channel m_channel;// 通道对象
		std::vector<Channel> m_channelList;// 通道列表

		//框架逻辑记录
		int m_numOfFrame;// 框架的个数
		std::vector<Frame> m_frameList;// 框架列表

		//解编通道
		int m_numOfDlisDecodeChannel;// 解编通道的个数
		std::vector<DlisDecodeChannel> m_decodeChannelList;// 解编通道列表
		int m_numOfDlisDecodePar;// 通道参数的个数
		std::vector<DlisDecodePar> m_decodeParaList;// 通道列表
		string m_CMRParaStr;// 参数字符串
	};
}

#endif
