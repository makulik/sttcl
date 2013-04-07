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
#include "ConcurrentStatemachine.h"
#include "Event.h"

namespace Application
{

class ConcurrentStateMachine;

class RegionA
: public sttcl::Region<RegionA,ConcurrentStateMachine,IConcurrentStateMachine,Event>
{
public:
	typedef sttcl::Region<RegionA,ConcurrentStateMachine,IConcurrentStateMachine,Event> RegionBaseClass;
	typedef typename RegionBaseClass::InnerStateClass InnerStateClass;
	typedef ConcurrentStateMachine RegionContainerClass;

	RegionA(RegionContainerClass* regionContainer);
	virtual ~RegionA();

	virtual void handleEvent1(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<Event> eventArgs);
	virtual void handleEvent2(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<Event> eventArgs);
	virtual void handleEvent3(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<Event> eventArgs);
	virtual void handleEvent4(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<Event> eventArgs);

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
