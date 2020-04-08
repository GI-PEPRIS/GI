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
#ifndef __ANYPETRO_PETRO_DATA_H__
#define __ANYPETRO_PETRO_DATA_H__

// Refer to EXPORT etc
#include "anypetro.h"

// refer to its parent
#include "anypetroobject.h"

#include "any/base/anygeom.h"
using namespace AnyBase;

// namespace 
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CAnyPetroData : public CAnyPetroObject
	{
	protected:
		//
		//
		//
		/*!
		*
		**/
		virtual ~CAnyPetroData();

	protected:
		//
		//	kida semantics
		//
		/*!
		*
		**/
		virtual void CommitActivity(unsigned short type) = 0;

		//
		//
		//
		/*!
		*
		**/
		const char *GetTypeName();
		
		/*!
		*
		**/
		bool IsSameType(const CAnyObject *other);

	public:

		/*!
		*
		**/
		static bool AddKIDAClassRecord(long categoryid, long type, string name, string source, CGeoRect<double> extent, \
			long layerorder = 0, long isshown = 1, long canselect = 1, string remark = "", int seisparentid = 0, int contourtype = -1, int projtype = -1, int coordtype = -1);

		/*!
		*
		**/
		static bool RemoveKIDAClassRecord(string source);

		/*!
		*
		**/
		static bool UpdateKIDAClassRecordOrder(long layerorder, string source);

		/*!
		*
		**/
		static bool UpdateKIDAClassRecordCategoryid(long categoryid, string source);

		/*!
		*
		**/
		static bool UpdateKIDAClassRecordIsshown(long isshown, string source);
		
		/*!
		*
		**/
		static int GetKIDAClassRecordIsshown(string source);

		/*!
		*
		**/
		static bool UpdateKIDAClassRecordCanselect(long canselect, string source);

		/*!
		*
		**/
		static bool UpdateKIDAClassRecordName(string name, string source);
		
		/*!
		*
		**/
		static bool UpdateKIDAClassRecordParentName(string parentname, string source);

		/*!
		*
		**/
		static bool UpdateKIDAClassRecordExtent(CGeoRect<double> &extent, string source);
		
		/*!
		*
		**/
		static bool GetKIDAClassRecordExtent(CGeoRect<double> &extent, string source);

		/*!
		*
		**/
		static bool UpdateKIDAClassRecordSource(string oldsource, string source);

		/*!
		*
		**/
		static bool LoadKIDACategoryRecords(std::vector<int> &categoryids, std::vector<int> &categoryparentids, std::vector<string> &names);

		/*!
		*
		**/
		static bool AddKIDACategoryRecord(long categoryid, long categoryparentid, string name, long categoryorder = 0);

		/*!
		*
		**/
		static bool RemoveKIDACategoryRecord(long categoryid);
				
		/*!
		*
		**/
		static bool UpdateKIDACategoryRecordName(long categoryid, string name);
				
		/*!
		*
		**/
		static bool UpdateKIDACategoryRecordOrder(long categoryid, long categoryorder);
						
		/*!
		*
		**/
		static bool UpdateKIDACategoryRecordParentid(long categoryid, long categoryparentid);;
						
		/*!
		*
		**/
		static bool UpdateKIDACategoryRecordActivate(long categoryid);

		/*!
		*
		**/
		static bool AddKIDAThemeRecord(long type, string name);
		
		/*!
		*
		**/
		static int GetClassidBySource(string source);
				
		/*!
		*
		**/
		static string GetSourceByClassid(int classid);

		/*!
		*
		**/
		static bool AddGisSdeRecord(int classid, int elementid);
		
		/*!
		*
		**/
		static bool GetGisSdeRecord(int elementid, std::vector<int> &classids);
				
		/*!
		*
		**/
		static bool GetGisSdeRecord(int classid, int &elementid);

		/*!
		*
		**/
		static bool UpdateGisSdeRecord(int classid, int elementid);

		/*!
		*
		**/
		static bool DelGisSdeRecord(int classid);
		
		/*!
		*
		**/
		static string CheckFilePath(string filepath, bool allowonesame = false);
				
		/*!
		*
		**/
		static string CheckItemName(string itemname, bool allowonesame = false);

		//
		//methods that contain 'CAnyAccessor &accessor'
		//
		/*!
		*
		**/
		static bool UpdateKIDAClassRecordExtent(CAnyAccessor &accessor, CGeoRect<double> &extent, string source);
		static int GetClassidBySource(CAnyAccessor &accessor, string source);
		static string CheckFilePath(CAnyAccessor &accessor, string filepath, bool allowonesame = false);
		static string CheckItemName(CAnyAccessor &accessor, string itemname, bool allowonesame = false);
		static bool AddKIDAClassRecord(CAnyAccessor &accessor, long categoryid, long type, string name, string source, CGeoRect<double> extent, \
			long layerorder = 0, long isshown = 1, long canselect = 1, string remark = "", int seisparentid = 0, int contourtype = -1, int projtype = -1, int coordtype = -1);
	};
}

#endif