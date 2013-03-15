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
#include "IDemoState.h"

namespace Application
{
    class RegionA;
    class RegionB;

class ConcurrentStateMachine
: public sttcl::ConcurrentCompositeState<ConcurrentStateMachine,DemoStateMachine,IConcurrentStateMachine,2,EventArgsClass>
{
public:
	typedef sttcl::StateBase<ConcurrentStateMachine,IConcurrentStateMachine> InnerStateBaseClass;

	typedef sttcl::ConcurrentCompositeState<ConcurrentStateMachine,DemoStateMachine,IConcurrentStateMachine,2,EventArgsClass> CompositeStateBase;

	typedef typename CompositeStateBase::RegionsBaseType RegionsBaseType;

	ConcurrentStateMachine(DemoStateMachine* context);
	virtual ~ConcurrentStateMachine();

	virtual void handleEvent1(DemoStateMachine* context,const std::string& eventArgs);
	virtual void handleEvent2(DemoStateMachine* context,const std::string& eventArgs);
	virtual void handleEvent3(DemoStateMachine* context,const std::string& eventArgs);
	virtual void handleEvent4(DemoStateMachine* context,const std::string& eventArgs);

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

    void regionCompletedImpl(RegionsBaseType* region);

private:
	RegionA* regionA;
	RegionB* regionB;
	CompositeStateBase::RegionsArray regions;
	DemoStateMachine* context;

};

}

#endif /* CONCURRENTSTATEMACHINE_H_ */
