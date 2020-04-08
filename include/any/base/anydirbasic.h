/*!
 * The AnyBase package of PetroCOVERY Solution is a collection of native C++ classes that 
 * implement the fundamental algorithms & operations required to 
 * satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYBASE_PATHBASIC_H__
#define __ANYBASE_PATHBASIC_H__

// Export and import macro def
#include "anybase.h"

// Refer to _T() etc 
#include "anyport.h"

// UeBase namespace
namespace AnyBase
{
	/**
	* Uitility class as a singletion for getting paths, basic checks etc.
	*
	* Since we simply take this class as singleton one containing utility functions, there shouldn't no any member variables
	* which should be maintained or noticed when being used by one single instance every where. The side-effect of this way
	* is that it seems we have to pass more parameters to one function.
	*/
    class ANYBASE_CLASS CAnyDirBasic
    {
		/**
		* The various values for the path format.
		*
		* This mainly affects the path separator but also whether or not the path has the drive part (as under Windows)
		* Note:
		* Considering this class doesn't have any member variables, so from better semantic understanding, all functions 
		* are given as CONST functions.
		*/
		enum PathFormat
		{
			PF_Unknown = 0,
			PF_Unix,
			PF_Mac,
			PF_Dos,
			PF_Max // Not a valid value for specifying path format
		};

		/**
		* Seperators between two path components.
		*/
		enum PathSeperator
		{
			PS_Dos	= _T('\\'),
			PS_Unix = _T('/'),
			PS_Mac	= _T(':')
		};

		// Not be used in any default way except for explicitly being a singletion
		CAnyDirBasic()
		{
		}

		const CAnyDirBasic &operator=(const CAnyDirBasic &other)
		{
			// Do nothing
			return *this;
		}

        virtual ~CAnyDirBasic()
        {
        }

    public:
		// The maximum of path length
		static const int MAXPATHLENGTH = 1024;

        //
        // Methods for getting or merging different paths including absolute path, for example, current working path,
		// relative path, environment paths set by system environment varables("PATH") etc.
        //
        /**
        * Directly get working path.
		*
		* @param path the memory for receving the current working path, so it shouldn't be null
		* @param maximum the size of above memory in bytes or smaller than the size of path. And
		* it shouldn't be larger than the size of path
        */
        void GetModulePath(TCHAR *path, int maximum) const;

		/**
		* Get relative path especially recursivelly calling to this function, we can get the 
		* path like ".\filename" or "..\..\filename"etc.
		*
		* @param path current relative path which should be added when recursivly calling this function
		*/
		void GetPathSeperator(anystring &path) const;

		/**
		* Get expression of current relative path.
		*
		*/
		void GetDotPath(anystring &path) const;

		/**
		* Get expression of parent relative path.
		*/
		void GetDotDotPath(anystring &path) const;

		// Note:
		// Below two functions's name shound be FindXXX, however those would conflict with functions defined
		// by microsoft and cause compile error since this compiler can't correctly indicate which group. So
		// we had to change our idea facing the big bull like microsoft, woo...
		/**
		* Find the first file in one specified directory or file.
		*
		* @param oneDir the specified directory from which to loop all files
		* @param oneFile file search specification (*.* or *.bmp etc) while as the first file found
		* @param foundHandle memory allocated insidely indicating the handle of specified directoy
		* @param foundData memory allocate insidely indicating the found structure of current loop process
		* @return whethe exist the file which isn't sub-directoty or a hidden file
		*/
		bool FindFirst(const anystring &oneDir, anystring &oneFile, void **foundHandle, void **foundData, bool isFile = true) const;

		/**
		* Find the next file or directory in one specified directory until the filename is empty.
		*
		*/
		bool FindNext(anystring &oneFile, void *foundHandle, void *foundData, bool isFile = true) const;

		/**
		* Release those memory demanded by <code> GetFirstFile </code> and <code> GetNextFile</code>.
		* 
		* Never forget to call this function after looping those files since those memory is allocated insidely
		* and special way limited to one kind of os
		*/
		void FindOver(void *foundHandle, void *foundData) const;

		//
		// Different check mechansim for one path or file
		//
		/**
		*
		*/
		bool CreateDir(const anystring &oneDir) const;

		/**
		*
		*/
		bool RemoveDir(const anystring &oneDir) const;

        /**
        * Check whether this directory is exist.
		*
		* Note:
		* This function can check whether user already take SD card out then make suitable decision
		*
		* @param oneFile it represents one file and in fact also be taken as one path
		* @return whether this file or directory path exist
        */
		bool IsDirExist(const anystring &oneDir) const;

		/**
		*
		*/
		bool IsWritableDir(const anystring &oneDir) const;

		/**
		*
		*/
		bool IsReadableDir(const anystring &oneDir) const;

		/**
		*
		*/
		bool RemoveFile(const anystring &oneFile) const;

        /**
        * Check whether this directory is exist.
		*
		* @param oneFile it represents one file and in fact also be taken as one path
		* @return whether this file or directory path exist
        */
		bool IsFileExist(const anystring &oneFile) const;

		/**
		*
		*/
		bool IsWritableFile(const anystring &oneFile) const;

		/**
		*
		*/
		bool IsReadableFile(const anystring &oneFile) const;

		/**
		*
		*/
		bool IsExecutableFile(const anystring &oneFile) const;

		//
		// Singleton function
		//
		/**
		* This class only exist one instance since it is a utility class
		*/
		static const CAnyDirBasic &Get();

	private:
		/**
		* Get seperator type serving for current os.
		*
		* @return the type of path seperator
		*/
		short GetPathFormat() const;

		/**
		* Remove the path sperator in the tail of one path.
		*/
		void NormalizePath(TCHAR *path) const;

		/**
		* Check permission conditions of one file or direction, for example, only readable, writable or both etc.
		*/
		bool CheckPermission(const anystring &oneDir, unsigned int access) const;

		/**
		* Whether is end with path seperator
		*/
		bool IsSeperatorEnd(const anystring &oneDir) const;

	private:
		// Lazy initialization until the first time to get this object
		static CAnyDirBasic m_pathBasic;
    };
}

#endif
