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
#ifndef __ANYBASE_DOUBLE_BITS_H__
#define __ANYBASE_DOUBLE_BITS_H__

// Export and import macro def
#include "anybase.h"

// refer to unsigned long long
#include "anyport.h"

// namespace AnyBase
namespace AnyBase
{
	/*!
	*
	**/
	class ANYBASE_CLASS CAnyBinaryString
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyBinaryString(unsigned long length);

		/*!
		*
		**/
		~CAnyBinaryString();

	public:
		//
		//
		//
		/*!
		*
		**/
		long GetLength() const 
		{ 
			return m_length;
		}

		/*!
		*
		**/
		long GetAllocatedLength() const
		{ 
			return m_allocatedLength;
		}

		/*!
		*
		**/
		char& operator [] (long i) const 
		{ 
			return m_ptr[i];
		}

		/*!
		*
		**/
		void SetLength(long len) 
		{ 
			m_length = len;
		}

		/*!
		*
		**/
		bool IsEmpty() 
		{ 
			return (m_length == 0); 
		}

		/*!
		*
		**/
		void MarkAsConst()
		{ 
			m_allocatedLength = 0;
		}

		//
		//
		//
		/*!
		*
		**/
		void Set(CAnyBinaryString &str, long offset, long arg_length);

		/*!
		*
		**/
		void Set(char *str, long arg_length);

		/*!
		*
		**/
		void Set(const char *str, long arg_length);

		/*!
		*
		**/
		bool SetAscii(const char *str, long arg_length);

		/*!
		*
		**/
		void SetQuick(char *str, long arg_length);

		/*!
		*
		**/
		bool Set(long num);

		/*!
		*
		**/
		bool Set(unsigned long num);

		/*!
		*
		**/
		bool Set(double num, long decimals);

		/*!
		*
		**/
		const char *GetDirectPtr() const;
		
		/*!
		*
		**/
		char *GetPtr();

		/*!
		*
		**/
		char *GetQuickPtr();

		/*!
		*
		**/
		char *GetSafePtr();

		/*!
		*
		**/
		CAnyBinaryString& operator = (const CAnyBinaryString &s);

		//
		//
		//
		/*!
		*
		**/
		void Append(const char c);

		/*!
		*
		**/
		void Append(const unsigned long n);

		/*!
		*
		**/
		void Append(double d);

		/*!
		*
		**/
		void Append(double *d);

		/*!
		*
		**/
		void Append(const char *data, unsigned long data_len);

	private:
		//
		//
		//
		/*!
		*
		**/
		bool DoInitAlloc(long arg_length);

		/*!
		*
		**/
		bool DoAlloc(long arg_length);

		/*!
		*
		**/
		bool DoRealloc(long alloc_length);

		/*!
		*
		**/
		void DoFree();

		/*!
		*
		**/
		bool DoCopy();

		/*!
		*
		**/
		bool DoCopy(const CAnyBinaryString &str);

		/*!
		*
		**/
		bool DoCopy(const char *str, long arg_length);

	private:
		// data
		char *m_ptr;
		// current length or the last position used as far
		long m_length;
		// allocated length
		long m_allocatedLength;
		// is allocated
		bool m_isAllocated;
	};
}

#endif
