// anycgmprimitivelist.h: interface for the CCGMPrimList class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __ANYBRIDGE__CGMPRIMITIVELIST_H_
#define __ANYBRIDGE__CGMPRIMITIVELIST_H_

#include <vector>
#include <string>
using namespace std;

class CCGMPrimitive;

//////////////////////////////////////////////////////////////////////
// CCGMPrimList£¬Í¼Ôª¼¯ºÏ
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class  CCGMPrimList  
	{
	public:
		void WriteDataToASCIIFile(FILE *out);
		CCGMPrimitive * LastElement();
		void AddElement( CCGMPrimitive & element );
		void Reserve( int size );
		int size();
		CCGMPrimitive * ElementAt( int index );
		int ElementCount();
		int ReplaceText (int n, string & txt );
		CCGMPrimList();
		CCGMPrimList( int size );
		virtual ~CCGMPrimList();
	public:
		std::vector<CCGMPrimitive*> m_vectorobj;

	};



#endif 
