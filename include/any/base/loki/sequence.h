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
#ifndef __ANYBASE_LOKI_SEQUENCE_H__
#define __ANYBASE_LOKI_SEQUENCE_H__

//
#include "Typelist.h"

//
namespace AnyBase
{
	namespace Loki
	{
		template
		<
			 class T01=NullType,class T02=NullType,class T03=NullType,class T04=NullType,class T05=NullType,
			 class T06=NullType,class T07=NullType,class T08=NullType,class T09=NullType,class T10=NullType,
			 class T11=NullType,class T12=NullType,class T13=NullType,class T14=NullType,class T15=NullType,
			 class T16=NullType,class T17=NullType,class T18=NullType,class T19=NullType,class T20=NullType
		>
		struct Seq
		{
		private:
			 typedef typename Seq<T02, T03, T04, T05, T06, T07, T08, T09, T10,
									T11, T12, T13, T14, T15, T16, T17, T18, T19, T20>::Type 
								TailResult;
		public:
			 typedef Typelist<T01, TailResult> Type;
		};
	        
		template<>
		struct Seq<>
		{
			 typedef NullType Type;
		};

	}   // namespace Loki
}
#endif // end file guardian

