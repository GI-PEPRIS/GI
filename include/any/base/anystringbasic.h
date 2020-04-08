/*!
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
#ifndef __ANYBASE_STRING_BASIC_H__
#define __ANYBASE_STRING_BASIC_H__

// Refer to EXPORT definition
#include "anybase.h"

// Refer to indepedents of kinds of OS
#include "anyport.h"

// Anybase namespace
namespace AnyBase 
{
    /*! 
    * Common set of string operations ignoring varieties of character sets  
    */
    class ANYBASE_CLASS CAnyStringBasic
    {
	public:
        // Kinds of string output mechanism
        typedef std::ostringstream StringStream;

        // Kinds of string container
	    typedef stdext::hash_compare<anystring, std::less< anystring > > HashString;
        //typedef std::hash<anystring> HashString;
        typedef std::vector<anystring> VectorString;

    private:
        //
        // Ctrs & dctr
        //
        /*!
        * There is no any chance to declare this object
        **/
        ~CAnyStringBasic()
        {
        }

    public:
        //
        // Basic operations given an general input string
        //
        /*!
        * \brief
        * Removes any whitespace characters, be it standard space or TABs and so on.
        * The user may specify wether they want to trim only the  beginning or the end of 
        * the String ( the default action is to trim both)
        *
        * \para str, Given an input general string
        * \para left, Whether to trim on left side
        * \para right, Whether to trim on right side
        */
        void Trim(anystring &str, const anystring &delims = _T(" \t\r"), bool left = true, bool right = true);

        /*! 
        * \brief 
        * Returns a StringVector that contains all the substrings delimited by the characters in the passed 
        * \para str, Given an general input string 
        * \para ret, Splitted strings
        * \para delims, A list of delimiter characters to split by
        * \para maxSplits, The maximum number of splits to perform (0 for unlimited splits). If this parameters is > 0, 
        * the splitting process will stop after this many splits, left to right.
        */
		void Split(const anystring &str, VectorString &ret, const anystring &delims = _T("\t\n"), unsigned int maxSplits = 0);

        /*! 
        * Upper-cases all the characters given input string
        */
        void ToLowerCase(anystring &str);

        /*!
        * Lower-cases all the characters given input string
        */
        void ToUpperCase(anystring &str);

        /*! 
        * \brief
        * Returns whether the string begins with the pattern passed in.
        * \para str, Given an input string
        * \para pattern, The pattern to compare with
        * \para lowerCase, If true, the end of the string will be lower cased before
        * comparison, pattern should also be in lower case
        */
        bool IsStartWith(const anystring &str, const anystring &pattern, bool lowerCase = true);

        /*! 
        * \brief
        * Returns whether the string ends with the pattern passed in.
        * \para str, Given an input string
        * \para pattern, The pattern to compare with
        * \para lowerCase, If true, the end of the string will be lower cased before
        * comparison, pattern should also be in lower case.
        */
        bool IsEndWith(const anystring &str, const anystring &pattern, bool lowerCase = true);

        //
        // Operations of given path string
        //
        /*! 
        * \brief
        * Method for standardising paths - use forward slashes only, end with slash.
        *
        * \para fullName, Given an random input path info which may subject to different OS definition
        * \para ret, All "\\" should be replaced by "\"
        */
        void StandardisePath(const anystring &fullName, anystring &ret);

        /*! 
        * \brief
        * Method for splitting a fully qualified filename into the base name and path.
        * Path is standardised as in standardisePath
        */
        void SplitFilename(const anystring &qualifiedName, anystring &baseName, anystring &pathName);

		/*!
        * \brief
        * Method for splitting a fully qualified filename into the base name, extension and path,
        * Path is standardised as in standardisePath
        *
        * \para fullName, the whole file name with path info
        * \para baseName, only file name not EXT and PATH info
        * \para extName, the surfix info
        * \para pathName, path info igoring the last '\'
		*/
		void SplitFullFilename(const anystring &fullName, anystring &baseName, anystring &extName, anystring &pathName);

		/*! 
        * \brief
        * Method for splitting a filename into the base name and extension
        * \para fullName, given the file name ignoring path info
        * \para baseName, file name ignoring the EXT string
        * \para extName, surfix name of this file name
		*/
		static void SplitBaseFilename(const anystring &fullName,  anystring &basename, anystring &extName);

        //
        // Advanced operations of given input string
        //
        /*!
        * Simple pattern-matching routine allowing a wildcard pattern.
        * \para str String to test
        * \para pattern Pattern to match against; can include simple '*' wildcards
        * \para caseSensitive Whether the match is case sensitive or not
        */
        bool IsMatched(const anystring &str, const anystring &pattern, bool caseSensitive = true);

		//
		//
		//
		/**
		*
		*/
		int Wcs2Ascii(wchar_t* wStr, char *aStr, int num) const;

		/**
		*
		*/
		int Ascii2Wcs(char* aStr, wchar_t *wStr, int num) const;

		/**
		*
		*/
		int Chs2Ascii(wchar_t* wStr, char *aStr, int num = -1) const;

		/**
		*
		*/
		int Ascii2Chs(char* aStr, wchar_t *wStr, int num = -1) const;

		//
		//
		//
		/*!
		*
		**/
		static const CAnyStringBasic &Get();

    public:
        // Constant blank string, useful for returning by ref where local does not exist
        static const anystring BLANK;
    };
} 

#endif
