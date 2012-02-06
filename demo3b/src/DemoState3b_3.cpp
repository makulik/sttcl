/*
 * DemoState3b_3.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>

#include "../DemoState3b.h"
#include "../DemoState3b_3.h"
#include "../DemoState3b_1.h"

using namespace std;
using namespace Application;
using Application::DemoState3b_3;

DemoState3b_3::DemoState3b_3()
: StateBaseClass()
{
}

DemoState3b_3::~DemoState3b_3()
{
}

void DemoState3b_3::handleEvent1(DemoState3b* context)
{
	cout << "DemoState3b_3, handling event1 ..." << endl;
	// no guards, change to DemoState3b_1
	changeState(context,&DemoState3b_1::getInstance());
}

void DemoState3b_3::handleEvent2(DemoState3b* context)
{
	cout << "DemoState3b_3, handling event2 ..." << endl;
}

void DemoState3b_3::handleEvent3(DemoState3b* context)
{
	cout << "DemoState3b_3, handling event3 ..." << endl;
}

void DemoState3b_3::handleEvent4(DemoState3b* context)
{
	cout << "DemoState3b_3, handling event4 ..." << endl;
}

void DemoState3b_3::handleEvent5(DemoState3b* context)
{
	cout << "DemoState3b_3, handling event5 ..." << endl;
}

void DemoState3b_3::entryImpl(DemoState3b* context)
{
	cout << "DemoState3b_3, entering ..." << endl;
	StateBaseClass::entryImpl(context);
}

void DemoState3b_3::exitImpl(DemoState3b* context)
{
	cout << "DemoState3b_3, exiting ..." << endl;
	StateBaseClass::exitImpl(context);
}

DemoState3b_3& DemoState3b_3::getInstance()
{
	static DemoState3b_3 theInstance;
	return theInstance;
}
