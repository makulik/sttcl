/*
 * DemoState3b.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>

#include "../DemoState3.h"
#include "../DemoState3b.h"
#include "../DemoState3c.h"
#include "../DemoState3b_1.h"

using namespace std;
using namespace Application;
using Application::DemoState3b;

DemoState3b::DemoState3b(DemoState3* context)
: StateBaseClass()
, demoState3(context)
{
}

DemoState3b::~DemoState3b()
{
}

void DemoState3b::handleEvent1(DemoState3* context)
{
	cout << "DemoState3b, handling event1 ..." << endl;
	if(!isFinalized())
	{
		// Delegate event handling to sub state
		InnerStateBaseClass* currentState = getState();
		currentState->handleEvent1(this);
	}

	if(context->getZ() == 3)
	{
		cout << "DemoState3b, guard [z == 3] passed" << endl;
		changeState(context,&DemoState3c::getInstance());
	}
	else
	{
		cout << "DemoState3b, guard [z == 3] enabled" << endl;
		context->initialize();
	}
}

void DemoState3b::handleEvent2(DemoState3* context)
{
	cout << "DemoState3b, handling event2 ..." << endl;
	if(!isFinalized())
	{
		// Delegate event handling to sub state
		InnerStateBaseClass* currentState = getState();
		currentState->handleEvent2(this);
	}
}

void DemoState3b::handleEvent3(DemoState3* context)
{
	cout << "DemoState3b, handling event3 ..." << endl;
	if(!isFinalized())
	{
		// Delegate event handling to sub state
		InnerStateBaseClass* currentState = getState();
		currentState->handleEvent3(this);
	}
}

void DemoState3b::handleEvent4(DemoState3* context)
{
	cout << "DemoState3b, handling event4 ..." << endl;
	if(!isFinalized())
	{
		// Delegate event handling to sub state
		InnerStateBaseClass* currentState = getState();
		currentState->handleEvent4(this);
	}
}

void DemoState3b::handleEvent5(DemoState3* context)
{
	cout << "DemoState3b, handling event5 ..." << endl;
	if(!isFinalized())
	{
		// Delegate event handling to sub state
		InnerStateBaseClass* currentState = getState();
		currentState->handleEvent5(this);
	}
}

bool DemoState3b::initializeImpl(bool force)
{
	cout << "DemoState3b, initializing ..." << endl;
	return StateBaseClass::initializeImpl(force);
	//return true;
}

void DemoState3b::finalizeImpl(bool finalizeSubStateMachines)
{
	cout << "DemoState3b, finalizing ..." << endl;
	StateBaseClass::finalizeImpl(finalizeSubStateMachines);
}

void DemoState3b::entryImpl(DemoState3* context)
{
	cout << "DemoState3b, entering ..." << endl;
	StateBaseClass::entryImpl(context);
}

void DemoState3b::exitImpl(DemoState3* context)
{
	StateBaseClass::exitImpl(context);
	cout << "DemoState3b, exiting ..." << endl;
}

DemoState3b::InnerStateBaseClass* DemoState3b::getInitialStateImpl() const
{
	return &DemoState3b_1::getInstance();
}

int DemoState3b::getX() const
{
	return demoState3->getX();
}

int DemoState3b::getY() const
{
	return demoState3->getY();
}

int DemoState3b::getZ() const
{
	return demoState3->getZ();
}
