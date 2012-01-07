/*
 * DemoStateB2.cpp
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#include "../DemoStateB2.h"
#include "../DemoStateB1.h"
#include <iostream>

using namespace std;
using namespace Application;

DemoStateB2::DemoStateB2()
{
}

DemoStateB2::~DemoStateB2()
{
}

void DemoStateB2::handleEvent1(IConcurrentStateMachine::Context* context,const void* eventArgs)
{
	cout << "DemoStateB2, handling event1 ..." << endl;
	context->getRegionContext<RegionB>()->finalize();
}
void DemoStateB2::handleEvent2(IConcurrentStateMachine::Context* context,const void* eventArgs)
{
	cout << "DemoStateB2, handling event2 ..." << endl;
	changeState(context->getRegionContext<RegionB>(),&DemoStateB1::getInstance());
}
void DemoStateB2::handleEvent3(IConcurrentStateMachine::Context* context,const void* eventArgs)
{
	cout << "DemoStateB2, handling event3 ..." << endl;
}
void DemoStateB2::handleEvent4(IConcurrentStateMachine::Context* context,const void* eventArgs)
{
	cout << "DemoStateB2, handling event4 ..." << endl;
}

void DemoStateB2::entryImpl(IConcurrentStateMachine::Context* context)
{
	cout << "DemoStateB2, entering ..." << endl;
}

void DemoStateB2::exitImpl(IConcurrentStateMachine::Context* context)
{
	cout << "DemoStateB2, exiting ..." << endl;
}

DemoStateB2& DemoStateB2::getInstance()
{
	static DemoStateB2 theInstance;
	return theInstance;
}
