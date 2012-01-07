/*
 * ConcurrentStateMachine.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef CONCURRENTSTATEMACHINE_H_
#define CONCURRENTSTATEMACHINE_H_

#include "DemoStateMachine.h"
#include "ConcurrentCompositeState.h"
#include "IConcurrentStatemachine.h"
#include "RegionA.h"
#include "RegionB.h"

namespace Application
{

class ConcurrentStateMachine
: public sttcl::ConcurrentCompositeState<ConcurrentStateMachine,DemoStateMachine,IConcurrentStateMachine,2>
{
public:
	typedef sttcl::ConcurrentCompositeState<ConcurrentStateMachine,DemoStateMachine,IConcurrentStateMachine,2> CompositeStateBase;
	typedef typename CompositeStateBase::StateInterface StateInterface;

	ConcurrentStateMachine(DemoStateMachine* context);
	virtual ~ConcurrentStateMachine();

	virtual void handleEvent1(DemoStateMachine* context, const void* eventArgs = 0);
	virtual void handleEvent2(DemoStateMachine* context, const void* eventArgs = 0);
	virtual void handleEvent3(DemoStateMachine* context, const void* eventArgs = 0);
	virtual void handleEvent4(DemoStateMachine* context, const void* eventArgs = 0);

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
	RegionA regionA;
	RegionB regionB;
	CompositeStateBase::RegionsArray regions;
	DemoStateMachine* context;

};

}

#endif /* CONCURRENTSTATEMACHINE_H_ */
