/*
 * DemoStateMachine.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>

#include "../DemoStateMachine.h"
#include "../DemoState1.h"

using namespace std;
using namespace Application;
using Application::DemoStateMachine;

DemoStateMachine::DemoStateMachine()
: x(5)
, y(2)
{
}

DemoStateMachine::~DemoStateMachine()
{
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

DemoStateMachine::StateMachineBase::StateBaseClass* DemoStateMachine::getInitialStateImpl() const
{
	return &DemoState1::getInstance();
}
