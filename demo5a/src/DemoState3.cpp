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
#include "../DemoState2.h"

using namespace std;
using namespace Application;
using Application::DemoState3;

DemoState3::DemoState3()
: StateBaseClass(&DemoState3::doAction,false,sttcl::TimeDuration<>(0,0,20))
{
}

DemoState3::~DemoState3()
{
}

void DemoState3::handleEvent1(DemoStateMachine* context)
{
	cout << "DemoState3, handling event1 ..." << endl;
}

void DemoState3::handleEvent2(DemoStateMachine* context)
{
	cout << "DemoState3, handling event2 ..." << endl;
}

void DemoState3::handleEvent3(DemoStateMachine* context)
{
	cout << "DemoState3, handling event3 ..." << endl;
	// no guards, change to DemoState1
	changeState(context,&DemoState1::getInstance());
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

void DemoState3::doAction(DemoStateMachine* context, bool firstCall)
{
	cout << "DemoState3, do Action called ..." << endl;
}

bool DemoState3::checkDirectTransitionImpl(DemoStateMachine* context, bool& finalize, StateBase<DemoStateMachine,IDemoState>*& nextState)
{
	cout << "DemoState3, checking direct transitions  ..." << endl;
	if(context->getX() == 2)
	{
		// passed guard, changing to DemoState2
		nextState = &DemoState2::getInstance();
		return true;
	}
	else if(context->getY() >= 4)
	{
		// go on with DemoState1
		nextState = &DemoState1::getInstance();
		return true;
	}
	return false;
}
