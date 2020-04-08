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
		// ���۽׶Σ�һ���������״̬����������ǰ���״̬
		enum TrapEvaluationPhase
		{
			TEP_Preliminary = 1 << 29,							// ��̽ǰ���ۣ�����ҳ��������������Ϣ��Ȧ��Ҫ�ء�����������	���������������������Ԥ̽��������Ԥ̽������
			TEP_Verification = 1 << 30,							// ��̽�����ۣ�����ҳ��������������Ϣ��Ȧ��Ҫ�ء�����������	������������������� ��Ԥ̽��������Ԥ̽�����ȡ������Ϣ
		};

		// ���۽׶ζ�Ӧ��Ȧ�ձ䶯
		enum TrapReserveAdjustment
		{	
			TRA_Preliminary_Found													= 1, 										// ��̽ǰ���·��֣�����״̬���½��������ݿ��ʱ������Ȧ�ճ��⣬RECOGTIMES=0��
			TRA_Preliminary_Audit_GradeUp											= 1 << 1,									// ��̽ǰ����������������״̬
			TRA_Preliminary_Audit_GradeDown											= 1 << 2,									// ��̽ǰ�����齵�����Ǵ������Ӵ��������ߣ���Ϊ����Ȧ�գ�
			TRA_Preliminary_Describe_GradeUp										= 1 << 3,									// ��̽ǰ����������������״̬
			TRA_Preliminary_Describe_GradeDown										= 1 << 4,									// ��̽ǰ�������������Ǵ������Ӵ��������ߣ���Ϊ����Ȧ�գ�

			//2016/12/27:original reserve status
			TRA_Preliminary_Original_Reserve										= 1 << 5,				                    // ��̽ǰ��ԭ����������״̬

			TRA_Verification_GradeUp_Production										= 1 << 16,									// ��̽��������Ԥ̽�����������Ǵ������Ӵ��������ߣ���������⣩�����״̬�����״̬��
			TRA_Verification_GradeDown_Discard										= 1 << 17,									// ��̽�󣬽�����������III�ࣩ���Ǵ������Ӵ��������ߣ���������⣩�����״̬�����״̬��
			TRA_Verification_Describe_Reserve										= 1 << 18,									// ��̽����󴢱�������״̬
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
		// ����ģʽ
		static CAnyTrapManagement &GetSingleton();

		// ��һ�����۲��������۽׶Σ��ڶ���������Ȧ�ձ䶯״̬
		unsigned long MakeManagementPhase(unsigned long evaluationphase, unsigned long reservephase);
		string IsValidPhase(long elementidx, unsigned long managementphase);
		string IsValidPhase1(long elementidx, unsigned long managementphase);
		string IsValidPhase2(long elementidx, unsigned long managementphase);
		string IsValidPhase3(long elementidx, unsigned long managementphase);
		string IsValidPhase4(long elementidx, unsigned long managementphase, string trapsphasetype);
		// ����ʶ��״̬
		bool CommitManagementPhase(long elementidx, unsigned long managementphase);

		// ��ȡʶ���������Ӧi_el_trap_project�����ֶΣ�BLOB����identificaitonprocess����׷��MANAGEMENTPHASE
		long GetEvaluationNumber(long elementidx);
		// ��ȡĳһ��ʶ��MANAGEMENTPHASE
		unsigned long GetEvaluationManagementPhase(long elementidx, long order);
		unsigned long GetLatestManagementPhase(long elementidx);
		string GetManagementPhaseName(unsigned long managementphase);
		unsigned long GetManagementPhase(const std::string &name);


		// �Ƿ��Ǵ���Ȧ�գ�������ELEMENT ID
		bool IsReservedTrapWithElement(long elementidx);
		bool IsReservedTrapWithPhase(unsigned long managementphase);
		bool IsDiscardTrapWithElement(long elementidx);
		bool IsDiscardTrapWithPhase(unsigned long managementphase);
		bool IsPhaseCorrect( long phase );//�ж�ĳ��phase�Ƿ�Ϸ�

		// ��ȡ��ǰ��������»
		std::vector<unsigned long> GetManagementPracticeIdx(long elementidx, unsigned long managementphase, long activitytype);

		// ��ȡ���������elementid������
		void GetElementidRangeByOilField(std::vector<string> &fieldnames, std::vector<int> &elementidmins, std::vector<int> &elementidmaxs);

		// ��ȡ���������״̬������������������
		void GetElementidState(std::map<int, int> &elementid_state);
		int GetElementidStateSingle(int elementid);
	};
}
#endif