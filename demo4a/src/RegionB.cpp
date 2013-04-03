/*
 * RegionB.cpp
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#include "../DemoStateMachine.h"
#include "../ConcurrentStateMachine.h"
#include "../RegionB.h"
#include "../DemoStateB1.h"
#include <iostream>

using namespace std;
using namespace Application;

RegionB::RegionB(ConcurrentStateMachine* regionContainer)
: RegionB::RegionBaseClass(regionContainer,sttcl::TimeDuration<>(0,0,10))
{
}

RegionB::~RegionB()
{
}

void RegionB::handleEvent1(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "RegionB, handling event1 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(context,currentState,&IConcurrentStateMachine::handleEvent1,eventArgs);
	}
}

void RegionB::handleEvent2(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "RegionB, handling event2 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(context,currentState,&IConcurrentStateMachine::handleEvent2,eventArgs);
	}
}

void RegionB::handleEvent3(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "RegionB, handling event3 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(context,currentState,&IConcurrentStateMachine::handleEvent3,eventArgs);
	}
}

void RegionB::handleEvent4(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "RegionB, handling event4 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(context,currentState,&IConcurrentStateMachine::handleEvent4,eventArgs);
	}
}

void RegionB::entryImpl(ConcurrentStateMachine* context)
{
	RegionBaseClass::entryImpl(context);
	cout << "RegionB, entering ..." << endl;
}

void RegionB::exitImpl(ConcurrentStateMachine* context)
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
