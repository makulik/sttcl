/*
 * DemoStateA1.cpp
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#include "../DemoStateA1.h"
#include "../DemoStateA2.h"

#include <iostream>

using namespace std;
using namespace Application;

DemoStateA1::DemoStateA1()
{
}

DemoStateA1::~DemoStateA1()
{
}

void DemoStateA1::handleEvent1(IConcurrentStateMachine::Context* context, const void* eventArgs)
{
	cout << "DemoStateA1, handling event1 ..." << endl;
	changeState(context->getRegionContext<RegionA>(),&DemoStateA2::getInstance());
}
void DemoStateA1::handleEvent2(IConcurrentStateMachine::Context* context, const void* eventArgs)
{
	cout << "DemoStateA1, handling event2 ..." << endl;
}
void DemoStateA1::handleEvent3(IConcurrentStateMachine::Context* context, const void* eventArgs)
{
	cout << "DemoStateA1, handling event3 ..." << endl;
}
void DemoStateA1::handleEvent4(IConcurrentStateMachine::Context* context, const void* eventArgs)
{
	cout << "DemoStateA1, handling event4 ..." << endl;
}

void DemoStateA1::entryImpl(IConcurrentStateMachine::Context* context)
{
	cout << "DemoStateA1, entering ..." << endl;
}

void DemoStateA1::exitImpl(IConcurrentStateMachine::Context* context)
{
	cout << "DemoStateA1, exiting ..." << endl;
}

DemoStateA1& DemoStateA1::getInstance()
{
	static DemoStateA1 theInstance;
	return theInstance;
}
