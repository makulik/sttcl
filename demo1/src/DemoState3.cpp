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

using namespace std;
using namespace Application;
using Application::DemoState3;

DemoState3::DemoState3()
: StateBaseClass(&DemoState3::doAction)
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


DemoState3& DemoState3::getInstance()
{
	static DemoState3 theInstance;
	return theInstance;
}
