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

RegionB::RegionB(RegionContainerClass* regionContainer)
: RegionB::RegionBaseClass(regionContainer,sttcl::TimeDuration<>(0,0,10))
//: RegionB::RegionBaseClass()
{
}

RegionB::~RegionB()
{
}

void RegionB::handleEvent1(IDemoState::Context* context,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "RegionB, handling event1 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(context,currentState,&IConcurrentStateMachine::handleEvent1,eventArgs);
	}
}

void RegionB::handleEvent2(IDemoState::Context* context,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "RegionB, handling event2 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(context,currentState,&IConcurrentStateMachine::handleEvent2,eventArgs);
	}
}

void RegionB::handleEvent3(DemoStateMachine* context,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "RegionB, handling event3 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(context,currentState,&IConcurrentStateMachine::handleEvent3,eventArgs);
	}
}

void RegionB::handleEvent4(IDemoState::Context* context,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "RegionB, handling event4 ..." << endl;
	InnerStateClass* currentState = getState();
	if(currentState)
	{
		dispatchEvent(context,currentState,&IConcurrentStateMachine::handleEvent4,eventArgs);
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
