/*
 * ConcurrentStateMachine.cpp
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#include "../ConcurrentStateMachine.h"
#include <iostream>

using namespace std;
using namespace Application;
using Application::ConcurrentStateMachine;

ConcurrentStateMachine::ConcurrentStateMachine(DemoStateMachine* argContext)
: CompositeStateBase(argContext,regions)
, regionA(this)
, regionB(this)
, context(argContext)
{
	regions[0] = &regionA;
	regions[1] = &regionB;
}

ConcurrentStateMachine::~ConcurrentStateMachine()
{
}

void ConcurrentStateMachine::handleEvent1(DemoStateMachine* context,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "ConcurrentStateMachine, handling event1 ..." << endl;
	CompositeStateBase::broadcastEvent(context,&IDemoState::handleEvent1,eventArgs);
}

void ConcurrentStateMachine::handleEvent2(DemoStateMachine* context,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "ConcurrentStateMachine, handling event2 ..." << endl;
	CompositeStateBase::broadcastEvent(context,&IDemoState::handleEvent2,eventArgs);
}

void ConcurrentStateMachine::handleEvent3(DemoStateMachine* context,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "ConcurrentStateMachine, handling event3 ..." << endl;
	CompositeStateBase::broadcastEvent(context,&IDemoState::handleEvent3,eventArgs);
}

void ConcurrentStateMachine::handleEvent4(DemoStateMachine* context,sttcl::RefCountPtr<EventArgsClass> eventArgs)
{
	cout << "ConcurrentStateMachine, handling event4 ..." << endl;
	CompositeStateBase::broadcastEvent(context,&IDemoState::handleEvent4,eventArgs);
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

void ConcurrentStateMachine::regionCompletedImpl(RegionsBasetype* region)
{
	cout << "ConcurrentStateMachine, region completed ..." << endl;
	CompositeStateBase::regionCompletedImpl(region);
}

