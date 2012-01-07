/*
 * DemoState2.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>
#include "../DemoStateMachine.h"
#include "../DemoState2.h"

using namespace std;
using namespace Application;
using Application::DemoState2;

DemoState2::DemoState2()
: StateBaseClass()
{
}

DemoState2::~DemoState2()
{
}

void DemoState2::handleEvent1(DemoStateMachine* context)
{
	cout << "DemoState2, handling event1 ..." << endl;
	if(context->getY() < 4)
	{
		cout << "DemoState2, guard [y > 4] passed" << endl;
		changeState(context,context->getDemoState3());
	}
	else
	{
		cout << "DemoState2, guard [y > 4] enabled" << endl;
	}
}

void DemoState2::handleEvent2(DemoStateMachine* context)
{
	cout << "DemoState2, handling event2 ..." << endl;
}

void DemoState2::handleEvent3(DemoStateMachine* context)
{
	cout << "DemoState2, handling event3 ..." << endl;
}

void DemoState2::handleEvent4(DemoStateMachine* context)
{
	cout << "DemoState2, handling event4 ..." << endl;
}

void DemoState2::handleEvent5(DemoStateMachine* context)
{
	cout << "DemoState2, handling event5 ..." << endl;
}

void DemoState2::entryImpl(DemoStateMachine* context)
{
	cout << "DemoState2, entering ..." << endl;
	StateBaseClass::entryImpl(context);
}

void DemoState2::exitImpl(DemoStateMachine* context)
{
	cout << "DemoState2, exiting ..." << endl;
	StateBaseClass::exitImpl(context);
}

DemoState2& DemoState2::getInstance()
{
	static DemoState2 theInstance;
	return theInstance;
}
