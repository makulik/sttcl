/*
 * DemoStateA3.cpp
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#include "../DemoStateA3.h"
#include "../DemoStateA1.h"
#include "../DemoStateA2.h"
#include <iostream>

using namespace std;
using namespace Application;

DemoStateA3::DemoStateA3()
{
}

DemoStateA3::~DemoStateA3()
{
}

void DemoStateA3::handleEvent1(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateA3, handling event1 ..." << endl;
	changeState(regionContext->getRegionContext<RegionA>(),&DemoStateA2::getInstance());
}
void DemoStateA3::handleEvent2(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateA3, handling event2 ..." << endl;
}
void DemoStateA3::handleEvent3(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateA3, handling event3 ..." << endl;
	changeState(regionContext->getRegionContext<RegionA>(),&DemoStateA1::getInstance());
}
void DemoStateA3::handleEvent4(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateA3, handling event4 ..." << endl;
}

void DemoStateA3::entryImpl(IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateA3, entering ..." << endl;
}

void DemoStateA3::exitImpl(IConcurrentStateMachine::RegionContext* regionContext)
{
	cout << "DemoStateA3, exiting ..." << endl;
}

DemoStateA3& DemoStateA3::getInstance()
{
	static DemoStateA3 theInstance;

	return theInstance;
}
