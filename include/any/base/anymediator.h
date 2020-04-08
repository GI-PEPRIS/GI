/*!
 * The UrbanEye PND solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy one kind
 * of mobile or portable devices with competitive qualities being a leading one.
 *
 * Copyright (C) 2008 Xiujie Sheng
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
 * Graduate School
 *
 * Xiujie Sheng
 * herman.sheng@gmail.com
 */

// Refer to EXPORT & IMPORT macro definitions
#include "anybase.h"

// refer to CGeoPoint
#include "anygeom.h"

#ifndef __ANYBASE_MEDIATOR_H
#define __ANYBASE_MEDIATOR_H

// namespace
namespace AnyBase
{
	// Forward class
	class CAnyObserver;

	// Following the definition of OBERSVER & MEDIATOR patterns, there should have some obvious different semantics:
	// For OBSERVER pattern, it generllay maintain the message communication bewteen one object (CAnyObservable) with those
	// objects (CAnyObservers) interested by it. However, MEDIATOR is simply to decouple the unneccessary relationships among
	// some objects, namely, they shouldn't seen each other in order to let them development in more easiy way etc.
	// 
	// Here, both patterns supply an indirect calling to other objects, so it is possible to let those interfaces exposed by
	// those packeges can be envolved independently.
	//
	// But when mixing below interface defintion with one interface specified by one package, namely using multi-inherit way
	// we should care about its compiling error when against different C++ compiles and its memory layout.
	//
	/*!
	* Obersvale object is to notify its changes to those interesting observers.
	*/
    class CAnyObservable
    {
    public:
        //
        //
        //
        /*!
        *
        */
        virtual ~CAnyObservable(){}

        //
        //
        //
        /*!
        * Let sub-class have its specified event types
        */
        virtual void Notify(short type) = 0;

        /*!
        *
        */
        virtual void Register(CAnyObserver *oneObserver) = 0;
    };

	/*!
	* 
	*/
    class CAnyObserver
    {
    public:
        //
        //
        //
        /*!
        *
        */
        virtual ~CAnyObserver(){}

        //
        //
        //
        /*!
        *
        */
        virtual void Update(short type = 0, void *para = 0) = 0;
    };

	/*!
	* In order to throughly decouple the relationships between each package of UrbanEye PND, it had better to 
	* specify the funtion prototype here representing those kinds of relationship as suitable as possible.
	*/
	class CAnyMediator
	{
	public:
		//
		//
		//
		/*!
		*
		*/
		virtual ~CAnyMediator()
		{
		}

	public:
		//
		//
		//
		/*!
		* return encoding block from CAnyLogLayer
		**/
		virtual void PickLogTraceData(const CGeoPoint<double> &pos, void **data, int &number)
		{
			number = 0;
			*data = 0;
		}

		/*!
		* return TraceRecord data from CAnySegyLayer
		**/
		virtual void PickSeismicTraceData(const CGeoPoint<double> &pos, void **data, int &number)
		{
			number = 0;
			*data = 0;
		}
	};

	/*!
	*
	**/
	class CAnyFunctor
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		virtual ~CAnyFunctor()
		{
		}

	public:
		/*!
		*
		**/
		virtual bool operator()(bool, int, int) = 0;
	};
}

#endif