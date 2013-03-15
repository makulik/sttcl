/*
 * IConcurrentStateMachine.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef ICONCURRENTSTATEMACHINE_H_
#define ICONCURRENTSTATEMACHINE_H_

#include "Region.h"
#include "DemoStateMachine.h"
#include "EventArgsClass.h"

namespace Application
{

class ConcurrentStateMachine;

class IConcurrentStateMachine
{
public:
	typedef DemoStateMachine Context;
	typedef sttcl::RegionBase<DemoStateMachine,ConcurrentStateMachine,EventArgsClass> RegionContext;

	virtual void handleEvent1(DemoStateMachine* context,RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs) = 0;
	virtual void handleEvent2(DemoStateMachine* context,RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs) = 0;
	virtual void handleEvent3(DemoStateMachine* context,RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs) = 0;
	virtual void handleEvent4(DemoStateMachine* context,RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs) = 0;
	virtual ~IConcurrentStateMachine() {}
};

}

#endif /* ICONCURRENTSTATEMACHINE_H_ */
