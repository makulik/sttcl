/*
 * RegionA.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef REGIONA_H_
#define REGIONA_H_

#include "Region.h"
#include "DemoStateMachine.h"
#include "ConcurrentStateMachine.h"
#include "EventArgsClass.h"

namespace Application
{

class ConcurrentStateMachine;

class RegionA
: public sttcl::Region<RegionA,ConcurrentStateMachine,IConcurrentStateMachine,EventArgsClass>
{
public:
	typedef sttcl::Region<RegionA,ConcurrentStateMachine,IConcurrentStateMachine,EventArgsClass> RegionBaseClass;
	typedef typename RegionBaseClass::InnerStateClass InnerStateClass;
	typedef ConcurrentStateMachine RegionContainerClass;

	RegionA(ConcurrentStateMachine* regionContainer);
	virtual ~RegionA();

	virtual void handleEvent1(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs);
	virtual void handleEvent2(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs);
	virtual void handleEvent3(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs);
	virtual void handleEvent4(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs);

	void entryImpl(ConcurrentStateMachine* context);
	void exitImpl(ConcurrentStateMachine* context);

	void startingRegionThread();
	void endingRegionThread();

    bool initializeImpl(bool force);
    void finalizeImpl(bool finalizeSubStateMachines);

	InnerStateClass* getInitialStateImpl() const;
};

}

#endif /* REGIONA_H_ */
