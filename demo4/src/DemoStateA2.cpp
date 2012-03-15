/*
 * DemoStateA2.cpp
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#include "../DemoStateA2.h"
#include "../DemoStateA3.h"

#include <iostream>

using namespace std;
using namespace Application;

DemoStateA2::DemoStateA2()
{
}

DemoStateA2::~DemoStateA2()
{
}

void DemoStateA2::handleEvent1(IConcurrentStateMachine::Context* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateA2, handling event1 ..." << endl;
	regionContext->getRegionContext<RegionA>()->finalize();
}
void DemoStateA2::handleEvent2(IConcurrentStateMachine::Context* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateA2, handling event2 ..." << endl;
	changeState(regionContext->getRegionContext<RegionA>(),&DemoStateA3::getInstance());
}
void DemoStateA2::handleEvent3(IConcurrentStateMachine::Context* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateA2, handling event3 ..." << endl;
}
void DemoStateA2::handleEvent4(IConcurrentStateMachine::Context* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateA2, handling event4 ..." << endl;
}

void DemoStateA2::entryImpl(IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateA2, entering ..." << endl;
}

void DemoStateA2::exitImpl(IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateA2, exiting ..." << endl;
}

DemoStateA2& DemoStateA2::getInstance()
{
	static DemoStateA2 theInstance;
	return theInstance;
}
