/*
 * RegionA.cpp
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#include "../DemoStateMachine.h"
#include "../RegionA.h"
#include "../DemoStateA1.h"
#include <iostream>

using namespace std;
using namespace Application;

RegionA::RegionA()
: RegionA::RegionBaseClass(sttcl::TimeDuration<>(0,0,10))
{
}

RegionA::~RegionA()
{
}

void RegionA::handleEvent1(DemoStateMachine* context,const void* eventArgs)
{
	cout << "RegionA, handling event1 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(currentState,&IConcurrentStateMachine::handleEvent1,eventArgs);
	}
}

void RegionA::handleEvent2(DemoStateMachine* context,const void* eventArgs)
{
	cout << "RegionA, handling event2 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(currentState,&IConcurrentStateMachine::handleEvent2,eventArgs);
	}
}

void RegionA::handleEvent3(DemoStateMachine* context,const void* eventArgs)
{
	cout << "RegionA, handling event3 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(currentState,&IConcurrentStateMachine::handleEvent3,eventArgs);
	}
}

void RegionA::handleEvent4(DemoStateMachine* context,const void* eventArgs)
{
	cout << "RegionA, handling event4 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(currentState,&IConcurrentStateMachine::handleEvent4,eventArgs);
	}
}

void RegionA::entryImpl(DemoStateMachine* context)
{
	RegionBaseClass::entryImpl(context);
	cout << "RegionA, entering ..." << endl;
}

void RegionA::exitImpl(DemoStateMachine* context)
{
	RegionBaseClass::exitImpl(context);
	cout << "RegionA, exiting ..." << endl;
}

void RegionA::startingRegionThread()
{
	cout << "RegionA, starting region thread ..." << endl;
}

void RegionA::endingRegionThread()
{
	cout << "RegionA, ending region thread ..." << endl;
}

bool RegionA::initializeImpl(bool force)
{
	cout << "RegionA, initializing ..." << endl;
	return RegionBaseClass::initializeImpl(force);
}

void RegionA::finalizeImpl(bool finalizeSubStateMachines)
{
	cout << "RegionA, finalizing ..." << endl;
	RegionBaseClass::finalizeImpl(finalizeSubStateMachines);
}

RegionA::InnerStateClass* RegionA::getInitialStateImpl() const
{
	cout << "RegionA, returning initial state DemoStateA1 ..." << endl;
	return &DemoStateA1::getInstance();
}
