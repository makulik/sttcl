/*
 * ConcurrentStateMachine.cpp
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#include "../ConcurrentStateMachine.h"
#include "../RegionA.h"
#include "../RegionB.h"
#include <iostream>

using namespace std;
using namespace Application;
using Application::ConcurrentStateMachine;

ConcurrentStateMachine::ConcurrentStateMachine(DemoStateMachine* argContext)
: CompositeStateBase(argContext,regions)
, regionA(new RegionA(this))
, regionB(new RegionB(this))
, context(argContext)
{
	regions[0] = regionA;
	regions[1] = regionB;
}

ConcurrentStateMachine::~ConcurrentStateMachine()
{
	delete regionA;
	delete regionB;
}

void ConcurrentStateMachine::handleEvent1(DemoStateMachine* context,const std::string& eventArgs)
{
	cout << "ConcurrentStateMachine, handling event1 ..." << endl;
	sttcl::RefCountPtr<EventArgsClass> eventArgsPtr(new EventArgsClass(eventArgs));
	broadcastEvent(this,&IConcurrentStateMachine::handleEvent1,eventArgsPtr);
}

void ConcurrentStateMachine::handleEvent2(DemoStateMachine* context,const std::string& eventArgs)
{
	cout << "ConcurrentStateMachine, handling event2 ..." << endl;
	sttcl::RefCountPtr<EventArgsClass> eventArgsPtr(new EventArgsClass(eventArgs));
	broadcastEvent(this,&IConcurrentStateMachine::handleEvent2,eventArgsPtr);
}

void ConcurrentStateMachine::handleEvent3(DemoStateMachine* context,const std::string& eventArgs)
{
	cout << "ConcurrentStateMachine, handling event3 ..." << endl;
	sttcl::RefCountPtr<EventArgsClass> eventArgsPtr(new EventArgsClass(eventArgs));
	broadcastEvent(this,&IConcurrentStateMachine::handleEvent3,eventArgsPtr);
}

void ConcurrentStateMachine::handleEvent4(DemoStateMachine* context,const std::string& eventArgs)
{
	cout << "ConcurrentStateMachine, handling event4 ..." << endl;
	sttcl::RefCountPtr<EventArgsClass> eventArgsPtr(new EventArgsClass(eventArgs));
	broadcastEvent(this,&IConcurrentStateMachine::handleEvent4,eventArgsPtr);
}

void ConcurrentStateMachine::entryImpl(DemoStateMachine* context)
{
	cout << "ConcurrentStateMachine, entering ..." << endl;
	CompositeStateBase::entryImpl(context);
}

void ConcurrentStateMachine::exitImpl(DemoStateMachine* context)
{
	cout << "ConcurrentStateMachine, exiting ..." << endl;
	CompositeStateBase::exitImpl(context);
}

bool ConcurrentStateMachine::initializeImpl(bool force)
{
	cout << "ConcurrentStateMachine, initializing ..." << endl;
	return CompositeStateBase::initializeImpl(force);
}

void ConcurrentStateMachine::finalizeImpl(bool finalizeSubStateMachines)
{
	cout << "ConcurrentStateMachine, finalizing ..." << endl;
	CompositeStateBase::finalizeImpl(finalizeSubStateMachines);
}

void ConcurrentStateMachine::startDoImpl(DemoStateMachine* context)
{
	cout << "ConcurrentStateMachine, starting do action ..." << endl;
	CompositeStateBase::startDoImpl(context);
}

void ConcurrentStateMachine::endDoImpl(DemoStateMachine* context)
{
	cout << "ConcurrentStateMachine, ending do action ..." << endl;
	CompositeStateBase::endDoImpl(context);
}

void ConcurrentStateMachine::regionCompletedImpl(RegionsBaseType* region)
{
	cout << "ConcurrentStateMachine, region completed ..." << endl;
	CompositeStateBase::regionCompletedImpl(region);
}

