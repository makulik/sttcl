/*
 * DemoState1.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>

#include "../DemoStateMachine.h"
#include "../DemoState1.h"
#include "../DemoState2.h"

using namespace std;
using namespace Application;
using Application::DemoState1;

DemoState1::DemoState1()
: StateBaseClass()
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
		changeState(context,context->getDemoState3());
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

void DemoState1::handleEvent4(DemoStateMachine* context)
{
	cout << "DemoState1, handling event4 ..." << endl;
}

void DemoState1::handleEvent5(DemoStateMachine* context)
{
	cout << "DemoState1, handling event5 ..." << endl;
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

DemoState1& DemoState1::getInstance()
{
	static DemoState1 theInstance;
	return theInstance;
}
