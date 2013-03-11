/*
 * IConcurrentStateMachine.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef ICONCURRENTSTATEMACHINE_H_
#define ICONCURRENTSTATEMACHINE_H_

#include "Region.h"
#include "IDemoState.h"
#include "EventArgsClass.h"

namespace Application
{

class ConcurrentStateMachine;

class IConcurrentStateMachine;

class IConcurrentStateMachine
{
public:
	typedef DemoStateMachine Context;
	typedef sttcl::RegionBase<ConcurrentStateMachine,IConcurrentStateMachine,EventArgsClass> RegionContext;

	virtual void handleEvent1(Context* context,RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs) = 0;
	virtual void handleEvent2(Context* context,RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs) = 0;
	virtual void handleEvent3(Context* context,RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs) = 0;
	virtual void handleEvent4(Context* context,RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs) = 0;
	virtual ~IConcurrentStateMachine() {}
};

}

#endif /* ICONCURRENTSTATEMACHINE_H_ */
