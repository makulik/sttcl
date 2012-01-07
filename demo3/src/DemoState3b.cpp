/*
 * DemoState3b.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>

#include "../DemoState3b.h"
#include "../DemoState3.h"
#include "../DemoState3c.h"

using namespace std;
using namespace Application;
using Application::DemoState3b;

DemoState3b::DemoState3b()
: StateBaseClass()
{
}

DemoState3b::~DemoState3b()
{
}

void DemoState3b::handleEvent1(DemoState3* context)
{
	cout << "DemoState3b, handling event1 ..." << endl;
	if(context->getZ() == 3)
	{
		cout << "DemoState3b, guard [z == 3] passed" << endl;
		changeState(context,&DemoState3c::getInstance());
	}
	else
	{
		cout << "DemoState3b, guard [z == 3] enabled" << endl;
		context->initialize();
	}
}

void DemoState3b::handleEvent2(DemoState3* context)
{
	cout << "DemoState3b, handling event2 ..." << endl;
}

void DemoState3b::handleEvent3(DemoState3* context)
{
	cout << "DemoState3b, handling event3 ..." << endl;
}

void DemoState3b::handleEvent4(DemoState3* context)
{
	cout << "DemoState3b, handling event4 ..." << endl;
}

void DemoState3b::handleEvent5(DemoState3* context)
{
	cout << "DemoState3b, handling event5 ..." << endl;
}

void DemoState3b::entryImpl(DemoState3* context)
{
	cout << "DemoState3b, entering ..." << endl;
	StateBaseClass::entryImpl(context);
}

void DemoState3b::exitImpl(DemoState3* context)
{
	cout << "DemoState3b, exiting ..." << endl;
	StateBaseClass::exitImpl(context);
}

DemoState3b& DemoState3b::getInstance()
{
	static DemoState3b theInstance;
	return theInstance;
}
