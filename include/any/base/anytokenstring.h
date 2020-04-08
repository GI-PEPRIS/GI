/**
 * The AnySDB of PetroCOVERY solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy management 
 * and rendering of geometries being a leading one.
 *
 * Copyright (C) 2015 Xiujie Sheng
 *
 * This library isn't a free software, so you cann't take the sourcecode without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
 * if you illegally got it. 
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
#ifndef __ANYBASE_TOKENSTRING_H__
#define __ANYBASE_TOKENSTRING_H__

// Refer to EXPORT & IMPORT macroes
#include "anybase.h"

// Erase compile warning messages
#pragma warning( push )
#pragma warning( disable: 4996 )  // Deprecated function calling

// UeBase namespace
namespace AnyBase
{
	/**
	* With specified token rules to analyze the different part of one text.
	*
	* There are three kinds of pragma specification:
	* 1) Token Characters like comma which are used to seperate different text part also include \t and space character
	* 2) Builder Characters like "" and () which express referenced part and no need to remove middle \t and '' characters
	* 3) Divider Characters which mention just comment sentence and play no any sense except for taking it as one sentence
	*
	* There are also three analyzing rule using above three kinds of tokens:
	* 1) DEFAULT: Firstly get builder part, secondly get token part, lastly get divider part while considering space and '\t' by default as tokens
	* 2) NORMAL: Firstly get token part, secondly get divider part and lastly get builder part
	* 3) FIXED: Directly with specified column information, namely its width
	*/
    class ANYBASE_CLASS CAnyTokenString
    {
		// Disallow automatically create this object
		CAnyTokenString(const CAnyTokenString &other);
		void operator=(const CAnyTokenString &other);

    public:
        //
        // Constructors & deconstructor
        //
		/**
		* Default construcor means using default token setting.
		*/
		CAnyTokenString();

        /**
        * Constructor with parameters using specified token setting.
        */
	    CAnyTokenString(const char* token, const char* builder, const char* divider);

        /**
        *
        */
	    ~CAnyTokenString();

    public:
        //
        // Token rules
        //
        /**
        *
        */
        void SetDefault();

        /**
        *
        */
        void SetToken(const char *token, const char *builder = 0, const char *divider = 0);

        /**
        *
        */
        void SetFixedWidth(int no, int *widths);

        //
        // Analyze and results operations
        //
        /**
        *
        */
        int Trim(const char *str, int max);

        /**
        *
        */
        bool IsSame(const char *str, bool isCase);

        /**
        *
        */
        bool IsSame(int idx, const char *oneKey, bool isCase, int num = 1);

        /**
        *
        */
        int Count();

        /**
        *
        */
        int GetCount();

        /**
        *
        */
        int Find(int start, const char *str, bool isCase) const;

        /**
        *
        */
        char *GetAt(int idx) const;

        /**
        *
        */
        char *operator[](int idx) const;

        /**
        *
        */
        void RemoveAfter(int idx);

        /**
        *
        */
	    void RemoveResult();

    private:
        //
        //
        //
        /**
        *
        */
        bool AddResult(const char *res, int max);

        /**
        *
        */
        bool FindToken(char token);

        /**
        *
        */
        bool FindDivider(char divider);

        /**
        *
        */
        char FindBuilder(char builder, bool &mode);

        /**
        *
        */
        int TrimByDefault(const char *str, int max);

        /**
        *
        */
        int TrimByNormal(const char *str, int max);

        /**
        *
        */
        int TrimByFixed(const char *str);

        /**
        *
        */
        void RemoveEndSpace(char *str);

    private:
        // Maximum length of  
        const static short m_maxTokenSize = 64;

		// Default setting
	    bool m_isDefault;

		// Pragma rules
	    char m_strToken[m_maxTokenSize+1];
	    char m_strBuilder[m_maxTokenSize+1];
	    char m_strDivider[m_maxTokenSize+1];

        // String results be analyzed
	    char** m_strResults;
	    int m_strNum;

		// Analyze in fixed width
	    int* m_columnWidth;
	    int m_columnNum;
    };
}

#pragma warning( pop )

#endif 
