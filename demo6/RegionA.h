/*
 * RegionA.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef REGIONA_H_
#define REGIONA_H_

#include "Region.h"
#include "IConcurrentStatemachine.h"

namespace Application
{

class ConcurrentStateMachine;
class DemoStateMachine;

class RegionA
: public sttcl::Region<RegionA,ConcurrentStateMachine,IConcurrentStateMachine,EventArgsClass,sttcl::CompositeStateHistoryType::None>
{
public:
	typedef sttcl::Region<RegionA,ConcurrentStateMachine,IConcurrentStateMachine,EventArgsClass,sttcl::CompositeStateHistoryType::None> RegionBaseClass;
	typedef typename RegionBaseClass::InnerStateClass InnerStateClass;
	typedef ConcurrentStateMachine RegionContainerClass;

	RegionA(RegionContainerClass* regionContainer);
	virtual ~RegionA();

	virtual void handleEvent1(DemoStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs);
	virtual void handleEvent2(DemoStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs);
	virtual void handleEvent3(DemoStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs);
	virtual void handleEvent4(DemoStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext	,sttcl::RefCountPtr<EventArgsClass> eventArgs);

	void entryImpl(DemoStateMachine* context);
	void exitImpl(DemoStateMachine* context);

	void startingRegionThread();
	void endingRegionThread();

    bool initializeImpl(bool force);
    void finalizeImpl(bool finalizeSubStateMachines);

	InnerStateClass* getInitialStateImpl() const;
};

}

#endif /* REGIONA_H_ */
