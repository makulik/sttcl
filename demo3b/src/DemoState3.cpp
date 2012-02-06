/*
 * DemoState3.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>
#include "../DemoStateMachine.h"
#include "../DemoState3.h"
#include "../DemoState1.h"
#include "../DemoState3a.h"
#include "../DemoState3b.h"

using namespace std;
using namespace Application;
using Application::DemoState3;

DemoState3::DemoState3(DemoStateMachine* context)
: demoStateMachine(context)
, demoState3b(new DemoState3b(this))
{
}

DemoState3::~DemoState3()
{
	delete demoState3b;
}

void DemoState3::handleEvent1(DemoStateMachine* context)
{
	cout << "DemoState3, handling event1 ..." << endl;
	if(!isFinalized())
	{
		// Delegate event handling to sub state
		InnerStateBaseClass* currentState = getState();
		currentState->handleEvent1(this);
	}
}

void DemoState3::handleEvent2(DemoStateMachine* context)
{
	cout << "DemoState3, handling event2 ..." << endl;
	if(!isFinalized())
	{
		// Delegate event handling to sub state
		InnerStateBaseClass* currentState = getState();
		currentState->handleEvent2(this);
	}
}

void DemoState3::handleEvent3(DemoStateMachine* context)
{
	cout << "DemoState3, handling event3 ..." << endl;
	if(!isFinalized())
	{
		// First delegate event handling to sub state
		InnerStateBaseClass* currentState = getState();
		currentState->handleEvent3(this);
	}

	// no guards, change to DemoState1
	changeState(context,&DemoState1::getInstance());
}

void DemoState3::handleEvent4(DemoStateMachine* context)
{
	cout << "DemoState3, handling event4 ..." << endl;
	if(!isFinalized())
	{
		// Delegate event handling to sub state
		InnerStateBaseClass* currentState = getState();
		currentState->handleEvent4(this);
	}
}

void DemoState3::handleEvent5(DemoStateMachine* context)
{
	cout << "DemoState3, handling event5 ..." << endl;
	if(!isFinalized())
	{
		// Delegate event handling to sub state
		InnerStateBaseClass* currentState = getState();
		currentState->handleEvent5(this);
	}
}


void DemoState3::entryImpl(DemoStateMachine* context)
{
	cout << "DemoState3, entering ..." << endl;
	StateBaseClass::entryImpl(context);
}

void DemoState3::exitImpl(DemoStateMachine* context)
{
	cout << "DemoState3, exiting ..." << endl;
	StateBaseClass::exitImpl(context);
}

bool DemoState3::initializeImpl(bool force)
{
	cout << "DemoState3, initializing ..." << endl;
	return StateBaseClass::initializeImpl(force);
}

void DemoState3::finalizeImpl(bool finalizeSubStateMachines)
{
	cout << "DemoState3, finalizing ..." << endl;
	StateBaseClass::finalizeImpl(finalizeSubStateMachines);
}

DemoState3::InnerStateBaseClass* DemoState3::getInitialStateImpl() const
{
	return &DemoState3a::getInstance();
}

int DemoState3::getX() const
{
	return demoStateMachine->getX();
}

int DemoState3::getY() const
{
	return demoStateMachine->getY();
}

int DemoState3::getZ() const
{
	return demoStateMachine->getZ();
}
