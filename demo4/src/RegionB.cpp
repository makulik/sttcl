/*
 * RegionB.cpp
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#include "../DemoStateMachine.h"
#include "../RegionB.h"
#include "../DemoStateB1.h"
#include <iostream>

using namespace std;
using namespace Application;

RegionB::RegionB()
: RegionB::RegionBaseClass(sttcl::TimeDuration<>(0,0,10))
{
}

RegionB::~RegionB()
{
}

void RegionB::handleEvent1(DemoStateMachine* context,const void* eventArgs)
{
	cout << "RegionB, handling event1 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(currentState,&IConcurrentStateMachine::handleEvent1,eventArgs);
	}
}

void RegionB::handleEvent2(DemoStateMachine* context,const void* eventArgs)
{
	cout << "RegionB, handling event2 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(currentState,&IConcurrentStateMachine::handleEvent2,eventArgs);
	}
}

void RegionB::handleEvent3(DemoStateMachine* context,const void* eventArgs)
{
	cout << "RegionB, handling event3 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(currentState,&IConcurrentStateMachine::handleEvent3,eventArgs);
	}
}

void RegionB::handleEvent4(DemoStateMachine* context,const void* eventArgs)
{
	cout << "RegionB, handling event4 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(currentState,&IConcurrentStateMachine::handleEvent4,eventArgs);
	}
}

void RegionB::entryImpl(DemoStateMachine* context)
{
	RegionBaseClass::entryImpl(context);
	cout << "RegionB, entering ..." << endl;
}

void RegionB::exitImpl(DemoStateMachine* context)
{
	cout << "RegionB, exiting ..." << endl;
	RegionBaseClass::exitImpl(context);
}

void RegionB::startingRegionThread()
{
	cout << "RegionB, starting region thread ..." << endl;
}

void RegionB::endingRegionThread()
{
	cout << "RegionB, ending region thread ..." << endl;
}

bool RegionB::initializeImpl(bool force)
{
	cout << "RegionB, initializing ..." << endl;
	return RegionBaseClass::initializeImpl(force);
}

void RegionB::finalizeImpl(bool finalizeSubStateMachines)
{
	cout << "RegionB, finalizing ..." << endl;
	RegionBaseClass::finalizeImpl(finalizeSubStateMachines);
}

RegionB::InnerStateClass* RegionB::getInitialStateImpl() const
{
	cout << "RegionB, returning initial state DemoStateB1 ..." << endl;
	return &DemoStateB1::getInstance();
}
