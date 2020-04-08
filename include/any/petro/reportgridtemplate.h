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
#ifndef __ANYPETRO_REPORTGRID_TEMPLATE_H__
#define __ANYPETRO_REPORTGRID_TEMPLATE_H__

// refer to EXPORT etc macroes
#include "anypetro.h"


// refer to persistence
#include "any/db/anyaccessor.h"
using namespace AnyDB;

// 
namespace AnyPetro
{

	/*!
	*
	**/
	class ANYPETRO_CLASS CReportGridTemplate
	{

	public:
		struct rowcondition
		{
			DBFieldDesc m_field;
			std::vector<string> fieldvalue;
			rowcondition(){}
		};
		struct colcondition
		{
			DBFieldDesc m_field;
			std::vector<string> fieldvalue;
			colcondition(){}
		};
		struct datacondition
		{
			DBFieldDesc m_field;
			datacondition(){}
		};
	public:
		/*!
		*
		**/
		CReportGridTemplate(){}

		/*!
		*
		**/
		~CReportGridTemplate(){}

	public:

		/*!
		*
		**/
		static bool GetReportGridTemplate(string username, int templateIdx, std::vector<rowcondition*> &rowconditions, std::vector<colcondition*> &colconditions, std::vector<datacondition*> &dataconditions);

		/*!
		*
		**/
		static int CommitReportGridTemplate(string templatename, std::vector<rowcondition*> &rowconditions, std::vector<colcondition*> &colconditions, std::vector<datacondition*> &dataconditions);

		/*!
		*
		**/
		static bool LoadReportGridTemplateRecords(string username, std::vector<int> &templateids, std::vector<string> &templatenames);

		/*!
		*
		**/
		static bool DeleteTemplate(int templateid);
	public:
		static string m_reportgridtemplateTable;
	};
}
#endif