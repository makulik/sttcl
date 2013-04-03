/*
 * ConcurrentStateMachine.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef CONCURRENTSTATEMACHINE_H_
#define CONCURRENTSTATEMACHINE_H_

#include "ConcurrentCompositeState.h"
#include "DemoStateMachine.h"
#include "IConcurrentStatemachine.h"
#include "EventArgsClass.h"

namespace Application
{

class RegionA;
class RegionB;

class ConcurrentStateMachine
: public sttcl::ConcurrentCompositeState<ConcurrentStateMachine,DemoStateMachine,IConcurrentStateMachine,2,EventArgsClass>
{
public:
	typedef sttcl::ConcurrentCompositeState<ConcurrentStateMachine,DemoStateMachine,IConcurrentStateMachine,2,EventArgsClass> CompositeStateBase;

	ConcurrentStateMachine(DemoStateMachine* context);
	virtual ~ConcurrentStateMachine();

	virtual void handleEvent1(DemoStateMachine* context,sttcl::RefCountPtr<EventArgsClass> eventArgs);
	virtual void handleEvent2(DemoStateMachine* context,sttcl::RefCountPtr<EventArgsClass> eventArgs);
	virtual void handleEvent3(DemoStateMachine* context,sttcl::RefCountPtr<EventArgsClass> eventArgs);
	virtual void handleEvent4(DemoStateMachine* context,sttcl::RefCountPtr<EventArgsClass> eventArgs);

    void entryImpl(DemoStateMachine* context);
    void exitImpl(DemoStateMachine* context);
    void startDoImpl(DemoStateMachine* context);
    void endDoImpl(DemoStateMachine* context);

    bool initializeImpl(bool force);

    /**
     * Default implementation for finalize().
     *
     * @param finalizeSubStateMachines Indicates to finalize any sub state machines.
     */
    void finalizeImpl(bool finalizeSubStateMachines);

private:
	RegionA* regionA;
	RegionB* regionB;
	CompositeStateBase::RegionsArray regions;
	//DemoStateMachine* context;

};

}

#endif /* CONCURRENTSTATEMACHINE_H_ */
