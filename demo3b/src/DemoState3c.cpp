/*
 * DemoState3c.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>

#include "DemoState3c.h"

using namespace std;
using namespace Application;
using Application::DemoState3c;

DemoState3c::DemoState3c()
: StateBaseClass()
{
}

DemoState3c::~DemoState3c()
{
}

void DemoState3c::handleEvent1(DemoState3* context)
{
	cout << "DemoState3c, handling event1 ..." << endl;
}

void DemoState3c::handleEvent2(DemoState3* context)
{
	cout << "DemoState3c, handling event2 ..." << endl;
}

void DemoState3c::handleEvent3(DemoState3* context)
{
	cout << "DemoState3c, handling event3 ..." << endl;
}

void DemoState3c::handleEvent4(DemoState3* context)
{
	cout << "DemoState3c, handling event4 ..." << endl;
	// no guards, finalize sub state machine
	context->finalize();
}

void DemoState3c::handleEvent5(DemoState3* context)
{
	cout << "DemoState3c, handling event5 ..." << endl;
}

void DemoState3c::entryImpl(DemoState3* context)
{
	cout << "DemoState3c, entering ..." << endl;
	StateBaseClass::entryImpl(context);
}

void DemoState3c::exitImpl(DemoState3* context)
{
	cout << "DemoState3c, exiting ..." << endl;
	StateBaseClass::exitImpl(context);
}

DemoState3c& DemoState3c::getInstance()
{
	static DemoState3c theInstance;
	return theInstance;
}
