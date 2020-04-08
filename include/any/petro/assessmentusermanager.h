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
#ifndef __ANYPETRO_ASSESSMENT_USER_MANAGER_H__
#define __ANYPETRO_ASSESSMENT_USER_MANAGER_H__

// refer to EXPORT etc macroes
#include "anypetro.h"
#include "accumulationassessor.h"
//
#include "any/base/anystl.h"

//
namespace AnyPetro
{
	class ANYPETRO_CLASS CAssessmentUserManager
	{
	public:
		/*!
		*
		**/
		struct UserRecord
		{
			int userid;
			string username;
			string department;
			int priority;
			std::vector<bool> authorities;
			std::vector<bool> readvalidtables;
			std::vector<bool> writevalidtables;
			int m_oilfiledid;
			std::vector<bool> m_privilege;
			UserRecord() : userid(0), username(""), department(""), priority(0),m_oilfiledid(0)
			{
			}
		};
		typedef std::vector<UserRecord> UserVector;

	private:
		CAssessmentUserManager();
		~CAssessmentUserManager();
	public:
		static void commitUser(CAnyAccessor &accessor);
		static void commitUser(CAnyAccessor &accessor, UserRecord &userrecord);
		static bool loadUser(CAnyAccessor &accessor);
		static bool addUser(int userid, string username, string department, int priority, string authorities, string readvalidtables, string writevalidtables,int fieldid);
		static bool addUser(UserRecord &userrecord);
		static bool deleteUser(string username);

		static void getAllUsernames(std::vector<string> &username);
		static void setCurrentUserName(string username);
		static string getCurrentUserName();

		static string getUserDepartment(string username);
		static bool motifyUserDepartment(string username, string department);
		static int getUserPriority(string username);
		static bool motifyUserPriority(string username, int priority);
		static bool getUserAuthority(string username, int ActivityType);
		static bool motifyUserAuthority(string username, int ActivityType, bool Authority);

		static bool IsReadValidTable(string username, string tablename);
		static bool IsWriteValidTable(string username, string tablename);
		static bool IsReadValidTable(string username, int tableoffset);
		static bool IsWriteValidTable(string username, int tableoffset);
		static void SetReadValidTable(string username, string tablename, bool isvalid);
		static void SetWriteValidTable(string username, string tablename, bool isvalid);
		static void SetReadValidTable(string username, int tableoffset, bool isvalid);
		static void SetWriteValidTable(string username, int tableoffset, bool isvalid);
	private:
		static string currentUserName;
		static UserVector m_users;
		static string m_userTable;
	};
}

#endif
