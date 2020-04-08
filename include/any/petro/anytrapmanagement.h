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
#ifndef __ANYPETRO_TRAP_MANAGEMENT_H__
#define __ANYPETRO_TRAP_MANAGEMENT_H__

// refer to EXPORT etc macroes
#include "anypetro.h"

#include "any/base/anystl.h"

#include "any/base/loki/singleton.h"
using namespace AnyBase::Loki;

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CAnyTrapManagement
	{
		// sinleton
		typedef SingletonHolder<CAnyTrapManagement, CreateUsingNew> Singleton;

	public:
		// 评价阶段：一旦进入钻后状态，不能切钻前相关状态
		enum TrapEvaluationPhase
		{
			TEP_Preliminary = 1 << 29,							// 钻探前评价，属性页：基本、管理信息、圈闭要素、断裂特征、	体积三参数、参数样本、预探井基本、预探井进度
			TEP_Verification = 1 << 30,							// 钻探后评价，属性页：基本、管理信息、圈闭要素、断裂特征、	体积三参数、参数样本 、预探井基本、预探井进度、钻后信息
		};

		// 评价阶段对应的圈闭变动
		enum TrapReserveAdjustment
		{	
			TRA_Preliminary_Found													= 1, 										// 钻探前，新发现，储备状态（新建或导入数据库的时候，三类圈闭除外，RECOGTIMES=0）
			TRA_Preliminary_Audit_GradeUp											= 1 << 1,									// 钻探前，复查升级，储备状态
			TRA_Preliminary_Audit_GradeDown											= 1 << 2,									// 钻探前，复查降级，非储备（从储备库移走，变为三类圈闭）
			TRA_Preliminary_Describe_GradeUp										= 1 << 3,									// 钻探前，描述升级，储备状态
			TRA_Preliminary_Describe_GradeDown										= 1 << 4,									// 钻探前，描述降级，非储备（从储备库移走，变为三类圈闭）

			//2016/12/27:original reserve status
			TRA_Preliminary_Original_Reserve										= 1 << 5,				                    // 钻探前，原储备，储备状态

			TRA_Verification_GradeUp_Production										= 1 << 16,									// 钻探后，升级（预探到开发），非储备（从储备库移走，进入核销库）（这个状态是最后状态）
			TRA_Verification_GradeDown_Discard										= 1 << 17,									// 钻探后，降级（储备到III类），非储备（从储备库移走，进入核销库）（这个状态是最后状态）
			TRA_Verification_Describe_Reserve										= 1 << 18,									// 钻探后，钻后储备，储备状态
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyTrapManagement();
		~CAnyTrapManagement();

	private:
		CAnyTrapManagement(const CAnyTrapManagement &other);
		const CAnyTrapManagement &operator=(const CAnyTrapManagement &other);

	public:
		// 单例模式
		static CAnyTrapManagement &GetSingleton();

		// 第一个评价参数：评价阶段，第二个参数：圈闭变动状态
		unsigned long MakeManagementPhase(unsigned long evaluationphase, unsigned long reservephase);
		string IsValidPhase(long elementidx, unsigned long managementphase);
		string IsValidPhase1(long elementidx, unsigned long managementphase);
		string IsValidPhase2(long elementidx, unsigned long managementphase);
		string IsValidPhase3(long elementidx, unsigned long managementphase);
		string IsValidPhase4(long elementidx, unsigned long managementphase, string trapsphasetype);
		// 保存识别状态
		bool CommitManagementPhase(long elementidx, unsigned long managementphase);

		// 获取识别次数，对应i_el_trap_project的新字段（BLOB）（identificaitonprocess），追加MANAGEMENTPHASE
		long GetEvaluationNumber(long elementidx);
		// 获取某一次识别MANAGEMENTPHASE
		unsigned long GetEvaluationManagementPhase(long elementidx, long order);
		unsigned long GetLatestManagementPhase(long elementidx);
		string GetManagementPhaseName(unsigned long managementphase);
		unsigned long GetManagementPhase(const std::string &name);


		// 是否是储备圈闭，参数是ELEMENT ID
		bool IsReservedTrapWithElement(long elementidx);
		bool IsReservedTrapWithPhase(unsigned long managementphase);
		bool IsDiscardTrapWithElement(long elementidx);
		bool IsDiscardTrapWithPhase(unsigned long managementphase);
		bool IsPhaseCorrect( long phase );//判断某个phase是否合法

		// 获取钻前或钻后最新活动
		std::vector<unsigned long> GetManagementPracticeIdx(long elementidx, unsigned long managementphase, long activitytype);

		// 获取各个油田的elementid上下限
		void GetElementidRangeByOilField(std::vector<string> &fieldnames, std::vector<int> &elementidmins, std::vector<int> &elementidmaxs);

		// 获取各个对象的状态，储备，核销，Ⅲ类
		void GetElementidState(std::map<int, int> &elementid_state);
		int GetElementidStateSingle(int elementid);
	};
}
#endif