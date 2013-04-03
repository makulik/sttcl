/*
 * RegionA.cpp
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#include "../DemoStateMachine.h"
#include "../ConcurrentStateMachine.h"
#include "../RegionA.h"
#include "../DemoStateA1.h"
#include <iostream>

using namespace std;
using namespace Application;

RegionA::RegionA(ConcurrentStateMachine* regionContainer)
: RegionA::RegionBaseClass(regionContainer,sttcl::TimeDuration<>(0,0,10))
{
}

RegionA::~RegionA()
{
}

void RegionA::handleEvent1(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "RegionA, handling event1 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(context,currentState,&IConcurrentStateMachine::handleEvent1,eventArgs);
	}
}

void RegionA::handleEvent2(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "RegionA, handling event2 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(context,currentState,&IConcurrentStateMachine::handleEvent2,eventArgs);
	}
}

void RegionA::handleEvent3(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "RegionA, handling event3 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(context,currentState,&IConcurrentStateMachine::handleEvent3,eventArgs);
	}
}

void RegionA::handleEvent4(ConcurrentStateMachine* context, IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "RegionA, handling event4 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(context,currentState,&IConcurrentStateMachine::handleEvent4,eventArgs);
	}
}

void RegionA::entryImpl(ConcurrentStateMachine* context)
{
	RegionBaseClass::entryImpl(context);
	cout << "RegionA, entering ..." << endl;
}

void RegionA::exitImpl(ConcurrentStateMachine* context)
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
