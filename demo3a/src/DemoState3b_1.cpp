/*
 * DemoState3b_1.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>

#include "../DemoState3b.h"
#include "../DemoState3b_1.h"
#include "../DemoState3b_2.h"

using namespace std;
using namespace Application;
using Application::DemoState3b_1;

DemoState3b_1::DemoState3b_1()
: StateBaseClass()
{
}

DemoState3b_1::~DemoState3b_1()
{
}

void DemoState3b_1::handleEvent1(DemoState3b* context)
{
	cout << "DemoState3b_1, handling event1 ..." << endl;
}

void DemoState3b_1::handleEvent2(DemoState3b* context)
{
	cout << "DemoState3b_1, handling event2 ..." << endl;
	// no guards, change to DemoState3b_2
	changeState(context,&DemoState3b_2::getInstance());
}

void DemoState3b_1::handleEvent3(DemoState3b* context)
{
	cout << "DemoState3b_1, handling event3 ..." << endl;
}

void DemoState3b_1::handleEvent4(DemoState3b* context)
{
	cout << "DemoState3b_1, handling event4 ..." << endl;
}

void DemoState3b_1::handleEvent5(DemoState3b* context)
{
	cout << "DemoState3b_1, handling event5 ..." << endl;
}

void DemoState3b_1::entryImpl(DemoState3b* context)
{
	cout << "DemoState3b_1, entering ..." << endl;
	StateBaseClass::entryImpl(context);
}

void DemoState3b_1::exitImpl(DemoState3b* context)
{
	StateBaseClass::exitImpl(context);
	cout << "DemoState3b_1, exiting ..." << endl;
}

DemoState3b_1& DemoState3b_1::getInstance()
{
	static DemoState3b_1 theInstance;
	return theInstance;
}
