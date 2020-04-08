#ifndef __ANYPETRO_FILL_TEMPLATE_DATA_H__
#define __ANYPETRO_FILL_TEMPLATE_DATA_H__
// refer to EXPORT etc macro definitions
#include "anypetro.h"
#include "templatedata.h"

// refer to AnyDB relatives
#include "any/db/anyaccessor.h"
using namespace AnyDB;

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CFillTemplateData
	{

	public:


		CFillTemplateData(){;}
		
		~CFillTemplateData(){;}

		static long InitScoreTemplate2(int type);

		static long InitSimpleTemplate(CTempalteData& tdata);
		static long InitNormalTemplate(CTempalteData& tdata);
		static long InitAccumTemplate(CTempalteData& tdata);
		static long InitAbundanceTemplate(CTempalteData& tdata);
		static long InitEvalTemplate(CTempalteData& tdata);

		static long Init2dEvalTemplate(CTempalteData& tdata);
		static long Init3dEvalTemplate(CTempalteData& tdata);
		static long Init2dPlanTemplate(CTempalteData& tdata);
		static long Init3dPlanTemplate(CTempalteData& tdata);

		/*!
		*
		**/
		static long InitshalelowEvalTemplate(CTempalteData& tdata);
		static long InitshalehighEvalTemplate(CTempalteData& tdata);
		static long InitshalelowPlanTemplate(CTempalteData& tdata);
		static long InitshaleTargetEvalTemplate(CTempalteData& tdata);

		static long InitBlockMidTemplate(CTempalteData& tdata);
		static long InitBlockLowTemplate(CTempalteData& tdata);
		static long InitBlockLikelyLowTemplate(CTempalteData& tdata);
		static long InitBlockValueTemplate(CTempalteData& tdata);

		static long InitOverSeaPlayTemplate(CTempalteData& tdata);
		static long InitOverSeaPoolTemplate(CTempalteData& tdata);
	};
}
#endif