/*
 * InputEvent.cpp
 *
 *  Created on: 21.03.2012
 *      Author: Admin
 */

#include "../InputEvent.h"

using namespace std;
using namespace Application;

using Application::InputEvent;

InputEvent::InputEvent(const std::string& argInput)
: input(argInput)
{
}

InputEvent::InputEvent(const InputEvent& rhs)
: input(rhs.input)
{
}


InputEvent::~InputEvent()
{
}

InputEvent& InputEvent::operator =(const InputEvent& rhs)
{
	input = rhs.input;
	return *this;
}
