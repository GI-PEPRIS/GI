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
		 *	输出日志到txt（顺序：CGMContext--CGMPicture--CGMPrimList--CGMPrimitive）
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
		 *	增加字体（Class-1, ElementID-13: Font List）
		**/
		void AddFont(string str);

		// 当前图形
		CCGMPicture *m_curPic;

		// 图形列表
		std::vector<CCGMPicture*>pictures;

		// 是否读取完毕
		bool m_finishedLoading;
		
		// 文件名
		string m_fileName;

		// 字体列表
		std::vector< CFont* > m_fontList;

	};

#endif 