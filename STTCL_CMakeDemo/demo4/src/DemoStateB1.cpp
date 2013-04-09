/*
 * DemoStateB1.cpp
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#include "../DemoStateB1.h"
#include "../DemoStateB2.h"
#include <iostream>

using namespace std;
using namespace Application;

DemoStateB1::DemoStateB1()
{
}

DemoStateB1::~DemoStateB1()
{
}

void DemoStateB1::handleEvent1(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateB1, handling event1 ..." << endl;
}
void DemoStateB1::handleEvent2(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateB1, handling event2 ..." << endl;
}
void DemoStateB1::handleEvent3(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateB1, handling event3 ..." << endl;
}
void DemoStateB1::handleEvent4(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateB1, handling event4 ..." << endl;
	changeState(regionContext->getRegionContext<RegionB>(),&DemoStateB2::getInstance());
}

void DemoStateB1::entryImpl(IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateB1, entering ..." << endl;
}

void DemoStateB1::exitImpl(IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateB1, exiting ..." << endl;
}

DemoStateB1& DemoStateB1::getInstance()
{
	static DemoStateB1 theInstance;
	return theInstance;
}
