/*
 * EventArgsClass.cpp
 *
 *  Created on: 14.03.2012
 *      Author: Admin
 */

#include <iostream>
#include "../EventArgsClass.h"

using namespace std;
using namespace Application;
using Application::EventArgsClass;

EventArgsClass::EventArgsClass(const string& argData)
: data(argData)
{
	//cout << "EventArgsClass('" << data << "')" << endl;
}

EventArgsClass::~EventArgsClass()
{
	//cout << "~EventArgsClass()" << endl;
}
