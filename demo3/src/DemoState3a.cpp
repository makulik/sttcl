/*
 * DemoState3a.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>

#include "../DemoState3a.h"
#include "../DemoState3.h"
#include "../DemoState3b.h"
#include "../DemoState3c.h"

using namespace std;
using namespace Application;
using Application::DemoState3a;

DemoState3a::DemoState3a()
: StateBaseClass()
{
}

DemoState3a::~DemoState3a()
{
}

void DemoState3a::handleEvent1(DemoState3* context)
{
	cout << "DemoState3a, handling event1 ..." << endl;
}

void DemoState3a::handleEvent2(DemoState3* context)
{
	cout << "DemoState3a, handling event2 ..." << endl;
	// no guards, change to state DemoState3c
	changeState(context,&DemoState3c::getInstance());
}

void DemoState3a::handleEvent3(DemoState3* context)
{
	cout << "DemoState3a, handling event3 ..." << endl;
}

void DemoState3a::handleEvent4(DemoState3* context)
{
	cout << "DemoState3a, handling event4 ..." << endl;
}

void DemoState3a::handleEvent5(DemoState3* context)
{
	cout << "DemoState3a, handling event5 ..." << endl;
	// no guards, change to state DemoState3b
	changeState(context,&DemoState3b::getInstance());
}

void DemoState3a::entryImpl(DemoState3* context)
{
	cout << "DemoState3a, entering ..." << endl;
	StateBaseClass::entryImpl(context);
}

void DemoState3a::exitImpl(DemoState3* context)
{
	cout << "DemoState3a, exiting ..." << endl;
	StateBaseClass::exitImpl(context);
}

DemoState3a& DemoState3a::getInstance()
{
	static DemoState3a theInstance;
	return theInstance;
}
