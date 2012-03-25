/*
 * InputEvent.h
 *
 *  Created on: 21.03.2012
 *      Author: Admin
 */

#ifndef INPUTEVENT_H_
#define INPUTEVENT_H_

#include "Event.h"
#include <string>

namespace Application
{

class InputEvent
: public Event
{
public:
	InputEvent(const std::string& argInput);
	InputEvent(const InputEvent& rhs);
	virtual ~InputEvent();

	InputEvent& operator=(const InputEvent& rhs);

	const std::string& getInput() const
	{
		return input;
	}
private:
	std::string input;
};

} /* namespace Application */
#endif /* INPUTEVENT_H_ */
