/*
 * DemoState3b_2.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>

#include "../DemoState3b.h"
#include "../DemoState3b_2.h"
#include "../DemoState3b_3.h"

using namespace std;
using namespace Application;
using Application::DemoState3b_2;

DemoState3b_2::DemoState3b_2()
: StateBaseClass()
{
}

DemoState3b_2::~DemoState3b_2()
{
}

void DemoState3b_2::handleEvent1(DemoState3b* context)
{
	cout << "DemoState3b_2, handling event1 ..." << endl;
}

void DemoState3b_2::handleEvent2(DemoState3b* context)
{
	cout << "DemoState3b_2, handling event2 ..." << endl;
}

void DemoState3b_2::handleEvent3(DemoState3b* context)
{
	cout << "DemoState3b_2, handling event3 ..." << endl;
	// no guards, change to DemoState3b_3
	changeState(context,&DemoState3b_3::getInstance());
}

void DemoState3b_2::handleEvent4(DemoState3b* context)
{
	cout << "DemoState3b_2, handling event4 ..." << endl;
}

void DemoState3b_2::handleEvent5(DemoState3b* context)
{
	cout << "DemoState3b_2, handling event5 ..." << endl;
}

void DemoState3b_2::entryImpl(DemoState3b* context)
{
	cout << "DemoState3b_2, entering ..." << endl;
	StateBaseClass::entryImpl(context);
}

void DemoState3b_2::exitImpl(DemoState3b* context)
{
	StateBaseClass::exitImpl(context);
	cout << "DemoState3b_2, exiting ..." << endl;
}

DemoState3b_2& DemoState3b_2::getInstance()
{
	static DemoState3b_2 theInstance;
	return theInstance;
}
