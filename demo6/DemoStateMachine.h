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
#include "ClassMethodThread.h"
#include "EventQueue.h"
#include "EventArgsClass.h"
#include "RefCountPtr.h"

namespace Application
{

class CmdInterpreter;
class ConcurrentStateMachine;

class DemoStateMachine
: public sttcl::StateMachine<DemoStateMachine,IDemoState>
{
    friend class CmdInterpreter;
public:
	typedef sttcl::StateMachine<DemoStateMachine,IDemoState> StateMachineBase;
	typedef sttcl::RefCountPtr<EventArgsClass> EventPtr;

	DemoStateMachine();
	virtual ~DemoStateMachine();

	void run();
	void sendEvent(const EventPtr& event);
	bool isTerminationCmd(const std::string& cmd);
	bool isTerminated();
	void waitForTermination();

	StateMachineBase::StateBaseClass* getInitialStateImpl() const;

    void subStateMachineCompletedImpl(StateMachineBase::StateBaseClass* state);

private:
	void event1();
	void event2();
	void event3();
	void event4();

	void* threadMethod(void* userArgs);

	sttcl::ClassMethodThread<DemoStateMachine> thread;
	sttcl::EventQueue<EventPtr> eventQueue;
	ConcurrentStateMachine* concurrentStateMachine;
	CmdInterpreter* cmdInterpreter;
	sttcl::internal::SttclMutex<> threadMutex;

	bool terminated;
};

}

#endif /* DEMOSTATEMACHINE_H_ */
