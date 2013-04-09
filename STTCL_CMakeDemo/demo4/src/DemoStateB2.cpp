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

void DemoStateB2::handleEvent1(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateB2, handling event1 ..." << endl;
	regionContext->getRegionContext<RegionB>()->finalize();
}
void DemoStateB2::handleEvent2(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateB2, handling event2 ..." << endl;
	changeState(regionContext->getRegionContext<RegionB>(),&DemoStateB1::getInstance());
}
void DemoStateB2::handleEvent3(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateB2, handling event3 ..." << endl;
}
void DemoStateB2::handleEvent4(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateB2, handling event4 ..." << endl;
}

void DemoStateB2::entryImpl(IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateB2, entering ..." << endl;
}

void DemoStateB2::exitImpl(IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateB2, exiting ..." << endl;
}

DemoStateB2& DemoStateB2::getInstance()
{
	static DemoStateB2 theInstance;
	return theInstance;
}
