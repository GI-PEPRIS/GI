#ifndef __ANYPETRO_TEMPLATEDATA_H__
#define __ANYPETRO_TEMPLATEDATA_H__
#include "riskquickscore.h"
#include "riskfuzzyscore.h"
// refer to AnyDB relatives
#include "any/db/anyaccessor.h"
using namespace AnyDB;

#include "any/base/anytokenstring.h"
#include "any/base/anydbgmacro.h"
#include "any/base/anystringbasic.h"
#include "any/base/anytimebasic.h"
#include "any/base/anystl.h"
using namespace AnyBase;

namespace AnyPetro
{
	class CTempalteData{
	public:
		CTempalteData(){Init();}
		~CTempalteData(){;}
		void Init();
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//simple version
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		CRiskQuickScore::QuickScoreTemplate tempalte66;
		CRiskQuickScore::ScoreFactor factor1628;
		CRiskQuickScore::ScoreFactor factor1629;
		CRiskQuickScore::ScoreFactor factor1630;
		CRiskQuickScore::ScoreFactor factor1631;

		//order of lower and upper field is wrong
		CRiskQuickScore::QuickScoreStandard qstandard1621;
		CRiskQuickScore::QuickScoreStandard qstandard1622;
		CRiskQuickScore::QuickScoreStandard qstandard1623;
		CRiskQuickScore::QuickScoreStandard qstandard1624;
		CRiskQuickScore::QuickScoreStandard qstandard1625;
		CRiskQuickScore::QuickScoreStandard qstandard1626;
		CRiskQuickScore::QuickScoreStandard qstandard1627;

		
		/*	CRiskFuzzyScore::FuzzyScoreStandard fstandard1645;
		CRiskFuzzyScore::FuzzyScoreStandard fstandard1646;
		CRiskFuzzyScore::FuzzyScoreStandard fstandard1647;
		CRiskFuzzyScore::FuzzyScoreStandard fstandard1648;
		CRiskFuzzyScore::FuzzyScoreStandard fstandard1649;*/

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardSimpleVec;
		/*CRiskQuickScore::QuickScoreRule qrule1A1628;
		CRiskQuickScore::QuickScoreRule qrule2A1628;
		CRiskQuickScore::QuickScoreRule qrule3A1628;
		CRiskQuickScore::QuickScoreRule qrule4A1628;
		CRiskQuickScore::QuickScoreRule qrule5A1628;
		CRiskQuickScore::QuickScoreRule qrule1A1629;
		CRiskQuickScore::QuickScoreRule qrule2A1629;
		CRiskQuickScore::QuickScoreRule qrule3A1629;
		CRiskQuickScore::QuickScoreRule qrule4A1629;
		CRiskQuickScore::QuickScoreRule qrule5A1629;
		CRiskQuickScore::QuickScoreRule qrule1A1630;
		CRiskQuickScore::QuickScoreRule qrule2A1630;
		CRiskQuickScore::QuickScoreRule qrule3A1630;
		CRiskQuickScore::QuickScoreRule qrule4A1630;
		CRiskQuickScore::QuickScoreRule qrule5A1630;
		CRiskQuickScore::QuickScoreRule qrule1A1631;
		CRiskQuickScore::QuickScoreRule qrule2A1631;
		CRiskQuickScore::QuickScoreRule qrule3A1631;
		CRiskQuickScore::QuickScoreRule qrule4A1631;
		CRiskQuickScore::QuickScoreRule qrule5A1631;*/

		std::vector<CRiskQuickScore::QuickScoreRule> qruleSimpleVec;



		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//normal version
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		CRiskQuickScore::QuickScoreTemplate tempalte67;

		CRiskQuickScore::ScoreFactor factor515;
		CRiskQuickScore::ScoreFactor factor516;
		CRiskQuickScore::ScoreFactor factor517;
		CRiskQuickScore::ScoreFactor factor518;;

		CRiskQuickScore::ScoreFactor factor519;;
		CRiskQuickScore::ScoreFactor factor520;
		CRiskQuickScore::ScoreFactor factor521;
		CRiskQuickScore::ScoreFactor factor522;

		CRiskQuickScore::ScoreFactor factor523;
		CRiskQuickScore::ScoreFactor factor524;
		CRiskQuickScore::ScoreFactor factor525;

		CRiskQuickScore::ScoreFactor factor526;
		CRiskQuickScore::ScoreFactor factor527;
		CRiskQuickScore::ScoreFactor factor528;

		CRiskQuickScore::ScoreFactor factor529;
		CRiskQuickScore::ScoreFactor factor530;
		CRiskQuickScore::ScoreFactor factor531;

		CRiskQuickScore::QuickScoreStandard qstandard503;
		CRiskQuickScore::QuickScoreStandard qstandard504;
		CRiskQuickScore::QuickScoreStandard qstandard505;
		CRiskQuickScore::QuickScoreStandard qstandard506;
		CRiskQuickScore::QuickScoreStandard qstandard507;
		CRiskQuickScore::QuickScoreStandard qstandard508;
		CRiskQuickScore::QuickScoreStandard qstandard509;

		/*CRiskFuzzyScore::FuzzyScoreStandard fstandard510;;
		CRiskFuzzyScore::FuzzyScoreStandard fstandard511;
		CRiskFuzzyScore::FuzzyScoreStandard fstandard512;
		CRiskFuzzyScore::FuzzyScoreStandard fstandard513;
		CRiskFuzzyScore::FuzzyScoreStandard fstandard514;*/

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardNormalVec;

		/*CRiskQuickScore::QuickScoreRule qrule1A515;
		CRiskQuickScore::QuickScoreRule qrule2A515;
		CRiskQuickScore::QuickScoreRule qrule3A515;
		CRiskQuickScore::QuickScoreRule qrule4A515;
		CRiskQuickScore::QuickScoreRule qrule5A515;
		CRiskQuickScore::QuickScoreRule qrule1A516;
		CRiskQuickScore::QuickScoreRule qrule2A516;
		CRiskQuickScore::QuickScoreRule qrule3A516;
		CRiskQuickScore::QuickScoreRule qrule4A516;
		CRiskQuickScore::QuickScoreRule qrule5A516;
		CRiskQuickScore::QuickScoreRule qrule1A517;
		CRiskQuickScore::QuickScoreRule qrule2A517;
		CRiskQuickScore::QuickScoreRule qrule3A517;
		CRiskQuickScore::QuickScoreRule qrule4A517;
		CRiskQuickScore::QuickScoreRule qrule5A517;
		CRiskQuickScore::QuickScoreRule qrule1A518;
		CRiskQuickScore::QuickScoreRule qrule2A518;
		CRiskQuickScore::QuickScoreRule qrule3A518;
		CRiskQuickScore::QuickScoreRule qrule4A518;
		CRiskQuickScore::QuickScoreRule qrule5A518;
		CRiskQuickScore::QuickScoreRule qrule1A519;
		CRiskQuickScore::QuickScoreRule qrule2A519;
		CRiskQuickScore::QuickScoreRule qrule3A519;
		CRiskQuickScore::QuickScoreRule qrule4A519;
		CRiskQuickScore::QuickScoreRule qrule5A519;
		CRiskQuickScore::QuickScoreRule qrule1A520;
		CRiskQuickScore::QuickScoreRule qrule2A520;
		CRiskQuickScore::QuickScoreRule qrule3A520;
		CRiskQuickScore::QuickScoreRule qrule4A520;
		CRiskQuickScore::QuickScoreRule qrule5A520;
		CRiskQuickScore::QuickScoreRule qrule1A521;
		CRiskQuickScore::QuickScoreRule qrule2A521;
		CRiskQuickScore::QuickScoreRule qrule3A521;
		CRiskQuickScore::QuickScoreRule qrule4A521;
		CRiskQuickScore::QuickScoreRule qrule5A521;
		CRiskQuickScore::QuickScoreRule qrule1A522;
		CRiskQuickScore::QuickScoreRule qrule2A522;
		CRiskQuickScore::QuickScoreRule qrule3A522;
		CRiskQuickScore::QuickScoreRule qrule4A522;
		CRiskQuickScore::QuickScoreRule qrule5A522;
		CRiskQuickScore::QuickScoreRule qrule1A523;
		CRiskQuickScore::QuickScoreRule qrule2A523;
		CRiskQuickScore::QuickScoreRule qrule3A523;
		CRiskQuickScore::QuickScoreRule qrule4A523;
		CRiskQuickScore::QuickScoreRule qrule5A523;
		CRiskQuickScore::QuickScoreRule qrule1A524;
		CRiskQuickScore::QuickScoreRule qrule2A524;
		CRiskQuickScore::QuickScoreRule qrule3A524;
		CRiskQuickScore::QuickScoreRule qrule4A524;
		CRiskQuickScore::QuickScoreRule qrule5A524;
		CRiskQuickScore::QuickScoreRule qrule1A525;
		CRiskQuickScore::QuickScoreRule qrule2A525;
		CRiskQuickScore::QuickScoreRule qrule3A525;
		CRiskQuickScore::QuickScoreRule qrule4A525;
		CRiskQuickScore::QuickScoreRule qrule5A525;
		CRiskQuickScore::QuickScoreRule qrule1A526;
		CRiskQuickScore::QuickScoreRule qrule2A526;
		CRiskQuickScore::QuickScoreRule qrule3A526;
		CRiskQuickScore::QuickScoreRule qrule4A526;
		CRiskQuickScore::QuickScoreRule qrule5A526;
		CRiskQuickScore::QuickScoreRule qrule1A527;
		CRiskQuickScore::QuickScoreRule qrule2A527;
		CRiskQuickScore::QuickScoreRule qrule3A527;
		CRiskQuickScore::QuickScoreRule qrule4A527;
		CRiskQuickScore::QuickScoreRule qrule5A527;
		CRiskQuickScore::QuickScoreRule qrule1A528;
		CRiskQuickScore::QuickScoreRule qrule2A528;
		CRiskQuickScore::QuickScoreRule qrule3A528;
		CRiskQuickScore::QuickScoreRule qrule4A528;
		CRiskQuickScore::QuickScoreRule qrule5A528;
		CRiskQuickScore::QuickScoreRule qrule1A529;
		CRiskQuickScore::QuickScoreRule qrule2A529;
		CRiskQuickScore::QuickScoreRule qrule3A529;
		CRiskQuickScore::QuickScoreRule qrule4A529;
		CRiskQuickScore::QuickScoreRule qrule5A529;
		CRiskQuickScore::QuickScoreRule qrule1A530;
		CRiskQuickScore::QuickScoreRule qrule2A530;
		CRiskQuickScore::QuickScoreRule qrule3A530;
		CRiskQuickScore::QuickScoreRule qrule4A530;
		CRiskQuickScore::QuickScoreRule qrule5A530;
		CRiskQuickScore::QuickScoreRule qrule1A531;
		CRiskQuickScore::QuickScoreRule qrule2A531;
		CRiskQuickScore::QuickScoreRule qrule3A531;
		CRiskQuickScore::QuickScoreRule qrule4A531;
		CRiskQuickScore::QuickScoreRule qrule5A531;*/


		std::vector<CRiskQuickScore::QuickScoreRule> qruleNormalVec;















		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//accumulation version
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		CRiskQuickScore::QuickScoreTemplate tempalte68;

		CRiskQuickScore::ScoreFactor factor815;
		CRiskQuickScore::ScoreFactor factor816;
		CRiskQuickScore::ScoreFactor factor817;
		CRiskQuickScore::ScoreFactor factor818;

		CRiskQuickScore::ScoreFactor factor819;
		CRiskQuickScore::ScoreFactor factor820;
		CRiskQuickScore::ScoreFactor factor821;
		CRiskQuickScore::ScoreFactor factor822;
		CRiskQuickScore::ScoreFactor factor823;
		CRiskQuickScore::ScoreFactor factor824;

		CRiskQuickScore::ScoreFactor factor825;
		CRiskQuickScore::ScoreFactor factor826;
		CRiskQuickScore::ScoreFactor factor827;
		CRiskQuickScore::ScoreFactor factor828;

		CRiskQuickScore::ScoreFactor factor829;
		CRiskQuickScore::ScoreFactor factor830;
		CRiskQuickScore::ScoreFactor factor831;
		CRiskQuickScore::ScoreFactor factor832;
		CRiskQuickScore::ScoreFactor factor833;
		CRiskQuickScore::ScoreFactor factor834;
		CRiskQuickScore::ScoreFactor factor835;
		CRiskQuickScore::ScoreFactor factor836;

		CRiskQuickScore::ScoreFactor factor837;
		CRiskQuickScore::ScoreFactor factor838;
		CRiskQuickScore::ScoreFactor factor839;
		CRiskQuickScore::ScoreFactor factor840;
		CRiskQuickScore::ScoreFactor factor841;

		CRiskQuickScore::QuickScoreStandard qstandard803;
		CRiskQuickScore::QuickScoreStandard qstandard804;
		CRiskQuickScore::QuickScoreStandard qstandard805;
		CRiskQuickScore::QuickScoreStandard qstandard806;
		CRiskQuickScore::QuickScoreStandard qstandard807;
		CRiskQuickScore::QuickScoreStandard qstandard808;
		CRiskQuickScore::QuickScoreStandard qstandard809;
		CRiskQuickScore::QuickScoreStandard qstandard810;
		CRiskQuickScore::QuickScoreStandard qstandard811;
		CRiskQuickScore::QuickScoreStandard qstandard812;
		CRiskQuickScore::QuickScoreStandard qstandard813;


		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardAccumulationVec;


		std::vector<CRiskQuickScore::QuickScoreRule> qruleAccumulationVec;

		std::vector<CRiskFuzzyScore::FuzzyFunctionMember> fmemberAccumulationVec;










		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//evaluation project version
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		CRiskQuickScore::QuickScoreTemplate tempalte69;



		CRiskQuickScore::ScoreFactor factor915;
		CRiskQuickScore::ScoreFactor factor916;
		CRiskQuickScore::ScoreFactor factor917;
		CRiskQuickScore::ScoreFactor factor918;
		CRiskQuickScore::ScoreFactor factor919;
		
		CRiskQuickScore::ScoreFactor factor920;
		//CRiskQuickScore::ScoreFactor factor921;
		CRiskQuickScore::ScoreFactor factor922;
		CRiskQuickScore::ScoreFactor factor923;
		CRiskQuickScore::ScoreFactor factor924;

		CRiskQuickScore::ScoreFactor factor925;
		CRiskQuickScore::ScoreFactor factor926;
		CRiskQuickScore::ScoreFactor factor927;
		CRiskQuickScore::ScoreFactor factor928;
		CRiskQuickScore::ScoreFactor factor929;
		CRiskQuickScore::ScoreFactor factor930;
		
		CRiskQuickScore::ScoreFactor factor931;
		CRiskQuickScore::ScoreFactor factor932;
		CRiskQuickScore::ScoreFactor factor933;
		CRiskQuickScore::ScoreFactor factor934;
		CRiskQuickScore::ScoreFactor factor935;

		CRiskQuickScore::ScoreFactor factor936;
		CRiskQuickScore::ScoreFactor factor937;
		//CRiskQuickScore::ScoreFactor factor938;

		CRiskQuickScore::ScoreFactor factor939;
		//CRiskQuickScore::ScoreFactor factor940;
		CRiskQuickScore::ScoreFactor factor941;

		CRiskQuickScore::QuickScoreStandard qstandard903;
		CRiskQuickScore::QuickScoreStandard qstandard904;
		CRiskQuickScore::QuickScoreStandard qstandard905;
		CRiskQuickScore::QuickScoreStandard qstandard906;
		CRiskQuickScore::QuickScoreStandard qstandard907;
		CRiskQuickScore::QuickScoreStandard qstandard908;
		CRiskQuickScore::QuickScoreStandard qstandard909;
		CRiskQuickScore::QuickScoreStandard qstandard910;
		CRiskQuickScore::QuickScoreStandard qstandard911;
		CRiskQuickScore::QuickScoreStandard qstandard912;
		CRiskQuickScore::QuickScoreStandard qstandard913;
		CRiskQuickScore::QuickScoreStandard qstandard914;
		CRiskQuickScore::QuickScoreStandard qstandard915;
		CRiskQuickScore::QuickScoreStandard qstandard916;
		CRiskQuickScore::QuickScoreStandard qstandard917;
		CRiskQuickScore::QuickScoreStandard qstandard918;
		CRiskQuickScore::QuickScoreStandard qstandard919;
		CRiskQuickScore::QuickScoreStandard qstandard920;
		CRiskQuickScore::QuickScoreStandard qstandard921;
		CRiskQuickScore::QuickScoreStandard qstandard922;
		CRiskQuickScore::QuickScoreStandard qstandard923;
		CRiskQuickScore::QuickScoreStandard qstandard924;
		CRiskQuickScore::QuickScoreStandard qstandard925;
		CRiskQuickScore::QuickScoreStandard qstandard926;
		CRiskQuickScore::QuickScoreStandard qstandard927;
		CRiskQuickScore::QuickScoreStandard qstandard928;
		CRiskQuickScore::QuickScoreStandard qstandard929;
		CRiskQuickScore::QuickScoreStandard qstandard930;
		CRiskQuickScore::QuickScoreStandard qstandard931;
		CRiskQuickScore::QuickScoreStandard qstandard932;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardEvalVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qruleEvalVec;
		



		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//2d youqipingjia version
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		CRiskQuickScore::QuickScoreTemplate tempalte70;

		std::vector<CRiskQuickScore::ScoreFactor> factor2dEvalVec;

		std::vector<CRiskQuickScore::QuickScoreStandard> qstandard2dEvalVec;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandard2dEvalVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qrule2dEvalVec;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//3d youqipingjia version
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		CRiskQuickScore::QuickScoreTemplate tempalte71;

		std::vector<CRiskQuickScore::ScoreFactor> factor3dEvalVec;

		std::vector<CRiskQuickScore::QuickScoreStandard> qstandard3dEvalVec;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandard3dEvalVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qrule3dEvalVec;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//2d fangankexingxing version
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		CRiskQuickScore::QuickScoreTemplate tempalte72;

		std::vector<CRiskQuickScore::ScoreFactor> factor2dPlanVec;

		std::vector<CRiskQuickScore::QuickScoreStandard> qstandard2dPlanVec;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandard2dPlanVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qrule2dPlanVec;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//3d fangankexingxing version
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		CRiskQuickScore::QuickScoreTemplate tempalte73;

		std::vector<CRiskQuickScore::ScoreFactor> factor3dPlanVec;

		std::vector<CRiskQuickScore::QuickScoreStandard> qstandard3dPlanVec;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandard3dPlanVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qrule3dPlanVec;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//shalelow非常规低勘探程度
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		CRiskQuickScore::QuickScoreTemplate tempalte74;

		std::vector<CRiskQuickScore::ScoreFactor> factorshalelowPlanVec;

		std::vector<CRiskQuickScore::QuickScoreStandard> qstandardshalelowPlanVec;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardshalelowPlanVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qruleshalelowPlanVec;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//shale high非常规高勘探程度
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		CRiskQuickScore::QuickScoreTemplate tempalte75;

		std::vector<CRiskQuickScore::ScoreFactor> factorshalehighPlanVec;

		std::vector<CRiskQuickScore::QuickScoreStandard> qstandardshalehighPlanVec;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardshalehighPlanVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qruleshalehighPlanVec;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//shale high非常规高勘探程度
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		CRiskQuickScore::QuickScoreTemplate tempalte76;

		std::vector<CRiskQuickScore::ScoreFactor> factorshaleTargetPlanVec;

		std::vector<CRiskQuickScore::QuickScoreStandard> qstandardshaleTargetPlanVec;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardshaleTargetPlanVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qruleshaleTargetPlanVec;


		



	


		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//区块版 Block 中等勘探程度
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		CRiskQuickScore::QuickScoreTemplate tempalte77;
		CRiskQuickScore::ScoreFactor factor1028;
		CRiskQuickScore::ScoreFactor factor1029;
		CRiskQuickScore::ScoreFactor factor1030;
		CRiskQuickScore::ScoreFactor factor1031;

		//order of lower and upper field is wrong
		CRiskQuickScore::QuickScoreStandard qstandard1021;
		CRiskQuickScore::QuickScoreStandard qstandard1022;
		CRiskQuickScore::QuickScoreStandard qstandard1023;
		CRiskQuickScore::QuickScoreStandard qstandard1024;
		CRiskQuickScore::QuickScoreStandard qstandard1025;
		CRiskQuickScore::QuickScoreStandard qstandard1026;
		CRiskQuickScore::QuickScoreStandard qstandard1027;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardblockmidVec;
		
		std::vector<CRiskQuickScore::QuickScoreRule> qruleblockmidVec;
		
	
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//区块版 Block 低勘探程度
		///////////////////////////////////////////////////////////////////////////////////////////////////////////

		CRiskQuickScore::QuickScoreTemplate tempalte78;
		CRiskQuickScore::ScoreFactor factor1128;

		CRiskQuickScore::QuickScoreStandard qstandard1121;
		CRiskQuickScore::QuickScoreStandard qstandard1122;
		CRiskQuickScore::QuickScoreStandard qstandard1123;
		CRiskQuickScore::QuickScoreStandard qstandard1124;
		CRiskQuickScore::QuickScoreStandard qstandard1125;
		CRiskQuickScore::QuickScoreStandard qstandard1126;
		CRiskQuickScore::QuickScoreStandard qstandard1127;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardblocklowVec;
		std::vector<CRiskQuickScore::QuickScoreRule> qruleblocklowVec;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//区块版 Block 较低勘探程度
		///////////////////////////////////////////////////////////////////////////////////////////////////////////

		CRiskQuickScore::QuickScoreTemplate tempalte79;
		CRiskQuickScore::ScoreFactor factor1228;
		CRiskQuickScore::ScoreFactor factor1229;
		CRiskQuickScore::ScoreFactor factor1230;


		//order of lower and upper field is wrong
		CRiskQuickScore::QuickScoreStandard qstandard1221;
		CRiskQuickScore::QuickScoreStandard qstandard1222;
		CRiskQuickScore::QuickScoreStandard qstandard1223;
		CRiskQuickScore::QuickScoreStandard qstandard1224;
		CRiskQuickScore::QuickScoreStandard qstandard1225;
		CRiskQuickScore::QuickScoreStandard qstandard1226;
		CRiskQuickScore::QuickScoreStandard qstandard1227;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardblocklikelylowVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qruleblocklikelylowVec;



		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//区块版 Block 较低勘探程度
		///////////////////////////////////////////////////////////////////////////////////////////////////////////

		CRiskQuickScore::QuickScoreTemplate tempalte80;
		CRiskQuickScore::ScoreFactor factor1528;
		CRiskQuickScore::ScoreFactor factor1529;
		CRiskQuickScore::ScoreFactor factor1530;


		//order of lower and upper field is wrong
		CRiskQuickScore::QuickScoreStandard qstandard1521;
		CRiskQuickScore::QuickScoreStandard qstandard1522;
		CRiskQuickScore::QuickScoreStandard qstandard1523;
		CRiskQuickScore::QuickScoreStandard qstandard1524;
		CRiskQuickScore::QuickScoreStandard qstandard1526;
		CRiskQuickScore::QuickScoreStandard qstandard1527;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardblockvalueVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qruleblockvalueVec;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//资源丰度
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		CRiskQuickScore::QuickScoreTemplate tempalte81;

		std::vector<CRiskQuickScore::ScoreFactor> factorabundanceVec;

		std::vector<CRiskQuickScore::QuickScoreStandard> qstandardabundanceVec;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardabundanceVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qruleabundanceVec;

		//海外区带
		CRiskQuickScore::QuickScoreTemplate tempalte82;
		std::vector<CRiskQuickScore::ScoreFactor> factorOverseaPlayVec;

		std::vector<CRiskQuickScore::QuickScoreStandard> qstandardOverseaPlayVec;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardOverseaPlayVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qruleOverseaPlayVec;

		//海外对象
		CRiskQuickScore::QuickScoreTemplate tempalte83;
		std::vector<CRiskQuickScore::ScoreFactor> factorOverseaPoolVec;

		std::vector<CRiskQuickScore::QuickScoreStandard> qstandardOverseaPoolVec;

		std::vector<CRiskFuzzyScore::FuzzyScoreStandard> fstandardOverseaPoolVec;

		std::vector<CRiskQuickScore::QuickScoreRule> qruleOverseaPoolVec;

	};






}
#endif
