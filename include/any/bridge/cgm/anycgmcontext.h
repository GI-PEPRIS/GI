// anycgmcontext.h: interface for the CCGMContext class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __ANYBRIDGE_CGM_CONTEXT_H__
#define __ANYBRIDGE_CGM_CONTEXT_H__

#include "anycgmpicture.h"
#include "anycgm.h"

class CCGMPicture;
class CFont;
class CCGMReader;
class CCGMPrimitive; 

#include <vector>
#include <string>
using namespace std;

	/*!
	*
	*/
	class   CCGMContext : public CCGM  
	{
	public:

		/*!
		 *	
		**/
		CCGMContext();

		/*!
		 *	
		**/
		CCGMContext( string &filename );

		/*!
		 *	
		**/
		~CCGMContext();

	public:

		/*!
		 *	�����־��txt��˳��CGMContext--CGMPicture--CGMPrimList--CGMPrimitive��
		**/
		void WriteDataToASCIIFile(FILE *out);

		/*!
		 *	Begin MetaFile, Class-0, ElementID-1
		**/
		string BeginMF(string & name);

		/*!
		*	Begin Picture, Class-0, ElementID-3
		**/
		string BeginPic(string & name);

		/*!
		 *	End MetaFile, Class-0, ElementID-2
		**/
		void EndMF();

		/*!
		 *	�������壨Class-1, ElementID-13: Font List��
		**/
		void AddFont(string str);

		// ��ǰͼ��
		CCGMPicture *m_curPic;

		// ͼ���б�
		std::vector<CCGMPicture*>pictures;

		// �Ƿ��ȡ���
		bool m_finishedLoading;
		
		// �ļ���
		string m_fileName;

		// �����б�
		std::vector< CFont* > m_fontList;

	};

#endif 