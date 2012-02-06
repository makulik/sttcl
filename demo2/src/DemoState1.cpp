/*
 * DemoState1.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>
#include <unistd.h>
#include <stddef.h>

#include "../DemoStateMachine.h"
#include "../DemoState1.h"
#include "../DemoState2.h"
#include "../DemoState3.h"

using namespace std;
using namespace Application;
using Application::DemoState1;

DemoState1::DemoState1()
: StateBaseClass(&DemoState1::doAction,sttcl::TimeDuration<>(0,0,20))
{
}

DemoState1::~DemoState1()
{
}

void DemoState1::handleEvent1(DemoStateMachine* context)
{
	cout << "DemoState1, handling event1 ..." << endl;
	// no guards, change to DemoState2
	changeState(context,&DemoState2::getInstance());
}

void DemoState1::handleEvent2(DemoStateMachine* context)
{
	cout << "DemoState1, handling event2 ..." << endl;
	if(context->getX() >= 3)
	{
		cout << "DemoState1, guard [x >= 3] passed" << endl;
		changeState(context,&DemoState3::getInstance());
	}
	else
	{
		cout << "DemoState1, guard [x >= 3] enabled" << endl;
	}
}

void DemoState1::handleEvent3(DemoStateMachine* context)
{
	cout << "DemoState1, handling event3 ..." << endl;
}

void DemoState1::entryImpl(DemoStateMachine* context)
{
	cout << "DemoState1, entering ..." << endl;
	StateBaseClass::entryImpl(context);
}

void DemoState1::exitImpl(DemoStateMachine* context)
{
	cout << "DemoState1, exiting ..." << endl;
	StateBaseClass::exitImpl(context);
}

void DemoState1::doAction(DemoStateMachine* context, bool initialCall)
{
	if(initialCall)
	{
		cout << "DemoState1, do Action called 1st time after entering ..." << endl;
	}
	else
	{
		cout << "DemoState1, do Action called ..." << endl;
	}
}
