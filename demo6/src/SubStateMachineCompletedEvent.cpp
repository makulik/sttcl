/*
 * SubStateMachineCompletedEvent.cpp
 *
 *  Created on: 25.03.2012
 *      Author: Admin
 */

#include "../SubStateMachineCompletedEvent.h"

namespace Application {

SubStateMachineCompletedEvent::SubStateMachineCompletedEvent() {
	// TODO Auto-generated constructor stub

}

SubStateMachineCompletedEvent::~SubStateMachineCompletedEvent() {
	// TODO Auto-generated destructor stub
}

std::ostream& SubStateMachineCompletedEvent::printData(std::ostream& os) const {
	os << "SubStateMachineCompletedEvent";
	return os;
}


} /* namespace Application */
