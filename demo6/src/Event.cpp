/*
 * Event.cpp
 *
 *  Created on: 21.03.2012
 *      Author: Admin
 */

#include "../Event.h"

using namespace Application;

using Application::Event;

Event::Event()
{
}

Event::~Event()
{
}

std::ostream& Application::Event::printData(std::ostream& os) const {
	os << "Event: Unknown derivate.";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Application::Event& event) {
	return event.printData(os);
}
