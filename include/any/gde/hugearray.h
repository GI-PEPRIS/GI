#ifndef __HUGEARRAY_H__20D21E1E_D3C9_40b8_8B82_FC1686BDBB58__
#define __HUGEARRAY_H__20D21E1E_D3C9_40b8_8B82_FC1686BDBB58__

#include <crtdbg.h>
#include <vector>
#include <map>
#include <tchar.h>
#include <Vector>
#include "bitvector.h"
#include "any/base/anyport.h"

#define _TWOGB	(0x80000000)
#define _64KB	(0x00010000)
#define _64MB	(0x04000000)
#define _32MB	(0x02000000)
#define _256MB	(0x10000000)

typedef long long BIGNUMBER;

inline static DWORD ErrorMessage()
{
    LPVOID lpMsgBuf; DWORD dwErrorCode;
    FormatMessage( 
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dwErrorCode = GetLastError(),
        0, // Default language
        (LPTSTR) &lpMsgBuf,
        0,
        NULL 
    );
    MessageBox( NULL, (LPCTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONINFORMATION );
    LocalFree( lpMsgBuf );
	return dwErrorCode;
}

/// The HugeArray class facilitates large byte arrays to allocated and accessed by using the file mapping techniques.
/// It uses multiple files of _MaxFileSize to allocate the space and maps views on the files. Views are mapped and
/// unmapped as required, with a limited number of views cached at a time. _MaxNoOfCachedViews governs this limit.
/// CachedViews are picked in FIFO fashion to unmap so as to make space for new views. (FIFO could be replaced with
/// LRU or any other efficent techqniue, but that requires keeping track of the view usage and thus avoided for performance
/// reasons.)
/// The _ViewSize governs the size of the view that is mapped. (_MaxFileSize/_ViewSize) gives the max no. of views per file.
/// Since MaxNoOfViewsPerFile require only 16bits, we can use the upper 16 bits (of a 32-bit integer) to keep track 
/// of which file this view belongs to. Thus, we are restricting the maximum number of files to be 2^16 (=65536). 
/// With 2GB per file, this restricts us to have at most 65536 * 2GB address space. Thus our HugeArray cannot work for 
/// arrays that require more than 131072GB space.
/// If we require more space to be mapped, then we need to maintain the FileIndex and View offset seperately (instead
/// of merging them both into one 32-bit integer), thus increasing the number of bits for FileIndex making it possible
/// to have more files mapped.
template<typename ElementType>
class HugeArray
{
public:
	//enum : unsigned long 
	//{	_ElemSize			= sizeof(ElementType/*BYTE*/), 
	//	_ViewSize			= _64KB,
	//	_MaxFileSize		= _TWOGB,
	//	_MaxNoOfCachedViews = 16,
	//	_MaxNoOfElemsPerFile= (_MaxFileSize/_ElemSize),
	//	_MaxNoOfViewsPerFile= (_MaxFileSize/_ViewSize)	//=0x00008000	
	//};

	struct MappingParameter 
	{
		unsigned long	_ElemSize;				//元素大小
		unsigned long	_ViewSize;				//view大小
		BIGNUMBER		_MaxFileSize;			//文件最大大小
		unsigned long	_MaxNoOfCachedViews;	//最大view缓存数量
		BIGNUMBER		_MaxNoOfElemsPerFile;	//文件中包含最多元素数量
		unsigned long	_MaxNoOfViewsPerFile;	//文件中包含最多view数量
		unsigned long	_NoOfElemsPerView;		//view中包含元素数量

		MappingParameter()
		{
			_ElemSize			= sizeof(ElementType);
			_ViewSize			= /*_64KB*/_32MB;
			_MaxFileSize		= /*_64KB*/_32MB;
			_MaxNoOfCachedViews = 1;
			_MaxNoOfElemsPerFile= (_MaxFileSize/_ElemSize);
			_MaxNoOfViewsPerFile= (_MaxFileSize/_ViewSize);
			_NoOfElemsPerView	= (_ViewSize/_ElemSize);
		}
	};
	MappingParameter m_parameter;

public:
	HANDLE*						hFileMappings;// The File mappings
	/*ATL::CAtlFile*/HANDLE*				Files;	// The Files that were mapped
	unsigned int				nFileCount; // Number of Files
	BIGNUMBER					_RequestedLen;	// No.of Elements requested
	BIGNUMBER					_AllocatedLen;	// No.of Elements actually allocated
	/*ATL::CAtlMap*/std::map<unsigned int, LPVOID> pCachedViews; //[FileIndex, FileView] map for few cached views
	std::vector<CBitVector>		bvFileViewCleared;	// Keeps track of views that need be cleared upon mapping
	anystring					m_lpszDirPath;
public:
	HugeArray() // Directory where to create the memory mapped files
		: _RequestedLen(0), _AllocatedLen(0), hFileMappings(0), Files(0), nFileCount(0)
	{
	}

	// _nCount: Number of Elements to allocate space for
	// lpszDirPath: Directory where to create the memory mapped files
	// nInitVal: Value that should be used to initialize the allocated space
	HugeArray(const BIGNUMBER& _nCount, LPCTSTR lpszDirPath = _T("."), int nInitVal=0)  
		: _RequestedLen(0), _AllocatedLen(0), hFileMappings(0), Files(0), nFileCount(0), m_lpszDirPath(lpszDirPath)
	{		
		Allocate(_nCount, lpszDirPath, nInitVal);
	}

	~HugeArray()
	{
		DeAllocate();
	}

	// Allocates space for _nCount number of elements (each of _ElemSize)
	//returns the error code in case of failures
	DWORD Allocate(const BIGNUMBER& _nCount, LPCTSTR lpszDirPath = _T("."), int nInitVal=0)
	{
		m_parameter._MaxNoOfElemsPerFile= (m_parameter._MaxFileSize/m_parameter._ElemSize);
		m_parameter._MaxNoOfViewsPerFile= (m_parameter._MaxFileSize/m_parameter._ViewSize);
		m_parameter._NoOfElemsPerView	= (m_parameter._ViewSize/m_parameter._ElemSize);
		m_lpszDirPath = lpszDirPath;
		// Make sure things are clean
		DeAllocate();

		// Prepare the file name prefixes
		/*ATL::CString*/ anystring strDir(lpszDirPath), strPrefix;
		TCHAR TempFileName[MAX_PATH+32];

		// Make sure the directory path is terminate with "\"
		if(strDir[strDir.length() - 1] != '\\')
		{
			strDir += _T("\\");
			CreateDirectory((LPCWSTR)(strDir.c_str()), NULL);
		}
		// Compute the required number of files
		unsigned long lNumFiles = (unsigned long)(_nCount / m_parameter._MaxNoOfElemsPerFile) + 1;

		// Allocate space for the handles
		if(NULL == (Files = new HANDLE/*ATL::CAtlFile*/[lNumFiles]) ||
			NULL == (hFileMappings = new HANDLE[lNumFiles]))
			return E_OUTOFMEMORY;

		for(unsigned long l=0; l < lNumFiles; ++l)
		{
			// Get a unique name for the file
			::swprintf(TempFileName, _T("data%d"), l);
			strPrefix = TempFileName;
			anystring FileName = strDir + strPrefix;

			//::swprintf(TempFileName, _T("%dHA"), l);
			//strPrefix = TempFileName;

			//if(!GetTempFileName((LPCWSTR)(strDir.c_str()), (LPCWSTR)(strPrefix.c_str()), 0, FileName))
				//return ErrorMessage();

			// Create the file
			if(FAILED(Files[l] = CreateFile((LPCWSTR)(FileName.c_str()), GENERIC_READ|GENERIC_WRITE|STANDARD_RIGHTS_ALL, 
							FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL, OPEN_ALWAYS, 
							/*FILE_ATTRIBUTE_TEMPORARY|*/FILE_ATTRIBUTE_NOT_CONTENT_INDEXED|/*FILE_FLAG_DELETE_ON_CLOSE|*/FILE_FLAG_SEQUENTIAL_SCAN,NULL)))
				return ErrorMessage();

			// Set the file size to the maximum	
			// TODO: to create file in maxfilesize for PC
			// ...
			{
				LARGE_INTEGER liDistanceToMove;
				liDistanceToMove.QuadPart = m_parameter._MaxFileSize;
				if(!SetFilePointerEx(Files[l], liDistanceToMove, NULL, FILE_BEGIN))
					return ErrorMessage();
				if(!SetEndOfFile(Files[l]))
					return ErrorMessage();
			}

			//if(FAILED(Files[l].SetSize((0x00000000ffffffff & _MaxFileSize))))
			//	return ErrorMessage();

			// Create the File Mapping
			if(NULL == (hFileMappings[l] = ::CreateFileMapping(Files[l], NULL, PAGE_READWRITE, 0, 0, NULL)))
				return ErrorMessage();

			// Create the Clearance vector
			bvFileViewCleared.push_back(CBitVector());
		}

		_RequestedLen = _AllocatedLen = _nCount; nFileCount = lNumFiles;

		return S_OK;
	}

	void DeAllocate()
	{
		// Unmap the cached views
		std::map<unsigned int, LPVOID>::iterator first = pCachedViews.begin();
		std::map<unsigned int, LPVOID>::iterator last = pCachedViews.end();
		for(; first != last; first++)
		{
			LPVOID pViewBase = first->second;
			if(pViewBase != NULL)
				::UnmapViewOfFile(pViewBase);
		}
		pCachedViews.clear();

		// Close the File Mapping Handles
		for(unsigned int i = 0; i < nFileCount; ++i)
		{
			if(hFileMappings[i] != NULL)
				::CloseHandle(hFileMappings[i]);
		}
		// Free the File Mapping Handles memory
		if(hFileMappings != NULL)
			delete[] hFileMappings;
		// Free the Files Memory (which automatically closes the Files too)
		if(Files != NULL)
			delete[] Files;
		// Clear the bitvector
		bvFileViewCleared.clear();
		// Reset Values to NULL
		hFileMappings = NULL;
		Files = NULL;
		nFileCount = 0;
		_AllocatedLen = 0;
		_RequestedLen = 0;
	}

	inline ElementType/*BYTE*/* _GetAt(unsigned long lFileIndex, unsigned long nViewIndex, unsigned long nViewOffset)
	{
		_ASSERTE(lFileIndex < nFileCount);

		unsigned long nFileViewIndex = ((lFileIndex & 0x0000ffff) << 16) | (nViewIndex & 0x0000ffff);

		LPVOID pViewBase = NULL;

		if(pCachedViews.find(nFileViewIndex) == pCachedViews.end())	// Cache Miss
		{
			if(pCachedViews.size() >= m_parameter._MaxNoOfCachedViews)	// if Cache is full, make room to load the new map
			{
				// TODO: PC whether it is being used
				// ...

				//POSITION pos = pCachedViews.GetStartPosition();
				//pViewBase = pCachedViews.GetAt(pos)->m_value;
				//if(pViewBase != NULL) ::UnmapViewOfFile(pViewBase);
				//pCachedViews.RemoveAtPos(pos);

				std::map<unsigned int, LPVOID>::iterator first = pCachedViews.begin();
				pViewBase = first->second;
				if(pViewBase != NULL) ::UnmapViewOfFile(pViewBase);
				pCachedViews.erase(first);
			}

			// Map the View
			if(NULL == (pViewBase = ::MapViewOfFile(hFileMappings[lFileIndex], FILE_MAP_WRITE|FILE_MAP_READ/*FILE_MAP_ALL_ACCESS*/, 0, nViewIndex*m_parameter._ViewSize, m_parameter._ViewSize)))
			{
				/*ATL::CString*/ TCHAR strFilePath[2014]; 
				::swprintf(strFilePath, _T("Unable to map view for File Index: %d"), lFileIndex);
				::MessageBox(NULL,  strFilePath, _T("Error"), MB_OK|MB_ICONERROR);

				ErrorMessage();
				return (ElementType/*BYTE*/*)pViewBase;
			}

			// Clear the contents of the view if this is the first time it is mapped
			//if(bvFileViewCleared[lFileIndex].IsBitSet(nViewIndex)==false)
			//{
				//::memset(pViewBase, 0, m_parameter._ViewSize);
				//bvFileViewCleared[lFileIndex] += nViewIndex; // set the cleared flag
			//}

			// Cache the mapped view
			pCachedViews[nFileViewIndex] = pViewBase;
		}
		else
			pViewBase = pCachedViews[nFileViewIndex];
		if(!pViewBase)
		{
			ErrorMessage();
			return (ElementType*)NULL;
		}
		return ((ElementType/*BYTE*/*)((unsigned char*)pViewBase + nViewOffset * m_parameter._ElemSize));
	}

	inline ElementType/*BYTE*/* _GetAt(const BIGNUMBER& nIndex)
	{
		unsigned long lFileIndex = (unsigned long)(nIndex / m_parameter._MaxNoOfElemsPerFile);
		BIGNUMBER lFileOffset = (nIndex % m_parameter._MaxNoOfElemsPerFile); // Compute the offset in file
		unsigned long nViewIndex = (unsigned long)(lFileOffset / m_parameter._NoOfElemsPerView); // Compute the view that should be containing the offset
		unsigned long nViewOffset = (unsigned long)(lFileOffset % m_parameter._NoOfElemsPerView); // Compute the offset in the view

		return _GetAt(lFileIndex, nViewIndex, nViewOffset);
	}

	inline ElementType/*BYTE*/& operator[](const BIGNUMBER& nIndex)
	{
		unsigned long lFileIndex = (unsigned long)(nIndex / m_parameter._MaxNoOfElemsPerFile);
		BIGNUMBER lFileOffset = (nIndex % m_parameter._MaxNoOfElemsPerFile); // Compute the offset in file
		unsigned long nViewIndex = (unsigned long)(lFileOffset / m_parameter._NoOfElemsPerView); // Compute the view that should be containing the offset
		unsigned long nViewOffset = (unsigned long)(lFileOffset % m_parameter._NoOfElemsPerView); // Compute the offset in the view

		return *_GetAt(lFileIndex, nViewIndex, nViewOffset);
	}

	//inline ElementType/*BYTE*/& operator[](const unsigned long ulIndex)
	//{
	//	unsigned long lFileIndex = (ulIndex / (unsigned long)m_parameter._MaxNoOfElemsPerFile);
	//	unsigned long lFileOffset = (ulIndex % (unsigned long)m_parameter._MaxNoOfElemsPerFile); // Compute the offset in file
	//	unsigned long nViewIndex = (lFileOffset / (unsigned long)m_parameter._ViewSize); // Compute the view that should be containing the offset
	//	unsigned long nViewOffset = (lFileOffset % (unsigned long)m_parameter._ViewSize); // Compute the offset in the view

	//	return *_GetAt(lFileIndex, nViewIndex, nViewOffset);
	//}

	// Attemps to allocate space for _nCount number of elements.
	// If the currently allocate space is more than what is required, this would do nothing.
	// Else Deallocates the existing space and allocates new space.
	// In any case clears the contents.
	bool ReDim(const BIGNUMBER& _nCount, LPCTSTR lpszDirPath = _T("."), int nInitVal=0)
	{
		if(_AllocatedLen < _nCount)
		{
			return (S_OK == Allocate(_nCount, lpszDirPath, nInitVal));
		}
		else
		{
			_RequestedLen = _nCount;
			ClearContents();
		}
		return false;
	}
	bool ReAllocate(BIGNUMBER _nCount)
	{
		if(_AllocatedLen < _nCount)
		{
			return (S_OK == Allocate(_nCount, m_lpszDirPath.c_str()));
		}
		else
		{
			_RequestedLen = _nCount;
			ClearContents();
		}
		return false;
	}
	void ClearContents()
	{
		// Unmap the cached views
		std::map<unsigned int, LPVOID>::iterator first  = pCachedViews.begin();
		std::map<unsigned int, LPVOID>::iterator last  = pCachedViews.end();
		for(; first != last; first++)
		{
			LPVOID pViewBase = first->second;
			if(pViewBase != NULL)
				::UnmapViewOfFile(pViewBase);
		}
		pCachedViews.clear();
		// Clear the Clearance vector and Create it again
		bvFileViewCleared.clear();		
		for(unsigned int i = 0; i < nFileCount; ++i)
			bvFileViewCleared.push_back(CBitVector());
	}

	const BIGNUMBER& Length() const { return _RequestedLen; }

	struct _MemPtr
	{
		unsigned long lViewOffset;
		unsigned long lViewIndex;
		unsigned long lFileIndex;
		unsigned long lMaxViewOffset;
		ElementType/*BYTE*/*		pViewBase;
		HugeArray*	pArray;
		ElementType/*BYTE*/		Dummy[1];
		_MemPtr() :	lViewOffset(0), pViewBase(Dummy), pArray(0), lMaxViewOffset(0), lViewIndex(0), lFileIndex(0)
		{
			Dummy[0] = 0;
		}
		_MemPtr(ElementType/*BYTE*/* _pViewBase, HugeArray* _pArray, unsigned long _lViewOffset=0, unsigned long _lViewIndex=0, unsigned long _lFileIndex=0)
			:	lViewOffset(_lViewOffset), lViewIndex(_lViewIndex), lFileIndex(_lFileIndex), 
			pViewBase(_pViewBase), pArray(_pArray), lMaxViewOffset(/*HugeArray::*/pArray->m_parameter._ViewSize)
		{
			Dummy[0] = 0;
		}
		inline ElementType/*BYTE*/& operator *()
		{			
			return pViewBase[lViewOffset];
		}
		inline _MemPtr operator+(const BIGNUMBER& _increment) const
		{
			if(pViewBase == Dummy) return _MemPtr(); // Are we at the end?

			BIGNUMBER lOffset = (BIGNUMBER(lFileIndex) * /*HugeArray::*/_pArray->m_parameter._MaxNoOfElemsPerFile) + 
				(BIGNUMBER(lViewIndex) * /*HugeArray::*/pArray->m_parameter._NoOfElemsPerView) + 
								lViewOffset + _increment;

			unsigned long lFileIndex = (unsigned long)(lOffset / /*HugeArray::*/pArray->m_parameter._MaxNoOfElemsPerFile);
			BIGNUMBER lFileOffset = (lOffset % /*HugeArray::*/pArray->m_parameter._MaxNoOfElemsPerFile); // Compute the new offset in file
			unsigned long nViewIndex = (unsigned long)(lFileOffset / /*HugeArray::*/pArray->m_parameter._NoOfElemsPerView); // Compute the view that should be containing the offset
			unsigned long nViewOffset = (unsigned long)(lFileOffset % /*HugeArray::*/pArray->m_parameter._NoOfElemsPerView); // Compute the offset in the view

			return _MemPtr(pArray->_GetAt(lFileIndex, nViewIndex, 0), pArray, nViewOffset, nViewIndex, lFileIndex);
		}
		inline _MemPtr& operator++()
		{
			if(++lViewOffset >= lMaxViewOffset)
			{
				lViewOffset = 0;
				if(++lViewIndex >= /*HugeArray::*/pArray->m_parameter._MaxNoOfViewsPerFile)
				{
					lViewIndex = 0;
					if(++lFileIndex >= pArray->nFileCount)
					{
						lFileIndex = 0;
						lMaxViewOffset = 0;
						pViewBase = Dummy;
						pArray = NULL;
						return *this;
					}
				}
				if(pArray != NULL)
					pViewBase = pArray->_GetAt(lFileIndex, lViewIndex, 0);
				else
					pViewBase = Dummy;
			}
			return *this;
		}
		inline bool operator == (const _MemPtr& other) const
		{
			if(pViewBase != Dummy)	// if we are not at end
			{
				return pArray == other.pArray && lViewOffset == other.lViewOffset && lViewIndex == other.lViewIndex && lFileIndex == other.lFileIndex;
			}
			return other.pViewBase == other.Dummy;
		}
		inline bool operator != (const _MemPtr& other) const
		{
			if(other.pViewBase == other.Dummy)	// if the other pointer is at end
			{
				return pViewBase != Dummy;
			}
			return pArray != other.pArray || lViewOffset != other.lViewOffset || lViewIndex != other.lViewIndex || lFileIndex != other.lFileIndex;
		}
	};

	inline _MemPtr Begin()
	{
		return _MemPtr(_GetAt(0,0,0), this);
	}
	inline _MemPtr BeginAt(const BIGNUMBER& _lOffset)
	{
		unsigned long lFileIndex = (unsigned long)(_lOffset / /*HugeArray::*/pArray->m_parameter._MaxNoOfElemsPerFile);
		BIGNUMBER lFileOffset = (unsigned long)(_lOffset % /*HugeArray::*/pArray->m_parameter._MaxNoOfElemsPerFile); // Compute the new offset in file
		unsigned long nViewIndex = (lFileOffset / /*HugeArray::*/pArray->m_parameter._NoOfElemsPerView); // Compute the view that should be containing the offset
		unsigned long nViewOffset = (lFileOffset % /*HugeArray::*/pArray->m_parameter._NoOfElemsPerView); // Compute the offset in the view

		return _MemPtr(_GetAt(lFileIndex, nViewIndex, 0), this, nViewOffset, nViewIndex, lFileIndex);				
	}
	inline _MemPtr End()	// logical end
	{
		return BeginAt(Length());
	}
};

#endif //__HUGEARRAY_H__20D21E1E_D3C9_40b8_8B82_FC1686BDBB58__