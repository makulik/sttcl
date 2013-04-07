/*
 * SubStateMachineCompletedEvent.h
 *
 *  Created on: 25.03.2012
 *      Author: Admin
 */

#ifndef SUBSTATEMACHINECOMPLETEDEVENT_H_
#define SUBSTATEMACHINECOMPLETEDEVENT_H_

#include "Event.h"

namespace Application
{

class SubStateMachineCompletedEvent
: public Application::Event
{
public:
	SubStateMachineCompletedEvent();
	virtual ~SubStateMachineCompletedEvent();

	virtual std::ostream& printData(std::ostream& os) const;
};

} /* namespace Application */
#endif /* SUBSTATEMACHINECOMPLETEDEVENT_H_ */
