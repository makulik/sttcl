/*
 * DemoStateMachine.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>

#include "../ConcurrentStateMachine.h"
#include "../DemoStateMachine.h"

using namespace std;
using namespace Application;
using Application::DemoStateMachine;

DemoStateMachine::DemoStateMachine()
: concurrentStateMachine(new ConcurrentStateMachine(this))
{
}

DemoStateMachine::~DemoStateMachine()
{
	delete concurrentStateMachine;
}

void DemoStateMachine::event1()
{
	cout << "DemoStateMachine, event1 triggered ..." << endl;
	StateMachineBase::StateBaseClass* currentState = getState();
	if(currentState)
	{
		currentState->handleEvent1(this);
	}
}

void DemoStateMachine::event2()
{
	cout << "DemoStateMachine, event2 triggered ..." << endl;
	StateMachineBase::StateBaseClass* currentState = getState();
	if(currentState)
	{
		currentState->handleEvent2(this);
	}
}

void DemoStateMachine::event3()
{
	cout << "DemoStateMachine, event3 triggered ..." << endl;
	StateMachineBase::StateBaseClass* currentState = getState();
	if(currentState)
	{
		currentState->handleEvent3(this);
	}
}

void DemoStateMachine::event4()
{
	cout << "DemoStateMachine, event4 triggered ..." << endl;
	StateMachineBase::StateBaseClass* currentState = getState();
	if(currentState)
	{
		currentState->handleEvent4(this);
	}
}

void DemoStateMachine::subStateMachineCompletedImpl(StateMachineBase::StateBaseClass* state)
{
	cout << "DemoStateMachine, sub statemachine completed ..." << endl;
	StateMachineBase::subStateMachineCompletedImpl(state);
	finalize();
}

sttcl::StateBase<DemoStateMachine,IDemoState>* DemoStateMachine::getInitialStateImpl() const
{
	cout << "DemoStateMachine, returning initial state ..." << endl;
	return concurrentStateMachine;
}
