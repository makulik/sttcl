/*
 * DemoStateMachine.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATEMACHINE_H_
#define DEMOSTATEMACHINE_H_

#include "IDemoState.h"
#include "StateMachine.h"

namespace Application
{

class ConcurrentStateMachine;

class DemoStateMachine
: public sttcl::StateMachine<DemoStateMachine,IDemoState>
{
public:
	typedef sttcl::StateMachine<DemoStateMachine,IDemoState> StateMachineBase;

	DemoStateMachine();
	virtual ~DemoStateMachine();

	void event1();
	void event2();
	void event3();
	void event4();

	StateMachineBase::StateBaseClass* getInitialStateImpl() const;

    void subStateMachineCompletedImpl(StateMachineBase::StateBaseClass* state);

private:
    ConcurrentStateMachine* concurrentStateMachine;
};

}

#endif /* DEMOSTATEMACHINE_H_ */
