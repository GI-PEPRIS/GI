// ConvertCGM2TXT.h : Declaration of the CAnyCgmConverter

#ifndef __ANYBRIDGE__CONVERTCGM2TXT_H_
#define __ANYBRIDGE__CONVERTCGM2TXT_H_

class CCGMContext;
class CCGMReader;

// Refer to EXPORT & IMPORT
#include "..\anybridge.h"

#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////
// CAnyCgmConverter
//////////////////////////////////////////////////////////////////////

	/*!
	*
	*/
	class  ANYBRIDGE_CLASS CAnyCgmConverter
	{

	public:

		/*!
		*	
		**/
		CAnyCgmConverter()
		{
			m_pCGMBinRead = NULL;
			m_pCGMContext = NULL;
		}

		/*!
		*	
		**/
		~CAnyCgmConverter()
		{
			if(m_pCGMBinRead)
			{
				delete m_pCGMBinRead;
				m_pCGMBinRead=NULL;
			}
			if(m_pCGMContext)
			{
				delete m_pCGMContext;
				m_pCGMBinRead=NULL;
			}
		}

	public:

		/*!
		*	StringתTstring
		**/
		wstring String2Tstring(const string& str);

		/*!
		*	�����־��txt��˳��CGMContext--CGMPicture--CGMPrimList--CGMPrimitive��
		**/
		void WriteCGMDataToTXTFile(const string &FileName);

		/*!
		*	��ȡCGM�ļ�
		**/
		bool ReadCGM(const string &CGMFileName);

	public:

		// CCGMReaderָ��
		CCGMReader * m_pCGMBinRead;

		// CCGMContextָ��
		CCGMContext *m_pCGMContext;
	};


#endif 