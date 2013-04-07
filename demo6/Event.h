/*
 * Event.h
 *
 *  Created on: 21.03.2012
 *      Author: Admin
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <ostream>

namespace Application
{

class Event
{
public:
	Event();
	virtual ~Event();

	Event& operator=(const Event& rhs) { return *this; }

	virtual std::ostream& printData(std::ostream& os) const;

protected:
	Event(const Event& rhs) {}
};
} /* namespace Application */

std::ostream& operator<<(std::ostream& os, const Application::Event& event);

#endif /* EVENT_H_ */
