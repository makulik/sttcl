/*
 * MainApplication.h
 *
 *  Created on: 22.03.2012
 *      Author: Admin
 */

#ifndef MAINAPPLICATION_H_
#define MAINAPPLICATION_H_

#include "DemoStateMachine.h"
#include <iostream>

namespace Application
{

class MainApplication
{
public:
	MainApplication(std::istream& argInput, DemoStateMachine& argStateMachine);
	virtual ~MainApplication();

	int run();

private:
	std::istream& input;
	DemoStateMachine& stateMachine;
};

} /* namespace Application */
#endif /* MAINAPPLICATION_H_ */
