/*
 * Event.h
 *
 *  Created on: 21.03.2012
 *      Author: Admin
 */

#ifndef EVENT_H_
#define EVENT_H_

namespace Application
{

class Event
{
public:
	Event();
	Event(const Event& rhs) {}
	virtual ~Event();

	Event& operator=(const Event& rhs) { return *this; }
};

} /* namespace Application */
#endif /* EVENT_H_ */
