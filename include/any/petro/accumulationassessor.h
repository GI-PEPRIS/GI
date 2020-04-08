/*!
 * The AnyPetro of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the domain data model etc.
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
#ifndef __ANYPETRO_ACCUMULATION_ASSESSOR_H__
#define __ANYPETRO_ACCUMULATION_ASSESSOR_H__

// refer to EXPORT etc macroes
#include "anypetro.h"

// refer to its parent
#include "anypetroactivity.h"
#include "anytrapmanagement.h"
// refer to persistence
#include "any/db/anyaccessor.h"
using namespace AnyDB;
// refer to functor
#include "any/base/anymediator.h"
#include "any/base/anygeom.h"
using namespace AnyBase;
// 
namespace AnyPetro
{
	// forward class
	class CAssessmentStrategy;
	class CAccumulationElement;

	/*!
	*
	**/
	class ANYPETRO_CLASS CAccumulationAssessor : public CAnyPetroActivity
	{
		// relatives
		friend class CAccumulationElement;

	public:
		/*!
		* deprecated
		**/
		enum ActivityFlowType
		{
			AFT_Unknown = -1,
			AFT_Play,
			AFT_Trap,
			AFT_Max
		};

		/*!
		* 
		**/
		enum ActivityTemplateType
		{
			Play_General = 0,	// �������� 
			Play_Seismic = 1,	// ������
			Trap_Prospect = 2,	// ������Ŀ
			Trap_Wildcat = 3,	// Ȧ��Ԥ̽����ѡ
			Nonconventional = 4, // �ǳ�������
			BigData = 5,		//�����ݰ汾
			Portfolio = 6,		//Ͷ����ϰ汾
			Block = 7,		    //�����
			Performance = 8,	//ҳ�������ܷ���
			Reservoir = 9,		//����Ԥ��
			Trap_Manage = 10,	// Ȧ�չ���
			Nonconventional_Oil=11,//ҳ����
			BasinSim=12,		//���ģ��   
			OverSeaEva,		//������Ŀ����
			Nonconventional_basin = 101,
			Nonconventional_favzone = 102,
			Nonconventional_play = 103,
			Nonconventional_target = 104,
			Nonconventional_well = 105,
			Block_block = 106,//���� ����
			Performance_Well = 107,//��̬���� ��
			Block_play = 108,//���� ����
			Template_MAX = 109,
		};

		/*!
		* 
		**/
		enum FunctorType
		{
			Functor_Factor_Delete =0,
			Functor_Progress,
		};

		/*!
		* 
		**/
		enum BlobType
		{
			Normal_Image =0,
			Normal_Grid,
			Distribution_Image,
			Distribution_Grid,
			Input_Parameter,
			Normal_Image_Group,
			Normal_Table_Res,
			Normal_Table_Group,
			Normal_Table_scatter,
			Normal_Table_trend,
			Normal_Table_elements,
			Normal_Table_elementsPropdata,
			Normal_Table_Dispara1,
			Normal_Table_List1,
			Normal_Table_scatter2,
			DUAl_Table_Layer,
			DUAl_Table_Para,
			DUAl_Table_CurveParas,
			Dual_Data_toccurve,
			DUal_Data_orgcurve,
			DUAl_BASIC_Paras,
			DUAl_BASIC_LineParas,
			DUAl_BASIC_LineThiParas,
			DUAl_BASIC_LineTFParas,

		};
		/*!
		* note:
		* below is tightly coupled with InitActivityRecords()
		**/
		enum StrategyType
		{
			ST_Unknown = -1,
			ST_Framework,//0											// parent
			ST_Framework_PetroBank,							// import petrobank data
			ST_Framework_GIS,									// import kinds of GIS files
			ST_Framework_Query,								// topic query
			ST_Framework_Trap_Prospect_Decision,			// prospect report 7
			ST_Framework_Trap_Prospect_Report,				// prospect report 6-11
			ST_Framework_Trap_Report,						// trap standard report 0-5
			ST_Framework_Seismic_Report,						// seismic standard report 12-16
			ST_Seismic_Evaluation,							// seismic evaluation
			ST_Seismic_Evaluation_Risk_Setup,						// seiemic select soring template
			ST_Seismic_Evaluation_Risk_Maturity,	//10					// seismic risk assessment
			ST_Risk_Model,											// parent
			ST_Risk_Setup,											// set up scoring schema
			ST_Risk_Maturity,										// accumulation maturity analysis
			ST_Risk_Condition,										// margin/condition probability analysis
			ST_Risk_Montecarlo,	//15								// risk uncertainty analysis
			ST_Risk_Parallel,										// parallel
			ST_Risk_Reality,											// reality check against risk evaluation
			ST_Resource_Model,									// parent
			ST_Resource_Model_Monte_Simulate,					// parent
			ST_Resource_Model_Statistics,	//20						// parent
			ST_Resource_Model_Probability,						// parent
			ST_Resource_Model_Discovery_Process,				// parent
			ST_Resource_Model_Space_Distribution,				// parent
			ST_Resource_Sample,								// sample analysis
			ST_Resource_Analogue,	//25							// analogue
			ST_Resource_Trend,									// exploration efficiency trend
			ST_Resource_Sequence,								// pool size in sequence
			ST_Resource_Nonparameter,						// gsc non-parameter
			ST_Resource_Volumetric,							// volumetric
			ST_Resource_Supperpopulation,	//30				// given a prior distribution
			ST_Resource_Discovery,								// discovery model
			ST_Resource_Pool_Rank,							// pool-rank-by-size
			ST_Resource_Montecarlo,							// usgs 2000 monte carlo
			ST_Resource_Reality,									// resource reality check
			ST_Resource_Spatial_Stochastic,		//35			// 
			ST_Economic_Model,									// parent
			ST_Economic_NPV,										// npv
			ST_Economic_MultiNPV,
			ST_Economic_ROV,									// rov
			ST_Economic_Play,										// economic rapid assessment
			ST_Value_Model,		//40								// parent
			ST_Value_Trap,											// selection against trap candidates
			ST_Value_Predrill,										// optimization against trap selected above
			ST_Value_Report_Header,
			ST_Value_Prospect,									// prospect-segment model
			ST_Value_Resource,			//45						// resource manager
			ST_Value_Portfolio,									// portfolio investment
			ST_Performance,										// post-drill evaluation
			ST_Performance_Risk,								//
			ST_Visualization,										//
			ST_Visualization_Report,	//50							// evaluation report
			ST_Visualization_Parallel,							// parallel coordinate
			ST_Visualization_Contour,							// contour
			ST_Visualization_Scatter,							// scatter plot
			ST_Visualization_Distribution,						// distribution panel
			ST_Visualization_Probability_Tree,//55
			ST_Visualization_Bayes_Network,
			ST_Visualization_Decision_Tree,
			ST_Spatial,
			ST_Spatial_Map_Algebra,
			ST_Shale_Basin,													// ��ؼ������Ե //60			
			ST_Shale_Basin_Simulation,								// 1D\2Dģ�⣬����չ��
			ST_Shale_Basin_GIS,											// GISͼ����ϣ���ͼ������
			ST_Shale_Basin_GeoFracture,								  //���ڹ���Ӧ��ĵ����ѷ����
			ST_Shale_Basin_Simulation_Bury,							//���ʷģ��
			ST_Shale_Basin_Simulation_Thermal, 						//��ʷģ��
			ST_Shale_Basin_Simulation_Migration,					//�˾�ʷģ��
			ST_Shale_Basin_GIS_Overlap,								//�����ؿռ����
			ST_Shale_Basin_TOCRecoverCal,							// ԭʼ�л�̼�����ָ�����
			ST_Shale_Play,														// ������
			ST_Shale_Play_Volume,										// ������ʯ�Ƚ����ݵ������
			ST_Shale_Play_Volume_Gen,									// ������ͨ���ݵ������
			ST_Shale_Play_Ro,												// ���������� 	//65
			ST_Shale_Play_Risk,											// ��̽�ɹ�������
			ST_Shale_Play_Analogue,									// ���
			ST_Shale_Play_Forspan,        							// ����Ǳ������
			ST_Shale_Play_NPV,          								// ���鿱̽�ɱ�����
			ST_Shale_Play_Repository,								// ������ѡ					//70    
			ST_Shale_Play_GIS,             								// ҳ�������ؼ����ط�������ͼ������
			ST_Shale_Play_Evidence,									// ҳ�������ؼ����ط�����֤��Ȩ��
			ST_Shale_Play_Risk_Prj,									//�����빤�̷�������
			ST_Shale_Play_Rank,									//�Ŷ���ѡ
			ST_Shale_Target,													// Ŀ��
			ST_Shale_Target_Sweet_Geology,      				// ��������ģ��ĵ���������\Ӧ��Ӧ��������
			ST_Shale_Target_Sweet_Seismic,      			    // ��ǰ��ʯ������������			//75
			ST_Shale_Target_Sweet_Log,			       			// ���񡢳���⾮��Ȼ�ѷ����  
			ST_Shale_Target_Risk,					 					// ��������������
			ST_Shale_Target_EUR_Passey,         				// ˫��(?)ģ�������	
			ST_Shale_Target_EUR_PasseyPara,         				// ˫��(?)ģ��������Ĳ�������
			ST_Shale_Target_EUR_Well,								// �ྮEUR
			ST_Shale_Target_EUR_Well_Krig,								// �ྮEUR�����˳��ģ��,С��Ԫ//80
			ST_Shale_Target_Volume,								//Ŀ���������
			ST_Shale_Target_NPV,                						// ��㾭������
			ST_Shale_Target_Portfolio,              					// ���Ͷ�������ѡ������ϵ����㣩
			ST_Shale_Target_Production,							// ���ܽ��跽����������Ԫͳ�ơ�����ѧϰ��
			ST_Shale_Target_RecursiveRegression,                // ���Եݹ�
			ST_Shale_Target_Sweet_Seismic_PostAttr,                // ���������ѷ����
			ST_Shale_Target_Sweet_Seismic_PrevAttr,                // ���������ѷ����
			ST_Shale_Target_Sweet_Seismic_Bayes,                // ��ǰ��ʯ������������
			ST_Shale_Target_Volumn_oilbitumen,					// �ȷ�����A
			ST_Shale_Well,
			ST_Shale_Well_Single_Curve,							// �����ݼ����߷���//85
			ST_Shale_Well_Typical_Curve,							// ���;����߷���
			ST_Shale_Well_EUR,											// ����EUR				
			ST_Shale_Well_NPV,											// ������������
			ST_Shale_Well_Reserve_Evaluation,				//������������		 //89
			ST_Shale_Well_Wavelet_Analysis,					//��������		 //90
			ST_Shale_Well_EUR_Chen,							//��Ԥ��ģ�ͷ�
			ST_Block_Evaluation,
			ST_Block_Risk_Setup,							//������������ģ��
			ST_Block_Exploration_Evaluation,				//���鿱̽�̶�����
			ST_Block_Risk_Evaluation,						//�����������
			ST_Block_Value_Evaluation,						//�����ֵ����
			ST_Block_Exploration_Level_Schema,				//��̽�̶ȱ�׼
			ST_Block_Geological_Risk_Schema,				//���ʷ��ձ�׼
			ST_Block_Resource_Value_Schema,					//��Դ��ֵ��׼
			ST_Block_Engineering_Risk_Schema,				//���̷��ձ�׼
			ST_Block_Block_Exploration_Level_Schema,		//��������׼
			ST_Block_Block_Exploration_Level_Assessment_Low,//���鿱̽�̶�����
			ST_Block_Deterministic_Risk_Assessment_Low,		//���ʷ�������
			ST_Block_Analogue_Predication_Low,				//��ȷ�
			ST_Block_Volumetric_Method_Low,					//�����
			ST_Block_The_Seventh_Approximation_Low,			//USGS���߱ƽ���
			ST_Block_Resource_Value_Assessment_Low,			//��Դ��ֵ����
			ST_Block_Block_Preference_Low,					//��ѡ�Ŷ�
			ST_Block_Deterministic_Risk_Assessment_High,	//���ʷ�������
			ST_Block_Uncertain_Risk_Assessment_High,		//��ȷ���Է��շ���
			ST_Block_Pool_Size_By_Rank_High,				//�Ͳع�ģ���з�
			ST_Block_Exploration_Efficiency_Predication_High,//��̽Ч�����Ʒ�
			ST_Block_Non_Biased_Sample_Inference_High,		//��ƫȡ������
			ST_Block_Biased_Sample_Inference_High,			//��ƫȡ������
			ST_Block_Economic_Rapid_Assessment_High,		//���پ�������
			ST_Block_Block_Preference_High,					//��ѡ�Ŷ�
			ST_Block_Probability_Composition_Method,		//������ϼӺͷ�
			ST_Block_Delphi_Method,							//�¶��Ʒ�
			ST_Block_Economic_Evaluation,					//��������
			ST_Block_Decision_Methodology,					//��ѡ����
			ST_Block_Investment_Portfolio,					//Ͷ����Ϸ���
			ST_Performance_Static_Pressure,					//����ƽ�ⷨ
			ST_Performance_Flowing_Pressure,				//��������ƽ�ⷨ
			ST_Performance_Production_Pressure,				//��̬����ƽ�ⷨ
			ST_Performance_Material_Balance,				//����ʽ��������
			ST_Performance_MultiStage_Fracturing,			//����ƽ����̬��������
			ST_Performance_Non_Steady,						//����̬��������
			ST_Performance_characterCurveAnalysis,			//�������߷���
			ST_Trap_OilGas_Well_Analysis,					//�ɹ������� 143
			ST_Trap_Dry_Hole_Analysis,						//ʧ�ܾ����� 
			ST_Trap_POS_Adjustment,							//��������
			ST_Trap_EUR_Parameters_Analysis,				//EUR��������
			ST_Trap_EUR_Analysis,							//EURͳ�Ʒ���
			ST_Trap_DFI_Analysis,							//DFI����
			ST_Trap_Drilling_statistics,					//��̽ͳ��
			ST_Trap_Inventories_statistics,					//����ͳ��
			ST_Trap_Domain_Statistics,						//����ͳ��
			ST_Trap_Wildcat_statistics,						//Ԥ̽��ͳ��
			ST_Trap_Poat_drilling_statistics,				//���ͳ��
			ST_Trap_Trap_Identify_Table,					//Ȧ��ʶ��
			ST_Trap_H_Index_Balance,						//��ָ������ƽ�ⷨ
			ST_Trap_C_Index_Balance,						//�л�̼����ƽ�ⷨ
			ST_Trap_Bitumn_A,								//�ȷ�����A
			ST_Trap_Small_Patch,							//С��Ԫ
			ST_Max,
			ST_QuickSave_TinyVolParas,						//С��Ԫ���ٱ���
		};

		enum DocType
		{
			ID_Doc_UnknowType=0,
			ID_Doc_MineRightMap=1,
			ID_Doc_EXPDegreeMap=2,
			ID_Doc_EXPAchiveMap=3,
			ID_Doc_EXPDeployMap=4,
		};


		struct RecordSelection
		{
			long m_propertyidx;
			bool m_isselected;
			RecordSelection():m_propertyidx(-1),m_isselected(false)
			{
				
			}
			RecordSelection &operator=(const RecordSelection &other) 
			{
				m_propertyidx = other.m_propertyidx;
				m_isselected = other.m_isselected;
			}
			RecordSelection(const RecordSelection& other)
			{
				m_propertyidx = other.m_propertyidx;
				m_isselected = other.m_isselected;
			}
		};

		struct BlobParameter
		{
			char* m_blobdata;
			int m_bloblength;
			string m_explanation;
			int m_blobtype;
			int m_pos;

			BlobParameter():m_blobdata(NULL)
			{

			}
			~BlobParameter()
			{
				if(m_blobdata)
				{
					delete[] m_blobdata;
					//::free(m_blobdata);
					m_blobdata=NULL;
				}
			}
			BlobParameter(const BlobParameter& other)
			{
				m_bloblength=other.m_bloblength;
				m_explanation=other.m_explanation;
				m_blobtype=other.m_blobtype;
				m_pos=other.m_pos;
				if(other.m_blobdata)
				{
					//m_blobdata=new char[m_bloblength];
					m_blobdata =(char*)malloc(m_bloblength+sizeof(int));
					//memcpy(m_blobdata,other.m_blobdata,m_bloblength+sizeof(int));
					for(int i=0;i<m_bloblength+sizeof(int);i++)
					{
						m_blobdata[i]=other.m_blobdata[i];
					}
				}
				else
				{
					m_blobdata=NULL;
				}
			}
			BlobParameter &operator=(const BlobParameter &other) 
			{
				if(this == &other)
				{
					return *this;
				}
				m_bloblength=other.m_bloblength;
				m_explanation=other.m_explanation;
				m_blobtype=other.m_blobtype;
				m_pos=other.m_pos;
				if(other.m_blobdata)
				{
					m_blobdata =(char*)malloc(m_bloblength+sizeof(int));
					memcpy(m_blobdata,other.m_blobdata,m_bloblength+sizeof(int));
				}
				else
				{
					m_blobdata=NULL;
				}
				return *this;
			}
		};

		/*!
		*  record of "r_activity"
		**/
		struct ActivityRecord
		{
			long m_activityIdx;
			long m_parentIdx;
			long m_type;
			string m_name;
			string m_remark;
		};
		typedef std::vector<ActivityRecord> ActivityVector;

		/*!
		*  record of "r_activity_template"
		**/
		struct ActivityRecordSettings
		{
			string m_user;
			long m_templateIdx;
			string m_templatename;
			long m_activityIdx;
			long m_parentIdx;
			long m_type;
			string m_name;
			string m_remark;
			long m_index;
			bool m_isshown[50];
			int m_unitfor;
			bool m_iscurrenttemplate;
			bool m_isvalid[50];
			ActivityRecordSettings() : m_user(""), m_templateIdx(-1), m_templatename(""), m_activityIdx(0), m_parentIdx(-1), m_type(0), m_name(""), m_remark(""), m_index(-1), m_unitfor(0), m_iscurrenttemplate(false)
			{
				for(int i = 0; i < 50; i++)
				{
					m_isshown[i] = true;
					m_isvalid[i] = true;
				}
			}
		};
		typedef std::vector<ActivityRecordSettings*> ActivitySettingsVector;

		/*!
		* record of "a_practice"
		**/
		struct ActivityPracticeRecord
		{
			long			m_practiceIdx;
			long			m_elementIdx;
			long			m_managementphase;
			long			m_activityIdx;
			double			m_whendo;
			string			m_whodo;
			unsigned char	m_isApproved;
			long			m_templateIdx;
			double			m_npv;
			string			m_groupName;
			string			m_distributionName;
			string			m_distributionParameter;
			string			m_remark;
			string			m_recordtype;
			long			m_iscanreplace;
			/*!
			*
			**/
			ActivityPracticeRecord() : m_practiceIdx(0), m_elementIdx(0), m_activityIdx(0), m_whendo(0), m_whodo(""), m_isApproved(false),m_managementphase(CAnyTrapManagement::TEP_Preliminary | CAnyTrapManagement::TRA_Preliminary_Found),
				m_templateIdx(0), m_npv(0.), m_groupName(""), m_distributionName(""), m_distributionParameter(""), m_remark(""),m_recordtype("0"),m_iscanreplace(0)
			{
			}

			const ActivityPracticeRecord &operator=(const ActivityPracticeRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_practiceIdx				=other.m_practiceIdx;
				m_elementIdx				=other.m_elementIdx;
				m_managementphase			=other.m_managementphase;
				m_activityIdx				=other.m_activityIdx;
				m_whendo					=other.m_whendo;
				m_whodo						=other.m_whodo;
				m_isApproved				=other.m_isApproved;
				m_templateIdx				=other.m_templateIdx;
				m_npv						=other.m_npv;
				m_groupName					=other.m_groupName;
				m_distributionName			=other.m_distributionName;
				m_distributionParameter		=other.m_distributionParameter;
				m_remark					=other.m_remark;
				m_recordtype				=other.m_recordtype;
				m_iscanreplace				=other.m_iscanreplace;

				return *this;
			}




		};
		typedef std::vector<ActivityPracticeRecord> PracticeVector;

		/*!
		* record of "a_risk"
		**/
		struct ActivityRiskRecord
		{
			long m_practiceIdx;
			long m_elementIdx;
			long m_factorIdx;
			 // crisp value
			double m_maturity;
			// uncertainty value
			double m_minrisk; 
			double m_avgrisk;
			double m_maxrisk;
			double m_pshare;
			int m_probabilitytreeid;

			/*!
			*
			**/
			ActivityRiskRecord() : m_practiceIdx(0), m_elementIdx(0), m_factorIdx(0), m_maturity(0.), \
				m_minrisk(0.), m_avgrisk(0.), m_maxrisk(0.), m_pshare(0.), m_probabilitytreeid(-1)
			{
			}
		};
		typedef std::vector<ActivityRiskRecord> RiskVector;

		struct ActivityBlobDataRecord
		{
			long m_blobIdx;
			long m_practiceIdx;
			long m_parentpracticeIdx;
			long m_blobtype;
			long m_blobpos;
			string m_blobExplanation;
			char* m_blob ;
			int m_length;
			/*!
			*
			**/
			ActivityBlobDataRecord() : m_practiceIdx(0), m_blobIdx(0),m_parentpracticeIdx(0), m_blobtype(0),m_blobpos(0),m_blobExplanation(""),m_blob(NULL),m_length(0) 
			{
			}
			~ActivityBlobDataRecord()
			{
				if(m_blob)
				{
					delete[] m_blob;
					//::free(m_blob);
					m_blob=NULL;
				}
			}
			void SetBlob(char* data,int length)
			{
				//m_blob=(char*)malloc(length+sizeof(int));
				m_blob=new char[length+sizeof(int)];
				memcpy(m_blob,data,length+sizeof(int));
				m_length=length;
			}
			char* SerializeVec( int &len,std::vector<std::vector<string> >& vecdata )
			{
				char *data;
				int curSize=0;
				int rownums=vecdata.size();
				if(rownums<1)
				{
					return NULL;
				}
				int colnums=vecdata[0].size();

				curSize+=sizeof(int)*2;

				for(int i=0;i<rownums;i++){
					for(int j=0;j<colnums;j++){
						string val=vecdata[i][j];
						int length=val.length()+1;
						curSize+=sizeof(int);
						curSize+=length;
					}
				}
				data=(char*)malloc(curSize);
				memcpy(data,&rownums,sizeof(int));
				data+=sizeof(int);
				memcpy(data,&colnums,sizeof(int));
				data+=sizeof(int);


				for(int i=0;i<rownums;i++){
					for(int j=0;j<colnums;j++){
							string valstring=vecdata[i][j];
							int length=valstring.length()+1;
							//char* val=const_cast<char*>(valstring.c_str());
							char* val=new char[length];
							for(int k=0;k<length-1;k++){
								val[k]=valstring.at(k);
							}
							val[length-1]='\0';
							int length2=strlen(val)+1;
							
							memcpy(data,&length,sizeof(int));
							data+=sizeof(int);
							memcpy(data,val,length);
							data+=length;
							delete[] val;
						}
				}
				data-=curSize;
				len=curSize;
				//memcpy(memory,&memory,curSize);
				return data;
			}

			void RestoreVec(char* data,std::vector<std::vector<string> >& vecdata )
			{
				int rowcount=0;
				memcpy(&rowcount,data,sizeof(int));
				data+=sizeof(int);
				int colcount=0;
				memcpy(&colcount,data,sizeof(int));
				data+=sizeof(int);
			
				int *len=new int[rowcount*colcount];
				char **val=new char*[rowcount*colcount];
				for(int i=0;i<rowcount*colcount;i++){
					
					memcpy(&len[i],data,sizeof(int));
					data+=sizeof(int);
					val[i]=new char[len[i]];
					memcpy(val[i],data,len[i]);
					data+=len[i];
				}
				for(int i=0;i<rowcount;i++)
				{
					std::vector<string> rowVec;
					for(int j=0;j<colcount;j++)
					{
						string sval(val[i*colcount+j]); 
						rowVec.push_back(sval);
					}
					vecdata.push_back(rowVec);
				}
				
				delete[] len;
				for(int i=0;i<rowcount*colcount;i++){
					delete[] val[i];
				}
				delete[] val;
			}

			void SetBlob(std::vector<std::vector<string> >& vecdata)
			{
				
				//m_blob=(char*)malloc(length+sizeof(int));
				int length=0;
				char* data=SerializeVec(length,vecdata);
				m_blob=new char[length];
				memcpy(m_blob,data,length);
				m_length=length;
				delete[] data;

			}

			void SetBlob2(std::vector<std::vector<std::vector<string> >> & vecdata)
			{
				if(vecdata.size()<=0)
				{
					return;
				}
				int alllength = sizeof(int);
				char* alldata;
				int allrow = vecdata.size();
				for(int i=0;i<vecdata.size();i++)
				{
					int length=0;
					char* data=SerializeVec(length,vecdata[i]);
					alllength= alllength+length+sizeof(int);
					
					delete[] data;
				}
				alldata=(char*)malloc(alllength);
				memcpy(alldata,&allrow,sizeof(int));
				alldata = alldata+sizeof(int);
			
				for(int i=0;i<vecdata.size();i++)
				{
					int length=0;
					char* data=SerializeVec(length,vecdata[i]);
					
					memcpy(alldata,&length,sizeof(int));
					alldata =alldata+sizeof(int);

					memcpy(alldata,data,length);
					alldata = alldata +length;
					delete[] data;
				}
				m_length=alllength;
				m_blob=new char[alllength];
				memcpy(m_blob,alldata,alllength);
			}

			void RestoreVec2(char* data,std::vector<std::vector<std::vector<string> >> & vecdata)
			{
				vecdata.clear();
				int allcount=0;
				memcpy(&allcount,data,sizeof(int));
				data+=sizeof(int);

				for(int i=0;i<allcount;i++)
				{
					int length=0;
					memcpy(&length,data,sizeof(int));
					data = data + sizeof(int);
					char *perdata;
					perdata=(char*)malloc(length);
					memcpy(perdata,data,length);

					std::vector<std::vector<string>> pervecdata;
					RestoreVec(perdata,pervecdata);
					vecdata.push_back(pervecdata);

					data = data + length;
				}
			}

			ActivityBlobDataRecord(const ActivityBlobDataRecord& other){
				 m_practiceIdx=other.m_practiceIdx;
				 m_blobIdx=other.m_blobIdx;
				 m_parentpracticeIdx=other.m_parentpracticeIdx;
				 m_blobtype=other.m_blobtype ; 
				 m_blobpos=other.m_blobpos;
				m_length=other.m_length;
				m_blobExplanation=other.m_blobExplanation;
				if(other.m_blob)
				{
					//m_blob=(char* )malloc(m_length+sizeof(int));
					m_blob=new char[m_length+sizeof(int)];
					memcpy(m_blob,other.m_blob,m_length+sizeof(int));
					/*for(int i=0;i<m_length;i++){
						m_blob[i]=other.m_blob[i];
					}*/
				}
				else
				{
					m_blob=NULL;
				}

			}

			const ActivityBlobDataRecord &operator=(const ActivityBlobDataRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_practiceIdx=other.m_practiceIdx;
				m_parentpracticeIdx=other.m_parentpracticeIdx;
				m_blobIdx=other.m_blobIdx ; 
				m_blobtype=other.m_blobtype ; 
				m_length=other.m_length;
				m_blobpos=other.m_blobpos;
				m_blobExplanation=other.m_blobExplanation;
				if(other.m_blob)
				{
					//m_blob=(char* )malloc(m_length+sizeof(int));
					if(m_blob)
					{
						delete[] m_blob;
					}
					m_blob=new char[m_length+sizeof(int)];
					memcpy(m_blob,other.m_blob,m_length+sizeof(int));
				}
				else
				{
					if(m_blob)
					{
						delete[] m_blob;
					}
					m_blob=NULL;
				}
				return *this;
			}
		};
		typedef std::vector<ActivityBlobDataRecord> PracticeBlobDataVector;

		/*!
		* record of "a_resource"
		**/
		struct ActivityResourceRecord
		{
			long   m_practiceIdx;
			long   m_elementIdx;
			string m_kindName; // resource kind such as oil, gas, oil/gas, etc
			string m_categoryName; // resource type such as in-place, or reserve
			string m_className; // resource class. for in-place, it includes ...
			string m_groupName; // "" means all
			long   m_minN;
			long   m_avgN;
			long   m_maxN;
			double m_minPool; // P90
			double m_avgPool; // P50
			double m_maxPool; // P5
			double m_meanQ;
			double m_stdQ;
			double m_minQ;
			double m_avgQ;
			double m_maxQ;
			/*!
			*
			**/
			ActivityResourceRecord() : m_practiceIdx(0), m_elementIdx(0), m_kindName(""), m_categoryName(""), m_className(""), m_groupName(""), m_minN(0), m_avgN(0), m_maxN(0), m_minPool(0.), m_avgPool(0.), m_maxPool(0.), \
				m_meanQ(0.), m_stdQ(0.), m_avgQ(0.), m_minQ(0.), m_maxQ(0.)
			{
			}

			const ActivityResourceRecord &operator=(const ActivityResourceRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_practiceIdx	=other.m_practiceIdx;
				m_elementIdx	=other.m_elementIdx;
				m_kindName 		=other.m_kindName;  
				m_categoryName	=other.m_categoryName;
				m_className		=other.m_className; 
				m_groupName 	=other.m_groupName; 
				m_minN			=other.m_minN;
				m_avgN			=other.m_avgN;
				m_maxN			=other.m_maxN;
				m_minPool		=other.m_minPool; 
				m_avgPool		=other.m_avgPool; 
				m_maxPool		=other.m_maxPool; 
				m_meanQ			=other.m_meanQ;
				m_stdQ			=other.m_stdQ;
				m_minQ			=other.m_minQ;
				m_avgQ			=other.m_avgQ;
				m_maxQ			=other.m_maxQ;



				return *this;
			}
		};
		typedef std::vector<ActivityResourceRecord> ResourceVector;

		/*!
		*
		**/
		struct ActivityParameterRecord
		{
			long   m_practiceIdx;
			long   m_elementIdx;
			string m_probName;
			string m_probPara;
			long   m_fractiles;
			string m_parameter; // predication setting

			/*!
			*
			**/
			ActivityParameterRecord() : m_practiceIdx(0), m_elementIdx(0), m_probName(""), m_probPara(""), m_fractiles(0), m_parameter("")
			{
			}

			const ActivityParameterRecord &operator=(const ActivityParameterRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_practiceIdx =other.m_practiceIdx;
				m_elementIdx  =other.m_elementIdx;
				m_probName	  =other.m_probName;
				m_probPara	  =other.m_probPara;
				m_fractiles	  =other.m_fractiles;
				m_parameter	  =other.m_parameter; 

				return *this;
			}


		};
		typedef std::vector<ActivityParameterRecord> ParameterVector;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAccumulationAssessor(CAccumulationElement *curElement, int activityType);

		/*!
		*
		**/
		virtual ~CAccumulationAssessor();

	public:
		//
		// acitivity persistence issues
		//
		/*!
		*
		**/
		virtual void Load();

		/*!
		*
		**/
		int GetPracticeCount();

		/*!
		*
		**/
		const ActivityPracticeRecord &GetPracticeRecord(int index);

		/*!
		*
		**/
		bool DeletePracticeRecord(long practiceIdx);
		
		/*!
		*
		**/
		bool ApprovePracticeRecord(long practiceIdx, bool isApproved = true);

		/*!
		*
		**/
		bool UpdateRemarkPracticeRecord(long practiceIdx, const string &remark);

		/*!
		*
		**/
		const void GetParameterRecord(long practiceIdx, ParameterVector &parameters);

		/*!
		*
		**/
		const void GetResourceRecord(long practiceIdx, ResourceVector &resources);

		/*!
		*
		**/
		const void GetRiskRecord(long practiceIdx, RiskVector &risks);
		/*!
		*
		**/
		const void GetBlobRecord(long practiceIdx, PracticeBlobDataVector &blobs);
		//
		//
		//
		/*!
		*
		**/
		const string &GetName() const
		{
			return m_name;
		}

		/*!
		*
		**/
		void SetName(const string &name)
		{
			m_name = name;
		}

		/*!
		*
		**/
		CAccumulationElement *GetElement()
		{
			assert(m_element);
			return m_element;
		}

		/*!
		*
		**/
		bool IsActivityEnable(unsigned long activityType);

		//
		// activity hierarchy
		//
		/*!
		* 0 - for play, 1 - for trap
		**/
		static bool InitActivityRecords(int type = 0);
		
		/*!
		*
		**/
		static bool InitActivityTemplate(CAnyAccessor &accessor, string username, int type = 0);
		
		/*!
		*
		**/
		static bool GetActivityTreeSettings(string username, int templateIdx, ActivitySettingsVector &activitysettings);

		/*!
		*
		**/
		static bool GetInuseActivityTreeSettings(string username, ActivitySettingsVector &activitysettings, int unitfor);
		/*!
		*
		**/
		static int CommitActivityTreeSettings(ActivitySettingsVector &activitysettings);

		/*!
		*
		**/
		static bool GetActivityTreeSettingsFromRefTable(ActivitySettingsVector &activitysettings);

		/*!
		*
		**/
		static bool LoadActivityTreeSettingsRecords(string username, std::vector<int> &templateids, std::vector<string> &templatenames);

		/*!
		*
		**/
		static bool DeleteTemplate(int templateid);

		/*!
		*
		**/
		static bool DeleteAllTemplate();

		/*!
		*
		**/
		static int GetActivityRecordCount();

		/*!
		*
		**/
		static const ActivityRecord &GetAcitivityRecord(long order);

		/*!
		*
		**/
		static long GetActivityIdx(unsigned short type);

		/*!
		*2015/4/29:from activity to st_type
		**/
		static long GetActivityType(long activityIdx);

		/*!
		*
		**/
		static void GetPracticeRecordsByPracticeId(long practiceId, PracticeVector &practices);

		/*!
		*
		**/
		static bool CompareActivityRecord(const ActivityRecord &first, const ActivityRecord &second);

		/*!
		*
		**/
		static bool CompareActivitySettingsRecord(const ActivityRecordSettings *first, const ActivityRecordSettings *second);

		/*!
		*
		**/
		static bool CompareActivitySettingsRecordByActivityId(const ActivityRecordSettings *first, const ActivityRecordSettings *second);

		/*!
		*
		**/
		static bool LoadActivityResourceDetail(long practiceid, long elementid, long activityid, std::vector<CGeoPoint<double> > &geologicalsamples, std::vector<CGeoPoint<double> > &recoverysamples, string type = "");

		/*!
		*
		**/
		static void GetResFromSamples(std::vector<CGeoPoint<double> > &geologicalsamples,double &p10,double &p50,double &p90);
	
		/*!
		*
		**/
		static bool SaveActivityResourceDetail(long practiceid, long elementid, long activityid, std::vector<CGeoPoint<double> > &geologicalsamples, std::vector<CGeoPoint<double> > &recoverysamples, string type = "");
		
		/*!
		*
		**/
		static bool LoadActivityResourceDetailTypeString(long practiceid, long elementid, long activityid, std::vector<string> &geologicalsamples, string type = "");

		/*!
		*
		**/
		static bool SaveActivityResourceDetailTypeString(long practiceid, long elementid, long activityid, std::vector<string> &geologicalsamples, string type = "");

		/*!
		*
		**/
		static void GetResourceDetailType(long practiceid, long elementid, long activityid, std::vector<string> &types);

		/*!
		*
		**/
		static bool CompareActivityName(string name1, string name2);

		/*!
		*
		**/
		static void GetResourceRecordByPracticeIdx(long practiceIdx, int activetype,ResourceVector &resourcerecord);

		/*!
		*
		**/
		static long FromEATtoST(long EATactivityType);
		
		/*!
		*
		**/
		static long FromSTtoEAT(long STactivityType);

		/*!
		*
		**/
		static void SetTrapEvalueStep(string &trap ,long elementidx);

		/*!
		*
		**/
		static void GetTrapEvalueStep(string &trap ,long elementidx);

		/*!
		*
		**/
		static void GetVolPracticeContentProspectValuePracticeidx(string practiceidx,std::vector<long> &idxs);

		/*!
		*
		**/
		static bool AddBlobDataPracticeRecord(long practiceidx, ActivityBlobDataRecord &blobdataRecord);
		static bool DoInsertPracticeRecord(CAnyAccessor &accessor, ActivityPracticeRecord &practiceRecord);

		

		
		/*!
		*
		**/
		static bool LoadBlobDataPracticeRecord(std::vector<ActivityPracticeRecord> &practiceRecords,long activityid,long elementid=0);
		static bool DeleteBlobDataPracticeRecord( long practiceidx,long elementid=0 );
		static bool UpdataBlobDataPracticeRecord(string &remark ,long practiceidx,long elementid=0 );
		static void GetBlobRecordByPractice(long practiceIdx, PracticeBlobDataVector &blobs);

		static int LoadTrapTypeByElementID(long idx);
		static void SetTrapTypeByElementID(long idx,int type,string &name);
		static bool IsTrapRecordExist(long idx);

		static void GetActivityTemplateNameByType(int type ,string &name);
		static int  GetActivityTemplateIdxByName( string &name );

		static void LoadP10P90Check(long idx,double &up,double &down);
		static void LoadNpvExpandDevCostbyPractice(long practiceid,double &devcost,double &expcost);
	
		static void GetStdQbyPracticeandElementid(long practiceid,long elementidx,double &stdQ);
		static bool SetStdQbyPracticeandElementid(long practiceid,long elementidx,double stdQ);

		static bool SetVolParaRes(long elementidx,int restype,int phasetype,double res);

		static bool UpdataShaleWellFormula( long elementid,string &formula );

		static long GetFileNameFromdocblobByDocDefineType(long elementid,int docdefine,string &name );
	protected:
		//
		//
		//
		/*!
		*
		**/
		bool AddPracticeRecord(CAnyAccessor &accessor, ActivityPracticeRecord &practiceRecord);

		/*!
		*
		**/
		bool AddRiskRecord(ActivityPracticeRecord &practiceRecord, ActivityRiskRecord &riskRecord, ActivityParameterRecord &parameter);

		/*!
		* isFirstPractce to control the PracticeRecord only be inserted once
		**/
		bool AddResourceRecord(ActivityPracticeRecord &practiceRecord, ActivityResourceRecord &resourceRecord, ActivityParameterRecord &parameter, bool isFirstPractice = true);
		/*!
		*
		**/
		bool AddSpatialRecord(ActivityPracticeRecord &practiceRecord,ActivityParameterRecord &parameter);

		/*!
		* 
		**/
		bool AddBlobDataRecord(ActivityPracticeRecord &practiceRecord, ActivityBlobDataRecord &blobdataRecord);


	public:
		//
		//
		//
		/*!
		*
		**/
		//static bool DoInsertPracticeRecord(CAnyAccessor &accessor, ActivityPracticeRecord &practiceRecord);

		/*!
		*
		**/
		static bool DoInsertRiskRecord(CAnyAccessor &accessor, ActivityRiskRecord &riskRecord);

		/*!
		*
		**/
		bool DoInsertParameterRecord(CAnyAccessor &accessor, ActivityParameterRecord &paraRecord);

		bool DoInsertResourceRecord(CAnyAccessor &accessor, ActivityResourceRecord &resourceRecord);

		/*!
		*
		**/
		static void DoLoadPracticeRecord(CAnyAccessor &accessor, PracticeVector &practices);

		/*!
		*
		**/
		void DoLoadParameterRecord(CAnyAccessor &accessor, ParameterVector &parameters);

		/*!
		*
		**/
		void DoLoadResourceRecord(CAnyAccessor &accessor, ResourceVector &parameters);

		/*!
		*
		**/
		void DoLoadRiskRecord(CAnyAccessor &accessor, RiskVector &parameters);

		/*!
		*
		**/
		static void DoLoadBlobRecord(CAnyAccessor &accessor, PracticeBlobDataVector &parameters);
		//
		// remove those objects in memory
		//
		/*!
		*
		**/
		void DoRemoveResourceObject(long practiceIdx);

		/*!
		*
		**/
		void DoRemoveRiskObject(long practiceIdx);

		/*!
		*
		**/
		void DoRemoveParameterObject(long practiceIdx);

		/*!
		*
		**/
		void DoRemovePracticeObject(long practiceIdx);

		//
		//
		//
		/*!
		*
		**/
		bool IsSpecifyScoringTemplate();

		/*!
		*
		**/
		bool IsHasActivityPractice(long activityType);

		/*!
		*
		**/
		bool IsExistPracticeRecord(long activityIdx);
public:
		/*!
		*
		**/
		bool RegisterFunctor(int type,CAnyFunctor *func);

		/*!
		*
		**/
		bool RemoveFunctor(int type);
		
		/*!
		*
		**/		
		bool IsPracticeExist(long practiceIdx, const string& remark);

		/*!
		*
		**/		
		bool IsPracticeExist(long practiceIdx, bool remark);

		//
		//
		//
		/*!
		*
		**/
		static void DoLoadActivityRecords(CAnyAccessor &accessor);

		/*!
		*
		**/
		static bool DoAddActivityRecord(CAnyAccessor &accessor, const ActivityRecord &activity);

		/*!
		*
		**/
		static bool DoAddActivityRecordToTemplate(CAnyAccessor &accessor, string username, const ActivityRecord &activity, int templateIdx, string templatename, int indexvalue, string isshown, int unitfor, int iscurrenttemplate, string isvalid);

		//
		//
		//
		/*!
		*
		**/
		static bool ComparePracticeIdx(const ActivityPracticeRecord &first, const ActivityPracticeRecord &second)
		{
			return first.m_practiceIdx < second.m_practiceIdx;
		}

		/*!
		*
		**/
		static bool CompareParameterIdx(const ActivityParameterRecord &first, const ActivityParameterRecord &second)
		{
			return first.m_practiceIdx < second.m_practiceIdx;
		}

		/*!
		*
		**/
		static bool CompareResourceIdx(const ActivityResourceRecord &first, const ActivityResourceRecord &second)
		{
			return first.m_practiceIdx < second.m_practiceIdx;
		}

		/*!
		*
		**/
		static bool CompareRiskIdx(const ActivityRiskRecord &first, const ActivityRiskRecord &second)
		{
			return first.m_practiceIdx < second.m_practiceIdx;
		}
		
		/*!
		*
		**/
		static bool CompareBlobDataIdx(const ActivityBlobDataRecord &first, const ActivityBlobDataRecord &second)
		{
			return first.m_practiceIdx < second.m_practiceIdx;
		}

		static bool IsPracticeRecordCanReplace(long practicidx);
		static bool UpdatePracticeRecordCanReplace(long practicidx,long elementidx,long activityidx);

	public:
		// host element
		CAccumulationElement *m_element;
	protected:
		// persistence 
		PracticeVector m_practices;
		RiskVector m_risks;
		ResourceVector m_resources;
		ParameterVector m_parameters;
		PracticeBlobDataVector m_blobdataVec;
		std::map<int,CAnyFunctor*> m_functorMap;

	private:
		// activity hierarchy
		static ActivityVector m_activities;

	public:
		// activity-related tables
		static string m_refTable;
		static string m_refActivitySettingsTable;
		static string m_practiceTable;
		static string m_riskTable;
		static string m_resourceTable;
		static string m_parameterTable;
		static string m_resourcedetailTable;
		static string m_blobdataTable;
	};
}
#endif